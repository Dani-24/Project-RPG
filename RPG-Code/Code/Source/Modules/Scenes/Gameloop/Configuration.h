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

	GuiButton* btn1;
	GuiButton* btn2;

	int backFx, loadFx, saveFx;

public:
	bool pause;


};



#endif