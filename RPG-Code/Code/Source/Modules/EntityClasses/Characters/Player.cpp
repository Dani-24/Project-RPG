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

Player::Player() : Character(CharacterType::PLAYER)
{
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

	currentAnimation = &idleAnimR; //player start with idle anim

	configName = "player";

	margin = 10;
	colDownDistance = 26;

	baseCollider = app->collisions->AddCollider({ position.x, position.y , 30,  24 }, Collider::Type::PLAYER, this);

	mapPosition = { 0,0 };
	battlePosition = { 100, 100 };

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

	return ret;
}

bool Player::Start()
{
	LOG("start Player");
	bool ret = true;

	erectionFx = app->audio->LoadFx("Assets/audio/sfx/fx_character_yes.wav");
	walkFx = app->audio->LoadFx("Assets/audio/sfx/fx_walk.wav");

	PlayerMTex = app->tex->Load(MaleChar);
	PlayerFTex = app->tex->Load("Assets/sprites/MainCh/MainChF/Walk/MainChF.png");

	//player start with idle anim
	currentAnimation = &idleAnimDown;
	PlayerErection = 1;

	canMove = true;

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

	if (app->scene->pause == false && canMove == true) {

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

		MovementPlayer(dt);
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
		for (int i = 0; i < MAX_ENTRIES; i++) {
			if (app->map->mapEntries[i] != nullptr) {
				if (app->map->mapEntries[i]->col == col2) {
					//LOG("%d", app->map->mapEntries[i]->id);
					switch (app->map->mapEntries[i]->id) 
					{
						case 0:
							LOG("Loading Shop map");
							break;
						case 1:
						case 2:
							LOG("Loading Tavern map");
							break;
						case 3:
							LOG("Loading Dojo map");
							break;
						default:
							break;
					}
				}
			}
		}
		
		
	}

}