#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "Title.h"
#include "FadeToBlack.h"
#include "ModuleQFonts.h"
#include "Stages.h"
#include "Scene.h"
#include "Camera.h"

#include "Defs.h"
#include "Log.h"

TitleScene::TitleScene(App* application, bool start_enabled) : Module(application, start_enabled)
{
	name.Create("titleScene");
}

// Destructor
TitleScene::~TitleScene()
{}

// Called before render is available
bool TitleScene::Awake()
{
	LOG("Loading Title");
	bool ret = true;

	return ret;
}

// Called before the first frame
bool TitleScene::Start()
{
	// Load Assets

	buttonsUI = app->tex->Load("Assets/gui/buttons_2x.png");
	title = app->tex->Load("Assets/textures/title.png");

	app->audio->PlayMusic("Assets/audio/music/music_title.ogg");

	confirmFx = app->audio->LoadFx("Assets/audio/sfx/fx_select_confirm.wav");

	app->camera->SetPos({ 0,0 });

	pause = false;

	return true;
}

// Called each loop iteration
bool TitleScene::PreUpdate()
{
	bool ret = true;

	if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN) {
		if (pause == false) {
			pause = true;
			app->audio->PlayFx(confirmFx);
		}
		app->stages->ChangeStage(StageIndex::TOWN);

		app->fade->DoFadeToBlack(this, (Module*)app->scene);
	}

	if (app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN) {
		ret = false;
	}
	return ret;
}

// Called each loop iteration
bool TitleScene::Update(float dt)
{

	return true;
}

// Called each loop iteration
bool TitleScene::PostUpdate()
{
	bool ret = true;

	// Render
	app->render->DrawTexture(title, 100, 20);
	app->render->DrawTexture(buttonsUI, 0, 0);

	// Render Text
	app->font->DrawTextDelayed("Press SPACE to start", 225, 300);

	return ret;
}

// Called before quitting
bool TitleScene::CleanUp()
{
	LOG("Freeing Title scene");

	app->font->CleanFonts();

	return true;
}