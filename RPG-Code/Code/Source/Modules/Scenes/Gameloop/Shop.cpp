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
#include "Item.h"

Shop::Shop(App* application, bool start_enabled) : Module(application, start_enabled)
{
	name.Create("shop");

	apple.PushBack({ 14,12,20,24 });
	life_potion.PushBack({ 60,538,24,30 });
	pie.PushBack({ 246,12,34,26 });
	delicious_pie.PushBack({ 342,54,34,32 });
	meat.PushBack({ 730,59,28,28 });
	egg.PushBack({542,12,20,22 });
	candy.PushBack({ 250,540,28,26 });
	fried_egg.PushBack({ 300,110,24,22 });
	hamburger.PushBack({ 60,108,22,26 });
	elixir.PushBack({ 208,538,16,30 });
	chest_key.PushBack({ 204,686,28,22 });
	door_key.PushBack({ 250,684,30,24 });
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
	int a = -app->camera->GetPos().y / 2 -9;
	int b = -app->camera->GetPos().x / 2+61;

	ShopTex = app->tex->Load("Assets/gui/inventory/ui_shop.png");
	ItemTex = app->tex->Load("Assets/items/items2.png");
	//Buttons
	Section1Btn= (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 250, "section1", { a + 88,b + 85, 167, 35 }, this);
	Section2Btn = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 251, "section2", { a + 88,b + 138, 167, 35 }, this);
	Section3Btn = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 252, "section3", { a + 88,b + 192, 167, 35 }, this);
	Section4Btn = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 253, "section4", { a + 88,b + 245, 167, 35 }, this);
	Item1Btn = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 254, "item1", { a + 282, b + 99, 33, 33 }, this);
	Item2Btn = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 255, "item2", { a + 348,b + 99, 33, 33 }, this);
	Item3Btn = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 256, "item3", { a + 415,b + 99, 33, 33 }, this);
	Item4Btn = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 257, "item4", { a + 484, b + 99, 33, 33 }, this);
	WantToBuy = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 258, "buy", { a + 400, b + 10, 80, 30 }, this);
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
	if (app->input->GetKey(SDL_SCANCODE_C) == KEY_DOWN) {
		Money += 10;
		LOG("%d", Money);
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
	int x = -app->camera->GetPos().x / 2+45;
	
	app->render->DrawTexture(ShopTex, x-45, y, 0);
	app->font->DrawText("Food", x+170, y+92, { 255,255,255 });
	app->font->DrawText("Potions", x + 147, y+142, { 255,255,255 });
	app->font->DrawText("Section 3", x + 147, y + 196, { 255,255,255 });
	app->font->DrawText("Section 4", x + 147, y + 248, { 255,255,255 });
	app->font->DrawText("Buy", x + 400, y + 8, { 255,255,255 });

	if (canBuy == true) {
		app->font->DrawText("Item added to inventory", x + 100, y + 260, { 255,255,255 });
	}
	if (canBuy == false) {
		app->font->DrawText("you have no money cabron", x + 100, y + 260, { 255,255,255 });
	}

	switch (ShopSection) {
	case 1:
		app->render->DrawTexture(ItemTex, x + 308, y + 103, &apple.GetCurrentFrame());
		app->render->DrawTexture(ItemTex, x + 368, y + 103, &pie.GetCurrentFrame());
		app->render->DrawTexture(ItemTex, x + 437, y + 96, &delicious_pie.GetCurrentFrame());
		if (ShopItem == 1) {
			app->font->DrawText("Apple", x + 204, y + 20, { 255,255,255 });
		}
		if (ShopItem == 2) {
			app->font->DrawText("Pie", x + 214, y + 20, { 255,255,255 });
		}
		if (ShopItem == 3) {
			app->font->DrawText("Delicious", x + 208, y + 20, { 255,255,255 });
		}
		if (ShopItem == 4) {

		}
		break;
	case 2:
		app->render->DrawTexture(ItemTex, x + 306, y + 100, &life_potion.GetCurrentFrame());
		app->render->DrawTexture(ItemTex, x + 371, y + 103, &elixir.GetCurrentFrame());
		if (ShopItem == 13) {
			app->font->DrawText("Life Potion", x + 172, y + 20, { 255,255,255 });
		}
		if (ShopItem == 14) {
			app->font->DrawText("Elixir", x + 204, y + 20, { 255,255,255 });
		}
		if (ShopItem == 15) {

		}
		if (ShopItem == 16) {

		}
		break;
	case 3:
		app->render->DrawTexture(ItemTex, x + 306, y + 103, &egg.GetCurrentFrame());
		app->render->DrawTexture(ItemTex, x + 437, y + 103, &fried_egg.GetCurrentFrame());
		app->render->DrawTexture(ItemTex, x + 370, y + 102, &meat.GetCurrentFrame());
		if (ShopItem == 25) {
			app->font->DrawText("Egg", x + 212, y + 20, { 255,255,255 });
		}
		if (ShopItem == 26) {
			app->font->DrawText("Meat", x + 210, y + 20, { 255,255,255 });
		}
		if (ShopItem == 27) {
			app->font->DrawText("Fried Egg", x + 205, y + 20, { 255,255,255 });
		}
		if (ShopItem == 28) {

		}
		break;
	case 4:
		app->render->DrawTexture(ItemTex, x + 306, y + 103, &chest_key.GetCurrentFrame());
		app->render->DrawTexture(ItemTex, x + 370, y + 103, &door_key.GetCurrentFrame());
		if (ShopItem == 37) {
			app->font->DrawText("Chest Key", x + 197, y + 20, { 255,255,255 });
		}
		if (ShopItem == 38) {
			app->font->DrawText("Door Key", x + 199, y + 20, { 255,255,255 });
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
		if (control->id == 258)
		{
			if (ShopItem == 1 || ShopItem == 2 || ShopItem == 25) {
				CheckMoney(Money, 20);
			}
			if (ShopItem == 36 || ShopItem == 3) {
				CheckMoney(Money, 30);
			}
			if (ShopItem == 37) {
				CheckMoney(Money, 40);
			}
			if (ShopItem == 13 || ShopItem == 38) {
				CheckMoney(Money, 50);
			}
			if (ShopItem == 14) {
				CheckMoney(Money, 80);
			}
			if (ShopItem == 37) {
				CheckMoney(Money, 100);
			}
			if (ShopItem == 38) {
				CheckMoney(Money, 200);
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
	WantToBuy->state = GuiControlState::DISABLED;

	app->tex->UnLoad(ShopTex);
	app->tex->UnLoad(ItemTex);

	return ret;
}

void Shop::CheckMoney(int Cash, int Price) {

	if (Cash - Price >= 0) {
		canBuy = true;
		Money -= Price;
	}
	else {
		canBuy = false;
	}
}