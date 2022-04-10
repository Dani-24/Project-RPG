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
#include "EnemyMovement.h"
#include "EntityManager.h"
#include "Battle.h"
#include "Stages.h"
#include "Cock.h"
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
		}


		break;

	}

	//PRINTS THE COCKS
	ListItem<NPC*>* npcInList;
	npcListPtr = app->scene->npcList;
	npcInList = npcListPtr.start;
	for (npcInList = npcListPtr.start; npcInList != NULL && ret == true; npcInList = npcInList->next)
	{
		if (npcInList->data->activeOnStage == app->stages->actualStage) {
			npcInList->data->spriteRect = npcInList->data->currentAnimation->GetCurrentFrame();
			app->render->DrawTexture(npcInList->data->spriteText, npcInList->data->position.x, npcInList->data->position.y, &npcInList->data->spriteRect);

		}
	}


	//PRINT THE BARKEEPER
	//PRINTS THE COCKS
	ListItem<NPC*>* npcInList;
	npcListPtr = app->scene->npcList;
	npcInList = npcListPtr.start;
	for (npcInList = npcListPtr.start; npcInList != NULL && ret == true; npcInList = npcInList->next)
	{
		if (npcInList->data->activeOnStage == app->stages->actualStage) {
			npcInList->data->spriteRect = npcInList->data->currentAnimation->GetCurrentFrame();
			app->render->DrawTexture(npcInList->data->spriteText, npcInList->data->position.x, npcInList->data->position.y, &npcInList->data->spriteRect);

		}
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
