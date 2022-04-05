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

Player::Player() : Character(CharacterType::PLAYER)
{
	LOG("EntityList: %d", app->entities->entityList.count());
	//Player* ent = new Player();
	//app->entities->entityList.add(ent);
	LOG("EntityList: %d", app->entities->entityList.count());

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

	yesFx = 0;

	currentAnimation = &idleAnimR; //player start with idle anim

	canMove = true;
}

// Destructor
Player::~Player()
{}

bool Player::Awake(pugi::xml_node& config)
{
	LOG("Init Image library, ta guapa la libreria de imagenes llamada player");
	bool ret = true;

	return ret;
}

bool Player::Start()
{
	LOG("start Player");
	bool ret = true;

	yesFx = app->audio->LoadFx("Assets/audio/sfx/fx_character_yes.wav");

	PlayerMTex = app->tex->Load("Assets/sprites/MainCh/MainChM/Walk/MainChM.png");
	PlayerFTex = app->tex->Load("Assets/sprites/MainCh/MainChF/Walk/MainChF.png");

	currentAnimation = &idleAnimR; //player start with idle anim
	PlayerDirectionRight = 1;//if its 1, player will be looking at the right, if it's 2, player will be looking at the left
	PlayerDirectionUp = 0;
	PlayerErection = 1;

	position.x = 950;
	position.y = 950;
	return ret;
}

bool Player::PreUpdate()
{
	CameraToPlayer();

	LOG("Player position X:%d Y:%d", position.x, position.y);

	return true;
}

bool Player::Update(float dt) {
	bool ret = true;

	if (app->scene->pause == false && canMove == true) {

		if ((app->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN)) {
			if (PlayerErection != true) {
				PlayerErection = true;
				app->audio->PlayFx(yesFx);
			}
		}
		if ((app->input->GetKey(SDL_SCANCODE_2) == KEY_DOWN)) {
			if (PlayerErection != false) {
				PlayerErection = false;
				app->audio->PlayFx(yesFx);
			}
		}

		MovementPlayer(dt);

	}

	return ret;
}

bool Player::PostUpdate()
{
	bool ret = true;

	

	return true;
}

bool Player::CleanUp() {

	app->tex->UnLoad(PlayerFTex);
	app->tex->UnLoad(PlayerMTex);

	currentAnimation = nullptr;

	return true;
}

void Player::MovementPlayer(float dt) {
	float speed = dt * 0.2f;

	if ((app->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT && app->input->GetKey(SDL_SCANCODE_W) != KEY_REPEAT && app->input->GetKey(SDL_SCANCODE_S) != KEY_REPEAT))
	{
		position.x += speed;
		if (currentAnimation != &walkAnimR)
		{
			walkAnimR.Reset();
			currentAnimation = &walkAnimR;
			PlayerDirectionRight = 1;
			PlayerDirectionUp = 0;
		}

	}
	if ((app->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT && app->input->GetKey(SDL_SCANCODE_W) != KEY_REPEAT && app->input->GetKey(SDL_SCANCODE_S) != KEY_REPEAT))
	{
		position.x -= speed;
		if (currentAnimation != &walkAnimL)
		{
			walkAnimL.Reset();
			currentAnimation = &walkAnimL;
			PlayerDirectionRight = 2;
			PlayerDirectionUp = 0;
		}
	}
	if ((app->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT)) {
		position.y -= speed;
		if (currentAnimation != &walkAnimUp)
		{
			walkAnimUp.Reset();
			currentAnimation = &walkAnimUp;
			PlayerDirectionUp = 1;
			PlayerDirectionRight = 0;
		}
	}
	if ((app->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT)) {
		position.y += speed;
		if (currentAnimation != &walkAnimDown)
		{
			walkAnimDown.Reset();
			currentAnimation = &walkAnimDown;
			PlayerDirectionUp = 2;
			PlayerDirectionRight = 0;
		}
	}

	currentAnimation->Update(dt);

	if (PlayerDirectionRight == 1 || PlayerDirectionRight == 2) {
		PlayerDirectionUp = 0;
	}
	if (PlayerDirectionUp == 1 || PlayerDirectionUp == 2) {
		PlayerDirectionRight = 0;
	}
	if (app->input->GetKey(SDL_SCANCODE_D) == KEY_IDLE && app->input->GetKey(SDL_SCANCODE_A) == KEY_IDLE && app->input->GetKey(SDL_SCANCODE_W) == KEY_IDLE && app->input->GetKey(SDL_SCANCODE_S) == KEY_IDLE) {
		if (currentAnimation != &idleAnimR && currentAnimation != &idleAnimL && currentAnimation != &idleAnimDown && currentAnimation != &idleAnimUp) {
			if (PlayerDirectionRight == 1) {
				idleAnimR.Reset();
				currentAnimation = &idleAnimR;
			}
			if (PlayerDirectionRight == 2) {
				idleAnimL.Reset();
				currentAnimation = &idleAnimL;
			}
			if (PlayerDirectionUp == 1) {
				idleAnimUp.Reset();
				currentAnimation = &idleAnimUp;
			}
			if (PlayerDirectionUp == 2) {
				idleAnimDown.Reset();
				currentAnimation = &idleAnimDown;
			}
		}
	}
}

void Player::CameraToPlayer() {
	app->render->camera.x = -position.x * app->win->GetScale() + app->win->GetWidth() / 2 - (currentAnimation->GetCurrentFrame().w /2) * app->win->GetScale();
	app->render->camera.y = -position.y * app->win->GetScale() + app->win->GetHeight() / 2 - (currentAnimation->GetCurrentFrame().h / 2) * app->win->GetScale();
}