#ifndef __STAGES_H__
#define __STAGES_H__

#include "Module.h"
#include "GuiButton.h"
#include "Animation.h"

#define TRAFFIC_LIGHT_TIME 500
#define TILE_SIZE 32

struct SDL_Texture;
class Player;
class Cock;

class NPC;
class NormalEnemy;
class Character;

struct Collider;

enum class StageIndex {
	NONE,
	TOWN,
	TAVERN,
	DOJO,
	SHOP,
	SHOPSUB,
	INTRODUCTION,
	WIN,
	LOSE,
	TOWER_0,
	TOWER_1,
	TOWER_2,
	TOWER_3,
	TOWER_4,
	TOWER_BOSS_1,
	TOWER_BOSS_2,
	TOWER_BOSS_3,
	PROLOGUE
};

enum class TLState {
	PASS,
	CAUTION,
	STOP
};

enum class TLOrder {
	VERTICAL,
	UNGAUNGAS,
	HORIZONTAL
};

struct TrafficLight {
	TLState state;

	iPoint position;
	SDL_Rect hitbox;

	SDL_Texture* sprite, * lightSprite;

	Animation animPass, animCaution, animStop;
};

class Car {
public:
	Car(bool goRight, iPoint position)
	{
		this->position = position;

		if (goRight) {
			direction = 1;
		}
		else {
			direction = -1;
		}

		sprite = app->tex->Load("Assets/sprites/trafficLights/cars.png");
	}

public:

	iPoint position;
	float speed = 0, acceleration = 0.1f, maxSpeed = 5;

	// -1 left & 1 right
	int direction;

	SDL_Rect hitbox;
	Collider* collider;

	SDL_Texture* sprite;

	Animation* carType = nullptr;

	int claxonCooldown = 0;
};

class Stages : public Module
{
public:

	Stages(App* application, bool start_enabled = true);

	// Destructor
	virtual ~Stages();

	// Called before render is available
	bool Awake(pugi::xml_node& config);

	// Called before the first frame
	bool Start();

	// Called before all Updates
	bool PreUpdate();

	// Called each loop iteration
	bool Update(float dt);

	// Called before all Updates
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

	void ChangeStage(StageIndex newStage);

private:
	int hitfx1, hitfx2, hitfx3, shieldfx, chdiefx, doorFx, loseFx;

	int introductionFase = 0;

	SDL_Texture* WinScreen;
	SDL_Texture* LoseScreen;
	SDL_Texture* WinMessage;
	SDL_Texture* LoseMessage;

	bool _wait;

public:
	bool pause;

	bool onBattle;

	bool fxbool = false;

	int eAnim = 1, pAnim = 1, vAnim = 1;

	StageIndex actualStage;

	Player* playerPtr;
	List<NPC*>* npcListPtr;
	List<NormalEnemy*>* normalEnemyListPtr;

	List<Character*>* partyListPtr;

	int intStage = 0;

	bool elect;

	SString LoseScreenChar;
	SString WinScreenChar;
	SString LoseTextChar;
	SString WinTextChar;
	SString Hitfx1Char;
	SString Hitfx2Char;
	SString Hitfx3Char;
	SString ShieldfxChar;
	SString ChDiefxChar;
	SString DoorChar;
	SString LosefxChar;


private:

	// TL => Traffic light ---- Pe => Peaton
	TrafficLight TLVertical, TLPeIzq, TLPeDer, TLIzq, TLDer;

	void TrafficLightSystem();
	void CarManagement();
	bool DeleteCars(ListItem<Car*>* c);

	int changeTL, cautionTL;

	TLOrder tlOrder;

	Animation	carRedL,
		carRedR,
		carBlueL,
		carBlueR,
		carGreenL,
		carGreenR,
		carPinkL,
		carPinkR,
		carGreyL,
		carGreyR;

	List<Car*> cars;

	int randomCarCount;

	int fxCar1, fxCar2, fxCar3, fxCar4;
};

#endif // __STAGES_H__