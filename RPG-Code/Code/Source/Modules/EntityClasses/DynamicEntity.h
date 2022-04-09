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

class Stats
{
public:
	int health;
	int maxHealth;

	int level;
	int attack;
	int deffense;
	int mana;

	Stats() {
		this->level = 0;

		this->maxHealth = 100;
		this->health = 100;

		this->attack = 1;
		this->deffense = 1;
		this->mana = 10;
	}

	Stats(int level, int maxHealth, int attack, int deffense, int mana) {
		this->level = level;

		this->maxHealth = maxHealth;
		this->health = maxHealth;

		this->attack = attack;
		this->deffense = deffense;
		this->mana = mana;
	}

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

	Collider* baseCollider;

	Animation* currentAnimation = nullptr;

	Animation idleAnim;

	Stats EStats;

};

#endif // !__DYNAMIC_ENTITY_H__
