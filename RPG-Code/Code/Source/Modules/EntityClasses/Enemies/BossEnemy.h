#ifndef __BOSS_ENEMY_H__
#define __BOSS_ENEMY_H__

#include "App.h"
#include "Point.h"
#include "Animation.h"
#include "Render.h"
#include "Entity.h"

#include "EntityManager.h"

#include <vector>

struct SDL_Texture;

enum class BossType
{
	TRUCK,
	VALION,
	RAYLA,
	DHION
};

class BossEnemy : public Enemy
{
public:

	BossEnemy(BossType type);
	~BossEnemy();

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

	BossType bossType;

};

#endif // !__BOSS_ENEMY_H__

