#include "EntityManager.h"

#include "Entity.h"
#include "DynamicEntity.h"
#include "NPCEntity.h"

NPC::NPC(NPCType NPCType) : DynamicEntity(DynamicType::NPC)
{


}

NPC::~NPC()
{}

bool NPC::Awake(pugi::xml_node& config)
{

	return true;
}

// Called before the first frame
bool NPC::Start()
{
	return true;
}

bool NPC::PreUpdate()
{
	return true;
}

// Call modules on each loop iteration
bool NPC::Update(float dt)
{
	return true;
}

// Call modules after each loop iteration
bool NPC::PostUpdate()
{
	return true;
}

// Called before quitting
bool NPC::CleanUp()
{
	return true;
}