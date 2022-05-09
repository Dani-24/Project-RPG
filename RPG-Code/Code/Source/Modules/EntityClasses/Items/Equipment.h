#ifndef __EQUIPMENT_H__
#define __EQUIPMENT_H__

#include "App.h"
#include "Point.h"
#include "Animation.h"
#include "Render.h"
#include "Entity.h"

#include "EntityManager.h"

#include <vector>

struct SDL_Texture;

enum class EquipmentType
{
	WEAPON,
	SHIELD,
	HELMET,
	ARMOR,
	GLOVES,
	BOOTS,
	TALISMAN
};

class Equipment : public Item
{
public:

	Equipment(EquipmentType type, const char*name);
	~Equipment();

	bool Awake(pugi::xml_node& config);
	bool Start();
	bool PreUpdate();
	bool Update(float dt);
	bool PostUpdate();

	bool CleanUp();


public:

	EquipmentType equipmentType;

};

#endif // !__EQUIPMENT_H__
