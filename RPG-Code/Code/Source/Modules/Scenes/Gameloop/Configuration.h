#ifndef __CONFIGURATION_H__
#define __CONFIGURATION_H__

#include "Module.h"
#include "Animation.h"
#include "GuiButton.h"

#include "App.h"

#include "SDL/include/SDL_rect.h"

struct SDL_Texture;


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

	bool _wait, wait;
	int ab;

public:
	bool pause;
	int backFx, loadFx, saveFx, btnSelection;
	
	bool fulls;
	SDL_Texture* background;

};



#endif