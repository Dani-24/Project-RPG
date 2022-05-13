#include "EntityManager.h"
#include "Entity.h"

#include "DynamicEntity.h"
#include "StaticEntity.h"

#include "Character.h"
#include "Player.h"

#include "NPC.h"
#include "NormalEnemy.h"
#include "Camera.h"

#include "Party.h"
#include "Stages.h"
#include "App.h"
#include "Scene.h"



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

bool EntityManager::SaveState(pugi::xml_node& data) const
{
	pugi::xml_node playerpos = data.append_child("playerpos");
	pugi::xml_node stage = data.append_child("actualStage");
	pugi::xml_node stats = data.append_child("stats");

	playerpos.append_attribute("x") = app->scene->partyList.At(0)->data->position.x;
	playerpos.append_attribute("y") = app->scene->partyList.At(0)->data->position.y;

	stage.append_attribute("stage") = app->stages->intStage;

	/*stats.append_attribute("PlayerHp") = app->scene->partyList.At(0)->data->stats->maxHealth;
	stats.append_attribute("ValionHp") = app->scene->partyList.At(1)->data->stats->maxHealth;*/

	//Saved.attribute("saved").set_value(saved);

	return false;
}

bool EntityManager::LoadState(pugi::xml_node& data)
{
	app->stages->intStage= data.child("actualStage").attribute("stage").as_int();

	if (app->stages->intStage == 2 && app->stages->actualStage!=StageIndex::TOWN) {
		app->stages->ChangeStage(StageIndex::TOWN);
	}
	if (app->stages->intStage == 3 && app->stages->actualStage != StageIndex::TAVERN) {
		app->stages->ChangeStage(StageIndex::TAVERN);
	}
	if (app->stages->intStage == 4 && app->stages->actualStage != StageIndex::DOJO) {
		app->stages->ChangeStage(StageIndex::DOJO);
	}
	if (app->stages->intStage == 5 && app->stages->actualStage != StageIndex::SHOP) {
		app->stages->ChangeStage(StageIndex::SHOP);
	}
	if (app->stages->intStage == 6 && app->stages->actualStage != StageIndex::SHOPSUB) {
		app->stages->ChangeStage(StageIndex::SHOPSUB);
	}
	if (app->stages->intStage == 7 && app->stages->actualStage != StageIndex::INTRODUCTION) {
		app->stages->ChangeStage(StageIndex::INTRODUCTION);
	}
	if (app->stages->intStage == 0 && app->stages->actualStage != StageIndex::NONE) {
		app->stages->ChangeStage(StageIndex::NONE);
	}
	if (app->stages->intStage == 8 && app->stages->actualStage != StageIndex::WIN) {
		app->stages->ChangeStage(StageIndex::WIN);
	}
	if (app->stages->intStage == 9 && app->stages->actualStage != StageIndex::LOSE) {
		app->stages->ChangeStage(StageIndex::LOSE);
	}
	if (app->stages->intStage == 10 && app->stages->actualStage != StageIndex::TOWER0) {
		app->stages->ChangeStage(StageIndex::TOWER0);
	}
	if (app->stages->intStage == 11 && app->stages->actualStage != StageIndex::TOWER1) {
		app->stages->ChangeStage(StageIndex::TOWER1);
	}
	if (app->stages->intStage == 12 && app->stages->actualStage != StageIndex::TOWER2) {
		app->stages->ChangeStage(StageIndex::TOWER2);
	}
	if (app->stages->intStage == 13 && app->stages->actualStage != StageIndex::TOWER3) {
		app->stages->ChangeStage(StageIndex::TOWER3);
	}

	app->scene->partyList.At(0)->data->position.x = data.child("playerpos").attribute("x").as_int();
	app->scene->partyList.At(0)->data->position.y = data.child("playerpos").attribute("y").as_int();

	/*app->scene->partyList.At(0)->data->stats->maxHealth = data.child("stats").attribute("PlayerHp").as_int();
	app->scene->partyList.At(1)->data->stats->maxHealth = data.child("stats").attribute("ValionHp").as_int();*/
	

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

Entity* EntityManager::CreateEntity(PartyType type, int x, int y)
{
	Entity* ret = nullptr;

	ret = new Party(type, x, y);

	if (ret != nullptr) {
		entityList.add(ret);
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
	case NPCType::FUENTE:

		ret = new NPC(NPCType::FUENTE, x, y);
		break;
	case NPCType::CARTELSUDTOWN:

		ret = new NPC(NPCType::CARTELSUDTOWN, x, y);
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
	case NormalEnemyType::SKELETON:

		ret = new NormalEnemy(NormalEnemyType::SKELETON, x, y);
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

