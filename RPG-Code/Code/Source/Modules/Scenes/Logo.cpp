#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "Logo.h"
#include "FadeToBlack.h"

#include "Defs.h"
#include "Log.h"

LogoScene::LogoScene(App* application, bool start_enabled) : Module(application, start_enabled)
{
	name.Create("scene");
}

// Destructor
LogoScene::~LogoScene()
{}

// Called before render is available
bool LogoScene::Awake()
{
	LOG("Loading Scene");
	bool ret = true;

	return ret;
}

// Called before the first frame
bool LogoScene::Start()
{
	logo = app->tex->Load("Assets/textures/logo.png");

	cont = 0;

	return true;
}

// Called each loop iteration
bool LogoScene::PreUpdate()
{
	bool ret = true;

	if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN) {
		app->fade->StartFadeToBlack(this, (Module*)app->scene);
	}

	return ret;
}

// Called each loop iteration
bool LogoScene::Update(float dt)
{

	if (cont < 1000) {
		cont += dt;
	}
	else {
		app->fade->StartFadeToBlack(this, (Module*)app->scene);
	}

	return true;
}

// Called each loop iteration
bool LogoScene::PostUpdate()
{
	bool ret = true;

	app->render->DrawTexture(logo, app->win->GetWidth()/2 -343, app->win->GetHeight()/2 - 343);

	return ret;
}

// Called before quitting
bool LogoScene::CleanUp()
{
	LOG("Freeing Logo scene");

	app->tex->UnLoad(logo);

	return true;
}
