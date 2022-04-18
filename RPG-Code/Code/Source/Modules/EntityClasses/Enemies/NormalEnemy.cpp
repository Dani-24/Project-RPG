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

		idleAnim.PushBack({ 44 , 0 , 44 , 32 });
		idleAnim.PushBack({ 44 , 0 , 44 , 32 });
		idleAnim.PushBack({ 44 , 0 , 44 , 32 });
		idleAnim.PushBack({ 44 , 0 , 44 , 32 });
		idleAnim.PushBack({ 44 , 3 , 44 , 32 });
		idleAnim.PushBack({ 44 , 3 , 44 , 32 });
		idleAnim.PushBack({ 44 , 5 , 44 , 32 });
		idleAnim.PushBack({ 44 , 5 , 44 , 32 });
		idleAnim.PushBack({ 44 , 5 , 44 , 32 });
		idleAnim.PushBack({ 44 , 5 , 44 , 32 });
		idleAnim.PushBack({ 44 , 3 , 44 , 32 });
		idleAnim.PushBack({ 44 , 3 , 44 , 32 });
		idleAnim.loop = true;
		idleAnim.speed = 0.006f;

		idleAnimL.PushBack({ 242 , 102 , 44 , 32 });
		idleAnimL.PushBack({ 242 , 102 , 44 , 32 });
		idleAnimL.PushBack({ 242 , 102 , 44 , 32 });
		idleAnimL.PushBack({ 242 , 102 , 44 , 32 });
		idleAnimL.PushBack({ 242 , 105 , 44 , 32 });
		idleAnimL.PushBack({ 242 , 105 , 44 , 32 });
		idleAnimL.PushBack({ 242 , 107 , 44 , 32 });
		idleAnimL.PushBack({ 242 , 107 , 44 , 32 });
		idleAnimL.PushBack({ 242 , 107 , 44 , 32 });
		idleAnimL.PushBack({ 242 , 107 , 44 , 32 });
		idleAnimL.PushBack({ 242 , 105 , 44 , 32 });
		idleAnimL.PushBack({ 242 , 105 , 44 , 32 });
		idleAnimL.loop = true;
		idleAnimL.speed = 0.006f;

		battleAnim.PushBack({ 286 , 102 , 44 , 32 });
		battleAnim.PushBack({ 286 , 102 , 44 , 32 });
		battleAnim.PushBack({ 286 , 102 , 44 , 32 });
		battleAnim.PushBack({ 286 , 102 , 44 , 32 });
		battleAnim.PushBack({ 286 , 105 , 44 , 32 });
		battleAnim.PushBack({ 286 , 105 , 44 , 32 });
		battleAnim.PushBack({ 286 , 107 , 44 , 32 });
		battleAnim.PushBack({ 286 , 107 , 44 , 32 });
		battleAnim.PushBack({ 286 , 107 , 44 , 32 });
		battleAnim.PushBack({ 286 , 107 , 44 , 32 });
		battleAnim.PushBack({ 286 , 105 , 44 , 32 });
		battleAnim.PushBack({ 286 , 105 , 44 , 32 });
		battleAnim.loop = true;
		battleAnim.speed = 0.006f;

		attackAnim.PushBack({ 286 , 102 , 44 , 32 });
		attackAnim.PushBack({ 242 , 102 , 44 , 32 });
		attackAnim.PushBack({ 198 , 102 , 44 , 32 });
		attackAnim.PushBack({ 154 , 102 , 44 , 32 });
		attackAnim.PushBack({ 110 , 102 , 44 , 32 });
		attackAnim.PushBack({ 66 , 102 , 44 , 32 });
		attackAnim.loop = true;
		attackAnim.speed = 0.006f;

		dieAnim.PushBack({ 0 , 59 , 44 , 43 });
		dieAnim.PushBack({ 44 , 59 , 44 , 43 });
		dieAnim.PushBack({ 88 , 59 , 44 , 43 });
		dieAnim.PushBack({ 132 , 59 , 44 , 43 });
		dieAnim.PushBack({ 176 , 59 , 44 , 43 });
		dieAnim.PushBack({ 220 , 59 , 44 , 43 });
		dieAnim.PushBack({ 264 , 59 , 44 , 43 });
		dieAnim.PushBack({ 308 , 59 , 44 , 43 });
		dieAnim.loop = true;
		dieAnim.speed = 0.006f;

		baseCollider = app->collisions->AddCollider({ position.x, position.y, 25, 32 }, Collider::Type::INSTANT, this);

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

		idleAnimL.PushBack({ 64 , 95 , 16 , 16 });
		idleAnimL.PushBack({ 48 , 95 , 16 , 16 });
		idleAnimL.PushBack({ 32 , 95 , 16 , 16 });
		idleAnimL.PushBack({ 16 , 95 , 16 , 16 });
		idleAnimL.PushBack({ 0 , 95 , 16 , 16 });
		idleAnimL.loop = true;
		idleAnimL.speed = 0.01f;

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

		dieAnim.PushBack({ 64 , 120 , 16 , 23 });
		dieAnim.PushBack({ 48 , 120 , 16 , 23 });
		dieAnim.PushBack({ 32 , 120 , 16 , 23 });
		dieAnim.PushBack({ 16 , 120 , 16 , 23 });
		dieAnim.PushBack({ 0 , 120 , 16 , 23 });
		dieAnim.loop = true;
		dieAnim.speed = 0.006f;

		baseCollider = app->collisions->AddCollider({ position.x, position.y, 16, 16 }, Collider::Type::INSTANT, this);

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

		battleAnim.PushBack({ 1050 , 810 , 150 , 101 });
		battleAnim.PushBack({ 900 , 810 , 150 , 101 });
		battleAnim.PushBack({ 750 , 810 , 150 , 101 });
		battleAnim.PushBack({ 600 , 810 , 150 , 101 });
		battleAnim.loop = true;
		battleAnim.speed = 0.01f;

		walkAnimL.PushBack({ 1050 , 911 , 150 , 101 });
		walkAnimL.PushBack({ 900 , 911 , 150 , 101 });
		walkAnimL.PushBack({ 750 , 911 , 150 , 101 });
		walkAnimL.PushBack({ 600 , 911 , 150 , 101 });
		walkAnimL.loop = true;
		walkAnimL.speed = 0.01f;

		attackAnim.PushBack({ 1050 , 1012 , 150 , 101 });
		attackAnim.PushBack({ 900 , 1012 , 150 , 101 });
		attackAnim.PushBack({ 750 , 1012 , 150 , 101 });
		attackAnim.PushBack({ 600 , 1012 , 150 , 101 });
		attackAnim.PushBack({ 450 , 1012 , 150 , 101 });
		attackAnim.PushBack({ 300 , 1012 , 150 , 101 });
		attackAnim.PushBack({ 150 , 1012 , 150 , 101 });
		attackAnim.PushBack({ 0 , 1012 , 150 , 101 });
		//attackAnim.loop = true;
		attackAnim.speed = 0.01f;

		attackAnim2.PushBack({ 1050 , 1113 , 150 , 101 });
		attackAnim2.PushBack({ 900 , 1113 , 150 , 101 });
		attackAnim2.PushBack({ 750 , 1113 , 150 , 101 });
		attackAnim2.PushBack({ 600 , 1113 , 150 , 101 });
		attackAnim2.PushBack({ 450 , 1113 , 150 , 101 });
		attackAnim2.PushBack({ 300 , 1113 , 150 , 101 });
		attackAnim2.PushBack({ 150 , 1113 , 150 , 101 });
		attackAnim2.PushBack({ 0 , 1113 , 150 , 101 });
		attackAnim2.loop = true;
		attackAnim2.speed = 0.01f;

		attackAnim3.PushBack({ 1050 , 1214 , 150 , 101 });
		attackAnim3.PushBack({ 900 , 1214 , 150 , 101 });
		attackAnim3.PushBack({ 750 , 1214 , 150 , 101 });
		attackAnim3.PushBack({ 600 , 1214 , 150 , 101 });
		attackAnim3.PushBack({ 450 , 1214 , 150 , 101 });
		attackAnim3.PushBack({ 300 , 1214 , 150 , 101 });
		attackAnim3.loop = true;
		attackAnim3.speed = 0.01f;

		protectAnim.PushBack({ 1050 , 1315 , 150 , 101 });
		protectAnim.PushBack({ 900 , 1315 , 150 , 101 });
		protectAnim.PushBack({ 750 , 1315 , 150 , 101 });
		protectAnim.PushBack({ 600 , 1315 , 150 , 101 });
		protectAnim.loop = true;
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
		dieAnim.loop = true;
		dieAnim.speed = 0.01f;

		baseCollider = app->collisions->AddCollider({ position.x + 60, position.y + 50, 45, 51 }, Collider::Type::INSTANT, this);

		name = "Skeleton";
		configName = "skeleton";

		break;

	default:
		break;
	}

	isAlive = true;

	currentAnimation = &idleAnim;

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

		spriteText = app->tex->Load("Assets/sprites/enemies/eye/eye.png");

		stats = new Stats(1, 10, 3, 3, 3, 18);

		break;
	case NormalEnemyType::BAT:

		spriteText = app->tex->Load("Assets/sprites/enemies/bat/bat.png");

		stats = new Stats(1, 5, 10, 1, 1, 27);

		break;
	case NormalEnemyType::SKELETON:

		spriteText = app->tex->Load("Assets/sprites/enemies/skeleton/skeletonSprite.png");

		stats = new Stats(1, 15, 6, 5, 1, 10);

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