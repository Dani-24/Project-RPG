#include "EntityManager.h"

#include "Entity.h"
#include "DynamicEntity.h"
#include "Enemy.h"


Enemy::Enemy(EnemyType enemyType) : DynamicEntity(DynamicType::ENEMY)
{
	this->enemyType = enemyType;
}

Enemy::~Enemy()
{}

bool Enemy::Awake(pugi::xml_node& config)
{
	return true;
}

// Called before the first frame
bool Enemy::Start()
{
	return true;
}

bool Enemy::PreUpdate()
{
	return true;
}

// Call modules on each loop iteration
bool Enemy::Update(float dt)
{
	return true;
}

// Call modules after each loop iteration
bool Enemy::PostUpdate()
{
	return true;
}

// Called before quitting
bool Enemy::CleanUp()
{
	return true;
}