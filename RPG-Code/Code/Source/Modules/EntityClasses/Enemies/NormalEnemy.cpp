#include "EntityManager.h"

#include "Entity.h"
#include "DynamicEntity.h"
#include "Enemy.h"
#include "NormalEnemy.h"
#include "Scene.h"
#include "PauseMenu.h"

NormalEnemy::NormalEnemy(NormalEnemyType normalEnemyType, int x, int y) : Enemy(EnemyType::NORMAL)
{
	position = { x, y };
	this->normalEnemyType = normalEnemyType;

	switch (normalEnemyType) {
	case NormalEnemyType::FLYING_EYE:

		idleAnim.PushBack({ 0 , 0 , 150 , 101 });
		idleAnim.PushBack({ 150 , 0 , 150 , 101 });
		idleAnim.PushBack({ 300 , 0 , 150 , 101 });
		idleAnim.PushBack({ 450 , 0 , 150 , 101 });
		idleAnim.PushBack({ 600 , 0 , 150 , 101 });
		idleAnim.PushBack({ 750 , 0 , 150 , 101 });
		idleAnim.PushBack({ 900 , 0 , 150 , 101 });
		idleAnim.PushBack({ 1050 , 0 , 150 , 101 });
		idleAnim.loop = true;
		idleAnim.speed = 0.01f;

		walkAnim.PushBack({ 0 , 0 , 150 , 101 });
		walkAnim.PushBack({ 150 , 0 , 150 , 101 });
		walkAnim.PushBack({ 300 , 0 , 150 , 101 });
		walkAnim.PushBack({ 450 , 0 , 150 , 101 });
		walkAnim.PushBack({ 600 , 0 , 150 , 101 });
		walkAnim.PushBack({ 750 , 0 , 150 , 101 });
		walkAnim.PushBack({ 900 , 0 , 150 , 101 });
		walkAnim.PushBack({ 1050 , 0 , 150 , 101 });
		walkAnim.loop = true;
		walkAnim.speed = 0.01f;

		idleAnimL.PushBack({ 1050 , 566 , 150 , 101 });
		idleAnimL.PushBack({ 900 , 566 , 150 , 101 });
		idleAnimL.PushBack({ 750 , 566 , 150 , 101 });
		idleAnimL.PushBack({ 600 , 566 , 150 , 101 });
		idleAnimL.PushBack({ 450 , 566 , 150 , 101 });
		idleAnimL.PushBack({ 300 , 566 , 150 , 101 });
		idleAnimL.PushBack({ 150 , 566 , 150 , 101 });
		idleAnimL.PushBack({ 0 , 566 , 150 , 101 });
		idleAnimL.loop = true;
		idleAnimL.speed = 0.01f;

		walkAnimL.PushBack({ 1050 , 566 , 150 , 101 });
		walkAnimL.PushBack({ 900 , 566 , 150 , 101 });
		walkAnimL.PushBack({ 750 , 566 , 150 , 101 });
		walkAnimL.PushBack({ 600 , 566 , 150 , 101 });
		walkAnimL.PushBack({ 450 , 566 , 150 , 101 });
		walkAnimL.PushBack({ 300 , 566 , 150 , 101 });
		walkAnimL.PushBack({ 150 , 566 , 150 , 101 });
		walkAnimL.PushBack({ 0 , 566 , 150 , 101 });
		walkAnimL.loop = true;
		walkAnimL.speed = 0.01f;

		battleAnim.PushBack({ 1050 , 566 , 150 , 101 });
		battleAnim.PushBack({ 900 , 566 , 150 , 101 });
		battleAnim.PushBack({ 750 , 566 , 150 , 101 });
		battleAnim.PushBack({ 600 , 566 , 150 , 101 });
		battleAnim.PushBack({ 450 , 566 , 150 , 101 });
		battleAnim.PushBack({ 300 , 566 , 150 , 101 });
		battleAnim.PushBack({ 150 , 566 , 150 , 101 });
		battleAnim.PushBack({ 0 , 566 , 150 , 101 });
		battleAnim.loop = true;
		battleAnim.speed = 0.01f;

		attackAnim.PushBack({ 1050 , 667 , 150 , 101 });
		attackAnim.PushBack({ 900 , 667 , 150 , 101 });
		attackAnim.PushBack({ 750 , 667 , 150 , 101 });
		attackAnim.PushBack({ 600 , 667 , 150 , 101 });
		attackAnim.PushBack({ 450 , 667 , 150 , 101 });
		attackAnim.PushBack({ 300 , 667 , 150 , 101 });
		attackAnim.PushBack({ 150 , 667 , 150 , 101 });
		attackAnim.PushBack({ 0 , 667 , 150 , 101 });
		attackAnim.PushBack({ 1050 , 566 , 150 , 101 });
		attackAnim.PushBack({ 900 , 566 , 150 , 101 });
		attackAnim.PushBack({ 750 , 566 , 150 , 101 });
		attackAnim.PushBack({ 600 , 566 , 150 , 101 });
		attackAnim.PushBack({ 450 , 566 , 150 , 101 });
		attackAnim.PushBack({ 300 , 566 , 150 , 101 });
		attackAnim.PushBack({ 150 , 566 , 150 , 101 });
		attackAnim.PushBack({ 0 , 566 , 150 , 101 });
		attackAnim.loop = false;
		attackAnim.speed = 0.01f;

		attackAnim2.PushBack({ 1050 , 768 , 150 , 101 });
		attackAnim2.PushBack({ 900 , 768 , 150 , 101 });
		attackAnim2.PushBack({ 750 , 768 , 150 , 101 });
		attackAnim2.PushBack({ 600 , 768 , 150 , 101 });
		attackAnim2.PushBack({ 450 , 768 , 150 , 101 });
		attackAnim2.PushBack({ 300 , 768 , 150 , 101 });
		attackAnim2.PushBack({ 150 , 768 , 150 , 101 });
		attackAnim2.PushBack({ 0 , 768 , 150 , 101 });
		attackAnim2.PushBack({ 1050 , 566 , 150 , 101 });
		attackAnim2.PushBack({ 900 , 566 , 150 , 101 });
		attackAnim2.PushBack({ 750 , 566 , 150 , 101 });
		attackAnim2.PushBack({ 600 , 566 , 150 , 101 });
		attackAnim2.PushBack({ 450 , 566 , 150 , 101 });
		attackAnim2.PushBack({ 300 , 566 , 150 , 101 });
		attackAnim2.PushBack({ 150 , 566 , 150 , 101 });
		attackAnim2.PushBack({ 0 , 566 , 150 , 101 });
		attackAnim2.loop = false;
		attackAnim2.speed = 0.01f;

		attackAnim3.PushBack({ 1050 , 869 , 150 , 101 });
		attackAnim3.PushBack({ 900 , 869 , 150 , 101 });
		attackAnim3.PushBack({ 750 , 869 , 150 , 101 });
		attackAnim3.PushBack({ 600 , 869 , 150 , 101 });
		attackAnim3.PushBack({ 450 , 869 , 150 , 101 });
		attackAnim3.PushBack({ 300 , 869 , 150 , 101 });
		attackAnim3.PushBack({ 1050 , 566 , 150 , 101 });
		attackAnim3.PushBack({ 900 , 566 , 150 , 101 });
		attackAnim3.PushBack({ 750 , 566 , 150 , 101 });
		attackAnim3.PushBack({ 600 , 566 , 150 , 101 });
		attackAnim3.PushBack({ 450 , 566 , 150 , 101 });
		attackAnim3.PushBack({ 300 , 566 , 150 , 101 });
		attackAnim3.PushBack({ 150 , 566 , 150 , 101 });
		attackAnim3.PushBack({ 0 , 566 , 150 , 101 });
		attackAnim3.loop = false;
		attackAnim3.speed = 0.01f;

		protectAnim.PushBack({ 900 , 869 , 150 , 101 });
		protectAnim.PushBack({ 900 , 869 , 150 , 101 });
		protectAnim.PushBack({ 900 , 869 , 150 , 101 });
		protectAnim.PushBack({ 900 , 869 , 150 , 101 });
		protectAnim.PushBack({ 900 , 872 , 150 , 101 });
		protectAnim.PushBack({ 900 , 872 , 150 , 101 });
		protectAnim.PushBack({ 900 , 874 , 150 , 101 });
		protectAnim.PushBack({ 900 , 874 , 150 , 101 });
		protectAnim.PushBack({ 900 , 874 , 150 , 101 });
		protectAnim.PushBack({ 900 , 874 , 150 , 101 });
		protectAnim.PushBack({ 900 , 872 , 150 , 101 });
		protectAnim.PushBack({ 900 , 872 , 150 , 101 });
		protectAnim.loop = true;
		protectAnim.speed = 0.01f;

		hitAnim.PushBack({ 1050 , 970 , 150 , 101 });
		hitAnim.PushBack({ 900 , 970 , 150 , 101 });
		hitAnim.PushBack({ 750 , 970 , 150 , 101 });
		hitAnim.PushBack({ 600 , 970 , 150 , 101 });
		hitAnim.loop = true;
		hitAnim.speed = 0.01f;

		dieAnim.PushBack({ 1050 , 1071 , 150 , 101 });
		dieAnim.PushBack({ 900 , 1071 , 150 , 101 });
		dieAnim.PushBack({ 750 , 1071 , 150 , 101 });
		dieAnim.PushBack({ 600 , 1071 , 150 , 101 });
		dieAnim.loop = false;
		dieAnim.speed = 0.006f;

		baseCollider = app->collisions->AddCollider({ position.x + 56, position.y + 60, 47, 43 }, Collider::Type::INSTANT, this);

		currentAnimation = &idleAnimL;

		name = "Flying eye";
		configName = "flying_eye";

		break;

	case NormalEnemyType::BAT:
		idleAnim.PushBack({ 0 , 24 , 16 , 16 });
		idleAnim.PushBack({ 16 , 24 , 16 , 16 });
		idleAnim.PushBack({ 32 , 24 , 16 , 16 });
		idleAnim.PushBack({ 48 , 24 , 16 , 16 });
		idleAnim.PushBack({ 64 , 24 , 16 , 16 });
		idleAnim.loop = true;
		idleAnim.speed = 0.01f;

		walkAnim.PushBack({ 0 , 24 , 16 , 16 });
		walkAnim.PushBack({ 16 , 24 , 16 , 16 });
		walkAnim.PushBack({ 32 , 24 , 16 , 16 });
		walkAnim.PushBack({ 48 , 24 , 16 , 16 });
		walkAnim.PushBack({ 64 , 24 , 16 , 16 });
		walkAnim.loop = true;
		walkAnim.speed = 0.01f;

		idleAnimL.PushBack({ 64 , 95 , 16 , 16 });
		idleAnimL.PushBack({ 48 , 95 , 16 , 16 });
		idleAnimL.PushBack({ 32 , 95 , 16 , 16 });
		idleAnimL.PushBack({ 16 , 95 , 16 , 16 });
		idleAnimL.PushBack({ 0 , 95 , 16 , 16 });
		idleAnimL.loop = true;
		idleAnimL.speed = 0.01f;

		walkAnimL.PushBack({ 64 , 95 , 16 , 16 });
		walkAnimL.PushBack({ 48 , 95 , 16 , 16 });
		walkAnimL.PushBack({ 32 , 95 , 16 , 16 });
		walkAnimL.PushBack({ 16 , 95 , 16 , 16 });
		walkAnimL.PushBack({ 0 , 95 , 16 , 16 });
		walkAnimL.loop = true;
		walkAnimL.speed = 0.01f;

		battleAnim.PushBack({ 64 , 71 , 16 , 16 });
		battleAnim.PushBack({ 48 , 71 , 16 , 16 });
		battleAnim.PushBack({ 32 , 71 , 16 , 16 });
		battleAnim.PushBack({ 16 , 71 , 16 , 16 });
		battleAnim.PushBack({ 0 , 71 , 16 , 16 });
		battleAnim.loop = true;
		battleAnim.speed = 0.02f;

		attackAnim.PushBack({ 64 , 71 , 16 , 16 });
		attackAnim.PushBack({ 48 , 71 , 16 , 16 });
		attackAnim.PushBack({ 32 , 71 , 16 , 16 });
		attackAnim.PushBack({ 16 , 71 , 16 , 16 });
		attackAnim.PushBack({ 0 , 71 , 16 , 16 });
		attackAnim.loop = true;
		attackAnim.speed = 0.02f;

		attackAnim2.PushBack({ 64 , 71 , 16 , 16 });
		attackAnim2.PushBack({ 48 , 71 , 16 , 16 });
		attackAnim2.PushBack({ 32 , 71 , 16 , 16 });
		attackAnim2.PushBack({ 16 , 71 , 16 , 16 });
		attackAnim2.PushBack({ 0 , 71 , 16 , 16 });
		attackAnim2.loop = true;
		attackAnim2.speed = 0.02f;

		attackAnim3.PushBack({ 64 , 71 , 16 , 16 });
		attackAnim3.PushBack({ 48 , 71 , 16 , 16 });
		attackAnim3.PushBack({ 32 , 71 , 16 , 16 });
		attackAnim3.PushBack({ 16 , 71 , 16 , 16 });
		attackAnim3.PushBack({ 0 , 71 , 16 , 16 });
		attackAnim3.loop = true;
		attackAnim3.speed = 0.02f;

		protectAnim.PushBack({ 64 , 71 , 16 , 16 });
		protectAnim.PushBack({ 48 , 71 , 16 , 16 });
		protectAnim.PushBack({ 32 , 71 , 16 , 16 });
		protectAnim.PushBack({ 16 , 71 , 16 , 16 });
		protectAnim.PushBack({ 0 , 71 , 16 , 16 });
		protectAnim.loop = true;
		protectAnim.speed = 0.02f;

		hitAnim.PushBack({ 64 , 95 , 16 , 16 });
		hitAnim.PushBack({ 48 , 95 , 16 , 16 });
		hitAnim.PushBack({ 32 , 95 , 16 , 16 });
		hitAnim.PushBack({ 16 , 95 , 16 , 16 });
		hitAnim.PushBack({ 0 , 95 , 16 , 16 });
		hitAnim.loop = true;
		hitAnim.speed = 0.02f;

		dieAnim.PushBack({ 64 , 120 , 16 , 23 });
		dieAnim.PushBack({ 48 , 120 , 16 , 23 });
		dieAnim.PushBack({ 32 , 120 , 16 , 23 });
		dieAnim.PushBack({ 16 , 120 , 16 , 23 });
		dieAnim.PushBack({ 0 , 120 , 16 , 23 });
		dieAnim.loop = false;
		dieAnim.speed = 0.006f;

		baseCollider = app->collisions->AddCollider({ position.x, position.y, 16, 16 }, Collider::Type::INSTANT, this);

		currentAnimation = &idleAnimL;

		name = "Bat";
		configName = "bat";

		break;

	case NormalEnemyType::SKELETON:
		idleAnim.PushBack({ 0 , 0 , 150 , 101 });
		idleAnim.PushBack({ 150 , 0 , 150 , 101 });
		idleAnim.PushBack({ 300 , 0 , 150 , 101 });
		idleAnim.PushBack({ 450 , 0 , 150 , 101 });
		idleAnim.loop = true;
		idleAnim.speed = 0.01f;

		walkAnim.PushBack({ 0 , 101 , 150 , 101 });
		walkAnim.PushBack({ 150 , 101 , 150 , 101 });
		walkAnim.PushBack({ 300 , 101 , 150 , 101 });
		walkAnim.PushBack({ 450 , 101 , 150 , 101 });
		walkAnim.loop = true;
		walkAnim.speed = 0.01f;

		idleAnimL.PushBack({ 1050 , 810 , 150 , 101 });
		idleAnimL.PushBack({ 900 , 810 , 150 , 101 });
		idleAnimL.PushBack({ 750 , 810 , 150 , 101 });
		idleAnimL.PushBack({ 600 , 810 , 150 , 101 });
		idleAnimL.loop = true;
		idleAnimL.speed = 0.01f;

		walkAnimL.PushBack({ 1050 , 911 , 150 , 101 });
		walkAnimL.PushBack({ 900 , 911 , 150 , 101 });
		walkAnimL.PushBack({ 750 , 911 , 150 , 101 });
		walkAnimL.PushBack({ 600 , 911 , 150 , 101 });
		walkAnimL.loop = true;
		walkAnimL.speed = 0.01f;

		battleAnim.PushBack({ 1050 , 810 , 150 , 101 });
		battleAnim.PushBack({ 900 , 810 , 150 , 101 });
		battleAnim.PushBack({ 750 , 810 , 150 , 101 });
		battleAnim.PushBack({ 600 , 810 , 150 , 101 });
		battleAnim.loop = true;
		battleAnim.speed = 0.01f;

		attackAnim.PushBack({ 1050 , 1012 , 150 , 101 });
		attackAnim.PushBack({ 900 , 1012 , 150 , 101 });
		attackAnim.PushBack({ 750 , 1012 , 150 , 101 });
		attackAnim.PushBack({ 600 , 1012 , 150 , 101 });
		attackAnim.PushBack({ 450 , 1012 , 150 , 101 });
		attackAnim.PushBack({ 300 , 1012 , 150 , 101 });
		attackAnim.PushBack({ 150 , 1012 , 150 , 101 });
		attackAnim.PushBack({ 0 , 1012 , 150 , 101 });
		attackAnim.PushBack({ 1050 , 810 , 150 , 101 });
		attackAnim.PushBack({ 900 , 810 , 150 , 101 });
		attackAnim.PushBack({ 750 , 810 , 150 , 101 });
		attackAnim.PushBack({ 600 , 810 , 150 , 101 });
		attackAnim.loop = false;
		attackAnim.speed = 0.01f;

		attackAnim2.PushBack({ 1050 , 1113 , 150 , 101 });
		attackAnim2.PushBack({ 900 , 1113 , 150 , 101 });
		attackAnim2.PushBack({ 750 , 1113 , 150 , 101 });
		attackAnim2.PushBack({ 600 , 1113 , 150 , 101 });
		attackAnim2.PushBack({ 450 , 1113 , 150 , 101 });
		attackAnim2.PushBack({ 300 , 1113 , 150 , 101 });
		attackAnim2.PushBack({ 150 , 1113 , 150 , 101 });
		attackAnim2.PushBack({ 0 , 1113 , 150 , 101 });
		attackAnim2.PushBack({ 1050 , 810 , 150 , 101 });
		attackAnim2.PushBack({ 900 , 810 , 150 , 101 });
		attackAnim2.PushBack({ 750 , 810 , 150 , 101 });
		attackAnim2.PushBack({ 600 , 810 , 150 , 101 });
		attackAnim2.loop = false;
		attackAnim2.speed = 0.01f;

		attackAnim3.PushBack({ 1050 , 1214 , 150 , 101 });
		attackAnim3.PushBack({ 900 , 1214 , 150 , 101 });
		attackAnim3.PushBack({ 750 , 1214 , 150 , 101 });
		attackAnim3.PushBack({ 600 , 1214 , 150 , 101 });
		attackAnim3.PushBack({ 450 , 1214 , 150 , 101 });
		attackAnim3.PushBack({ 300 , 1214 , 150 , 101 });
		attackAnim3.PushBack({ 1050 , 810 , 150 , 101 });
		attackAnim3.PushBack({ 900 , 810 , 150 , 101 });
		attackAnim3.PushBack({ 750 , 810 , 150 , 101 });
		attackAnim3.PushBack({ 600 , 810 , 150 , 101 });
		attackAnim3.loop = false;
		attackAnim3.speed = 0.01f;

		protectAnim.PushBack({ 1050 , 1315 , 150 , 101 });
		protectAnim.PushBack({ 900 , 1315 , 150 , 101 });
		protectAnim.PushBack({ 750 , 1315 , 150 , 101 });
		protectAnim.PushBack({ 600 , 1315 , 150 , 101 });
		protectAnim.loop = false;
		protectAnim.speed = 0.01f;

		hitAnim.PushBack({ 1050 , 1416 , 150 , 101 });
		hitAnim.PushBack({ 900 , 1416 , 150 , 101 });
		hitAnim.PushBack({ 750 , 1416 , 150 , 101 });
		hitAnim.PushBack({ 600 , 1416 , 150 , 101 });
		hitAnim.loop = true;
		hitAnim.speed = 0.01f;

		dieAnim.PushBack({ 1050 , 1517 , 150 , 101 });
		dieAnim.PushBack({ 900 , 1517 , 150 , 101 });
		dieAnim.PushBack({ 750 , 1517 , 150 , 101 });
		dieAnim.PushBack({ 600 , 1517 , 150 , 101 });
		dieAnim.loop = false;
		dieAnim.speed = 0.01f;

		baseCollider = app->collisions->AddCollider({ position.x + 60, position.y + 50, 45, 51 }, Collider::Type::INSTANT, this);

		currentAnimation = &idleAnimL;

		name = "Skeleton";
		configName = "skeleton";

		break;

	default:
		break;
	}

	isAlive = true;

	NormalEnemyID = app->scene->normalEnemyList.count();
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

		spriteText = app->tex->Load("Assets/sprites/enemies/flying_eye/eyeSprite.png");

		stats = new Stats(1, 10, 3, 3, 3, 18);

		break;
	case NormalEnemyType::BAT:

		spriteText = app->tex->Load("Assets/sprites/enemies/bat/bat.png");

		stats = new Stats(1, 5, 10, 1, 1, 27);

		break;
	case NormalEnemyType::SKELETON:

		spriteText = app->tex->Load("Assets/sprites/enemies/skeleton/skeletonSprite.png");

		/*stats = new Stats(1, 15, 6, 5, 1, 10);*/
		stats = new Stats(1, 15,70, 5, 1, 18);

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
	if (!app->pauseM->pauseGame) {
		if (currentAnimation != nullptr) {
			currentAnimation->Update(dt);
		}
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