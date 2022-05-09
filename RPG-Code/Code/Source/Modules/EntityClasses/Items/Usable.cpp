#include "EntityManager.h"

#include "Entity.h"
#include "StaticEntity.h"
#include "Item.h"
#include "Usable.h"


Usable::Usable(UsableType usableType) : Item(ItemType::USABLE)
{
	this->usableType = usableType;
}

Usable::~Usable()
{}

bool Usable::Awake(pugi::xml_node& config)
{
	return true;
}

// Called before the first frame
bool Usable::Start()
{
	switch (usableType) {

	case UsableType::APPLE:
		spriteTex = app->tex->Load("Assets/items/items2.png");
		spriteRect = { 0 * ITEM_SIZE, 0 * ITEM_SIZE, ITEM_SIZE, ITEM_SIZE };
		break;

	case UsableType::LIFE_POTION:
		spriteTex = app->tex->Load("Assets/items/items2.png");
		spriteRect = { 13 * ITEM_SIZE, 11 * ITEM_SIZE, ITEM_SIZE, ITEM_SIZE };
		break;

	case UsableType::PIE:
		spriteTex = app->tex->Load("Assets/items/items2.png");
		spriteRect = { 5 * ITEM_SIZE, 0 * ITEM_SIZE, ITEM_SIZE, ITEM_SIZE };
		break;

	case UsableType::DELICIOUS_PIE:
		spriteTex = app->tex->Load("Assets/items/items2.png");
		spriteRect = { 14 * ITEM_SIZE, 1 * ITEM_SIZE, ITEM_SIZE, ITEM_SIZE };
		break;

	case UsableType::CANDY:
		spriteTex = app->tex->Load("Assets/items/items2.png");
		spriteRect = { 15 * ITEM_SIZE, 2 * ITEM_SIZE, ITEM_SIZE, ITEM_SIZE };
		break;


	case UsableType::ELIXIR:
		spriteTex = app->tex->Load("Assets/items/items2.png");
		spriteRect = { 14 * ITEM_SIZE, 0 * ITEM_SIZE, ITEM_SIZE, ITEM_SIZE };
		break;

	case UsableType::DYNAMITE:
		spriteTex = app->tex->Load("Assets/items/items2.png");
		spriteRect = { 3 * ITEM_SIZE, 7 * ITEM_SIZE, ITEM_SIZE, ITEM_SIZE };
		break;

	case UsableType::BOMB:
		spriteTex = app->tex->Load("Assets/items/items2.png");
		spriteRect = { 15 * ITEM_SIZE, 13 * ITEM_SIZE, ITEM_SIZE, ITEM_SIZE };
		break;

	case UsableType::SUPER_BOMB:
		spriteTex = app->tex->Load("Assets/items/items2.png");
		spriteRect = { 0 * ITEM_SIZE, 7 * ITEM_SIZE, ITEM_SIZE, ITEM_SIZE };
		break;


	case UsableType::WILL_TO_LIFE:
		spriteTex = app->tex->Load("Assets/items/items2.png");
		spriteRect = { 15 * ITEM_SIZE, 14 * ITEM_SIZE, ITEM_SIZE, ITEM_SIZE };
		break;
	

	case UsableType::CHEST_KEY:
		spriteTex = app->tex->Load("Assets/items/items2.png");
		spriteRect = { 4 * ITEM_SIZE, 7 * ITEM_SIZE, ITEM_SIZE, ITEM_SIZE };
		break;

	case UsableType::DOOR_KEY:
		spriteTex = app->tex->Load("Assets/items/items2.png");
		spriteRect = { 5 * ITEM_SIZE, 7 * ITEM_SIZE, ITEM_SIZE, ITEM_SIZE };
		break;


	case UsableType::TEDDY_BEAR:
		spriteTex = app->tex->Load("Assets/items/items2.png");
		spriteRect = { 3 * ITEM_SIZE, 13 * ITEM_SIZE, ITEM_SIZE, ITEM_SIZE };
		break;

	case UsableType::LETTER:
		spriteTex = app->tex->Load("Assets/items/items2.png");
		spriteRect = { 5 * ITEM_SIZE, 13 * ITEM_SIZE, ITEM_SIZE, ITEM_SIZE };
		break;

	case UsableType::CLOSE_PARCHMENT:
		spriteTex = app->tex->Load("Assets/items/items2.png");
		spriteRect = { 7 * ITEM_SIZE, 13 * ITEM_SIZE, ITEM_SIZE, ITEM_SIZE };
		break;
	case UsableType::OPEN_PARCHMENT:
		spriteTex = app->tex->Load("Assets/items/items2.png");
		spriteRect = { 6 * ITEM_SIZE, 13 * ITEM_SIZE, ITEM_SIZE, ITEM_SIZE };
		break;


	case UsableType::BONE:
		spriteTex = app->tex->Load("Assets/items/items2.png");
		spriteRect = { 2 * ITEM_SIZE, 12 * ITEM_SIZE, ITEM_SIZE, ITEM_SIZE };
		break;

	}

	return true;
}

bool Usable::PreUpdate()
{
	return true;
}

// Call modules on each loop iteration
bool Usable::Update(float dt)
{
	return true;
}

// Call modules after each loop iteration
bool Usable::PostUpdate()
{
	return true;
}

// Called before quitting
bool Usable::CleanUp()
{
	return true;
}