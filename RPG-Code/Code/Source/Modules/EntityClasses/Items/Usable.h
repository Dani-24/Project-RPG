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
	CANDY,
	MEAT,
	EGG,
	FRIED_EGG,
	HAMBURGER,

	//Restore energy
	ELIXIR,

	//Damage all entities in battle (only a bit if they are allies)
	DYNAMITE,
	BOMB,
	SUPER_BOMB,

	//Boost
	PILL,

	//Revive
	WILL_TO_LIFE,

	//Map
	CHEST_KEY,
	DOOR_KEY,

	//Missions
	TEDDY_BEAR,
	LETTER,
	CLOSE_PARCHMENT,
	OPEN_PARCHMENT,

	//Others
	BAT_WING,
	EYE,
	BONE
	
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
