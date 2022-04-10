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
	if (currentAnimation != nullptr) {
		
		app->render->DrawTexture(spriteText, position.x, position.y, &(currentAnimation->GetCurrentFrame()));
		app->render->DrawTexture(spriteTextB, position.x, position.y, &(currentAnimation->GetCurrentFrame()));
		
	}
}

void Entity::SetToDelete()
{
	
}
