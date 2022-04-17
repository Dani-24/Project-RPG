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

		currentAnimation = &idleBattle; //Valion start with battle anim

		name = "Valion";
		configName = "valion";

		baseCollider = nullptr;

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