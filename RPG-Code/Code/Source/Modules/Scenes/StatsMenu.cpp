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

	int x = -app->camera->GetPos().x / 2;
	int y = -app->camera->GetPos().y / 2;

	// Block player movement
	app->scene->player->canMove = false;

	// Buttons
	backButton = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 400, "Back", { x + 20, y + 10, 74, 32 }, this);
	invent = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 401, "invent", { x + 20, y + 45, 74, 32 }, this);
	invent->state = GuiControlState::DISABLED;


	ch1 = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 402, "ch1", { x + 50, y + 50, 196, 47 }, this);
	ch2 = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 403, "ch2", { x + 50, y + 50, 196, 47 }, this);
	ch3 = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 404, "ch3", { x + 50, y + 50, 196, 47 }, this);
	ch4 = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 405, "ch4", { x + 50, y + 50, 196, 47 }, this);
	ch1->state = GuiControlState::DISABLED;
	ch2->state = GuiControlState::DISABLED;
	ch3->state = GuiControlState::DISABLED;
	ch4->state = GuiControlState::DISABLED;

	backButtonTexture = app->tex->Load("Assets/gui/buttons/back_text.png");
	backButtonPressedTexture = app->tex->Load("Assets/gui/buttons/pressed_back_text.png");

	gui = app->tex->Load("Assets/gui/inventory/UI_stats.png");

	invTex = app->tex->Load("Assets/gui/buttons/invent.png");
	presinvTex = app->tex->Load("Assets/gui/buttons/pressed_invent.png");

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
	if (app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_UP) {
		Disable();
	}

	return ret;
}

bool StatsMenu::Update(float dt)
{
	int x = -app->camera->GetPos().x / 2;
	int y = -app->camera->GetPos().y / 2;

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
	int by = 20;
	if(invent->state == GuiControlState::DISABLED)invent->state = GuiControlState::NORMAL;
	// Draw UI

	app->render->DrawTexture(gui, x, y+10);

	backButton->state != GuiControlState::PRESSED ? app->render->DrawTexture(backButtonTexture, backButton->bounds.x, backButton->bounds.y ) : app->render->DrawTexture(backButtonPressedTexture, backButton->bounds.x, backButton->bounds.y );
	invent->state != GuiControlState::PRESSED ? app->render->DrawTexture(invTex, invent->bounds.x, invent->bounds.y) : app->render->DrawTexture(presinvTex, invent->bounds.x, invent->bounds.y );
	
	for (int i = 0; i < app->scene->partyList.count(); i++)
	{
		////FACEES
		app->render->DrawTexture(app->scene->partyList.At(i)->data->spriteFace, x + 33, y + 96 + i * 47);
		app->font->DrawText(app->scene->partyList.At(i)->data->name, x + 85, y + 103 + i * 50);


		//app->font->DrawText(app->scene->partyList.At(i)->data->stats,x,y);

	}
	return ret;
}

bool StatsMenu::CleanUp()
{
	LOG("Closing STATS MENU");

	//// Allow player to move
	app->scene->player->canMove = true;
	
	backButton->state = GuiControlState::DISABLED;
	invent->state = GuiControlState::DISABLED;

	ch1->state = GuiControlState::DISABLED;
	ch2->state = GuiControlState::DISABLED;
	ch3->state = GuiControlState::DISABLED;
	ch4->state = GuiControlState::DISABLED;

	////statsButton->state = GuiControlState::DISABLED;

	//app->scene->showLocation = true;

	app->tex->UnLoad(backButtonTexture);
	app->tex->UnLoad(backButtonPressedTexture);

	app->tex->UnLoad(invTex);
	app->tex->UnLoad(presinvTex);
	
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
				
				app->inventory->Enable();
				Disable();
				
			}
			
		default: break;
		}
	}
	return true;
}