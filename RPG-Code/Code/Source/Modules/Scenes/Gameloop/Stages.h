#ifndef __STAGES_H__
#define __STAGES_H__

#include "Module.h"
#include "GuiButton.h"
#include "Animation.h"

struct SDL_Texture;
class Player;
class Cock;

class NPC;
class NormalEnemy;
class Character;

enum class StageIndex {
	NONE,
	TOWN,
	TAVERN,
	DOJO,
	SHOP,
	SHOPSUB,
	INTRODUCTION,
};

class Stages : public Module
{
public:

	Stages(App* application, bool start_enabled = true);

	// Destructor
	virtual ~Stages();

	// Called before render is available
	bool Awake(pugi::xml_node& config);

	// Called before the first frame
	bool Start();

	// Called before all Updates
	bool PreUpdate();

	// Called each loop iteration
	bool Update(float dt);

	// Called before all Updates
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

	void ChangeStage(StageIndex newStage);

private:
	int hitfx1, hitfx2, hitfx3, shieldfx, chdiefx;

	int epilogFase = 0;
public:
	bool pause;

	bool onBattle;

	bool fxbool = false;

	int eAnim = 1, pAnim = 1, vAnim = 1;

	StageIndex actualStage;

	Player* playerPtr;
	List<NPC*> *npcListPtr;
	List<NormalEnemy*>* normalEnemyListPtr;

	List<Character*>* partyListPtr;

};

#endif // __STAGES_H__
