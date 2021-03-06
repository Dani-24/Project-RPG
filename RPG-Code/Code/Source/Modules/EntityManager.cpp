#include "EntityManager.h"
#include "Entity.h"

#include "DynamicEntity.h"
#include "StaticEntity.h"

#include "Character.h"
#include "Player.h"

#include "NPC.h"
#include "NormalEnemy.h"
#include "BossEnemy.h"
#include "Camera.h"

#include "Item.h"
#include "Equipment.h"
#include "Usable.h"
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

	pugi::xml_node saves = data.append_child("Saves");

	saves.append_attribute("save1") = app->scene->ch1;
	saves.append_attribute("save2") = app->scene->ch2;
	saves.append_attribute("save3") = app->scene->ch3;

	if (app->scene->partyList.count() > 1) {
		pugi::xml_node party = data.append_child("Valion");
		party.append_attribute("level") = app->scene->partyList.At(1)->data->stats->level;
		party.append_attribute("life") = app->scene->partyList.At(1)->data->stats->health;
		party.append_attribute("x") = app->scene->partyList.At(1)->data->position.x;
		party.append_attribute("y") = app->scene->partyList.At(1)->data->position.y;
	}
	if (app->scene->partyList.count() > 2) {
		pugi::xml_node party = data.append_child("Rayla");
		party.append_attribute("level") = app->scene->partyList.At(2)->data->stats->level;
		party.append_attribute("life") = app->scene->partyList.At(2)->data->stats->health;
		party.append_attribute("x") = app->scene->partyList.At(2)->data->position.x;
		party.append_attribute("y") = app->scene->partyList.At(2)->data->position.y;
	}
	if (app->scene->partyList.count() > 3) {
		pugi::xml_node party = data.append_child("Dhion");
		party.append_attribute("level") = app->scene->partyList.At(3)->data->stats->level;
		party.append_attribute("life") = app->scene->partyList.At(3)->data->stats->health;
		party.append_attribute("x") = app->scene->partyList.At(3)->data->position.x;
		party.append_attribute("y") = app->scene->partyList.At(3)->data->position.y;
	}


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
	if (app->stages->intStage == 10 && app->stages->actualStage != StageIndex::TOWER_0) {
		app->stages->ChangeStage(StageIndex::TOWER_0);
	}
	if (app->stages->intStage == 11 && app->stages->actualStage != StageIndex::TOWER_1) {
		app->stages->ChangeStage(StageIndex::TOWER_1);
	}
	if (app->stages->intStage == 12 && app->stages->actualStage != StageIndex::TOWER_2) {
		app->stages->ChangeStage(StageIndex::TOWER_2);
	}
	if (app->stages->intStage == 13 && app->stages->actualStage != StageIndex::TOWER_FINAL_BOSS) {
		app->stages->ChangeStage(StageIndex::TOWER_FINAL_BOSS);
	}
	if (app->stages->intStage == 14 && app->stages->actualStage != StageIndex::TOWER_3) {
		app->stages->ChangeStage(StageIndex::TOWER_3);
	}
	if (app->stages->intStage == 15 && app->stages->actualStage != StageIndex::TOWER_BOSS_1) {
		app->stages->ChangeStage(StageIndex::TOWER_BOSS_1);
	}
	if (app->stages->intStage == 16 && app->stages->actualStage != StageIndex::TOWER_BOSS_2) {
		app->stages->ChangeStage(StageIndex::TOWER_BOSS_2);
	}
	if (app->stages->intStage == 17 && app->stages->actualStage != StageIndex::TOWER_BOSS_3) {
		app->stages->ChangeStage(StageIndex::TOWER_BOSS_3);
	}

	app->scene->partyList.At(0)->data->position.x = data.child("playerpos").attribute("x").as_int();
	app->scene->partyList.At(0)->data->position.y = data.child("playerpos").attribute("y").as_int();

	/*app->scene->partyList.At(0)->data->stats->maxHealth = data.child("stats").attribute("PlayerHp").as_int();
	app->scene->partyList.At(1)->data->stats->maxHealth = data.child("stats").attribute("ValionHp").as_int();*/
	//app->scene->ch1 = data.child("Saves").attribute("save1").as_bool();
	//app->scene->ch2 = data.child("Saves").attribute("save2").as_bool();
	//app->scene->ch3 = data.child("Saves").attribute("save3").as_bool();

	//pugi::xml_node Rayla = data.child("Rayla");
	//pugi::xml_node Dhion = data.child("Dhion");
	//pugi::xml_node Valion = data.child("Valion");

	//if (app->scene->ch1 == true) {

	//	int x, y, level;
	//	double life;
	//		const char* name;
	//		x = Valion.attribute("x").as_int();
	//		y = Valion.attribute("y").as_int();
	//	//	level = Valion.attribute("level").as_int();
	//	///*	life = Valion.attribute("life").as_int();*/
	//		name = Valion.attribute("name").as_string();
	//		app->scene->partyList.add((Party*)app->entities->CreateEntity(PartyType::VALION, x, y));
	//	//partyList.At(1)->data->stats->health= Valion.attribute("life").as_int();;
	//	//partyList.At(1)->data->stats->level = level;
	//}
	////if (app->scene->partyList.count() > 1) {
	////	//app->scene->partyList.At(1)->data->stats->health= Valion.attribute("life").as_double();
	////	app->scene->partyList.At(1)->data->stats->level = Valion.attribute("level").as_int();
	////}

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

	ret = new NPC(type, x, y);


	if (ret != nullptr) {
		entityList.add(ret);
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

Entity* EntityManager::CreateEntity(BossType type)
{
	Entity* ret = nullptr;

	ret = new BossEnemy(type);

	if (ret != nullptr) {
		entityList.add(ret);
	}

	return ret;
}

Entity* EntityManager::CreateEntity(UsableType type)
{
	Entity* ret = nullptr;

	ret = new Usable(type);

	if (ret != nullptr) {
		entityList.add(ret);
	}

	return ret;
}

Entity* EntityManager::CreateEntity(EquipmentType type, const char* name)
{
	Entity* ret = nullptr;

	ret = new Equipment(type, name);

	if (ret != nullptr) {
		entityList.add(ret);
	}

	return ret;
}

Entity* EntityManager::CreateEntity(WeaponType type, const char* name)
{
	Entity* ret = nullptr;

	ret = new Equipment(type, name);

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

