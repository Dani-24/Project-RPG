#ifndef __QUEST_MANAGER_H__
#define __QUEST_MANAGER_H__

#include "Module.h"
#include "List.h"
#include <vector>

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



};


#endif // !__QUEST_MANAGER_H__