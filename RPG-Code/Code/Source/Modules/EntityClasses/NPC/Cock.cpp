#include "App.h"
#include "Render.h"
#include "Audio.h"
#include "Textures.h"
#include "Input.h"
#include "Log.h"
#include "Window.h"
#include "Scene.h"

#include "EntityManager.h"
#include "Entity.h"
#include "DynamicEntity.h"
#include "NPC.h"
#include "Cock.h"


Cock::Cock(NPCType type) : NPC(NPCType::COCK)
{
	

	//player start with idle anim
	currentAnimation = &idleAnim; 

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

	//CockTex = app->tex->Load("Assets/sprites/npc/Taberna/chicken.png");



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
	//app->render->DrawTexture(CockTex, position.x, position.y, &rect);

	return true;
}

bool Cock::CleanUp() {

	//app->tex->UnLoad(CockTex);

	currentAnimation = nullptr;

	return true;
}