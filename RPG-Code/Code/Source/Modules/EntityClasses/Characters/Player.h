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
#include "DialogSystem.h"

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
		protectM,
		hitM,
		dieM,
		idleBattleF,
		attackF,
		attackF2,
		attackChainF,
		protectF,
		hitF,
		dieF;

	int erectionFx;

	int walkFx;

	int walkFxCooldown;

public:

	// Textures
	SDL_Texture* PlayerMTex = nullptr;
	SDL_Texture* PlayerFTex = nullptr;
	SDL_Texture* BattleMTex = nullptr;
	SDL_Texture* BattleFTex = nullptr;

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

	bool toggleGui = true;

public:
	iPoint townPos = {950, 1000};
	iPoint shopPos = { 69, 238 };
	bool shopPosOn = false;
private:
	int townPosYAxisfix = 5;

	iPoint lastFramePos;
	int showGuiCont;

private: // DIALOGS

	const char* barkeeperDialog[DIALOG_LENGHT] = { 
	"Hola buenas, bienvenido a la taverna",
	"? Desearia tomar algo ?",
	"me quieroo morirrr", 
	"bueno parece que ya funka" 
	};

	const char* trainerDialog[DIALOG_LENGHT] = { 
	"Buenooo miii gentee vamoss ha empezar",
	"animo a todess antes de nada",
	"hoy empezaremos haciendo 20 flexiones",
	"quiero q primero mireis como las hago", 
	"ahora os tocara a vosotres",
	"vamos chiquess que vosotres podeiss!!"
	};

	const char* merchantDialog[DIALOG_LENGHT] = { 
	"HOOOLA, soy Vince con Slap Chop, y esto te va A",
	"FASCINAAAAAAAR",
	"Mira mi huevo!",
	"Un golpe, blandes, papas fritas",
	"Tu gerard, yo gerard? NO mas gerard",
	"Perechini, martini, bambini, lenguini, bikini",
	"COmpra Slap Chop por 5.95€",
	"PARA ORENAR!"
	};

	const char* cockDialog[DIALOG_LENGHT] = { 
	"kiki koko,  coro koko koko ro",
	"kokoroco?",
	"Q te saco la navaja y te rajo tt",
	"digo, kiri kikii!" 
	};

	const char* emilioDialog[DIALOG_LENGHT] = {
	"Lo siento estoy pintando",
	"poyo"
	};

};
#endif !__PLAYER_H__