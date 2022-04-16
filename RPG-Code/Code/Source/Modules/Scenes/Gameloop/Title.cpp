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

#define CREDITS_LINK "https://www.youtube.com/watch?v=FJ-Dhxs1EGM&ab_channel=Jabenyezza"

TitleScene::TitleScene(App* application, bool start_enabled) : Module(application, start_enabled)
{
	name.Create("titleScene");
}

// Destructor
TitleScene::~TitleScene()
{}

// Called before render is available
bool TitleScene::Awake(pugi::xml_node& config)
{
	LOG("Loading Title");
	bool ret = true;

	startChar = config.child("startb").attribute("path").as_string();
	contChar = config.child("continueb").attribute("path").as_string();
	optChar = config.child("optionsb").attribute("path").as_string();
	credChar = config.child("creditsb").attribute("path").as_string();
	exitChar = config.child("exitb").attribute("path").as_string();
	titlChar = config.child("title").attribute("path").as_string();
	mustitlChar = config.child("mustitle").attribute("path").as_string();
	fxselChar = config.child("sfsxconfirm").attribute("path").as_string();

	return ret;
}

// Called before the first frame
bool TitleScene::Start()
{
	// Set title animation
	int N = 498, M = 249;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 4; j++) {
			titleBGAnim.PushBack({ N * j, M * i, N, M });
		}
	}
	titleBGAnim.speed = 0.0005f;
	titleBGAnim.loop = true;

	// GUI
	btn1 = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 1, "Start", { (app->win->GetWidth() / 2) - 580, (app->win->GetWidth() / 50) + 250, 74, 32 }, this);
	btn2 = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 2, "Albert", { (app->win->GetWidth() / 2) - 470, (app->win->GetWidth() / 50) + 250, 74, 32 }, this);
	btn3 = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 3, "sos", { (app->win->GetWidth() / 2) - 360, (app->win->GetWidth() / 50) + 250, 74, 32 }, this);
	btn4 = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 4, "putaso", { (app->win->GetWidth() / 2) - 250, (app->win->GetWidth() / 50) + 250, 74, 32 }, this);
	btn5 = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 5, "comoLaAbuela", { (app->win->GetWidth() / 2) - 140, (app->win->GetWidth() / 50) + 250, 74, 32 }, this);

	// Load Assets

	startb = app->tex->Load("Assets/gui/button_start.png");
	continueb = app->tex->Load("Assets/gui/button_continue.png");
	optionsb = app->tex->Load("Assets/gui/button_options.png");
	creditsb = app->tex->Load("Assets/gui/button_credits.png");
	exitb = app->tex->Load("Assets/gui/button_exit.png");

	titleBg = app->tex->Load("Assets/textures/title_screen_bg.png");

	// Audio 

	app->audio->PlayMusic("Assets/audio/music/music_title.ogg");
	confirmFx = app->audio->LoadFx("Assets/audio/sfx/fx_select_confirm.wav");

	// Set camera to 0,0

	app->camera->SetPos({ 0,0 });

	pause = exitGame = false;

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

			if (pause == false) {

				app->audio->PlayFx(confirmFx);

				app->stages->ChangeStage(StageIndex::TOWN);

				app->fade->DoFadeToBlack(this, (Module*)app->scene);
			}
		}

		if (control->id == 2)
		{
			LOG("Click on Continue");
		}
		if (control->id == 3)
		{
			LOG("Click on Options");

			if (pause == false) {

				app->audio->PlayFx(confirmFx);

				app->fade->DoFadeToBlack(this, (Module*)app->conf);
			}

		}
		if (control->id == 4)
		{
			LOG("Click on Credits");

			if (pause == false) {

				LOG("Opening Link : %s", CREDITS_LINK);
				SDL_OpenURL(CREDITS_LINK);

			}
		}
		if (control->id == 5)
		{
			LOG("Click on Exit");
			
			if (pause == false) {
				exitGame = true;
			}
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
	if (app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN || exitGame == true) {
		return false;
	}

	pause = app->fade->fading;

	return true;
}

// Called each loop iteration
bool TitleScene::Update(float dt)
{
	titleBGAnim.Update(dt);

	return true;
}

// Called each loop iteration
bool TitleScene::PostUpdate()
{
	bool ret = true;

	// Draw BG
	app->render->DrawTexture(titleBg, 65, 50, &titleBGAnim.GetCurrentFrame());

	// Render Buttons
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

	app->tex->UnLoad(titleBg);
	app->tex->UnLoad(startb);
	app->tex->UnLoad(continueb);
	app->tex->UnLoad(optionsb);
	app->tex->UnLoad(creditsb);
	app->tex->UnLoad(exitb);

	return true;
}