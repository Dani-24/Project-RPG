#include "Player.h"

#include "App.h"
#include "Render.h"
#include "Audio.h"
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

	walkAnimDown.PushBack({ 9,10,31,46 });
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
	idleAnimDown.PushBack({ 62,8,31,46 });

	//----------------------------------------------------------------------------------Battle Male------------------------------------

	idleBattleM.PushBack({ 0, 22, 32, 39 });
	idleBattleM.PushBack({ 138 , 22 , 35 , 39 });
	idleBattleM.PushBack({ 273 , 22 , 39 , 39 });
	idleBattleM.PushBack({ 414 , 22 , 42 , 39 });
	idleBattleM.PushBack({ 535 , 22 , 86 , 39 });
	idleBattleM.PushBack({ 675 , 22 , 56 , 39 });
	idleBattleM.PushBack({ 840 , 22 , 31 , 39 });
	idleBattleM.PushBack({ 980 , 22 , 31 , 39 });
	idleBattleM.PushBack({ 1120 , 22 , 32 , 39 });
	idleBattleM.PushBack({ 1260 , 22 , 32 , 39 });
	idleBattleM.PushBack({ 1400 , 22 , 32 , 39 });
	idleBattleM.loop = true;
	idleBattleM.speed = 0.006f;

	attackM.PushBack({ 0 , 86 , 32 , 61 });
	attackM.PushBack({ 138 , 86 , 35 , 61 });
	attackM.PushBack({ 273 , 86 , 39 , 61 });
	attackM.PushBack({ 414 , 86 , 42 , 61 });
	attackM.PushBack({ 535 , 86 , 86 , 61 });
	attackM.PushBack({ 675 , 86 , 56 , 61 });
	attackM.loop = true;
	attackM.speed = 0.006f;

	dashM.PushBack({ 0 , 192 , 32 , 30 });
	dashM.PushBack({ 138 , 192 , 35 , 30 });
	dashM.PushBack({ 273 , 192 , 39 , 30 });
	dashM.PushBack({ 414 , 192 , 42 , 30 });
	dashM.loop = true;
	dashM.speed = 0.006f;

	hitM.PushBack({ 0 , 266 , 32 , 40 });
	hitM.PushBack({ 138 , 266 , 35 , 40 });
	hitM.PushBack({ 273 , 266 , 39 , 40 });
	hitM.PushBack({ 414 , 266 , 42 , 40 });
	hitM.loop = true;
	hitM.speed = 0.006f;

	//----------------------------------------------------------------------------------Battle Female------------------------------------

	idleBattleF.PushBack({ 0 , 201 , 73 , 51 });
	idleBattleF.PushBack({ 74 , 201 , 67 , 51 });
	idleBattleF.PushBack({ 142 , 201 , 71 , 51 });
	idleBattleF.PushBack({ 214 , 201 , 115 , 51 });
	idleBattleF.PushBack({ 330 , 201 , 98 , 51 });
	idleBattleF.PushBack({ 429 , 201 , 95 , 51 });
	idleBattleF.PushBack({ 525 , 201 , 83 , 51 });
	idleBattleF.PushBack({ 609 , 201 , 85 , 51 });
	idleBattleF.PushBack({ 694 , 201 , 80 , 51 });
	idleBattleF.PushBack({ 774 , 201 , 80 , 51 });
	idleBattleF.PushBack({ 1854 , 201 ,  80 , 51 });
	idleBattleF.loop = true;
	idleBattleF.speed = 0.006f;

	attackF.PushBack({ 17 , 0 , 45 , 70 });
	attackF.PushBack({ 84 , 0 , 47 , 70 });
	attackF.PushBack({ 150 , 0 , 52 , 70 });
	attackF.PushBack({ 226 , 0 , 58 , 70 });
	attackF.PushBack({ 346 , 0 , 55 , 70 });
	attackF.PushBack({ 444 , 0 , 55 , 70 });
	attackF.PushBack({ 532 , 0 , 35 , 70 });
	attackF.loop = true;
	attackF.speed = 0.006f;

	attackF2.PushBack({ 0 , 70 , 73 , 80 });
	attackF2.PushBack({ 74 , 70 , 67 , 80 });
	attackF2.PushBack({ 142 , 70 , 71 , 80 });
	attackF2.PushBack({ 214 , 70 , 115 , 80 });
	attackF2.PushBack({ 330 , 70 , 98 , 80 });
	attackF2.PushBack({ 429 , 70 , 95 , 80 });
	attackF2.PushBack({ 525 , 70 , 89 , 80 });
	attackF2.loop = true;
	attackF2.speed = 0.006f;

	hitF.PushBack({ 0 , 150 , 73 , 51 });
	hitF.PushBack({ 74 , 150 , 67 , 51 });
	hitF.PushBack({ 142 , 150 , 71 , 51 });
	hitF.PushBack({ 214 , 150 , 115 , 51 });
	hitF.loop = true;
	hitF.speed = 0.006f;

	dieF.PushBack({ 0 , 252 , 73 , 56 });
	dieF.PushBack({ 74 , 252 , 67 , 56 });
	dieF.PushBack({ 142 , 252 , 71 , 56 });
	dieF.PushBack({ 214 , 252 , 115 , 56 });
	dieF.PushBack({ 330 , 252 , 98 , 56 });
	dieF.PushBack({ 429 , 252 , 95 , 56 });
	dieF.PushBack({ 525 , 252 , 83 , 56 });
	dieF.PushBack({ 609 , 252 , 85 , 56 });
	dieF.PushBack({ 694 , 252 , 80 , 56 });
	dieF.PushBack({ 774 , 252 , 80 , 56 });
	dieF.PushBack({ 854  , 252 ,  80 , 56 });
	dieF.loop = true;
	dieF.speed = 0.006f;

	currentAnimation = &idleAnimR; //player start with idle anim

	name = "Player";
	configName = "player";

	margin = 10;
	colDownDistance = 26;

	baseCollider = app->collisions->AddCollider({ position.x, position.y , 30,  24 }, Collider::Type::PLAYER, this);

	mapPosition = { 0,0 };
	battlePosition = { 100, 100 };

	isAlive = true;

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
	BattleMTex = app->tex->Load("Assets/sprites/main_ch/mainChM/battle/mpsprite.png");
	BattleFTex = app->tex->Load("Assets/sprites/main_ch/mainChF/battle/fpsprite.png");

	//player start with idle anim
	currentAnimation = &idleAnimDown;
	PlayerErection = 1;

	canMove = true;

	stats = new Stats(1, 20, 5 , 5, 5, 20);

	return ret;
}

bool Player::PreUpdate()
{
	// DEBUG PLAYER POSITION
	//LOG("position x %d y %d", position.x, position.y);

	return true;
}

bool Player::Update(float dt) {
	bool ret = true;

	if (app->scene->pause == false && canMove == true && app->dialogs->dialoging == false) {

		if ((app->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN)) {
			if (PlayerErection != true) {
				PlayerErection = true;
				app->audio->PlayFx(erectionFx);
			}
		}
		if ((app->input->GetKey(SDL_SCANCODE_2) == KEY_DOWN)) {
			if (PlayerErection != false) {
				PlayerErection = false;
				app->audio->PlayFx(erectionFx);
			}
		}

		if (app->fade->fading == false) {
			MovementPlayer(dt);
		}
	}

	baseCollider->rect.x = position.x;
	baseCollider->rect.y = position.y + colDownDistance;

	return ret;
}

bool Player::PostUpdate()
{
	bool ret = true;

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

	if (col1 == baseCollider && col2->type == Collider::WALL) {

		//Cant move Left
		if (col2->rect.x + col2->rect.w > col1->rect.x					&&
			col2->rect.x + col2->rect.w < col1->rect.x + col1->rect.w	&&
			col1->rect.y < col2->rect.y + col2->rect.h - margin			&&
			col1->rect.y + col1->rect.h > col2->rect.y + margin) {
		
			this->position.x = col2->rect.x + col2->rect.w;
		}

		//Cant move Right
		if (col2->rect.x > col1->rect.x									&&
			col2->rect.x < col1->rect.x + col1->rect.w					&&
			col1->rect.y < col2->rect.y + col2->rect.h - margin			&&
			col1->rect.y + col1->rect.h > col2->rect.y + margin) {
			
			this->position.x = col2->rect.x - col1->rect.w;
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
					app->battle->entitiesInBattle[4] = normalEnemyInList->data;
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
							break;
					}
				}
			}
		}
	}

	if (col1 == baseCollider && col2->type == Collider::INTERACT) {

		// NPC COLLISIONS

		// APPLY WALL COLLIDER bc if not you are kidnapped forever to dialog with the npcs

		//Cant move Left
		if (col2->rect.x + col2->rect.w > col1->rect.x &&
			col2->rect.x + col2->rect.w < col1->rect.x + col1->rect.w &&
			col1->rect.y < col2->rect.y + col2->rect.h - margin &&
			col1->rect.y + col1->rect.h > col2->rect.y + margin) {

			this->position.x = col2->rect.x + col2->rect.w + 15;
		}

		//Cant move Right
		if (col2->rect.x > col1->rect.x &&
			col2->rect.x < col1->rect.x + col1->rect.w &&
			col1->rect.y < col2->rect.y + col2->rect.h - margin &&
			col1->rect.y + col1->rect.h > col2->rect.y + margin) {

			this->position.x = col2->rect.x - col1->rect.w - 15;

		}

		//Cant move Up
		if (col2->rect.y + col2->rect.h > col1->rect.y &&
			col2->rect.y + col2->rect.h < col1->rect.y + col1->rect.h &&
			col1->rect.x + col1->rect.w > col2->rect.x + margin &&
			col1->rect.x < col2->rect.x + col2->rect.w - margin) {

			this->position.y = col2->rect.y + col2->rect.h - colDownDistance;
		}
		//Cant move Down
		if (col2->rect.y < col1->rect.y + col1->rect.h &&
			col2->rect.y > col1->rect.y &&
			col1->rect.x + col1->rect.w > col2->rect.x + margin &&
			col1->rect.x < col2->rect.x + col2->rect.w - margin) {

			this->position.y = col2->rect.y - col1->rect.h - colDownDistance;
		}

		// Then the dialogs

		if (app->dialogs->dialoging == false) {
			ListItem<Entity*>* entityInList;

			for (entityInList = app->entities->entityList.start; entityInList != NULL; entityInList = entityInList->next)
			{
				if (entityInList->data->GetCollider() != nullptr) {
					if (entityInList->data->GetCollider() == col2) {

						switch (entityInList->data->npcID)
						{
						case 1:
							app->dialogs->CreateDialog(NPCType::COCK, cockDialog);
							break;
						case 2:
							app->dialogs->CreateDialog(NPCType::MERCHANT, merchantDialog);
							break;
						case 3:
							app->dialogs->CreateDialog(NPCType::BARKEEPER, barkeeperDialog);
							break;
						case 4:
							app->dialogs->CreateDialog(NPCType::TRAINER, trainerDialog);
							break;
						case 5:
							app->dialogs->CreateDialog(NPCType::EMILIO, emilioDialog);
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