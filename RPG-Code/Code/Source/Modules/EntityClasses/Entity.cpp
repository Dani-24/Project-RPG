#include "Entity.h"
#include "EntityManager.h"

Entity::Entity()
{
	configName = "entity";
}

Entity::Entity(EntityType entType) : entityType(entType)
{
	configName = "entity";
}

Entity::~Entity()
{
}

void Entity::Draw()
{

}

void Entity::SetToDelete()
{
	
}
