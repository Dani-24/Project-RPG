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
#include "ModulePlayer.h"
#include "EnemyMovement.h"

#include "Defs.h"
#include "Log.h"

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
	app->player->Enable();

	app->enemyMovement->Enable();

	app->map->Load("initial_town_map.tmx");
	
	// Load music
	app->audio->PlayMusic("Assets/audio/music/music_credits.ogg");

	backFx = app->audio->LoadFx("Assets/audio/sfx/fx_select_back.wav");

	loadFx = app->audio->LoadFx("Assets/audio/sfx/fx_load.wav");
	saveFx = app->audio->LoadFx("Assets/audio/sfx/fx_save.wav");

	btn1 = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 1, "Test1", { (app->win->GetWidth() / 2) - 300, app->win->GetWidth() / 10, 160, 40 }, this);
	btn2 = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 2, "Test2", { (app->win->GetWidth() / 2) + 300, app->win->GetWidth() / 10, 160, 40 }, this);

	// Texture
	img = app->tex->Load("Assets/textures/sample.png");

	for (int j = 0; j < 2; j++) {
		for (int i = 0; i < 27; i++) {
			imgAnim.PushBack({ i * 195,j * 200, 195, 200 });
		}
	}
	imgAnim.speed = 0.02f;
	imgAnim.loop = true;

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
		app->fade->StartFadeToBlack(this, (Module*)app->titleScene);
	}

	return ret;
}

bool Scene::Update(float dt)
{
	if (pause == false) {
		// ================================
		//       SAVE / LOAD requests
		// ================================

		if (app->input->GetKey(SDL_SCANCODE_9) == KEY_DOWN) {
			app->audio->PlayFx(loadFx);
			app->LoadGameRequest();
		}

		if (app->input->GetKey(SDL_SCANCODE_0) == KEY_DOWN) {
			app->audio->PlayFx(saveFx);
			app->SaveGameRequest();
		}

		// Update Anim
		imgAnim.Update(dt);
	}
	return true;
}

// Render bullshit
bool Scene::PostUpdate()
{
	bool ret = true;

	app->map->Draw();
	app->guiManager->Draw();

	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			app->render->DrawTexture(img, i * 200, j * 200, &imgAnim.GetCurrentFrame());
		}
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

	app->tex->UnLoad(img);

	imgAnim.DeleteAnim();

	app->player->Disable();

	app->enemyMovement->Disable();

	return true;
}
