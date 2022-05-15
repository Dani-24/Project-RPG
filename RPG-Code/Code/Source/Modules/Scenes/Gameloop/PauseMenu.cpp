#include "PauseMenu.h"
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
#include "GuiManager.h"
#include "Camera.h"
#include "Player.h"
#include "Defs.h"
#include "Log.h"
#include "Shop.h"
#include "GuiButton.h"
#include "Configuration.h"
#include "Battle.h"
#include "Inventory.h"
#include "StatsMenu.h"

PauseMenu::PauseMenu(App* application, bool start_enabled) : Module(application, start_enabled)
{
	name.Create("pauseMenu");
	
}

// Destructor
PauseMenu::~PauseMenu()
{}

// Called before render is available
bool PauseMenu::Awake(pugi::xml_node& config)
{
	LOG("Loading Title");
	bool ret = true;

	

	return ret;
}

// Called before the first frame
bool PauseMenu::Start()
{
	// GUI
	party = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 21, "Start", { (app->win->GetWidth() / 2) - 580, (app->win->GetWidth() / 50) + 250, 74, 20 }, this);
	invent = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 22, "Albert", { (app->win->GetWidth() / 2) - 470, (app->win->GetWidth() / 50) + 250, 74, 20 }, this);
	town = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 23, "sos", { (app->win->GetWidth() / 2) - 360, (app->win->GetWidth() / 50) + 250, 74, 20 }, this);
	resume = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 24, "putaso", { (app->win->GetWidth() / 2) - 250, (app->win->GetWidth() / 50) + 250, 74, 20 }, this);
	config = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 25, "comoLaAbuela", { (app->win->GetWidth() / 2) - 140, (app->win->GetWidth() / 50) + 250, 74, 20 }, this);
	save = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 26, "comoLaAbuela", { (app->win->GetWidth() / 2) - 140, (app->win->GetWidth() / 50) + 250, 74, 20 }, this);
	load = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 27, "comoLaAbuela", { (app->win->GetWidth() / 2) - 140, (app->win->GetWidth() / 50) + 250, 74, 20 }, this);
	exit = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 28, "comoLaAbuela", { (app->win->GetWidth() / 2) - 140, (app->win->GetWidth() / 50) + 250, 74, 20 }, this);
	
	DissButt();
	// Load Assets

	// Audio 

	confirmFx = app->audio->LoadFx("Assets/audio/sfx/fx_select_confirm.wav");

	Pausetex = app->tex->Load("Assets/gui/pause_menu2.png");
		
	resumen = false;
	pauseGame = false;
	exitg = false;
	_wait,wait = false; 

	return true;
}

bool PauseMenu::OnGuiMouseClickEvent(GuiControl* control)
{
	if (!app->conf->isEnabled()) {
		switch (control->type)
		{
		case GuiControlType::BUTTON:
		{
			//Checks the GUI element ID

			if (control->id == 21)
			{
				LOG("partu");
				app->stmen->Enable();
				resumen = true;
				
			}
			if (control->id == 22)
			{
				LOG("invent");

				app->inventory->Enable();
				resumen = true;
			}
			if (control->id == 23)
			{
				LOG("town");
				resumen = true;
				app->fade->DoFadeToBlack(StageIndex::TOWN);
			}
			if (control->id == 24)
			{
				LOG("resume");
				resumen = true;

			}
			if (control->id == 25)
			{
				LOG("config");
				DissButt();
				if (!app->conf->isEnabled())app->conf->Enable();
			}
			if (control->id == 26)
			{
				LOG("save");
				app->audio->PlayFx(app->scene->saveFx);
				app->SaveGameRequest();
			}
			if (control->id == 27)
			{
				LOG("loadd");
				resumen = true;
				app->audio->PlayFx(app->scene->loadFx);
				app->LoadGameRequest();
			}
			if (control->id == 28)
			{
				LOG("exit");
				exitg = true;
				resumen = true;
			}

		}
		//Other cases here

		default: break;
		}
	}
	return true;
}

bool PauseMenu::PreUpdate()
{
	bool ret = true;
	//ret = exitg;
	int xt, yt, xc, yc;

	//variables for textures
	xt = -app->camera->GetPos().x / 2 + app->win->GetWidth() / 2;
	yt = -app->camera->GetPos().y / 2 + app->win->GetHeight() / 2;

	//variables for text
	xc = -app->camera->GetPos().x / app->win->GetScale() + app->win->GetWidth() / 2;
	yc = -app->camera->GetPos().y / app->win->GetScale() + app->win->GetHeight() / 2;

	if (pauseGame)
	{
		party->SetPos({ xc - 100,yc - 265 });
		invent->SetPos({ xc - 100,yc - 240 });
		town->SetPos({ xc - 100,yc - 215 });
		resume->SetPos({ xc - 100, yc - 190 });
		config->SetPos({ xc - 100,yc - 165 });
		save->SetPos({ xc - 100,yc - 140 });
		load->SetPos({ xc - 100,yc - 115 });
		exit->SetPos({ xc - 100,yc - 90 });

		KeyboardControl();

	}
	return ret;
}

// Called each loop iteration
bool PauseMenu::Update(float dt)
{

	int xt, yt, xc, yc;
	GamePad& pad = app->input->pads[0];

	//variables for textures
	xt = -app->camera->GetPos().x / 2 + app->win->GetWidth() / 2;
	yt = -app->camera->GetPos().y / 2 + app->win->GetHeight() / 2;

	//variables for text
	xc = -app->camera->GetPos().x / app->win->GetScale() + app->win->GetWidth() / 2;
	yc = -app->camera->GetPos().y / app->win->GetScale() + app->win->GetHeight() / 2;
	if (!pad.start && !pad.b) _wait = true;

	if ((app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN || resumen == true || pad.start && _wait == true || pad.b&& _wait == true)&&app->scene->playing&&!app->battle->isEnabled() && !app->shop->isEnabled()) {

		if (pauseGame ){
			if (app->conf->isEnabled())app->conf->Disable();
			
			pauseGame = false;
			resumen = false;
			app->scene->player->canMove = true; app->scene->player->toggleGui = true;
			app->camera->SetTarget(app->scene->player);
			app->camera->SetLimits(640, 350, 4490, 4200);
			CleanUp();
		}
		else
		{
			/*if (app->inventory->isEnabled() == false) {*/
				pauseGame = true, app->scene->player->canMove = false; app->scene->player->toggleGui = false;
				EnButt();
				app->audio->ChangeVolume(app->audio->vol / 3);
			//}
		}
		_wait = false;
	}
	return true;
}

// Called each loop iteration
bool PauseMenu::PostUpdate()
{
	bool ret = true;
	SDL_Color c = { 0,0,0 };
	SDL_Color w = { 255,255,255 };
	int xt, yt, xc, yc;

	//variables for textures
	xt = -app->camera->GetPos().x / 2 + app->win->GetWidth() / 2;
	yt = -app->camera->GetPos().y / 2 + app->win->GetHeight() / 2;

	//variables for text
	xc = -app->camera->GetPos().x / app->win->GetScale() + app->win->GetWidth() / 2;
	yc = -app->camera->GetPos().y / app->win->GetScale() + app->win->GetHeight() / 2;


	if (pauseGame && app->scene->playing) {
		app->render->DrawRectangle({ xt + -1000 ,yt - 1000, 1000,1000  },0,0,0,120);

		app->render->DrawTexture(Pausetex, xc - 120, yc - 280);

		party->state != GuiControlState::FOCUSED ? app->font->DrawText("Party", xc - 100,yc - 265, c) : app->font->DrawText("Party", xc - 100, yc - 265, w);

		invent->state != GuiControlState::FOCUSED ? app->font->DrawText("Inventory", xc - 100,yc - 240, c): app->font->DrawText("Inventory", xc - 100, yc - 240, w);

		town->state != GuiControlState::FOCUSED ? app->font->DrawText("Town", xc - 100,yc - 215, c): app->font->DrawText("Town", xc - 100, yc - 215, w);

		resume->state != GuiControlState::FOCUSED ? app->font->DrawText("Resume", xc - 100, yc - 190, c): app->font->DrawText("Resume", xc - 100, yc - 190, w);

		config->state != GuiControlState::FOCUSED ? app->font->DrawText("Config.", xc - 100,yc - 165, c): app->font->DrawText("Config.", xc - 100, yc - 165, w);

		save->state != GuiControlState::FOCUSED ? app->font->DrawText("Save", xc - 100,yc - 140, c): app->font->DrawText("Save", xc - 100, yc - 140, w);

		load->state != GuiControlState::FOCUSED ? app->font->DrawText("Load", xc - 100,yc - 115, c): app->font->DrawText("Load", xc - 100, yc - 115, w);

		exit->state != GuiControlState::FOCUSED ? app->font->DrawText("Exit", xc - 100,yc - 90, c): app->font->DrawText("Exit", xc - 100, yc - 90, w);
	}
	return ret;
}

// Called before quitting
bool PauseMenu::CleanUp()
{
	LOG("Freeing Title scene");

	/*app->font->CleanFonts();*/

	DissButt();
	
	//app->tex->UnLoad(titleBg);
	//app->tex->UnLoad(startb);
	//app->tex->UnLoad(continueb);
	//app->tex->UnLoad(optionsb);
	//app->tex->UnLoad(creditsb);
	//app->tex->UnLoad(exitb);

	app->audio->ChangeVolume(app->audio->vol * 3);

	return true;
}

//called on preupdate
void PauseMenu::KeyboardControl()
{
	GamePad& pad = app->input->pads[0];
	if (!pad.down && !pad.up) wait = true;

	if (party->state == GuiControlState::NORMAL && invent->state == GuiControlState::NORMAL &&
		town->state == GuiControlState::NORMAL && resume->state == GuiControlState::NORMAL &&
		config->state == GuiControlState::NORMAL && save->state == GuiControlState::NORMAL &&
		load->state == GuiControlState::NORMAL && exit->state == GuiControlState::NORMAL)
	{
		if (app->input->GetKey(SDL_SCANCODE_UP) == KEY_DOWN || app->input->GetKey(SDL_SCANCODE_DOWN) ||
			app->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_DOWN || app->input->GetKey(SDL_SCANCODE_LEFT) == KEY_DOWN ||
			pad.right || pad.left || pad.up || pad.down)
		{
			party->state = GuiControlState::FOCUSED;
			app->guiManager->keyb = true;
		}
	}

	if (party->state == GuiControlState::FOCUSED) {

		if (app->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN || pad.a)
		{
			party->state = GuiControlState::PRESSED;
			party->NotifyObserver();
		}
		if (!pad.down && !pad.up) wait = true;
		
		if (app->input->GetKey(SDL_SCANCODE_DOWN) == KEY_DOWN || pad.down && wait == true) {
			invent->state = GuiControlState::FOCUSED;
			party->state = GuiControlState::NORMAL;
			wait = false;
		}
		if (app->input->GetKey(SDL_SCANCODE_UP) == KEY_DOWN || pad.up && wait == true) {
			exit->state = GuiControlState::FOCUSED;
			party->state = GuiControlState::NORMAL;
			wait = false;
		}
		
	}
	else if (invent->state == GuiControlState::FOCUSED) {

		if (app->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN || pad.a)
		{
			invent->state = GuiControlState::PRESSED;
			invent->NotifyObserver();
		}
		if (!pad.down && !pad.up) wait = true;
		if (app->input->GetKey(SDL_SCANCODE_DOWN) == KEY_DOWN || pad.down && wait == true) {
			town->state = GuiControlState::FOCUSED;
			invent->state = GuiControlState::NORMAL;
			wait = false;
		}

		if (app->input->GetKey(SDL_SCANCODE_UP) == KEY_DOWN || pad.up && wait == true) {
			party->state = GuiControlState::FOCUSED;
			invent->state = GuiControlState::NORMAL;
			wait = false;
		}

		
	}
	else if (town->state == GuiControlState::FOCUSED) {

		if (app->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN || pad.a)
		{
			town->state = GuiControlState::PRESSED;
			town->NotifyObserver();
		}
		if (!pad.down && !pad.up) wait = true;
		if (app->input->GetKey(SDL_SCANCODE_DOWN) == KEY_DOWN || pad.down && wait == true) {
			resume->state = GuiControlState::FOCUSED;
			town->state = GuiControlState::NORMAL;
			wait = false;
		}

		if (app->input->GetKey(SDL_SCANCODE_UP) == KEY_DOWN || pad.up && wait == true) {
			invent->state = GuiControlState::FOCUSED;
			town->state = GuiControlState::NORMAL;
			wait = false;
		}


	}
	else if (resume->state == GuiControlState::FOCUSED) {

		if (app->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN || pad.a)
		{
			resume->state = GuiControlState::PRESSED;
			resume->NotifyObserver();
		}
		if (!pad.down && !pad.up) wait = true;
		if (app->input->GetKey(SDL_SCANCODE_DOWN) == KEY_DOWN || pad.down && wait == true) {
			config->state = GuiControlState::FOCUSED;
			resume->state = GuiControlState::NORMAL;
			wait = false;
		}

		if (app->input->GetKey(SDL_SCANCODE_UP) == KEY_DOWN || pad.up && wait == true) {
			town->state = GuiControlState::FOCUSED;
			resume->state = GuiControlState::NORMAL;
			wait = false;
		}


	}
	else if (config->state == GuiControlState::FOCUSED) {

		if (app->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN || pad.a)
		{
			config->state = GuiControlState::PRESSED;
			config->NotifyObserver();
		}
		if (!pad.down && !pad.up) wait = true;
		if (app->input->GetKey(SDL_SCANCODE_DOWN) == KEY_DOWN || pad.down && wait == true) {
			save->state = GuiControlState::FOCUSED;
			config->state = GuiControlState::NORMAL;
			wait = false;
		}

		if (app->input->GetKey(SDL_SCANCODE_UP) == KEY_DOWN || pad.up && wait == true) {
			resume->state = GuiControlState::FOCUSED;
			config->state = GuiControlState::NORMAL;
			wait = false;
		}


	}
	else if (load->state == GuiControlState::FOCUSED) {

		if (app->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN || pad.a)
		{
			load->state = GuiControlState::PRESSED;
			load->NotifyObserver();
		}
		if (!pad.down && !pad.up) wait = true;
		if (app->input->GetKey(SDL_SCANCODE_DOWN) == KEY_DOWN || pad.down && wait == true) {
			exit->state = GuiControlState::FOCUSED;
			load->state = GuiControlState::NORMAL;
			wait = false;
		}

		if (app->input->GetKey(SDL_SCANCODE_UP) == KEY_DOWN || pad.up && wait == true) {
			save->state = GuiControlState::FOCUSED;
			load->state = GuiControlState::NORMAL;
			wait = false;
		}


	}
	else if (save->state == GuiControlState::FOCUSED) {

		if (app->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN || pad.a)
		{
			save->state = GuiControlState::PRESSED;
			save->NotifyObserver();
		}
		if (!pad.down && !pad.up) wait = true;
		if (app->input->GetKey(SDL_SCANCODE_DOWN) == KEY_DOWN || pad.down && wait == true) {
			load->state = GuiControlState::FOCUSED;
			save->state = GuiControlState::NORMAL;
			wait = false;
		}

		if (app->input->GetKey(SDL_SCANCODE_UP) == KEY_DOWN || pad.up && wait == true) {
			config->state = GuiControlState::FOCUSED;
			save->state = GuiControlState::NORMAL;
			wait = false;
		}


	}
	else if (exit->state == GuiControlState::FOCUSED) {

		if (app->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN || pad.a)
		{
			exit->state = GuiControlState::PRESSED;
			exit->NotifyObserver();
		}
		if (!pad.down && !pad.up) wait = true;

		if (app->input->GetKey(SDL_SCANCODE_UP) == KEY_DOWN || pad.up && wait == true) {
			load->state = GuiControlState::FOCUSED;
			exit->state = GuiControlState::NORMAL;
			wait = false;
		}


	}

}

void PauseMenu::EnButt()
{
	
		party->state = GuiControlState::NORMAL;
		invent->state = GuiControlState::NORMAL;
		town->state = GuiControlState::NORMAL;
		resume->state = GuiControlState::NORMAL;
		config->state = GuiControlState::NORMAL;
		save->state = GuiControlState::NORMAL;
		load->state = GuiControlState::NORMAL;
		exit->state = GuiControlState::NORMAL;
		party->state = GuiControlState::NORMAL;	
	
}

void PauseMenu::DissButt()
{
	party->state = GuiControlState::DISABLED;
	invent->state = GuiControlState::DISABLED;
	town->state = GuiControlState::DISABLED;
	resume->state = GuiControlState::DISABLED;
	config->state = GuiControlState::DISABLED;
	save->state = GuiControlState::DISABLED;
	load->state = GuiControlState::DISABLED;
	exit->state = GuiControlState::DISABLED;
}