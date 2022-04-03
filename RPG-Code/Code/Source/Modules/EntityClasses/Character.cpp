#include "Character.h"


Character::Character(CharacterType characterType) : DynamicEntity(DynamicType::CHARACTER)
{
	this->characterType = characterType;
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

// Called before quitting
bool Character::CleanUp()
{
	return true;
}