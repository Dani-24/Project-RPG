#ifndef __SHOP_H__
#define __SHOP_H__

#include "Module.h"
#include "App.h"
#include "GuiButton.h"
#include "GuiManager.h"
#include "Animation.h"
#include "Camera.h"
struct SDL_Texture;


#pragma once
class Shop : public Module
{
public:
	Shop(App* application, bool start_enabled = true);

	virtual ~Shop();

	bool Awake(pugi::xml_node& config);

	// Called before the first frame
	bool Start();

	// Called before all Updates
	bool PreUpdate();

	// Called each loop iteration
	bool Update(float dt);

	// Called before all Updates
	bool PostUpdate();

	bool OnGuiMouseClickEvent(GuiControl* control);

	bool CleanUp();

	void CheckMoney(int Cash, int Price);

	void showPrice(int item, int x, int y);
private:
	SDL_Texture* ShopTex;

	SDL_Texture* ItemTex;

	Animation apple,
		life_potion,
		pie,
		delicious_pie,
		candy,
		meat,
		egg,
		fried_egg,
		hamburger,
		elixir,
		chest_key,
		door_key;

	int ShopSection = 1;
	int ShopItem = 0;


	int canBuy = 0;
	int price = 0;

	GuiButton* Section1Btn;
	GuiButton* Section2Btn;
	GuiButton* Section3Btn;
	GuiButton* Section4Btn;
	GuiButton* Item1Btn;
	GuiButton* Item2Btn;
	GuiButton* Item3Btn;
	GuiButton* Item4Btn;
	GuiButton* WantToBuy;
};

#endif // !__SHOP_H__