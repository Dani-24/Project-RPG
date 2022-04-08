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
#include "Stages.h"

#include "Defs.h"
#include "Log.h"

Stages::Stages(App* application, bool start_enabled) : Module(application, start_enabled)
{
	name.Create("stages");

	actualStage = StageIndex::NONE;
	playerPtr = nullptr;

	pause = false;
}

Stages::~Stages()
{}

bool Stages::Awake()
{
	LOG("Loading Scene");
	bool ret = true;

	return ret;
}

bool Stages::Start()
{

	return true;
}

bool Stages::PreUpdate()
{
	bool ret = true;

	switch (actualStage)
	{
	case StageIndex::NONE:
		break;

	case StageIndex::TOWN:

		

		break;

	default:

		break;
	}

	return ret;
}

bool Stages::Update(float dt)
{
	switch (actualStage)
	{
	case StageIndex::NONE:
		break;

	case StageIndex::TOWN:

		break;

	default:

		break;
	}

	return true;
}

// Render bullshit
bool Stages::PostUpdate()
{
	bool ret = true;

	switch (actualStage)
	{
	case StageIndex::NONE:
		break;

	case StageIndex::TOWN:
		
		app->map->Draw();
		app->guiManager->Draw();

		/*for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 10; j++) {
				app->render->DrawTexture(img, i * 200, j * 200, &imgAnim.GetCurrentFrame());
			}
		}*/

		//PRINT THE PLAYER
		if (playerPtr != nullptr) {
			SDL_Rect rect = playerPtr->currentAnimation->GetCurrentFrame();
			if (playerPtr->PlayerErection == true) {
				app->render->DrawTexture(playerPtr->PlayerMTex, playerPtr->position.x, playerPtr->position.y, &rect);
			}
			if (playerPtr->PlayerErection == false) {
				app->render->DrawTexture(playerPtr->PlayerFTex, playerPtr->position.x, playerPtr->position.y, &rect);
			}
			//LOG("Player null = FALSE");
		}
		else {
			int a = 6;
			//LOG("Player null = TRUE");
		}
		
		int i = 7;

		break;

	}
	return ret;
}

void Stages::ChangeStage(StageIndex newStage) {
	actualStage = newStage;

	switch (newStage)
	{
	case StageIndex::NONE:

		break;

	case StageIndex::TOWN:

		//playerPtr = app->scene->player;

		break;
	default:

		break;
	}
}

// Called before quitting
bool Stages::CleanUp()
{

	return true;
}
