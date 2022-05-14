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
#include "Shop.h"


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
	Quest* quest1 = new Quest();
	questList.add(quest1);


	return ret;
}

bool QuestManager::PreUpdate()
{
	bool ret = true;

	

	return ret;
}

bool QuestManager::Update(float dt)
{
	bool ret = true;
	ListItem<Quest*>* QuestInList;
	for (QuestInList = questList.start; QuestInList != NULL; QuestInList = QuestInList->next)
	{
		if (QuestInList->data->autoComplete)
		{
			GiveReward(QuestInList->data->QuestId);
			CheckChain(QuestInList->data->QuestId);
			QuestInList->data->State = QuestState::FINISHED;
		}
	}
	

	return ret;
}

bool QuestManager::PostUpdate()
{
	bool ret = true;

	return ret;
}

bool QuestManager::CleanUp() 
{
	bool ret = true;

	return ret;
}

void QuestManager::QInteract(NPCType npc, const char* dialog[DIALOG_LENGHT]) {

	app->dialogs->CreateDialog(npc, dialog);
	if (npc == NPCType::FUENTE) {
		for (ListItem<Character*>* characterList = app->scene->partyList.start; characterList != NULL; characterList = characterList->next) {
			characterList->data->stats->health = characterList->data->stats->maxHealth;
			characterList->data->isAlive = true;
			app->scene->player->dieM.Reset();
			app->scene->player->dieF.Reset();
			characterList->data->deathAnim.Reset();
		}

	}
	if (npc == NPCType::MERCHANT) {
		app->shop->Enable();
	}
}

void QuestManager::CheckQuest(int NPCid)
{
	bool n = false;
	ListItem<Quest*>* QuestInList;

	for (QuestInList = questList.start; QuestInList != NULL; QuestInList = QuestInList->next)
	{
		if (QuestInList->data->NPCId == NPCid) 
		{
			n = true;
			CheckState(QuestInList->data->QuestId);
		}

		if (QuestInList->data->questType == QuestType::INTERACT) {
			if (QuestInList->data->NPCinteractId == NPCid)
			{
				//CompleteInteract(QuestInList->data->QuestId);
				if (QuestInList->data->State == QuestState::ACTIVE) 
				{
					n = true;
					QuestInList->data->State = QuestState::COMPLETED;
					CheckState(QuestInList->data->QuestId);
				}
				
			}
		}

	}

	if (n == false) {
		switch (NPCid)
		{
		case 1:
			QInteract(NPCType::COCK, app->scene->player->cockDialog);
			break;
		case 2:
			app->scene->player->Interact(NPCType::MERCHANT, app->scene->player->merchantDialog);
			break;
		case 3:
			app->scene->player->Interact(NPCType::BARKEEPER, app->scene->player->barkeeperDialog);
			break;
		case 4:
			app->scene->player->Interact(NPCType::TRAINER, app->scene->player->trainerDialog);
			break;
		case 5:
			app->scene->player->Interact(NPCType::EMILIO, app->scene->player->emilioDialog);
			break;
		case 7:
			app->scene->player->Interact(NPCType::FUENTE, app->scene->player->fuenteDialog);
			break;
		case 8:
			app->scene->player->Interact(NPCType::CARTELSUDTOWN, app->scene->player->cartelSudTownDialog);
			break;
		default:
			break;
		}
	}
}

void QuestManager::CheckState(int Id)
{
	ListItem<Quest*>* QuestInList;
	for (QuestInList = questList.start; QuestInList != NULL; QuestInList = QuestInList->next)
	{
		if (QuestInList->data->QuestId == Id) {
			switch (QuestInList->data->State)
			{
			case QuestState::DISABLED:
				switch (QuestInList->data->NPCId)
				{
				case 1:
					QInteract(NPCType::COCK, app->scene->player->cockDialog);
					break;
				case 2:
					app->scene->player->Interact(NPCType::MERCHANT, app->scene->player->merchantDialog);
					break;
				case 3:
					app->scene->player->Interact(NPCType::BARKEEPER, app->scene->player->barkeeperDialog);
					break;
				case 4:
					app->scene->player->Interact(NPCType::TRAINER, app->scene->player->trainerDialog);
					break;
				case 5:
					app->scene->player->Interact(NPCType::EMILIO, app->scene->player->emilioDialog);
					break;
				case 7:
					app->scene->player->Interact(NPCType::FUENTE, app->scene->player->fuenteDialog);
					break;
				case 8:
					app->scene->player->Interact(NPCType::CARTELSUDTOWN, app->scene->player->cartelSudTownDialog);
					break;
				default:
					break;
				}
				break;
			case QuestState::AVAILABLE:
				switch (QuestInList->data->NPCId)
				{
				case 1:
					app->scene->player->Interact(NPCType::COCK, QuestInList->data->availableDialog);
					break;
				case 2:
					app->scene->player->Interact(NPCType::MERCHANT, QuestInList->data->availableDialog);
					break;
				case 3:
					app->scene->player->Interact(NPCType::BARKEEPER, QuestInList->data->availableDialog);
					break;
				case 4:
					app->scene->player->Interact(NPCType::TRAINER, QuestInList->data->availableDialog);
					break;
				case 5:
					app->scene->player->Interact(NPCType::EMILIO, QuestInList->data->availableDialog);
					break;
				case 7:
					app->scene->player->Interact(NPCType::FUENTE, QuestInList->data->availableDialog);
					break;
				case 8:
					app->scene->player->Interact(NPCType::CARTELSUDTOWN, QuestInList->data->availableDialog);
					break;
				default:
					break;
				}
				QuestInList->data->State = QuestState::ACTIVE;
				break;
			case QuestState::ACTIVE:
				switch (QuestInList->data->NPCId)
				{
				case 1:
					QInteract(NPCType::COCK, QuestInList->data->activeDialog);
					break;
				case 2:
					app->scene->player->Interact(NPCType::MERCHANT, QuestInList->data->activeDialog);
					break;
				case 3:
					app->scene->player->Interact(NPCType::BARKEEPER, QuestInList->data->activeDialog);
					break;
				case 4:
					app->scene->player->Interact(NPCType::TRAINER, QuestInList->data->activeDialog);
					break;
				case 5:
					app->scene->player->Interact(NPCType::EMILIO, QuestInList->data->activeDialog);
					break;
				case 7:
					app->scene->player->Interact(NPCType::FUENTE, QuestInList->data->activeDialog);
					break;
				case 8:
					app->scene->player->Interact(NPCType::CARTELSUDTOWN, QuestInList->data->activeDialog);
					break;
				default:
					break;
				}
				break;
			case QuestState::COMPLETED:
				switch (QuestInList->data->NPCId)
				{
				case 1:
					QInteract(NPCType::COCK, QuestInList->data->completedDialog);
					break;
				case 2:
					app->scene->player->Interact(NPCType::MERCHANT, QuestInList->data->completedDialog);
					break;
				case 3:
					app->scene->player->Interact(NPCType::BARKEEPER, QuestInList->data->completedDialog);
					break;
				case 4:
					app->scene->player->Interact(NPCType::TRAINER, QuestInList->data->completedDialog);
					break;
				case 5:
					app->scene->player->Interact(NPCType::EMILIO, QuestInList->data->completedDialog);
					break;
				case 7:
					app->scene->player->Interact(NPCType::FUENTE, QuestInList->data->completedDialog);
					break;
				case 8:
					app->scene->player->Interact(NPCType::CARTELSUDTOWN, QuestInList->data->completedDialog);
					break;
				default:
					break;
				}
				GiveReward(QuestInList->data->QuestId);
				CheckChain(QuestInList->data->QuestId);
				QuestInList->data->State = QuestState::FINISHED;
				break;
			case QuestState::FINISHED:
				switch (QuestInList->data->NPCId)
				{
				case 1:
					QInteract(NPCType::COCK, app->scene->player->cockDialog);
					break;
				case 2:
					app->scene->player->Interact(NPCType::MERCHANT, app->scene->player->merchantDialog);
					break;
				case 3:
					app->scene->player->Interact(NPCType::BARKEEPER, app->scene->player->barkeeperDialog);
					break;
				case 4:
					app->scene->player->Interact(NPCType::TRAINER, app->scene->player->trainerDialog);
					break;
				case 5:
					app->scene->player->Interact(NPCType::EMILIO, app->scene->player->emilioDialog);
					break;
				case 7:
					app->scene->player->Interact(NPCType::FUENTE, app->scene->player->fuenteDialog);
					break;
				case 8:
					app->scene->player->Interact(NPCType::CARTELSUDTOWN, app->scene->player->cartelSudTownDialog);
					break;
				default:
					break;
				}
				break;
			default:
				break;
			}

		}
	}

}

void QuestManager::GiveReward(int Id) {
	ListItem<Quest*>* QuestInList;
	for (QuestInList = questList.start; QuestInList != NULL; QuestInList = QuestInList->next)
	{
		if (QuestInList->data->QuestId == Id) {
			for (int i = 0; i < app->scene->partyList.count(); i++) {
				app->scene->partyList.At(i)->data->stats->lvlup(QuestInList->data->QuestExp);
			}
		}
	}
}

void QuestManager::CheckChain(int Id)
{
	int sChainId = 0, sInChainId = 0;
	ListItem<Quest*>* QuestInList;
	for (QuestInList = questList.start; QuestInList != NULL; QuestInList = QuestInList->next)
	{
		if (QuestInList->data->QuestId == Id) {
			if (QuestInList->data->QuestChain) 
			{
				if (!QuestInList->data->QuestLastChain)
				{
					sChainId = QuestInList->data->QuestChainId;
					sInChainId = QuestInList->data->QuestInChainId;
				}
			}
		}

		if (QuestInList->data->QuestChainId == sChainId) {
			if (QuestInList->data->QuestInChainId == sInChainId+1) {
				QuestInList->data->State = QuestState::AVAILABLE;
			}
		}
	}
}