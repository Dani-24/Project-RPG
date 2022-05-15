#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "Scene.h"
#include "Map.h"
#include "GuiManager.h"
#include "FadeToBlack.h"
#include "Player.h"
#include "PauseMenu.h"
#include "StatsMenu.h"

#include "Battle.h"
#include "Stages.h"
#include "ModuleQFonts.h"
#include "Camera.h"

#include "NormalEnemy.h"
#include "NPC.h"
#include "EntityManager.h"

#include "Party.h"
#include "Inventory.h"

#include "StaticEntity.h"
#include "Item.h"

#include "Defs.h"
#include "Log.h"

#include <time.h>

Scene::Scene(App* application, bool start_enabled) : Module(application, start_enabled)
{
	name.Create("scene");
}

Scene::~Scene()
{}

bool Scene::Awake(pugi::xml_node& config)
{
	LOG("Loading Scene");
	bool ret = true;

	return ret;
}

bool Scene::Start()
{
	LOG("Starting Scene");
	
	// Apple just for inventory testing
	AddItem(UsableType::APPLE);

	// Enables & idk
	app->map->Enable();
	app->dialogs->Enable();

	// Load textures
	backFx = app->audio->LoadFx("Assets/audio/sfx/fx_select_back.wav");
	loadFx = app->audio->LoadFx("Assets/audio/sfx/fx_load.wav");
	saveFx = app->audio->LoadFx("Assets/audio/sfx/fx_save.wav");

	//buttons
	restart = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 40, "Restart", { 280, 280 , 74, 32 }, this);
	backtoMenu = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 41, "BackToMenu", { 240, 280 , 150, 32 }, this);
	restartTex = app->tex->Load("Assets/gui/buttons/button_restart.png");
	press_restartTex = app->tex->Load("Assets/gui/buttons/pressed_button_restart.png");
	backtoMenuTex = app->tex->Load("Assets/gui/buttons/button_back_to_menu.png");
	press_backtoMenuTex = app->tex->Load("Assets/gui/buttons/pressed_button_back_to_menu.png");
	locationUI = app->tex->Load("Assets/gui/inventory/ui_localizacion.png");

	// Player Entity
	player = (Player*)app->entities->CreateEntity(CharacterType::PLAYER, 950, 1730);

	/*Party* valion = (Party*)app->entities->CreateEntity(PartyType::VALION, 20, 50);
	partyList.add(valion);*/

	app->stages->playerPtr = player;
	app->camera->SetTarget(player);
	partyList.add(player);

	app->stages->partyListPtr = &partyList;

	// NPCs
	iPoint cockPos = { 900, 1400 };
	iPoint barkeeperPos = { 450, 300 };
	iPoint trainerPos = { 290, 160 };
	iPoint merchantPos = { 255, 150 };
	iPoint emilioPos = { 850, 200 };
	iPoint fuentePos = { 380, 1390 };
	iPoint cartelSudTownPos = { 1000, 1764 };

	NPC* cock = (NPC*)app->entities->CreateEntity(NPCType::COCK, cockPos.x, cockPos.y);
	npcList.add(cock);
	cock->activeOnStage = StageIndex::TOWN;

	NPC* barkeeper = (NPC*)app->entities->CreateEntity(NPCType::BARKEEPER, barkeeperPos.x, barkeeperPos.y);
	npcList.add(barkeeper);
	barkeeper->activeOnStage = StageIndex::TAVERN;

	NPC* trainer = (NPC*)app->entities->CreateEntity(NPCType::TRAINER, trainerPos.x, trainerPos.y);
	npcList.add(trainer);
	trainer->activeOnStage = StageIndex::DOJO;

	NPC* merchant = (NPC*)app->entities->CreateEntity(NPCType::MERCHANT, merchantPos.x, merchantPos.y);
	npcList.add(merchant);
	merchant->activeOnStage = StageIndex::SHOP;

	NPC* emilio = (NPC*)app->entities->CreateEntity(NPCType::EMILIO, emilioPos.x, emilioPos.y);
	npcList.add(emilio);
	emilio->activeOnStage = StageIndex::TOWN;

	NPC* fuente = (NPC*)app->entities->CreateEntity(NPCType::FUENTE, fuentePos.x, fuentePos.y);
	npcList.add(fuente);
	fuente->activeOnStage = StageIndex::TOWN;

	NPC* cartelSudTown = (NPC*)app->entities->CreateEntity(NPCType::CARTELSUDTOWN, cartelSudTownPos.x, cartelSudTownPos.y);
	npcList.add(cartelSudTown);
	cartelSudTown->activeOnStage = StageIndex::TOWN;

	// ============================

	app->stages->npcListPtr = &npcList;

	// Normal Enemies
	iPoint eyePos = { 660, 100 }; // 680 100
	iPoint batPos = { 600, 100 };
	iPoint skeletonPos = { 750, 50 };

	NormalEnemy* eye = (NormalEnemy*)app->entities->CreateEntity(NormalEnemyType::FLYING_EYE, eyePos.x, eyePos.y);
	normalEnemyList.add(eye);
	eye->activeOnStage = StageIndex::DOJO;

	NormalEnemy* bat = (NormalEnemy*)app->entities->CreateEntity(NormalEnemyType::BAT, batPos.x, batPos.y);
	normalEnemyList.add(bat);
	bat->activeOnStage = StageIndex::DOJO;

	NormalEnemy* skeleton = (NormalEnemy*)app->entities->CreateEntity(NormalEnemyType::SKELETON, skeletonPos.x, skeletonPos.y);
	normalEnemyList.add(skeleton);
	skeleton->activeOnStage = StageIndex::DOJO;

	app->stages->normalEnemyListPtr = &normalEnemyList;


	// TOWN LIMITS for camera
	app->camera->SetLimits(640, 350, 4490, 4200);

	pause = false;
	playing = true;
	godmode = false;

	app->guiManager->Enable();
	if (playloading == true) {
		playloading = false;
		app->LoadGameRequest();
	}
	restart->state = GuiControlState::DISABLED;
	backtoMenu->state = GuiControlState::DISABLED;

	// UI

	characterBG = app->tex->Load("Assets/gui/inventory/ui_inventory_char.png");

	return true;
}

bool Scene::PreUpdate()
{
	bool ret = true;

	if (app->pauseM->exitg) {
		if (pause == false) {
			pause = true;
			app->audio->PlayFx(backFx);
		}
		app->pauseM->exitg = false;
		
		
		app->fade->DoFadeToBlack(this, (Module*)app->titleScene);
		app->pauseM->CleanUp();
	}
	
	// Hide UI
	guiactivate = false;

	if (app->inventory->isEnabled() == false) {
		if (app->input->GetKey(SDL_SCANCODE_I) == KEY_DOWN) {
			app->inventory->Enable();
		}
	}

	if (app->input->GetKey(SDL_SCANCODE_E) == KEY_DOWN) {
		app->stmen->Enable();
	}

	return ret;
}

bool Scene::Update(float dt)
{

	int xt, yt;
	//variables for textures
	xt = -app->camera->GetPos().x / 2 + app->win->GetWidth() / 2;
	yt = -app->camera->GetPos().y / 2 + app->win->GetHeight() / 2;
	

	fpsdt = dt*3.75;
	//GUI activation

	if (app->input->GetKey(SDL_SCANCODE_F10) == KEY_DOWN)
	{
		if (godmode)
		{
			godmode = false;
		
			for (int i = 0; i < partyList.count(); i++)
			{
				partyList.At(i)->data->stats->LoadStats();
			}

		}
		else
		{			
			for (int i = 0; i < partyList.count(); i++)
			{
				partyList.At(i)->data->stats->SaveStats();
				partyList.At(i)->data->stats->SetStats(9999, 9999, 9999, partyList.At(i)->data->stats->mana);
			}
			
			godmode = true;
			
		}
	}

	if (app->input->GetKey(SDL_SCANCODE_G) == KEY_REPEAT)
	{
		guiactivate = true;
	}

	//LOG("INT VALUES: %d", app->map->intValues.count());

	if (pause == false) {
		// ================================
		//       SAVE / LOAD requests
		// ================================

		if (app->input->GetKey(SDL_SCANCODE_0) == KEY_DOWN) {
			app->audio->PlayFx(loadFx);
			app->LoadGameRequest();
		}

		if (app->input->GetKey(SDL_SCANCODE_9) == KEY_DOWN) {
			app->audio->PlayFx(saveFx);
			app->SaveGameRequest();
		}
	}

	// ================================
	//			DEBUG KEYS 
	// ================================

	// Change map
	if (app->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN) {
		app->fade->DoFadeToBlack(StageIndex::TOWN);
	}

	if (app->input->GetKey(SDL_SCANCODE_F2) == KEY_DOWN) {
		app->fade->DoFadeToBlack(StageIndex::DOJO);
	}

	if (app->input->GetKey(SDL_SCANCODE_F3) == KEY_DOWN) {
		app->fade->DoFadeToBlack(StageIndex::SHOP);
	}

	if (app->input->GetKey(SDL_SCANCODE_F4) == KEY_DOWN) {
		app->fade->DoFadeToBlack(StageIndex::SHOPSUB);
	}

	if (app->input->GetKey(SDL_SCANCODE_F5) == KEY_DOWN) {
		app->fade->DoFadeToBlack(StageIndex::TAVERN);
	}
	if (app->input->GetKey(SDL_SCANCODE_F6) == KEY_DOWN) {
		app->fade->DoFadeToBlack(StageIndex::WIN);
	}
	if (app->input->GetKey(SDL_SCANCODE_F7) == KEY_DOWN) {
		app->fade->DoFadeToBlack(StageIndex::LOSE);
	}
	if (app->input->GetKey(SDL_SCANCODE_F8) == KEY_DOWN) {
		app->fade->DoFadeToBlack(StageIndex::TOWER_0);
	}
	if (app->input->GetKey(SDL_SCANCODE_K) == KEY_DOWN) {
		app->fade->DoFadeToBlack(StageIndex::TOWER_1);
	}
	if (app->input->GetKey(SDL_SCANCODE_L) == KEY_DOWN) {
		app->fade->DoFadeToBlack(StageIndex::TOWER_2);
	}
	if (app->input->GetKey(SDL_SCANCODE_F11) == KEY_DOWN) {
		app->fade->DoFadeToBlack(StageIndex::TOWER_4);
	}
	if (app->input->GetKey(SDL_SCANCODE_M) == KEY_DOWN) {
		app->fade->DoFadeToBlack(StageIndex::TOWER_3);
	}

	// Player movement
	if (app->input->GetKey(SDL_SCANCODE_6) == KEY_DOWN) {
		player->canMove ? player->canMove = false : player->canMove = true;
	}

	// Add ally to the party
	if (app->input->GetKey(SDL_SCANCODE_7) == KEY_DOWN) {

		if (partyList.At(1) == nullptr) {
			int x = 80;
			int y = 130 - 50;
			partyList.add((Party*)app->entities->CreateEntity(PartyType::VALION, x, y));
		}else{
			partyList.del(partyList.At(1));
		}
		//partyList.At(1) == nullptr ? partyList.add((Party*)app->entities->CreateEntity(PartyType::VALION, 20, 50)) : partyList.del(partyList.At(1));
	}
	if (app->input->GetKey(SDL_SCANCODE_8) == KEY_DOWN) {

		if (partyList.At(2) == nullptr) {
			int x = -200;
			int y = 120 - 50;
			partyList.add((Party*)app->entities->CreateEntity(PartyType::RAYLA, x, y));
		}
		else {
			partyList.del(partyList.At(2));
		}
		//partyList.At(1) == nullptr ? partyList.add((Party*)app->entities->CreateEntity(PartyType::VALION, 20, 50)) : partyList.del(partyList.At(1));
	}
	if (app->input->GetKey(SDL_SCANCODE_9) == KEY_DOWN) {

		if (partyList.At(3) == nullptr) {
			int x = 200;
			int y = 0 - 50;
			partyList.add((Party*)app->entities->CreateEntity(PartyType::DHION, x, y));
		}
		else {
			partyList.del(partyList.At(3));
		}
		//partyList.At(1) == nullptr ? partyList.add((Party*)app->entities->CreateEntity(PartyType::VALION, 20, 50)) : partyList.del(partyList.At(1));
	}
	if (app->stages->actualStage == StageIndex::WIN) {
		restart->state = GuiControlState::DISABLED;
		backtoMenu->state = GuiControlState::NORMAL;
	}
	if (app->stages->actualStage == StageIndex::LOSE) {
		backtoMenu->state = GuiControlState::DISABLED;
		restart->state = GuiControlState::NORMAL;
	}

	return true;
}

// Render bullshit
bool Scene::PostUpdate()
{
	bool ret = true;
	int w = 45, h = 5, wpm=25;


	std::string fps = std::to_string(fpsdt);
	char const* fpsChar = fps.c_str();
	
	// Variables
	int x = -app->camera->GetPos().x / 2,
		y = -app->camera->GetPos().y / 2;

	if (guiactivate == true && app->stages->actualStage != StageIndex::WIN && app->stages->actualStage != StageIndex::LOSE)
	{
		// Checkear miembros de la party y imprimir sus carteles

		if (app->battle->isEnabled() == false) {
			ShowGUI();
		}
	}
	if (app->collisions->debug)
	{
		app->font->DrawText(fpsChar, x + 10, y + 100);
		
		app->render->Vsync == true?	app->font->DrawText("Vsync: On", x + 10, y + 120): app->font->DrawText("Vsync: Off", x + 10, y + 120);
		
	}
	if (app->stages->actualStage == StageIndex::WIN) {
		backtoMenu->state != GuiControlState::PRESSED ? app->render->DrawTexture(backtoMenuTex, 240, 280) : app->render->DrawTexture(press_backtoMenuTex, 240, 280);
	}
	if (app->stages->actualStage == StageIndex::LOSE) {
		restart->state != GuiControlState::PRESSED ? app->render->DrawTexture(restartTex, 280, 280) : app->render->DrawTexture(press_restartTex, 280, 280);

	}
	return ret;
}

bool Scene::OnGuiMouseClickEvent(GuiControl* control)
{
	switch (control->type)
	{
	case GuiControlType::BUTTON:
	{
		//Checks the GUI element ID
		if (control->id == 1)
		{
			LOG("Click on button 1");
		}

		if (control->id == 2)
		{
			LOG("Click on button 2");
		}

		if (app->stages->actualStage == StageIndex::LOSE) {
	
			if (control->id == 40)
			{
				LOG("Click on Restart");
			
				restart->state = GuiControlState::DISABLED;
				backtoMenu->state = GuiControlState::DISABLED;

				app->camera->SetTarget(player);
				app->LoadGameRequest();
				app->scene->player->canMove = true;
				

			}
		}
		if (app->stages->actualStage == StageIndex::WIN) {
			if (control->id == 41)
			{
				LOG("Click on Back to Menu");

				restart->state = GuiControlState::DISABLED;
				backtoMenu->state = GuiControlState::DISABLED;

				app->fade->DoFadeToBlack(this, (Module*)app->titleScene);


			}
		}
	}
	//Other cases here

	default: break;
	}

	return true;
}

// Called before quitting
bool Scene::CleanUp()
{
	LOG("Freeing scene");

	app->font->CleanFonts();

	app->camera->ReleaseTarget();

	app->tex->UnLoad(restartTex);
	app->tex->UnLoad(backtoMenuTex);
	app->tex->UnLoad(press_restartTex);
	app->tex->UnLoad(press_backtoMenuTex);
	app->tex->UnLoad(characterBG);
	app->tex->UnLoad(locationUI);

	//Stages:
	app->entities->DestroyEntity(player);

	restart->state = GuiControlState::DISABLED;
	backtoMenu->state = GuiControlState::DISABLED;

	app->stages->ChangeStage(StageIndex::NONE);

	
	ListItem<Item*>* itemInList;
	for (itemInList = itemList.start; itemInList != NULL; itemInList = itemInList->next)
	{
		itemInList->data->CleanUp();
	}

	ListItem<NPC*>* npcInList;
	for (npcInList = npcList.start; npcInList != NULL; npcInList = npcInList->next)
	{
		npcInList->data->CleanUp();
	}

	ListItem<NormalEnemy*>* normalEnemyInList;
	for (normalEnemyInList = normalEnemyList.start; normalEnemyInList != NULL; normalEnemyInList = normalEnemyInList->next)
	{
		normalEnemyInList->data->CleanUp();
	}

	ListItem<Character*>* characterInList;
	for (characterInList = partyList.start; characterInList != NULL; characterInList = characterInList->next)
	{
		characterInList->data->CleanUp();
	}

	itemList.clear();
	npcList.clear();
	normalEnemyList.clear();
	partyList.clear();

	player = nullptr;
	delete player;

	app->dialogs->Disable();

	app->map->Disable();

	return true;
}

void Scene::ShowGUI() 
{
	int x = -app->camera->GetPos().x / 2,
		y = -app->camera->GetPos().y / 2,
		charX = x + 110,
		charY = y + 5;

	ListItem<Character*>* ch = partyList.start;

	for (ch; ch != NULL; ch = ch->next)
	{
		app->render->DrawTexture(characterBG, charX, charY);

		app->render->DrawTexture(ch->data->spriteFace, charX + 15, charY + 20);

		app->font->DrawText(ch->data->name, charX + 25, charY - 2);
		charX += 130;
	}

	CharBars();

	// Current Stage on UI
	if (showLocation == true) {
		app->render->DrawTexture(locationUI, x + 10, y + 25);

		switch (app->stages->actualStage) {
		case StageIndex::NONE:
			break;
		case StageIndex::TOWN:
			sprintf_s(currentPlace_UI, "Town");

			app->font->DrawText(currentPlace_UI, x + 25, y + 30, { 0, 0, 0 });
			break;
		case StageIndex::DOJO:
			sprintf_s(currentPlace_UI, "Dojo");

			app->font->DrawText(currentPlace_UI, x + 30, y + 30, { 0, 0, 0 });
			break;
		case StageIndex::SHOP:
			sprintf_s(currentPlace_UI, "Shop");

			app->font->DrawText(currentPlace_UI, x + 30, y + 30, { 0, 0, 0 });
			break;
		case StageIndex::SHOPSUB:
			sprintf_s(currentPlace_UI, "Shop -1");

			app->font->DrawText(currentPlace_UI, x + 25, y + 30, { 0, 0, 0 });
			break;
		case StageIndex::TAVERN:
			sprintf_s(currentPlace_UI, "Tavern");

			app->font->DrawText(currentPlace_UI, x + 20, y + 30, { 0, 0, 0 });
			break;
		case StageIndex::TOWER_0:
			sprintf_s(currentPlace_UI, "Tower");

			app->font->DrawText(currentPlace_UI, x + 20, y + 30, { 0, 0, 0 });
			break;
		case StageIndex::TOWER_1:
			sprintf_s(currentPlace_UI, "Floor 1");

			app->font->DrawText(currentPlace_UI, x + 20, y + 30, { 0, 0, 0 });
			break;
		case StageIndex::TOWER_2:
			sprintf_s(currentPlace_UI, "Floor 2");

			app->font->DrawText(currentPlace_UI, x + 20, y + 30, { 0, 0, 0 });
			break;
		case StageIndex::TOWER_4:
			sprintf_s(currentPlace_UI, "Floor 4");

			app->font->DrawText(currentPlace_UI, x + 20, y + 30, { 0, 0, 0 });
			break;
		case StageIndex::TOWER_3:
			sprintf_s(currentPlace_UI, "Floor 3");

			app->font->DrawText(currentPlace_UI, x + 20, y + 30, { 0, 0, 0 });
			break;
		}
	}
}
void Scene::CharBars()
{
	// Variables
	int w = 35, h = 6, wpm = 25;
	int x = -app->camera->GetPos().x / 2,
		y = -app->camera->GetPos().y / 2,
		barsX = x + 173,
		barsY = y + 28;
	
	if (guiactivate == true && app->stages->actualStage != StageIndex::WIN && app->stages->actualStage != StageIndex::LOSE)
	{
		// Party List
		ListItem<Character*>* ch = partyList.start;

		// Debug Keys:
		if (app->input->GetKey(SDL_SCANCODE_H) == KEY_DOWN) {
			for (ch; ch != NULL; ch = ch->next) {
				ch->data->stats->health += 1;
			}
		}
		ch = partyList.start;
		if (app->input->GetKey(SDL_SCANCODE_J) == KEY_DOWN) {
			for (ch; ch != NULL; ch = ch->next) {
				ch->data->stats->health -= 1;
			}
		}
		ch = partyList.start;

		// Barras Stats Party
		for (ch; ch != NULL; ch = ch->next) {
			// HP bars
			if (ch->data->stats != nullptr && ch->data->stats->health != NULL && ch->data->stats->maxHealth != NULL && ch->data->stats->mana != NULL && ch->data->stats->maxMana != NULL) {
				hpc = ((float)ch->data->stats->health / (float)ch->data->stats->maxHealth) * w;
				SDL_Rect HPrect = { barsX + 7, barsY, hpc, h };

				app->render->DrawRectangle({ barsX + 7, barsY, w, h }, 0, 0, 0);
				app->render->DrawRectangle(HPrect, 0, 255, 0);

				// PM bars
				pmc = ((float)ch->data->stats->mana / (float)ch->data->stats->maxMana) * wpm;
				SDL_Rect  PMrect = { barsX + 7, barsY + h + 1, pmc, h };
				app->render->DrawRectangle({ barsX + 7, barsY + h + 1, wpm, h }, 0, 0, 0);
				app->render->DrawRectangle(PMrect, 0, 78, 255);

				// Life text
				sprintf_s(lifeTextUI, 50, "hp:%2d", ch->data->stats->health);
				app->font->DrawText(lifeTextUI, barsX, barsY + h + 9, { 0,255,30 });
				barsX += 130;
			}
		}
	}
}

bool Scene::AddItem(UsableType type) {
	if (itemList.count() < app->inventory->inventorySlots) {
		Usable* item = (Usable*)app->entities->CreateEntity(type);
		itemList.add(item);

		return true;
	}
	else {
		LOG("Inventory is full");
		return false;
	}
}