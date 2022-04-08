#include "App.h"
#include "Render.h"
#include "Textures.h"
#include "Input.h"
#include "EnemyMovement.h"
#include "Log.h"
#include "Window.h"

EnemyMovement::EnemyMovement(App* application, bool start_enabled) : Module(application, start_enabled)
{
	name.Create("enemy");

	idleAnim.PushBack({0,0,25,30});
	idleAnim.PushBack({ 39,0,25,30 });
	idleAnim.PushBack({ 78,0,25,30 });
	idleAnim.PushBack({ 117,0,25,30 });
	idleAnim.PushBack({ 156,0,25,30 });
	idleAnim.PushBack({ 196,0,25,30 });
	idleAnim.PushBack({ 234,0,25,30 });
	idleAnim.PushBack({ 279,0,25,30 });
	idleAnim.loop = true;
	idleAnim.speed = 0.0001f;


	walkAnimR.PushBack({ 0,32,25,32 });
	walkAnimR.PushBack({ 39,32,25,32 });
	walkAnimR.PushBack({ 78,32,25,32 });
	walkAnimR.PushBack({ 117,32,25,32 });
	walkAnimR.PushBack({ 156,32,25,32 });
	walkAnimR.PushBack({ 196,32,25,32 });
	walkAnimR.PushBack({ 234,32,25,32 });
	walkAnimR.PushBack({ 279,32,25,32 });
	walkAnimR.loop = true;
	walkAnimR.speed = 0.006f;


	walkAnimL.PushBack({ 0,65,25,31 });
	walkAnimL.PushBack({ 39,65,25,31 });
	walkAnimL.PushBack({ 78,65,25,31 });
	walkAnimL.PushBack({ 117,65,25,31 });
	walkAnimL.PushBack({ 156,65,25,31 });
	walkAnimL.PushBack({ 196,65,25,31 });
	walkAnimL.PushBack({ 234,65,25,31 });
	walkAnimL.PushBack({ 279,65,25,31 });
	walkAnimL.loop = true;
	walkAnimL.speed = 0.006f;
}

//Destructor
EnemyMovement::~EnemyMovement()
{}

bool EnemyMovement::Awake(pugi::xml_node& config)
{
	LOG("Init Enemy Image librari");
	bool ret = true;

	return ret;
}

bool EnemyMovement::Start()
{
	LOG("Start Enemy");
	bool ret = true;

	// Kirbo negro ? donde tas?
	//EnemyTex = app->tex->Load("Assets/sprites/Enemigos/EnemyMovement/EnemyMovement.png");

	//currentAnimation = &idleAnim;

	position.x = 0;
	position.y = 0;

	return ret;
}

bool EnemyMovement::PreUpdate()
{
	return true;
}

bool EnemyMovement::Update(float dt)
{
	bool ret = true;
	
		/*idleAnim.Reset();
		currentAnimation = &idleAnim;*/
	
	return ret;
}

bool EnemyMovement::PostUpdate()
{
	bool ret = true;

	//SDL_Rect rect = currentAnimation->GetCurrentFrame();
	//app->render->DrawTexture(EnemyTex, position.x, position.y, &rect);
	return true;
}

bool EnemyMovement::CleanUp()
{
	//app->tex->UnLoad(EnemyTex);

	currentAnimation = nullptr;

	return true;
}