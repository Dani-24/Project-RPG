#include "App.h"
#include "Inventory.h"
#include "StatsMenu.h"

#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"

#include "Scene.h"
#include "Stages.h"
#include "GuiManager.h"
#include "FadeToBlack.h"
#include "Player.h"
#include "Camera.h"

#include "Battle.h"

Inventory::Inventory(App* application, bool start_enabled) : Module(application, start_enabled)
{
	name.Create("inventory");
}

Inventory::~Inventory()
{}

bool Inventory::Awake(pugi::xml_node& config)
{
	LOG("Awakening Inventory");
	bool ret = true;

	return ret;
}

bool Inventory::Start()
{
	LOG("Starting Inventory");

	srand(SDL_GetTicks());

	// Block player movement
	app->scene->player->canMove = false;

	if (app->battle->isEnabled()) {
		inventoryOnBattle = true;
	}

	// Load assets

	inventoryBG = app->tex->Load("Assets/gui/inventory/ui_inventory.png");

	// Esta deberia ir con un animation que cada frame sea cada arma
	//weaponType = app->tex->Load("Assets/gui/inventory/ui_inventory.png");

	// Buttons
	backButton = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 298, "Back", { (-app->camera->GetPos().x / 2) + 20, (-app->camera->GetPos().y / 2) + 10, 74, 32 }, this);
	statsButton = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 299, "Stats", { (-app->camera->GetPos().x / 2) + 20, (-app->camera->GetPos().y / 2) + 45, 74, 32 }, this);
	statsButton->state = GuiControlState::DISABLED;

	backButtonTexture = app->tex->Load("Assets/gui/buttons/back_text.png");
	backButtonPressedTexture = app->tex->Load("Assets/gui/buttons/pressed_back_text.png");

	statsButtonTexture = app->tex->Load("Assets/gui/buttons/stats.png");
	statsButtonPressedTexture = app->tex->Load("Assets/gui/buttons/pressed_stats.png");

	selectorItems = app->tex->Load("Assets/gui/inventory/selector_items.png");
	selectorCharacters = app->tex->Load("Assets/gui/inventory/selector_personaje.png");

	itemInfo = app->tex->Load("Assets/gui/inventory/ui_inventory_info.png");

	int x = -app->camera->GetPos().x / 2,
		y = -app->camera->GetPos().y / 2;

	int	butX = x + 270,
		butY = y + 154,
		charX = x + 105,
		charY = y + 7,
		equipX = x + 112,
		equipY = y + 172;

	selectorItemPos = lastItemPos = { butX, butY };
	selectorCharsPos = lastCharPos = { charX, charY };

	// Crear "botones" de la UI || ITEMS
	ListItem<Item*>* obtainedItem = app->scene->itemList.start;

	for (int i = 0; i < inventorySlots; i++) {
		if (i == 5) {
			butX = x + 270;
			butY = y + 214;
		}
		if (i == 10) {
			butX = x + 270;
			butY = y + 274;
		}

		if (obtainedItem != NULL) {
			Slot* s = new Slot({ butX,butY }, { 45, 45 }, obtainedItem->data, false);

			slots.add(s);

			s = nullptr;
			delete s;

			obtainedItem = obtainedItem->next;
		}
		else {
			Slot* s = new Slot({ butX,butY }, { 45, 45 }, nullptr, false);

			slots.add(s);

			s = nullptr;
			delete s;
		}

		butX += 67;
	}

	// Crear "botones" de la UI || Equipment
	for (int i = 0; i < 7; i++)
	{
		if (i == 2) {
			equipX = x + 112;
			equipY = y + 220;
		}
		if (i == 4) {
			equipX = x + 112;
			equipY = y + 283;
		}
		if (i == 6) {
			equipX = x + 39;
		}

		Slot* s = new Slot({ equipX, equipY }, { 45, 45 }, nullptr, true);

		slots.add(s);

		s = nullptr;
		delete s;
		equipX += 48;
	}

	// Crear "botones" de la UI || Characters
	for (ListItem<Character*>* party = app->scene->partyList.start; party != NULL; party = party->next)
	{
		Slot* s = new Slot({ charX, charY }, { 121, 67 }, party->data);

		slots.add(s);
		s = nullptr;
		delete s;

		charX += 130;
	}

	// Botones al seleccionar items de la UI
	itemUseButton = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 300, "  Use", { x, y, 74, 32 }, this, true);
	itemBackButon = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 301, " Cancel", { x, y, 74, 32 }, this, true);
	itemInfoButton = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 302, "  Info", { x, y, 74, 32 }, this, true);
	itemInfoCloseButton = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 303, "  Close", { x + 80, y + 320, 74, 32 }, this, true);

	itemUseButton->state = itemBackButon->state = itemInfoButton->state = itemInfoCloseButton->state = GuiControlState::DISABLED;

	// SFX
	buttonSfx = app->audio->LoadFx("Assets/audio/sfx/fx_select_confirm.wav");
	moveSfx = app->audio->LoadFx("Assets/audio/sfx/fx_select_next_2.wav");
	backSfx = app->audio->LoadFx("Assets/audio/sfx/fx_select_back.wav");
	useSfx = app->audio->LoadFx("Assets/audio/sfx/fx_item_use.wav");

	app->scene->showLocation = false;

	return true;
}

bool Inventory::PreUpdate()
{
	bool ret = true;

	return ret;
}

bool Inventory::Update(float dt)
{

	if (app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_UP) {
		Disable();
	}

	app->scene->guiactivate = true;

	// Get Mouse position for selected Slot

	int mouseX, mouseY;
	app->input->GetMousePosition(mouseX, mouseY);
	mouseX -= app->camera->GetPos().x / 2;
	mouseY -= app->camera->GetPos().y / 2;

		if (itemBackButon->state == GuiControlState::DISABLED) {
			if (&slots != nullptr) {
				for (ListItem<Slot*>* s = slots.start; s != NULL; s = s->next) {

					// Selectors 
					if ((mouseX > s->data->position.x) && (mouseX < (s->data->position.x + s->data->size.x)) &&
						(mouseY > s->data->position.y) && (mouseY < (s->data->position.y + s->data->size.y))) {

						if (s->data->isEquipment && itemInfoCloseButton->state == GuiControlState::DISABLED) {
							selectorItemPos = s->data->position;
							s->data->isSelected = true;
						}
						else if (s->data->isItem) {
							selectorItemPos = s->data->position;
							s->data->isSelected = true;
						}
						else if (s->data->isCharacter) {
							selectorCharsPos = s->data->position;
							s->data->isSelected = true;
						}

						if (selectorItemPos != lastItemPos || selectorCharsPos != lastCharPos) {
							app->audio->PlayFx(moveSfx);

							lastItemPos = selectorItemPos;
							lastCharPos = selectorCharsPos;
						}
						if (app->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KeyState::KEY_DOWN)
						{
							if (s->data->isCharacter == false) {
								if (s->data->asignedItem != nullptr) {
									app->audio->PlayFx(buttonSfx);

									// SHOW selected item UI
									if (s->data->asignedItem->usableFromInventory) {
										itemUseButton->state = GuiControlState::NORMAL;
									}
									itemInfoButton->state = itemBackButon->state = GuiControlState::NORMAL;

									if (s->data->position.x > -app->camera->GetPos().x / 2 + 520) {
										itemUseButton->SetPos({ s->data->position.x - 75, s->data->position.y - 15 });
										itemInfoButton->SetPos({ s->data->position.x - 75, s->data->position.y + 15 });
										itemBackButon->SetPos({ s->data->position.x - 75, s->data->position.y + 45 });
									}
									else {
										itemUseButton->SetPos({ s->data->position.x + 50, s->data->position.y - 15 });
										itemInfoButton->SetPos({ s->data->position.x + 50, s->data->position.y + 15 });
										itemBackButon->SetPos({ s->data->position.x + 50, s->data->position.y + 45 });
									}
								}
							}

						}
					}
					else {
						s->data->isSelected = false;
					}

					if (s->data->isCharacter) {
						if (selectorCharsPos == s->data->position) {
							s->data->activated = true;
						}
						else {
							s->data->activated = false;
						}
					}
				}
			}
		}

	return true;
}

// Render bullshit
bool Inventory::PostUpdate()
{
	bool ret = true;

	int x = -app->camera->GetPos().x / 2,
		y = -app->camera->GetPos().y / 2;

	// Draw UI

	if (app->battle->isEnabled()) {
		app->scene->ShowGUI();
	}

	app->render->DrawTexture(inventoryBG, x, y);

	char moneyText[100];
	sprintf_s(moneyText, "%d money", app->scene->player->PlayerMoney);
	app->font->DrawText(moneyText, x + 120, y + 100);

	if (&slots != nullptr) {
			for (ListItem<Slot*>* s = slots.start; s != NULL; s = s->next) {

				// ======================
				//    MENU EQUIPACION 
				// ======================

				int equipX = x + 9,
					equipY = y + 83;

				if (s->data->isCharacter && s->data->activated) {
					app->font->DrawText(s->data->asignedCharacter->name, equipX + 24, equipY + 13);

					if (s->data->asignedCharacter->spriteTex != nullptr) {
						//app->render->DrawTexture(s->data->asignedCharacter->spriteTex, equipX, equipY + 30, &s->data->asignedCharacter->currentAnimation->GetCurrentFrame());
					}
				}

				if (s->data->asignedItem != nullptr) // Draw items & equipment
				{
					app->render->DrawTexture(s->data->asignedItem->spriteTex, s->data->position.x, s->data->position.y, &s->data->asignedItem->spriteRect);
				}
			}

			backButton->state != GuiControlState::PRESSED ? app->render->DrawTexture(backButtonTexture, backButton->bounds.x, backButton->bounds.y) : app->render->DrawTexture(backButtonPressedTexture, backButton->bounds.x, backButton->bounds.y);
			statsButton->state != GuiControlState::PRESSED ? app->render->DrawTexture(statsButtonTexture, statsButton->bounds.x, statsButton->bounds.y) : app->render->DrawTexture(statsButtonPressedTexture, statsButton->bounds.x, statsButton->bounds.y);

			app->render->DrawTexture(selectorItems, selectorItemPos.x, selectorItemPos.y);
			app->render->DrawTexture(selectorCharacters, selectorCharsPos.x, selectorCharsPos.y);

			if (itemInfoCloseButton->state != GuiControlState::DISABLED) {
				app->render->DrawTexture(itemInfo, x + 9, y + 83);

				for (ListItem<Slot*>* s = slots.start; s != NULL; s = s->next) {
					if (s->data->isSelected && s->data->asignedItem != nullptr) {
						app->render->DrawTexture(s->data->asignedItem->spriteTex, x + 20, y + 150, &s->data->asignedItem->spriteRect);
						if (s->data->asignedItem->name != NULL) {
							app->font->DrawText(s->data->asignedItem->name, x + 75, y + 155, {0,0,0});
							app->font->DrawText(s->data->asignedItem->effect, x + 30, y + 200);
							app->font->DrawText(s->data->asignedItem->description, x + 15, y + 250);
						}
					}
				}

			}

		}
	if (statsButton->state == GuiControlState::DISABLED)statsButton->state = GuiControlState::NORMAL;


	return ret;
}

bool Inventory::CleanUp()
{
	LOG("Closing Inventory");

	// Allow player to move
	app->scene->player->canMove = true;

	inventoryOnBattle = false;

	backButton->state = GuiControlState::DISABLED;
	statsButton->state = GuiControlState::DISABLED;

	if (itemUseButton != nullptr) {
		itemUseButton->state = itemBackButon->state = itemInfoButton->state = itemInfoCloseButton->state = GuiControlState::DISABLED;
	}

	app->scene->showLocation = true;

	app->tex->UnLoad(backButtonTexture);
	app->tex->UnLoad(backButtonPressedTexture);
	app->tex->UnLoad(statsButtonPressedTexture);
	app->tex->UnLoad(statsButtonTexture);
	app->tex->UnLoad(selectorCharacters);
	app->tex->UnLoad(selectorItems);
	app->tex->UnLoad(itemInfo);

	slots.clear();

	buttonSfx = backSfx = moveSfx = useSfx = NULL;

	return true;
}

bool Inventory::OnGuiMouseClickEvent(GuiControl* control)
{
	switch (control->type)
	{		
	case GuiControlType::BUTTON:
	{
			//Checks the GUI element ID
		if (control->id == 298)
		{
			LOG("Click on Back");

			app->audio->PlayFx(backSfx);

			Disable();
		}

		if (control->id == 299)
		{
			LOG("Stats button");
			statsButton->state = GuiControlState::DISABLED;
			app->stmen->Enable();
			Disable();
			
			app->audio->PlayFx(buttonSfx);
		}

		if (control->id == 300) {
			LOG("Use item");
			app->audio->PlayFx(useSfx);

			for (ListItem<Slot*>* s = slots.start; s != NULL; s = s->next) {
				if (s->data->isSelected) {
					// Consume item
					if (s->data->isItem) {
						for (ListItem<Item*>* it = app->scene->itemList.start; it != NULL; it = it->next) {
							if (it->data == s->data->asignedItem) 
							{
								for (ListItem<Slot*>* ch = slots.start; ch != NULL; ch = ch->next) {
									if (ch->data->isCharacter && ch->data->activated && it->data->itemType == ItemType::USABLE) {

										LOG("Using %s item on %d", it->data->name, ch->data->asignedCharacter->name);

										AddStats(ch->data->asignedCharacter, (Usable*)it->data);

										break;
									}
								}

								// Delete item from inventory & close menu
								s->data->asignedItem = nullptr;
								app->scene->itemList.del(it);

								itemUseButton->state = itemBackButon->state = itemInfoButton->state = itemInfoCloseButton->state = GuiControlState::DISABLED;
								break;
							}
						}
					}

					// Equip equipment


					// Take out equipment
				}
			}
		}

		if (control->id == 301) {
			LOG("Back item");
			itemUseButton->state = itemInfoButton->state = itemBackButon->state = itemInfoCloseButton->state = GuiControlState::DISABLED;
			app->audio->PlayFx(backSfx);
		}

		if (control->id == 302) {
			LOG("Show info item");
			itemInfoCloseButton->state = GuiControlState::NORMAL;
			app->audio->PlayFx(buttonSfx);

		}

		if (control->id == 303) {
			LOG("Close info item");
			itemInfoCloseButton->state = GuiControlState::DISABLED;
			app->audio->PlayFx(backSfx);
		}

		default: break;
		}
	}
	return true;
}

void Inventory::AddStats(Character* character, Usable* item) {

	int addHP,
		addMaxHP,
		addMP,
		addMaxMP,
		addAttack,
		addDefense,
		addSpeed,
		addExp,
		add = 10,
	    randomValue = rand() % 7,
		badChance = rand() % 10;

	switch (item->usableType)
	{
	case UsableType::APPLE:

		addHP = 5;

		if (character->stats->health < character->stats->maxHealth - addHP) {
			character->stats->health += addHP;
		}
		else {
			character->stats->health = character->stats->maxHealth;
		}

		break;
	case UsableType::LIFE_POTION:

		addHP = 10;

		if (character->stats->health < character->stats->maxHealth - addHP) {
			character->stats->health += addHP;
		}
		else {
			character->stats->health = character->stats->maxHealth;
		}

		break;
	case UsableType::PIE:

		addSpeed = 1;

		character->stats->speed+= addSpeed;

		break;
	case UsableType::DELICIOUS_PIE:

		addSpeed = 10;

		character->stats->speed += addSpeed;

		break;
	case UsableType::CANDY:

		addExp = 100;

		character->stats->exp += addExp;

		break;
	case UsableType::MEAT:

		addMaxHP = 10;

		character->stats->maxHealth += addMaxHP;
		character->stats->health += addMaxHP;

		break;
	case UsableType::EGG:

		addDefense = 1;

		character->stats->defense += addDefense;

		break;
	case UsableType::FRIED_EGG:

		addDefense = 5;

		character->stats->defense += addDefense;

		break;
	case UsableType::HAMBURGER:

		addHP = 15;
		addSpeed = -1;

		if (character->stats->health < character->stats->maxHealth - addHP) {
			character->stats->health += addHP;
		}
		else {
			character->stats->health = character->stats->maxHealth;
		}

		character->stats->speed += addSpeed;

		break;
	case UsableType::ELIXIR:

		addMP = 20;

		if (character->stats->mana < character->stats->maxMana - addMP) {
			character->stats->mana += addMP;
		}
		else {
			character->stats->mana = character->stats->maxMana;
		}

		break;
	case UsableType::DYNAMITE:
		break;
	case UsableType::BOMB:
		break;
	case UsableType::SUPER_BOMB:
		break;
	case UsableType::PILL:

		if (badChance == 0) {
			add = -add;
		}

		switch (randomValue)
		{
		case 0:

			// Add HP

			if (character->stats->health < character->stats->maxHealth - add) {
				character->stats->health += add;
			}
			else {
				character->stats->health = character->stats->maxHealth;
			}

			break;
		case 1:

			// Add Max HP

			character->stats->maxHealth += add;
			character->stats->health += add;

			break;
		case 2:

			// Add mana

			if (character->stats->mana < character->stats->maxMana - add) {
				character->stats->mana += add;
			}
			else {
				character->stats->mana = character->stats->maxMana;
			}

			break;
		case 3:

			// Add max mana

			character->stats->maxMana += add;
			character->stats->mana += add;

			break;
		case 4:

			// add attack

			character->stats->attack += add;

			break;
		case 5:

			// add defense
			character->stats->defense += add;

			break;
		default:

			// Chance to do absolutely nothing

			break;
		}
		
		break;
	case UsableType::WILL_TO_LIFE:
		break;
	case UsableType::CHEST_KEY:
		break;
	case UsableType::DOOR_KEY:
		break;
	case UsableType::TEDDY_BEAR:

		addMaxMP = 5;

		character->stats->maxMana += addMaxMP;
		character->stats->mana += addMaxMP;

		break;
	case UsableType::LETTER:
		break;
	case UsableType::CLOSE_PARCHMENT:
		break;
	case UsableType::OPEN_PARCHMENT:
		break;
	case UsableType::BAT_WING:
		break;
	case UsableType::EYE:
		break;
	case UsableType::BONE:
		break;
	default:
		break;
	}

}