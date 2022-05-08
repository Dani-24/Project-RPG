#include "EntityManager.h"

#include "Entity.h"
#include "StaticEntity.h"
#include "Item.h"
#include "Equipment.h"

#define ITEM_SIZE 48


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

	switch (equipmentType) {
		
	case EquipmentType::WEAPON:
		//_____________________[WEAPONS]______________________________

		//Swords
		if (name == std::string("Practice sword")) { //Wood
			spriteTex = app->tex->Load("Assets/items/items2.png");
			spriteRect = { 15 * ITEM_SIZE, 3 * ITEM_SIZE, ITEM_SIZE, ITEM_SIZE };
		}

		if (name == std::string("Apprentice sword")) { //Iron
			spriteTex = app->tex->Load("Assets/items/items2.png");
			spriteRect = { 0 * ITEM_SIZE, 3 * ITEM_SIZE, ITEM_SIZE, ITEM_SIZE };
		}

		if (name == std::string("Soldier sword")) { //Steel
			spriteTex = app->tex->Load("Assets/items/items2.png");
			spriteRect = { 1 * ITEM_SIZE, 3 * ITEM_SIZE, ITEM_SIZE, ITEM_SIZE };
		}

		if (name == std::string("Heavy sword")) { //Big
			spriteTex = app->tex->Load("Assets/items/items2.png");
			spriteRect = { 2 * ITEM_SIZE, 3 * ITEM_SIZE, ITEM_SIZE, ITEM_SIZE };
		}

		//Crosiers
		if (name == std::string("Stick crosier")) { //Stick
			spriteTex = app->tex->Load("Assets/items/items2.png");
			spriteRect = { 0 * ITEM_SIZE, 5 * ITEM_SIZE, ITEM_SIZE, ITEM_SIZE };
		}

		if (name == std::string("Apprentice crosier")) { //Wood
			spriteTex = app->tex->Load("Assets/items/items2.png");
			spriteRect = { 8 * ITEM_SIZE, 5 * ITEM_SIZE, ITEM_SIZE, ITEM_SIZE };
		}

		if (name == std::string("Refined crosier")) { 
			spriteTex = app->tex->Load("Assets/items/items2.png");
			spriteRect = { 1 * ITEM_SIZE, 5 * ITEM_SIZE, ITEM_SIZE, ITEM_SIZE };
		}

		if (name == std::string("Magician crosier")) { 
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

		if (name == std::string("Wood helmet")) { //

		}

		if (name == std::string("Apprentice helmet")) { //

		}

		if (name == std::string("Robust helmet")) { //

		}

		if (name == std::string("Iron helmet")) { //

		}

		break;

	case EquipmentType::ARMOR:
		//_____________________[ARMORS]______________________________ ////Faltan decidir los nombres y sprites

		if (name == std::string("Wood armor")) { //

		}

		if (name == std::string("Apprentice armor")) { //

		}

		if (name == std::string("Robust armor")) { //

		}

		if (name == std::string("Iron armor")) { //

		}

		break;
	case EquipmentType::GLOVES:
		//_____________________[GLOVES]______________________________ ////Faltan decidir los nombres y sprites

		if (name == std::string("Wood gloves")) { //

		}

		if (name == std::string("Apprentice gloves")) { //

		}

		if (name == std::string("Robust gloves")) { //

		}

		if (name == std::string("Iron gloves")) { //

		}

		break;
		
	case EquipmentType::BOOTS:
		//_____________________[BOOTS]______________________________ ////Faltan decidir los nombres y sprites

		if (name == std::string("Wood boots")) { //

		}

		if (name == std::string("Apprentice boots")) { //

		}

		if (name == std::string("Robust boots")) { //

		}

		if (name == std::string("Iron boots")) { //

		}

		break;

	case EquipmentType::TALISMAN:
		//_____________________[TALISMANS]______________________________ ////Faltan decidir los nombres y sprites

		if (name == std::string("Wood talisman")) { //

		}

		if (name == std::string("Apprentice talisman")) { //

		}

		if (name == std::string("Robust talisman")) { //

		}

		if (name == std::string("Iron talisman")) { //

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