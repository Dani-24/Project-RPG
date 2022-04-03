#include "App.h"
#include "Render.h"
#include "Textures.h"
#include "Input.h"
#include "ModulePlayer.h"
#include "Log.h"

ModulePlayer::ModulePlayer(App* application, bool start_enabled) : Module(application, start_enabled)
{
	name.Create("player");

	walkAnimDown.PushBack({ 9,10,31,46 });
	walkAnimDown.PushBack({ 62,8,31,46 });
	walkAnimDown.PushBack({ 114,10,31,46 });
	walkAnimDown.loop = true;
	walkAnimDown.speed = 0.1f;

	walkAnimUp.PushBack({ 9,218,31,46 });
	walkAnimUp.PushBack({ 62,221,31,46 });
	walkAnimUp.PushBack({ 114,218,31,47 });
	walkAnimUp.loop = true;
	walkAnimUp.speed = 0.1f;

	walkAnimL.PushBack({ 11,82,26,44 });
	walkAnimL.PushBack({ 64,80,26,45 });
	walkAnimL.PushBack({ 116,82,27,44 });
	walkAnimL.loop = true;
	walkAnimL.speed = 0.1f;

	walkAnimR.PushBack({ 11,153,27,44 });
	walkAnimR.PushBack({ 64,150,27,44 });
	walkAnimR.PushBack({ 116,153,27,44 });
	walkAnimR.loop = true;
	walkAnimR.speed = 0.1f;
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

	currentAnimation = &walkAnimDown; //player start with idle anim
	PlayerDirectionRight = true;//if its true, player will be looking at the right, if not, player will be looking at the left
	PlayerDirectionUp = true;

	position.x = 70;
	position.y = 70;
	return ret;
}

bool ModulePlayer::PreUpdate()
{
	return true;
}

bool ModulePlayer::Update(float dt) {
	bool ret = true;

	
	MovementPlayer(dt);

	return ret;
}

bool ModulePlayer::PostUpdate()
{
	bool ret = true;

	Uint8 alpha = 80;

	SDL_Rect rect = currentAnimation->GetCurrentFrame();
	app->render->DrawTexture(PlayerMTex, position.x, position.y, &rect);

	return true;
}
void ModulePlayer::MovementPlayer(float dt) {
	float speed = 2 * dt * 0.09;

	if ((app->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT))
	{
		position.x += speed;
		if (currentAnimation != &walkAnimR)
		{
			walkAnimR.Reset();
			currentAnimation = &walkAnimR;
			PlayerDirectionRight = true;
		}

	}
	if ((app->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT))
	{
		position.x -= speed;
		if (currentAnimation != &walkAnimL)
		{
			walkAnimL.Reset();
			currentAnimation = &walkAnimL;
			PlayerDirectionRight = false;
		}
	}
	if ((app->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT)){
		position.y -= speed ;
		if (currentAnimation != &walkAnimUp)
		{
			walkAnimUp.Reset();
			currentAnimation = &walkAnimUp;
			PlayerDirectionUp = true;
		}
	}
	if ((app->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT)) {
		position.y += speed;
		if (currentAnimation != &walkAnimDown)
		{
			walkAnimDown.Reset();
			currentAnimation = &walkAnimDown;
			PlayerDirectionUp = false;
		}
	}

}