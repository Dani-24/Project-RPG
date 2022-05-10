#ifndef __SCENE_H__
#define __SCENE_H__

#include "Module.h"
#include "GuiButton.h"
#include "Animation.h"

struct SDL_Texture;
class Player;
class Cock;
class Barkeeper;
class NPC;
class NormalEnemy;
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

private:

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
	List<Character*> partyList;
	List<Item*> itemList;
	Character* valionchar;
	int backFx, loadFx, saveFx;
	int hp,hpw;
	char lifeprota[100] = { "\0" };
	char lifewizard[100] = { "\0" };
	char towns[100] = { "\0" };
	char dojos[100] = { "\0" };
	char shops[100] = { "\0" };
	char shopsubs[100] = { "\0" };
	char taberns[100] = { "\0" };

	SDL_Texture* gui;
	SDL_Texture* mpfgui;
	SDL_Texture* fpfgui;
	SDL_Texture* magogui;

	bool playloading = false;

	GuiButton* restart;
	GuiButton* backtoMenu;

	SDL_Texture* restartTex;
	SDL_Texture* press_restartTex;


	SDL_Texture* backtoMenuTex;
	SDL_Texture* press_backtoMenuTex;
	

};

#endif // __SCENE_H__