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

#include "Battle.h"
#include "Stages.h"
#include "ModuleQFonts.h"
#include "Camera.h"

#include "NormalEnemy.h"
#include "NPC.h"
#include "EntityManager.h"

#include "Party.h"


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
	// Enables & idk
	app->map->Enable();
	app->dialogs->Enable();

	switch (app->stages->actualStage) {
	case StageIndex::NONE:
		break;
	case StageIndex::TOWN:
		app->map->Load("initial_town_map.tmx");
		break;
	case StageIndex::DOJO:
		app->map->Load("initial_town_dojo.tmx");
		break;
	case StageIndex::SHOP:
		app->map->Load("initial_town_shop.tmx");
		break;
	case StageIndex::SHOPSUB:
		app->map->Load("initial_town_under_shop.tmx");
		break;
	case StageIndex::TAVERN:
		app->map->Load("initial_town_tavern.tmx");
		break;
	}

	// Load textures
	gui = app->tex->Load("Assets/gui/GUIFinal.png");

	// Load music
	app->audio->PlayMusic("Assets/audio/music/music_town.ogg");

	backFx = app->audio->LoadFx("Assets/audio/sfx/fx_select_back.wav");
	loadFx = app->audio->LoadFx("Assets/audio/sfx/fx_load.wav");
	saveFx = app->audio->LoadFx("Assets/audio/sfx/fx_save.wav");

	// Player Entity
	player = (Player*)app->entities->CreateEntity(CharacterType::PLAYER, 950, 1730);

	app->stages->playerPtr = player;
	app->camera->SetTarget(player);
	partyList.add(player);

	//Party members
	Party* valion = (Party*)app->entities->CreateEntity(PartyType::VALION, 10, 50);
	partyList.add(valion);
	
	valionchar = valion;

	app->stages->partyListPtr = &partyList;

	// NPCs
	iPoint cockPos = { 900, 1400 };
	iPoint barkeeperPos = { 450, 300 };
	iPoint trainerPos = { 290, 160 };
	iPoint merchantPos = { 255, 150 };
	iPoint emilioPos = { 850, 200 };

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

	app->stages->npcListPtr = &npcList;

	// Normal Enemies
	iPoint eyePos = { 1000, 500 };
	iPoint batPos = { 800, 950 };
	iPoint skeletonPos = { 650, 850 };

	NormalEnemy* eye = (NormalEnemy*)app->entities->CreateEntity(NormalEnemyType::FLYING_EYE, eyePos.x, eyePos.y);
	normalEnemyList.add(eye);
	eye->activeOnStage = StageIndex::TOWN;

	NormalEnemy* bat = (NormalEnemy*)app->entities->CreateEntity(NormalEnemyType::BAT, batPos.x, batPos.y);
	normalEnemyList.add(bat);
	bat->activeOnStage = StageIndex::TOWN;

	NormalEnemy* skeleton = (NormalEnemy*)app->entities->CreateEntity(NormalEnemyType::SKELETON, skeletonPos.x, skeletonPos.y);
	normalEnemyList.add(skeleton);
	skeleton->activeOnStage = StageIndex::TOWN;

	app->stages->normalEnemyListPtr = &normalEnemyList;


	// TOWN LIMITS for camera
	app->camera->SetLimits(640, 350, 4490, 4200);

	pause = false;
	playing = true;
	godmode = false;

	app->guiManager->Enable();

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
		app->pauseM->resumen = true;
		app->fade->DoFadeToBlack(this, (Module*)app->titleScene);
		app->pauseM->CleanUp();
	}
	

	return ret;
}

bool Scene::Update(float dt)
{

	

	int xt, yt;
	//variables for textures
	xt = -app->camera->GetPos().x / 2 + app->win->GetWidth() / 2;
	yt = -app->camera->GetPos().y / 2 + app->win->GetHeight() / 2;

	//GUI activation

	guiactivate = false;

	if (app->input->GetKey(SDL_SCANCODE_F10) == KEY_DOWN)
	{
		if (godmode)
		{
			godmode = false;
			valionchar->stats->LoadStats();
			player->stats->LoadStats();
		}
		else
		{
			valionchar->stats->SaveStats();
			player->stats->SaveStats();
			valionchar->stats->SetStats(9999, 9999, 9999, 9999, 9999);
			player->stats->SetStats(9999, 9999, 9999, 9999, 9999);
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

	// Player movement
	if (app->input->GetKey(SDL_SCANCODE_7) == KEY_DOWN) {
		player->canMove ? player->canMove = false : player->canMove = true;
	}

	// Add ally to the party
	if (app->input->GetKey(SDL_SCANCODE_8) == KEY_DOWN) {
		partyList.At(1) == nullptr ? partyList.add((Party*)app->entities->CreateEntity(PartyType::VALION, 100, 150)) : partyList.del(partyList.At(1));
		//app->battle->isEnabled() == false ? app->battle->Enable(): app->battle->Disable();
	}
	return true;
}

// Render bullshit
bool Scene::PostUpdate()
{
	bool ret = true;

	int xt, yt;
	//variables for textures
	xt = -app->camera->GetPos().x / 2 + app->win->GetWidth() / 2;
	yt = -app->camera->GetPos().y / 2 + app->win->GetHeight() / 2;

	if (guiactivate == true)
	{
		app->render->DrawTexture(gui, xt - 606, yt - 360);
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

	app->tex->UnLoad(gui);

	//Stages:
	app->entities->DestroyEntity(player);

	

	app->stages->ChangeStage(StageIndex::NONE);

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

	if (btn1 != nullptr) {
		btn1->state = GuiControlState::DISABLED;
	}
	btn1 = nullptr;
	delete btn1;

	if (btn2 != nullptr) {
		btn2->state = GuiControlState::DISABLED;
	}
	btn2 = nullptr;
	delete btn2;

	npcList.clear();
	normalEnemyList.clear();

	player = nullptr;
	delete player;


	app->dialogs->Disable();

	app->map->Disable();


	return true;
}
