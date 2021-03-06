#ifndef __ITEM_H__
#define __ITEM_H__

#include "App.h"
#include "Point.h"
#include "Animation.h"
#include "Render.h"
#include "Entity.h"
#include "StaticEntity.h"
#include "EntityManager.h"

#include <vector>

#define ITEM_SIZE 48

struct SDL_Texture;

enum class ItemType
{
	EQUIPMENT,
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

	virtual bool CleanUp();


public:

	ItemType itemType;

	const char* effect = " ";
	const char* description = " ";
	bool usableFromInventory = false;

};

#endif // !__ITEM_H__
