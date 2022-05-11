#include "QuestManager.h"
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

QuestManager::QuestManager(App* application, bool start_enabled) : Module(application, start_enabled)
{
	name.Create("QuestManager");
}

QuestManager::~QuestManager()
{}

bool QuestManager::Awake(pugi::xml_node& config)
{

	return true;
}

bool QuestManager::Start() 
{
	bool ret = true;

	return ret;
}

bool QuestManager::PreUpdate()
{
	bool ret = true;

	switch (ActualQuest)
	{
	case QuestState::DISABLED:
		break;
	case QuestState::AVAILABLE:
		break;
	case QuestState::INPROCESS:
		break;
	case QuestState::FINISHED:
		break;
	default:
		break;
	}

	return ret;
}

bool QuestManager::Update(float dt)
{
	bool ret = true;

	switch (ActualQuest)
	{
	case QuestState::DISABLED:
		break;
	case QuestState::AVAILABLE:
		break;
	case QuestState::INPROCESS:
		break;
	case QuestState::FINISHED:
		break;
	default:
		break;
	}

	return ret;
}

bool QuestManager::PostUpdate()
{
	bool ret = true;

	switch (ActualQuest)
	{
	case QuestState::DISABLED:

		break;
	case QuestState::AVAILABLE:
		break;
	case QuestState::INPROCESS:
		break;
	case QuestState::FINISHED:
		break;
	default:
		break;
	}

	return ret;
}

bool QuestManager::CleanUp() 
{
	bool ret = true;

	return ret;
}