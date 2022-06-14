#ifndef __QUESTMENU_H__
#define __QUESTMENU_H__

#include "Module.h"
#include "GuiButton.h"
#include "Animation.h"
#include "EasingFunctions.h"
#include "QuestManager.h"

#include "Defs.h"
#include "Log.h"

struct SDL_Texture;
struct Q_Pos
{
	iPoint Position;
};

class Character;


class QuestMenu : public Module
{
public:

	QuestMenu(App* application, bool start_enabled = true);
	virtual ~QuestMenu();

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

	//variables de interfaz
	SDL_Texture* backButtonText,
		* backButtonPressedText,
		* qmenu, *invText,*presinvText;

	// Lists
	List<Quest*>* quests;
	int questToPrint;

	// anim

	Q_Pos Q_pos;

	iPoint Q_pointA;
	iPoint Q_pointB;

	int Q_iterations;
	int Q_total_iterations;
	bool Q_easing_active;
	EasingFunctions Q_Efunction;

	Q_Pos Q_pos_out;

	iPoint Q_pointA_out;
	iPoint Q_pointB_out;

	int Q_iterations_out;
	int Q_total_iterations_out;
	bool Q_easing_active_out;
	
	//  GUI_buttons
	GuiButton*  backButton, *invent, *q1,*q2,*q3,*q4;

	int qselect;

	int buttonSfx, backSfx;

	bool wait, _wait;
};

#endif