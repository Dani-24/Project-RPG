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
#include "EntityClasses/Player.h"
#include "EnemyMovement.h"
#include "EntityManager.h"
#include "Battle.h"

#include "Defs.h"
#include "Log.h"

Battle::Battle(App* application, bool start_enabled) : Module(application, start_enabled)
{
	name.Create("battle");
}

Battle::~Battle()
{}

bool Battle::Awake()
{
	LOG("Loading Scene");
	bool ret = true;

	return ret;
}

bool Battle::Start()
{

	return true;
}

bool Battle::PreUpdate()
{
	bool ret = true;

	if (app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN) {
		if (battlePause == false) {
			battlePause = true;
		}
	}

	return ret;
}

bool Battle::Update(float dt)
{
	if (battlePause == false) {



	}



	return true;
}

// Render bullshit
bool Battle::PostUpdate()
{
	bool ret = true;

	//app->map->Draw();
	//app->guiManager->Draw();

	//PRINT THE PLAYER
	SDL_Rect rect = player->currentAnimation->GetCurrentFrame();
	if (player->PlayerErection == true) {
		app->render->DrawTexture(player->PlayerMTex, player->position.x, player->position.y, &rect);
	}
	if (player->PlayerErection == false) {
		app->render->DrawTexture(player->PlayerFTex, player->position.x, player->position.y, &rect);
	}

	return ret;
}


bool Battle::OnGuiMouseClickEvent(GuiControl* control)
{

	switch (control->type)
	{
	case GuiControlType::BUTTON:
	{
		//Checks the GUI element ID
		if (control->id == 1)
		{
			LOG("Click on button 1");
		}

		if (control->id == 2)
		{
			LOG("Click on button 2");
		}

	}
	//Other cases here

	default: break;
	}

	return true;
}

// Called before quitting
bool Battle::CleanUp()
{

	//app->tex->UnLoad(img);

	return true;
}
