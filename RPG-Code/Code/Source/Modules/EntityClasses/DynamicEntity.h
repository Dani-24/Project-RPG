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
	int deffense ;
	int speed;
	int mana;

	int Shealth;
	int SmaxHealth;

	int Slevel;
	int Sattack;
	int Sdeffense;
	int Sspeed;
	int Smana;

	int localTurn;
	bool defenseBuffed;

	Stats() {
		this->level = 0;

		this->maxHealth = 100;
		this->health = 100;

		this->attack = 1;
		this->deffense = 1;
		this->speed = 20;
		this->mana = 10;

		this->localTurn = 0;
		this->defenseBuffed = false;
	}

	Stats(int level, int maxHealth, int attack, int deffense, int mana, int speed) {
		this->level = level;

		this->maxHealth = maxHealth;
		this->health = maxHealth;

		this->attack = attack;
		this->deffense = deffense;
		this->speed = speed;
		this->mana = mana;

		this->localTurn = 0;
		this->defenseBuffed = false;
	}

	float TurnValue() {
		float a = ((float)localTurn / (float)speed) * 100.0f;
		return a;
	}
	void SetStats(int maxHealth, int attack, int deffense, int mana, int speed)
	{

		this->maxHealth = maxHealth;
		this->health = maxHealth;

		this->attack = attack;
		this->deffense = deffense;
		this->speed = speed;
		this->mana = mana;

		this->defenseBuffed = false;

	}
	void SaveStats()
	{
		this->Slevel = level;

		this->SmaxHealth = maxHealth;
		this->Shealth = maxHealth;

		this->Sattack = attack;
		this->Sdeffense = deffense;
		this->Sspeed = speed;
		this->Smana = mana;
	}
	void LoadStats()
	{
		this->level = Slevel;

		this->maxHealth = SmaxHealth;
		this->health = SmaxHealth;

		this->attack = Sattack;
		this->deffense = Sdeffense;
		this->speed = Sspeed;
		this->mana = Smana;
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

	virtual void SaveStats()
	{

	}

	// Returns the enemy's collider
	const Collider* GetCollider() const override;
	//virtual void OnCollision(Collider* collider);

	virtual bool CleanUp();


public:

	Stats* stats, savestats;

	DynamicType dynamicType;

	Collider* baseCollider;

	Animation idleAnim, idleAnimL, walkAnim, walkAnimL, battleAnim, hitAnim, dieAnim, attackAnim, attackAnim2, attackAnim3, protectAnim;

	bool isAlive;

	iPoint mapPosition;
	iPoint battlePosition;
	Animation* mapAnimation;

};

#endif // !__DYNAMIC_ENTITY_H__
