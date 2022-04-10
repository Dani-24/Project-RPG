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

	// Load Map
	app->map->Load("initial_town_map.tmx");

	// Load music
	app->audio->PlayMusic("Assets/audio/music/music_town.ogg");

	backFx = app->audio->LoadFx("Assets/audio/sfx/fx_select_back.wav");
	loadFx = app->audio->LoadFx("Assets/audio/sfx/fx_load.wav");
	saveFx = app->audio->LoadFx("Assets/audio/sfx/fx_save.wav");

	// GUI
	/*btn1 = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 1, "Test1", { (app->win->GetWidth() / 2) - 300, app->win->GetWidth() / 10, 160, 40 }, this);
	btn2 = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 2, "Test2", { (app->win->GetWidth() / 2) + 300, app->win->GetWidth() / 10, 160, 40 }, this);*/

	// Player Entity
	player = (Player*)app->entities->CreateEntity(CharacterType::PLAYER, 950, 950);
	app->stages->playerPtr = player;
	app->camera->SetTarget(player);

	srand(time(NULL));
	int randX = (rand() % (1250 - 650)) + 650;
	int randY = (rand() % (1250 - 650)) + 650;
	// Cock Entity
	Cock* cock = (Cock*)app->entities->CreateEntity(NPCType::COCK, randX, randY);
	npcList.add(cock);
	cock->activeOnStage = StageIndex::TOWN;
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

	if (app->input->GetKey(SDL_SCANCODE_7) == KEY_DOWN) {
		player->canMove ? player->canMove = false : player->canMove = true;
	}

	if (app->input->GetKey(SDL_SCANCODE_8) == KEY_DOWN) {
		//app->fade->StartFadeToBlack(this, (Module*)app->battle);
	}
	return true;
}

// Render bullshit
bool Scene::PostUpdate()
{
	bool ret = true;

	app->font->DrawTextDelayed("Sos putasoo", 950, 950);

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

	//Stages:
	app->entities->DestroyEntity(player);
	
	app->stages->ChangeStage(StageIndex::NONE);
	
	npcList.clear();

	app->map->Disable();

	app->enemyMovement->Disable();

	return true;
}
