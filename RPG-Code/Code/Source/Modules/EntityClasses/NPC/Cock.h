#ifndef __COCK_H__
#define __COCK_H__

#include "App.h"
#include "Point.h"
#include "Animation.h"
#include "Render.h"
#include "Entity.h"
#include "NPC.h"
#include "EntityManager.h"

#include <vector>

struct SDL_Texture;
struct SDL_Surface;
struct Collider;

enum class NPCType;

class Cock : public NPC
{
public:

	Cock(NPCType type);
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
	

	

};

#endif // !__COCK_H__