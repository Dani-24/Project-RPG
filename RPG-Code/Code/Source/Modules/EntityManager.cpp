#include "EntityManager.h"
#include "Entity.h"

#include "DynamicEntity.h"
#include "StaticEntity.h"

#include "Character.h"
#include "Player.h"

#include "Cock.h"
#include "NPCEntity.h"


EntityManager::EntityManager(App* application, bool start_enabled) : Module(application, start_enabled)
{
	name.Create("EntityManager");
}

EntityManager::~EntityManager()
{}

bool EntityManager::Awake(pugi::xml_node& config)
{

	return true;
}

// Called before the first frame
bool EntityManager::Start()
{
	bool ret = true;
	ListItem<Entity*>* entityInList;
	entityInList = entityList.start;

	while (entityInList != NULL && ret == true)
	{
		ret = entityInList->data->Start();
		entityInList = entityInList->next;
	}
	return ret;
}

bool EntityManager::PreUpdate()
{
	bool ret = true;
	ListItem<Entity*>* entityInList;

	for (entityInList = entityList.start; entityInList != NULL && ret == true; entityInList = entityInList->next)
	{
		if (entityInList->data->hasStarted == false) {
			continue;
		}
		ret = entityInList->data->PreUpdate();
	}
	return ret;
}

// Call modules on each loop iteration
bool EntityManager::Update(float dt)
{
	//___________________________

	pugi::xml_document configFile;
	pugi::xml_node config;
	pugi::xml_node configApp;

	config = app->LoadConfig(configFile);
	//configApp = config.child("app");

	//____________________________
	bool ret = true;
	ListItem<Entity*>* entityInList;
	entityInList = entityList.start;

	for (entityInList = entityList.start; entityInList != NULL && ret == true; entityInList = entityInList->next)
	{
		if (entityInList->data->hasAwaken == false) {
			//AAAAAAAAAAAAAAAAAA//
			ret = entityInList->data->Awake(config.child(entityInList->data->configName.GetString()));
			entityInList->data->hasAwaken = true;
			continue;
		}

		if (entityInList->data->hasStarted == false) {
			ret = entityInList->data->Start();
			entityInList->data->hasStarted = true;
			continue;
		}
		ret = entityInList->data->Update(dt);
	}

	//bool ret = true;
	//ListItem<Entity*>* item;
	//Entity* pEntity = NULL;

	//for (item = entityList.start; item != NULL && ret == true; item = item->next)
	//{
	//		pEntity = item->data;

	//		if (pEntity->active == false) continue;
	//		ret = item->data->Update(dt);
	//}

	return ret;
}

// Call modules after each loop iteration
bool EntityManager::PostUpdate()
{
	bool ret = true;
	ListItem<Entity*>* entityInList;
	entityInList = entityList.start;

	for (entityInList = entityList.start; entityInList != NULL && ret == true; entityInList = entityInList->next)
	{
		if (entityInList->data->hasStarted == false) {
			continue;
		}
		ret = entityInList->data->PostUpdate();
	}
	return ret;
}

//bool EntityManager::Draw()
//{
//	bool ret = true;
//	ListItem<Entity*>* entityInList;
//	entityInList = entityList.end;
//
//	while (entityInList != NULL && ret == true)
//	{
//		ret = entityInList->data->Draw();
//		entityInList = entityInList->prev;
//	}
//
//	return ret;
//}

// Called before quitting
bool EntityManager::CleanUp()
{
	bool ret = true;
	ListItem<Entity*>* entityInList;
	entityInList = entityList.end;

	while (entityInList != NULL && ret == true)
	{
		ret = entityInList->data->CleanUp();
		entityInList = entityInList->prev;
	}

	return ret;
}

bool EntityManager::Save(pugi::xml_node& file) const
{
	return false;
}

bool EntityManager::Load(pugi::xml_node& file)
{
	return false;
}


Entity* EntityManager::CreateEntity(DynamicType type)
{
	Entity* ret = nullptr;

	switch (type)
	{
	case DynamicType::CHARACTER:

		break;
	case DynamicType::ENEMY:

		break;
	case DynamicType::NPC:

		break;
	case DynamicType::INTERACTABLE:

		break;
	default:

		LOG("ERROR: Entity Type not set when creating");
		break;
	}

	if (ret != nullptr) {
		entityList.add(ret);
	}

	return ret;
}

Entity* EntityManager::CreateEntity(CharacterType type)
{
	Entity* ret = nullptr;

	switch (type)
	{
	case CharacterType::PLAYER:

		ret = new Player();

		break;
	case CharacterType::PARTY:

		break;
	default:

		LOG("ERROR: Entity Type not set when creating");
		break;
	}

	if (ret != nullptr) {
		entityList.add(ret);
	}

	return ret;
}
Entity* EntityManager::CreateEntity(NPCType type)
{
	Entity* ret = nullptr;

	switch (type)
	{
	case NPCType::COCK:

		ret = new Cock();

		break;
	case NPCType::BARKEEPER:

		break;
	case NPCType::MERCHANT:

		break;
	default:

		LOG("ERROR: Entity Type not set when creating");
		break;
	}

	if (ret != nullptr) {
		entityList.add(ret);
	}

	return ret;
}

Entity* EntityManager::FindEntity(EntityType EntityType)
{
	Entity* ret = nullptr;

	ListItem<Entity*>* entityInList;
	entityInList = entityList.start;

	for (entityInList = entityList.start; entityInList != NULL; entityInList = entityInList->next)
	{
		if (entityInList->data->entityType == EntityType)
			ret = entityInList->data;
	}

	/*for (int i = 0; i < entities.count(); i++) {
		if (entities.At(i)->data->type == EntityType) {


			ret = entities.At(i)->data;
		}
	}*/

	return ret;
}

void EntityManager::DestroyEntity(Entity* entity)
{
	ListItem<Entity*>* entityInList;
	entityInList = entityList.start;
	for (entityInList = entityList.start; entityInList != nullptr; entityInList = entityInList->next)
	{
		if (entityInList->data == entity) {
			entityList.del(entityInList);
		}
	}
}