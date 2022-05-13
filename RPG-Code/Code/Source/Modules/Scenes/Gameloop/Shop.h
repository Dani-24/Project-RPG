#ifndef __SHOP_H__
#define __SHOP_H__

#include "Module.h"
#include "GuiButton.h"
#include "GuiManager.h"
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

	bool CleanUp();
private:
	SDL_Texture* ShopTex;


};

#endif // !__SHOP_H__