#include "EntityManager.h"

#include "Entity.h"
#include "StaticEntity.h"
#include "Item.h"


Item::Item(ItemType itemType) : StaticEntity(StaticType::ITEM)
{
	this->itemType = itemType;
}

Item::~Item()
{}

bool Item::Awake(pugi::xml_node& config)
{
	return true;
}

// Called before the first frame
bool Item::Start()
{
	return true;
}

bool Item::PreUpdate()
{
	return true;
}

// Call modules on each loop iteration
bool Item::Update(float dt)
{
	return true;
}

// Call modules after each loop iteration
bool Item::PostUpdate()
{
	return true;
}

// Called before quitting
bool Item::CleanUp()
{
	return true;
}