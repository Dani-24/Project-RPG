#ifndef __STATSMENU_H__
#define __STATSMENU_H__

#include "Module.h"
#include "GuiButton.h"
#include "Animation.h"

#include "Defs.h"
#include "Log.h"

struct SDL_Texture;

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
		* gui, *invTex,*presinvTex;

	// Lists
	List<Character*>* charactersOnUI;
	
	//  GUI_buttons
	GuiButton*  backButton, *invent, *ch1,*ch2,*ch3,*ch4;

	int chselect;

	int buttonSfx, backSfx;

	bool wait, _wait;
};

#endif