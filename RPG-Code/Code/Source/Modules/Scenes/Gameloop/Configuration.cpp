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
#include "PauseMenu.h"
#include "Scene.h"

#include "Defs.h"
#include "Log.h"

Configuration::Configuration(App* application, bool start_enabled) : Module(application, start_enabled)
{
	name.Create("conf");
}

Configuration::~Configuration()
{}

bool Configuration::Awake(pugi::xml_node& config)
{
	LOG("Loading Scene");
	bool ret = true;

	return ret;
}

bool Configuration::Start()
{
	
	// Load music
	//app->audio->PlayMusic("Assets/audio/music/music_settings.ogg");

	backFx = app->audio->LoadFx("Assets/audio/sfx/fx_select_back.wav");
	background = app->tex->Load("Assets/gui/marco_opciones.png");

	// Load sFx
	btnSelection= app->audio->LoadFx("Assets/audio/sfx/fx_select_next.wav");

	// GUI
	musp = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 6, "mus+", { (app->win->GetWidth() / 2) - 300, (app->win->GetWidth() / 50) + 50, 32, 32 }, this);
	musm = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 7, "mus-", { (app->win->GetWidth() / 2) - 350, (app->win->GetWidth() / 50) + 50, 32, 32 }, this);
	FXp = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 8, "FX+", { (app->win->GetWidth() / 2) - 300, (app->win->GetWidth() / 50) + 90, 32, 32 }, this);
	FXm = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 9, "FX-", { (app->win->GetWidth() / 2) - 350 , (app->win->GetWidth() / 50) + 90, 32, 32 }, this);
	fullS = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 10, "fulls", { (app->win->GetWidth() / 2) - 325, (app->win->GetWidth() / 50) + 130, 32, 32 }, this);
	Vsync = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 11, "vsync", { (app->win->GetWidth() / 2) - 325, (app->win->GetWidth() / 50) + 170, 32, 32 }, this);
	//frcap30 = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 12, "30fps", { (app->win->GetWidth() / 2) - 580, (app->win->GetWidth() / 50) + 230, 32, 32 }, this);
	//frcap60 = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 13, "60fps", { (app->win->GetWidth() / 2) - 580, (app->win->GetWidth() / 50) + 230, 32, 32 }, this);
	back = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 14, "back", { (app->win->GetWidth() / 2) - 180, (app->win->GetWidth() / 50) + 37, 32, 32 }, this);

	
	if(!app->scene->playing)app->camera->SetPos({ 0,0 });
	

	pause = false;
	
	return true;
}

bool Configuration::PreUpdate()
{
	bool ret = true;

	/*if (app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN) {
		if (pause == false) {
			pause = true;
			app->audio->PlayFx(backFx);
		}
		app->fade->DoFadeToBlack(this, (Module*)app->titleScene);
	}*/

	return ret;
}

bool Configuration::Update(float dt)
{
	if (pause == false) {
		
	}
	//app->render->DrawRectangle({ (app->win->GetWidth() / 2)-500 , (app->win->GetWidth() / 50)+30 , 350, 200 },125,0,125);
	
	return true;
}

// Render bullshit
bool Configuration::PostUpdate()
{
	bool ret = true;

	std::string sVOL = std::to_string(app->audio->vol);
	char const* volchar = sVOL.c_str();

	std::string sFX = std::to_string(app->audio->volFX);
	char const* FXchar = sFX.c_str();


	//if (app->pauseM->pauseGame == false && app->scene->playing==false )
	//{
	SDL_Color c = {0,0,0};
		app->render->DrawTexture(background, (app->win->GetWidth() / 2) - 475, (app->win->GetWidth() / 50) + 40);

		app->font->DrawText("Music", (app->win->GetWidth() / 2) - 470, (app->win->GetWidth() / 50) + 50,c);
		app->font->DrawText("+", (app->win->GetWidth() / 2) - 300, (app->win->GetWidth() / 50) + 50, c);
		app->font->DrawText("-", (app->win->GetWidth() / 2) - 350, (app->win->GetWidth() / 50) + 50, c);
		app->font->DrawText(volchar, (app->win->GetWidth() / 2) - 265, (app->win->GetWidth() / 50) + 50, c);
		app->font->DrawText("SFX", (app->win->GetWidth() / 2) - 470, (app->win->GetWidth() / 50) + 90, c);
		app->font->DrawText("+", (app->win->GetWidth() / 2) - 300, (app->win->GetWidth() / 50) + 90, c);
		app->font->DrawText("-", (app->win->GetWidth() / 2) - 350, (app->win->GetWidth() / 50) + 90, c);
		app->font->DrawText(FXchar, (app->win->GetWidth() / 2) - 265, (app->win->GetWidth() / 50) + 90, c);

		app->font->DrawText("FullScreen", (app->win->GetWidth() / 2) - 470, (app->win->GetWidth() / 50) + 130, c);
		if (app->win->fullscreen == true) app->font->DrawText("X", (app->win->GetWidth() / 2) - 325, (app->win->GetWidth() / 50) + 130, c);

		app->font->DrawText("VSync", (app->win->GetWidth() / 2) - 470, (app->win->GetWidth() / 50) + 170, c);
		if (app->render->Vsync == true) app->font->DrawText("X", (app->win->GetWidth() / 2) - 325, (app->win->GetWidth() / 50) + 170, c);


		app->font->DrawText("X", (app->win->GetWidth() / 2) - 180, (app->win->GetWidth() / 50) + 37, c);

	//}
	//else if (app->pauseM->pauseGame == true && app->scene->playing == true)
	//{

	//	int xt, yt, xc, yc;

	//	//variables for textures
	//	xt = -app->camera->GetPos().x / 2 + app->win->GetWidth() / 2;
	//	yt = -app->camera->GetPos().y / 2 + app->win->GetHeight() / 2;

	//	//variables for text
	//	xc = -app->camera->GetPos().x / app->win->GetScale() + app->win->GetWidth() / 2;
	//	yc = -app->camera->GetPos().y / app->win->GetScale() + app->win->GetHeight() / 2;

	//	app->render->DrawTexture(background, xc - 475, yc + 40);

	//	app->font->DrawText("Music", xc - 470, yc + 50);
	//	app->font->DrawText("+", xc - 300, yc + 50);
	//	app->font->DrawText("-", xc - 350, yc + 50);
	//	app->font->DrawText(volchar, xc - 265, yc + 50);
	//	app->font->DrawText("SFX", xc - 470, yc + 90);
	//	app->font->DrawText("+", xc - 300, yc + 90);
	//	app->font->DrawText("-", xc - 350, yc + 90);
	//	app->font->DrawText(FXchar, xc - 265, yc + 90);

	//	app->font->DrawText("FullScreen", xc - 470, yc + 130);
	//	if (app->win->fullscreen == true) app->font->DrawText("X", xc - 325, yc + 130);

	//	app->font->DrawText("VSync", xc - 470, yc + 170);
	//	if (app->render->Vsync == true) app->font->DrawText("X", xc - 325, yc + 170);


	//	app->font->DrawText("X", xc - 180, yc + 37);
	//}


	/*app->font->DrawText("Music", 170, 85);
	app->font->DrawText("SFX", 170, 125);
	app->font->DrawText("FullScreen", 170, 165);
	app->font->DrawText("VSync", 170, 205);*/

	/*app->font->DrawText("FPS cap", 170, 245);
	app->font->DrawText("30", 290, 245);
	fpscap == false? app->font->DrawText("X", 330, 245) : app->font->DrawText("X", 410, 245);
	app->font->DrawText("60", 370, 245);*/
	

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

			if(app->audio->vol < 100)app->audio->vol += 5; app->audio->ChangeVolume(app->audio->vol);
			
			app->audio->PlayFx(btnSelection);
		}

		if (control->id == 7)
		{
			LOG("volume -");
			if (app->audio->vol > 0)app->audio->vol -= 5; app->audio->ChangeVolume(app->audio->vol);
			app->audio->PlayFx(btnSelection);
		}
		if (control->id == 8)
		{
			LOG("FX +");
			app->audio->PlayFx(btnSelection);
			if (app->audio->volFX < 100)app->audio->volFX += 5; app->audio->ChangeFXVolume(app->audio->volFX);
		}
		if (control->id == 9)
		{
			LOG("FX -");
			if (app->audio->volFX > 0)app->audio->volFX -= 5; app->audio->ChangeFXVolume(app->audio->volFX);
			app->audio->PlayFx(btnSelection);
		}
		if (control->id == 10)
		{
			LOG("FULLSCREeN");
			/*	Uint32 flags = SDL_WINDOW_SHOWN;*/
			app->audio->PlayFx(btnSelection);
			if (app->win->fullscreen == false) {
				app->win->fullscreen = true;
				app->win->SwitchScreen();
				/*	if (app->win->fullscreen == true) flags |= SDL_WINDOW_FULLSCREEN;*/
			}
			else if (app->win->fullscreen == true) {
				app->win->fullscreen = false;
				app->win->SwitchScreen();
			}
		}
		if (control->id == 11)
		{
			LOG("VSYNC");
			if (!app->render->Vsync)app->render->Vsync=true;
			else app->render->Vsync=false;
			app->audio->PlayFx(btnSelection);
		}
		/*if (control->id == 12)
		{
			LOG("volume -");

		}
		if (control->id == 13)
		{
			LOG("volume -");

		}*/
		if (control->id == 14)
		{
			LOG("BACK");
			if (!app->scene->playing) {
				if (pause == false) {
					pause = true;
					app->audio->PlayFx(backFx);
				}
				Disable();
			}
			else
			{
				Disable();
			}
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

	// Borra los botones que sino invaden el proyecto. Aquí solo se invade Francia.
	musp->state = GuiControlState::DISABLED;
	musm->state = GuiControlState::DISABLED;
	FXp->state = GuiControlState::DISABLED;
	FXm->state = GuiControlState::DISABLED;
	fullS->state = GuiControlState::DISABLED;
	Vsync->state = GuiControlState::DISABLED;
	//frcap30->state = GuiControlState::DISABLED;
	//frcap60->state = GuiControlState::DISABLED;
	back->state = GuiControlState::DISABLED;


	return true;
}