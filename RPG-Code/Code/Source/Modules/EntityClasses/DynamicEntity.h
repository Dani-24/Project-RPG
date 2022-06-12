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
	double health;
	double maxHealth;
	

	int level;
	double attack;
	double defense;
	double speed;
	double mana;
	double maxMana;
	int exp;
	int nexp;

	double Shealth;
	double SmaxHealth;
	
	int Slevel;
	double Sattack;
	double Sdefense;
	double Sspeed;
	double Smana;
	double SmaxMana;
	bool firstgod;

	int localTurn;
	bool defenseBuffed;
	int attackMulti;
	int defMulti;
	bool isStunned;

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
		this->firstgod = false;
		this->attackMulti = 1;
		this->defMulti = 1;
		this->isStunned = false;
	}
	//lvl mxhealth attak defense mana speed
	Stats(int level, double maxHealth, double attack, double defense, double mana, double speed) {
		this->level = 1;

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
		this->attackMulti = 1;
		this->defMulti = 1;
		this->isStunned = false;

		if (level > 1) {
			int lvl = this->nexp;
			for (int i = 0; i < level - 1; i++)
			{

				lvl *= 1.1;
				lvlup(lvl);
			}

		}

	}

	float TurnValue() {
		float a = ((float)localTurn / (float)speed) * 100.0f;
		return a;
	}
	void SetStats(double Health, double attack, double defense, double mana/*, int speed*/)
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

		exp += rep;
		if (exp >= nexp)
		{
			while (exp >= nexp) {
				int a = 0;
				a = exp - nexp;
				exp = a;
				LOG("LEVEL UP! jovani de puerto rico");
				level++;
				attack += attack*0.08;
				defense +=defense * 0.08;
				speed += speed*0.08;
				mana += mana * 0.08;
				maxMana += maxMana * 0.08;
				nexp *= 1.1;
				maxHealth += maxHealth * 0.08;
				health +=health * 0.08;
			}
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
