#include "Entity.h"
#include "EntityManager.h"


Entity::Entity(EntityType type) : type(type)
{
}

Entity::Entity(EntityType type, int x, int y) : position(x, y), type(type)
{
	spawnPosition = position;
}

Entity::~Entity()
{
}

void Entity::Draw()
{
	if (currentAnim != nullptr) {
		
		app->render->DrawTexture(texture, position.x, position.y, &(currentAnim->GetCurrentFrame()));
		
	}
}

void Entity::SetToDelete()
{
	
}
