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

		//Restore health
	case UsableType::APPLE:
		spriteTex = app->tex->Load("Assets/items/items2.png");
		spriteRect = { 0 * ITEM_SIZE, 0 * ITEM_SIZE, ITEM_SIZE, ITEM_SIZE };

		name = "Apple";
		effect = "+5 HP";
		description = "Apple are red, bc they are SUS";

		break;

	case UsableType::LIFE_POTION:
		spriteTex = app->tex->Load("Assets/items/items2.png");
		spriteRect = { 13 * ITEM_SIZE, 11 * ITEM_SIZE, ITEM_SIZE, ITEM_SIZE };

		name = "Life Potion";
		effect = "+10 HP";
		description = "Apiretal > Dalsy";

		break;

	case UsableType::PIE:
		spriteTex = app->tex->Load("Assets/items/items2.png");
		spriteRect = { 5 * ITEM_SIZE, 0 * ITEM_SIZE, ITEM_SIZE, ITEM_SIZE };

		name = "Pie";
		effect = "+5 MP";
		description = "Pie, in spanish: patas";

		break;

	case UsableType::DELICIOUS_PIE:
		spriteTex = app->tex->Load("Assets/items/items2.png");
		spriteRect = { 14 * ITEM_SIZE, 1 * ITEM_SIZE, ITEM_SIZE, ITEM_SIZE };

		name = "Delicious Pie";
		effect = "+10 MP";
		description = "Pie delicioso??? pero bueno Xavi 2";

		break;

	case UsableType::CANDY:
		spriteTex = app->tex->Load("Assets/items/items2.png");
		spriteRect = { 15 * ITEM_SIZE, 2 * ITEM_SIZE, ITEM_SIZE, ITEM_SIZE };

		name = "Candy";
		effect = "+1 HP";
		description = "Proviene de una furgoneta";

		break;

	case UsableType::MEAT:
		spriteTex = app->tex->Load("Assets/items/items2.png");
		spriteRect = { 4 * ITEM_SIZE, 2 * ITEM_SIZE, ITEM_SIZE, ITEM_SIZE };

		name = "Meat";
		effect = "+25 HP";
		description = "Not vegan-friendly product";

		break;

	case UsableType::EGG:
		spriteTex = app->tex->Load("Assets/items/items2.png");
		spriteRect = { 11 * ITEM_SIZE, 0 * ITEM_SIZE, ITEM_SIZE, ITEM_SIZE };

		name = "Egg";
		effect = "+1 HP";
		description = "A simple Eggggg";

		break;

	case UsableType::FRIED_EGG:
		spriteTex = app->tex->Load("Assets/items/items2.png");
		spriteRect = { 6 * ITEM_SIZE, 2 * ITEM_SIZE, ITEM_SIZE, ITEM_SIZE };

		name = "Fried Egg";
		effect = "+5 HP";
		description = "Where are the fried potatos?";

		break;

	case UsableType::HAMBURGER:
		spriteTex = app->tex->Load("Assets/items/items2.png");
		spriteRect = { 1 * ITEM_SIZE, 2 * ITEM_SIZE, ITEM_SIZE, ITEM_SIZE };

		name = "Hamburger";
		effect = "+15 HP";
		description = "Hambur, burger, burbur, gerham, burhamger";

		break;

		//Restore enery
	case UsableType::ELIXIR:
		spriteTex = app->tex->Load("Assets/items/items2.png");
		spriteRect = { 14 * ITEM_SIZE, 0 * ITEM_SIZE, ITEM_SIZE, ITEM_SIZE };

		name = "Elixir";
		effect = "+20 MP";
		description = "Recover some mana with elixir kh6!";

		break;

		//Boost
	case UsableType::PILL:
		spriteTex = app->tex->Load("Assets/items/items2.png");
		spriteRect = { 15 * ITEM_SIZE, 11 * ITEM_SIZE, ITEM_SIZE, ITEM_SIZE };

		name = "Pill";
		effect = "+50 Drugs";
		description = "Drohaaa";

		break;

		//Damage
	case UsableType::DYNAMITE:
		spriteTex = app->tex->Load("Assets/items/items2.png");
		spriteRect = { 3 * ITEM_SIZE, 7 * ITEM_SIZE, ITEM_SIZE, ITEM_SIZE };

		name = "Dynamite";
		effect = "+5 Terrorism";
		description = "Kaboom";

		break;

	case UsableType::BOMB:
		spriteTex = app->tex->Load("Assets/items/items2.png");
		spriteRect = { 15 * ITEM_SIZE, 13 * ITEM_SIZE, ITEM_SIZE, ITEM_SIZE };

		name = "Bomb";
		effect = "+10 Terrorism";
		description = "Now backpack-sized";

		break;

	case UsableType::SUPER_BOMB:
		spriteTex = app->tex->Load("Assets/items/items2.png");
		spriteRect = { 0 * ITEM_SIZE, 7 * ITEM_SIZE, ITEM_SIZE, ITEM_SIZE };

		name = "Super Bomb";
		effect = "+20 Terrorism";
		description = "No one will survive";

		break;

		//Revive
	case UsableType::WILL_TO_LIFE:
		spriteTex = app->tex->Load("Assets/items/items2.png");
		spriteRect = { 15 * ITEM_SIZE, 14 * ITEM_SIZE, ITEM_SIZE, ITEM_SIZE };

		name = "Will to life";
		effect = "Idk";
		description = "Idk q hace esto";

		break;
	
		//Map
	case UsableType::CHEST_KEY:
		spriteTex = app->tex->Load("Assets/items/items2.png");
		spriteRect = { 4 * ITEM_SIZE, 14 * ITEM_SIZE, ITEM_SIZE, ITEM_SIZE };

		name = "Chest key";
		effect = "Opens a chest";
		description = "All locks can be opened with the correct key";

		break;

	case UsableType::DOOR_KEY:
		spriteTex = app->tex->Load("Assets/items/items2.png");
		spriteRect = { 5 * ITEM_SIZE, 14 * ITEM_SIZE, ITEM_SIZE, ITEM_SIZE };

		name = "Door key";
		effect = "+5 Amogus";
		description = "That are the keys you thought you lost";

		break;

		//Missions
	case UsableType::TEDDY_BEAR:
		spriteTex = app->tex->Load("Assets/items/items2.png");
		spriteRect = { 3 * ITEM_SIZE, 13 * ITEM_SIZE, ITEM_SIZE, ITEM_SIZE };

		name = "Teddy bear";
		effect = "+5 Hapiness";
		description = "Yes";

		break;

	case UsableType::LETTER:
		spriteTex = app->tex->Load("Assets/items/items2.png");
		spriteRect = { 5 * ITEM_SIZE, 13 * ITEM_SIZE, ITEM_SIZE, ITEM_SIZE };

		name = "Letter";
		effect = "+5 Comprensión Lectora";
		description = "Incluye una carta para Tom";

		break;

	case UsableType::CLOSE_PARCHMENT:
		spriteTex = app->tex->Load("Assets/items/items2.png");
		spriteRect = { 7 * ITEM_SIZE, 13 * ITEM_SIZE, ITEM_SIZE, ITEM_SIZE };
		break;
	case UsableType::OPEN_PARCHMENT:
		spriteTex = app->tex->Load("Assets/items/items2.png");
		spriteRect = { 6 * ITEM_SIZE, 13 * ITEM_SIZE, ITEM_SIZE, ITEM_SIZE };
		break;

		//Others
	case UsableType::BAT_WING:
		spriteTex = app->tex->Load("Assets/items/items2.png");
		spriteRect = { 6 * ITEM_SIZE, 15 * ITEM_SIZE, ITEM_SIZE, ITEM_SIZE };
		break;

	case UsableType::EYE:
		spriteTex = app->tex->Load("Assets/items/items2.png");
		spriteRect = { 3 * ITEM_SIZE, 12 * ITEM_SIZE, ITEM_SIZE, ITEM_SIZE };
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