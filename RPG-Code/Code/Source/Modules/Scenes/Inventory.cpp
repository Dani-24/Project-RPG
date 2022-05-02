#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "Scene.h"
#include "Map.h"
#include "GuiManager.h"
#include "FadeToBlack.h"
#include "Player.h"
#include "EntityManager.h"
#include "Battle.h"
#include "Inventory.h"
#include "Defs.h"
#include "Log.h"

Inventory::Inventory(App* application, bool start_enabled) : Module(application, start_enabled)
{
	name.Create("inventory");
}

Inventory::~Inventory()
{}

bool Inventory::Awake(pugi::xml_node& config)
{
	LOG("Loading Inventory");
	bool ret = true;

	return ret;
}

bool Inventory::Start()
{

	return true;
}

bool Inventory::PreUpdate()
{
	bool ret = true;

	if (app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN) {
		Disable();
	}

	return ret;
}

bool Inventory::Update(float dt)
{

	return true;
}

// Render bullshit
bool Inventory::PostUpdate()
{
	bool ret = true;

	return ret;
}

bool Inventory::CleanUp()
{
	LOG("Closing Inventory");

	return true;
}