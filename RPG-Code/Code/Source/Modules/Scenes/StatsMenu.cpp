#include "StatsMenu.h"
#include "App.h"
#include "Inventory.h"

#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"

#include "Scene.h"
#include "Stages.h"
#include "GuiManager.h"
#include "FadeToBlack.h"
#include "Player.h"
#include "Camera.h"

StatsMenu::StatsMenu(App* application, bool start_enabled) : Module(application, start_enabled)
{
	name.Create("stmen");
}

StatsMenu::~StatsMenu()
{}

bool StatsMenu::Awake(pugi::xml_node& config)
{
	LOG("Awakening STATS MENU");
	bool ret = true;

	return ret;
}

bool StatsMenu::Start()
{
	LOG("Starting STATS MENU");

	// Block player movement
	app->scene->player->canMove = false;

	// Buttons
	backButton = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 400, "Back", { (-app->camera->GetPos().x / 2) + 20, (-app->camera->GetPos().y / 2) + 10, 74, 32 }, this);
	//statsButton = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 299, "Stats", { (-app->camera->GetPos().x / 2) + 20, (-app->camera->GetPos().y / 2) + 45, 74, 32 }, this);

	backButtonTexture = app->tex->Load("Assets/gui/buttons/back_text.png");
	backButtonPressedTexture = app->tex->Load("Assets/gui/buttons/pressed_back_text.png");

	gui = app->tex->Load("Assets/gui/inventory/UI_stats.png");

	// SFX
	buttonSfx = app->audio->LoadFx("Assets/audio/sfx/fx_select_confirm.wav");
	backSfx = app->audio->LoadFx("Assets/audio/sfx/fx_select_back.wav");

	app->scene->showLocation = false;

	return true;
}

bool StatsMenu::PreUpdate()
{
	bool ret = true;

	// Get Inputs here

	return ret;
}

bool StatsMenu::Update(float dt)
{

	//if (app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_UP) {
	//	Disable();
	//}

	//app->scene->guiactivate = true;

	return true;
}

// Render bullshit
bool StatsMenu::PostUpdate()
{
	bool ret = true;

	int x = -app->camera->GetPos().x / 2;
	int y = -app->camera->GetPos().y / 2;

	// Draw UI

	app->render->DrawTexture(gui, x, y);

	backButton->state != GuiControlState::PRESSED ? app->render->DrawTexture(backButtonTexture, backButton->bounds.x, backButton->bounds.y) : app->render->DrawTexture(backButtonPressedTexture, backButton->bounds.x, backButton->bounds.y);
	//statsButton->state != GuiControlState::PRESSED ? app->render->DrawTexture(statsButtonTexture, statsButton->bounds.x, statsButton->bounds.y) : app->render->DrawTexture(statsButtonPressedTexture, statsButton->bounds.x, statsButton->bounds.y);

	return ret;
}

bool StatsMenu::CleanUp()
{
	LOG("Closing STATS MENU");

	//// Allow player to move
	app->scene->player->canMove = true;

	//backButton->state = GuiControlState::DISABLED;
	////statsButton->state = GuiControlState::DISABLED;

	//app->scene->showLocation = true;

	//app->tex->UnLoad(backButtonTexture);
	//app->tex->UnLoad(backButtonPressedTexture);
	
	return true;
}

bool StatsMenu::OnGuiMouseClickEvent(GuiControl* control)
{
	switch (control->type)
	{
		case GuiControlType::BUTTON:
		{
			
			if (control->id == 400)
			{
				LOG("Click on Back");

				Disable();

			}
			if (control->id == 401)
			{
				LOG("Click on Back");

				Disable();
				app->inventory->Enable();
			}
			
		default: break;
		}
	}
	return true;
}