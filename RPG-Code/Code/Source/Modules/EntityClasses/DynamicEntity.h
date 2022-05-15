#ifndef __DYNAMIC_ENTITY_H__
#define __DYNAMIC_ENTITY_H__

#include "App.h"
#include "Point.h"
#include "Animation.h"
#include "Render.h"

#include "Entity.h"

#include <vector>

#define BATTLE_SIZE 180

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
	int defense;
	int speed;
	int mana;
	int maxMana;
	int exp;
	int nexp;

	int Shealth;
	int SmaxHealth;
	
	int Slevel;
	int Sattack;
	int Sdefense;
	int Sspeed;
	int Smana;
	int SmaxMana;

	int localTurn;
	bool defenseBuffed;

	Stats() {
		this->level = 0;
		this->exp = 0;
		this->nexp = 100;

		this->maxHealth = 100;
		this->health = 100;

		this->attack = 1;
		this->defense = 1;
		this->speed = 20;
		this->mana = 10;

		this->localTurn = 0;
		this->defenseBuffed = false;
	}
	//lvl mxhealth attak defense mana speed
	Stats(int level, int maxHealth, int attack, int defense, int mana, int speed) {
		this->level = level;
		
		this->maxHealth = maxHealth;
		this->health = maxHealth;

		this->attack = attack;
		this->defense = defense;
		this->speed = speed;

		this->mana = mana;
		this->maxMana = mana;

		/*this->exp = exp;
		this->nexp = nexp;*/
		this->exp = 0;
		this->nexp = 100;
		this->localTurn = 0;
		this->defenseBuffed = false;
	}

	float TurnValue() {
		float a = ((float)localTurn / (float)speed) * 100.0f;
		return a;
	}
	void SetStats(int Health, int attack, int defense, int mana/*, int speed*/)
	{

		this->health = Health;
		this->maxHealth = Health;
		this->attack = attack;
		this->defense = defense;
		/*this->speed = speed;*/
		this->mana = mana;
		this->maxMana = mana;



	}
	void SaveStats()
	{
		Slevel = level;

		Shealth = health;
		SmaxHealth = maxHealth;
		Sattack = attack;
		Sdefense = defense;
		/*this->Sspeed = speed;*/
		Smana = mana;

		SmaxMana = maxMana;
	}
	void LoadStats()
	{
		level = Slevel;
		maxHealth = SmaxHealth;
		health = Shealth;
		

		attack = Sattack;
		defense = Sdefense;
		/*this->speed = Sspeed*/;
		mana = Smana;

		maxMana = SmaxMana;
	}

	void lvlup(int rep)
	{
		int a = 0;
		exp += rep;
		if (exp>=nexp)
		{
			if (exp > nexp)a = exp - nexp;
			exp = a;
			LOG("LEVEL UP! jovani de puerto rico");
			level++;
			attack*=1.2;
			defense *= 1.2;
			speed *= 1.2;
			mana *= 1.2;
			maxMana *= 1.2;
			nexp *= 1.2;
			maxHealth *= 1.2;
			health *= 1.2;
		}
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

	Animation idleAnim, idleAnimL, walkAnim, walkAnimL, battleAnim, hitAnim, dieAnim, attackAnim, attackAnim2, attackAnim3, protectAnim, jumpAnim, fallAnim;

	bool isAlive;

	iPoint mapPosition;
	iPoint battlePosition;
	Animation* mapAnimation;

	int zoom;

};

#endif // !__DYNAMIC_ENTITY_H__
