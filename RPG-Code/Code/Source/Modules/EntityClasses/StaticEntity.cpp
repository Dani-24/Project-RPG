#include "EntityManager.h"

#include "Entity.h"
#include "StaticEntity.h"


StaticEntity::StaticEntity(StaticType staticType) : Entity(EntityType::STATIC)
{
	staticThing = 0;
	this->staticType = staticType;
}

StaticEntity::~StaticEntity()
{}

bool StaticEntity::Awake(pugi::xml_node& config)
{

	return true;
}

// Called before the first frame
bool StaticEntity::Start()
{
	return true;
}

bool StaticEntity::PreUpdate()
{
	return true;
}

// Call modules on each loop iteration
bool StaticEntity::Update(float dt)
{
	return true;
}

// Call modules after each loop iteration
bool StaticEntity::PostUpdate()
{
	return true;
}

// Called before quitting
bool StaticEntity::CleanUp()
{
	return true;
}