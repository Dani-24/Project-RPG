#ifndef __CONFIGURATION_H__
#define __CONFIGURATION_H__

#include "Module.h"
#include "Animation.h"
#include "GuiButton.h"
#include "GuiSliders.h"
#include "EasingFunctions.h"

#include "App.h"

#include "SDL/include/SDL_rect.h"

struct SDL_Texture;
struct C_Pos
{
	iPoint Position;
};

class Configuration : public Module
{
public:

	Configuration(App* application, bool start_enabled = true);

	// Destructor
	virtual ~Configuration();

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

	float EaseInBetweenPoints(iPoint posA, iPoint posB);

	float EaseOutBetweenPoints(iPoint posA, iPoint posB);

	// Called before quitting
	bool CleanUp();

	// Define multiple Gui Event methods
	bool OnGuiMouseClickEvent(GuiControl* control);

private:

	GuiButton* musp;//increse the music volume
	GuiButton* musm;//decrese the music volume
	GuiButton* FXp;//increse the FX volume
	GuiButton* FXm;//decrese the FX volume
	GuiButton* fullS;//Change fullscreen mode
	GuiButton* Vsync;//active/deactive Vsync
	//GuiButton* frcap30;//change frcap to 30fps
	//GuiButton* frcap60;//change frcap to 60fps
	GuiButton* back;//back to the last screen
	
	
	List<GuiButton*> conb;

	int xt=460, yt=-15;

	void GampadControl();

	// anim

	C_Pos C_pos;

	iPoint C_pointA;
	iPoint C_pointB;

	int C_iterations;
	int C_total_iterations;
	bool C_easing_active;
	EasingFunctions C_Efunction;

	C_Pos C_pos_out;

	iPoint C_pointA_out;
	iPoint C_pointB_out;

	int C_iterations_out;
	int C_total_iterations_out;
	bool C_easing_active_out;

	bool _wait, wait;
	int ab;

public:
	bool pause;
	int backFx, loadFx, saveFx, btnSelection;
	
	bool fulls;
	SDL_Texture* background;

};



#endif