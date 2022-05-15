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
	bool _wait;

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

	SDL_Texture* male_character_face_gui;
	SDL_Texture* female_character_face_gui;

	// Current Sprite
	bool PlayerErection = true;

	const char* MaleChar;
	const char* FemaleChar;
	const char* electionfxChar;
	const char* WalkfxChar;
	const char* interactionButtonChar;
	
	bool canMove;

	fPoint cameraSpeed = { 0.1f , 0.1f };

	int timeWalkingVer;
	int timeWalkingHor;

	// Collisions:

	// Distance from player top to his collider
	int colDownDistance;
	int colRightDistance;

	// Margin pixels from edge of colliders 
	int margin;

	iPoint mapPosition;
	iPoint battlePosition;

	bool toggleGui = true;

	int PlayerMoney = 0;

public:
	iPoint townPos = {950, 1730};
	iPoint shopPos = { 69, 238 };
	bool shopPosOn = false;
	
	iPoint tower0Pos = { 364, 600 };
	iPoint tower1Pos = { 1212, 1651 };
	iPoint tower2Pos = { 1850, 2198 };
	iPoint tower3Pos = { 393, 697 };
private:
	int townPosYAxisfix = 5;
	int tower0PosYAxisfix = 5;
	int tower1PosYAxisfix = 5;
	int tower2PosYAxisfix = 5;
	int tower3PosYAxisfix = 5;

	iPoint lastFramePos;
	int showGuiCont;

	SDL_Texture* interactionButton;
	Animation interactionButtonJustSpace;
	bool printInteractionButt = false;
	//variable para que no pete con mando
	bool wait;

public: // DIALOGS

	const char* barkeeperDialog[DIALOG_LENGHT] = { 
	"Hello !, welcome to the tavern",
	"Whould you like something to drink ?",
	". . .", 
	". . . . . .",
	"I will interpret your silence as a no" 
	};

	const char* trainerDialog[DIALOG_LENGHT] = { 
	"jo jo jo",
	"So you are the new one",
	"Common, show me what you know",
	"Fight with the enemies on your right", 
	"and destroy them before they destroy you",
	"A tope jefe de equipo"
	};

	const char* merchantDialog[DIALOG_LENGHT] = { 
	"HOOOLA!, Hellooo!, soy Vincen�",
	"We have no products right now",
	"You know , the truck riot ...",
	"Anyways, you can take your time looking the shop",
	"Aunque all we have is exclusivo de muestra",
	"As you can see, not for sale", 
	"We hope to restock soon!"
	};

	const char* cockDialog[DIALOG_LENGHT] = { 
	"kokoroco?",
	"If you want a chikita guide I can help you",
	"This red house is the Shop",
	"They sell everything, or that's supposed",
	"On the right above the river there's the Tavern",
	"pretty much popular between the rookies like you",
	"If they are not consummed by the tower . . .",
	"they are consummed because of the alcohol",
	"koko ro ko",
	"Finally, going up this street . . .",
	"on the right side of the tavern, there is the Dojo",
	"Test there your habilities with some enemies",
	"And avoid dying there ( it will be a good detail )",
	"You will be able to recover all your health",
	"in the fountain following this left street",
	"ko ko",
	"At the north you will find the Tower of Camion-kun",
	"Although we had closed it because nobody wants to go",
	"And . . . Emilio started to paint the outside",
	"co ro ko",
	"That's all",
	"Now give me a bit of bread in exchange of the info"
	};

	const char* emilioDialog[DIALOG_LENGHT] = {
	"Sorry I'm painting . . .",
	"poyo"
	};

	const char* fuenteDialog[DIALOG_LENGHT] = {
	"HP restored to all party members"
	};

	const char* cartelSudTownDialog[DIALOG_LENGHT] = {
	"Anonymous Developer: Uhuhu Sample Text uhu",
	"Use WASD to move your character",
	"If you see a NPC, try talking with it with SPACE",
	"Some Villager: Explore the town as you like!",
	"Anonymous: Feed the chicken plz",
	"The Tower is currently unavailable",
	"Remember that you have an extra party member",
	"Just a developing gift :D"
	};

	void Interact(NPCType, const char* [DIALOG_LENGHT]);

};
#endif !__PLAYER_H__