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

	//All player movement
	void MovementPlayer(float dt);

public:

	float playerSpeed;

	// Current Sprite
	bool PlayerErection = true;

	//Direction
	int PlayerDirectionUp = 0;
	int PlayerDirectionRight = 0;

	//cargar textura del jugador
	SDL_Texture* PlayerMTex = nullptr;
	SDL_Texture* PlayerFTex = nullptr;

	//player animations
	Animation* currentAnimation = nullptr;
	Animation
		walkAnimUp,
		walkAnimDown,
		walkAnimR,
		walkAnimL,
		idleAnimR,
		idleAnimL,
		idleAnimUp,
		idleAnimDown;

	int yesFx;

public:
	const char* MaleChar;
	bool canMove;

	fPoint cameraSpeed = { 0.1f , 0.1f };

};
#endif !__PLAYER_H__