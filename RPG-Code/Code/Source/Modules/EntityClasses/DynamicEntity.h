#ifndef __DYNAMIC_ENTITY_H__
#define __DYNAMIC_ENTITY_H__

#include "App.h"
#include "Point.h"
#include "Animation.h"
#include "Render.h"

#include "Entity.h"

#include <vector>

struct SDL_Texture;

enum class DynamicType
{
	CHARACTER,
	ENEMY,
	NPC,
	INTERACTABLE
};

class DynamicEntity : public Entity
{
public:

	DynamicEntity(DynamicType type);
	~DynamicEntity();

	virtual bool Awake(pugi::xml_node& config);
	virtual bool Start();
	virtual bool PreUpdate();
	virtual bool Update(float dt);
	virtual bool PostUpdate();

	// Returns the enemy's collider
	//const Collider* GetCollider() const;
	//virtual void OnCollision(Collider* collider);

	virtual bool CleanUp();


public:

	DynamicType dynamicType;

	int dynamicThing;

};

#endif // !__DYNAMIC_ENTITY_H__
