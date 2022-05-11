#ifndef __QUEST_MANAGER_H__
#define __QUEST_MANAGER_H__

#include "Module.h"
#include "List.h"
#include <vector>

enum class QuestState 
{
	DISABLED,
	AVAILABLE,
	INPROCESS,
	FINISHED	
};

struct Quest {
	int QuestId;
	int NPCId;
	int QuestGold;
	int QuestExp;
	bool QuestChain;
	const char* QuestType;
	int QuestChainId;
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

	//// Load / Save
	//bool LoadState(pugi::xml_node&);
	//bool SaveState(pugi::xml_node&) const;
	

public:
	QuestState ActualQuest;

	List<Quest> quests;

};


#endif // !__QUEST_MANAGER_H__