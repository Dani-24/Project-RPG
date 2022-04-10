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
	if (currentAnim != nullptr) {
		
		app->render->DrawTexture(spriteText, position.x, position.y, &(currentAnim->GetCurrentFrame()));
		
	}
}

void Entity::SetToDelete()
{
	
}
