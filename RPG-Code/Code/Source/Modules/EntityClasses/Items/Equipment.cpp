#include "EntityManager.h"

#include "Entity.h"
#include "StaticEntity.h"
#include "Item.h"
#include "Equipment.h"


Equipment::Equipment(EquipmentType equipmentType, const char* name) : Item(ItemType::EQUIPMENT)
{
	this->equipmentType = equipmentType;
	this->name = name;

	spriteTex = nullptr;
}

Equipment::~Equipment()
{}

bool Equipment::Awake(pugi::xml_node& config)
{
	return true;
}

// Called before the first frame
bool Equipment::Start()
{

	if (equipmentType != EquipmentType::WEAPON) {
		weaponType = WeaponType::NONE;
	}

	switch (equipmentType) {
		
	case EquipmentType::WEAPON:
		//_____________________[WEAPONS]______________________________

		//Swords

		if (name == std::string("Shovel")) { //Wood
			weaponType = WeaponType::SWORD;
			spriteTex = app->tex->Load("Assets/items/items2.png");
			spriteRect = { 4 * ITEM_SIZE, 6 * ITEM_SIZE, ITEM_SIZE, ITEM_SIZE };
		}

		if (name == std::string("Practice sword")) { //Wood
			weaponType = WeaponType::SWORD;
			spriteTex = app->tex->Load("Assets/items/items2.png");
			spriteRect = { 15 * ITEM_SIZE, 3 * ITEM_SIZE, ITEM_SIZE, ITEM_SIZE };
		}

		if (name == std::string("Apprentice sword")) { //Iron
			weaponType = WeaponType::SWORD;
			spriteTex = app->tex->Load("Assets/items/items2.png");
			spriteRect = { 0 * ITEM_SIZE, 3 * ITEM_SIZE, ITEM_SIZE, ITEM_SIZE };
		}

		if (name == std::string("Soldier sword")) { //Steel
			weaponType = WeaponType::SWORD;
			spriteTex = app->tex->Load("Assets/items/items2.png");
			spriteRect = { 1 * ITEM_SIZE, 3 * ITEM_SIZE, ITEM_SIZE, ITEM_SIZE };
		}

		if (name == std::string("Heavy sword")) { //Big
			spriteTex = app->tex->Load("Assets/items/items2.png");
			spriteRect = { 2 * ITEM_SIZE, 3 * ITEM_SIZE, ITEM_SIZE, ITEM_SIZE };
		}

		//Crosiers
		if (name == std::string("Stick crosier")) { //Stick
			weaponType = WeaponType::CROSIER;
			spriteTex = app->tex->Load("Assets/items/items2.png");
			spriteRect = { 0 * ITEM_SIZE, 5 * ITEM_SIZE, ITEM_SIZE, ITEM_SIZE };
		}

		if (name == std::string("Apprentice crosier")) { //Wood
			weaponType = WeaponType::CROSIER;
			spriteTex = app->tex->Load("Assets/items/items2.png");
			spriteRect = { 8 * ITEM_SIZE, 5 * ITEM_SIZE, ITEM_SIZE, ITEM_SIZE };
		}

		if (name == std::string("Magician crosier")) { 
			weaponType = WeaponType::CROSIER;
			spriteTex = app->tex->Load("Assets/items/items2.png");
			spriteRect = { 1 * ITEM_SIZE, 5 * ITEM_SIZE, ITEM_SIZE, ITEM_SIZE };
		}

		if (name == std::string("Refined crosier")) { 
			weaponType = WeaponType::CROSIER;
			spriteTex = app->tex->Load("Assets/items/items2.png");
			spriteRect = { 2 * ITEM_SIZE, 6 * ITEM_SIZE, ITEM_SIZE, ITEM_SIZE };
		}

		//Bow
		if (name == std::string("Simple bow")) { 
			weaponType = WeaponType::BOW;
			spriteTex = app->tex->Load("Assets/items/items2.png");
			spriteRect = { 0 * ITEM_SIZE, 5 * ITEM_SIZE, ITEM_SIZE, ITEM_SIZE };
		}

		if (name == std::string("Apprentice bow")) { 
			weaponType = WeaponType::BOW;
			spriteTex = app->tex->Load("Assets/items/items2.png");
			spriteRect = { 8 * ITEM_SIZE, 5 * ITEM_SIZE, ITEM_SIZE, ITEM_SIZE };
		}

		if (name == std::string("Elf bow")) {
			weaponType = WeaponType::BOW;
			spriteTex = app->tex->Load("Assets/items/items2.png");
			spriteRect = { 1 * ITEM_SIZE, 5 * ITEM_SIZE, ITEM_SIZE, ITEM_SIZE };
		}

		if (name == std::string("Heavy bow")) {
			weaponType = WeaponType::BOW;
			spriteTex = app->tex->Load("Assets/items/items2.png");
			spriteRect = { 2 * ITEM_SIZE, 6 * ITEM_SIZE, ITEM_SIZE, ITEM_SIZE };
		}

		//Lance
		if (name == std::string("Stick lance")) { 
			weaponType = WeaponType::LANCE;
			spriteTex = app->tex->Load("Assets/items/items2.png");
			spriteRect = { 0 * ITEM_SIZE, 5 * ITEM_SIZE, ITEM_SIZE, ITEM_SIZE };
		}

		if (name == std::string("Apprentice lance")) { 
			weaponType = WeaponType::LANCE;
			spriteTex = app->tex->Load("Assets/items/items2.png");
			spriteRect = { 8 * ITEM_SIZE, 5 * ITEM_SIZE, ITEM_SIZE, ITEM_SIZE };
		}

		if (name == std::string("Armamentalist lance")) {
			weaponType = WeaponType::LANCE;
			spriteTex = app->tex->Load("Assets/items/items2.png");
			spriteRect = { 1 * ITEM_SIZE, 5 * ITEM_SIZE, ITEM_SIZE, ITEM_SIZE };
		}

		if (name == std::string("Ultra lance")) {
			weaponType = WeaponType::LANCE;
			spriteTex = app->tex->Load("Assets/items/items2.png");
			spriteRect = { 2 * ITEM_SIZE, 6 * ITEM_SIZE, ITEM_SIZE, ITEM_SIZE };
		}
		
		break;

	case EquipmentType::SHIELD:
		//_____________________[SHIELDS]______________________________

		if (name == std::string("Wood shield")) { //
			spriteTex = app->tex->Load("Assets/items/items1.png");
			spriteRect = { 7 * ITEM_SIZE, 11 * ITEM_SIZE, ITEM_SIZE, ITEM_SIZE };
		}

		if (name == std::string("Apprentice shield")) { //
			spriteTex = app->tex->Load("Assets/items/items1.png");
			spriteRect = { 6 * ITEM_SIZE, 11 * ITEM_SIZE, ITEM_SIZE, ITEM_SIZE };
		}

		if (name == std::string("Robust shield")) { //
			spriteTex = app->tex->Load("Assets/items/items1.png");
			spriteRect = { 5 * ITEM_SIZE, 11 * ITEM_SIZE, ITEM_SIZE, ITEM_SIZE };
		}

		if (name == std::string("Iron shield")) { //
			spriteTex = app->tex->Load("Assets/items/items1.png");
			spriteRect = { 8 * ITEM_SIZE, 11 * ITEM_SIZE, ITEM_SIZE, ITEM_SIZE };
		}


		break;

	case EquipmentType::HELMET:
		//_____________________[HELMETS]______________________________ ////Faltan decidir los nombres y sprites

		if (name == std::string("Basic helmet")) { //
			spriteTex = app->tex->Load("Assets/items/items1.png");
			spriteRect = { 2 * ITEM_SIZE, 9 * ITEM_SIZE, ITEM_SIZE, ITEM_SIZE };
		}

		if (name == std::string("Apprentice helmet")) { //
			spriteTex = app->tex->Load("Assets/items/items1.png");
			spriteRect = { 0 * ITEM_SIZE, 9 * ITEM_SIZE, ITEM_SIZE, ITEM_SIZE };
		}

		if (name == std::string("Soldier helmet")) { //
			spriteTex = app->tex->Load("Assets/items/items1.png");
			spriteRect = { 1 * ITEM_SIZE, 9 * ITEM_SIZE, ITEM_SIZE, ITEM_SIZE };
		}

		if (name == std::string("Defensive helmet")) { //
			spriteTex = app->tex->Load("Assets/items/items1.png");
			spriteRect = { 3 * ITEM_SIZE, 9 * ITEM_SIZE, ITEM_SIZE, ITEM_SIZE };
		}

		break;

	case EquipmentType::ARMOR:
		//_____________________[ARMORS]______________________________ ////Faltan decidir los nombres y sprites

		if (name == std::string("Battle uniform")) { //
			spriteTex = app->tex->Load("Assets/items/items2.png");
			spriteRect = { 0 * ITEM_SIZE, 8 * ITEM_SIZE, ITEM_SIZE, ITEM_SIZE };
		}

		if (name == std::string("Training vest")) { //
			spriteTex = app->tex->Load("Assets/items/items2.png");
			spriteRect = { 1 * ITEM_SIZE, 8 * ITEM_SIZE, ITEM_SIZE, ITEM_SIZE };
		}

		if (name == std::string("Bronze armor")) { //
			spriteTex = app->tex->Load("Assets/items/items2.png");
			spriteRect = { 2 * ITEM_SIZE, 8 * ITEM_SIZE, ITEM_SIZE, ITEM_SIZE };
		}

		if (name == std::string("Steel armor")) { //
			spriteTex = app->tex->Load("Assets/items/items2.png");
			spriteRect = { 3 * ITEM_SIZE, 8 * ITEM_SIZE, ITEM_SIZE, ITEM_SIZE };
		}

		break;
	case EquipmentType::GLOVES:
		//_____________________[GLOVES]______________________________ ////Faltan decidir los nombres y sprites

		if (name == std::string("Leather gloves")) { //
			spriteTex = app->tex->Load("Assets/items/items2.png");
			spriteRect = { 6 * ITEM_SIZE, 9 * ITEM_SIZE, ITEM_SIZE, ITEM_SIZE };
		}

		if (name == std::string("Iron gloves")) { //
			spriteTex = app->tex->Load("Assets/items/items2.png");
			spriteRect = { 7 * ITEM_SIZE, 9 * ITEM_SIZE, ITEM_SIZE, ITEM_SIZE };
		}

		if (name == std::string("Midas gloves")) { //
			spriteTex = app->tex->Load("Assets/items/items2.png");
			spriteRect = { 8 * ITEM_SIZE, 9 * ITEM_SIZE, ITEM_SIZE, ITEM_SIZE };
		}

		if (name == std::string("Relic gloves")) { //
			spriteTex = app->tex->Load("Assets/items/items2.png");
			spriteRect = { 9 * ITEM_SIZE, 9 * ITEM_SIZE, ITEM_SIZE, ITEM_SIZE };
		}

		break;
		
	case EquipmentType::BOOTS:
		//_____________________[BOOTS]______________________________ ////Faltan decidir los nombres y sprites

		if (name == std::string("Leather boots")) { //
			spriteTex = app->tex->Load("Assets/items/items2.png");
			spriteRect = { 0 * ITEM_SIZE, 10 * ITEM_SIZE, ITEM_SIZE, ITEM_SIZE };
		}

		if (name == std::string("Training boots")) { //
			spriteTex = app->tex->Load("Assets/items/items2.png");
			spriteRect = { 1 * ITEM_SIZE, 10 * ITEM_SIZE, ITEM_SIZE, ITEM_SIZE };
		}

		if (name == std::string("Iron boots")) { //
			spriteTex = app->tex->Load("Assets/items/items2.png");
			spriteRect = { 2 * ITEM_SIZE, 10 * ITEM_SIZE, ITEM_SIZE, ITEM_SIZE };
		}

		if (name == std::string("Golden boots")) { //
			spriteTex = app->tex->Load("Assets/items/items2.png");
			spriteRect = { 3 * ITEM_SIZE, 10 * ITEM_SIZE, ITEM_SIZE, ITEM_SIZE };
		}

		break;

	case EquipmentType::TALISMAN:
		//_____________________[TALISMANS]______________________________ ////Faltan decidir los nombres y sprites

		if (name == std::string("Belt")) { //
			spriteTex = app->tex->Load("Assets/items/items2.png");
			spriteRect = { 9 * ITEM_SIZE, 10 * ITEM_SIZE, ITEM_SIZE, ITEM_SIZE };
		}

		if (name == std::string("Magic ring")) { //
			spriteTex = app->tex->Load("Assets/items/items2.png");
			spriteRect = { 10 * ITEM_SIZE, 10 * ITEM_SIZE, ITEM_SIZE, ITEM_SIZE };
		}

		if (name == std::string("Golden ring")) { //
			spriteTex = app->tex->Load("Assets/items/items2.png");
			spriteRect = { 11 * ITEM_SIZE, 10 * ITEM_SIZE, ITEM_SIZE, ITEM_SIZE };
		}

		if (name == std::string("Mystic ring")) { //
			spriteTex = app->tex->Load("Assets/items/items2.png");
			spriteRect = { 12 * ITEM_SIZE, 10 * ITEM_SIZE, ITEM_SIZE, ITEM_SIZE };
		}

		if (name == std::string("Clover")) { //
			spriteTex = app->tex->Load("Assets/items/items2.png");
			spriteRect = { 12 * ITEM_SIZE, 10 * ITEM_SIZE, ITEM_SIZE, ITEM_SIZE };
		}

		break;
	}

	return true;
}

bool Equipment::PreUpdate()
{
	return true;
}

// Call modules on each loop iteration
bool Equipment::Update(float dt)
{
	return true;
}

// Call modules after each loop iteration
bool Equipment::PostUpdate()
{
	return true;
}

// Called before quitting
bool Equipment::CleanUp()
{
	return true;
}