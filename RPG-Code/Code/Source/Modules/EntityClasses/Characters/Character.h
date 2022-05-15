#ifndef __CHARACTER_H__
#define __CHARACTER_H__

#include "App.h"
#include "Point.h"
#include "Animation.h"
#include "Render.h"

#include "EntityManager.h"
#include "Entity.h"
#include "DynamicEntity.h"

#include <vector>

struct SDL_Texture;
class Equipment;
enum class EquipmentType;

enum class CharacterType
{
	PLAYER,
	PARTY
};

class Character : public DynamicEntity
{
public:

	Character(CharacterType type);
	~Character();

	virtual bool Awake(pugi::xml_node& config);
	virtual bool Start();
	virtual bool PreUpdate();
	virtual bool Update(float dt);
	virtual bool PostUpdate();

	virtual void Equip(Equipment*equip);
	virtual void Unequip(EquipmentType slot);

	virtual bool CleanUp();


public:

	Equipment* equipment[7];

	Animation
		idleBattle,
		attackAnim1,
		attackAnim2,
		hitAnim,
		deathAnim,
		jumpAnim,
		fallAnim,
		runAnim,
		protectedAnim;

	CharacterType characterType;

	Collider* battleCollider;

	SDL_Texture* spriteFace;

	bool skillsList[3];

};

#endif // !__ENEMY_H__


