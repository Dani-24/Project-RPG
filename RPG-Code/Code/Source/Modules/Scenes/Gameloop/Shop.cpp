#include "Shop.h"
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
#include "GuiButton.h"
#include "Inventory.h"

Shop::Shop(App* application, bool start_enabled) : Module(application, start_enabled)
{
	name.Create("shop");
}

Shop::~Shop()
{

}

bool Shop::Awake(pugi::xml_node& config)
{
	LOG("Starting Shop");
	bool ret = true;

	return ret;

}

bool Shop::Start() {
	bool ret = true;

	ShopTex = app->tex->Load("Assets/gui/inventory/ui_shop.png");
	//app->scene->player->canMove = false;

	return ret;
}

bool Shop::PreUpdate() {
	bool ret = true;

	return ret;
}

bool Shop::Update(float dt) {
	bool ret = true;
	if (app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN && app->shop->isEnabled()==true)
	{
		app->shop->Disable();
	}

	return ret;
}

bool Shop::PostUpdate() {
	bool ret = true;
	int y = -app->camera->GetPos().y / 2;
	int x = -app->camera->GetPos().x / 2;
	
	app->render->DrawTexture(ShopTex, x, y, 0);
	return ret;
}

bool Shop::CleanUp() {
	bool ret = true;

	return ret;
}