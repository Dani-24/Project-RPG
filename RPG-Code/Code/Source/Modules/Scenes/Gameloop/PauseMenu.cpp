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
	/*btn1 = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 1, "Start", { (app->win->GetWidth() / 2) - 580, (app->win->GetWidth() / 50) + 250, 74, 32 }, this);
	btn2 = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 2, "Albert", { (app->win->GetWidth() / 2) - 470, (app->win->GetWidth() / 50) + 250, 74, 32 }, this);
	btn3 = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 3, "sos", { (app->win->GetWidth() / 2) - 360, (app->win->GetWidth() / 50) + 250, 74, 32 }, this);
	btn4 = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 4, "putaso", { (app->win->GetWidth() / 2) - 250, (app->win->GetWidth() / 50) + 250, 74, 32 }, this);
	btn5 = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 5, "comoLaAbuela", { (app->win->GetWidth() / 2) - 140, (app->win->GetWidth() / 50) + 250, 74, 32 }, this);*/

	// Load Assets

	// Audio 

	confirmFx = app->audio->LoadFx("Assets/audio/sfx/fx_select_confirm.wav");

	Pausetex = app->tex->Load("Assets/gui/pause_menu2.png");
	// Set camera to 0,0

	//app->camera->SetPos({ 0,0 });

	

	

	return true;
}


bool PauseMenu::OnGuiMouseClickEvent(GuiControl* control)
{
	switch (control->type)
	{
	case GuiControlType::BUTTON:
	{
		//Checks the GUI element ID
		
		if (control->id == 2)
		{
			LOG("Click on Continue");
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
	if (app->input->GetKey(SDL_SCANCODE_P) == KEY_DOWN) {
		if (pauseGame)pauseGame = false, app->scene->player->canMove=true;
		else pauseGame = true, app->scene->player->canMove = false;
	}

	
		return true;
}

// Called each loop iteration
bool PauseMenu::PostUpdate()
{
	bool ret = true;
	if (pauseGame) {
		app->render->DrawRectangle({ -app->camera->GetPos().x / 2 + app->win->GetWidth() / 2 + -1000 ,
			-app->camera->GetPos().y / 2 + app->win->GetHeight() / 2-1000, 1000,1000  },0,0,0,120);
		app->render->DrawTexture(Pausetex, -app->camera->GetPos().x / app->win->GetScale() + app->win->GetWidth() / 2 - 120,
			-app->camera->GetPos().y / app->win->GetScale() + app->win->GetHeight() / 2 - 280);
	}

	
	return ret;
}

// Called before quitting
bool PauseMenu::CleanUp()
{
	LOG("Freeing Title scene");

	app->font->CleanFonts();

	//btn1->state = GuiControlState::DISABLED;
	//btn2->state = GuiControlState::DISABLED;
	//btn3->state = GuiControlState::DISABLED;
	//btn4->state = GuiControlState::DISABLED;
	//btn5->state = GuiControlState::DISABLED;

	//app->tex->UnLoad(titleBg);
	//app->tex->UnLoad(startb);
	//app->tex->UnLoad(continueb);
	//app->tex->UnLoad(optionsb);
	//app->tex->UnLoad(creditsb);
	//app->tex->UnLoad(exitb);

	return true;
}