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

#include <vector>

#include "Animation.h"

struct SDL_Texture;
struct SDL_Surface;
struct Collider;

class Player :public Character {
public:
	Player();
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

	// Player animations
	Animation
		walkAnimUp,
		walkAnimDown,
		walkAnimR,
		walkAnimL,
		idleAnimR,
		idleAnimL,
		idleAnimUp,
		idleAnimDown;

	int erectionFx;

public:

	// Textures
	SDL_Texture* PlayerMTex = nullptr;
	SDL_Texture* PlayerFTex = nullptr;

	// Current Sprite
	bool PlayerErection = true;

	const char* MaleChar;
	bool canMove;

	fPoint cameraSpeed = { 0.1f , 0.1f };

	// Collisions:

	// Distance from player top to his collider
	int colDownDistance;

	// Margin pixels from edge of colliders 
	int margin;

};
#endif !__PLAYER_H__