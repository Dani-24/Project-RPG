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
#include "Camera.h"
#include "ModuleQFonts.h"
#include "Title.h"

#include <time.h>

#include "Defs.h"
#include "Log.h"

Battle::Battle(App* application, bool start_enabled) : Module(application, start_enabled)
{
	name.Create("battle");

	battlePause = false;
	playerBattleSprite = nullptr;
	townBackground = nullptr;
	dojoBackground = nullptr;
	battleStage = nullptr;
	targetEntity = nullptr;

	actualTurnEntity = nullptr;

	someoneAttacking = false;
	someoneDefending = false;
	itsPlayerTurn = false;
	canSelect = false;
	hasToShake = false;

	//Battle stages time
	//1000 - 2000 its ok
	attackTime = 1500;
	defenseTime = 1500;
	itemTime = 1500;
	escapeTime = 1500;

	winTime = 1500;
	loseTime = 1500;

	outcomeTime = 2000;

	//Battle shake time - 100 its ok
	shakeTime = 100;

	//Higher it is -> Less shake in screen - 500 its ok
	shakeForce = 500;


	defenseBuff = 5;


	//Dojoanim
	int w = 640, h = 489;
	for (int i = 0; i < 6; i++) {
		dojoAnim.PushBack({ w * i, 0, w, h });
		
	}

	dojoAnim.speed = 0.01f;
	dojoAnim.loop = true;


	battlePhase = BattlePhase::THINKING;

}

Battle::~Battle()
{}

bool Battle::Awake()
{
	bool ret = true;
	
	return ret;
}

bool Battle::Start()
{
	app->scene->player->toggleGui = false;

	battlePhase = BattlePhase::THINKING;
	hasStarted = false;
	hasTriedToEscape = false;
	canEscape = false;
	gameOver = false;
	hasToShake = false;
	damageTaken = 0;
	shakePos = 0;
	changeSide = 0;
	cont = 0;
	battleTurn = 0;
	turnValue = 321.123f;
	LOG("Loading Battle");
	
	battleStage = &app->stages->actualStage;

	switch (*battleStage) {
	case StageIndex::NONE:
		break;
	case StageIndex::TOWN:
		townBackground = app->tex->Load("Assets/textures/forest_big.png");
		dojoBackground = app->tex->Load("Assets/textures/dojo3.png");
		break;
	default:
		break;
	}

	//Load GUI textures
	attackTex = app->tex->Load("Assets/gui/attack.png");
	defenseTex = app->tex->Load("Assets/gui/defense.png");
	itemsTex = app->tex->Load("Assets/gui/items.png");
	escapeTex = app->tex->Load("Assets/gui/escape.png");

	app->map->RemoveCol();
	app->stages->onBattle = true;
	
	//Saving player State before battle
	//Position
	app->stages->playerPtr->mapPosition = app->stages->playerPtr->position;
	app->stages->playerPtr->position = app->stages->playerPtr->battlePosition;

	//Animation
	app->stages->playerPtr->mapAnimation = app->stages->playerPtr->currentAnimation;
	if(app->stages->playerPtr->PlayerErection == true)
	{
		app->stages->playerPtr->currentAnimation = &app->stages->playerPtr->idleBattleM;
	}
	if (app->stages->playerPtr->PlayerErection == false)
	{
		app->stages->playerPtr->currentAnimation = &app->stages->playerPtr->idleBattleF;
	}
	//app->stages->playerPtr->currentAnimation->currentFrame = 1.0f;
	
	app->stages->playerPtr->canMove = false;


	//Enemies
	entitiesInBattle[4]->mapPosition = entitiesInBattle[4]->position;
	entitiesInBattle[4]->position = { 500, 100 };
	entitiesInBattle[4]->mapAnimation = entitiesInBattle[4]->currentAnimation;


	for (int i = 0; i < 8; i++) {
		if (entitiesInBattle[i] != nullptr) {
			if (entitiesInBattle[i]->isAlive == true) {
				entitiesInBattle[i]->stats->localTurn = 1;
			}
		}
		
	}

	app->camera->SetPos({ 0, 0 });
	
	//GUI
	attackButton = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 101, "Attack", { app->win->GetWidth()/2/2 - (74*4 + 50*3) /2  , app->win->GetHeight() / 2 - 50 , 74, 32 }, this);
	defenseButton = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 102, "Defense", { app->win->GetWidth() / 2 / 2 - (74 * 4 + 50 * 3) / 2 + 74 + 50 ,app->win->GetHeight() / 2 - 50 , 74, 32 }, this);
	itemButton = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 103, "Item", { app->win->GetWidth() / 2 / 2 - (74 * 4 + 50 * 3) / 2  + 74*2 +50*2,app->win->GetHeight() / 2 - 50 , 74, 32 }, this);
	escapeButton = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 104, "Escape", { app->win->GetWidth() / 2 / 2 - (74 * 4 + 50 * 3) / 2 + 74*3 + 50*3, app->win->GetHeight() / 2 - 50 , 74, 32 }, this);

	SetTurnOrder();

	app->audio->PlayMusic("Assets/audio/music/music_battle.ogg");

	return true;
}



bool Battle::PreUpdate()
{
	bool ret = true;

	//CheckWinLose();
	

	return ret;
}

bool Battle::Update(float dt)
{	

	if (battlePause == false) {

		//if (app->input->GetKey(SDL_SCANCODE_H) == KEY_DOWN) {
			dojoAnim.Update(dt);
		//}
		//Player turn
		if (actualTurnEntity->dynamicType == DynamicType::CHARACTER) {

			switch (battlePhase) {
			case BattlePhase::THINKING:
				//Debuff if protected las turn
				if (actualTurnEntity->stats->defenseBuffed == true) {
					actualTurnEntity->stats->deffense -= defenseBuff;
					actualTurnEntity->stats->defenseBuffed = false;
				}
				canSelect = true;
				break;
			case BattlePhase::OUTCOME:
				if (cont < outcomeTime) {
					cont += dt;
				}
				//OUTCOME
				else {
					cont = 0;
					hasToShake = false;
					if (CheckWinLose() == true) {

					}
					else {
						SetTurnOrder();
						battleTurn++;
						battlePhase = BattlePhase::THINKING;
					}
				}
				break;
			case BattlePhase::ATTACKING:
				if (cont < attackTime) {
					cont += dt;
				}
				//ATTACK
				else {
					cont = 0;
					app->stages->pAnim = rand() % 3 + 1;
					app->stages->vAnim = rand() % 2 + 1;
					Attack(targetEntity);
					battlePhase = BattlePhase::OUTCOME;
					
				}
				break;
			case BattlePhase::DEFENDING:
				if (cont < defenseTime) {
					cont += dt;
				}
				//DEFENSE
				else {
					cont = 0;
					Defense();
					SetTurnOrder();
					battleTurn++;
					battlePhase = BattlePhase::THINKING;
				}
				break;
			case BattlePhase::USING_ITEM:
				if (cont < itemTime) {
					cont += dt;
				}
				//USING ITEM
				else {
					cont = 0;
					//UseItem();
					//actualTurnEntity = entitiesInBattle[4];
					//battleTurn++;
					battlePhase = BattlePhase::THINKING;
				}
				break;
			case BattlePhase::ESCAPING:
				//ESCAPING
				//1rst message (trying)
				if(cont < escapeTime) {
					cont += dt;
				}
				//Tries to escape
				else if (cont < escapeTime * 2 && hasTriedToEscape == false) {
					cont += dt;
					canEscape = Escape();
					hasTriedToEscape = true;
				}
				else if (cont < escapeTime * 2 && hasTriedToEscape == true) {
					cont += dt;
				}
				else if (cont < escapeTime * 3 && hasTriedToEscape == true) {
					cont = 0;
					if (canEscape == true) {
						//app->fade->DoFadeToBlack(this, (Module*)app->titleScene);
						this->Disable();
					}
					else {
						hasTriedToEscape = false;
						SetTurnOrder();
						battleTurn++;
						battlePhase = BattlePhase::THINKING;
					}
				}
				break;

			case BattlePhase::WIN:
				if (cont < winTime) {
					cont += dt;
				}
				//WINNING
				else {
					if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN) {
						//app->fade->DoFadeToBlack(this, (Module*)app->titleScene);
						this->Disable();
					}
				}
				break;

			case BattlePhase::LOSE:
				if (cont < loseTime) {
					cont += dt;
				}
				//LOSING
				else {
					if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN) {
						//app->fade->DoFadeToBlack(this, (Module*)app->titleScene);
						this->Disable();
					}
				}
				break;
			}

		}
		//Enemy turn
		else if (actualTurnEntity->dynamicType == DynamicType::ENEMY) {
			switch (battlePhase) {
			case BattlePhase::THINKING:
				
				//Debuff if protected las turn
				if (actualTurnEntity->stats->defenseBuffed == true) {
					actualTurnEntity->stats->deffense -= defenseBuff;
					actualTurnEntity->stats->defenseBuffed = false;
				}
				optionPercent = 0;
				srand(time(NULL));
				optionPercent = (rand() % (100 - 0)) + 0;
				//If the enemy is NOT afraid
				if (actualTurnEntity->stats->health >= actualTurnEntity->stats->maxHealth / 2) {
					if (optionPercent < 70) {
						battlePhase = BattlePhase::ATTACKING;
						int targetNum = (rand() % CountAllies());
						targetEntity = entitiesInBattle[targetNum];
					}
					else {
						battlePhase = BattlePhase::DEFENDING;
					}

				}
				//If the enemy IS afraid
				else {
					if (optionPercent < 60) {
						battlePhase = BattlePhase::ATTACKING;
						int targetNum = (rand() % CountAllies());
						targetEntity = entitiesInBattle[targetNum];
					}
					else if(optionPercent < 85) {
						battlePhase = BattlePhase::DEFENDING;
					}
					else {
						battlePhase = BattlePhase::ESCAPING;
					}
				}
				
				break;
			case BattlePhase::OUTCOME:
				if (cont < outcomeTime) {
					cont += dt;
				}
				//OUTCOME
				else {
					cont = 0;
					hasToShake = false;
					if (CheckWinLose() == true) {

					}
					else {
						SetTurnOrder();
						battleTurn++;
						battlePhase = BattlePhase::THINKING;
					}
				}
				break;
			case BattlePhase::ATTACKING:
				if (cont < attackTime) {
					cont += dt;
				}
				
				//ATTACK
				else {
					cont = 0;
					app->stages->eAnim = rand() % 3 + 1;
					Attack(targetEntity);
					battlePhase = BattlePhase::OUTCOME;

				}
				break;
			case BattlePhase::DEFENDING:
				if (cont < defenseTime) {
					cont += dt;
				}
				//DEFENSE
				else {
					cont = 0;
					Defense();
					SetTurnOrder();
					battleTurn++;
					battlePhase = BattlePhase::THINKING;
				}
				break;
			case BattlePhase::USING_ITEM:
				
				break;
			case BattlePhase::ESCAPING:
				//ESCAPING
				//1rst message (trying)
				if (cont < escapeTime) {
					cont += dt;
				}
				//Tries to escape
				else if (cont < escapeTime * 2 && hasTriedToEscape == false) {
					cont += dt;
					canEscape = Escape();
					hasTriedToEscape = true;
				}
				else if (cont < escapeTime * 2 && hasTriedToEscape == true) {
					cont += dt;
				}
				else if (cont < escapeTime * 3 && hasTriedToEscape == true) {
					cont = 0;
					if (canEscape == true) {
						//app->fade->DoFadeToBlack(this, (Module*)app->titleScene);
						this->Disable();
					}
					else {
						hasTriedToEscape = false;
						actualTurnEntity = entitiesInBattle[0];
						battleTurn++;
						battlePhase = BattlePhase::THINKING;
					}
				}
				break;

			case BattlePhase::WIN:
				if (cont < winTime) {
					cont += dt;
				}
				//WINNING
				else {
					if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN) {
						//app->fade->DoFadeToBlack(this, (Module*)app->titleScene);
						this->Disable();
					}
				}
				break;

			case BattlePhase::LOSE:
				if (cont < loseTime) {
					cont += dt;
				}
				//LOSING
				else {
					if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN) {
						//app->fade->DoFadeToBlack(this, (Module*)app->titleScene);
						this->Disable();
					}
				}
				break;
			}

		}
		
			
		
		if (app->stages->actualStage!=StageIndex::NONE) {
			app->stages->playerPtr->currentAnimation->Update(dt);
		}
		
	}

	/*if (gameOver == true) {
		if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN) {
			app->fade->DoFadeToBlack(this, (Module*)app->titleScene);
		}

	}*/
	if (battleStage != nullptr) {
		switch (*battleStage) {
		case StageIndex::NONE:
			break;
		case StageIndex::TOWN:
			//app->render->DrawTexture(townBackground, -200, -250);
			if (hasToShake == false) {
				app->render->DrawTexture(dojoBackground, 0, 0, &dojoAnim.GetCurrentFrame());
				changeSide = 0;
			}
			else {

				if (shakePos > shakeTime * damageTaken) {
					hasToShake = false;
				}

				if (shakePos < -shakeTime * damageTaken) {
					hasToShake = false;
				}

				if (shakePos == 0) {
					shakePos += dt;
					changeSide += dt;
					app->render->DrawTexture(dojoBackground, (int)shakePos / (shakeForce / damageTaken), 0, &dojoAnim.GetCurrentFrame());
				}
				else if (shakePos > 0) {
					shakePos += dt;
					changeSide += dt;
					if (changeSide >= 50) {
						changeSide = 0;
						shakePos = shakePos * -1;
					}
					app->render->DrawTexture(dojoBackground, (int)shakePos / (shakeForce / damageTaken), 0, &dojoAnim.GetCurrentFrame());
				}
				else if (shakePos < 0) {
					shakePos -= dt;
					changeSide += dt;
					if (changeSide >= 50) {
						changeSide = 0;
						shakePos = shakePos * -1;
					}
					app->render->DrawTexture(dojoBackground, (int)shakePos / (shakeForce * damageTaken), 0, &dojoAnim.GetCurrentFrame());
				}
				
			}

			break;
		default:
			break;
		}
	}

	return true;
}

// Render bullshit
bool Battle::PostUpdate()
{
	bool ret = true;
	
	app->render->DrawRectangle({app->camera->GetPos().x,app->camera->GetPos().y,app->win->GetWidth()/2,80 }, 0, 0, 0, 200);
	app->render->DrawRectangle({app->camera->GetPos().x,app->camera->GetPos().y + app->win->GetHeight()/2 - 120 ,app->win->GetWidth(),125 }, 0, 0, 0, 200);


		
		//app->map->Draw();
		//app->guiManager->Draw();

		//PRINT THE PLAYER
		/*SDL_Rect rect = player->currentAnimation->GetCurrentFrame();
		if (player->PlayerErection == true) {
			app->render->DrawTexture(player->PlayerMTex, player->position.x, player->position.y, &rect);
		}
		if (player->PlayerErection == false) {
			app->render->DrawTexture(player->PlayerFTex, player->position.x, player->position.y, &rect);
		}*/
	//}

	if (battleTurn > 99) {
		battleTurn = 99;
	}

	//Print battle Turn
	sprintf_s(battleTurnChar, 9, "Turn: %02d", battleTurn);
	app->font->DrawText(battleTurnChar, app->win->GetWidth() / 2 - 100, 15);

	//Print turn value (depending on entities speed)
	/*sprintf_s(turnValueChar, 20, "Turn Value: %.2f", turnValue);

	if (actualTurnEntity->dynamicType == DynamicType::CHARACTER) {
		app->font->DrawText(turnValueChar, 50, app->win->GetHeight() / 2 - 30);
	}
	else if (actualTurnEntity->dynamicType == DynamicType::ENEMY) {
		app->font->DrawText(turnValueChar, app->win->GetWidth() / 2 - 200, app->win->GetHeight() / 2 - 30);
	}*/

	if (turnsTimeLine[0]!=nullptr && turnsTimeLine[1] != nullptr && turnsTimeLine[2] != nullptr &&  turnsTimeLine[3] != nullptr && turnsTimeLine[4] != nullptr) {
		sprintf_s(nameChar, 100, "%s -> %s -> %s -> %s -> %s", turnsTimeLine[0]->name, turnsTimeLine[1]->name, turnsTimeLine[2]->name, turnsTimeLine[3]->name, turnsTimeLine[4]->name);
		app->font->DrawText(nameChar, 50, 15);
	}

	
	
	//Print battle messages
	switch (battlePhase) {
		case BattlePhase::THINKING:
			if (actualTurnEntity->dynamicType == DynamicType::CHARACTER) {
				sprintf_s(nameChar, 50, "It's %s's turn", actualTurnEntity->name);
				app->font->DrawText(nameChar, 50,50);
			}
			break;

		case BattlePhase::SELECTING:
			app->font->DrawText("Select a target", 50 , 50);
			break;
		case BattlePhase::OUTCOME:
			sprintf_s(nameChar, 100, "%s takes %i points of damage!", targetEntity->name, damageTaken);
			app->font->DrawText(nameChar, 50 , 50);
			break;
		case BattlePhase::ATTACKING:
			sprintf_s(nameChar, 100, "%s is attacking %s!", actualTurnEntity->name, targetEntity->name);
			app->font->DrawText(nameChar, 50 , 50);
			break;

		case BattlePhase::DEFENDING:
			sprintf_s(nameChar, 50, "%s is protected!", actualTurnEntity->name);
			app->font->DrawText(nameChar, 50,  50);
			break;

		case BattlePhase::USING_ITEM:
			app->font->DrawText("You have no items left!", 50, 50);
			break;

		case BattlePhase::ESCAPING:
			if (hasTriedToEscape == false) {
				sprintf_s(nameChar, 50, "%s is trying to escape...", actualTurnEntity->name);
				app->font->DrawText(nameChar, 50, 50);
			}
			else if (canEscape == false){
				sprintf_s(nameChar, 50, "%s could not escape!", actualTurnEntity->name);
				app->font->DrawText(nameChar, 50, 50);
			}
			else if (canEscape == true) {
				sprintf_s(nameChar, 50, "%s could escape successfully!", actualTurnEntity->name);
				app->font->DrawText(nameChar, 50, 50);
			}
			
			break;

			
		case BattlePhase::WIN:
				app->font->DrawText("Victory! Press SPACE to continue", 50, 50);
			break;
		case BattlePhase::LOSE:
				app->font->DrawText("Game over! Press SPACE to go back to title", 50, 50);
			break;
	}

	sprintf_s(nameChar, 50, "%s's health: %2d", entitiesInBattle[0]->name ,entitiesInBattle[0]->stats->health);
	app->font->DrawText(nameChar, 50, app->win->GetHeight() / 2 - 115);

	if (entitiesInBattle[1] != nullptr) {
		sprintf_s(nameChar, 50, "%s's health: %2d", entitiesInBattle[1]->name, entitiesInBattle[1]->stats->health);
		app->font->DrawText(nameChar, 50, app->win->GetHeight() / 2 - 85);
	}
	
	sprintf_s(nameChar, 50, "Enemy health: %2d", entitiesInBattle[4]->stats->health);
	app->font->DrawText(nameChar, app->win->GetWidth() / 2 - 200, app->win->GetHeight() / 2 - 120);
	

	app->render->DrawTexture(attackTex, app->win->GetWidth() / 2 / 2 - (74 * 4 + 50 * 3) / 2  , app->win->GetHeight() / 2 - 50);
	app->render->DrawTexture(defenseTex, app->win->GetWidth() / 2 / 2 - (74 * 4 + 50 * 3) / 2 + 74 + 50, app->win->GetHeight() / 2 - 50);
	app->render->DrawTexture(itemsTex, app->win->GetWidth() / 2 / 2 - (74 * 4 + 50 * 3) / 2 + 74 * 2 + 50 * 2, app->win->GetHeight() / 2 - 50);
	app->render->DrawTexture(escapeTex, app->win->GetWidth() / 2 / 2 - (74 * 4 + 50 * 3) / 2 + 74 * 3 + 50 * 3, app->win->GetHeight() / 2 - 50);


	return ret;
}


bool Battle::OnGuiMouseClickEvent(GuiControl* control)
{
	if (canSelect == true && actualTurnEntity->isAlive == true && (
		actualTurnEntity == entitiesInBattle[0] || actualTurnEntity == entitiesInBattle[1] ||
		actualTurnEntity == entitiesInBattle[2] || actualTurnEntity == entitiesInBattle[3])) {

		switch (control->type)
		{
		case GuiControlType::BUTTON:

			switch (control->id) {
			case 101:
					targetEntity = entitiesInBattle[4];
					battlePhase = BattlePhase::ATTACKING;
					app->stages->fxbool = true;
					canSelect = false;
				
				break;
			case 102:
			
					battlePhase = BattlePhase::DEFENDING;
					app->stages->fxbool = true;
					canSelect = false;
				
				break;
			case 103:
			
					battlePhase = BattlePhase::USING_ITEM;
					app->stages->fxbool = true;
					canSelect = false;
			
				break;
			case 104:
			
					battlePhase = BattlePhase::ESCAPING;
					app->stages->fxbool = true;
					canSelect = false;
			
				break;
			}

			break;

			//Other cases here
		default:
			break;
		}
	}
		
	return true;
}

void Battle::SetTurnOrder() 
{
	//TURN ORDER: PLAYER - ENEMY
	//if (hasStarted == false) {

	//	if (entitiesInBattle[0]->stats->speed >= entitiesInBattle[4]->stats->speed) {
	//		actualTurnEntity = entitiesInBattle[0];
	//	}
	//	else {
	//		actualTurnEntity = entitiesInBattle[4];
	//	}

	//	hasStarted = true;
	//}
	//else {
	//	if (actualTurnEntity == entitiesInBattle[0]) {
	//		actualTurnEntity = entitiesInBattle[4];
	//		
	//	}
	//	else if (actualTurnEntity == entitiesInBattle[4]) {
	//		actualTurnEntity = entitiesInBattle[0];
	//	}
	//}

	//TURN ORDER: TURN VALUE
	//Set the minor turn value from all entities in battle

	if (hasStarted == false) {
		for (int h = 0; h < 5; h++) {
			turnValue = 0.0f;
			for (int i = 0; i < 8; i++) {
				if (entitiesInBattle[i] != nullptr) {
					if (entitiesInBattle[i]->isAlive == true) {
						if (turnValue == 0) {
							turnValue = entitiesInBattle[i]->stats->TurnValue();
						}
						else if (entitiesInBattle[i]->stats->TurnValue() < turnValue)
						{
							turnValue = entitiesInBattle[i]->stats->TurnValue();
						}
					}
				}

			}

			//Compare if more than one entities have the same turn value
			DynamicEntity* equalTurnValue[8];

			int equalValues = 0;
			for (int j = 0; j < 8; j++) {
				if (entitiesInBattle[j] != nullptr) {
					if (entitiesInBattle[j]->isAlive == true) {
						if (entitiesInBattle[j]->stats->TurnValue() == turnValue) {
							equalTurnValue[equalValues] = entitiesInBattle[j];
							equalValues++;
						}
					}
				}
			}

			//Choose a random one and set turn
			if (equalValues > 1) {
				srand(time(NULL));
				int chosenValue = (rand() % equalValues);

				turnsTimeLine[h] = equalTurnValue[chosenValue];
				equalTurnValue[chosenValue]->stats->localTurn++;
			}
			else {
				turnsTimeLine[h] = equalTurnValue[0];
				equalTurnValue[0]->stats->localTurn++;
			}

		}

		actualTurnEntity = turnsTimeLine[0];

		hasStarted = true;
	}
	else {
		turnValue = 0.0f;
		for (int i = 0; i < 8; i++) {
			if (entitiesInBattle[i] != nullptr) {
				if (entitiesInBattle[i]->isAlive == true) {
					if (turnValue == 0) {
						turnValue = entitiesInBattle[i]->stats->TurnValue();
					}
					else if (entitiesInBattle[i]->stats->TurnValue() < turnValue)
					{
						turnValue = entitiesInBattle[i]->stats->TurnValue();
					}
				}
			}

		}

		//Compare if more than one entities have the same turn value
		DynamicEntity* equalTurnValue[8];

		int equalValues = 0;
		for (int j = 0; j < 8; j++) {
			if (entitiesInBattle[j] != nullptr) {
				if (entitiesInBattle[j]->isAlive == true) {
					if (entitiesInBattle[j]->stats->TurnValue() == turnValue) {
						equalTurnValue[equalValues] = entitiesInBattle[j];
						equalValues++;
					}
				}
			}
		}

		turnsTimeLine[0] = turnsTimeLine[1];
		turnsTimeLine[1] = turnsTimeLine[2];
		turnsTimeLine[2] = turnsTimeLine[3];
		turnsTimeLine[3] = turnsTimeLine[4];
		

		//Choose a random one and set turn
		if (equalValues > 1) {
			srand(time(NULL));
			int chosenValue = (rand() % equalValues);

			turnsTimeLine[4] = equalTurnValue[chosenValue];
			turnsTimeLine[4]->stats->localTurn++;
		}
		else {
			turnsTimeLine[4] = equalTurnValue[0];
			turnsTimeLine[4]->stats->localTurn++;
		}
		

		actualTurnEntity = turnsTimeLine[0];

	}
	


}

void Battle::Attack(DynamicEntity *target) {

	damageTaken = 0;

	if (target->stats->deffense  < actualTurnEntity->stats->attack) {
		damageTaken = actualTurnEntity->stats->attack - target->stats->deffense;
		target->stats->health = target->stats->health + target->stats->deffense - actualTurnEntity->stats->attack;
		hasToShake = true;
		shakePos = 0;
	}
	
	if (target->stats->health <= 0) {
		target->stats->health = 0;
		target->isAlive = false;
	}
}

void Battle::Defense() {
	actualTurnEntity->stats->deffense += defenseBuff;
	actualTurnEntity->stats->defenseBuffed = true;
}

void Battle::UseItem(DynamicEntity target) {
	
}

bool Battle::Escape() {

	bool ret;

	srand(time(NULL));
	int percent = (rand() % (100 - 0)) + 0;

	if (percent > 70) {
		ret = true;
	}
	else {
		ret = false;
	}
	
	return ret;
}

int Battle::CountAllies() {

	int allies = 0;

	for (int i = 0; i < 4; i++) {
		if (entitiesInBattle[i] != nullptr) {
			if (entitiesInBattle[i]->isAlive == true) {
				allies++;
			}
		}
	}

	return allies;
}

int Battle::CountEnemies() {

	int enemies = 0;

	for (int i = 4; i < 8; i++) {
		if (entitiesInBattle[i] != nullptr) {
			if (entitiesInBattle[i]->isAlive == true) {
				enemies++;
			}
		}
	}

	return enemies;
}


bool Battle::CheckWinLose() {

	bool ret = false;

	alliesCount = CountAllies();
	enemiesCount = CountEnemies();

	if (alliesCount <= 0) {
		battlePhase = BattlePhase::LOSE;
		ret = true;
	}
	else if (enemiesCount <= 0) {
		battlePhase = BattlePhase::WIN;
		ret = true;
	}

	return ret;
}

// Called before quitting
bool Battle::CleanUp()
{

	attackButton->state = GuiControlState::DISABLED;
	defenseButton->state = GuiControlState::DISABLED;
	itemButton->state = GuiControlState::DISABLED;
	escapeButton->state = GuiControlState::DISABLED;

	attackButton = nullptr;
	delete attackButton;

	defenseButton = nullptr;
	delete defenseButton;

	itemButton = nullptr;
	delete itemButton;

	escapeButton = nullptr;
	delete escapeButton;

	switch(battlePhase) {
	case BattlePhase::WIN:
		
		//Destroy enemy
		app->entities->DestroyEntity(entitiesInBattle[4]);
		app->scene->normalEnemyList.del(app->scene->normalEnemyList.At(app->scene->normalEnemyList.find((NormalEnemy*)entitiesInBattle[4])));

		//Take back player position
		app->stages->playerPtr->position = app->stages->playerPtr->mapPosition;
		app->camera->SetTarget(app->stages->playerPtr);
		app->camera->OnTarget();
		app->camera->SetLimits(640, 350, 4490, 4200);

		//Take back player animation
		app->stages->playerPtr->currentAnimation = app->stages->playerPtr->mapAnimation;

		app->stages->playerPtr->canMove = true;
		app->map->LoadCol();
		app->stages->onBattle = false;

		break;
	case BattlePhase::LOSE:
		
		//Destroy enemy
		app->entities->DestroyEntity(entitiesInBattle[4]);
		app->scene->normalEnemyList.del(app->scene->normalEnemyList.At(app->scene->normalEnemyList.find((NormalEnemy*)entitiesInBattle[4])));

		//Take back player position
		app->stages->playerPtr->position = app->stages->playerPtr->mapPosition;
		app->camera->SetTarget(app->stages->playerPtr);
		app->camera->OnTarget();
		app->camera->SetLimits(640, 350, 4490, 4200);

		//Take back player animation
		app->stages->playerPtr->currentAnimation = app->stages->playerPtr->mapAnimation;

		app->stages->onBattle = false;

		app->scene->Disable();
		app->titleScene->Enable();

		break;

	case BattlePhase::ESCAPING:
		if (actualTurnEntity->dynamicType == DynamicType::CHARACTER) {

			//Take back enemy position
			entitiesInBattle[4]->position = entitiesInBattle[4]->mapPosition;
			//Take back enemy animation
			entitiesInBattle[4]->currentAnimation = entitiesInBattle[4]->mapAnimation;


			//Take back player position
			app->stages->playerPtr->position = { app->stages->playerPtr->mapPosition.x ,entitiesInBattle[4]->baseCollider->rect.y + entitiesInBattle[4]->baseCollider->rect.h +1 - app->stages->playerPtr->colDownDistance };
			app->camera->SetTarget(app->stages->playerPtr);
			app->camera->OnTarget();
			app->camera->SetLimits(640, 350, 4490, 4200);

			//Take back player animation
			app->stages->playerPtr->currentAnimation = app->stages->playerPtr->mapAnimation;

			app->stages->playerPtr->canMove = true;
			app->map->LoadCol();
			app->stages->onBattle = false;

		}
		if (actualTurnEntity->dynamicType == DynamicType::ENEMY) {

			//Destroy enemy
			app->entities->DestroyEntity(entitiesInBattle[4]);
			app->scene->normalEnemyList.del(app->scene->normalEnemyList.At(app->scene->normalEnemyList.find((NormalEnemy*)entitiesInBattle[4])));

			//Take back player position
			app->stages->playerPtr->position = app->stages->playerPtr->mapPosition;
			app->camera->SetTarget(app->stages->playerPtr);
			app->camera->OnTarget();
			app->camera->SetLimits(640, 350, 4490, 4200);

			//Take back player animation
			app->stages->playerPtr->currentAnimation = app->stages->playerPtr->mapAnimation;

			app->stages->playerPtr->canMove = true;
			app->map->LoadCol();
			app->stages->onBattle = false;
		}

		break;
	}

	//app->entities->DestroyEntity(entitiesInBattle[app->scene->normalEnemyList.find((NormalEnemy*)entitiesInBattle[4])]);

	//Music

	switch (app->stages->actualStage) {
	case StageIndex::NONE:
		break;
	case StageIndex::TOWN:
		app->audio->PlayMusic("Assets/audio/music/music_town.ogg");
		break;
	case StageIndex::DOJO:
		app->audio->PlayMusic("Assets/audio/music/music_dojo.ogg");
		break;
	case StageIndex::SHOP:
		app->audio->PlayMusic("Assets/audio/music/music_shop.ogg");
		break;
	case StageIndex::SHOPSUB:
		app->audio->PlayMusic("Assets/audio/music/music_shopsub.ogg");
		break;
	case StageIndex::TAVERN:
		app->audio->PlayMusic("Assets/audio/music/music_tavern.ogg");
		break;
	}

	app->scene->player->toggleGui = true;

	return true;
}
