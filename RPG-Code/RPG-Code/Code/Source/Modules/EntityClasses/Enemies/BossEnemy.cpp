#include "EntityManager.h"

#include "Entity.h"
#include "DynamicEntity.h"
#include "Enemy.h"
#include "BossEnemy.h"


BossEnemy::BossEnemy(BossType bossType) : Enemy(EnemyType::BOSS)
{
	this->bossType = bossType;
}

BossEnemy::~BossEnemy()
{}

bool BossEnemy::Awake(pugi::xml_node& config)
{
	return true;
}

// Called before the first frame
bool BossEnemy::Start()
{
	return true;
}

bool BossEnemy::PreUpdate()
{
	return true;
}

// Call modules on each loop iteration
bool BossEnemy::Update(float dt)
{
	return true;
}

// Call modules after each loop iteration
bool BossEnemy::PostUpdate()
{
	return true;
}

// Called before quitting
bool BossEnemy::CleanUp()
{
	return true;
}