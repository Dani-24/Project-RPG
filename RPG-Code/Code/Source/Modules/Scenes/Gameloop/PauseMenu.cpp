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
#include "GuiButton.h"

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

	pauseGame = false;

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
	
	/*party->state = GuiControlState::DISABLED;*/
	invent->state = GuiControlState::DISABLED;
	town->state = GuiControlState::DISABLED;
	resume->state = GuiControlState::DISABLED;
	config->state = GuiControlState::DISABLED;
	save->state = GuiControlState::DISABLED;
	load->state = GuiControlState::DISABLED;
	exit->state = GuiControlState::DISABLED;
	// Load Assets

	// Audio 

	confirmFx = app->audio->LoadFx("Assets/audio/sfx/fx_select_confirm.wav");

	Pausetex = app->tex->Load("Assets/gui/pause_menu2.png");
	// Set camera to 0,0

	//app->camera->SetPos({ 0,0 });

	
	resumen = false;
	

	return true;
}


bool PauseMenu::OnGuiMouseClickEvent(GuiControl* control)
{
	
	switch (control->type)
	{
	case GuiControlType::BUTTON:
	{
		//Checks the GUI element ID
		
		if (control->id == 21)
		{
			LOG("partu");
		}
		if (control->id == 22)
		{
			LOG("invenyt");
		}
		if (control->id == 23)
		{
			LOG("town");
		}
		if (control->id == 24)
		{
			LOG("resume");
			resumen = true;

		}
		if (control->id == 25)
		{
			LOG("config");
		}
		if (control->id == 26)
		{
			LOG("save");
		}
		if (control->id == 27)
		{
			LOG("loadd");
		}
		if (control->id == 28)
		{
			LOG("exit");
		}
		
	}
	//Other cases here

	default: break;
	}
	
	return true;
}


// Called each loop iteration
bool PauseMenu::PreUpdate()
{
	bool ret = true;

	//int xt, yt, xc, yc;

	////variables for textures
	//xt = -app->camera->GetPos().x / 2 + app->win->GetWidth() / 2;
	//yt = -app->camera->GetPos().y / 2 + app->win->GetHeight() / 2;

	////variables for text
	//xc = -app->camera->GetPos().x / app->win->GetScale() + app->win->GetWidth() / 2;
	//yc = -app->camera->GetPos().y / app->win->GetScale() + app->win->GetHeight() / 2;

	if (pauseGame)
	{
		

		

	}

	//if (start == true) {
	//	if (pause == false) {
	//		pause = true;
	//		app->audio->PlayFx(confirmFx);
	//	}
	//	app->stages->ChangeStage(StageIndex::TOWN);

	//	app->fade->DoFadeToBlack(this, (Module*)app->scene);
	//}

	//if (options == true) {
	//	options = false;
	//	app->audio->PlayFx(confirmFx);

	//	app->fade->DoFadeToBlack(this, (Module*)app->conf);
	//}

	//if (app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN || exit == true) {
	//	ret = false;
	//}
	return ret;
}

// Called each loop iteration
bool PauseMenu::Update(float dt)
{

	int xt, yt, xc, yc;

	//variables for textures
	xt = -app->camera->GetPos().x / 2 + app->win->GetWidth() / 2;
	yt = -app->camera->GetPos().y / 2 + app->win->GetHeight() / 2;

	//variables for text
	xc = -app->camera->GetPos().x / app->win->GetScale() + app->win->GetWidth() / 2;
	yc = -app->camera->GetPos().y / app->win->GetScale() + app->win->GetHeight() / 2;
	party->SetPos({ xc - 100,yc - 265 });
	if (app->input->GetKey(SDL_SCANCODE_P) == KEY_DOWN || resumen == true) {

		if (pauseGame){
			pauseGame = false;
			resumen = false;
			app->scene->player->canMove = true;
			CleanUp();
		}
		else
		{
			pauseGame = true, app->scene->player->canMove = false;
			party->state = GuiControlState::NORMAL;
			invent->state = GuiControlState::NORMAL;
			town->state = GuiControlState::NORMAL;
			resume->state = GuiControlState::NORMAL;
			config->state = GuiControlState::NORMAL;
			save->state = GuiControlState::NORMAL;
			load->state = GuiControlState::NORMAL;
			exit->state = GuiControlState::NORMAL;
			party->state= GuiControlState::NORMAL;
			
			invent->SetPos({ xc - 100,yc - 240 });
			town->SetPos({ xc - 100,yc - 215 });
			resume->SetPos({ xc - 100, yc - 190 });
			config->SetPos({ xc - 100,yc - 165 });
			save->SetPos({ xc - 100,yc - 140 });
			load->SetPos({ xc - 100,yc - 115 });
			exit->SetPos({ xc - 100,yc - 90 });
		}
		
	}

	
		return true;
}

// Called each loop iteration
bool PauseMenu::PostUpdate()
{
	bool ret = true;

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

		app->font->DrawText("Party", xc - 100,yc - 265);

		app->font->DrawText("Inventory", xc - 100,yc - 240);

		app->font->DrawText("Town", xc - 100,yc - 215);

		app->font->DrawText("Resume", xc - 100, yc - 190);

		app->font->DrawText("Config.", xc - 100,yc - 165);

		app->font->DrawText("Save", xc - 100,yc - 140);

		app->font->DrawText("Load", xc - 100,yc - 115);

		app->font->DrawText("Exit", xc - 100,yc - 90);
	}

	
	return ret;
}

// Called before quitting
bool PauseMenu::CleanUp()
{
	LOG("Freeing Title scene");

	/*app->font->CleanFonts();*/

	party->state = GuiControlState::DISABLED;
	invent->state = GuiControlState::DISABLED;
	town->state = GuiControlState::DISABLED;
	resume->state = GuiControlState::DISABLED;
	config->state = GuiControlState::DISABLED;
	save->state = GuiControlState::DISABLED;
	load->state = GuiControlState::DISABLED;
	exit->state = GuiControlState::DISABLED;
	
	//app->tex->UnLoad(titleBg);
	//app->tex->UnLoad(startb);
	//app->tex->UnLoad(continueb);
	//app->tex->UnLoad(optionsb);
	//app->tex->UnLoad(creditsb);
	//app->tex->UnLoad(exitb);

	return true;
}