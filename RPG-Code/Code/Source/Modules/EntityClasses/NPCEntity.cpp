#include "EntityManager.h"

#include "Entity.h"
#include "DynamicEntity.h"
#include "NPCEntity.h"

NPCEntity::NPCEntity(NPCType NPCType) : DynamicEntity(DynamicType::NPC)
{}

NPCEntity::~NPCEntity()
{}

bool NPCEntity::Awake(pugi::xml_node& config)
{

	return true;
}

// Called before the first frame
bool NPCEntity::Start()
{
	return true;
}

bool NPCEntity::PreUpdate()
{
	return true;
}

// Call modules on each loop iteration
bool NPCEntity::Update(float dt)
{
	return true;
}

// Call modules after each loop iteration
bool NPCEntity::PostUpdate()
{
	return true;
}

// Called before quitting
bool NPCEntity::CleanUp()
{
	return true;
}