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
		break;

	case UsableType::LIFE_POTION:
		spriteTex = app->tex->Load("Assets/items/items2.png");
		break;

	case UsableType::ELIXIR:
		spriteTex = app->tex->Load("Assets/items/items2.png");
		break;

	case UsableType::BOMB:
		spriteTex = app->tex->Load("Assets/items/items2.png");
		break;

	case UsableType::SUPER_BOMB:
		spriteTex = app->tex->Load("Assets/items/items2.png");
		break;

	case UsableType::WILL_TO_LIFE:
		spriteTex = app->tex->Load("Assets/items/items2.png");
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