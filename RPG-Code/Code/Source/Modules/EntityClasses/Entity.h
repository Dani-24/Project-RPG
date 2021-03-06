#ifndef __ENTITY_H__
#define __ENTITY_H__

#include "App.h"
#include "Point.h"
#include "Animation.h"
#include "Render.h"
#include "Collisions.h"
#include "Textures.h"

#include <vector>

struct SDL_Texture;

class Entity;

enum class StageIndex;

enum class EntityType
{
	STATIC,
	DYNAMIC
};

class Entity
{
public:

	Entity();
	Entity(EntityType type);
	~Entity();

	virtual bool Awake(pugi::xml_node& config) { return true; };
	virtual bool Start() { return true; };
	virtual bool PreUpdate() { return true; };
	virtual bool Update(float dt) { return true; };
	virtual bool PostUpdate() { return true; };

	// Returns the enemy's collider
	virtual const Collider* GetCollider() const { return nullptr; };
	virtual void OnCollision(Collider* collider1, Collider* collider2) {  };

	virtual void Draw();
	virtual void SetToDelete();
	virtual bool CleanUp() { return true; };


public:

	bool hasAwaken = false;
	bool hasStarted = false;

	const char* name;
	const char* battleName;
	SString configName;

	EntityType entityType;
	iPoint position;

	// The entity's texture
	SDL_Texture* spriteTex;

	SDL_Rect spriteRect;


	// Sound fx when destroyed
	int destroyedFx = 0;

	// A flag for the entity removal. Important! We do not delete objects instantly
	bool pendingToDelete = false;

	// A ptr to the current animation
	Animation* currentAnimation = nullptr;

	// Original spawn position. Stored for movement calculations
	iPoint spawnPosition;

	SString entityName;

	int npcID;

	StageIndex activeOnStage;
};

#endif // !__ENTITY_H__
