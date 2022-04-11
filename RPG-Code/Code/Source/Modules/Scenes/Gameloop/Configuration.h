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
	bool Awake();

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
	GuiButton* FXp;//increse the music volume
	GuiButton* FXm;//decrese the music volume
	GuiButton* fullS;//increse the music volume
	GuiButton* Vsync;//decrese the music volume
	GuiButton* frcap30;//increse the music volume
	GuiButton* frcap60;//increse the music volume
	GuiButton* back;//increse the music volume
	
	int backFx, loadFx, saveFx;

public:
	bool pause;


};



#endif