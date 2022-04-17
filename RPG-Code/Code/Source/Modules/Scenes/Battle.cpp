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
#include <time.h>

#include "Defs.h"
#include "Log.h"

Battle::Battle(App* application, bool start_enabled) : Module(application, start_enabled)
{
	name.Create("battle");

	battlePause = false;
	playerBattleSprite = nullptr;
	townBattleBackground = nullptr;
	battleStage = nullptr;

	actualTurnEntity = nullptr;

	someoneAttacking = false;
	someoneDefending = false;
	itsPlayerTurn = false;
	canSelect = false;

	//2000 its ok
	attackTime = 1000;
	defenseTime = 1000;
	itemTime = 1000;
	escapeTime = 1000;

	winTime = 1000;
	loseTime = 1000;

	defenseBuff = 5;


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
	hasStarted = false;
	hasTriedToEscape = false;
	canEscape = false;
	gameOver = false;
	defenseBuffed = false;
	cont = 0;
	battleTurn = 0;
	TurnValue = 321.123f;
	LOG("Loading Battle");
	
	battleStage = &app->stages->actualStage;

	switch (*battleStage) {
	case StageIndex::NONE:
		break;
	case StageIndex::TOWN:
		townBattleBackground = app->tex->Load("Assets/textures/dungeon_1.jpg");
		
		
		break;
	default:
		break;
	}

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
	app->stages->playerPtr->currentAnimation->currentFrame = 1.0f;
	
	app->stages->playerPtr->canMove = false;
	app->camera->SetPos({ 0, 0 });
	
	//GUI
	attackButton = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 101, "Attack", { app->win->GetWidth()/2/2 - (74*4 + 50*3) /2  , (app->win->GetWidth() / 50) + 250, 74, 32 }, this);
	defenseButton = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 102, "Defense", { app->win->GetWidth() / 2 / 2 - (74 * 4 + 50 * 3) / 2 + 74 + 50 , (app->win->GetWidth() / 50) + 250, 74, 32 }, this);
	itemButton = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 103, "Item", { app->win->GetWidth() / 2 / 2 - (74 * 4 + 50 * 3) / 2  + 74*2 +50*2, (app->win->GetWidth() / 50) + 250, 74, 32 }, this);
	escapeButton = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 104, "Escape", { app->win->GetWidth() / 2 / 2 - (74 * 4 + 50 * 3) / 2 + 74*3 + 50*3, (app->win->GetWidth() / 50) + 250, 74, 32 }, this);

	SetTurnOrder();

	return true;
}



bool Battle::PreUpdate()
{
	bool ret = true;

	CheckWinLose();
	

	return ret;
}

bool Battle::Update(float dt)
{
	if (battlePause == false) {

		//Player turn
		if (actualTurnEntity->dynamicType == DynamicType::CHARACTER) {

			switch (battlePhase) {
			case BattlePhase::THINKING:
				//Debuff if protected las turn
				if (defenseBuffed == true) {
					actualTurnEntity->stats->deffense -= defenseBuff;
					defenseBuffed = false;
				}
				canSelect = true;
				break;
			case BattlePhase::ATTACKING:
				if (cont < attackTime) {
					cont += dt;
				}
				//ATTACK
				else {
					cont = 0;
					Attack(*entitiesInBattle[4]);
					actualTurnEntity = entitiesInBattle[4];
					battleTurn++;
					battlePhase = BattlePhase::THINKING;
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
					actualTurnEntity = entitiesInBattle[4];
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
					
					canEscape = Escape();
					hasTriedToEscape = true;
				}
				else if (cont < escapeTime * 3 && hasTriedToEscape == true) {
					cont = 0;
					if (canEscape == true) {
						app->fade->DoFadeToBlack(this, (Module*)app->titleScene);
					}
					else {
						hasTriedToEscape = false;
						actualTurnEntity = entitiesInBattle[4];
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
					cont = 0;
					app->fade->DoFadeToBlack(this, (Module*)app->titleScene);
				}
				break;

			case BattlePhase::LOSE:
				if (cont < loseTime) {
					cont += dt;
				}
				//LOSING
				else {
					cont = 0;
					app->fade->DoFadeToBlack(this, (Module*)app->titleScene);
				}
				break;
			}

		}
		//Enemy turn
		else if (actualTurnEntity->dynamicType == DynamicType::ENEMY) {
			switch (battlePhase) {
			case BattlePhase::THINKING:
				
				//Debuff if protected las turn
				if (defenseBuffed == true) {
					actualTurnEntity->stats->deffense -= defenseBuff;
					defenseBuffed = false;
				}
				optionPercent = 0;
				srand(time(NULL));
				optionPercent = (rand() % (100 - 0)) + 0;
				//If the enemy is NOT afraid
				if (actualTurnEntity->stats->health >= actualTurnEntity->stats->maxHealth / 2) {
					if (optionPercent < 70) {
						battlePhase = BattlePhase::ATTACKING;
					}
					else {
						battlePhase = BattlePhase::DEFENDING;
					}

				}
				//If the enemy IS afraid
				else {
					if (optionPercent < 60) {
						battlePhase = BattlePhase::ATTACKING;
					}
					else if(optionPercent < 85) {
						battlePhase = BattlePhase::DEFENDING;
					}
					else {
						battlePhase = BattlePhase::ESCAPING;
					}
				}
				
				break;

			case BattlePhase::ATTACKING:
				if (cont < attackTime) {
					cont += dt;
				}
				//ATTACK
				else {
					//int targetNum = (rand() % (1 - 1)) + 1;
					int targetNum = 0;
					Attack(*entitiesInBattle[targetNum]);
					actualTurnEntity = entitiesInBattle[0];
					battleTurn++;
					battlePhase = BattlePhase::THINKING;
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
					actualTurnEntity = entitiesInBattle[0];
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

					canEscape = Escape();
					hasTriedToEscape = true;
				}
				else if (cont < escapeTime * 3 && hasTriedToEscape == true) {
					cont = 0;
					if (canEscape == true) {
						app->fade->DoFadeToBlack(this, (Module*)app->titleScene);
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
					cont = 0;
					app->fade->DoFadeToBlack(this, (Module*)app->titleScene);
				}
				break;

			case BattlePhase::LOSE:
				if (cont < loseTime) {
					cont += dt;
				}
				//LOSING
				else {
					cont = 0;
					app->fade->DoFadeToBlack(this, (Module*)app->titleScene);
				}
				break;
			}

		}
		
			
		

		app->stages->playerPtr->currentAnimation->Update(dt);
	}

	if (gameOver == true) {
		if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN) {
			app->fade->DoFadeToBlack(this, (Module*)app->titleScene);
		}

	}

	return true;
}

// Render bullshit
bool Battle::PostUpdate()
{
	bool ret = true;
	if (battleStage != nullptr) {
		switch (*battleStage) {
		case StageIndex::NONE:
			break;
		case StageIndex::TOWN:
			app->render->DrawTexture(townBattleBackground, 0, 0);
			break;
		default:
			break;
		}
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
	}

	if (battleTurn > 99) {
		battleTurn = 99;
	}

	//Print battle Turn
	sprintf_s(battleTurnChar, 9, "Turn: %02d", battleTurn);
	app->font->DrawText(battleTurnChar, app->win->GetWidth() / 2 - 100, 15);

	//Print turn value (depending on entities speed)
	sprintf_s(turnValueChar, 20, "Turn Value: %.2f", TurnValue);

	if (actualTurnEntity->dynamicType == DynamicType::CHARACTER) {
		app->font->DrawText(turnValueChar, 50, app->win->GetHeight() / 2 - 30);
	}
	else if (actualTurnEntity->dynamicType == DynamicType::ENEMY) {
		app->font->DrawText(turnValueChar, app->win->GetWidth() / 2 - 300, app->win->GetHeight() / 2 - 30);
	}

	
	
	//Print battle messages
	switch (battlePhase) {
		case BattlePhase::THINKING:
			sprintf_s(nameChar, 50, "It's %s's turn", actualTurnEntity->name);
			app->font->DrawText(nameChar, 50, app->win->GetHeight() / 2 - 150);
			break;

		case BattlePhase::SELECTING:
			app->font->DrawText("Select a target", 50, app->win->GetHeight() / 2 - 150);
			break;

		case BattlePhase::ATTACKING:
			sprintf_s(nameChar, 50, "%s attacks!", actualTurnEntity->name);
			app->font->DrawText(nameChar, 50, app->win->GetHeight() / 2 - 150);
			break;

		case BattlePhase::DEFENDING:
			sprintf_s(nameChar, 50, "%s is protected!", actualTurnEntity->name);
			app->font->DrawText(nameChar, 50, app->win->GetHeight() / 2 - 150);
			break;

		case BattlePhase::USING_ITEM:
			app->font->DrawText("You have no items left!", 50, app->win->GetHeight() / 2 - 150);
			break;

		case BattlePhase::ESCAPING:
			if (hasTriedToEscape == false) {
				sprintf_s(nameChar, 50, "%s is trying to escape...", actualTurnEntity->name);
				app->font->DrawText(nameChar, 50, app->win->GetHeight() / 2 - 150);
			}
			else if (canEscape == false){
				sprintf_s(nameChar, 50, "%s could not escape!", actualTurnEntity->name);
				app->font->DrawText(nameChar, 50, app->win->GetHeight() / 2 - 150);
			}
			else if (canEscape == true) {
				sprintf_s(nameChar, 50, "%s could escape successfully!", actualTurnEntity->name);
				app->font->DrawText(nameChar, 50, app->win->GetHeight() / 2 - 150);
			}
			
			break;

		case BattlePhase::WIN:
			app->font->DrawText("Victory! Press SPACE to continue", 50, app->win->GetHeight() / 2 - 150);
			break;

		case BattlePhase::LOSE:
			app->font->DrawText("Game over! Press SPACE to go back to title", 50, app->win->GetHeight() / 2 - 150);
			break;
	}

	sprintf_s(nameChar, 50, "Player health: %2d", entitiesInBattle[0]->stats->health);
	app->font->DrawText(nameChar, 50, app->win->GetHeight() / 2 - 120);

	sprintf_s(nameChar, 50, "Enemy health: %2d", entitiesInBattle[4]->stats->health);
	app->font->DrawText(nameChar, app->win->GetWidth() / 2 - 300, app->win->GetHeight() / 2 - 120);
	
	
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
				if (actualTurnEntity == entitiesInBattle[0] && actualTurnEntity->isAlive == true) {
					battlePhase = BattlePhase::ATTACKING;
					canSelect = false;
				}
				break;
			case 102:
				if (actualTurnEntity == entitiesInBattle[0] && actualTurnEntity->isAlive == true) {
					battlePhase = BattlePhase::DEFENDING;
					canSelect = false;
				}
				break;
			case 103:
				if (actualTurnEntity == entitiesInBattle[0] && actualTurnEntity->isAlive == true) {
					battlePhase = BattlePhase::USING_ITEM;
					canSelect = false;
				}
				break;
			case 104:
				if (actualTurnEntity == entitiesInBattle[0] && actualTurnEntity->isAlive == true) {
					battlePhase = BattlePhase::ESCAPING;
					canSelect = false;
				}
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
	if (hasStarted == false) {

		if (entitiesInBattle[0]->stats->speed >= entitiesInBattle[4]->stats->speed) {
			actualTurnEntity = entitiesInBattle[0];
		}
		else {
			actualTurnEntity = entitiesInBattle[4];
		}

		hasStarted = true;
	}
	else {
		if (actualTurnEntity == entitiesInBattle[0]) {
			actualTurnEntity = entitiesInBattle[4];
			
		}
		else if (actualTurnEntity == entitiesInBattle[4]) {
			actualTurnEntity = entitiesInBattle[0];
		}
	}

}

void Battle::Attack(DynamicEntity target) {
	target.stats->health = target.stats->health + target.stats->deffense - actualTurnEntity->stats->attack;
	if (target.stats->health <= 0) {
		target.isAlive = false;
	}
}

void Battle::Defense() {
	actualTurnEntity->stats->deffense += defenseBuff;
	defenseBuffed = true;
}

void Battle::UseItem(DynamicEntity target) {
	
}

bool Battle::Escape() {

	bool ret;

	srand(time(NULL));
	int percent = (rand() % (100 - 0)) + 0;

	if (percent > 75) {
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


void Battle::CheckWinLose() {

	alliesCount = CountAllies();
	enemiesCount = CountEnemies();

	if (alliesCount <= 0) {
		battlePhase = BattlePhase::LOSE;
	}
	else if (enemiesCount <= 0) {
		battlePhase = BattlePhase::WIN;
	}
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
	
	entitiesInBattle[4]->position = entitiesInBattle[4]->mapPosition;

	//Take back player position
	app->stages->playerPtr->position = app->stages->playerPtr->mapPosition;
	app->camera->SetTarget(app->stages->playerPtr);
	app->camera->OnTarget();

	//Take back player animation
	app->stages->playerPtr->currentAnimation = app->stages->playerPtr->mapAnimation;

	app->stages->playerPtr->canMove = true;
	app->map->LoadCol();
	app->stages->onBattle = false;

	if (gameOver == true) {
		app->scene->Disable();
	}

	return true;
}
