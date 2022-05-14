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

	// Block player movement
	app->scene->player->canMove = false;

	if (app->battle->isEnabled()) {
		inventoryOnBattle = true;
	}

	// Load assets

	if (inventoryOnBattle == false) {
		inventoryBG = app->tex->Load("Assets/gui/inventory/ui_inventory.png");
	}
	else {
		inventoryBG = app->tex->Load("Assets/gui/inventory/ui_inventory_battle.png");
	}

	// Esta deberia ir con un animation que cada frame sea cada arma
	//weaponType = app->tex->Load("Assets/gui/inventory/ui_inventory.png");

	// Buttons
	backButton = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 298, "Back", { (-app->camera->GetPos().x / 2) + 20, (-app->camera->GetPos().y / 2) + 10, 74, 32 }, this);
	statsButton = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 299, "Stats", { (-app->camera->GetPos().x / 2) + 20, (-app->camera->GetPos().y / 2) + 45, 74, 32 }, this);

	backButtonTexture = app->tex->Load("Assets/gui/buttons/back_text.png");
	backButtonPressedTexture = app->tex->Load("Assets/gui/buttons/pressed_back_text.png");

	statsButtonTexture = app->tex->Load("Assets/gui/buttons/stats.png");
	statsButtonPressedTexture = app->tex->Load("Assets/gui/buttons/pressed_stats.png");

	selectorItems = app->tex->Load("Assets/gui/inventory/selector_items.png");
	selectorCharacters = app->tex->Load("Assets/gui/inventory/selector_personaje.png");

	itemInfo = app->tex->Load("Assets/gui/inventory/ui_inventory_info.png");

	int x = -app->camera->GetPos().x / 2,
		y = -app->camera->GetPos().y / 2,
		butX = x + 270,
		butY = y + 136,
		charX = x + 105,
		charY = y + 7,
		specialX = x + 270,
		specialY = y + 292,
		equipX = x + 112,
		equipY = y + 172;

	selectorItemPos = lastItemPos = { butX, butY };
	selectorCharsPos = lastCharPos = { charX, charY };

	// Crear "botones" de la UI || ITEMS
	for (int i = 0; i < inventorySlots; i++) {
		if (i == 5) {
			butX = x + 270;
			butY = y + 196;
		}
		Slot* s = new Slot({ butX,butY }, {45, 45}, nullptr, false);

		slots.add(s);

		s = nullptr;
		delete s;

		butX += 67;
	}

	// Crear "botones" de la UI || Special Items
	for (int i = 0; i < inventorySpecialSlots; i++) {
		Slot* s = new Slot({ specialX, specialY }, { 45, 45 }, nullptr, false);

		slots.add(s);

		s = nullptr;
		delete s;

		specialX += 67;
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

	// SFX
	buttonSfx = app->audio->LoadFx("Assets/audio/sfx/fx_select_confirm.wav");
	moveSfx = app->audio->LoadFx("Assets/audio/sfx/fx_select_next_2.wav");
	backSfx = app->audio->LoadFx("Assets/audio/sfx/fx_select_back.wav");

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

	if (&slots != nullptr) {
		for (ListItem<Slot*>* s = slots.start; s != NULL; s = s->next) {

			// Selectors 
			if ((mouseX > s->data->position.x) && (mouseX < (s->data->position.x + s->data->size.x)) &&
				(mouseY > s->data->position.y) && (mouseY < (s->data->position.y + s->data->size.y))) {

				if (s->data->isItem || s->data->isEquipment) {
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
						app->audio->PlayFx(buttonSfx);
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

	return true;
}

// Render bullshit
bool Inventory::PostUpdate()
{
	bool ret = true;

	int x = -app->camera->GetPos().x / 2,
		y = -app->camera->GetPos().y / 2;

	// Draw UI

	app->render->DrawTexture(inventoryBG, x, y);

	if (&slots != nullptr) {
		for (ListItem<Slot*>* s = slots.start; s != NULL; s = s->next) {

			// ======================
			//    MENU EQUIPACION 
			// ======================

			int equipX = x + 9,
				equipY = y + 83;

			if (s->data->isCharacter && s->data->activated) {
				app->font->DrawText(s->data->asignedCharacter->name, equipX + 24, equipY + 13);
				
				app->render->DrawTexture(s->data->asignedCharacter->spriteTex, equipX, equipY + 30, &s->data->asignedCharacter->currentAnimation->GetCurrentFrame());
			}
		}
	}

	backButton->state != GuiControlState::PRESSED ? app->render->DrawTexture(backButtonTexture, backButton->bounds.x, backButton->bounds.y) : app->render->DrawTexture(backButtonPressedTexture, backButton->bounds.x, backButton->bounds.y);
	statsButton->state != GuiControlState::PRESSED ? app->render->DrawTexture(statsButtonTexture, statsButton->bounds.x, statsButton->bounds.y) : app->render->DrawTexture(statsButtonPressedTexture, statsButton->bounds.x, statsButton->bounds.y);

	app->render->DrawTexture(selectorItems, selectorItemPos.x, selectorItemPos.y);
	app->render->DrawTexture(selectorCharacters, selectorCharsPos.x, selectorCharsPos.y);

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

	app->scene->showLocation = true;

	app->tex->UnLoad(backButtonTexture);
	app->tex->UnLoad(backButtonPressedTexture);
	app->tex->UnLoad(statsButtonPressedTexture);
	app->tex->UnLoad(statsButtonTexture);
	app->tex->UnLoad(selectorCharacters);
	app->tex->UnLoad(selectorItems);
	app->tex->UnLoad(itemInfo);

	buttonSfx = NULL;

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
			Disable();
			app->stmen->Enable();
			app->audio->PlayFx(buttonSfx);
		}

		default: break;
		}
	}
	return true;
}
