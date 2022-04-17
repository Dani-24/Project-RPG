#ifndef __PARTY_H__
#define __PARTY_H__

#include "App.h"
#include "Point.h"
#include "Animation.h"
#include "Render.h"

#include "EntityManager.h"
#include "Entity.h"
#include "DynamicEntity.h"
#include "Character.h"
#include "NormalEnemy.h"

#include <vector>

#include "Animation.h"
#include "DialogSystem.h"

struct SDL_Texture;
struct SDL_Surface;
struct Collider;

enum class PartyType
{
	VALION,
	RAYLA,
	DHION
};

class Party :public Character {
public:
	Party(PartyType partyType, int x, int y);
	~Party();

	// Called before render is available
	bool Awake(pugi::xml_node&);
	bool Start() override;
	bool PreUpdate() override;
	bool Update(float dt) override;
	bool PostUpdate() override;
	bool CleanUp() override;


public:

	// Player animations
	Animation
		idleBattle;

	// Textures
	SDL_Texture* PartyTex = nullptr;
	SDL_Texture* BattleTex = nullptr;

	const char* ValionChar;
	const char* RaylaChar;
	const char* DhionChar;

	iPoint battlePosition;

	PartyType partyType;

};
#endif !__PARTY_H__
