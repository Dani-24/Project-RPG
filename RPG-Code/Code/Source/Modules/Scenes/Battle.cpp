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
	battleTurn = 0;
	LOG("Loading Battle");
	
	battleStage = &app->stages->actualStage;

	switch (*battleStage) {
	case StageIndex::NONE:
		break;
	case StageIndex::TOWN:
		townBattleBackground = app->tex->Load("Assets/textures/forest_bg_1.png");
		
		
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
	app->stages->playerPtr->currentAnimation = &app->stages->playerPtr->walkAnimR;

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



	}
	else {

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

	sprintf_s(battleTurnChar, 3, "%02d", battleTurn);

	app->font->DrawText("Turn: ", app->win->GetWidth() / 2 - 100 - 6 * 10, 15);
	app->font->DrawText(battleTurnChar, app->win->GetWidth() / 2 - 100, 15);

	sprintf_s(turnValueChar, 3, "%02d", TurnValue);

	if (actualTurnEntity->dynamicType == DynamicType::CHARACTER) {
		app->font->DrawText("Turn Value: ", 100, app->win->GetHeight()/2 - 100);
		app->font->DrawText(turnValueChar, 250, app->win->GetHeight() / 2 - 100);
	}
	else if (actualTurnEntity->dynamicType == DynamicType::ENEMY) {
		app->font->DrawText("Turn Value: ", app->win->GetWidth() / 2 - 250, app->win->GetHeight() / 2 - 100);
		app->font->DrawText(turnValueChar, app->win->GetWidth() / 2 - 100, app->win->GetHeight() / 2 - 100);
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
					if (actualTurnEntity == entitiesInBattle[4]) {
						actualTurnEntity = entitiesInBattle[0];
					}
					else if (actualTurnEntity == entitiesInBattle[0]) {
						actualTurnEntity = entitiesInBattle[4];
					}
					battleTurn++;
					break;
				case 102:
					battleTurn++;
					break;
				case 103:
					battleTurn++;
					break;
				case 104:
					battleTurn++;
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
	}
	else {
		actualTurnEntity = entitiesInBattle[4];
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
	return true;
}
