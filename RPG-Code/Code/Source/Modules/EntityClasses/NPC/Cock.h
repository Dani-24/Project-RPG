#ifndef __GALLINA_NPC_H__
#define __GALLINA_NPC_H__

#include "App.h"
#include "Point.h"
#include "Animation.h"
#include "Render.h"
#include "Entity.h"
#include "NPCEntity.h"
#include "EntityManager.h"

#include <vector>

struct SDL_Texture;
struct SDL_Surface;
struct Collider;

class Cock : public NPC
{
public:
	Cock();
	~Cock();

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
	

	SDL_Texture* CockTex = nullptr;

	

};

#endif // !__NPC_ENTITY_H__