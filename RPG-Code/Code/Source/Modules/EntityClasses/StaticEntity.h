#ifndef __STATIC_ENTITY_H__
#define __STATIC_ENTITY_H__

#include "App.h"
#include "Point.h"
#include "Animation.h"
#include "Render.h"
#include "Entity.h"

#include "EntityManager.h"

#include <vector>

struct SDL_Texture;

enum class StaticType
{
	ITEM
};

class StaticEntity : public Entity
{
public:

	StaticEntity(StaticType type);
	~StaticEntity();

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

	StaticType staticType;

};

#endif // !__STATIC_ENTITY_H__

