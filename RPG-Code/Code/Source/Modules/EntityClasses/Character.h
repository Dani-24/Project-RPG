#ifndef __CHARACTER_H__
#define __CHARACTER_H__

#include "App.h"
#include "Point.h"
#include "Animation.h"
#include "Render.h"
#include "Entity.h"

#include "EntityManager.h"

#include <vector>

struct SDL_Texture;

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

	// Returns the enemy's collider
	//const Collider* GetCollider() const;
	//virtual void OnCollision(Collider* collider);

	virtual bool CleanUp();


public:

	CharacterType characterType;

};

#endif // !__ENEMY_H__


