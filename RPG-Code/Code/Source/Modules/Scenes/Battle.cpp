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

	itsPlayerTurn = true;

	target = nullptr;

	//2000 its ok
	attackTime = 100;

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
	gameOver = false;
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
		//Enemy is attacking
		if (itsPlayerTurn == false) {
			if (cont < attackTime) {
				someoneAttacking = true;
				cont += dt;
			}
			else {
				cont = 0;
				someoneAttacking = false;
				srand(time(NULL));
				//int targetNum = (rand() % (1 - 1)) + 1;
				int targetNum = 0;
				target = entitiesInBattle[targetNum];
				target->stats->health = target->stats->health + target->stats->deffense - actualTurnEntity->stats->attack;
				actualTurnEntity = entitiesInBattle[0];
				itsPlayerTurn = true;
				battleTurn++;
				if (target->stats->health <=0) {
					target->isAlive = false;
					gameOver = true;
				}
			}
		}
		//Player is thinking
		else if(itsPlayerTurn == true && someoneAttacking == false){

		}
		//Player is attacking
		else if(itsPlayerTurn == true && someoneAttacking == true){
			if (cont < attackTime) {
				someoneAttacking = true;
				cont += dt;
			}
			else {
				cont = 0;
				someoneAttacking = false;
				actualTurnEntity = entitiesInBattle[4];
				itsPlayerTurn = false;

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
	if (gameOver == false) {
		if (someoneAttacking == true) {
			sprintf_s(nameChar, 50, "%s attacks!", actualTurnEntity->name);
			app->font->DrawText(nameChar, 50, app->win->GetHeight() / 2 - 150);
		}
		else if (itsPlayerTurn == true) {
			sprintf_s(nameChar, 50, "It's %s's turn", actualTurnEntity->name);
			app->font->DrawText(nameChar, 50, app->win->GetHeight() / 2 - 150);
		}

		sprintf_s(nameChar, 50, "Player health: %2d", entitiesInBattle[0]->stats->health);
		app->font->DrawText(nameChar, 50, app->win->GetHeight() / 2 - 120);

		sprintf_s(nameChar, 50, "Enemy health: %2d", entitiesInBattle[4]->stats->health);
		app->font->DrawText(nameChar, app->win->GetWidth() / 2 - 300, app->win->GetHeight() / 2 - 120);
	}
	else {
		app->font->DrawText("Game over! Press SPACE to go back to title", 50, app->win->GetHeight() / 2 - 150);
	}
	
	
	return ret;
}


bool Battle::OnGuiMouseClickEvent(GuiControl* control)
{

	switch (control->type)
	{
		case GuiControlType::BUTTON:
		
			switch (control->id) {
				case 101:
					if (actualTurnEntity == entitiesInBattle[0] && actualTurnEntity->isAlive == true) {
						someoneAttacking = true;
						//itsPlayerTurn = false;
						battleTurn++;
					}
					break;
				case 102:
					if (actualTurnEntity == entitiesInBattle[0]) {
						battleTurn++;
					}
					break;
				case 103:
					if (actualTurnEntity == entitiesInBattle[0]) {
						battleTurn++;
					}
					break;
				case 104:
					if (actualTurnEntity == entitiesInBattle[0]) {
						battleTurn++;
					}
					break;
			}
		
			break;

		//Other cases here
		default:
			break;
	}
		
	return true;
}

void Battle::SetTurnOrder() 
{
	if (entitiesInBattle[0]->stats->speed >= entitiesInBattle[4]->stats->speed) {
		actualTurnEntity = entitiesInBattle[0];
		itsPlayerTurn = true;
	}
	else {
		actualTurnEntity = entitiesInBattle[4];
		itsPlayerTurn = false;
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
