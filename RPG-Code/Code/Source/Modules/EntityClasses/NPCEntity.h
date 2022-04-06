#ifndef __NPC_ENTITY_H__
#define __NPC_ENTITY_H__

#include "App.h"
#include "Point.h"
#include "Animation.h"
#include "Render.h"
#include "Entity.h"

#include "EntityManager.h"

#include <vector>

struct SDL_Texture;
struct SDL_Surface;
struct Collider;

enum class NPCType
{
	GALLINA,
	TABERNERA,
	TENDERO
};

class NPCEntity : public Entity
{
public:

	NPCEntity(NPCType type);
	~NPCEntity();

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

	/*SDL_Texture* NPC1Tex = nullptr;

	Animation* currentAnimationNPC = nullptr;
	Animation idleAnimNPC;*/

};

#endif // !__NPC_ENTITY_H__