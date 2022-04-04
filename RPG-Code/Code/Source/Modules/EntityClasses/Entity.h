#ifndef __ENTITY_H__
#define __ENTITY_H__

#include "App.h"
#include "Point.h"
#include "Animation.h"
#include "Render.h"

#include <vector>

struct SDL_Texture;

class Entity;

enum class EntityType 
{
	STATIC,
	DYNAMIC
};

class Entity
{
public:

	Entity(EntityType type);
	Entity(EntityType type, int x, int y);
	~Entity();

	virtual bool Awake(pugi::xml_node& config) { return true; };
	virtual bool Start() { return true; };
	virtual bool PreUpdate() { return true; };
	virtual bool Update(float dt) { return true; };
	virtual bool PostUpdate() { return true; };

	// Returns the enemy's collider
	//const Collider* GetCollider() const;
	//virtual void OnCollision(Collider* collider);

	virtual void Draw();
	virtual void SetToDelete();
	virtual bool CleanUp() { return true; };


public:
	
	

	EntityType type;
	iPoint position;

	// The entity's texture
	SDL_Texture* texture = nullptr;

	// Sound fx when destroyed
	int destroyedFx = 0;

	// A flag for the entity removal. Important! We do not delete objects instantly
	bool pendingToDelete = false;


	// A ptr to the current animation
	Animation* currentAnim = nullptr;

	// The entity's collider
	//Collider* collider = nullptr;

	// Original spawn position. Stored for movement calculations
	iPoint spawnPosition;

	SString entityName;

};

#endif // !__ENTITY_H__
