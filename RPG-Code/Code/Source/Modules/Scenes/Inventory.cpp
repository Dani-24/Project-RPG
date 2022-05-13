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

#include "Battle.h"

Inventory::Inventory(App* application, bool start_enabled) : Module(application, start_enabled)
{
	name.Create("inventory");
}

Inventory::~Inventory()
{}

bool Inventory::Awake(pugi::xml_node& config)
{
	LOG("Awakening Inventory");
	bool ret = true;

	return ret;
}

bool Inventory::Start()
{
	LOG("Starting Inventory");

	// Block player movement
	app->scene->player->canMove = false;

	if (app->battle->isEnabled()) {
		inventoryOnBattle = true;
	}

	// Load party characters
	charactersOnUI = app->stages->partyListPtr;
	//itemsOnUI = app->stages->itemsList;

	// Load assets

	if (inventoryOnBattle == false) {
		inventoryBG = app->tex->Load("Assets/gui/inventory/ui_inventory.png");
	}
	else {
		inventoryBG = app->tex->Load("Assets/gui/inventory/ui_inventory_battle.png");
	}

	// Esta deberia ir con un animation que cada frame sea cada arma
	//weaponType = app->tex->Load("Assets/gui/inventory/ui_inventory.png");

	// Buttons
	backButton = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 298, "Back", { (-app->camera->GetPos().x / 2) + 20, (-app->camera->GetPos().y / 2) + 10, 74, 32 }, this);
	statsButton = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 299, "Stats", { (-app->camera->GetPos().x / 2) + 20, (-app->camera->GetPos().y / 2) + 45, 74, 32 }, this);

	backButtonTexture = app->tex->Load("Assets/gui/buttons/back_text.png");
	backButtonPressedTexture = app->tex->Load("Assets/gui/buttons/pressed_back_text.png");

	statsButtonTexture = app->tex->Load("Assets/gui/buttons/stats.png");
	statsButtonPressedTexture = app->tex->Load("Assets/gui/buttons/pressed_stats.png");

	// SFX
	buttonSfx = app->audio->LoadFx("Assets/audio/sfx/fx_select_confirm.wav");
	backSfx = app->audio->LoadFx("Assets/audio/sfx/fx_select_back.wav");

	app->scene->showLocation = false;

	return true;
}

bool Inventory::PreUpdate()
{
	bool ret = true;

	// Get Inputs here

	return ret;
}

bool Inventory::Update(float dt)
{

	if (app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_UP) {
		Disable();
	}

	app->scene->guiactivate = true;

	return true;
}

// Render bullshit
bool Inventory::PostUpdate()
{
	bool ret = true;

	int x = -app->camera->GetPos().x / 2;
	int y = -app->camera->GetPos().y / 2;

	// Draw UI

	app->render->DrawTexture(inventoryBG, x, y);

	backButton->state != GuiControlState::PRESSED ? app->render->DrawTexture(backButtonTexture, backButton->bounds.x, backButton->bounds.y) : app->render->DrawTexture(backButtonPressedTexture, backButton->bounds.x, backButton->bounds.y);
	statsButton->state != GuiControlState::PRESSED ? app->render->DrawTexture(statsButtonTexture, statsButton->bounds.x, statsButton->bounds.y) : app->render->DrawTexture(statsButtonPressedTexture, statsButton->bounds.x, statsButton->bounds.y);

	return ret;
}

bool Inventory::CleanUp()
{
	LOG("Closing Inventory");

	// Allow player to move
	app->scene->player->canMove = true;

	inventoryOnBattle = false;

	buttonsIDCount = 300;

	backButton->state = GuiControlState::DISABLED;
	statsButton->state = GuiControlState::DISABLED;

	app->scene->showLocation = true;

	app->tex->UnLoad(backButtonTexture);
	app->tex->UnLoad(backButtonPressedTexture);
	app->tex->UnLoad(statsButtonPressedTexture);
	app->tex->UnLoad(statsButtonTexture);

	buttonSfx = NULL;

	return true;
}

bool Inventory::OnGuiMouseClickEvent(GuiControl* control)
{
	switch (control->type)
	{		
	case GuiControlType::BUTTON:
	{
			//Checks the GUI element ID
		if (control->id == 298)
		{
			LOG("Click on Back");

			app->audio->PlayFx(backSfx);

			Disable();
		}

		if (control->id == 299)
		{
			LOG("Stats button");

			app->audio->PlayFx(buttonSfx);
		}
		
		for (int i = 300; i < buttonsIDCount; i++) {
			if (control->id == i) {
				// PRESS ON X BUTTON
			}
		}

		default: break;
		}
	}
	return true;
}
