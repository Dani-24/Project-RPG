#include "App.h"
#include "Render.h"
#include "Textures.h"
#include "Input.h"
#include "ModulePlayer.h"

ModulePlayer::ModulePlayer(App* application, bool start_enabled) : Module(application, start_enabled)
{
	name.Create("player");

	walkAnimDown.PushBack({ 3,1,27,31 });
	walkAnimDown.PushBack({ 36,1,27,31 });
	walkAnimDown.PushBack({ 68,1,27,31 });
	walkAnimDown.loop = true;
	walkAnimDown.speed = 0.1f;

	walkAnimUp.PushBack({ 3,97,27,31 });
	walkAnimUp.PushBack({ 35,1,27,31 });
	walkAnimUp.PushBack({ 67,1,27,31 });
	walkAnimUp.loop = true;
	walkAnimUp.speed = 0.1f;

	walkAnimL.PushBack({ 3,33,27,31 });
	walkAnimL.PushBack({ 36,32,27,32 });
	walkAnimL.PushBack({ 68,33,27,32 });
	walkAnimL.loop = true;
	walkAnimL.speed = 0.1f;

	walkAnimR.PushBack({ 3,65,27,32 });
	walkAnimR.PushBack({ 36,64,27,32 });
	walkAnimR.PushBack({ 67,65,27,32 });
	walkAnimR.loop = true;
	walkAnimR.speed = 0.1f;
}

// Destructor
ModulePlayer::~ModulePlayer()
{}