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

	return true;
}

// Render bullshit
bool Inventory::PostUpdate()
{
	bool ret = true;

	//int x = -app->camera->GetPos().x / 2 /* - app->win->GetWidth() / 2*/;
	//int y = -app->camera->GetPos().y / 2 /* - app->win->GetHeight() * 2*/;

	//app->font->DrawText("Inventory is Open", x, y);

	//LOG("%d %d %d %d %d %d", x, y, app->camera->GetPos().x, app->camera->GetPos().y, app->scene->player->position.x, app->scene->player->position.y);

	// Draw UI & texts

	app->render->DrawTexture(inventoryBG, 0, 0);

	return ret;
}

bool Inventory::CleanUp()
{
	LOG("Closing Inventory");

	// Allow player to move
	app->scene->player->canMove = true;

	inventoryOnBattle = false;

	return true;
}