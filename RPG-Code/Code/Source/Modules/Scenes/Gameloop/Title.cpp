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

#include "Defs.h"
#include "Log.h"

#define CREDITS_LINK "https://github.com/Dani-24/Project-RPG"

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

	// GUI
	btn1 = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 1, "Start", { (app->win->GetWidth() / 2) - 580, (app->win->GetWidth() / 50) + 250, 74, 32 }, this);
	btn2 = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 2, "Albert", { (app->win->GetWidth() / 2) - 470, (app->win->GetWidth() / 50) + 250, 74, 32 }, this);
	btn3 = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 3, "sos", { (app->win->GetWidth() / 2) - 360, (app->win->GetWidth() / 50) + 250, 74, 32 }, this);
	btn4 = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 4, "putaso", { (app->win->GetWidth() / 2) - 250, (app->win->GetWidth() / 50) + 250, 74, 32 }, this);
	btn5 = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 5, "comoLaAbuela", { (app->win->GetWidth() / 2) - 140, (app->win->GetWidth() / 50) + 250, 74, 32 }, this);

	// Load Assets

	startb = app->tex->Load("Assets/gui/buttonstart.png");
	continueb = app->tex->Load("Assets/gui/buttoncontinue.png");
	optionsb = app->tex->Load("Assets/gui/buttonoptions.png");
	creditsb = app->tex->Load("Assets/gui/buttoncredits.png");
	exitb = app->tex->Load("Assets/gui/buttonexit.png");
	title = app->tex->Load("Assets/textures/title.png");

	app->audio->PlayMusic("Assets/audio/music/music_title.ogg");

	confirmFx = app->audio->LoadFx("Assets/audio/sfx/fx_select_confirm.wav");

	
	app->camera->SetPos({ 0,0 });

	pause = false;

	start = false;
	continu = false;
	credits = false;
	exit = false;

	return true;
}


bool TitleScene::OnGuiMouseClickEvent(GuiControl* control)
{
	switch (control->type)
	{
	case GuiControlType::BUTTON:
	{
		//Checks the GUI element ID
		if (control->id == 1)
		{
			LOG("Click on Start");

			start = true;
		}

		if (control->id == 2)
		{
			LOG("Click on Continue");
		}
		if (control->id == 3)
		{
			LOG("Click on Options");

			options = true;

		}
		if (control->id == 4)
		{
			LOG("Click on Credits");

			LOG("Opening Link : %s", CREDITS_LINK);
			SDL_OpenURL(CREDITS_LINK);
		}
		if (control->id == 5)
		{
			LOG("Click on Exit");
			exit = true;
		}
	}
	//Other cases here

	default: break;
	}

	return true;
}


// Called each loop iteration
bool TitleScene::PreUpdate()
{
	bool ret = true;

	if (start == true) {
		if (pause == false) {
			pause = true;
			app->audio->PlayFx(confirmFx);
		}
		app->stages->ChangeStage(StageIndex::TOWN);

		app->fade->DoFadeToBlack(this, (Module*)app->scene);
	}

	if (options == true) {
		options = false;
		app->audio->PlayFx(confirmFx);
		
		app->fade->DoFadeToBlack(this, (Module*)app->conf);
	}

	if (app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN || exit == true) {
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
	app->render->DrawTexture(startb, (app->win->GetWidth() / 2) - 580, (app->win->GetWidth() / 50) + 250);
	app->render->DrawTexture(continueb, (app->win->GetWidth() / 2) - 470, (app->win->GetWidth() / 50) + 250);
	app->render->DrawTexture(optionsb, (app->win->GetWidth() / 2) - 360, (app->win->GetWidth() / 50) + 250);
	app->render->DrawTexture(creditsb, (app->win->GetWidth() / 2) - 250, (app->win->GetWidth() / 50) + 250);
	app->render->DrawTexture(exitb, (app->win->GetWidth() / 2) - 140, (app->win->GetWidth() / 50) + 250);

	return ret;
}

// Called before quitting
bool TitleScene::CleanUp()
{
	LOG("Freeing Title scene");

	app->font->CleanFonts();

	btn1->state = GuiControlState::DISABLED;
	btn2->state = GuiControlState::DISABLED;
	btn3->state = GuiControlState::DISABLED;
	btn4->state = GuiControlState::DISABLED;
	btn5->state = GuiControlState::DISABLED;

	return true;
}