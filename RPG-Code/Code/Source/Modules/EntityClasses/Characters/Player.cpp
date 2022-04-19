#include "Player.h"

#include "App.h"
#include "Render.h"
#include "Audio.h"
#include "Camera.h"
#include "Textures.h"
#include "Input.h"
#include "Player.h"
#include "Log.h"
#include "Window.h"
#include "Scene.h"
#include "Map.h"
#include "Stages.h"
#include "Battle.h"
#include "FadeToBlack.h"

Player::Player( int x, int y) : Character(CharacterType::PLAYER)
{

	position = {x,y};

	//----------------------------------------------------------------------------------Overworld------------------------------------

	/*walkAnimDown.PushBack({ 9,10,31,46 });
	walkAnimDown.PushBack({ 62,8,31,46 });
	walkAnimDown.PushBack({ 114,10,31,46 });
	walkAnimDown.loop = true;
	walkAnimDown.speed = 0.006f;

	walkAnimUp.PushBack({ 9,218,31,46 });
	walkAnimUp.PushBack({ 62,221,31,46 });
	walkAnimUp.PushBack({ 114,218,31,47 });
	walkAnimUp.loop = true;
	walkAnimUp.speed = 0.006f;

	walkAnimL.PushBack({ 11,82,26,44 });
	walkAnimL.PushBack({ 64,80,26,45 });
	walkAnimL.PushBack({ 116,82,27,44 });
	walkAnimL.loop = true;
	walkAnimL.speed = 0.006f;

	walkAnimR.PushBack({ 11,153,27,44 });
	walkAnimR.PushBack({ 64,150,27,44 });
	walkAnimR.PushBack({ 116,153,27,44 });
	walkAnimR.loop = true;
	walkAnimR.speed = 0.006f;

	idleAnimR.PushBack({ 64,150,27,44 });
	idleAnimL.PushBack({ 64,80,26,45 });
	idleAnimUp.PushBack({ 62,221,31,46 });
	idleAnimDown.PushBack({ 62,8,31,46 });*/

	walkAnimDown.PushBack({ 0,0,48,64 });
	walkAnimDown.PushBack({ 48,0,48,64 });
	walkAnimDown.PushBack({ 96,0,48,64 });
	walkAnimDown.loop = true;
	walkAnimDown.speed = 0.006f;

	walkAnimUp.PushBack({ 0,192,48,64 });
	walkAnimUp.PushBack({ 48,192,48,64 });
	walkAnimUp.PushBack({ 96, 192,48,64 });
	walkAnimUp.loop = true;
	walkAnimUp.speed = 0.006f;

	walkAnimL.PushBack({ 0,64,48,64 });
	walkAnimL.PushBack({ 48,64,48,64 });
	walkAnimL.PushBack({ 96,64,48,64 });
	walkAnimL.loop = true;
	walkAnimL.speed = 0.006f;

	walkAnimR.PushBack({ 0,128,48,64 });
	walkAnimR.PushBack({ 48,128,48,64 });
	walkAnimR.PushBack({ 96,128,48,64 });
	walkAnimR.loop = true;
	walkAnimR.speed = 0.006f;

	idleAnimR.PushBack({ 48,128,48,64 });
	idleAnimL.PushBack({ 48,64,48,64 });
	idleAnimUp.PushBack({ 48,192,48,64 });
	idleAnimDown.PushBack({ 48,0,48,64 });

	//----------------------------------------------------------------------------------Battle Male------------------------------------

	idleBattleM.PushBack({ 0, 0, 140, 83 });
	idleBattleM.PushBack({ 140 , 0 , 140 , 83 });
	idleBattleM.PushBack({ 280 , 0 , 140 , 83 });
	idleBattleM.PushBack({ 420 , 0 , 140 , 83 });
	idleBattleM.PushBack({ 560 , 0 , 140 , 83 });
	idleBattleM.PushBack({ 700 , 0 , 140 , 83 });
	idleBattleM.PushBack({ 840 , 0 , 140 , 83 });
	idleBattleM.PushBack({ 980 , 0 , 140 , 83 });
	idleBattleM.PushBack({ 1120 , 0 , 140 , 83 });
	idleBattleM.PushBack({ 1260 , 0 , 140 , 83 });
	idleBattleM.PushBack({ 1400 , 0 , 140 , 83 });
	idleBattleM.loop = true;
	idleBattleM.speed = 0.015f;

	attackM.PushBack({ 0 , 83 , 140 , 83 });
	attackM.PushBack({ 140 , 83 , 140 , 83 });
	attackM.PushBack({ 280 , 83 , 140 , 83 });
	attackM.PushBack({ 420 , 83 , 140 , 83 });
	attackM.PushBack({ 560 , 83 , 140 , 83 });
	attackM.PushBack({ 700 , 83 , 140 , 83 });
	attackM.PushBack({ 0, 0, 140, 83 });
	attackM.PushBack({ 140 , 0 , 140 , 83 });
	attackM.PushBack({ 280 , 0 , 140 , 83 });
	attackM.PushBack({ 420 , 0 , 140 , 83 });
	attackM.PushBack({ 560 , 0 , 140 , 83 });
	attackM.PushBack({ 700 , 0 , 140 , 83 });
	attackM.PushBack({ 840 , 0 , 140 , 83 });
	attackM.PushBack({ 980 , 0 , 140 , 83 });
	attackM.PushBack({ 1120 , 0 , 140 , 83 });
	attackM.PushBack({ 1260 , 0 , 140 , 83 });
	attackM.PushBack({ 1400 , 0 , 140 , 83 });
	attackM.loop = false;
	attackM.speed = 0.008f;

	protectM.PushBack({ 0 , 581 , 140 , 83 });
	protectM.PushBack({ 140 , 581 , 140 , 83 });
	protectM.PushBack({ 280 , 581 , 140 , 83 });
	protectM.PushBack({ 420 , 581 , 140 , 83 });
	protectM.loop = true;
	protectM.speed = 0.006f;

	hitM.PushBack({ 0 , 249 , 140 , 83 });
	hitM.PushBack({ 140 , 249 , 140 , 83 });
	hitM.PushBack({ 280 , 249 , 140 , 83 });
	hitM.PushBack({ 420 , 249 , 140 , 83 });
	hitM.loop = true;
	hitM.speed = 0.006f;

	dieM.PushBack({ 0, 166, 140, 83 });
	dieM.PushBack({ 140 , 166 , 140 , 83 });
	dieM.PushBack({ 280 , 166 , 140 , 83 });
	dieM.PushBack({ 420 , 166 , 140 , 83 });
	dieM.PushBack({ 560 , 166 , 140 , 83 });
	dieM.PushBack({ 700 , 166 , 140 , 83 });
	dieM.PushBack({ 840 , 166 , 140 , 83 });
	dieM.PushBack({ 980 , 166 , 140 , 83 });
	dieM.PushBack({ 1120 , 166 , 140 , 83 });
	dieM.loop = false;
	dieM.speed = 0.006f;

	//----------------------------------------------------------------------------------Battle Female------------------------------------

	idleBattleF.PushBack({ 0 , 456 , 180 , 114 });
	idleBattleF.PushBack({ 180 , 456 , 180 , 114 });
	idleBattleF.PushBack({ 360 , 456 , 180 , 114 });
	idleBattleF.PushBack({ 540 , 456 , 180 , 114 });
	idleBattleF.PushBack({ 720 , 456 , 180 , 114 });
	idleBattleF.PushBack({ 900 , 456 , 180 , 114 });
	idleBattleF.PushBack({ 1080 , 456 , 180 , 114 });
	idleBattleF.PushBack({ 1260 , 456 , 180 , 114 });
	idleBattleF.PushBack({ 1440 , 456 , 180 , 114 });
	idleBattleF.PushBack({ 1620 , 456 , 180 , 114 });
	idleBattleF.PushBack({ 1800 , 456 ,  180 , 114 });
	idleBattleF.loop = true;
	idleBattleF.speed = 0.015f;

	attackF.PushBack({ 0 , 0 , 180 , 114 });
	attackF.PushBack({ 180 , 0 , 180 , 114 });
	attackF.PushBack({ 360 , 0 , 180 , 114 });
	attackF.PushBack({ 540 , 0 , 180 , 114 });
	attackF.PushBack({ 720 , 0 , 180 , 114 });
	attackF.PushBack({ 900 , 0 , 180 , 114 });
	attackF.PushBack({ 1080 , 0 , 180 , 114 });
	attackF.PushBack({ 0 , 456 , 180 , 114 });
	attackF.PushBack({ 180 , 456 , 180 , 114 });
	attackF.PushBack({ 360 , 456 , 180 , 114 });
	attackF.PushBack({ 540 , 456 , 180 , 114 });
	attackF.PushBack({ 720 , 456 , 180 , 114 });
	attackF.PushBack({ 900 , 456 , 180 , 114 });
	attackF.PushBack({ 1080 , 456 , 180 , 114 });
	attackF.PushBack({ 1260 , 456 , 180 , 114 });
	attackF.PushBack({ 1440 , 456 , 180 , 114 });
	attackF.PushBack({ 1620 , 456 , 180 , 114 });
	attackF.PushBack({ 1800 , 456 ,  180 , 114 });
	attackF.loop = false;
	attackF.speed = 0.008f;

	attackF2.PushBack({ 0 , 114 , 180 , 114 });
	attackF2.PushBack({ 180 , 114 , 180 , 114 });
	attackF2.PushBack({ 360 , 114 , 180 , 114 });
	attackF2.PushBack({ 540 , 114 , 180 , 114 });
	attackF2.PushBack({ 720 , 114 , 180 , 114 });
	attackF2.PushBack({ 900 , 114 , 180 , 114 });
	attackF2.PushBack({ 1080 , 114 , 180 , 114 });
	attackF2.PushBack({ 0 , 456 , 180 , 114 });
	attackF2.PushBack({ 180 , 456 , 180 , 114 });
	attackF2.PushBack({ 360 , 456 , 180 , 114 });
	attackF2.PushBack({ 540 , 456 , 180 , 114 });
	attackF2.PushBack({ 720 , 456 , 180 , 114 });
	attackF2.PushBack({ 900 , 456 , 180 , 114 });
	attackF2.PushBack({ 1080 , 456 , 180 , 114 });
	attackF2.PushBack({ 1260 , 456 , 180 , 114 });
	attackF2.PushBack({ 1440 , 456 , 180 , 114 });
	attackF2.PushBack({ 1620 , 456 , 180 , 114 });
	attackF2.PushBack({ 1800 , 456 ,  180 , 114 });
	attackF2.loop = false;
	attackF2.speed = 0.009f;

	attackChainF.PushBack({ 0 , 0 , 180 , 114 });
	attackChainF.PushBack({ 180 , 0 , 180 , 114 });
	attackChainF.PushBack({ 360 , 0 , 180 , 114 });
	attackChainF.PushBack({ 540 , 0 , 180 , 114 });
	attackChainF.PushBack({ 720 , 0 , 180 , 114 });
	attackChainF.PushBack({ 900 , 0 , 180 , 114 });
	attackChainF.PushBack({ 1080 , 0 , 180 , 114 });
	attackChainF.PushBack({ 0 , 114 , 180 , 114 });
	attackChainF.PushBack({ 180 , 114 , 180 , 114 });
	attackChainF.PushBack({ 360 , 114 , 180 , 114 });
	attackChainF.PushBack({ 540 , 114 , 180 , 114 });
	attackChainF.PushBack({ 720 , 114 , 180 , 114 });
	attackChainF.PushBack({ 900 , 114 , 180 , 114 });
	attackChainF.PushBack({ 1080 , 114 , 180 , 114 });
	attackChainF.PushBack({ 0 , 456 , 180 , 114 });
	attackChainF.PushBack({ 180 , 456 , 180 , 114 });
	attackChainF.PushBack({ 360 , 456 , 180 , 114 });
	attackChainF.PushBack({ 540 , 456 , 180 , 114 });
	attackChainF.PushBack({ 720 , 456 , 180 , 114 });
	attackChainF.PushBack({ 900 , 456 , 180 , 114 });
	attackChainF.PushBack({ 1080 , 456 , 180 , 114 });
	attackChainF.PushBack({ 1260 , 456 , 180 , 114 });
	attackChainF.PushBack({ 1440 , 456 , 180 , 114 });
	attackChainF.PushBack({ 1620 , 456 , 180 , 114 });
	attackChainF.PushBack({ 1800 , 456 ,  180 , 114 });
	attackChainF.loop = false;
	attackChainF.speed = 0.009f;

	protectF.PushBack({ 540 , 228 , 180 , 114 });
	protectF.loop = true;

	hitF.PushBack({ 0 , 798 , 180 , 114 });
	hitF.PushBack({ 180 , 798 , 180 , 114 });
	hitF.PushBack({ 360 , 798 , 180 , 114 });
	hitF.PushBack({ 540 , 798 , 180 , 114 });
	hitF.loop = true;
	hitF.speed = 0.006f;

	dieF.PushBack({ 0 , 228 , 180 , 114 });
	dieF.PushBack({ 180 , 228 , 180 , 114 });
	dieF.PushBack({ 360 , 228 , 180 , 114 });
	dieF.PushBack({ 540 , 228 , 180 , 114 });
	dieF.PushBack({ 720 , 228 , 180 , 114 });
	dieF.PushBack({ 900 , 228 , 180 , 114 });
	dieF.PushBack({ 1080 , 228 , 180 , 114 });
	dieF.PushBack({ 1260 , 228 , 180 , 114 });
	dieF.PushBack({ 1440 , 228 , 180 , 114 });
	dieF.PushBack({ 1620 , 228 , 180 , 114 });
	dieF.PushBack({ 1800 , 228 ,  180 , 114 });
	dieF.loop = false;
	dieF.speed = 0.006f;

	currentAnimation = &idleAnimR; //player start with idle anim

	name = "Rhen";
	configName = "player";

	margin = 10;
	colDownDistance = 47;
	colRightDistance = 9;

	baseCollider = app->collisions->AddCollider({ position.x + colRightDistance, position.y+ colDownDistance , 30,  24 }, Collider::Type::PLAYER, this);

	mapPosition = { 0,0 };
	battlePosition = { 150, 150 };

	isAlive = true;

	interactionButtonJustSpace.PushBack({ 83, 41, 36, 16 });
	interactionButtonJustSpace.loop = false;
}

// Destructor
Player::~Player()
{}

bool Player::Awake(pugi::xml_node& config)
{
	LOG("Init Image library, ta guapa la libreria de imagenes llamada player");
	bool ret = true;
	LOG("Num in config: %d",config.child("exampleNumber").attribute("num").as_int());

	MaleChar = config.child("male").attribute("path").as_string();
	FemaleChar = config.child("female").attribute("path").as_string();
	electionfxChar = config.child("election").attribute("path").as_string();
	WalkfxChar = config.child("walkFx").attribute("path").as_string();
	interactionButtonChar = config.child("interactionButton").attribute("path").as_string();

	return ret;
}

bool Player::Start()
{
	LOG("start Player");
	bool ret = true;

	erectionFx = app->audio->LoadFx(electionfxChar);
	walkFx = app->audio->LoadFx(WalkfxChar);

	PlayerMTex = app->tex->Load(MaleChar);
	PlayerFTex = app->tex->Load(FemaleChar);
	BattleMTex = app->tex->Load("Assets/sprites/main_ch/mainChM/battle/mBattleSprite.png");
	BattleFTex = app->tex->Load("Assets/sprites/main_ch/mainChF/battle/fBattlesprite.png");
	interactionButton = app->tex->Load(interactionButtonChar);

	//player start with idle anim
	currentAnimation = &idleAnimDown;
	PlayerErection = 1;

	canMove = true;

	stats = new Stats(1, 20, 6 , 5, 5, 20);

	return ret;
}

bool Player::PreUpdate()
{
	// DEBUG PLAYER POSITION
	//LOG("position x %d y %d", position.x, position.y);
	
	//if (app->scene->godmode) stats->SetStats();	
	
	// Show GUI if player isn't moving
	if (toggleGui == true && app->stages->actualStage != StageIndex::INTRODUCTION) {
		if (lastFramePos == position) {
			showGuiCont++;
			if (showGuiCont >= 120) {
				app->scene->guiactivate = true;
			}
		}
		else {
			showGuiCont = 0;
		}

		lastFramePos = position;
	}
	return true;
}

bool Player::Update(float dt) {
	bool ret = true;

	if (app->scene->pause == false && canMove == true && app->dialogs->dialoging == false) {

		if ((app->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN)) {
			if (PlayerErection != true) {
				PlayerErection = true;
				name = "Rhen";
				app->audio->PlayFx(erectionFx);
			}
		}
		if ((app->input->GetKey(SDL_SCANCODE_2) == KEY_DOWN)) {
			if (PlayerErection != false) {
				PlayerErection = false;
				name = "Briar";
				app->audio->PlayFx(erectionFx);
			}
		}

		if (app->fade->fading == false && app->stages->actualStage != StageIndex::INTRODUCTION) {
			MovementPlayer(dt);
		}
	}

	baseCollider->rect.x = position.x + colRightDistance;
	baseCollider->rect.y = position.y + colDownDistance;

	return ret;
}

bool Player::PostUpdate()
{
	bool ret = true;

	if (printInteractionButt == true) {
		app->render->DrawTexture(interactionButton, position.x + 5, position.y, &interactionButtonJustSpace.GetCurrentFrame());
	}
	printInteractionButt = false;

	return true;
}

bool Player::CleanUp() {

	//Collisions
	app->collisions->RemoveCollider(baseCollider);
	app->collisions->RemoveCollider(battleCollider);

	baseCollider = nullptr;
	delete baseCollider;

	//Animations
	currentAnimation = nullptr;
	delete currentAnimation;

	//Textures
	app->tex->UnLoad(spriteText);
	app->tex->UnLoad(PlayerFTex);
	app->tex->UnLoad(PlayerMTex);

	return true;
}

void Player::MovementPlayer(float dt) {
	speed = 0.2 * dt;

	walkFxCooldown -= dt;
	int cooldown = 450;

	if (app->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT) {
		position.y -= speed;

		if (currentAnimation != &walkAnimUp) {
			currentAnimation = &walkAnimUp;
		}

		if (walkFxCooldown < 0) {
			app->audio->PlayFx(walkFx);
			walkFxCooldown = cooldown;
		}
	}
	else if (app->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT) {
		position.y += speed;

		if (currentAnimation != &walkAnimDown) {
			currentAnimation = &walkAnimDown;
		}

		if (walkFxCooldown < 0) {
			app->audio->PlayFx(walkFx);
			walkFxCooldown = cooldown;
		}
	}
	else if (app->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT) {
		position.x -= speed;

		if (currentAnimation != &walkAnimL) {
			currentAnimation = &walkAnimL;
		}

		if (walkFxCooldown < 0) {
			app->audio->PlayFx(walkFx);
			walkFxCooldown = cooldown;
		}
	}
	else if (app->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT) {
		position.x += speed;

		if (currentAnimation != &walkAnimR) {
			currentAnimation = &walkAnimR;
		}

		if (walkFxCooldown < 0) {
			app->audio->PlayFx(walkFx);
			walkFxCooldown = cooldown;
		}
	}
	else {
		if (currentAnimation == &walkAnimR) {
			currentAnimation = &idleAnimR;
		}
		else if(currentAnimation == &walkAnimL) {
			currentAnimation = &idleAnimL;
		}
		else if (currentAnimation == &walkAnimUp) {
			currentAnimation = &idleAnimUp;
		}
		else if (currentAnimation == &walkAnimDown) {
			currentAnimation = &idleAnimDown;
		}
	}

	currentAnimation->Update(dt);
}

void Player::OnCollision(Collider* col1, Collider* col2) {

	if (col1 == baseCollider && col2->type == Collider::WALL && !app->scene->godmode) {

		//Cant move Left
		if (col2->rect.x + col2->rect.w > col1->rect.x					&&
			col2->rect.x + col2->rect.w < col1->rect.x + col1->rect.w	&&
			col1->rect.y < col2->rect.y + col2->rect.h - margin			&&
			col1->rect.y + col1->rect.h > col2->rect.y + margin) {
		
			this->position.x = col2->rect.x + col2->rect.w - colRightDistance;
		}

		//Cant move Right
		if (col2->rect.x > col1->rect.x									&&
			col2->rect.x < col1->rect.x + col1->rect.w					&&
			col1->rect.y < col2->rect.y + col2->rect.h - margin			&&
			col1->rect.y + col1->rect.h > col2->rect.y + margin) {
			
			this->position.x = col2->rect.x - col1->rect.w - colRightDistance;
		}

		//Cant move Up
		if (col2->rect.y + col2->rect.h > col1->rect.y					&&
			col2->rect.y + col2->rect.h < col1->rect.y + col1->rect.h	&&
			col1->rect.x + col1->rect.w > col2->rect.x + margin			&&
			col1->rect.x < col2->rect.x + col2->rect.w - margin) {
			
			this->position.y = col2->rect.y + col2->rect.h - colDownDistance;
		}
		//Cant move Down
		if (col2->rect.y < col1->rect.y + col1->rect.h					&&
			col2->rect.y > col1->rect.y									&&
			col1->rect.x + col1->rect.w > col2->rect.x + margin			&&
			col1->rect.x < col2->rect.x + col2->rect.w - margin) {
			
			this->position.y = col2->rect.y - col1->rect.h - colDownDistance;
		}
	}

	if (col1 == baseCollider && col2->type == Collider::INSTANT) {

		//Collision with enemy

		ListItem<NormalEnemy*>* normalEnemyInList;

		for (normalEnemyInList = app->scene->normalEnemyList.start; normalEnemyInList != NULL; normalEnemyInList = normalEnemyInList->next)
		{
			if (normalEnemyInList->data->GetCollider() != nullptr) {
				if (normalEnemyInList->data->GetCollider() == col2 && app->battle->isEnabled() == false) {
					
					app->battle->entitiesInBattle[0] = this;
					app->battle->entitiesInBattle[1] = app->stages->partyListPtr->At(1)->data;
					app->battle->entitiesInBattle[4] = normalEnemyInList->data;
					//app->battle->normalEnemyInBattle = normalEnemyInList->data;
					//app->battle->CurrentEnemyType = EnemyInBattleType::NORMAL;
					app->battle->Enable();
				}
			}
			
		}

		//Collision with entrance
		for (int i = 0; i < MAX_ENTRIES; i++) {
			if (app->map->mapEntries[i] != nullptr) {
				if (app->map->mapEntries[i]->col == col2) {

					switch (app->map->mapEntries[i]->id) 
					{
						case 0:

							switch (app->stages->actualStage)
							{
							case StageIndex::NONE:

								break;
							case StageIndex::TOWN:

								LOG("Loading Shop map");
								townPos = { position.x, position.y + townPosYAxisfix };
								app->fade->DoFadeToBlack(StageIndex::SHOP);

								break;
							case StageIndex::DOJO:

								LOG("Loading town map");
								app->fade->DoFadeToBlack(StageIndex::TOWN);

								break;
							case StageIndex::SHOP:

								LOG("Loading Shop sub level map");
								app->fade->DoFadeToBlack(StageIndex::SHOPSUB);

								break;
							case StageIndex::SHOPSUB:

								LOG("Loading Shop map");
								shopPosOn = true;
								app->fade->DoFadeToBlack(StageIndex::SHOP);

								break;
							case StageIndex::TAVERN:

								LOG("Loading town map");
								app->fade->DoFadeToBlack(StageIndex::TOWN);

								break;
							}

							break;
						case 1:

							switch (app->stages->actualStage)
							{
							case StageIndex::NONE:

								break;
							case StageIndex::TOWN:

								LOG("Loading Tavern map");
								townPos = { position.x, position.y + townPosYAxisfix };
								app->fade->DoFadeToBlack(StageIndex::TAVERN);

								break;
							case StageIndex::DOJO:

								LOG("Returning to town");
								app->fade->DoFadeToBlack(StageIndex::TOWN);

								break;
							case StageIndex::SHOP:

								LOG("Loading town map");
								app->fade->DoFadeToBlack(StageIndex::TOWN);

								break;
							case StageIndex::TAVERN:

								LOG("Loading town map");
								app->fade->DoFadeToBlack(StageIndex::TOWN);

								break;
							}
							break;
						case 2:

							switch (app->stages->actualStage)
							{
							case StageIndex::NONE:

								break;
							case StageIndex::TOWN:

								LOG("Loading Tavern map");
								townPos = { position.x, position.y + townPosYAxisfix };
								app->fade->DoFadeToBlack(StageIndex::TAVERN);

								break;
							case StageIndex::DOJO:

								LOG("Returning to town");
								app->fade->DoFadeToBlack(StageIndex::TOWN);

								break;
							case StageIndex::SHOP:

								LOG("Loading town map");
								app->fade->DoFadeToBlack(StageIndex::TOWN);

								break;
							}

							break;
						case 3:
							switch (app->stages->actualStage)
							{
							case StageIndex::NONE:

								break;
							case StageIndex::TOWN:

								LOG("Loading Dojo map");
								townPos = { position.x, position.y + townPosYAxisfix };
								app->fade->DoFadeToBlack(StageIndex::DOJO);

								break;
							case StageIndex::DOJO:

								LOG("Returning to town");
								app->fade->DoFadeToBlack(StageIndex::TOWN);

								break;
							case StageIndex::SHOP:

								LOG("Loading town map");
								app->fade->DoFadeToBlack(StageIndex::TOWN);

								break;
							}
							break;
						default:
							if (app->stages->actualStage == StageIndex::DOJO) {
								LOG("Returning to town");
								app->fade->DoFadeToBlack(StageIndex::TOWN);
							}
							if (app->stages->actualStage == StageIndex::TOWN) {
								LOG("going to dojo");
								townPos = { position.x, position.y + townPosYAxisfix };
								app->fade->DoFadeToBlack(StageIndex::DOJO);
							}
							break;
					}
				}
			}
		}
	}

	if (col1 == baseCollider && col2->type == Collider::INTERACT) {

		// NPC COLLISIONS (Press Space)

		if (app->dialogs->dialoging == false) {
	
			for (ListItem<Entity*>* entityInList = app->entities->entityList.start; entityInList != NULL; entityInList = entityInList->next)
			{
				if (entityInList->data->activeOnStage == app->stages->actualStage) {
					
					if (entityInList->data->GetCollider() != nullptr) {
						if (entityInList->data->GetCollider() == col2) {
							switch (entityInList->data->npcID)
							{
							case 1:
								Interact(NPCType::COCK, cockDialog);
								break;
							case 2:
								Interact(NPCType::MERCHANT, merchantDialog);
								break;
							case 3:
								Interact(NPCType::BARKEEPER, barkeeperDialog);
								break;
							case 4:
								Interact(NPCType::TRAINER, trainerDialog);
								break;
							case 5:										
								Interact(NPCType::EMILIO, emilioDialog);
								break;
							case 7:
								Interact(NPCType::FUENTE, fuenteDialog);
								break;
							default:
								break;
							}
						}
					}
				}
			}
		}
	}
}

void Player::Interact(NPCType npc, const char* dialog[DIALOG_LENGHT]) {
	if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN) {
		app->dialogs->CreateDialog(npc, dialog);
		if (npc == NPCType::FUENTE) {
			for (ListItem<Character*>* characterList = app->scene->partyList.start; characterList != NULL; characterList = characterList->next) {
				characterList->data->stats->health = characterList->data->stats->maxHealth;
			}
		}
	}
	printInteractionButt = true;
}