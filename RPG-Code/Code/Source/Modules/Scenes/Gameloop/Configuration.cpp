#include "Configuration.h"

#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "Logo.h"
#include "FadeToBlack.h"
#include "Camera.h"
#include "ModuleQFonts.h"
#include "GuiManager.h"

#include "Defs.h"
#include "Log.h"

Configuration::Configuration(App* application, bool start_enabled) : Module(application, start_enabled)
{
	name.Create("conf");
}

Configuration::~Configuration()
{}

bool Configuration::Awake()
{
	LOG("Loading Scene");
	bool ret = true;

	return ret;
}

bool Configuration::Start()
{
	
	// Load music
	app->audio->PlayMusic("Assets/audio/music/music_town.ogg");

	backFx = app->audio->LoadFx("Assets/audio/sfx/fx_select_back.wav");

	// GUI
	musp = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 6, "mus+", { (app->win->GetWidth() / 2) - 580, (app->win->GetWidth() / 50) + 230, 74, 32 }, this);
	/*musm = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 2, "mus-", {}, this);
	FXp = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 3, "FX+", {}, this);
	FXm = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 4, "FX+", {}, this);
	fullS = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 5, "fulls", {}, this);
	Vsync = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 6, "vsync", {}, this);
	frcap30 = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 7, "30fps", {}, this);
	frcap60 = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 8, "60fps", {}, this);*/


	app->camera->SetPos({ 0,0 });
	

	pause = false;

	return true;
}

bool Configuration::PreUpdate()
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

bool Configuration::Update(float dt)
{
	if (pause == false) {
		
	}

	
	return true;
}

// Render bullshit
bool Configuration::PostUpdate()
{
	bool ret = true;

	app->font->DrawText("owowow", 200, 200);

	return ret;
}


bool Configuration::OnGuiMouseClickEvent(GuiControl* control)
{
	switch (control->type)
	{
	case GuiControlType::BUTTON:
	{
		//Checks the GUI element ID
		if (control->id == 6)
		{
			LOG("volume +");
		}

		if (control->id == 7)
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
bool Configuration::CleanUp()
{
	LOG("Freeing scene");

	app->font->CleanFonts();

	//Stages:
	

	//app->stages->ChangeStage(StageIndex::NONE);

	return true;
}