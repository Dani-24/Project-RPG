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
#include "PauseMenu.h"
#include "Configuration.h"

#include "Defs.h"
#include "Log.h"

#define CREDITS_LINK "https://github.com/Dani-24/Project-RPG"

TitleScene::TitleScene(App* application, bool start_enabled) : Module(application, start_enabled)
{
	name.Create("titleScene");
}

TitleScene::~TitleScene()
{}

bool TitleScene::Awake(pugi::xml_node& config)
{
	LOG("Loading Title");
	bool ret = true;

	titlChar = config.child("title").attribute("path").as_string();
	mustitlChar = config.child("mustitle").attribute("path").as_string();
	fxselChar = config.child("sfsxconfirm").attribute("path").as_string();
	fxtitleChar = config.child("sfxtitle").attribute("path").as_string();

	return ret;
}

bool TitleScene::Start()
{

	// GUI
	btn1 = (GuiButton*)app->guiManager->CreateGuiControl(this, GuiControlType::BUTTON, 1, "Start", { (app->win->GetWidth() / 2) - 580, (app->win->GetWidth() / 50) + 250 } );
	btn2 = (GuiButton*)app->guiManager->CreateGuiControl(this, GuiControlType::BUTTON, 2, "Continue", { (app->win->GetWidth() / 2) - 470, (app->win->GetWidth() / 50) + 250 });
	btn3 = (GuiButton*)app->guiManager->CreateGuiControl(this, GuiControlType::BUTTON, 3, "Options", { (app->win->GetWidth() / 2) - 360, (app->win->GetWidth() / 50) + 250 });
	btn4 = (GuiButton*)app->guiManager->CreateGuiControl(this, GuiControlType::BUTTON, 4, "Credits", { (app->win->GetWidth() / 2) - 250, (app->win->GetWidth() / 50) + 250 });
	btn5 = (GuiButton*)app->guiManager->CreateGuiControl(this, GuiControlType::BUTTON, 5, "Exit", { (app->win->GetWidth() / 2) - 140, (app->win->GetWidth() / 50) + 250 });

	// Load Assets
	titleBg = app->tex->Load("Assets/textures/title_screen_bg.png");
	titleLogo = app->tex->Load("Assets/textures/title_screen_logo.png");

	// Audio 

	app->audio->PlayMusic("Assets/audio/music/music_title.ogg");
	confirmFx = app->audio->LoadFx("Assets/audio/sfx/fx_select_confirm.wav");
	titleFx = app->audio->LoadFx("Assets/audio/sfx/fx_title.wav");

	app->audio->PlayFx(titleFx);

	// Set camera to 0,0

	app->camera->SetPos({ 0,0 });

	pause = exitGame = app->scene->playing = wait = false;

	return true;
}

bool TitleScene::OnGuiMouseClickEvent(GuiControl* control)
{
	if (!app->conf->isEnabled()) {
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

					app->stages->ChangeStage(StageIndex::INTRODUCTION);

					app->fade->DoFadeToBlack(this, (Module*)app->scene);
				}
			}

			if (control->id == 2)
			{
				LOG("Click on Continue");
				if (pause == false) {
					app->audio->PlayFx(confirmFx);
					app->scene->playloading = true;
					/*app->stages->ChangeStage(StageIndex::TOWN);*/

					app->fade->DoFadeToBlack(this, (Module*)app->scene);
				}
			}
			if (control->id == 3)
			{
				LOG("Click on Options");

				if (pause == false) {

					app->audio->PlayFx(confirmFx);
					app->conf->Enable();
					//app->fade->DoFadeToBlack(this, (Module*)app->conf);
				}

			}
			if (control->id == 4)
			{
				LOG("Click on Credits");

				if (pause == false) {

					LOG("Opening Link : %s", CREDITS_LINK);
					SDL_OpenURL(CREDITS_LINK);
					app->guiManager->keyb = false;

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
	}
	return true;
}

bool TitleScene::PreUpdate()
{
	GamePad& pad = app->input->pads[0];
	//btn1->state = GuiControlState::PRESSED;
	if (app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN || exitGame == true) {
		app->pauseM->CleanUp();
		return false;
	}

	if (btn1->state == GuiControlState::NORMAL && btn2->state == GuiControlState::NORMAL &&
		btn3->state == GuiControlState::NORMAL && btn4->state == GuiControlState::NORMAL && btn5->state == GuiControlState::NORMAL)
	{
		if (app->input->GetKey(SDL_SCANCODE_UP) == KEY_DOWN || app->input->GetKey(SDL_SCANCODE_DOWN) ||
			app->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_DOWN || app->input->GetKey(SDL_SCANCODE_LEFT) == KEY_DOWN || pad.right || pad.left || pad.up || pad.down)
		{
			btn1->state = GuiControlState::FOCUSED;
			app->guiManager->keyb = true;
		}
	}

	if (btn1->state == GuiControlState::FOCUSED) {

		if (app->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN || pad.a)
		{
			
			btn1->state = GuiControlState::PRESSED;
			btn1->NotifyObserver();
		}
		if (!pad.right && !pad.left) wait = true;
		/*if (app->input->GetKey(SDL_SCANCODE_RETURN) == KEY_UP)
		{
			
		}*/

		if (app->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_DOWN ||pad.right&& wait==true) {
			btn2->state = GuiControlState::FOCUSED;
			btn1->state = GuiControlState::NORMAL;
			wait = false;
		}
		 
		/*if (btn2->state != GuiControlState::NORMAL || btn3->state != GuiControlState::NORMAL || btn4->state != GuiControlState::NORMAL) {
			btn1->state = GuiControlState::NORMAL;
		}*/
	}
	else if (btn2->state == GuiControlState::FOCUSED) {

		if (app->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN || pad.a)
		{
			btn2->state = GuiControlState::PRESSED;
			btn2->NotifyObserver();
		}
		if (!pad.right && !pad.left) wait = true;
		if (app->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_DOWN || pad.right && wait == true) {
			btn3->state = GuiControlState::FOCUSED;
			btn2->state = GuiControlState::NORMAL;
			wait = false;
		}

		if (app->input->GetKey(SDL_SCANCODE_LEFT) == KEY_DOWN || pad.left && wait == true) {
			btn1->state = GuiControlState::FOCUSED;
			btn2->state = GuiControlState::NORMAL;
			wait = false;
		}
		 
		/*if (btn1->state != GuiControlState::NORMAL || btn3->state != GuiControlState::NORMAL || btn4->state != GuiControlState::NORMAL) {
			btn2->state = GuiControlState::NORMAL;
		}*/
	}
	else if (btn3->state == GuiControlState::FOCUSED) {

		if (app->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN || pad.a)
		{
			btn3->state = GuiControlState::PRESSED;
			btn3->NotifyObserver();
		}
		if (!pad.right && !pad.left) wait = true;
		if (app->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_DOWN || pad.right && wait == true) {
			btn4->state = GuiControlState::FOCUSED;
			btn3->state = GuiControlState::NORMAL;
			wait = false;
		}

		if (app->input->GetKey(SDL_SCANCODE_LEFT) == KEY_DOWN || pad.left && wait == true) {
			btn2->state = GuiControlState::FOCUSED;
			btn3->state = GuiControlState::NORMAL;
			wait = false;
		}
		 
		//if (btn1->state != GuiControlState::NORMAL || btn2->state != GuiControlState::NORMAL || btn4->state != GuiControlState::NORMAL) {
		//	btn3->state = GuiControlState::NORMAL;
		//}
	}
	else if (btn4->state == GuiControlState::FOCUSED) {

		if (app->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN || pad.a)
		{
			btn4->state = GuiControlState::PRESSED;
			btn4->NotifyObserver();
		}
		if(!pad.right&&!pad.left) wait = true;
		if (app->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_DOWN || pad.right && wait == true) {
			btn5->state = GuiControlState::FOCUSED;
			btn4->state = GuiControlState::NORMAL;
			wait = false;
		}

		if (app->input->GetKey(SDL_SCANCODE_LEFT) == KEY_DOWN || pad.left && wait == true) {
			btn3->state = GuiControlState::FOCUSED;
			btn4->state = GuiControlState::NORMAL;
			wait = false;
		}
		
	}
	else if (btn5->state == GuiControlState::FOCUSED) {

		if (app->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN || pad.a)
		{
			btn5->state = GuiControlState::PRESSED;
			btn5->NotifyObserver();
		}
		if (!pad.right && !pad.left) wait = true;
		if (app->input->GetKey(SDL_SCANCODE_LEFT) == KEY_DOWN ||pad.left && wait == true) {
			btn4->state = GuiControlState::FOCUSED;
			btn5->state = GuiControlState::NORMAL;
			wait = false;
		}

		 
	/*if (btn1->state != GuiControlState::NORMAL || btn2->state != GuiControlState::NORMAL || btn3->state != GuiControlState::NORMAL) {
		btn4->state = GuiControlState::NORMAL;
	}*/
	}
	
	pause = app->fade->fading;

	return true;
}

bool TitleScene::Update(float dt)
{
	
	// BG movement
	angle += rotateSpeed * dt/1000;

	fPoint offset = { sinf(angle) * radius, cosf(angle) * radius };
	titleBgPos = {(int)centre.x + (int)offset.x, (int)centre.y + (int)offset.y};

	return true;
}

bool TitleScene::PostUpdate()
{
	bool ret = true;

	// Draw BG
	app->render->DrawTexture(titleBg, titleBgPos.x, titleBgPos.y);
	app->render->DrawTexture(titleLogo, 0, 0);

	return ret;
}

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
	app->tex->UnLoad(titleLogo);

	return true;
}