#include "Player.h"

#include "App.h"
#include "Render.h"
#include "Audio.h"
#include "Textures.h"
#include "Input.h"
#include "Player.h"
#include "Log.h"
#include "Window.h"
#include "Scene.h"
#include "Map.h"
#include "Stages.h"
#include "Battle.h"
#include "FadeToBlack.h"
#include "Party.h"

Party::Party(PartyType partyType, int x, int y) : Character(CharacterType::PARTY)
{

	this->partyType = partyType;

	switch (partyType) {
	case PartyType::VALION:

		//IDLE
		idleBattle.PushBack({ 0 * BATTLE_SIZE , 0 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		idleBattle.PushBack({ 1 * BATTLE_SIZE , 0 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		idleBattle.PushBack({ 2 * BATTLE_SIZE , 0 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		idleBattle.PushBack({ 3 * BATTLE_SIZE , 0 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		idleBattle.PushBack({ 4 * BATTLE_SIZE , 0 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		idleBattle.PushBack({ 5 * BATTLE_SIZE , 0 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });

		idleBattle.loop = true;
		idleBattle.speed = 0.01f;

		//ATTACK 1
		attackAnim1.PushBack({ 0 * BATTLE_SIZE , 1 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		attackAnim1.PushBack({ 1 * BATTLE_SIZE , 1 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		attackAnim1.PushBack({ 2 * BATTLE_SIZE , 1 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		attackAnim1.PushBack({ 3 * BATTLE_SIZE , 1 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		attackAnim1.PushBack({ 4 * BATTLE_SIZE , 1 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		attackAnim1.PushBack({ 5 * BATTLE_SIZE , 1 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		attackAnim1.PushBack({ 6 * BATTLE_SIZE , 1 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		attackAnim1.PushBack({ 7 * BATTLE_SIZE , 1 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });

		attackAnim1.PushBack({ 0 * BATTLE_SIZE , 0 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		attackAnim1.PushBack({ 1 * BATTLE_SIZE , 0 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		attackAnim1.PushBack({ 2 * BATTLE_SIZE , 0 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		attackAnim1.PushBack({ 3 * BATTLE_SIZE , 0 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		attackAnim1.PushBack({ 4 * BATTLE_SIZE , 0 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		attackAnim1.PushBack({ 5 * BATTLE_SIZE , 0 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });

		attackAnim1.loop = false;
		attackAnim1.speed = 0.008f;

		//ATTACK 2
		attackAnim2.PushBack({ 0 * BATTLE_SIZE , 2 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		attackAnim2.PushBack({ 1 * BATTLE_SIZE , 2 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		attackAnim2.PushBack({ 2 * BATTLE_SIZE , 2 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		attackAnim2.PushBack({ 3 * BATTLE_SIZE , 2 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		attackAnim2.PushBack({ 4 * BATTLE_SIZE , 2 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		attackAnim2.PushBack({ 5 * BATTLE_SIZE , 2 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		attackAnim2.PushBack({ 6 * BATTLE_SIZE , 2 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		attackAnim2.PushBack({ 7 * BATTLE_SIZE , 2 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });

		attackAnim2.PushBack({ 0 * BATTLE_SIZE , 0 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		attackAnim2.PushBack({ 1 * BATTLE_SIZE , 0 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		attackAnim2.PushBack({ 2 * BATTLE_SIZE , 0 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		attackAnim2.PushBack({ 3 * BATTLE_SIZE , 0 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		attackAnim2.PushBack({ 4 * BATTLE_SIZE , 0 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		attackAnim2.PushBack({ 5 * BATTLE_SIZE , 0 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });

		attackAnim2.loop = false;
		attackAnim2.speed = 0.01f;

		protectedAnim.PushBack({ 0 * BATTLE_SIZE , 2 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });

		//HIT ANIM
		hitAnim.PushBack({ 0 * BATTLE_SIZE , 3 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		hitAnim.PushBack({ 1 * BATTLE_SIZE , 3 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		hitAnim.PushBack({ 2 * BATTLE_SIZE , 3 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		hitAnim.PushBack({ 3 * BATTLE_SIZE , 3 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });

		hitAnim.loop = false;
		hitAnim.speed = 0.006f;

		//DEATH
		deathAnim.PushBack({ 0 * BATTLE_SIZE , 4 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		deathAnim.PushBack({ 1 * BATTLE_SIZE , 4 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		deathAnim.PushBack({ 2 * BATTLE_SIZE , 4 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		deathAnim.PushBack({ 3 * BATTLE_SIZE , 4 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		deathAnim.PushBack({ 4 * BATTLE_SIZE , 4 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		deathAnim.PushBack({ 5 * BATTLE_SIZE , 4 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		deathAnim.PushBack({ 6 * BATTLE_SIZE , 4 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });

		deathAnim.loop = false;
		deathAnim.speed = 0.006f;

		//JUMP
		jumpAnim.PushBack({ 0 * BATTLE_SIZE , 5 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		jumpAnim.PushBack({ 1 * BATTLE_SIZE , 5 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });

		jumpAnim.loop = true;
		jumpAnim.speed = 0.006f;

		//FALL
		fallAnim.PushBack({ 0 * BATTLE_SIZE , 6 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		fallAnim.PushBack({ 1 * BATTLE_SIZE , 6 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });

		fallAnim.loop = true;
		fallAnim.speed = 0.006f;

		//RUN
		runAnim.PushBack({ 0 * BATTLE_SIZE , 7 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		runAnim.PushBack({ 1 * BATTLE_SIZE , 7 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		runAnim.PushBack({ 2 * BATTLE_SIZE , 7 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		runAnim.PushBack({ 3 * BATTLE_SIZE , 7 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		runAnim.PushBack({ 4 * BATTLE_SIZE , 7 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		runAnim.PushBack({ 5 * BATTLE_SIZE , 7 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		runAnim.PushBack({ 6 * BATTLE_SIZE , 7 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		runAnim.PushBack({ 7 * BATTLE_SIZE , 7 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });

		runAnim.loop = true;
		runAnim.speed = 0.006f;

		name = "Valion";
		configName = "valion";

		zoom = 2;

		break;
	case PartyType::RAYLA:

		//IDLE
		idleBattle.PushBack({ 0 * BATTLE_SIZE , 5 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		idleBattle.PushBack({ 1 * BATTLE_SIZE , 5 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		idleBattle.PushBack({ 2 * BATTLE_SIZE , 5 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		idleBattle.PushBack({ 3 * BATTLE_SIZE , 5 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		idleBattle.PushBack({ 4 * BATTLE_SIZE , 5 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		idleBattle.PushBack({ 5 * BATTLE_SIZE , 5 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		idleBattle.PushBack({ 6 * BATTLE_SIZE , 5 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		idleBattle.PushBack({ 7 * BATTLE_SIZE , 5 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		idleBattle.PushBack({ 8 * BATTLE_SIZE , 5 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		idleBattle.PushBack({ 9 * BATTLE_SIZE , 5 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });

		idleBattle.loop = true;
		idleBattle.speed = 0.01f;

		//ATTACK 1
		attackAnim1.PushBack({ 0 * BATTLE_SIZE , 1 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		attackAnim1.PushBack({ 1 * BATTLE_SIZE , 1 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		attackAnim1.PushBack({ 2 * BATTLE_SIZE , 1 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		attackAnim1.PushBack({ 3 * BATTLE_SIZE , 1 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		attackAnim1.PushBack({ 4 * BATTLE_SIZE , 1 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		attackAnim1.PushBack({ 5 * BATTLE_SIZE , 1 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });

		attackAnim1.PushBack({ 0 * BATTLE_SIZE , 5 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		attackAnim1.PushBack({ 1 * BATTLE_SIZE , 5 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		attackAnim1.PushBack({ 2 * BATTLE_SIZE , 5 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		attackAnim1.PushBack({ 3 * BATTLE_SIZE , 5 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		attackAnim1.PushBack({ 4 * BATTLE_SIZE , 5 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		attackAnim1.PushBack({ 5 * BATTLE_SIZE , 5 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		attackAnim1.PushBack({ 6 * BATTLE_SIZE , 5 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		attackAnim1.PushBack({ 7 * BATTLE_SIZE , 5 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		attackAnim1.PushBack({ 8 * BATTLE_SIZE , 5 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		attackAnim1.PushBack({ 9 * BATTLE_SIZE , 5 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });

		attackAnim1.loop = false;
		attackAnim1.speed = 0.008f;

		//ATTACK 2
		attackAnim2.PushBack({ 0 * BATTLE_SIZE , 1 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		attackAnim2.PushBack({ 1 * BATTLE_SIZE , 1 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		attackAnim2.PushBack({ 2 * BATTLE_SIZE , 1 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		attackAnim2.PushBack({ 3 * BATTLE_SIZE , 1 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		attackAnim2.PushBack({ 4 * BATTLE_SIZE , 1 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		attackAnim2.PushBack({ 5 * BATTLE_SIZE , 1 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });

		attackAnim2.PushBack({ 0 * BATTLE_SIZE , 5 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		attackAnim2.PushBack({ 1 * BATTLE_SIZE , 5 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		attackAnim2.PushBack({ 2 * BATTLE_SIZE , 5 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		attackAnim2.PushBack({ 3 * BATTLE_SIZE , 5 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		attackAnim2.PushBack({ 4 * BATTLE_SIZE , 5 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		attackAnim2.PushBack({ 5 * BATTLE_SIZE , 5 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		attackAnim2.PushBack({ 6 * BATTLE_SIZE , 5 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		attackAnim2.PushBack({ 7 * BATTLE_SIZE , 5 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		attackAnim2.PushBack({ 8 * BATTLE_SIZE , 5 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		attackAnim2.PushBack({ 9 * BATTLE_SIZE , 5 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });

		attackAnim2.loop = false;
		attackAnim2.speed = 0.01f;

		protectedAnim.PushBack({ 0 * BATTLE_SIZE , 4 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });

		//HIT ANIM
		hitAnim.PushBack({ 0 * BATTLE_SIZE , 4 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		hitAnim.PushBack({ 1 * BATTLE_SIZE , 4 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		hitAnim.PushBack({ 2 * BATTLE_SIZE , 4 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });

		hitAnim.loop = false;
		hitAnim.speed = 0.006f;

		//DEATH
		deathAnim.PushBack({ 0 * BATTLE_SIZE , 2 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		deathAnim.PushBack({ 1 * BATTLE_SIZE , 2 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		deathAnim.PushBack({ 2 * BATTLE_SIZE , 2 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		deathAnim.PushBack({ 3 * BATTLE_SIZE , 2 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		deathAnim.PushBack({ 4 * BATTLE_SIZE , 2 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		deathAnim.PushBack({ 5 * BATTLE_SIZE , 2 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		deathAnim.PushBack({ 6 * BATTLE_SIZE , 2 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		deathAnim.PushBack({ 7 * BATTLE_SIZE , 2 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });

		deathAnim.loop = false;
		deathAnim.speed = 0.006f;

		//JUMP
		jumpAnim.PushBack({ 0 * BATTLE_SIZE , 100 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		jumpAnim.PushBack({ 1 * BATTLE_SIZE , 100 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });

		jumpAnim.loop = true;
		jumpAnim.speed = 0.006f;

		//FALL
		fallAnim.PushBack({ 0 * BATTLE_SIZE , 3 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		fallAnim.PushBack({ 1 * BATTLE_SIZE , 3 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });

		fallAnim.loop = true;
		fallAnim.speed = 0.006f;

		//RUN
		runAnim.PushBack({ 0 * BATTLE_SIZE , 3 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		runAnim.PushBack({ 1 * BATTLE_SIZE , 3 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });

		runAnim.loop = true;
		runAnim.speed = 0.006f;

		name = "Rayla";
		configName = "rayla";

		zoom = 3;

		break;
	case PartyType::DHION:

		//IDLE
		idleBattle.PushBack({ 0 * BATTLE_SIZE , 5 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		idleBattle.PushBack({ 1 * BATTLE_SIZE , 5 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		idleBattle.PushBack({ 2 * BATTLE_SIZE , 5 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		idleBattle.PushBack({ 3 * BATTLE_SIZE , 5 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		idleBattle.PushBack({ 4 * BATTLE_SIZE , 5 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		idleBattle.PushBack({ 5 * BATTLE_SIZE , 5 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		idleBattle.PushBack({ 6 * BATTLE_SIZE , 5 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		idleBattle.PushBack({ 7 * BATTLE_SIZE , 5 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });

		idleBattle.loop = true;
		idleBattle.speed = 0.01f;

		//ATTACK 1
		attackAnim1.PushBack({ 0 * BATTLE_SIZE , 0 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		attackAnim1.PushBack({ 1 * BATTLE_SIZE , 0 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		attackAnim1.PushBack({ 2 * BATTLE_SIZE , 0 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		attackAnim1.PushBack({ 3 * BATTLE_SIZE , 0 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		attackAnim1.PushBack({ 4 * BATTLE_SIZE , 0 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });

		attackAnim1.PushBack({ 0 * BATTLE_SIZE , 5 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		attackAnim1.PushBack({ 1 * BATTLE_SIZE , 5 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		attackAnim1.PushBack({ 2 * BATTLE_SIZE , 5 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		attackAnim1.PushBack({ 3 * BATTLE_SIZE , 5 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		attackAnim1.PushBack({ 4 * BATTLE_SIZE , 5 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		attackAnim1.PushBack({ 5 * BATTLE_SIZE , 5 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		attackAnim1.PushBack({ 6 * BATTLE_SIZE , 5 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		attackAnim1.PushBack({ 7 * BATTLE_SIZE , 5 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });

		attackAnim1.loop = false;
		attackAnim1.speed = 0.008f;

		//ATTACK 2
		attackAnim2.PushBack({ 0 * BATTLE_SIZE , 1 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		attackAnim2.PushBack({ 1 * BATTLE_SIZE , 1 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		attackAnim2.PushBack({ 2 * BATTLE_SIZE , 1 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		attackAnim2.PushBack({ 3 * BATTLE_SIZE , 1 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		attackAnim2.PushBack({ 4 * BATTLE_SIZE , 1 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });

		attackAnim2.PushBack({ 0 * BATTLE_SIZE , 5 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		attackAnim2.PushBack({ 1 * BATTLE_SIZE , 5 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		attackAnim2.PushBack({ 2 * BATTLE_SIZE , 5 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		attackAnim2.PushBack({ 3 * BATTLE_SIZE , 5 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		attackAnim2.PushBack({ 4 * BATTLE_SIZE , 5 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		attackAnim2.PushBack({ 5 * BATTLE_SIZE , 5 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		attackAnim2.PushBack({ 6 * BATTLE_SIZE , 5 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		attackAnim2.PushBack({ 7 * BATTLE_SIZE , 5 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });

		attackAnim2.loop = false;
		attackAnim2.speed = 0.01f;

		protectedAnim.PushBack({ 0 * BATTLE_SIZE , 4 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });

		//HIT ANIM
		hitAnim.PushBack({ 0 * BATTLE_SIZE , 7 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		hitAnim.PushBack({ 1 * BATTLE_SIZE , 7 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		hitAnim.PushBack({ 2 * BATTLE_SIZE , 7 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });

		hitAnim.loop = false;
		hitAnim.speed = 0.006f;

		//DEATH
		deathAnim.PushBack({ 0 * BATTLE_SIZE , 3 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		deathAnim.PushBack({ 1 * BATTLE_SIZE , 3 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		deathAnim.PushBack({ 2 * BATTLE_SIZE , 3 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		deathAnim.PushBack({ 3 * BATTLE_SIZE , 3 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		deathAnim.PushBack({ 4 * BATTLE_SIZE , 3 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		deathAnim.PushBack({ 5 * BATTLE_SIZE , 3 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		deathAnim.PushBack({ 6 * BATTLE_SIZE , 3 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		deathAnim.PushBack({ 7 * BATTLE_SIZE , 3 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });

		deathAnim.loop = false;
		deathAnim.speed = 0.006f;

		//JUMP
		jumpAnim.PushBack({ 0 * BATTLE_SIZE , 100 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		jumpAnim.PushBack({ 1 * BATTLE_SIZE , 100 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });

		jumpAnim.loop = true;
		jumpAnim.speed = 0.006f;

		//FALL
		fallAnim.PushBack({ 0 * BATTLE_SIZE , 100 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		fallAnim.PushBack({ 1 * BATTLE_SIZE , 100 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });

		fallAnim.loop = true;
		fallAnim.speed = 0.006f;

		//RUN
		runAnim.PushBack({ 0 * BATTLE_SIZE , 4 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
		runAnim.PushBack({ 1 * BATTLE_SIZE , 4 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });

		runAnim.loop = true;
		runAnim.speed = 0.006f;

		name = "Dhion";
		configName = "dhion";

		zoom = 3;
		break;
	}

	baseCollider = nullptr;

	position = { x,y };
	battlePosition = { x, y };

	idleBattle.loop = true;
	
	currentAnimation = &idleBattle;

	isAlive = true;
}

// Destructor
Party::~Party()
{}

bool Party::Awake(pugi::xml_node& config)
{
	LOG("Init Image library, ta guapa la libreria de imagenes llamada player");
	bool ret = true;
	LOG("Num in config: %d", config.child("exampleNumber").attribute("num").as_int());

	ValionChar = "Assets/sprites/characters/wizard/wizardBattleSprite.png";
	RaylaChar = "Assets/sprites/characters/archer/combat/a_battle_spritesheet.png";
	DhionChar = "Assets/sprites/characters/lancer/combat/l_battle_spritesheet.png";

	return ret;
}

bool Party::Start()
{
	LOG("start Player");
	bool ret = true;

	//player start with idle anim
	currentAnimation = &idleBattle;

	switch (partyType) {
	case PartyType::VALION:

		//stats = new Stats(1, 15, 10, 3, 10, 32);
		if (app->scene->partyList.At(0)->data->stats->level > 1) {
			stats = new Stats(app->scene->partyList.At(0)->data->stats->level - 1, 15, 12, 10, 15, 16);
		}
		else {
			stats = new Stats(1, 15, 12, 10, 15, 16);
		}
		
		spriteTex = app->tex->Load(ValionChar);

		spriteFace = app->tex->Load("Assets/sprites/faces/wizard_gui.png");
		break;

	case PartyType::RAYLA:
		if (app->scene->partyList.At(0)->data->stats->level > 1) {
			stats = new Stats(app->scene->partyList.At(0)->data->stats->level - 1, 15, 10, 8, 12, 28);
		}
		else {
			stats = new Stats(1, 15, 10, 8, 12, 28);
		}
		spriteTex = app->tex->Load(RaylaChar);

		spriteFace = app->tex->Load("Assets/sprites/faces/archer_gui.png");
		break;
	case PartyType::DHION:

		if (app->scene->partyList.At(0)->data->stats->level > 1) {
			stats = new Stats(app->scene->partyList.At(0)->data->stats->level - 1, 24, 7, 12, 7, 22);
		}
		else {
			stats = new Stats(1, 24, 7, 12, 7, 22);
		}
		spriteTex = app->tex->Load(DhionChar);

		spriteFace = app->tex->Load("Assets/sprites/faces/lancer_gui.png");
		break;
	}

	
	return ret;
}

bool Party::PreUpdate()
{
	// DEBUG PLAYER POSITION
	//LOG("position x %d y %d", position.x, position.y);

	return true;
}

bool Party::Update(float dt) 
{
	bool ret = true;
	if (currentAnimation != nullptr) {
		currentAnimation->Update(dt);
	}
	return ret;
}

bool Party::PostUpdate()
{
	bool ret = true;

	return true;
}

bool Party::CleanUp() {

	//Collisions
	app->collisions->RemoveCollider(baseCollider);
	app->collisions->RemoveCollider(battleCollider);

	baseCollider = nullptr;
	delete baseCollider;

	//Animations
	currentAnimation = nullptr;
	delete currentAnimation;

	//Textures
	app->tex->UnLoad(spriteTex);
	app->tex->UnLoad(spriteFace);

	return true;
}