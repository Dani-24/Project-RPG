#ifndef __ITEM_H__
#define __ITEM_H__

#include "App.h"
#include "Point.h"
#include "Animation.h"
#include "Render.h"
#include "Entity.h"

#include "EntityManager.h"

#include <vector>

struct SDL_Texture;

enum class ItemType
{
	WEAPON,
	ARMOR,
	USABLE
};

class Item : public StaticEntity
{
public:

	Item(ItemType type);
	~Item();

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

	ItemType itemType;

};

#endif // !__ITEM_H__


