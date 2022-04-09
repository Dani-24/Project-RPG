#ifndef __NORMAL_ENEMY_H__
#define __NORMAL_ENEMY_H__

#include "App.h"
#include "Point.h"
#include "Animation.h"
#include "Render.h"
#include "Entity.h"

#include "EntityManager.h"

#include <vector>

struct SDL_Texture;

enum class NormalEnemyType
{
	FLYING_EYE,
	MUSHROOM,
	GOBLIN,
	SKELETON
};

class NormalEnemy : public Enemy
{
public:

	NormalEnemy(NormalEnemyType type);
	~NormalEnemy();

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

	NormalEnemyType normalEnemyType;

};

#endif // !__NORMAL_ENEMY_H__


