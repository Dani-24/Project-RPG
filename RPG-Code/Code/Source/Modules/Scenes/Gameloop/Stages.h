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
	WIN,
	LOSE,
	TOWER_0,
	TOWER_1,
	TOWER_2,
	TOWER_3,
	TOWER_4,
	TOWER_BOSS_1,
	TOWER_BOSS_2,
	TOWER_BOSS_3,
	PROLOGUE
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

	// Define multiple Gui Event methods
	bool OnGuiMouseClickEvent(GuiControl* control);

	/*bool SaveState(pugi::xml_node& data) const;
	bool 
	
	
	
	
	State(pugi::xml_node& data);*/

private:
	int hitfx1, hitfx2, hitfx3, shieldfx, chdiefx, doorFx, loseFx;

	int introductionFase = 0;

	SDL_Texture* WinScreen;
	SDL_Texture* LoseScreen;
	SDL_Texture* WinMessage;
	SDL_Texture* LoseMessage;

	bool _wait;

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

	int intStage = 0;

	bool elect;

	const char* LoseScreenChar;
	const char* WinScreenChar;
	const char* LoseTextChar;
	const char* WinTextChar;
	const char* Hitfx1Char;
	const char* Hitfx2Char;
	const char* Hitfx3Char;
	const char* ShieldfxChar;
	const char* ChDiefxChar;
	const char* DoorChar;
	const char* LosefxChar;
	
	
};

#endif // __STAGES_H__
