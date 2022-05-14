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
#include "GuiManager.h"
#include "Camera.h"
#include "Defs.h"
#include "Log.h"
#include "GuiButton.h"
#include "Inventory.h"
#include "Scene.h"
#include "Configuration.h"

Shop::Shop(App* application, bool start_enabled) : Module(application, start_enabled)
{
	name.Create("shop");

	apple.PushBack({ 14,12,20,24 });
	life_potion.PushBack({ 60,538,24,30 });
	pie.PushBack({ 246,12,34,26 });
	delicious_pie.PushBack({ 342,54,34,32 });
	meat.PushBack({ 730,59,28,28 });
	egg.PushBack({300,110,24,22 });
}

Shop::~Shop()
{}

bool Shop::Awake(pugi::xml_node& config)
{
	LOG("Starting Shop");
	bool ret = true;

	return ret;

}

bool Shop::Start() {
	bool ret = true;

	ShopTex = app->tex->Load("Assets/gui/inventory/ui_shop.png");
	ItemTex = app->tex->Load("Assets/items/items2.png");
	//Buttons
	Section1Btn= (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 250, "section1", { 88,85, 167, 35 }, this);
	Section2Btn = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 251, "section2", { 88,138, 167, 35 }, this);
	Section3Btn = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 252, "section3", { 88,192, 167, 35 }, this);
	Section4Btn = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 253, "section4", { 88,245, 167, 35 }, this);
	Item1Btn = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 254, "item1", { 282, 99, 33, 33 }, this);
	Item2Btn = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 255, "item2", { 348, 99, 33, 33 }, this);
	Item3Btn = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 256, "item3", { 415, 99, 33, 33 }, this);
	Item4Btn = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 257, "item4", { 484, 99, 33, 33 }, this);
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

	switch (ShopSection) {
	case 1:

		break;
	case 2:

		break;
	case 3:

		break;
	case 4:

		break;

	default:
		break;
	}

	return ret;
}

bool Shop::PostUpdate() {
	bool ret = true;
	int y = -app->camera->GetPos().y / 2;
	int x = -app->camera->GetPos().x / 2;
	
	app->render->DrawTexture(ShopTex, x, y, 0);
	app->font->DrawText("Food", 135, 92, { 255,234,123 });
	app->font->DrawText("More Food", 100, 140, { 238,255,123 });
	
	switch (ShopSection) {
	case 1:
		app->render->DrawTexture(ItemTex, 288, 103, &apple.GetCurrentFrame());
		app->render->DrawTexture(ItemTex, 348, 103, &pie.GetCurrentFrame());
		app->render->DrawTexture(ItemTex, 416, 100, &delicious_pie.GetCurrentFrame());
		if (ShopItem == 1) {
			app->font->DrawText("Apple", 180, 20, { 255,255,255 });
		}
		if (ShopItem == 2) {
			app->font->DrawText("Pie", 180, 20, { 255,255,255 });
		}
		if (ShopItem == 3) {
			app->font->DrawText("Delicious", 170, 20, { 255,255,255 });
		}
		if (ShopItem == 4) {

		}
		break;
	case 2:
		app->render->DrawTexture(ItemTex, 290, 100, &life_potion.GetCurrentFrame());
		if (ShopItem == 13) {
			app->font->DrawText("Life Potion", 170, 20, { 255,255,255 });
		}
		if (ShopItem == 14) {

		}
		if (ShopItem == 15) {

		}
		if (ShopItem == 16) {

		}
		break;
	case 3:
		app->render->DrawTexture(ItemTex, 288, 100, &egg.GetCurrentFrame());
		app->render->DrawTexture(ItemTex, 354, 102, &meat.GetCurrentFrame());
		if (ShopItem == 25) {
			app->font->DrawText("Egg", 180, 20, { 255,255,255 });
		}
		if (ShopItem == 26) {
			app->font->DrawText("Meat", 180, 20, { 255,255,255 });
		}
		if (ShopItem == 27) {

		}
		if (ShopItem == 28) {

		}
		break;
	case 4:
		if (ShopItem == 37) {

		}
		if (ShopItem == 38) {

		}
		if (ShopItem == 39) {

		}
		if (ShopItem == 40) {

		}
		break;

	default:
		break;
	}
	return ret;
}

bool Shop::OnGuiMouseClickEvent(GuiControl* control) {
	switch (control->type)
	{
	case GuiControlType::BUTTON:
	{
		//Checks the GUI element ID
		if (control->id == 250)
		{
			LOG("Section 1");
			app->audio->PlayFx(app->conf->btnSelection);
			ShopSection = 1;
		}

		if (control->id == 251)
		{
			LOG("Section 2");
			app->audio->PlayFx(app->conf->btnSelection);
			ShopSection = 2;
		}
		if (control->id == 252)
		{
			LOG("Section 3");
			app->audio->PlayFx(app->conf->btnSelection);
			ShopSection = 3;
	
		}
		if (control->id == 253)
		{
			LOG("Section 4");
			app->audio->PlayFx(app->conf->btnSelection);
			ShopSection = 4;			
		}
		//---------------------------------------------//
		if (control->id == 254)
		{
			LOG("item 1");
			app->audio->PlayFx(app->conf->btnSelection);
			if (ShopSection == 1) {
				ShopItem = 1;
			}
			if (ShopSection == 2) {
				ShopItem = 13;
			}
			if (ShopSection == 3) {
				ShopItem = 25;
			}
			if (ShopSection == 4) {
				ShopItem = 37;
			}
		}
		if (control->id == 255)
		{
			LOG("item 2");
			app->audio->PlayFx(app->conf->btnSelection);
			if (ShopSection == 1) {
				ShopItem = 2;
			}
			if (ShopSection == 2) {
				ShopItem = 14;
			}
			if (ShopSection == 3) {
				ShopItem = 26;
			}
			if (ShopSection == 4) {
				ShopItem = 38;
			}
		}
		if (control->id == 256)
		{
			LOG("item 3");
			app->audio->PlayFx(app->conf->btnSelection);
			if (ShopSection == 1) {
				ShopItem = 3;
			}
			if (ShopSection == 2) {
				ShopItem = 15;
			}
			if (ShopSection == 3) {
				ShopItem = 27;
			}
			if (ShopSection == 4) {
				ShopItem = 38;
			}
		}
		if (control->id == 257)
		{
			LOG("item 4");
			app->audio->PlayFx(app->conf->btnSelection);
			if (ShopSection == 1) {
				ShopItem = 4;
			}
			if (ShopSection == 2) {
				ShopItem = 16;
			}
			if (ShopSection == 3) {
				ShopItem = 28;
			}
			if (ShopSection == 4) {
				ShopItem = 39;
			}
		}
	
	}
	//Other cases here

	default: break;
	}

	return true;
}

bool Shop::CleanUp() {
	bool ret = true;
	Section1Btn->state = GuiControlState::DISABLED;
	Section2Btn->state = GuiControlState::DISABLED;
	Section3Btn->state = GuiControlState::DISABLED;
	Section4Btn->state = GuiControlState::DISABLED;
	Item1Btn->state = GuiControlState::DISABLED;
	Item2Btn->state = GuiControlState::DISABLED;
	Item3Btn->state = GuiControlState::DISABLED;
	Item4Btn->state = GuiControlState::DISABLED;

	app->tex->UnLoad(ShopTex);
	app->tex->UnLoad(ItemTex);

	return ret;
}