#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "Title.h"
#include "FadeToBlack.h"

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
	
	return true;
}

// Called each loop iteration
bool TitleScene::PreUpdate()
{
	bool ret = true;

	app->fade->StartFadeToBlack(this, (Module*)app->scene, 0);

	return ret;
}

// Called each loop iteration
bool TitleScene::Update(float dt)
{
	LOG("TITLE SCENE VACÍA UWU");
	return true;
}

// Called each loop iteration
bool TitleScene::PostUpdate()
{
	bool ret = true;

	return ret;
}

// Called before quitting
bool TitleScene::CleanUp()
{
	LOG("Freeing Title scene");

	return true;
}
