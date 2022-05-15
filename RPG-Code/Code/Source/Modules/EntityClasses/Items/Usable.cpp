#include "EntityManager.h"

#include "Entity.h"
#include "StaticEntity.h"
#include "Item.h"
#include "Usable.h"


Usable::Usable(UsableType usableType) : Item(ItemType::USABLE)
{
	this->usableType = usableType;
	switch (usableType) {

		//Restore health
	case UsableType::APPLE:
	
		name = "Apple";
	
		break;

	case UsableType::LIFE_POTION: //1

		name = "Life Potion";

		break;

	case UsableType::PIE: //2

		name = "Pie";

		break;

	case UsableType::DELICIOUS_PIE: //3

		name = "Delicious Pie";
	
		break;

	case UsableType::CANDY: //4
	
		name = "Candy";

		break;

	case UsableType::MEAT: //5

		name = "Meat";

		break;

	case UsableType::EGG: //6
	
		name = "Egg";

		break;

	case UsableType::FRIED_EGG: //7

		name = "Fried Egg";
	
		break;

	case UsableType::HAMBURGER: //8

		name = "Hamburger";

		break;

		//Restore enery
	case UsableType::ELIXIR: //9

		name = "Elixir";

		break;

		//Boost
	case UsableType::PILL: //10

		name = "Pill";

		break;

		//Damage
	case UsableType::DYNAMITE: //11
	
		name = "Dynamite";

		break;

	case UsableType::BOMB: //12

		name = "Bomb";
	
		break;

	case UsableType::SUPER_BOMB: //13

		name = "Super Bomb";

		break;

		//Revive
	case UsableType::WILL_TO_LIFE: //14
	
		name = "Will to life";

		break;

		//Map
	case UsableType::CHEST_KEY: //15

		name = "Chest key";
	
		break;

	case UsableType::DOOR_KEY: //16

		name = "Door key";

		break;

		//Missions
	case UsableType::TEDDY_BEAR: //17
	
		name = "Teddy bear";

		break;

	case UsableType::LETTER: //18

		name = "Letter";


		break;

	case UsableType::CLOSE_PARCHMENT: //19

		name = "Close Parchment";


		break;
	case UsableType::OPEN_PARCHMENT: //20

		name = "Open Parchment";

		break;

		//Others
	case UsableType::BAT_WING: //21

		name = "Bat Wing";

		break;

	case UsableType::EYE: //22
	
		name = "Eye";
		
		break;

	case UsableType::BONE: //23
	
		name = "Bone";
	
		break;
	}
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
		description = "Apple are red";

		usableFromInventory = true;

		break;

	case UsableType::LIFE_POTION: //1
		spriteTex = app->tex->Load("Assets/items/items2.png");
		spriteRect = { 13 * ITEM_SIZE, 11 * ITEM_SIZE, ITEM_SIZE, ITEM_SIZE };

		name = "Life Potion";
		effect = "+10 HP";
		description = "Apiretal > Dalsy";

		usableFromInventory = true;

		break;

	case UsableType::PIE: //2
		spriteTex = app->tex->Load("Assets/items/items2.png");
		spriteRect = { 5 * ITEM_SIZE, 0 * ITEM_SIZE, ITEM_SIZE, ITEM_SIZE };

		name = "Pie";
		effect = "+1 speed";
		description = "In spanish: patas";

		usableFromInventory = true;

		break;

	case UsableType::DELICIOUS_PIE: //3
		spriteTex = app->tex->Load("Assets/items/items2.png");
		spriteRect = { 14 * ITEM_SIZE, 1 * ITEM_SIZE, ITEM_SIZE, ITEM_SIZE };

		name = "Delicious Pie";
		effect = "+10 speed";
		description = "pero bueno Xavi 2";

		usableFromInventory = true;

		break;

	case UsableType::CANDY: //4
		spriteTex = app->tex->Load("Assets/items/items2.png");
		spriteRect = { 15 * ITEM_SIZE, 2 * ITEM_SIZE, ITEM_SIZE, ITEM_SIZE };

		name = "Candy";
		effect = "+100 exp points";
		description = "It's rare";

		usableFromInventory = true;

		break;

	case UsableType::MEAT: //5
		spriteTex = app->tex->Load("Assets/items/items2.png");
		spriteRect = { 4 * ITEM_SIZE, 2 * ITEM_SIZE, ITEM_SIZE, ITEM_SIZE };

		name = "Meat";
		effect = "+10 max HP";
		description = "Not vegan-friendly";

		usableFromInventory = true;

		break;

	case UsableType::EGG: //6
		spriteTex = app->tex->Load("Assets/items/items2.png");
		spriteRect = { 11 * ITEM_SIZE, 0 * ITEM_SIZE, ITEM_SIZE, ITEM_SIZE };

		name = "Egg";
		effect = "+1 defense";
		description = "A simple Eggggg";

		usableFromInventory = true;

		break;

	case UsableType::FRIED_EGG: //7
		spriteTex = app->tex->Load("Assets/items/items2.png");
		spriteRect = { 6 * ITEM_SIZE, 2 * ITEM_SIZE, ITEM_SIZE, ITEM_SIZE };

		name = "Fried Egg";
		effect = "+5 defense";
		description = "fried potatos?";

		usableFromInventory = true;

		break;

	case UsableType::HAMBURGER: //8
		spriteTex = app->tex->Load("Assets/items/items2.png");
		spriteRect = { 1 * ITEM_SIZE, 2 * ITEM_SIZE, ITEM_SIZE, ITEM_SIZE };

		name = "Hamburger";
		effect = "+15 HP but -1 speed";
		description = "Fat Hamburger";

		usableFromInventory = true;

		break;

		//Restore enery
	case UsableType::ELIXIR: //9
		spriteTex = app->tex->Load("Assets/items/items2.png");
		spriteRect = { 14 * ITEM_SIZE, 0 * ITEM_SIZE, ITEM_SIZE, ITEM_SIZE };

		name = "Elixir";
		effect = "+20 MP";
		description = "Recover some mana";

		usableFromInventory = true;

		break;

		//Boost
	case UsableType::PILL: //10
		spriteTex = app->tex->Load("Assets/items/items2.png");
		spriteRect = { 15 * ITEM_SIZE, 11 * ITEM_SIZE, ITEM_SIZE, ITEM_SIZE };

		name = "Pill";
		effect = "+20 random stat";
		description = "Drohaaa";

		usableFromInventory = true;

		break;

		//Damage
	case UsableType::DYNAMITE: //11
		spriteTex = app->tex->Load("Assets/items/items2.png");
		spriteRect = { 3 * ITEM_SIZE, 7 * ITEM_SIZE, ITEM_SIZE, ITEM_SIZE };

		name = "Dynamite";
		effect = "+5 Terrorism";
		description = "Kaboom";

		break;

	case UsableType::BOMB: //12
		spriteTex = app->tex->Load("Assets/items/items2.png");
		spriteRect = { 15 * ITEM_SIZE, 13 * ITEM_SIZE, ITEM_SIZE, ITEM_SIZE };

		name = "Bomb";
		effect = "+10 Terrorism";
		description = "Backpack-sized";

		break;

	case UsableType::SUPER_BOMB: //13
		spriteTex = app->tex->Load("Assets/items/items2.png");
		spriteRect = { 0 * ITEM_SIZE, 7 * ITEM_SIZE, ITEM_SIZE, ITEM_SIZE };

		name = "Super Bomb";
		effect = "+20 Terrorism";
		description = "UwU";

		break;

		//Revive
	case UsableType::WILL_TO_LIFE: //14
		spriteTex = app->tex->Load("Assets/items/items2.png");
		spriteRect = { 15 * ITEM_SIZE, 14 * ITEM_SIZE, ITEM_SIZE, ITEM_SIZE };

		name = "Will to life";
		effect = "Idk";
		description = "Idk q hace esto";

		break;
	
		//Map
	case UsableType::CHEST_KEY: //15
		spriteTex = app->tex->Load("Assets/items/items2.png");
		spriteRect = { 4 * ITEM_SIZE, 14 * ITEM_SIZE, ITEM_SIZE, ITEM_SIZE };

		name = "Chest key";
		effect = "Opens a chest";
		description = "No lock resist";

		break;

	case UsableType::DOOR_KEY: //16
		spriteTex = app->tex->Load("Assets/items/items2.png");
		spriteRect = { 5 * ITEM_SIZE, 14 * ITEM_SIZE, ITEM_SIZE, ITEM_SIZE };

		name = "Door key";
		effect = "+5 Amogus";
		description = "What will open?";

		break;

		//Missions
	case UsableType::TEDDY_BEAR: //17
		spriteTex = app->tex->Load("Assets/items/items2.png");
		spriteRect = { 3 * ITEM_SIZE, 13 * ITEM_SIZE, ITEM_SIZE, ITEM_SIZE };

		name = "Teddy bear";
		effect = "+5 max MP";
		description = "Furry";

		usableFromInventory = true;

		break;

	case UsableType::LETTER: //18
		spriteTex = app->tex->Load("Assets/items/items2.png");
		spriteRect = { 5 * ITEM_SIZE, 13 * ITEM_SIZE, ITEM_SIZE, ITEM_SIZE };

		name = "Letter";
		effect = "+5 Comprensión Lectora";
		description = "Essay for Tom";

		break;

	case UsableType::CLOSE_PARCHMENT: //19
		spriteTex = app->tex->Load("Assets/items/items2.png");
		spriteRect = { 7 * ITEM_SIZE, 13 * ITEM_SIZE, ITEM_SIZE, ITEM_SIZE };

		name = "Close Parchment";
		effect = "?????";
		description = "Closes ????";

		break;
	case UsableType::OPEN_PARCHMENT: //20
		spriteTex = app->tex->Load("Assets/items/items2.png");
		spriteRect = { 6 * ITEM_SIZE, 13 * ITEM_SIZE, ITEM_SIZE, ITEM_SIZE };
		
		name = "Open Parchment";
		effect = "?????";
		description = "Opens ????";
		
		break;

		//Others
	case UsableType::BAT_WING: //21
		spriteTex = app->tex->Load("Assets/items/items2.png");
		spriteRect = { 6 * ITEM_SIZE, 15 * ITEM_SIZE, ITEM_SIZE, ITEM_SIZE };
		
		name = "Bat Wing";
		effect = "Monster loot";
		description = "Tasty";
		
		break;

	case UsableType::EYE: //22
		spriteTex = app->tex->Load("Assets/items/items2.png");
		spriteRect = { 3 * ITEM_SIZE, 12 * ITEM_SIZE, ITEM_SIZE, ITEM_SIZE };
		
		name = "Eye";
		effect = "Monster loot";
		description = "For a fresh drink";
		
		break;

	case UsableType::BONE: //23
		spriteTex = app->tex->Load("Assets/items/items2.png");
		spriteRect = { 2 * ITEM_SIZE, 12 * ITEM_SIZE, ITEM_SIZE, ITEM_SIZE };

		name = "Bone";
		effect = "Monster loot";
		description = "Calcium Rich";

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