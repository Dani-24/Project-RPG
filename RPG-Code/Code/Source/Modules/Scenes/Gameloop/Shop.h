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

};

#endif // !__SHOP_H__