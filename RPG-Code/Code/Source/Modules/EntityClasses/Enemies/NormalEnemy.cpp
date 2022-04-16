#include "EntityManager.h"

#include "Entity.h"
#include "DynamicEntity.h"
#include "Enemy.h"
#include "NormalEnemy.h"
#include "Scene.h"


NormalEnemy::NormalEnemy(NormalEnemyType normalEnemyType, int x, int y) : Enemy(EnemyType::NORMAL)
{
	position = { x, y };
	this->normalEnemyType = normalEnemyType;

	switch (normalEnemyType) {
	case NormalEnemyType::FLYING_EYE:
		idleAnim.PushBack({ 0 / 0 / 25 / 32 });
		idleAnim.PushBack({ 48 / 0 / 18 / 26 });
		idleAnim.PushBack({ 96 / 0 / 18 / 26 });
		idleAnim.PushBack({ 134 / 0 / 33 / 32 });
		idleAnim.PushBack({ 183 / 0 / 35 / 32 });
		idleAnim.PushBack({ 227 / 0 / 35 / 31 });
		idleAnim.loop = true;
		idleAnim.speed = 0.006f;

		baseCollider = app->collisions->AddCollider({ position.x, position.y, 25, 32 }, Collider::Type::BATTLE, this);

		break;

	case NormalEnemyType::BAT:
		idleAnim.PushBack({ 0 / 25 / 16 / 16 });
		idleAnim.PushBack({ 16 / 25 / 16 / 16 });
		idleAnim.PushBack({ 32 / 25 / 16 / 16 });
		idleAnim.PushBack({ 48 / 25 / 16 / 16 });
		idleAnim.PushBack({ 64 / 25 / 16 / 16 });
		idleAnim.loop = true;
		idleAnim.speed = 0.006f;

		baseCollider = app->collisions->AddCollider({ position.x, position.y, 16, 16 }, Collider::Type::BATTLE, this);

		break;

	default:
		break;
	}

	currentAnimation = &idleAnim;

	NormalEnemyID = app->scene->normalEnemyList.count();
	////--------------------------------------------- Flying Eye Animations -------------------------------------------
	//EyeAnimR.PushBack({ 0 / 0 / 25 / 32 });
	//EyeAnimR.PushBack({ 48 / 0 / 18 / 26 });
	//EyeAnimR.PushBack({ 96 / 0 / 18 / 26 });
	//EyeAnimR.PushBack({ 134 / 0 / 33 / 32 });
	//EyeAnimR.PushBack({ 183 / 0 / 35 / 32 });
	//EyeAnimR.PushBack({ 227 / 0 / 35 / 31 });
	//EyeAnimR.loop = true;
	//EyeAnimR.speed = 0.006f;

	//EyeAnimL.PushBack({ 227 / 101 / 35 / 31 });
	//EyeAnimL.PushBack({ 183 / 101 / 35 / 32 });
	//EyeAnimL.PushBack({ 134 / 101 / 33 / 32 });
	//EyeAnimL.PushBack({ 96 / 101 / 18 / 26 });
	//EyeAnimL.PushBack({ 48 / 101 / 18 / 26 });
	//EyeAnimL.PushBack({ 0 / 101 / 25 / 32 });
	//EyeAnimL.loop = true;
	//EyeAnimL.speed = 0.006f;

	//EyeAnimDieR.PushBack({ 0 / 59 / 16 / 43 });
	//EyeAnimDieR.PushBack({ 48 / 59 / 16 / 43 });
	//EyeAnimDieR.PushBack({ 96 / 59 / 16 / 43 });
	//EyeAnimDieR.PushBack({ 134 / 59 / 21 / 43 });
	//EyeAnimDieR.PushBack({ 183 / 59 / 30 / 43 });
	//EyeAnimDieR.PushBack({ 227 / 59 / 37 / 43 });
	//EyeAnimDieR.PushBack({ 273 / 59 / 57 / 43 });
	//EyeAnimDieR.loop = false;
	//EyeAnimDieR.speed = 0.006f;

	//EyeAnimDieL.PushBack({ 273 / 161 / 57 / 43 });
	//EyeAnimDieL.PushBack({ 227 / 161 / 37 / 43 });
	//EyeAnimDieL.PushBack({ 183 / 161 / 30 / 43 });
	//EyeAnimDieL.PushBack({ 134 / 161 / 21 / 43 });
	//EyeAnimDieL.PushBack({ 96 / 161 / 16 / 43 });
	//EyeAnimDieL.PushBack({ 48 / 161 / 16 / 43 });
	//EyeAnimDieL.PushBack({ 0 / 161 / 16 / 43 });
	//EyeAnimDieL.loop = false;
	//EyeAnimDieL.speed = 0.006f;

	////--------------------------------------------- Bat Animations -------------------------------------------

	//BatAnimR.PushBack({ 0 / 25 / 16 / 16 });
	//BatAnimR.PushBack({ 16 / 25 / 16 / 16 });
	//BatAnimR.PushBack({ 32 / 25 / 16 / 16 });
	//BatAnimR.PushBack({ 48 / 25 / 16 / 16 });
	//BatAnimR.PushBack({ 64 / 25 / 16 / 16 });
	//BatAnimR.loop = true;
	//BatAnimR.speed = 0.006f;

	//BatAnimL.PushBack({ 64 / 80 / 16 / 16 });
	//BatAnimL.PushBack({ 48 / 80 / 16 / 16 });
	//BatAnimL.PushBack({ 32 / 80 / 16 / 16 });
	//BatAnimL.PushBack({ 16 / 80 / 16 / 16 });
	//BatAnimL.PushBack({ 0 / 80 / 16 / 16 });
	//BatAnimL.loop = true;
	//BatAnimL.speed = 0.006f;

	//BatAnimDieR.PushBack({ 0 / 52 / 16 / 19 });
	//BatAnimDieR.PushBack({ 16 / 52 / 16 / 19 });
	//BatAnimDieR.PushBack({ 32 / 52 / 16 / 19 });
	//BatAnimDieR.PushBack({ 48 / 52 / 16 / 19 });
	//BatAnimDieR.PushBack({ 64 / 52 / 16 / 19 });
	//BatAnimDieR.loop = false;
	//BatAnimDieR.speed = 0.006f;

	//BatAnimDieL.PushBack({ 64 / 66 / 16 / 19 });
	//BatAnimDieL.PushBack({ 48 / 66 / 16 / 19 });
	//BatAnimDieL.PushBack({ 32 / 66 / 16 / 19 });
	//BatAnimDieL.PushBack({ 16 / 66 / 16 / 19 });
	//BatAnimDieL.PushBack({ 0 / 66 / 16 / 19 });
	//BatAnimDieL.loop = false;
	//BatAnimDieL.speed = 0.006f;
}

NormalEnemy::~NormalEnemy()
{}

bool NormalEnemy::Awake(pugi::xml_node& config)
{
	

	return true;
}

// Called before the first frame
bool NormalEnemy::Start()
{
	LOG("Start Normal Enemies variables");

	switch (normalEnemyType) {
	case NormalEnemyType::FLYING_EYE:

		spriteText = app->tex->Load("Assets/sprites/enemies/eye/eye.png");
		break;
	case NormalEnemyType::BAT:

		spriteText = app->tex->Load("Assets/sprites/enemies/bat/bat.png");
		break;

	default:
		break;
	}

	return true;
}



bool NormalEnemy::PreUpdate()
{
	
	return true;
}

// Call modules on each loop iteration
bool NormalEnemy::Update(float dt)
{
	if (currentAnimation != nullptr) {
		currentAnimation->Update(dt);
	}
	return true;
}

// Call modules after each loop iteration
bool NormalEnemy::PostUpdate()
{
	//Draw Enemy
	
	
	return true;
}

// Called before quitting
bool NormalEnemy::CleanUp()
{
	if (baseCollider != nullptr) {
		app->collisions->RemoveCollider(baseCollider);
	}


	baseCollider = nullptr;
	delete baseCollider;

	app->tex->UnLoad(spriteText);


	currentAnimation = nullptr;
	delete currentAnimation;

	return true;
}