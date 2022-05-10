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

	GuiButton* musp;		//increase the music volume
	GuiButton* musm;		//decrease the music volume
	GuiButton* FXp;			//increase the FX volume
	GuiButton* FXm;			//decrease the FX volume
	GuiButton* fullS;		//Change fullscreen mode
	GuiButton* Vsync;		//enable/disable Vsync
	//GuiButton* frcap30;	//change frcap to 30fps
	//GuiButton* frcap60;	//change frcap to 60fps
	GuiButton* back;		//back to the last screen
	
	int backFx, loadFx, saveFx, btnSelection;

public:
	bool pause;
	
	bool fulls;
	SDL_Texture* background;

};



#endif