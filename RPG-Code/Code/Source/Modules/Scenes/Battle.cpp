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
	hasChangedPhase = false;

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


	ChangePhase(BattlePhase::THINKING);

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

	// initial fx
	startFx = app->audio->LoadFx("Assets/audio/sfx/fx_battle.wav");
	app->audio->PlayFx(startFx);

	ChangePhase(BattlePhase::THINKING);
	hasStarted = false;
	hasTriedToEscape = false;
	canEscape = false;
	gameOver = false;
	hasToShake = false;
	hasChangedPhase = false;
	damageTaken = 0;
	shakePos = 0;
	changeSide = 0;
	cont = 0;
	battleTurn = 0;
	turnValue = 321.123f;
	LOG("Loading Battle");
	
	battleStage = &app->stages->actualStage;

	for (int i = 0; i < 8; i++) {
		if (entitiesInBattle[i] != nullptr) {
			if (entitiesInBattle[i]->hasStarted == false) {
				entitiesInBattle[i]->Start();
				entitiesInBattle[i]->hasStarted = true;

			}

			if (entitiesInBattle[i]->stats->defenseBuffed == true) {
				entitiesInBattle[i]->stats->defense -= defenseBuff;
				entitiesInBattle[i]->stats->defenseBuffed = false;
			}
			
		}
	}

	switch (*battleStage) {
	case StageIndex::NONE:
		break;
	case StageIndex::TOWN:
		townBackground = app->tex->Load("Assets/textures/forest_big.png");
		dojoBackground = app->tex->Load("Assets/textures/dojo3.png");
		break;
	case StageIndex::DOJO:
		townBackground = app->tex->Load("Assets/textures/forest_big.png");
		dojoBackground = app->tex->Load("Assets/textures/dojo3.png");
		break;
	default:
		break;
	}

	//Load GUI textures
	attackTex = app->tex->Load("Assets/gui/buttons/attack.png");
	defenseTex = app->tex->Load("Assets/gui/buttons/defense.png");
	itemsTex = app->tex->Load("Assets/gui/buttons/items.png");
	escapeTex = app->tex->Load("Assets/gui/buttons/escape.png");

	press_attackTex = app->tex->Load("Assets/gui/buttons/pressed_attack.png");
	press_defenseTex = app->tex->Load("Assets/gui/buttons/pressed_defense.png");
	press_itemsTex = app->tex->Load("Assets/gui/buttons/pressed_items.png");
	press_escapeTex = app->tex->Load("Assets/gui/buttons/pressed_escape.png");

	shield = app->tex->Load("Assets/textures/shield.png");

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
	entitiesInBattle[4]->position = { 500, 50 };
	entitiesInBattle[4]->mapAnimation = entitiesInBattle[4]->currentAnimation;

	entitiesInBattle[5]->mapPosition = entitiesInBattle[5]->position;
	entitiesInBattle[5]->position = { 550, 100 };
	entitiesInBattle[5]->mapAnimation = entitiesInBattle[5]->currentAnimation;


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

	enemyButton1 = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 105, "Enemy1", { app->win->GetWidth() / 2 / 2 - (74 * 4 + 50 * 3) / 2  , app->win->GetHeight() / 2 - 50 , 74, 32 }, this);
	enemyButton2 = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 106, "Enemy2", { app->win->GetWidth() / 2 / 2 - (74 * 4 + 50 * 3) / 2 + 74 + 50 ,app->win->GetHeight() / 2 - 50 , 74, 32 }, this);
	enemyButton3 = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 107, "Enemy3", { app->win->GetWidth() / 2 / 2 - (74 * 4 + 50 * 3) / 2 + 74 * 2 + 50 * 2,app->win->GetHeight() / 2 - 50 , 74, 32 }, this);
	enemyButton4 = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 108, "Enemy4", { app->win->GetWidth() / 2 / 2 - (74 * 4 + 50 * 3) / 2 + 74 * 3 + 50 * 3, app->win->GetHeight() / 2 - 50 , 74, 32 }, this);


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

			attackButton->state = GuiControlState::DISABLED;
			defenseButton->state = GuiControlState::DISABLED;
			itemButton->state = GuiControlState::DISABLED;
			escapeButton->state = GuiControlState::DISABLED;

			enemyButton1->state = GuiControlState::DISABLED;
			enemyButton2->state = GuiControlState::DISABLED;
			enemyButton3->state = GuiControlState::DISABLED;
			enemyButton4->state = GuiControlState::DISABLED;

		//Player turn
		if (actualTurnEntity->dynamicType == DynamicType::CHARACTER) {

			switch (battlePhase) {
			case BattlePhase::THINKING:
				//Debuff if protected las turn
				if (actualTurnEntity->stats->defenseBuffed == true) {
					actualTurnEntity->stats->defense -= defenseBuff;
					actualTurnEntity->stats->defenseBuffed = false;
				}
				attackButton->state = GuiControlState::NORMAL;
				defenseButton->state = GuiControlState::NORMAL;
				itemButton->state = GuiControlState::NORMAL;
				escapeButton->state = GuiControlState::NORMAL;
				canSelect = true;
				break;
			case BattlePhase::SELECTING:

				if (entitiesInBattle[4] != nullptr) {
					if (entitiesInBattle[4]->isAlive == true) {
						enemyButton1->state = GuiControlState::NORMAL;
					}
					
				}
				if (entitiesInBattle[5] != nullptr) {
					if (entitiesInBattle[5]->isAlive == true) {
						enemyButton2->state = GuiControlState::NORMAL;
					}
				}
				if (entitiesInBattle[6] != nullptr) {
					if (entitiesInBattle[6]->isAlive == true) {
						enemyButton3->state = GuiControlState::NORMAL;
					}
				}
				if (entitiesInBattle[7] != nullptr) {
					if (entitiesInBattle[7]->isAlive == true) {
						enemyButton4->state = GuiControlState::NORMAL;
					}
				}
				

				if (targetEntity != nullptr) {
					ChangePhase(BattlePhase::ATTACKING);
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
						ChangePhase(BattlePhase::THINKING);
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
					ChangePhase(BattlePhase::OUTCOME);
					
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
					ChangePhase(BattlePhase::THINKING);
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
					ChangePhase(BattlePhase::THINKING);
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
						ChangePhase(BattlePhase::THINKING);
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
					actualTurnEntity->stats->defense -= defenseBuff;
					actualTurnEntity->stats->defenseBuffed = false;
				}
				optionPercent = 0;
				srand(time(NULL));
				optionPercent = (rand() % (100 - 0)) + 0;
				//If the enemy is NOT afraid
				if (actualTurnEntity->stats->health >= actualTurnEntity->stats->maxHealth / 2) {
					if (optionPercent < 70) {
						
						int targetNum = (rand() % 2);
						while (entitiesInBattle[targetNum]->isAlive == false) {
							targetNum = (rand() % 2);
						}
						targetEntity = entitiesInBattle[targetNum];

						ChangePhase(BattlePhase::ATTACKING);
					}
					else {
						ChangePhase(BattlePhase::DEFENDING);
					}

				}
				//If the enemy IS afraid
				else {
					if (optionPercent < 60) {
						
						int targetNum = (rand() % 2);
						while (entitiesInBattle[targetNum]->isAlive == false) {
							targetNum = (rand() % 2);
						}
						targetEntity = entitiesInBattle[targetNum];
						ChangePhase(BattlePhase::ATTACKING);
					}
					else if(optionPercent < 85) {
						ChangePhase(BattlePhase::DEFENDING);
					}
					else {
						ChangePhase(BattlePhase::ESCAPING);
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
						ChangePhase(BattlePhase::THINKING);
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
					ChangePhase(BattlePhase::OUTCOME);

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
					ChangePhase(BattlePhase::THINKING);
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
						ChangePhase(BattlePhase::THINKING);
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
		case StageIndex::DOJO:
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

				int totalShake = shakeForce / damageTaken;
				if (totalShake < 1) {
					totalShake = 1;
				}

				if (shakePos == 0) {
					shakePos += dt;
					changeSide += dt;
					app->render->DrawTexture(dojoBackground, (int)shakePos / totalShake, 0, &dojoAnim.GetCurrentFrame());
				}
				else if (shakePos > 0) {
					shakePos += dt;
					changeSide += dt;
					if (changeSide >= 50) {
						changeSide = 0;
						shakePos = shakePos * -1;
					}
					app->render->DrawTexture(dojoBackground, (int)shakePos / totalShake, 0, &dojoAnim.GetCurrentFrame());
				}
				else if (shakePos < 0) {
					shakePos -= dt;
					changeSide += dt;
					if (changeSide >= 50) {
						changeSide = 0;
						shakePos = shakePos * -1;
					}
					app->render->DrawTexture(dojoBackground, (int)shakePos / totalShake
						, 0, &dojoAnim.GetCurrentFrame());
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
		sprintf_s(nameChar, 100, "              -> %s -> %s -> %s -> %s", turnsTimeLine[1]->name, turnsTimeLine[2]->name, turnsTimeLine[3]->name, turnsTimeLine[4]->name);
		app->font->DrawText(nameChar, 40, 15);
		sprintf_s(actualTurnChar, 100, "%s", turnsTimeLine[0]->name);
		app->font->DrawText(actualTurnChar, 40, 15, {150 ,150,255 });
	}

	
	
	//Print battle messages
	switch (battlePhase) {
		case BattlePhase::THINKING:
			if (hasChangedPhase == true) {
				app->font->CleanFonts();
				hasChangedPhase = false;
			}
			else if (actualTurnEntity->dynamicType == DynamicType::CHARACTER) {
				sprintf_s(battleInfoChar, 50, "It's %s's turn", actualTurnEntity->name);
				app->font->DrawTextDelayed(battleInfoChar, 50,50);

				attackButton->state != GuiControlState::PRESSED ? app->render->DrawTexture(attackTex, app->win->GetWidth() / 2 / 2 - (74 * 4 + 50 * 3) / 2, app->win->GetHeight() / 2 - 50) : app->render->DrawTexture(press_attackTex, app->win->GetWidth() / 2 / 2 - (74 * 4 + 50 * 3) / 2, app->win->GetHeight() / 2 - 50);
				defenseButton->state != GuiControlState::PRESSED ? app->render->DrawTexture(defenseTex, app->win->GetWidth() / 2 / 2 - (74 * 4 + 50 * 3) / 2 + 74 + 50, app->win->GetHeight() / 2 - 50) : app->render->DrawTexture(press_defenseTex, app->win->GetWidth() / 2 / 2 - (74 * 4 + 50 * 3) / 2 + 74 + 50, app->win->GetHeight() / 2 - 50);
				itemButton->state != GuiControlState::PRESSED ? app->render->DrawTexture(itemsTex, app->win->GetWidth() / 2 / 2 - (74 * 4 + 50 * 3) / 2 + 74 * 2 + 50 * 2, app->win->GetHeight() / 2 - 50) : app->render->DrawTexture(press_itemsTex, app->win->GetWidth() / 2 / 2 - (74 * 4 + 50 * 3) / 2 + 74 * 2 + 50 * 2, app->win->GetHeight() / 2 - 50);
				escapeButton->state != GuiControlState::PRESSED ? app->render->DrawTexture(escapeTex, app->win->GetWidth() / 2 / 2 - (74 * 4 + 50 * 3) / 2 + 74 * 3 + 50 * 3, app->win->GetHeight() / 2 - 50) : app->render->DrawTexture(press_escapeTex, app->win->GetWidth() / 2 / 2 - (74 * 4 + 50 * 3) / 2 + 74 * 3 + 50 * 3, app->win->GetHeight() / 2 - 50);

			}
			break;
			
			
		case BattlePhase::SELECTING:
			if (hasChangedPhase == true) {
				app->font->CleanFonts();
				hasChangedPhase = false;
			}
			else {
				app->font->DrawText("Select a target", 50, 50);

				if (entitiesInBattle[4] != nullptr) {
					if (entitiesInBattle[4]->isAlive == true) {
						enemyButton1->state != GuiControlState::PRESSED ? app->render->DrawTexture(attackTex, app->win->GetWidth() / 2 / 2 - (74 * 4 + 50 * 3) / 2, app->win->GetHeight() / 2 - 50) : app->render->DrawTexture(press_attackTex, app->win->GetWidth() / 2 / 2 - (74 * 4 + 50 * 3) / 2, app->win->GetHeight() / 2 - 50);
					}
				}
				if (entitiesInBattle[5] != nullptr) {
					if (entitiesInBattle[5]->isAlive == true) {
						enemyButton2->state != GuiControlState::PRESSED ? app->render->DrawTexture(defenseTex, app->win->GetWidth() / 2 / 2 - (74 * 4 + 50 * 3) / 2 + 74 + 50, app->win->GetHeight() / 2 - 50) : app->render->DrawTexture(press_defenseTex, app->win->GetWidth() / 2 / 2 - (74 * 4 + 50 * 3) / 2 + 74 + 50, app->win->GetHeight() / 2 - 50);
					}
				}
				if (entitiesInBattle[6] != nullptr) {
					if (entitiesInBattle[6]->isAlive == true) {
						enemyButton3->state != GuiControlState::PRESSED ? app->render->DrawTexture(itemsTex, app->win->GetWidth() / 2 / 2 - (74 * 4 + 50 * 3) / 2 + 74 * 2 + 50 * 2, app->win->GetHeight() / 2 - 50) : app->render->DrawTexture(press_itemsTex, app->win->GetWidth() / 2 / 2 - (74 * 4 + 50 * 3) / 2 + 74 * 2 + 50 * 2, app->win->GetHeight() / 2 - 50);
					}
				}
				if (entitiesInBattle[7] != nullptr) {
					if (entitiesInBattle[7]->isAlive == true) {
						enemyButton4->state != GuiControlState::PRESSED ? app->render->DrawTexture(escapeTex, app->win->GetWidth() / 2 / 2 - (74 * 4 + 50 * 3) / 2 + 74 * 3 + 50 * 3, app->win->GetHeight() / 2 - 50) : app->render->DrawTexture(press_escapeTex, app->win->GetWidth() / 2 / 2 - (74 * 4 + 50 * 3) / 2 + 74 * 3 + 50 * 3, app->win->GetHeight() / 2 - 50);
					}
				}
					
			}
			
			break;
		case BattlePhase::OUTCOME:
			if (hasChangedPhase == true) {
				app->font->CleanFonts();
				hasChangedPhase = false;
			}
			else {
				if (damageTaken == 1) {
					sprintf_s(nameChar, 100, "%s takes  1 ", targetEntity->name, damageTaken);
					app->font->DrawTextDelayed(nameChar, 50, 50, { 255,100,0 });
					sprintf_s(damageChar, 100, "%s takes    point of damage!", targetEntity->name, damageTaken);
					app->font->DrawTextDelayed(damageChar, 50, 50);
				}
				else {
					sprintf_s(nameChar, 100, "%s takes %i", targetEntity->name, damageTaken);
					app->font->DrawTextDelayed(nameChar, 50, 50, { 255,100,0 });
					sprintf_s(damageChar, 100, "%s takes     points of damage!", targetEntity->name, damageTaken);
					app->font->DrawTextDelayed(damageChar, 50, 50);
				}
				
			}
			break;
		case BattlePhase::ATTACKING:
			if (hasChangedPhase == true) {
				app->font->CleanFonts();
				hasChangedPhase = false;
			}
			else {
				sprintf_s(nameChar, 100, "%s is attacking %s!", actualTurnEntity->name, targetEntity->name);
				app->font->DrawTextDelayed(nameChar, 50, 50);
			}
			break;

		case BattlePhase::DEFENDING:
			if (hasChangedPhase == true) {
				app->font->CleanFonts();
				hasChangedPhase = false;
			}
			else {
				sprintf_s(nameChar, 50, "%s is protected!", actualTurnEntity->name);
				app->font->DrawTextDelayed(nameChar, 50, 50);
			}
			
			break;

		case BattlePhase::USING_ITEM:
			if (hasChangedPhase == true) {
				app->font->CleanFonts();
				hasChangedPhase = false;
			}
			else {
				app->font->DrawTextDelayed("You have no items left!", 50, 50);
			}
			break;

		case BattlePhase::ESCAPING:
			if (hasChangedPhase == true) {
				app->font->CleanFonts();
				hasChangedPhase = false;
			}
			else {
				if (hasTriedToEscape == false) {
					sprintf_s(nameChar, 50, "%s is trying to escape...", actualTurnEntity->name);
					app->font->DrawTextDelayed(nameChar, 50, 50);
				}
				else if (canEscape == false) {
					sprintf_s(escapeChar, 50, "%s could not escape!", actualTurnEntity->name);
					app->font->DrawTextDelayed(escapeChar, 50, 50);
				}
				else if (canEscape == true) {
					sprintf_s(escapeChar, 50, "%s could escape successfully!", actualTurnEntity->name);
					app->font->DrawTextDelayed(escapeChar, 50, 50);
				}
			}
			
			break;

			
		case BattlePhase::WIN:
			if (hasChangedPhase == true) {
				app->font->CleanFonts();
				hasChangedPhase = false;
			}
			else {
				app->font->DrawTextDelayed("Victory! Press SPACE to continue", 50, 50, { 255,200,0 });
				break;
			}
		case BattlePhase::LOSE:
			if (hasChangedPhase == true) {
				app->font->CleanFonts();
				hasChangedPhase = false;
			}
			else {
				app->font->DrawTextDelayed("Game over! Press SPACE to go back to title", 50, 50, { 255,30,10 });
			}
			break;
	}

	if (entitiesInBattle[0]->stats->health == 0) {
		sprintf_s(lifeChar, 50, "%s's health: %2d", entitiesInBattle[0]->name, entitiesInBattle[0]->stats->health);
		app->font->DrawText(lifeChar, 50, app->win->GetHeight() / 2 - 85, { 255,30,0 });
		sprintf_s(nameChar, 50, "%s's health:", entitiesInBattle[0]->name, entitiesInBattle[0]->stats->health);
		app->font->DrawText(nameChar, 50, app->win->GetHeight() / 2 - 85);


	}
	else if(entitiesInBattle[0]->stats->health <= 5) {

	
		sprintf_s(lifeChar, 50, "%s's health: %2d", entitiesInBattle[0]->name, entitiesInBattle[0]->stats->health);
		app->font->DrawText(lifeChar, 50, app->win->GetHeight() / 2 - 85, { 180,0,0 });
		sprintf_s(nameChar, 50, "%s's health:", entitiesInBattle[0]->name, entitiesInBattle[0]->stats->health);
		app->font->DrawText(nameChar, 50, app->win->GetHeight() / 2 - 85);
	}
	else {
		sprintf_s(lifeChar, 50, "%s's health: %2d", entitiesInBattle[0]->name, entitiesInBattle[0]->stats->health);
		app->font->DrawText(lifeChar, 50, app->win->GetHeight() / 2 - 85, { 100,255,0 });
		sprintf_s(nameChar, 50, "%s's health:", entitiesInBattle[0]->name, entitiesInBattle[0]->stats->health);
		app->font->DrawText(nameChar, 50, app->win->GetHeight() / 2 - 85);
		/*sprintf_s(nameChar, 50, "%s's health: %2d", entitiesInBattle[0]->name, entitiesInBattle[0]->stats->health);
		app->font->DrawText(nameChar, 50, app->win->GetHeight() / 2 - 115);*/
	}
	

	


	if (entitiesInBattle[1] != nullptr) {
		if (entitiesInBattle[1]->stats->health == 0) {

			sprintf_s(lifeChar, 50, "%s's health: %2d", entitiesInBattle[1]->name, entitiesInBattle[1]->stats->health);
			app->font->DrawText(lifeChar, 50, app->win->GetHeight() / 2 - 115, { 255,30,0 });
			sprintf_s(nameChar, 50, "%s's health:", entitiesInBattle[1]->name, entitiesInBattle[1]->stats->health);
			app->font->DrawText(nameChar, 50, app->win->GetHeight() / 2 - 115);

		}
		else if (entitiesInBattle[1]->stats->health <= 5) {

			sprintf_s(lifeChar, 50, "%s's health: %2d", entitiesInBattle[1]->name, entitiesInBattle[1]->stats->health);
			app->font->DrawText(lifeChar, 50, app->win->GetHeight() / 2 - 115, { 180,0,0 });
			sprintf_s(nameChar, 50, "%s's health:", entitiesInBattle[1]->name, entitiesInBattle[1]->stats->health);
			app->font->DrawText(nameChar, 50, app->win->GetHeight() / 2 - 115);

		}
		else {
			sprintf_s(lifeChar, 50, "%s's health: %2d", entitiesInBattle[1]->name, entitiesInBattle[1]->stats->health);
			app->font->DrawText(lifeChar, 50, app->win->GetHeight() / 2 - 115, { 100,255,0 });
			sprintf_s(nameChar, 50, "%s's health:", entitiesInBattle[1]->name, entitiesInBattle[1]->stats->health);
			app->font->DrawText(nameChar, 50, app->win->GetHeight() / 2 - 115);
		}
		/*sprintf_s(nameChar, 50, "%s's health: %2d", entitiesInBattle[1]->name, entitiesInBattle[1]->stats->health);
		app->font->DrawText(nameChar, 50, app->win->GetHeight() / 2 - 85);*/
	}
	
	if (entitiesInBattle[4] != nullptr) {

		if (entitiesInBattle[4]->stats->health == 0) {

			sprintf_s(lifeChar, 50, "%s's health: %2d", entitiesInBattle[4]->name, entitiesInBattle[4]->stats->health);
			app->font->DrawText(lifeChar, app->win->GetWidth() / 2 - 250, app->win->GetHeight() / 2 - 115, { 255,30,0 });
			sprintf_s(nameChar, 50, "%s's health:", entitiesInBattle[4]->name, entitiesInBattle[4]->stats->health);
			app->font->DrawText(nameChar, app->win->GetWidth() / 2 - 250, app->win->GetHeight() / 2 - 115);

		}
		else if (entitiesInBattle[4]->stats->health <= 5) {

			sprintf_s(lifeChar, 50, "%s's health: %2d", entitiesInBattle[4]->name, entitiesInBattle[4]->stats->health);
			app->font->DrawText(lifeChar, app->win->GetWidth() / 2 - 250, app->win->GetHeight() / 2 - 115, { 200,100,20 });
			sprintf_s(nameChar, 50, "%s's health:", entitiesInBattle[4]->name, entitiesInBattle[4]->stats->health);
			app->font->DrawText(nameChar, app->win->GetWidth() / 2 - 250, app->win->GetHeight() / 2 - 115);
		}
		else {
			sprintf_s(lifeChar, 50, "%s's health: %2d", entitiesInBattle[4]->name, entitiesInBattle[4]->stats->health);
			app->font->DrawText(lifeChar, app->win->GetWidth() / 2 - 250, app->win->GetHeight() / 2 - 115, { 100,255,0 });
			sprintf_s(nameChar, 50, "%s's health:", entitiesInBattle[4]->name, entitiesInBattle[4]->stats->health);
			app->font->DrawText(nameChar, app->win->GetWidth() / 2 - 250, app->win->GetHeight() / 2 - 115);
		}
		/*sprintf_s(nameChar, 50, "Enemy health: %2d", entitiesInBattle[4]->stats->health);
		app->font->DrawText(nameChar, app->win->GetWidth() / 2 - 200, app->win->GetHeight() / 2 - 120);*/
	}
	if (entitiesInBattle[5] != nullptr) {

		if (entitiesInBattle[5]->stats->health == 0) {

			sprintf_s(lifeChar, 50, "%s's health: %2d", entitiesInBattle[5]->name, entitiesInBattle[5]->stats->health);
			app->font->DrawText(lifeChar, app->win->GetWidth() / 2 - 250, app->win->GetHeight() / 2 - 85, { 255,30,0 });
			sprintf_s(nameChar, 50, "%s's health:", entitiesInBattle[5]->name, entitiesInBattle[5]->stats->health);
			app->font->DrawText(nameChar, app->win->GetWidth() / 2 - 250, app->win->GetHeight() / 2 - 85);

		}
		else if (entitiesInBattle[5]->stats->health <= 5) {

			sprintf_s(lifeChar, 50, "%s's health: %2d", entitiesInBattle[5]->name, entitiesInBattle[5]->stats->health);
			app->font->DrawText(lifeChar, app->win->GetWidth() / 2 - 250, app->win->GetHeight() / 2 - 85, { 200,100,20 });
			sprintf_s(nameChar, 50, "%s's health:", entitiesInBattle[5]->name, entitiesInBattle[5]->stats->health);
			app->font->DrawText(nameChar, app->win->GetWidth() / 2 - 250, app->win->GetHeight() / 2 - 85);
		}
		else {
			sprintf_s(lifeChar, 50, "%s's health: %2d", entitiesInBattle[5]->name, entitiesInBattle[5]->stats->health);
			app->font->DrawText(lifeChar, app->win->GetWidth() / 2 - 250, app->win->GetHeight() / 2 - 85, { 100,255,0 });
			sprintf_s(nameChar, 50, "%s's health:", entitiesInBattle[5]->name, entitiesInBattle[5]->stats->health);
			app->font->DrawText(nameChar, app->win->GetWidth() / 2 - 250, app->win->GetHeight() / 2 - 85);
		}
		/*sprintf_s(nameChar, 50, "Enemy health: %2d", entitiesInBattle[4]->stats->health);
		app->font->DrawText(nameChar, app->win->GetWidth() / 2 - 200, app->win->GetHeight() / 2 - 120);*/
	}

	
	
	

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
					targetEntity = nullptr;
					ChangePhase(BattlePhase::SELECTING);
					app->stages->fxbool = true;
					canSelect = false;
				
				break;
			case 102:
			
					ChangePhase(BattlePhase::DEFENDING);
					app->stages->fxbool = true;
					canSelect = false;
				
				break;
			case 103:
			
					ChangePhase(BattlePhase::USING_ITEM);
					app->stages->fxbool = true;
					canSelect = false;
			
				break;
			case 104:
			
					ChangePhase(BattlePhase::ESCAPING);
					app->stages->fxbool = true;
					canSelect = false;
			
				break;

			case 105:
				targetEntity = entitiesInBattle[4];
				app->stages->fxbool = true;
				canSelect = false;
				break;
			case 106:
				targetEntity = entitiesInBattle[5];
				app->stages->fxbool = true;
				canSelect = false;
				break;
			case 107:
				targetEntity = entitiesInBattle[6];
				app->stages->fxbool = true;
				canSelect = false;
				break;
			case 108:
				targetEntity = entitiesInBattle[7];
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

		bool noNull = true;

		for (int k = 0; k < 5; k++) {
			if(turnsTimeLine[k]==nullptr){


				noNull = false;
				//Choose a random one and set turn
				if (equalValues > 1) {
					srand(time(NULL));
					int chosenValue = (rand() % equalValues);

					turnsTimeLine[k] = equalTurnValue[chosenValue];
					turnsTimeLine[k]->stats->localTurn++;
				}
				else {
					turnsTimeLine[k] = equalTurnValue[0];
					turnsTimeLine[k]->stats->localTurn++;
				}

				//actualTurnEntity = turnsTimeLine[0];

				break;

			}
			
		}

		if (noNull == true) {
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
		}
		
		

		actualTurnEntity = turnsTimeLine[0];

	}
	


}

void Battle::Attack(DynamicEntity *target) {

	damageTaken = 0;

	if (target->stats->defense  < actualTurnEntity->stats->attack) {
		damageTaken = actualTurnEntity->stats->attack - target->stats->defense;
		target->stats->health = target->stats->health + target->stats->defense - actualTurnEntity->stats->attack;
		hasToShake = true;
		shakePos = 0;
	}
	
	if (target->stats->health <= 0) {
		target->stats->health = 0;
		target->stats->defense -= defenseBuff;
		target->stats->defenseBuffed = false;
		target->isAlive = false;

		DynamicEntity* newTimeLine[5] = {nullptr,nullptr, nullptr, nullptr, nullptr};

		//Select each living entity in timeline
		for (int i = 0; i < 5; i++) {
			if (turnsTimeLine[i]->isAlive == true) {
				//Introduce it to a new array in order
				for (int j = 0; j < 5; j++) {
					if (newTimeLine[j] == nullptr) {
						newTimeLine[j] = turnsTimeLine[i];
						break;
					}

				}
			}
		}

		int emptySpots = 0;

		//Replace the old timeline with the new one
		for (int k = 0; k < 5; k++) {
			if (newTimeLine[k] != nullptr) {
				turnsTimeLine[k] = newTimeLine[k];
			}
			else {
				turnsTimeLine[k] = nullptr;
				emptySpots++;
			}
			
		}

		//Fill the new timeline
		for (int k = 0; k < emptySpots; k++) {

			SetTurnOrder();
		}
		
	}
}

void Battle::Defense() {
	actualTurnEntity->stats->defense += defenseBuff;
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
		ChangePhase(BattlePhase::LOSE);
		ret = true;
	}
	else if (enemiesCount <= 0) {
		ChangePhase(BattlePhase::WIN);
		ret = true;
	}

	return ret;
}

void Battle::ChangePhase(BattlePhase phase) {
	hasChangedPhase = true;
	battlePhase = phase;
}

// Called before quitting
bool Battle::CleanUp()
{
	//Buttons
	attackButton->state = GuiControlState::DISABLED;
	defenseButton->state = GuiControlState::DISABLED;
	itemButton->state = GuiControlState::DISABLED;
	escapeButton->state = GuiControlState::DISABLED;

	enemyButton1->state = GuiControlState::DISABLED;
	enemyButton2->state = GuiControlState::DISABLED;
	enemyButton3->state = GuiControlState::DISABLED;
	enemyButton4->state = GuiControlState::DISABLED;

	attackButton = nullptr;
	delete attackButton;

	defenseButton = nullptr;
	delete defenseButton;

	itemButton = nullptr;
	delete itemButton;

	escapeButton = nullptr;
	delete escapeButton;

	//Textures
	attackTex = nullptr;
	delete attackTex;

	defenseTex = nullptr;
	delete defenseTex;

	itemsTex = nullptr;
	delete itemsTex;

	press_escapeTex = nullptr;
	delete press_escapeTex;

	press_attackTex = nullptr;
	delete press_attackTex;

	press_defenseTex = nullptr;
	delete press_defenseTex;

	press_itemsTex = nullptr;
	delete press_itemsTex;

	press_escapeTex = nullptr;
	delete press_escapeTex;


	batButton = nullptr;
	delete batButton;

	flyingEyeButton = nullptr;
	delete flyingEyeButton;

	skeletonButton = nullptr;
	delete skeletonButton;

	press_batButton = nullptr;
	delete press_batButton;

	press_flyingEyeButton = nullptr;
	delete press_flyingEyeButton;

	press_skeletonButton = nullptr;
	delete press_skeletonButton;


	shield = nullptr;
	delete shield;

	switch(battlePhase) {
	case BattlePhase::WIN:
		
		//Destroy enemy
		for (int i = 4; i < 8; i++) {
			if (entitiesInBattle[i] != nullptr) {
				app->entities->DestroyEntity(entitiesInBattle[i]);
				app->scene->normalEnemyList.del(app->scene->normalEnemyList.At(app->scene->normalEnemyList.find((NormalEnemy*)entitiesInBattle[i])));
			}
		}
		
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

		break;
	case BattlePhase::LOSE:
		
		//Destroy enemy
		for (int i = 4; i < 8; i++) {
			if (entitiesInBattle[i] != nullptr) {
				app->entities->DestroyEntity(entitiesInBattle[i]);
				app->scene->normalEnemyList.del(app->scene->normalEnemyList.At(app->scene->normalEnemyList.find((NormalEnemy*)entitiesInBattle[i])));
			}
		}
	
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

			//Destroy enemy
			for (int i = 5; i < 8; i++) {
				if (entitiesInBattle[i] != nullptr ) {
					app->entities->DestroyEntity(entitiesInBattle[i]);
					app->scene->normalEnemyList.del(app->scene->normalEnemyList.At(app->scene->normalEnemyList.find((NormalEnemy*)entitiesInBattle[i])));
				}
			}
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

		}
		if (actualTurnEntity->dynamicType == DynamicType::ENEMY) {

			//Destroy enemy
			for (int i = 4; i < 8; i++) {
				if (entitiesInBattle[i] != nullptr) {
					app->entities->DestroyEntity(entitiesInBattle[i]);
					app->scene->normalEnemyList.del(app->scene->normalEnemyList.At(app->scene->normalEnemyList.find((NormalEnemy*)entitiesInBattle[i])));
				}
			}
			
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
		}

		break;
	}

	//app->entities->DestroyEntity(entitiesInBattle[app->scene->normalEnemyList.find((NormalEnemy*)entitiesInBattle[4])]);

	//Music

	

	return true;
}
