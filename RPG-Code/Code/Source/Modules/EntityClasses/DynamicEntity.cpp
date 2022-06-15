#include "EntityManager.h"

#include "Entity.h"
#include "DynamicEntity.h"


DynamicEntity::DynamicEntity(DynamicType dynamicType) : Entity(EntityType::DYNAMIC)
{
	this->dynamicType = dynamicType;
	isAlive = true;
	zoom = 1;
	isSelected = false;
	takesDamage = false;
}

DynamicEntity::~DynamicEntity()
{}

bool DynamicEntity::Awake(pugi::xml_node& config)
{

	return true;
}

// Called before the first frame
bool DynamicEntity::Start()
{
	return true;
}

bool DynamicEntity::PreUpdate()
{
	return true;
}

// Call modules on each loop iteration
bool DynamicEntity::Update(float dt)
{
	return true;
}

// Call modules after each loop iteration
bool DynamicEntity::PostUpdate()
{
	return true;
}

// Called before quitting
bool DynamicEntity::CleanUp()
{
	return true;
}

const Collider* DynamicEntity::GetCollider() const
{
	return baseCollider;
}