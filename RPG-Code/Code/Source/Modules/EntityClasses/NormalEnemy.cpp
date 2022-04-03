#include "EntityManager.h"

#include "Entity.h"
#include "DynamicEntity.h"
#include "Enemy.h"
#include "NormalEnemy.h"


NormalEnemy::NormalEnemy(NormalEnemyType normalEnemyType) : Enemy(EnemyType::NORMAL)
{
	this->normalEnemyType = normalEnemyType;
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
	return true;
}

bool NormalEnemy::PreUpdate()
{
	return true;
}

// Call modules on each loop iteration
bool NormalEnemy::Update(float dt)
{
	return true;
}

// Call modules after each loop iteration
bool NormalEnemy::PostUpdate()
{
	return true;
}

// Called before quitting
bool NormalEnemy::CleanUp()
{
	return true;
}