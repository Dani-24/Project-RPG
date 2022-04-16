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

#include "Battle.h"
#include "Stages.h"
#include "ModuleQFonts.h"
#include "Camera.h"

#include "NormalEnemy.h"
#include "NPC.h"
#include "EntityManager.h"


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

	// Load music
	app->audio->PlayMusic("Assets/audio/music/music_town.ogg");

	backFx = app->audio->LoadFx("Assets/audio/sfx/fx_select_back.wav");
	loadFx = app->audio->LoadFx("Assets/audio/sfx/fx_load.wav");
	saveFx = app->audio->LoadFx("Assets/audio/sfx/fx_save.wav");

	// Player Entity
	player = (Player*)app->entities->CreateEntity(CharacterType::PLAYER, 950, 1000);

	app->stages->playerPtr = player;
	app->camera->SetTarget(player);

	// NPCs
	iPoint cockPos = { 1240, 950 };
	iPoint barkeeperPos = { 450, 300 };
	iPoint trainerPos = { 290, 160 };
	iPoint merchantPos = { 255, 150 };

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

	app->stages->npcListPtr = &npcList;

	//// Normal Enemies
	//iPoint eyePos = {};
	//iPoint batPos = {};

	//NormalEnemy* eye = (NormalEnemy*)app->entities->CreateEntity(NPCType::COCK, cockPos.x, cockPos.y);
	//eye->activeOnStage = StageIndex::TOWN;


	

	// TOWN LIMITS for camera
	app->camera->SetLimits(640, 350, 4490, 4200);

	pause = false;

	return true;
}

bool Scene::PreUpdate()
{
	bool ret = true;

	if (app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN) {
		if (pause == false) {
			pause = true;
			app->audio->PlayFx(backFx);
		}
		app->fade->DoFadeToBlack(this, (Module*)app->titleScene);
	}

	return ret;
}

bool Scene::Update(float dt)
{
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
		app->stages->ChangeStage(StageIndex::TOWN);
	}

	if (app->input->GetKey(SDL_SCANCODE_F2) == KEY_DOWN) {
		app->stages->ChangeStage(StageIndex::DOJO);
	}

	if (app->input->GetKey(SDL_SCANCODE_F3) == KEY_DOWN) {
		app->stages->ChangeStage(StageIndex::SHOP);
	}

	if (app->input->GetKey(SDL_SCANCODE_F4) == KEY_DOWN) {
		app->stages->ChangeStage(StageIndex::SHOPSUB);
	}

	if (app->input->GetKey(SDL_SCANCODE_F5) == KEY_DOWN) {
		app->stages->ChangeStage(StageIndex::TAVERN);
	}

	// Player movement
	if (app->input->GetKey(SDL_SCANCODE_7) == KEY_DOWN) {
		player->canMove ? player->canMove = false : player->canMove = true;
	}

	// Show/Hide Colliders
	if (app->input->GetKey(SDL_SCANCODE_8) == KEY_DOWN) {

		//if (app->battle->isEnabled() == false) {
			
		//	app->battle->Enable();
			

		//}else
		//{
		//	app->battle->Disable();
			
			
		//}

		app->battle->isEnabled() == false ? app->battle->Enable(): app->battle->Disable();
	}
	return true;
}

// Render bullshit
bool Scene::PostUpdate()
{
	bool ret = true;

	app->font->DrawTextDelayed("SOS Putasooo    como la abuela", 950, 950);

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

	//Stages:
	app->entities->DestroyEntity(player);

	ListItem<NPC*>* npcInList;

	app->stages->ChangeStage(StageIndex::NONE);

	for (npcInList = npcList.start; npcInList != NULL; npcInList = npcInList->next)
	{
		npcInList->data->CleanUp();
	}

	if (btn1 != nullptr) {
		btn1->state = GuiControlState::DISABLED;
		btn1 = nullptr;
	}
	delete btn1;

	if (btn2 != nullptr) {
		btn2->state = GuiControlState::DISABLED;
		btn2 = nullptr;
	}
	delete btn2;

	npcList.clear();
	player = nullptr;
	delete player;

	app->map->Disable();


	return true;
}
