#ifndef __PAUSEMENU_H__
#define __PAUSEMENU_H__

#include "Module.h"
#include "GuiButton.h"
#include "GuiManager.h"
#include "EasingFunctions.h"
struct SDL_Texture;
struct Pos
{
	iPoint Position;
};

class PauseMenu : public Module
{
public:
	PauseMenu(App* application, bool start_enabled = true);

	// Destructor
	virtual ~PauseMenu();

	// Called before render is available
	bool Awake(pugi::xml_node& config);

	// Called before the first frame
	bool Start();

	// Define multiple Gui Event methods
	bool OnGuiMouseClickEvent(GuiControl* control);

	// Called before all Updates
	bool PreUpdate();

	// Called each loop iteration
	bool Update(float dt);

	// Called before all Updates
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

	//manage the control of ui with keyboard/gamepad
	void GampadControl();

	//Enable buttons
	void EnButt();

	// dissable buttons
	void DissButt();

	float EaseInBetweenPoints(iPoint posA, iPoint posB);

public:

	/*Player* player = nullptr;*/

	int confirmFx;

	bool pauseGame;

	bool resumen;

	bool exitg;

	SDL_Texture* Pausetex;

	Pos pos;

	iPoint pointA;
	iPoint pointB;

	int iterations;
	int total_iterations;
	bool easing_active;
	EasingFunctions Efunction;


	// Buttons

	GuiButton* party;
	GuiButton* invent;
	GuiButton* town;
	GuiButton* resume;
	GuiButton* config;
	GuiButton* save;
	GuiButton* load;
	GuiButton* exit;
	
private:
	//variable para que no pete con mando
	bool wait, _wait;
	bool pbutt;

};

#endif