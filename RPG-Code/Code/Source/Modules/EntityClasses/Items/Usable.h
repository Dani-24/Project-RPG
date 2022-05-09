#ifndef __USABLE_H__
#define __USABLE_H__

#include "App.h"
#include "Point.h"
#include "Animation.h"
#include "Render.h"
#include "Entity.h"

#include "EntityManager.h"

#include <vector>

struct SDL_Texture;

enum class UsableType
{
	//Restore life
	APPLE,
	LIFE_POTION,
	PIE,
	DELICIOUS_PIE,

	//Restore energy
	ELIXIR,

	//Damage all entities in battle (only a bit if they are allies)
	BOMB,
	SUPER_BOMB,

	//Revive
	WILL_TO_LIFE
};

class Usable : public Item
{
public:

	Usable(UsableType type);
	~Usable();

	bool Awake(pugi::xml_node& config);
	bool Start();
	bool PreUpdate();
	bool Update(float dt);
	bool PostUpdate();

	bool CleanUp();


public:
	bool onlyInBattle;
	UsableType usableType;

};

#endif // !__USABLE_H__
