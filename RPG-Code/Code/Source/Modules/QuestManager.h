#ifndef __QUEST_MANAGER_H__
#define __QUEST_MANAGER_H__

#include "Module.h"
#include "List.h"
#include "NPC.h"
#include "DialogSystem.h"
#include <vector>

enum class QuestType
{
	KILL,
	RECOLECT,
	INTERACT
};

enum class QuestState 
{
	DISABLED,
	AVAILABLE,
	ACTIVE,
	COMPLETED,
	FINISHED	
};

class Quest 
{
public:
	QuestType questType;
	QuestState State;
	const char* questName; //Name of the quest
	const char* questNumber; //Name of the quest
	const char* questDescription;; //A text to descrive the quest
	int QuestId; //Number of the quest
	int NPCId; //Npc that give you the quest
	int QuestGold; //Gold reward
	int QuestExp; //Exp reward
	bool QuestChain; //if it's in a chain
	bool QuestLastChain;
	int QuestChainId; //chain id
	int QuestInChainId; //in chain number
	bool toPrint;
	bool toPrintC;
	bool printed;

	int objectiveNum;

	int NPCinteractId;

	const char* availableDialog[DIALOG_LENGHT] = { "active quest" };
	const char* activeDialog[DIALOG_LENGHT] = { "quest in process" };
	const char* completedDialog[DIALOG_LENGHT] = { "take reward" };

	bool completedAnimation = true;

public:
	Quest()
	{
		questType = QuestType::INTERACT;
		State = QuestState::AVAILABLE;
		questName = "Default Name";
		questDescription = "Haz algo";
		questNumber = "Quest 0";
		QuestId = 0;
		NPCId = 0;
		QuestGold = 0;
		QuestExp = 0;
		QuestChain = false;
		QuestLastChain = false;
		QuestChainId = 0;
		QuestInChainId = 0;
		toPrint = false;
		toPrintC = false;
		printed = false;

		objectiveNum = 0;

		NPCinteractId = 0;

	}

	Quest(QuestType qtype, QuestState qState, int ID, int NPCid, const char* name, const char* number, const char* description, int Gold, int XP, int objective_NPCid, int ChainId, int inChainId, bool LastInChain,
		const char* available[DIALOG_LENGHT], const char* active[DIALOG_LENGHT], const char* completed[DIALOG_LENGHT], bool print, bool printC)
	{
		questType = qtype;
		State = qState;
		questName = name;
		questNumber = number;
		questDescription = description;
		QuestId = ID;
		NPCId = NPCid;
		QuestGold = Gold;
		QuestExp = XP;
		QuestChainId = ChainId;
		QuestInChainId = inChainId;
		if (QuestChainId != 0) {
			QuestChain = true;
		}
		QuestLastChain = LastInChain;
		toPrint = print;
		toPrintC = printC;


		switch (qtype) {
		case QuestType::INTERACT:
			objectiveNum = 0;

			NPCinteractId = objective_NPCid;
			break;
		default:
			objectiveNum = objective_NPCid;

			NPCinteractId = 0;
			break;
		}

		for (int i = 0; i < DIALOG_LENGHT; i++) {
			if (available[i] != NULL) {
				availableDialog[i] = available[i];
			}
			if (active[i] != NULL) {
				activeDialog[i] = active[i];
			}
			if (completed[i] != NULL) {
				completedDialog[i] = completed[i];
			}

		}
	}


};


class QuestManager : public Module
{
public:

	QuestManager(App* application, bool start_enabled = true);
	~QuestManager();

	bool Awake(pugi::xml_node& config);
	bool Start();
	bool PreUpdate();
	bool Update(float dt);
	bool PostUpdate();
	bool CleanUp();

	void CheckQuest(int NPCid);
	void CheckState(int ID);
	void GiveReward(int ID);
	void CheckChain(int ID);
	void InteractComplete(int ID);

	//// Load / Save
	//bool LoadState(pugi::xml_node&);
	//bool SaveState(pugi::xml_node&) const;
	

public:

	List<Quest*> questList, questToPrintList;
	bool q2 = false;
};


#endif // !__QUEST_MANAGER_H__