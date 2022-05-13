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