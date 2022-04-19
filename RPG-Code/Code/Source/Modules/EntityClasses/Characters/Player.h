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
	const char* interactionButtonChar;
	
	bool canMove;

	fPoint cameraSpeed = { 0.1f , 0.1f };

	// Collisions:

	// Distance from player top to his collider
	int colDownDistance;
	int colRightDistance;

	// Margin pixels from edge of colliders 
	int margin;

	iPoint mapPosition;
	iPoint battlePosition;

	bool toggleGui = true;

public:
	iPoint townPos = {950, 1730};
	iPoint shopPos = { 69, 238 };
	bool shopPosOn = false;
private:
	int townPosYAxisfix = 5;

	iPoint lastFramePos;
	int showGuiCont;

	SDL_Texture* interactionButton;
	Animation interactionButtonJustSpace;
	bool printInteractionButt = false;

private: // DIALOGS

	const char* barkeeperDialog[DIALOG_LENGHT] = { 
	"Hello !, welcome to the tavern",
	"Whould you like something to drink ?",
	". . .", 
	". . . . . .",
	"I will interpret your silence as a No" 
	};

	const char* trainerDialog[DIALOG_LENGHT] = { 
	"jo jo jo",
	"Con que tu eres el nuevo",
	"Venga, demuestrame lo que vales",
	"Combate contra los enemigos que hay a tu derecha", 
	"y acaba con ellos antes de que ellos acaben contigo",
	"A tope jefe de equipo"
	};

	const char* merchantDialog[DIALOG_LENGHT] = { 
	"HOOOLA!, Hellooo!, soy Vincenç",
	"We have NO products right now",
	"You know , the truck riot ...",
	"Anyways, you can take your time looking the shop",
	"Aunque all we have is exclusivo de muestra",
	"As you can see, not for sale", 
	"We hope to restock soon!"
	};

	const char* cockDialog[DIALOG_LENGHT] = { 
	"kokoroco?",
	"Si quieres una chikita guia yo me encargo",
	"Esta casita roja de aqui es la tienda",
	"Venden de todo, o eso se supone",
	"A la derecha sobre el canal se encuentra la taverna",
	"bastante popular entre los novatos como tu",
	"O son consumidos por la maldad de la torre . . .",
	"O bien son consumidos por el alcohol.",
	"koko ro ko",
	"Por ultimo, subiendo esta calle . . .",
	"justo a la derecha de la taverna esta el dojo",
	"Pon a prueba tus habilidades contra algun enemigo",
	"Y evita morir en el proceso, seria un buen detalle",
	"ko ko",
	"Ah, al norte encontraras la torre de Camion-kun",
	"Aunque la hemos cerrado ya que nadie quiere ir",
	"y Emilio se ha puesto a pintarla por fuera",
	"co ro ko",
	"Ahora me debes un cacho pan a cambio de esta info."
	};

	const char* emilioDialog[DIALOG_LENGHT] = {
	"Sorry I'm painting . . .",
	"poyo"
	};

	const char* fuenteDialog[DIALOG_LENGHT] = {
	"HP restored"
	};

	void Interact(NPCType, const char* [DIALOG_LENGHT]);

};
#endif !__PLAYER_H__