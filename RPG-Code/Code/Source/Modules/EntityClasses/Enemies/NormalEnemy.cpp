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

		idleAnim.PushBack({ 0 * BATTLE_SIZE , 0 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		idleAnim.PushBack({ 1 * BATTLE_SIZE , 0 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		idleAnim.PushBack({ 2 * BATTLE_SIZE , 0 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		idleAnim.PushBack({ 3 * BATTLE_SIZE , 0 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		idleAnim.PushBack({ 4 * BATTLE_SIZE , 0 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		idleAnim.PushBack({ 5 * BATTLE_SIZE , 0 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		idleAnim.PushBack({ 6 * BATTLE_SIZE , 0 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		idleAnim.PushBack({ 7 * BATTLE_SIZE , 0 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });

		idleAnim.loop = true;
		idleAnim.speed = 0.01f;

		walkAnim.PushBack({ 0 * BATTLE_SIZE , 0 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		walkAnim.PushBack({ 1 * BATTLE_SIZE , 0 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		walkAnim.PushBack({ 2 * BATTLE_SIZE , 0 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		walkAnim.PushBack({ 3 * BATTLE_SIZE , 0 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		walkAnim.PushBack({ 4 * BATTLE_SIZE , 0 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		walkAnim.PushBack({ 5 * BATTLE_SIZE , 0 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		walkAnim.PushBack({ 6 * BATTLE_SIZE , 0 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		walkAnim.PushBack({ 7 * BATTLE_SIZE , 0 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });

		walkAnim.loop = true;
		walkAnim.speed = 0.01f;

		idleAnimL.PushBack({ 7 * BATTLE_SIZE , 6 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		idleAnimL.PushBack({ 6 * BATTLE_SIZE , 6 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		idleAnimL.PushBack({ 5 * BATTLE_SIZE , 6 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		idleAnimL.PushBack({ 4 * BATTLE_SIZE , 6 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		idleAnimL.PushBack({ 3 * BATTLE_SIZE , 6 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		idleAnimL.PushBack({ 2 * BATTLE_SIZE , 6 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		idleAnimL.PushBack({ 1 * BATTLE_SIZE , 6 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		idleAnimL.PushBack({ 0 * BATTLE_SIZE , 6 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });

		idleAnimL.loop = true;
		idleAnimL.speed = 0.01f;

		walkAnimL.PushBack({ 7 * BATTLE_SIZE , 6 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		walkAnimL.PushBack({ 6 * BATTLE_SIZE , 6 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		walkAnimL.PushBack({ 5 * BATTLE_SIZE , 6 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		walkAnimL.PushBack({ 4 * BATTLE_SIZE , 6 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		walkAnimL.PushBack({ 3 * BATTLE_SIZE , 6 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		walkAnimL.PushBack({ 2 * BATTLE_SIZE , 6 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		walkAnimL.PushBack({ 1 * BATTLE_SIZE , 6 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		walkAnimL.PushBack({ 0 * BATTLE_SIZE , 6 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });

		walkAnimL.loop = true;
		walkAnimL.speed = 0.01f;

		battleAnim.PushBack({ 7 * BATTLE_SIZE , 6 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		battleAnim.PushBack({ 6 * BATTLE_SIZE , 6 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		battleAnim.PushBack({ 5 * BATTLE_SIZE , 6 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		battleAnim.PushBack({ 4 * BATTLE_SIZE , 6 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		battleAnim.PushBack({ 3 * BATTLE_SIZE , 6 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		battleAnim.PushBack({ 2 * BATTLE_SIZE , 6 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		battleAnim.PushBack({ 1 * BATTLE_SIZE , 6 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		battleAnim.PushBack({ 0 * BATTLE_SIZE , 6 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });

		battleAnim.loop = true;
		battleAnim.speed = 0.01f;

		attackAnim.PushBack({ 7 * BATTLE_SIZE , 7 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		attackAnim.PushBack({ 6 * BATTLE_SIZE , 7 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		attackAnim.PushBack({ 5 * BATTLE_SIZE , 7 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		attackAnim.PushBack({ 4 * BATTLE_SIZE , 7 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		attackAnim.PushBack({ 3 * BATTLE_SIZE , 7 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		attackAnim.PushBack({ 2 * BATTLE_SIZE , 7 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		attackAnim.PushBack({ 1 * BATTLE_SIZE , 7 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		attackAnim.PushBack({ 0 * BATTLE_SIZE , 7 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });

		attackAnim.PushBack({ 7 * BATTLE_SIZE , 6 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		attackAnim.PushBack({ 6 * BATTLE_SIZE , 6 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		attackAnim.PushBack({ 5 * BATTLE_SIZE , 6 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		attackAnim.PushBack({ 4 * BATTLE_SIZE , 6 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		attackAnim.PushBack({ 3 * BATTLE_SIZE , 6 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		attackAnim.PushBack({ 2 * BATTLE_SIZE , 6 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		attackAnim.PushBack({ 1 * BATTLE_SIZE , 6 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		attackAnim.PushBack({ 0 * BATTLE_SIZE , 6 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });

		attackAnim.loop = false;
		attackAnim.speed = 0.01f;

		attackAnim2.PushBack({ 7 * BATTLE_SIZE , 8 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		attackAnim2.PushBack({ 6 * BATTLE_SIZE , 8 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		attackAnim2.PushBack({ 5 * BATTLE_SIZE , 8 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		attackAnim2.PushBack({ 4 * BATTLE_SIZE , 8 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		attackAnim2.PushBack({ 3 * BATTLE_SIZE , 8 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		attackAnim2.PushBack({ 2 * BATTLE_SIZE , 8 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		attackAnim2.PushBack({ 1 * BATTLE_SIZE , 8 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		attackAnim2.PushBack({ 0 * BATTLE_SIZE , 8 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });

		attackAnim2.PushBack({ 7 * BATTLE_SIZE , 6 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		attackAnim2.PushBack({ 6 * BATTLE_SIZE , 6 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		attackAnim2.PushBack({ 5 * BATTLE_SIZE , 6 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		attackAnim2.PushBack({ 4 * BATTLE_SIZE , 6 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		attackAnim2.PushBack({ 3 * BATTLE_SIZE , 6 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		attackAnim2.PushBack({ 2 * BATTLE_SIZE , 6 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		attackAnim2.PushBack({ 1 * BATTLE_SIZE , 6 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		attackAnim2.PushBack({ 0 * BATTLE_SIZE , 6 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });

		attackAnim2.loop = false;
		attackAnim2.speed = 0.01f;

		attackAnim3.PushBack({ 7 * BATTLE_SIZE , 9 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		attackAnim3.PushBack({ 6 * BATTLE_SIZE , 9 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		attackAnim3.PushBack({ 5 * BATTLE_SIZE , 9 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		attackAnim3.PushBack({ 4 * BATTLE_SIZE , 9 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		attackAnim3.PushBack({ 3 * BATTLE_SIZE , 9 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		attackAnim3.PushBack({ 2 * BATTLE_SIZE , 9 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });

		attackAnim3.PushBack({ 7 * BATTLE_SIZE , 6 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		attackAnim3.PushBack({ 6 * BATTLE_SIZE , 6 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		attackAnim3.PushBack({ 5 * BATTLE_SIZE , 6 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		attackAnim3.PushBack({ 4 * BATTLE_SIZE , 6 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		attackAnim3.PushBack({ 3 * BATTLE_SIZE , 6 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		attackAnim3.PushBack({ 2 * BATTLE_SIZE , 6 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		attackAnim3.PushBack({ 1 * BATTLE_SIZE , 6 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		attackAnim3.PushBack({ 0 * BATTLE_SIZE , 6 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });

		attackAnim3.loop = false;
		attackAnim3.speed = 0.01f;

		protectAnim.PushBack({ 6 * BATTLE_SIZE , 9 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		protectAnim.PushBack({ 6 * BATTLE_SIZE , 9 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		protectAnim.PushBack({ 6 * BATTLE_SIZE , 9 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		protectAnim.PushBack({ 6 * BATTLE_SIZE , 9 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });

		protectAnim.PushBack({ 6 * BATTLE_SIZE , 9 * BATTLE_SIZE + 3 , BATTLE_SIZE , BATTLE_SIZE });
		protectAnim.PushBack({ 6 * BATTLE_SIZE , 9 * BATTLE_SIZE + 3 , BATTLE_SIZE , BATTLE_SIZE });

		protectAnim.PushBack({ 6 * BATTLE_SIZE , 9 * BATTLE_SIZE + 5 , BATTLE_SIZE , BATTLE_SIZE });
		protectAnim.PushBack({ 6 * BATTLE_SIZE , 9 * BATTLE_SIZE + 5 , BATTLE_SIZE , BATTLE_SIZE });
		protectAnim.PushBack({ 6 * BATTLE_SIZE , 9 * BATTLE_SIZE + 5 , BATTLE_SIZE , BATTLE_SIZE });
		protectAnim.PushBack({ 6 * BATTLE_SIZE , 9 * BATTLE_SIZE + 5 , BATTLE_SIZE , BATTLE_SIZE });

		protectAnim.PushBack({ 6 * BATTLE_SIZE , 9 * BATTLE_SIZE + 3 , BATTLE_SIZE , BATTLE_SIZE });
		protectAnim.PushBack({ 6 * BATTLE_SIZE , 9 * BATTLE_SIZE + 3 , BATTLE_SIZE , BATTLE_SIZE });

		protectAnim.loop = true;
		protectAnim.speed = 0.01f;

		hitAnim.PushBack({ 7 * BATTLE_SIZE , 10 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		hitAnim.PushBack({ 6 * BATTLE_SIZE , 10 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		hitAnim.PushBack({ 5 * BATTLE_SIZE , 10 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		hitAnim.PushBack({ 4 * BATTLE_SIZE , 10 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });

		hitAnim.loop = true;
		hitAnim.speed = 0.01f;

		dieAnim.PushBack({ 7 * BATTLE_SIZE , 11 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		dieAnim.PushBack({ 6 * BATTLE_SIZE , 11 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		dieAnim.PushBack({ 5 * BATTLE_SIZE , 11 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		dieAnim.PushBack({ 4 * BATTLE_SIZE , 11 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });

		dieAnim.loop = false;
		dieAnim.speed = 0.006f;

		SpriteEdges = {80,90};
		baseCollider = app->collisions->AddCollider({ position.x, position.y, 36, 28 }, Collider::Type::INSTANT, this);

		currentAnimation = &idleAnimL;

		name = "Flying eye";
		battleName = " Fl. Eye";
		configName = "flying_eye";

		break;

	case NormalEnemyType::BAT:

		idleAnim.PushBack({ 0 * BATTLE_SIZE , 1 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		idleAnim.PushBack({ 1 * BATTLE_SIZE , 1 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		idleAnim.PushBack({ 2 * BATTLE_SIZE , 1 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		idleAnim.PushBack({ 3 * BATTLE_SIZE , 1 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		idleAnim.PushBack({ 4 * BATTLE_SIZE , 1 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });

		idleAnim.loop = true;
		idleAnim.speed = 0.01f;

		walkAnim.PushBack({ 0 * BATTLE_SIZE , 1 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		walkAnim.PushBack({ 1 * BATTLE_SIZE , 1 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		walkAnim.PushBack({ 2 * BATTLE_SIZE , 1 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		walkAnim.PushBack({ 3 * BATTLE_SIZE , 1 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		walkAnim.PushBack({ 4 * BATTLE_SIZE , 1 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });

		walkAnim.loop = true;
		walkAnim.speed = 0.01f;

		idleAnimL.PushBack({ 4 * BATTLE_SIZE , 4 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		idleAnimL.PushBack({ 3 * BATTLE_SIZE , 4 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		idleAnimL.PushBack({ 2 * BATTLE_SIZE , 4 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		idleAnimL.PushBack({ 1 * BATTLE_SIZE , 4 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		idleAnimL.PushBack({ 0 * BATTLE_SIZE , 4 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });

		idleAnimL.loop = true;
		idleAnimL.speed = 0.01f;

		walkAnimL.PushBack({ 4 * BATTLE_SIZE , 4 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		walkAnimL.PushBack({ 3 * BATTLE_SIZE , 4 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		walkAnimL.PushBack({ 2 * BATTLE_SIZE , 4 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		walkAnimL.PushBack({ 1 * BATTLE_SIZE , 4 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		walkAnimL.PushBack({ 0 * BATTLE_SIZE , 4 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });

		walkAnimL.loop = true;
		walkAnimL.speed = 0.01f;

		battleAnim.PushBack({ 4 * BATTLE_SIZE , 3 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		battleAnim.PushBack({ 3 * BATTLE_SIZE , 3 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		battleAnim.PushBack({ 2 * BATTLE_SIZE , 3 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		battleAnim.PushBack({ 1 * BATTLE_SIZE , 3 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		battleAnim.PushBack({ 0 * BATTLE_SIZE , 3 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });

		battleAnim.loop = true;
		battleAnim.speed = 0.02f;

		attackAnim.PushBack({ 4 * BATTLE_SIZE , 3 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		attackAnim.PushBack({ 3 * BATTLE_SIZE , 3 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		attackAnim.PushBack({ 2 * BATTLE_SIZE , 3 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		attackAnim.PushBack({ 1 * BATTLE_SIZE , 3 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		attackAnim.PushBack({ 0 * BATTLE_SIZE , 3 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });

		attackAnim.loop = true;
		attackAnim.speed = 0.02f;

		attackAnim2.PushBack({ 4 * BATTLE_SIZE , 3 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		attackAnim2.PushBack({ 3 * BATTLE_SIZE , 3 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		attackAnim2.PushBack({ 2 * BATTLE_SIZE , 3 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		attackAnim2.PushBack({ 1 * BATTLE_SIZE , 3 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		attackAnim2.PushBack({ 0 * BATTLE_SIZE , 3 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });

		attackAnim2.loop = true;
		attackAnim2.speed = 0.02f;

		attackAnim3.PushBack({ 4 * BATTLE_SIZE , 3 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		attackAnim3.PushBack({ 3 * BATTLE_SIZE , 3 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		attackAnim3.PushBack({ 2 * BATTLE_SIZE , 3 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		attackAnim3.PushBack({ 1 * BATTLE_SIZE , 3 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		attackAnim3.PushBack({ 0 * BATTLE_SIZE , 3 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });

		attackAnim3.loop = true;
		attackAnim3.speed = 0.02f;

		protectAnim.PushBack({ 4 * BATTLE_SIZE , 3 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		protectAnim.PushBack({ 3 * BATTLE_SIZE , 3 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		protectAnim.PushBack({ 2 * BATTLE_SIZE , 3 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		protectAnim.PushBack({ 1 * BATTLE_SIZE , 3 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		protectAnim.PushBack({ 0 * BATTLE_SIZE , 3 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });

		protectAnim.loop = true;
		protectAnim.speed = 0.02f;

		hitAnim.PushBack({ 4 * BATTLE_SIZE , 4 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		hitAnim.PushBack({ 3 * BATTLE_SIZE , 4 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		hitAnim.PushBack({ 2 * BATTLE_SIZE , 4 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		hitAnim.PushBack({ 1 * BATTLE_SIZE , 4 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		hitAnim.PushBack({ 0 * BATTLE_SIZE , 4 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });

		hitAnim.loop = true;
		hitAnim.speed = 0.02f;

		dieAnim.PushBack({ 4 * BATTLE_SIZE , 5 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		dieAnim.PushBack({ 3 * BATTLE_SIZE , 5 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		dieAnim.PushBack({ 2 * BATTLE_SIZE , 5 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		dieAnim.PushBack({ 1 * BATTLE_SIZE , 5 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		dieAnim.PushBack({ 0 * BATTLE_SIZE , 5 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });

		dieAnim.loop = false;
		dieAnim.speed = 0.006f;

		SpriteEdges = { 80,90 };
		baseCollider = app->collisions->AddCollider({ position.x, position.y, 16, 16 }, Collider::Type::INSTANT, this);

		currentAnimation = &idleAnimL;

		name = "Bat";
		battleName = " Bat";
		configName = "bat";

		break;

	case NormalEnemyType::SKELETON:

		idleAnim.PushBack({ 3 * BATTLE_SIZE, 0 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		idleAnim.PushBack({ 2 * BATTLE_SIZE, 0 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		idleAnim.PushBack({ 1 * BATTLE_SIZE, 0 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		idleAnim.PushBack({ 0 * BATTLE_SIZE, 0 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });

		idleAnim.loop = true;
		idleAnim.speed = 0.01f;

		walkAnim.PushBack({ 3 * BATTLE_SIZE , 1 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		walkAnim.PushBack({ 2 * BATTLE_SIZE , 1 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		walkAnim.PushBack({ 1 * BATTLE_SIZE , 1 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		walkAnim.PushBack({ 0 * BATTLE_SIZE , 1 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });

		walkAnim.loop = true;
		walkAnim.speed = 0.01f;

		idleAnimL.PushBack({ 7 * BATTLE_SIZE , 8 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		idleAnimL.PushBack({ 6 * BATTLE_SIZE , 8 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		idleAnimL.PushBack({ 5 * BATTLE_SIZE , 8 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		idleAnimL.PushBack({ 4 * BATTLE_SIZE , 8 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });

		idleAnimL.loop = true;
		idleAnimL.speed = 0.01f;

		walkAnimL.PushBack({ 7 * BATTLE_SIZE , 9 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		walkAnimL.PushBack({ 6 * BATTLE_SIZE , 9 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		walkAnimL.PushBack({ 5 * BATTLE_SIZE , 9 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		walkAnimL.PushBack({ 4 * BATTLE_SIZE , 9 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });

		walkAnimL.loop = true;
		walkAnimL.speed = 0.01f;

		battleAnim.PushBack({ 7 * BATTLE_SIZE , 8 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		battleAnim.PushBack({ 6 * BATTLE_SIZE , 8 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		battleAnim.PushBack({ 5 * BATTLE_SIZE , 8 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		battleAnim.PushBack({ 4 * BATTLE_SIZE , 8 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });

		battleAnim.loop = true;
		battleAnim.speed = 0.01f;

		attackAnim.PushBack({ 7 * BATTLE_SIZE , 10 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		attackAnim.PushBack({ 6 * BATTLE_SIZE , 10 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		attackAnim.PushBack({ 5 * BATTLE_SIZE , 10 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		attackAnim.PushBack({ 4 * BATTLE_SIZE , 10 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		attackAnim.PushBack({ 3 * BATTLE_SIZE , 10 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		attackAnim.PushBack({ 2 * BATTLE_SIZE , 10 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		attackAnim.PushBack({ 1 * BATTLE_SIZE , 10 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		attackAnim.PushBack({ 0 * BATTLE_SIZE , 10 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });

		attackAnim.PushBack({ 7 * BATTLE_SIZE , 8 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		attackAnim.PushBack({ 6 * BATTLE_SIZE , 8 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		attackAnim.PushBack({ 5 * BATTLE_SIZE , 8 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		attackAnim.PushBack({ 4 * BATTLE_SIZE , 8 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });

		attackAnim.loop = false;
		attackAnim.speed = 0.01f;

		attackAnim2.PushBack({ 7 * BATTLE_SIZE , 11 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		attackAnim2.PushBack({ 6 * BATTLE_SIZE , 11 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		attackAnim2.PushBack({ 5 * BATTLE_SIZE , 11 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		attackAnim2.PushBack({ 4 * BATTLE_SIZE , 11 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		attackAnim2.PushBack({ 3 * BATTLE_SIZE , 11 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		attackAnim2.PushBack({ 2 * BATTLE_SIZE , 11 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		attackAnim2.PushBack({ 1 * BATTLE_SIZE , 11 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		attackAnim2.PushBack({ 0 * BATTLE_SIZE , 11 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });

		attackAnim2.PushBack({ 7 * BATTLE_SIZE , 8 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		attackAnim2.PushBack({ 6 * BATTLE_SIZE , 8 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		attackAnim2.PushBack({ 5 * BATTLE_SIZE , 8 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		attackAnim2.PushBack({ 4 * BATTLE_SIZE , 8 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });

		attackAnim2.loop = false;
		attackAnim2.speed = 0.01f;

		attackAnim3.PushBack({ 7 * BATTLE_SIZE , 12 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		attackAnim3.PushBack({ 6 * BATTLE_SIZE , 12 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		attackAnim3.PushBack({ 5 * BATTLE_SIZE , 12 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		attackAnim3.PushBack({ 4 * BATTLE_SIZE , 12 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		attackAnim3.PushBack({ 3 * BATTLE_SIZE , 12 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		attackAnim3.PushBack({ 2 * BATTLE_SIZE , 12 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		attackAnim3.PushBack({ 1 * BATTLE_SIZE , 12 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		attackAnim3.PushBack({ 0 * BATTLE_SIZE , 12 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });

		attackAnim3.PushBack({ 7 * BATTLE_SIZE , 8 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		attackAnim3.PushBack({ 6 * BATTLE_SIZE , 8 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		attackAnim3.PushBack({ 5 * BATTLE_SIZE , 8 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		attackAnim3.PushBack({ 4 * BATTLE_SIZE , 8 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });

		attackAnim3.loop = false;
		attackAnim3.speed = 0.01f;

		protectAnim.PushBack({ 7 * BATTLE_SIZE , 13 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		protectAnim.PushBack({ 6 * BATTLE_SIZE , 13 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		protectAnim.PushBack({ 5 * BATTLE_SIZE , 13 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		protectAnim.PushBack({ 4 * BATTLE_SIZE , 13 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });

		protectAnim.loop = false;
		protectAnim.speed = 0.01f;

		hitAnim.PushBack({ 7 * BATTLE_SIZE , 14 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		hitAnim.PushBack({ 6 * BATTLE_SIZE , 14 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		hitAnim.PushBack({ 5 * BATTLE_SIZE , 14 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		hitAnim.PushBack({ 4 * BATTLE_SIZE , 14 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });

		hitAnim.loop = true;
		hitAnim.speed = 0.01f;

		dieAnim.PushBack({ 7 * BATTLE_SIZE , 15 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		dieAnim.PushBack({ 6 * BATTLE_SIZE , 15 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		dieAnim.PushBack({ 5 * BATTLE_SIZE , 15 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		dieAnim.PushBack({ 4 * BATTLE_SIZE , 15 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });

		dieAnim.loop = false;
		dieAnim.speed = 0.01f;

		SpriteEdges = { 90,60 };//90 60
		baseCollider = app->collisions->AddCollider({ position.x, position.y, 45, 80 }, Collider::Type::INSTANT, this);

		currentAnimation = &idleAnimL;

		name = "Skeleton";
		battleName = " Skelet.";
		configName = "skeleton";

		break;

	default:
		break;
	}

	isAlive = true;
	onlyInBattle = false;

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

		spriteTex = app->tex->Load("Assets/sprites/enemies/flying_eye/eyeSprite.png");

		stats = new Stats(1, 10, 10, 4, 5, 18);

		break;
	case NormalEnemyType::BAT:

		spriteTex = app->tex->Load("Assets/sprites/enemies/bat/bat.png");

		stats = new Stats(1, 5, 10, 2, 2, 27);

		break;
	case NormalEnemyType::SKELETON:

		spriteTex = app->tex->Load("Assets/sprites/enemies/skeleton/skeletonSprite.png");

		/*stats = new Stats(1, 15, 6, 5, 1, 10);*/
		stats = new Stats(1, 15, 15, 5, 1, 18);

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

	app->tex->UnLoad(spriteTex);


	currentAnimation = nullptr;
	delete currentAnimation;

	return true;
}