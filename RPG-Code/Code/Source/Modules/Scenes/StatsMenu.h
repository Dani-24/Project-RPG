#ifndef __STATSMENU_H__
#define __STATSMENU_H__

#include "Module.h"
#include "GuiButton.h"
#include "Animation.h"
#include "EasingFunctions.h"

#include "Defs.h"
#include "Log.h"

struct SDL_Texture;
struct S_Pos
{
	iPoint Position;
};

class Character;


class StatsMenu : public Module
{
public:

	StatsMenu(App* application, bool start_enabled = true);
	virtual ~StatsMenu();

	bool Awake(pugi::xml_node& config);

	bool Start();

	bool PreUpdate();

	bool Update(float dt);

	bool PostUpdate();

	bool CleanUp();

	float EaseInBetweenPoints(iPoint posA, iPoint posB);

	float EaseOutBetweenPoints(iPoint posA, iPoint posB);

	bool OnGuiMouseClickEvent(GuiControl* control);

	//manage the control of ui with keyboard/gamepad
	void GampadControl();

private:

	void Statss();
	//variables de interfaz
	float hpc, hpv;
	float pmc, pmv;
	float expc;
	SDL_Texture* backButtonTexture,
		* backButtonPressedTexture,
		* gui, *questsTex,*presQuestsTex;

	// Lists
	List<Character*>* charactersOnUI;

	// anim

	S_Pos S_pos;

	iPoint S_pointA;
	iPoint S_pointB;

	int S_iterations;
	int S_total_iterations;
	bool S_easing_active;
	EasingFunctions S_Efunction;

	S_Pos S_pos_out;

	iPoint S_pointA_out;
	iPoint S_pointB_out;

	int S_iterations_out;
	int S_total_iterations_out;
	bool S_easing_active_out;
	
	//  GUI_buttons
	GuiButton*  backButton, *quests, *ch1,*ch2,*ch3,*ch4;

	int chselect;

	int buttonSfx, backSfx;

	bool wait, _wait;
};

#endif