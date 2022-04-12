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

	onBattle = false;

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
		
		if (onBattle == false) {

			app->map->Draw();
			app->guiManager->Draw();

			//Print skeletons
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

			app->map->ReDraw();
		}

		break;

	}

	//PRINTS THE COCKS
	if (npcListPtr != nullptr) {
		ListItem<NPC*>* npcInList;
		npcInList = npcListPtr->start;
		for (npcInList = npcListPtr->start; npcInList != NULL && ret == true; npcInList = npcInList->next)
		{
			if (npcInList->data->activeOnStage == app->stages->actualStage) {
				npcInList->data->spriteRect = npcInList->data->currentAnimation->GetCurrentFrame();
				app->render->DrawTexture(npcInList->data->spriteText, npcInList->data->position.x, npcInList->data->position.y, &npcInList->data->spriteRect);

			}
		}
	}
	
	//PRINTS THE BARKEEPER
	if (npcListPtr != nullptr) {
		ListItem<NPC*>* npcInList;
		npcInList = npcListPtr->start;
		for (npcInList = npcListPtr->start; npcInList != NULL && ret == true; npcInList = npcInList->next)
		{
			if (npcInList->data->activeOnStage == app->stages->actualStage) {
				npcInList->data->spriteRectB = npcInList->data->currentAnimation->GetCurrentFrame();
				app->render->DrawTexture(npcInList->data->spriteTextB, npcInList->data->position.x-100, npcInList->data->position.y+90, &npcInList->data->spriteRectB);


			}
		}
	}
	

	//PRINTS THE TRAINER
	if (npcListPtr != nullptr) {
		ListItem<NPC*>* npcInList;
		npcInList = npcListPtr->start;
		for (npcInList = npcListPtr->start; npcInList != NULL && ret == true; npcInList = npcInList->next)
		{
			if (npcInList->data->activeOnStage == app->stages->actualStage) {
				npcInList->data->spriteRectE = npcInList->data->currentAnimation->GetCurrentFrame();
				app->render->DrawTexture(npcInList->data->spriteTextE, npcInList->data->position.x+200, npcInList->data->position.y, &npcInList->data->spriteRectE);


			}
		}
	}


	//PRINTS THE MERCHANT
	if (npcListPtr != nullptr) {
		ListItem<NPC*>* npcInList;
		npcInList = npcListPtr->start;
		for (npcInList = npcListPtr->start; npcInList != NULL && ret == true; npcInList = npcInList->next)
		{
			if (npcInList->data->activeOnStage == app->stages->actualStage) {
				npcInList->data->spriteRectM = npcInList->data->currentAnimation->GetCurrentFrame();
				app->render->DrawTexture(npcInList->data->spriteTextM, npcInList->data->position.x+300, npcInList->data->position.y, &npcInList->data->spriteRectM);


			}
		}
	}
	return ret;
}

void Stages::ChangeStage(StageIndex newStage) {
	actualStage = newStage;

	switch (newStage)
	{
	case StageIndex::NONE:

		app->map->RemoveCol();

		playerPtr = nullptr;
		delete playerPtr;

		npcListPtr = nullptr;
		delete npcListPtr;
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
