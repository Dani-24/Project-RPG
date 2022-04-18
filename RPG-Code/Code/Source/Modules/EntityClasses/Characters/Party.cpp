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
	position = { 0,0 };
	this->partyType = partyType;

	switch (partyType) {
	case PartyType::VALION:

		
		//IDLE
		idleBattle.PushBack({ 0, 0, 231, 141 });
		idleBattle.PushBack({ 231, 0, 231, 141 });
		idleBattle.PushBack({ 462, 0, 231, 141 });
		idleBattle.PushBack({ 693, 0, 231, 141 });
		idleBattle.PushBack({ 924, 0, 231, 141 });
		idleBattle.PushBack({ 1155, 0, 231, 141 });

		idleBattle.speed = 0.01f;

		//ATTACK 1
		attackAnim1.PushBack({ 0, 141, 231, 141 });
		attackAnim1.PushBack({ 231, 141, 231, 141 });
		attackAnim1.PushBack({ 462, 141, 231, 141 });
		attackAnim1.PushBack({ 693, 141, 231, 141 });
		attackAnim1.PushBack({ 924, 141, 231, 141 });
		attackAnim1.PushBack({ 1155, 141, 231, 141 });
		attackAnim1.PushBack({ 1386, 141, 231, 141 });
		attackAnim1.PushBack({ 1617, 141, 231, 141 });

		attackAnim1.speed = 0.006f;

		//ATTACK 2
		attackAnim2.PushBack({ 0, 282, 231, 141 });
		attackAnim2.PushBack({ 231, 282, 231, 141 });
		attackAnim2.PushBack({ 462, 282, 231, 141 });
		attackAnim2.PushBack({ 693, 282, 231, 141 });
		attackAnim2.PushBack({ 924, 282, 231, 141 });
		attackAnim2.PushBack({ 1155, 282, 231, 141 });
		attackAnim2.PushBack({ 1386, 282, 231, 141 });
		attackAnim2.PushBack({ 1617, 282, 231, 141 });

		attackAnim2.speed = 0.006f;

		//HIT ANIM
		hitAnim.PushBack({ 0, 423, 231, 141 });
		hitAnim.PushBack({ 231, 423, 231, 141 });
		hitAnim.PushBack({ 462, 423, 231, 141 });
		hitAnim.PushBack({ 693, 423, 231, 141 });

		hitAnim.speed = 0.006f;

		//DEATH
		deathAnim.PushBack({ 0, 564, 231, 141 });
		deathAnim.PushBack({ 231, 564, 231, 141 });
		deathAnim.PushBack({ 462, 564, 231, 141 });
		deathAnim.PushBack({ 693, 564, 231, 141 });
		deathAnim.PushBack({ 924, 564, 231, 141 });
		deathAnim.PushBack({ 1155, 564, 231, 141 });
		deathAnim.PushBack({ 1386, 564, 231, 141 });

		deathAnim.speed = 0.006f;

		//JUMP
		jumpAnim.PushBack({ 0, 705, 231, 141 });
		jumpAnim.PushBack({ 231, 705, 231, 141 });

		jumpAnim.speed = 0.006f;

		//FALL
		fallAnim.PushBack({ 0, 846, 231, 141 });
		fallAnim.PushBack({ 231, 846, 231, 141 });

		fallAnim.speed = 0.006f;

		//RUN
		runAnim.PushBack({ 0, 973, 231, 141 });
		runAnim.PushBack({ 231, 973, 231, 141 });
		runAnim.PushBack({ 462, 973, 231, 141 });
		runAnim.PushBack({ 693, 973, 231, 141 });
		runAnim.PushBack({ 924, 973, 231, 141 });
		runAnim.PushBack({ 1155, 973, 231, 141 });
		runAnim.PushBack({ 1386, 973, 231, 141 });
		runAnim.PushBack({ 1617, 973, 231, 141 });

		runAnim.speed = 0.006f;

		name = "Valion";
		configName = "valion";

		baseCollider = nullptr;

		position = { x,y };
		battlePosition = { x, y };

		break;
	case PartyType::RAYLA:
		break;
	case PartyType::DHION:
		break;
	}

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
		stats = new Stats(1, 15, 10, 3, 10, 16);
		spriteText = app->tex->Load(ValionChar);
		break;
	}
	
	return ret;
}

bool Party::PreUpdate()
{
	// DEBUG PLAYER POSITION
	LOG("position x %d y %d", position.x, position.y);

	return true;
}

bool Party::Update(float dt) 
{
	bool ret = true;
	currentAnimation->Update(dt);
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
	app->tex->UnLoad(spriteText);

	return true;
}