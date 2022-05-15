#include "Character.h"

#include "Scene.h"
#include "StaticEntity.h"
#include "Item.h"
#include "Equipment.h"


Character::Character(CharacterType characterType) : DynamicEntity(DynamicType::CHARACTER)
{
	this->characterType = characterType;
	skillsList[0] = false;
	skillsList[1] = false;
	skillsList[2] = false;
}

Character::~Character()
{}

bool Character::Awake(pugi::xml_node& config)
{
	return true;
}

// Called before the first frame
bool Character::Start()
{
	return true;
}

bool Character::PreUpdate()
{
	return true;
}

// Call modules on each loop iteration
bool Character::Update(float dt)
{
	return true;
}

// Call modules after each loop iteration
bool Character::PostUpdate()
{
	return true;
}

void Character::Equip(Equipment *equip)
{
	switch (equip->equipmentType) {
	case EquipmentType::WEAPON:
		if (equipment[0] == nullptr) {
			equipment[0] = equip;
		}
		else {
			app->scene->itemList.add(equipment[0]);
			equipment[0] = equip;
		}
		break;
	case EquipmentType::SHIELD:
		if (equipment[1] == nullptr) {
			equipment[1] = equip;
		}
		else {
			app->scene->itemList.add(equipment[1]);
			equipment[1] = equip;
		}
		break;
	case EquipmentType::HELMET:
		if (equipment[2] == nullptr) {
			equipment[2] = equip;
		}
		else {
			app->scene->itemList.add(equipment[2]);
			equipment[2] = equip;
		}
		break;
	case EquipmentType::ARMOR:
		if (equipment[3] == nullptr) {
			equipment[3] = equip;
		}
		else {
			app->scene->itemList.add(equipment[3]);
			equipment[3] = equip;
		}
		break;
	case EquipmentType::GLOVES:
		if (equipment[4] == nullptr) {
			equipment[4] = equip;
		}
		else {
			app->scene->itemList.add(equipment[4]);
			equipment[4] = equip;
		}
		break;
	case EquipmentType::BOOTS:
		if (equipment[5] == nullptr) {
			equipment[5] = equip;
		}
		else {
			app->scene->itemList.add(equipment[5]);
			equipment[5] = equip;
		}
		break;
	case EquipmentType::TALISMAN:
		if (equipment[6] == nullptr) {
			equipment[6] = equip;
		}
		else {
			app->scene->itemList.add(equipment[6]);
			equipment[6] = equip;
		}
		break;
	}
}

void Character::Unequip(EquipmentType slot)
{
	switch (slot) {
	case EquipmentType::WEAPON:
		if (equipment[0] != nullptr) {
			app->scene->itemList.add(equipment[0]);
			equipment[0] = nullptr;
		}
		break;
	case EquipmentType::SHIELD:
		if (equipment[1] != nullptr) {
			app->scene->itemList.add(equipment[1]);
			equipment[1] = nullptr;
		}
		break;
	case EquipmentType::HELMET:
		if (equipment[2] != nullptr) {
			app->scene->itemList.add(equipment[2]);
			equipment[2] = nullptr;
		}
		break;
	case EquipmentType::ARMOR:
		if (equipment[3] != nullptr) {
			app->scene->itemList.add(equipment[3]);
			equipment[3] = nullptr;
		}
		break;
	case EquipmentType::GLOVES:
		if (equipment[4] != nullptr) {
			app->scene->itemList.add(equipment[4]);
			equipment[4] = nullptr;
		}
		break;
	case EquipmentType::BOOTS:
		if (equipment[5] != nullptr) {
			app->scene->itemList.add(equipment[5]);
			equipment[5] = nullptr;
		}
		break;
	case EquipmentType::TALISMAN:
		if (equipment[6] != nullptr) {
			app->scene->itemList.add(equipment[6]);
			equipment[6] = nullptr;
		}
		break;
	}
}


// Called before quitting
bool Character::CleanUp()
{
	return true;
}