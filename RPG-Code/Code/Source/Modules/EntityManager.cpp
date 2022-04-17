#include "EntityManager.h"
#include "Entity.h"

#include "DynamicEntity.h"
#include "StaticEntity.h"

#include "Character.h"
#include "Player.h"

#include "NPC.h"
#include "NormalEnemy.h"


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
			break;
		}

		if (entityInList->data->hasStarted == false) {
			ret = entityInList->data->Start();
			entityInList->data->hasStarted = true;
			break;
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

Entity* EntityManager::CreateEntity( int x, int y)
{
	Entity* ret = new Entity();

	if (ret != nullptr) {
		entityList.add(ret);
		ret->position.x = x;
		ret->position.y = y;
	}

	return ret;
}

Entity* EntityManager::CreateEntity(EntityType type, int x, int y)
{
	Entity* ret = nullptr;

	switch (type)
	{
	case EntityType::DYNAMIC:

		break;
	case EntityType::STATIC:

		break;

	default:

		LOG("ERROR: Entity Type not set when creating");
		break;
	}

	if (ret != nullptr) {
		entityList.add(ret);
		ret->position.x = x;
		ret->position.y = y;
	}

	return ret;
}

Entity* EntityManager::CreateEntity(DynamicType type, int x, int y)
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
		ret->position.x = x;
		ret->position.y = y;
	}

	return ret;
}

Entity* EntityManager::CreateEntity(CharacterType type, int x, int y)
{
	Entity* ret = nullptr;

	switch (type)
	{
	case CharacterType::PLAYER:

		ret = new Player(x,y);

		break;

	case CharacterType::PARTY:

		break;

	default:

		LOG("ERROR: Entity Type not set when creating");
		break;
	}

	if (ret != nullptr) {
		entityList.add(ret);
		//ret->position.x = x;
		//ret->position.y = y;
	}

	return ret;
}
Entity* EntityManager::CreateEntity(NPCType type, int x, int y)
{
	Entity* ret = nullptr;

	switch (type)
	{
	case NPCType::COCK:

		ret = new NPC(NPCType::COCK, x, y);
		break;

	case NPCType::BARKEEPER:

		ret = new NPC(NPCType::BARKEEPER, x, y);
		break;

	case NPCType::MERCHANT:

		ret = new NPC(NPCType::MERCHANT, x, y);
		break;
	
	case NPCType::TRAINER:

		ret = new NPC(NPCType::TRAINER, x, y);
		break;
	case NPCType::EMILIO:

		ret = new NPC(NPCType::EMILIO, x, y);
		break;

	default:

		LOG("ERROR: Entity Type not set when creating");
		break;
	}

	if (ret != nullptr) {
		entityList.add(ret);
		//ret->position.x = x;
		//ret->position.y = y;
	}

	return ret;
}

Entity* EntityManager::CreateEntity(NormalEnemyType type, int x, int y)
{
	Entity* ret = nullptr;

	switch (type)
	{
	case NormalEnemyType::FLYING_EYE:

		ret = new NormalEnemy(NormalEnemyType::FLYING_EYE, x, y);
		break;

	case NormalEnemyType::BAT:

		ret = new NormalEnemy(NormalEnemyType::BAT, x, y);
		break;
	
	default:

		LOG("ERROR: Entity Type not set when creating");
		break;
	}
	
	if (ret != nullptr) {
		entityList.add(ret);
		//ret->position.x = x;
		//ret->position.y = y;
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

	return ret;
}

void EntityManager::DestroyEntity(Entity* entity)
{
	ListItem<Entity*>* entityInList;
	entityInList = entityList.start;
	for (entityInList = entityList.start; entityInList != nullptr; entityInList = entityInList->next)
	{
		if (entityInList->data == entity) {
			entityInList->data->CleanUp();
			entityList.del(entityInList);
		}
	}
}