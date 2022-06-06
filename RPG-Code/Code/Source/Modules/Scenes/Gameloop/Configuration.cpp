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
#include "Title.h"

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
	int x = -app->camera->GetPos().x / 2,
		y = -app->camera->GetPos().y / 2;
	int xb = 10, yb = 10;
	musp = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 6, "mus+", {x + (app->win->GetWidth() / 2) - 300 -xb,y + (app->win->GetWidth() / 50) + 50 +yb, 32, 32 }, this);
	musm = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 7, "mus-", { x + (app->win->GetWidth() / 2) - 350 - xb,y + (app->win->GetWidth() / 50) + 50 + yb, 32, 32 }, this);
	FXp = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 8, "FX+", { x + (app->win->GetWidth() / 2) - 300 - xb,y + (app->win->GetWidth() / 50) + 90 + yb, 32, 32 }, this);
	FXm = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 9, "FX-", { x + (app->win->GetWidth() / 2) - 350 - xb ,y + (app->win->GetWidth() / 50) + 90 + yb, 32, 32 }, this);
	fullS = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 10, "fulls", { x + (app->win->GetWidth() / 2) - 325 - xb,y + (app->win->GetWidth() / 50) + 130 + yb, 32, 32 }, this);
	Vsync = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 11, "vsync", { x + (app->win->GetWidth() / 2) - 325 - xb,y + (app->win->GetWidth() / 50) + 170 + yb, 32, 32 }, this);
	//frcap30 = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 12, "30fps", {x + (app->win->GetWidth() / 2) - 580,y + (app->win->GetWidth() / 50) + 230, 32, 32 }, this);
	//frcap60 = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 13, "60fps", {x + (app->win->GetWidth() / 2) - 580,y + (app->win->GetWidth() / 50) + 230, 32, 32 }, this);
	back = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 14, "back", { x + (app->win->GetWidth() / 2) - 178,y + (app->win->GetWidth() / 50) + 33 + yb, 32, 32 }, this);
	conb.add(musm);
	conb.add(musp);
	conb.add(FXm);
	conb.add(FXp);
	conb.add(fullS);
	conb.add(Vsync);
	conb.add(back);


	pause = false;
	
	ab = 0;

	return true;
}

bool Configuration::PreUpdate()
{
	bool ret = true;
	GampadBut();
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
	SDL_Color c = { 0,0,0 };

	int x = -app->camera->GetPos().x / 2,
		y = -app->camera->GetPos().y / 2;

	app->render->DrawTexture(background, x + (app->win->GetWidth() / 2) - 475, y + (app->win->GetWidth() / 50) + 40);

	app->font->DrawText("Music", x + (app->win->GetWidth() / 2) - xt, y + (app->win->GetWidth() / 50) + 50 -yt, c);
	app->font->DrawText("+", x + (app->win->GetWidth() / 2) - 300, y + (app->win->GetWidth() / 50) + 50 - yt, c);
	app->font->DrawText("-", x + (app->win->GetWidth() / 2) - 350, y + (app->win->GetWidth() / 50) + 50 - yt, c);
	app->font->DrawText(volchar, x + (app->win->GetWidth() / 2) - 265, y + (app->win->GetWidth() / 50) + 50 - yt, c);
	app->font->DrawText("SFX", x + (app->win->GetWidth() / 2) - xt, y + (app->win->GetWidth() / 50) + 90 - yt, c);
	app->font->DrawText("+", x + (app->win->GetWidth() / 2) - 300, y + (app->win->GetWidth() / 50) + 90 - yt, c);
	app->font->DrawText("-", x + (app->win->GetWidth() / 2) - 350, y + (app->win->GetWidth() / 50) + 90 - yt, c);
	app->font->DrawText(FXchar, x + (app->win->GetWidth() / 2) - 265, y + (app->win->GetWidth() / 50) + 90 - yt, c);

	app->font->DrawText("FullScreen", x + (app->win->GetWidth() / 2) - xt, y + (app->win->GetWidth() / 50) + 130 - yt, c);
	if (app->win->fullscreen == true) app->font->DrawText("X", x + (app->win->GetWidth() / 2) - 325, y + (app->win->GetWidth() / 50) + 130 - yt, c);

	app->font->DrawText("VSync", x + (app->win->GetWidth() / 2) - xt, y + (app->win->GetWidth() / 50) + 170 - yt, c);
	if (app->render->Vsync == true) app->font->DrawText("X", x + (app->win->GetWidth() / 2) - 325, y + (app->win->GetWidth() / 50) + 170 - yt, c);


	app->font->DrawText("X", x + (app->win->GetWidth() / 2) - 170, y + (app->win->GetWidth() / 50) + 47, c);

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
				app->pauseM->EnButt();
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

void Configuration::GampadBut()
{
	GamePad& pad = app->input->pads[0];
	if (!pad.a && !pad.b) _wait = true;
	
	int uplim = 6, dowlim = 0;

	//btn1->state = GuiControlState::PRESSED;
	if (app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN  || pad.b && _wait) {
		if (!app->scene->playing) {
			if (pause == false) {
				pause = true;
				app->audio->PlayFx(backFx);
			}
			Disable();
		}
		else
		{
			app->pauseM->EnButt();
			Disable();
		}
		app->titleScene->_wait = false;
		_wait = false;
		
	}

	if (musp->state == GuiControlState::NORMAL && musm->state == GuiControlState::NORMAL &&
		FXp->state == GuiControlState::NORMAL && FXm->state == GuiControlState::NORMAL && fullS->state == GuiControlState::NORMAL
		&& Vsync->state == GuiControlState::NORMAL && back->state == GuiControlState::NORMAL)
	{
		if (app->input->GetKey(SDL_SCANCODE_UP) == KEY_DOWN || app->input->GetKey(SDL_SCANCODE_DOWN) ||
			app->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_DOWN || app->input->GetKey(SDL_SCANCODE_LEFT) == KEY_DOWN || pad.right || pad.left || pad.up || pad.down)
		{
			conb.At(ab)->data->state = GuiControlState::FOCUSED;
			app->guiManager->keyb = true;
		}
	}

	if (conb.At(ab)->data->state == GuiControlState::FOCUSED) {

		if (app->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN || pad.a && _wait)
		{

			conb.At(ab)->data->state = GuiControlState::PRESSED;
			conb.At(ab)->data->NotifyObserver();
			conb.At(ab)->data->state = GuiControlState::FOCUSED;
			_wait = false;
		}

		
		if (!pad.down && !pad.up) wait = true;

		if (app->input->GetKey(SDL_SCANCODE_DOWN) == KEY_DOWN || pad.down && wait == true) {
			if (ab!= uplim)
			{
				conb.At(ab)->data->state = GuiControlState::NORMAL;
				ab += 1;
				conb.At(ab)->data->state = GuiControlState::FOCUSED;
			}
			else
			{
				conb.At(ab)->data->state = GuiControlState::NORMAL;
				ab = dowlim;
				conb.At(ab)->data->state = GuiControlState::FOCUSED;
				
			}
			wait = false;
		}
		if (app->input->GetKey(SDL_SCANCODE_UP) == KEY_DOWN || pad.up && wait == true) {
			if (ab != dowlim)
			{
				conb.At(ab)->data->state = GuiControlState::NORMAL;
				ab -= 1;
				conb.At(ab)->data->state = GuiControlState::FOCUSED;
			}
			else
			{
				conb.At(ab)->data->state = GuiControlState::NORMAL;
				ab = uplim;
				conb.At(ab)->data->state = GuiControlState::FOCUSED;	
			}
			wait = false;
		}
		
	}
}