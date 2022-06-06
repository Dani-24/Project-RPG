#ifndef __SCENE_H__
#define __SCENE_H__

#include "Module.h"
#include "GuiButton.h"
#include "Animation.h"
#include "Usable.h"
#include "Item.h"

struct SDL_Texture;
class Player;
class Cock;
class Barkeeper;
class NPC;
class NormalEnemy;
class BossEnemy;
class Party;
class Character;
class Item;

class Scene : public Module
{
public:

	Scene(App* application, bool start_enabled = true);

	// Destructor
	virtual ~Scene();

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

	// Define multiple Gui Event methods
	bool OnGuiMouseClickEvent(GuiControl* control);

public:
	//Draws character bars on gui
	void ShowGUI();
	void CharBars();

	bool AddItem(UsableType type);

private:

	SString CharRest;
	SString	_CharRest;
	SString	CharBackTex;
	SString	_CharBackTex;
	SString	CharLoc;
	SString	CharFxBack;
	SString	CharFxLoad;
	SString	CharFxSave;

	float fpsdt;
	//variables de interfaz
	float hpc, hpv;
	float pmc, pmv;

public:
	bool pause;
	bool playing;
	bool guiactivate;
	bool godmode;
	Player* player = nullptr;
	List<NPC*> npcList;
	List<NormalEnemy*> normalEnemyList;
	List<BossEnemy*> bossList;
	List<Character*> partyList;
	List<Item*> itemList;
	List<StageIndex> allStages;
	ListItem<StageIndex>* stageSwap;
	
	int backFx, loadFx, saveFx;
	char lifeTextUI[100] = { "\0" };
	char currentPlace_UI[100] = { "\0" };

	SDL_Texture* characterBG;

	bool playloading = false;

	GuiButton* restart;
	GuiButton* backtoMenu;

	SDL_Texture* restartTex;
	SDL_Texture* press_restartTex;


	SDL_Texture* backtoMenuTex;
	SDL_Texture* press_backtoMenuTex;

	SDL_Texture* locationUI;
	bool showLocation = true;

private: // Hacer listas esta sobrevalorado supongo:

	// Normal Enemies
	iPoint eyePos = { 660, 100 }; // 680 100
	iPoint batPos = { 600, 100 };
	iPoint skeletonPos = { 750, 50 };

	//ENEMIES TOWER1
	iPoint eyePosT1 = { 1354, 1476 };
	iPoint batPosT1 = { 835, 999 };
	iPoint skeletonPosT1 = { 483, 259 };

	iPoint eyePosT1_2 = { 1343, 1103 };
	iPoint batPosT1_2 = { 784, 999 };
	iPoint skeletonPosT1_2 = { 483, 294 };

	iPoint eyePosT1_3 = { 2753, 524 };

	iPoint skeletonPosT1_3 = { 2464, 281 };

	//ENEMIES TOWER2
	iPoint eyePosT2 = { 2198, 1614 };
	iPoint batPosT2 = { 2286, 1678 };
	iPoint skeletonPosT2 = { 2616, 2014 };

	iPoint eyePosT2_2 = { 2616, 2080 };
	iPoint batPosT2_2 = { 4026, 1283 };
	iPoint skeletonPosT2_2 = { 3317, 598 };

	iPoint eyePosT2_3 = { 3317, 657 };

	iPoint skeletonPosT2_3 = { 1127, 1045 };


	//ENEMIES TOWER3
	iPoint eyePosT3 = { 1599, 2858 };
	iPoint batPosT3 = { 723, 2858 };
	iPoint skeletonPosT3 = { 2616, 2014 };

	iPoint eyePosT3_2 = { 454, 1868 };
	iPoint batPosT3_2 = { 3973, 841 };
	iPoint skeletonPosT3_2 = { 366, 304 };

	iPoint eyePosT3_3 = { 366, 350 };

	iPoint skeletonPosT3_3 = { 1127, 1045 };
};

#endif // __SCENE_H__