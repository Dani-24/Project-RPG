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
#include "EnemyMovement.h"
#include "EntityManager.h"
#include "Battle.h"
#include "Stages.h"
#include "ModuleQFonts.h"
#include "Camera.h"
#include "Cock.h"

#include "Defs.h"
#include "Log.h"

#include <time.h>

Scene::Scene(App* application, bool start_enabled) : Module(application, start_enabled)
{
	name.Create("scene");
}

Scene::~Scene()
{}

bool Scene::Awake()
{
	LOG("Loading Scene");
	bool ret = true;

	return ret;
}

bool Scene::Start()
{
	// Enables & idk
	app->map->Enable();
	app->enemyMovement->Enable();

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

	srand(time(NULL));
	int randX = 1000;
	int randY = 1000;
	int x = 1300;
	int y = 950;

	int xT = 1500;
	int yT = 1100;

	int xB = 1050;
	int yB = 900;

	int xM = 1100;
	int yM = 900;

	//Cock Entity
	NPC* cock = (NPC*)app->entities->CreateEntity(NPCType::COCK, x, y);
	npcList.add(cock);
	cock->activeOnStage = StageIndex::TOWN;

	NPC* barkeeper = (NPC*)app->entities->CreateEntity(NPCType::BARKEEPER, xB, yB);
	npcList.add(barkeeper);
	barkeeper->activeOnStage = StageIndex::TOWN;

	NPC* trainer = (NPC*)app->entities->CreateEntity(NPCType::TRAINER, xT, yT);
	npcList.add(trainer);
	trainer->activeOnStage = StageIndex::TOWN;

	NPC* merchant = (NPC*)app->entities->CreateEntity(NPCType::MERCHANT, xM, yM);
	npcList.add(merchant);
	merchant->activeOnStage = StageIndex::TOWN;

	//cock->position = { 950, 950 };
	//app->stages->npcListPtr.At(npcList.count())->data = (Cock*)npcList.At(npcList.count());

	app->stages->npcListPtr = &npcList;

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

		if (app->battle->isEnabled() == false) {
			
			//app->battle->Enable();
			//app->stages->onBattle = true;

		}else
		{
			//app->battle->Disable(), 
			//app->stages->onBattle = false;		
		}

		if (aaa == false) {

			app->map->RemoveCol();
			aaa = true;

		}
		else
		{
			app->map->LoadCol();
			aaa  = false;
		}
	

		//app->battle->isEnabled() == false ? app->battle->Enable() , app->stages->onBattle = true: app->battle->Disable(), app->stages->onBattle = false;
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
	
	app->stages->ChangeStage(StageIndex::NONE);
	
	npcList.clear();

	app->map->Disable();

	app->enemyMovement->Disable();

	return true;
}
