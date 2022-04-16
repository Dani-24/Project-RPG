#ifndef __PLAYER_H__
#define __PLAYER_H__

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

struct SDL_Texture;
struct SDL_Surface;
struct Collider;

class Player :public Character {
public:
	Player(int x, int y);
	~Player();

	// Called before render is available
	bool Awake(pugi::xml_node&);
	bool Start() override;
	bool PreUpdate() override;
	bool Update(float dt) override;
	bool PostUpdate() override;
	bool CleanUp() override;

	void OnCollision(Collider *collider1, Collider* collider2) override;

	//All player movement
	void MovementPlayer(float dt);

private:

	int speed;

public:

	// Animation saved here when battle starts to get it back later
	Animation* mapAnimation;

	// Player animations
	Animation
		walkAnimUp,
		walkAnimDown,
		walkAnimR,
		walkAnimL,
		idleAnimR,
		idleAnimL,
		idleAnimUp,
		idleAnimDown, 
		idleBattleM,
		attackM,
		dashM,
		hitM,
		idleBattleF,
		attackF,
		attackF2,
		hitF,
		dieF;

	int erectionFx;

	int walkFx;

	int walkFxCooldown;

public:

	// Textures
	SDL_Texture* PlayerMTex = nullptr;
	SDL_Texture* PlayerFTex = nullptr;

	// Current Sprite
	bool PlayerErection = true;

	const char* MaleChar;
	const char* FemaleChar;
	const char* electionfxChar;
	const char* WalkfxChar;
	
	bool canMove;

	fPoint cameraSpeed = { 0.1f , 0.1f };

	// Collisions:

	// Distance from player top to his collider
	int colDownDistance;

	// Margin pixels from edge of colliders 
	int margin;

	iPoint mapPosition;
	iPoint battlePosition;

};
#endif !__PLAYER_H__