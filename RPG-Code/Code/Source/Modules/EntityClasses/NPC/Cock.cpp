#include"Cock.h"

#include "App.h"
#include "Render.h"
#include "Audio.h"
#include "Textures.h"
#include "Input.h"
#include "NPCEntity.h"
#include "Log.h"
#include "Window.h"
#include "Scene.h"

Cock::Cock() : NPC(NPCType::COCK)
{

	idleAnim.PushBack({ 2, 2, 28, 28 });
		idleAnim.PushBack({ 32, 2, 30, 28 });
		idleAnim.PushBack({ 66, 2, 28, 28 });
		idleAnim.PushBack({ 96, 2, 30, 28 });

		currentAnimation = &idleAnim; //player start with idle anim

		configName = "cock";

		position.x = 950;
		position.y = 950;

	
}
Cock::Cock() : NPC(NPCType::BARKEEPER)
{

	idleAnim.PushBack({ 2, 2, 28, 28 });
	idleAnim.PushBack({ 32, 2, 30, 28 });
	idleAnim.PushBack({ 66, 2, 28, 28 });
	idleAnim.PushBack({ 96, 2, 30, 28 });

	currentAnimation = &idleAnim; //player start with idle anim

	configName = "barkeeper";

	position.x = 950;
	position.y = 950;


}
Cock::Cock() : NPC(NPCType::MERCHANT)
{

	idleAnim.PushBack({ 2, 2, 28, 28 });
	idleAnim.PushBack({ 32, 2, 30, 28 });
	idleAnim.PushBack({ 66, 2, 28, 28 });
	idleAnim.PushBack({ 96, 2, 30, 28 });

	currentAnimation = &idleAnim; //player start with idle anim

	configName = "merchant";

	position.x = 950;
	position.y = 950;


}
Cock::Cock() : NPC(NPCType::TRAINER)
{

	idleAnim.PushBack({ 2, 2, 28, 28 });
	idleAnim.PushBack({ 32, 2, 30, 28 });
	idleAnim.PushBack({ 66, 2, 28, 28 });
	idleAnim.PushBack({ 96, 2, 30, 28 });

	currentAnimation = &idleAnim; //player start with idle anim

	configName = "trainer";

	position.x = 950;
	position.y = 950;


}
// Destructor
Cock::~Cock()
{}

bool Cock::Awake(pugi::xml_node& config)
{
	LOG("cockkkkk");
	bool ret = true;
	LOG("Num in config: %d", config.child("exampleNumber").attribute("num").as_int());


	return ret;
}

bool Cock::Start()
{
	LOG("start cock");
	bool ret = true;

	CockTex = app->tex->Load("Assets/sprites/npc/Taberna/chicken.png");



	return ret;
}

bool Cock::PreUpdate()
{

	//LOG("Player position X:%d Y:%d", position.x, position.y);

	return true;
}

bool Cock::Update(float dt) {
	bool ret = true;

	currentAnimation->Update(dt);



	return ret;
}

bool Cock::PostUpdate()
{
	bool ret = true;
	SDL_Rect rect = currentAnimation->GetCurrentFrame();
	app->render->DrawTexture(CockTex, position.x, position.y, &rect);

	return true;
}

bool Cock::CleanUp() {

	app->tex->UnLoad(CockTex);

	currentAnimation = nullptr;

	return true;
}