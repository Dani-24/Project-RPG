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
#include "EntityManager.h"
#include "Battle.h"
#include "Stages.h"
#include "Defs.h"
#include "Log.h"
#include "DynamicEntity.h"
#include "NPC.h"
#include "NormalEnemy.h"
#include "Camera.h"

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

bool Stages::Awake(pugi::xml_node& config)
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
	case StageIndex::DOJO:

		break;
	case StageIndex::SHOP:

		break;
	case StageIndex::SHOPSUB:

		break;
	case StageIndex::TAVERN:

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
	case StageIndex::DOJO:

		break;
	case StageIndex::SHOP:

		break;
	case StageIndex::SHOPSUB:

		break;
	case StageIndex::TAVERN:

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

		break;
	case StageIndex::DOJO:

		break;
	case StageIndex::SHOP:

		break;
	case StageIndex::SHOPSUB:

		break;
	case StageIndex::TAVERN:

		break;
	}

	// Si me pones este if solo dentro de town el resto de mapas no se me imprimen :( -> Fixeado con el actualStage != NONE
	//oka doka
	if (onBattle == false && actualStage != StageIndex::NONE) {

		app->map->Draw();
		app->guiManager->Draw();



		if (playerPtr != nullptr) {
			//PRINT THE NPCs BELOW THE PLAYER
			if (npcListPtr != nullptr) {
				ListItem<NPC*>* npcInList;
				npcInList = npcListPtr->start;
				for (npcInList = npcListPtr->start; npcInList != NULL && ret == true; npcInList = npcInList->next)
				{
					if (npcInList->data->activeOnStage == app->stages->actualStage && playerPtr != nullptr) {
						
						if (npcInList->data->position.y + npcInList->data->currentAnimation->GetCurrentFrame().h <= playerPtr->position.y + playerPtr->currentAnimation->GetCurrentFrame().h) {
							npcInList->data->spriteRect = npcInList->data->currentAnimation->GetCurrentFrame();
							app->render->DrawTexture(npcInList->data->spriteText, npcInList->data->position.x, npcInList->data->position.y, &npcInList->data->spriteRect);
						}
					}
				}
			}

			//PRINT THE Enemies BELOW THE PLAYER
			if (normalEnemyListPtr != nullptr) {
				ListItem<NormalEnemy*>* NormalEnemyInList;
				NormalEnemyInList = normalEnemyListPtr->start;
				for (NormalEnemyInList = normalEnemyListPtr->start; NormalEnemyInList != NULL && ret == true; NormalEnemyInList = NormalEnemyInList->next)
				{
					if (NormalEnemyInList->data->activeOnStage == app->stages->actualStage && playerPtr != nullptr) {
						if (NormalEnemyInList->data->position.y + NormalEnemyInList->data->currentAnimation->GetCurrentFrame().h <= playerPtr->position.y + playerPtr->currentAnimation->GetCurrentFrame().h) {
							NormalEnemyInList->data->spriteRect = NormalEnemyInList->data->currentAnimation->GetCurrentFrame();
							app->render->DrawTexture(NormalEnemyInList->data->spriteText, NormalEnemyInList->data->position.x, NormalEnemyInList->data->position.y, &NormalEnemyInList->data->spriteRect);
						}
					}
				}
			}


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

			//PRINT THE NPCs ABOVE THE PLAYER
			if (npcListPtr != nullptr) {
				ListItem<NPC*>* npcInList;
				npcInList = npcListPtr->start;
				for (npcInList = npcListPtr->start; npcInList != NULL && ret == true; npcInList = npcInList->next)
				{
					if (npcInList->data->activeOnStage == app->stages->actualStage && playerPtr != nullptr) {
						if (npcInList->data->position.y + npcInList->data->currentAnimation->GetCurrentFrame().h > playerPtr->position.y + playerPtr->currentAnimation->GetCurrentFrame().h) {
							npcInList->data->spriteRect = npcInList->data->currentAnimation->GetCurrentFrame();
							app->render->DrawTexture(npcInList->data->spriteText, npcInList->data->position.x, npcInList->data->position.y, &npcInList->data->spriteRect);
						}
					}
				}
			}

			//PRINT THE Enemies ABOVE THE PLAYER
			if (normalEnemyListPtr != nullptr) {
				ListItem<NormalEnemy*>* NormalEnemyInList;
				NormalEnemyInList = normalEnemyListPtr->start;
				for (NormalEnemyInList = normalEnemyListPtr->start; NormalEnemyInList != NULL && ret == true; NormalEnemyInList = NormalEnemyInList->next)
				{
					if (NormalEnemyInList->data->activeOnStage == app->stages->actualStage && playerPtr != nullptr) {
						if (NormalEnemyInList->data->position.y + NormalEnemyInList->data->currentAnimation->GetCurrentFrame().h > playerPtr->position.y + playerPtr->currentAnimation->GetCurrentFrame().h) {
							NormalEnemyInList->data->spriteRect = NormalEnemyInList->data->currentAnimation->GetCurrentFrame();
							app->render->DrawTexture(NormalEnemyInList->data->spriteText, NormalEnemyInList->data->position.x, NormalEnemyInList->data->position.y, &NormalEnemyInList->data->spriteRect);
						}
					}
				}
			}
		}
		else {
			//PRINT ONLY THE NPCs
			if (npcListPtr != nullptr) {
				ListItem<NPC*>* npcInList;
				npcInList = npcListPtr->start;
				for (npcInList = npcListPtr->start; npcInList != NULL && ret == true; npcInList = npcInList->next)
				{
					if (npcInList->data->activeOnStage == app->stages->actualStage && playerPtr != nullptr) {
						npcInList->data->spriteRect = npcInList->data->currentAnimation->GetCurrentFrame();
						app->render->DrawTexture(npcInList->data->spriteText, npcInList->data->position.x, npcInList->data->position.y, &npcInList->data->spriteRect);
					}
				}
			}

			//PRINT ONLY THE Enemies
			if (normalEnemyListPtr != nullptr) {
				ListItem<NormalEnemy*>* NormalEnemyInList;
				NormalEnemyInList = normalEnemyListPtr->start;
				for (NormalEnemyInList = normalEnemyListPtr->start; NormalEnemyInList != NULL && ret == true; NormalEnemyInList = NormalEnemyInList->next)
				{
					if (NormalEnemyInList->data->activeOnStage == app->stages->actualStage && playerPtr != nullptr) {
						NormalEnemyInList->data->spriteRect = NormalEnemyInList->data->currentAnimation->GetCurrentFrame();
						app->render->DrawTexture(NormalEnemyInList->data->spriteText, NormalEnemyInList->data->position.x, NormalEnemyInList->data->position.y, &NormalEnemyInList->data->spriteRect);
					}
				}
			}
		}

		app->map->ReDraw();
	}

	//PRINT THE BATTLE SPRITES
	if (onBattle == true) {

		////PRINT THE PLAYER ON BATTLE
		//if (playerPtr != nullptr) {
		//	SDL_Rect rect = playerPtr->currentAnimation->GetCurrentFrame();
		//	if (playerPtr->PlayerErection == true) {
		//		app->render->DrawTexture(playerPtr->BattleMTex, playerPtr->position.x, playerPtr->position.y, &rect);
		//	}
		//	if (playerPtr->PlayerErection == false) {
		//		app->render->DrawTexture(playerPtr->BattleFTex, playerPtr->position.x, playerPtr->position.y, &rect);
		//	}
		//}

		//PRINT THE BATTLE ENTITIES
		

		for (int i = 0; i < 8; i++)
		{
			if (app->battle->entitiesInBattle[i] != nullptr) {

				//IF THEY ARE ENEMIES
				ListItem<NormalEnemy*>* NormalEnemyInList;

				for (NormalEnemyInList = normalEnemyListPtr->start; NormalEnemyInList != NULL && ret == true; NormalEnemyInList = NormalEnemyInList->next)
				{
					if (app->battle->entitiesInBattle[i] == NormalEnemyInList->data) {
						NormalEnemyInList->data->currentAnimation = &NormalEnemyInList->data->battleAnim;
						if (app->battle->actualTurnEntity->dynamicType == DynamicType::ENEMY) {
							switch (app->battle->battlePhase) {
							case BattlePhase::THINKING:
								NormalEnemyInList->data->currentAnimation = &NormalEnemyInList->data->battleAnim;
								break;
							case BattlePhase::ATTACKING:
								NormalEnemyInList->data->currentAnimation = &NormalEnemyInList->data->attackAnim;

								break;
							case BattlePhase::DEFENDING:
								NormalEnemyInList->data->currentAnimation = &NormalEnemyInList->data->protectAnim;
								break;
							case BattlePhase::LOSE:
								NormalEnemyInList->data->currentAnimation = &NormalEnemyInList->data->dieAnim;
								break;
							default:
								break;

							}
						}
						NormalEnemyInList->data->spriteRect = NormalEnemyInList->data->currentAnimation->GetCurrentFrame();
						if (NormalEnemyInList->data->normalEnemyType==NormalEnemyType::BAT) {
							app->render->DrawTexture(NormalEnemyInList->data->spriteText, NormalEnemyInList->data->position.x, NormalEnemyInList->data->position.y, &NormalEnemyInList->data->spriteRect, 3);
						}
						else {
							app->render->DrawTexture(NormalEnemyInList->data->spriteText, NormalEnemyInList->data->position.x, NormalEnemyInList->data->position.y, &NormalEnemyInList->data->spriteRect);
						}
						
					}
				}

				//IF THEY ARE ALLIES
				ListItem<Character*>* CharacterInList;

				for (CharacterInList = partyListPtr->start; CharacterInList != NULL && ret == true; CharacterInList = CharacterInList->next)
				{
					if (app->battle->entitiesInBattle[i] == CharacterInList->data) {

						if (i == 0)
						{
							SDL_Rect rect = playerPtr->currentAnimation->GetCurrentFrame();
							if (playerPtr->PlayerErection == true) {
								app->render->DrawTexture(playerPtr->BattleMTex, playerPtr->position.x, playerPtr->position.y, &rect, 2);
							}
							if (playerPtr->PlayerErection == false) {
								app->render->DrawTexture(playerPtr->BattleFTex, playerPtr->position.x, playerPtr->position.y, &rect, 2);
							}
						}
						else {
							//CharacterInList->data->currentAnimation = &CharacterInList->data->battleAnim;
							CharacterInList->data->spriteRect = CharacterInList->data->currentAnimation->GetCurrentFrame();
							app->render->DrawTexture(CharacterInList->data->spriteText, CharacterInList->data->position.x, CharacterInList->data->position.y, &CharacterInList->data->spriteRect);

						}
					}
				}
			}
		}
	
		
		//switch (app->battle->CurrentEnemyType) {
		//case EnemyInBattleType::NORMAL:
		//	app->battle->normalEnemyInBattle->currentAnimation = &app->battle->normalEnemyInBattle->battleAnim;
		//	SDL_Rect rect = app->battle->normalEnemyInBattle->currentAnimation->GetCurrentFrame();
		//	app->render->DrawTexture(app->battle->normalEnemyInBattle->spriteText, 500, 100, &rect);
		//	break;

		//default:
		//	break;
		//}
	}
	return ret;

}

void Stages::ChangeStage(StageIndex newStage) {
	actualStage = newStage;

	// Reset map.cpp
	if (app->map->isEnabled() == true) {
		app->map->Disable();
		app->map->Enable();
		app->camera->FreeLimits();
	}

	switch (newStage)
	{
	case StageIndex::NONE:

		playerPtr = nullptr;
		delete playerPtr;

		npcListPtr = nullptr;
		delete npcListPtr;
		break;

	case StageIndex::TOWN:

		// Load Map
		if (app->map->isEnabled() == true) {

			app->map->Load("initial_town_map.tmx");

			playerPtr->position = playerPtr->townPos;
			app->camera->OnTarget();
			app->camera->SetLimits(640, 350, 4490, 4200);
			LOG("Loading Town map");

			app->audio->PlayMusic("Assets/audio/music/music_town.ogg");
		}

		break;
	case StageIndex::DOJO:

		// Load Map
		if (app->map->isEnabled() == true) {
			app->map->Load("initial_town_dojo.tmx");

			playerPtr->position = { 415, 270 };
			app->camera->OnTarget();

			LOG("Loading Dojo map");

			app->audio->PlayMusic("Assets/audio/music/music_dojo.ogg");
		}

		break;
	case StageIndex::SHOP:

		// Load Map
		if (app->map->isEnabled() == true) {
			app->map->Load("initial_town_shop.tmx");

			if (playerPtr->shopPosOn == false) {
				playerPtr->position = { 255, 425 };
			}
			else {
				playerPtr->position = playerPtr->shopPos;
				playerPtr->shopPosOn = false;
			}
			app->camera->OnTarget();

			LOG("Loading Shop map");

			app->audio->PlayMusic("Assets/audio/music/music_shop.ogg");
		}

		break;
	case StageIndex::SHOPSUB:

		// Load Map
		if (app->map->isEnabled() == true) {
			app->map->Load("initial_town_under_shop.tmx");

			playerPtr->position = { 255, 80 };
			app->camera->OnTarget();

			LOG("Loading Shop lower floor map");

			app->audio->PlayMusic("Assets/audio/music/music_shop_underground.ogg");
		}

		break;
	case StageIndex::TAVERN:

		// Load Map
		if (app->map->isEnabled() == true) {
			app->map->Load("initial_town_tavern.tmx");

			playerPtr->position = { 240, 550 };
			app->camera->OnTarget();

			LOG("Loading Tavern map");

			app->audio->PlayMusic("Assets/audio/music/music_tavern.ogg");
		}

		break;
	default:

		break;
	}
}

// Called before quitting
bool Stages::CleanUp()
{
	playerPtr = nullptr;
	delete playerPtr;

	npcListPtr = nullptr;
	delete npcListPtr;

	normalEnemyListPtr = nullptr;
	delete normalEnemyListPtr;

	return true;
}
