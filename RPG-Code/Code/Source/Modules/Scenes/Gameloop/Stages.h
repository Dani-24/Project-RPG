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
	LOSE
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
	bool LoadState(pugi::xml_node& data);*/

private:
	int hitfx1, hitfx2, hitfx3, shieldfx, chdiefx, doorFx;

	int introductionFase = 0;

	SDL_Texture* WinScreen;
	SDL_Texture* LoseScreen;
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

	GuiButton* restart;
	SDL_Texture* restartTex;
	SDL_Texture* press_restartTex;

	GuiButton* backtoMenu;
	SDL_Texture* backtoMenuTex;
	SDL_Texture* press_backtoMenuTex;
};

#endif // __STAGES_H__
