#include "EntityManager.h"
#include "EntityClasses/Entity.h"


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
		ret = entityInList->data->PreUpdate();
	}
	return ret;
}

// Call modules on each loop iteration
bool EntityManager::Update(float dt)
{
	bool ret = true;
	ListItem<Entity*>* entityInList;
	entityInList = entityList.start;

	for (entityInList = entityList.start; entityInList != NULL && ret == true; entityInList = entityInList->next)
	{
		ret = entityInList->data->Update(dt);
	}
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
		ret = entityInList->data->PostUpdate();
	}
	return ret;
}

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

Entity* EntityManager::CreateEntity(EntityType type)
{
	/*Player* retPlayer = new Player();
	Enemies* retEnemy = new Enemies();
	Items* retItem = new Items();*/

	Entity* ret = nullptr;

	switch (type)
	{
	case EntityType::DYNAMIC:

		/*ret = retPlayer;
		ret->playerList.push_back(retPlayer);*/

		break;
	case EntityType::STATIC:

		/*ret = retEnemy;
		ret->enemyList.push_back(retEnemy);*/

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
		if(entityInList->data->type == EntityType)
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
}