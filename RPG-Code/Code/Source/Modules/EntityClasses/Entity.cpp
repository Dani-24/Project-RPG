#include "Entity.h"
#include "EntityManager.h"


Entity::Entity(EntityType entType) : entityType(entType)
{
	configName = "entity";
}

Entity::Entity(EntityType type, int x, int y) : position(x, y), entityType(type)
{
	spawnPosition = position;
}

Entity::~Entity()
{
}

void Entity::Draw()
{
	if (currentAnim != nullptr) {
		
		app->render->DrawTexture(sprite, position.x, position.y, &(currentAnim->GetCurrentFrame()));
		
	}
}

void Entity::SetToDelete()
{
	
}
