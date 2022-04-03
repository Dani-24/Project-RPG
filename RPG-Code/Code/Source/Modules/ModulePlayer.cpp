#include "App.h"
#include "Render.h"
#include "Textures.h"
#include "Input.h"
#include "ModulePlayer.h"
#include "Log.h"
#include "Window.h"
#include "Scene.h"

ModulePlayer::ModulePlayer(App* application, bool start_enabled) : Module(application, start_enabled)
{
	name.Create("player");

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
}

// Destructor
ModulePlayer::~ModulePlayer()
{}

bool ModulePlayer::Awake(pugi::xml_node& config)
{
	LOG("Init Image library, ta guapa la libreria de imagenes llamada player");
	bool ret = true;

	return ret;
}

bool ModulePlayer::Start()
{
	LOG("start Player");
	bool ret = true;

	PlayerMTex = app->tex->Load("Assets/sprites/MainCh/MainChM/Walk/MainChM.png");
	PlayerFTex = app->tex->Load("Assets/sprites/MainCh/MainChF/Walk/MainChF.png");

	currentAnimation = &idleAnimR; //player start with idle anim
	PlayerDirectionRight = 1;//if its 1, player will be looking at the right, if it's 2, player will be looking at the left
	PlayerDirectionUp = 0;
	PlayerErection = 1;

	position.x = app->win->GetWidth()/2;
	position.y = app->win->GetHeight() / 2;
	return ret;
}

bool ModulePlayer::PreUpdate()
{

	CameraToPlayer();

	return true;
}

bool ModulePlayer::Update(float dt) {
	bool ret = true;
	
	if (app->scene->pause == false) {

		if ((app->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN)) {
			PlayerErection = true;
		}
		if ((app->input->GetKey(SDL_SCANCODE_2) == KEY_DOWN)) {
			PlayerErection = false;
		}

		MovementPlayer(dt);

	}

	return ret;
}

bool ModulePlayer::PostUpdate()
{
	bool ret = true;

	SDL_Rect rect = currentAnimation->GetCurrentFrame();
	if (PlayerErection==true) {
		app->render->DrawTexture(PlayerMTex, position.x, position.y, &rect);
	}
	if(PlayerErection==false) {
		app->render->DrawTexture(PlayerFTex, position.x, position.y, &rect);
	}

	return true;
}

bool ModulePlayer::CleanUp() {
	
	app->tex->UnLoad(PlayerFTex);
	app->tex->UnLoad(PlayerMTex);

	currentAnimation = nullptr;

	return true;
}

void ModulePlayer::MovementPlayer(float dt) {
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
	if ((app->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT)){
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

void ModulePlayer::CameraToPlayer() {
	app->render->camera.x = -position.x * app->win->GetScale() + app->win->GetWidth() / 2;
	app->render->camera.y = -position.y * app->win->GetScale() + app->win->GetHeight() / 2;
}