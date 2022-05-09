#ifndef __PARTYSTATS_H__
#define __PARTYSTATS_H__

#include "Module.h"
#include "GuiButton.h"
#include "GuiManager.h"
struct SDL_Texture;

class PartyStats : public Module
{

public:
	PartyStats(App* application, bool start_enabled = true);

	// Destructor
	virtual ~PartyStats();

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

private:
	int confirmFx;

};

#endif