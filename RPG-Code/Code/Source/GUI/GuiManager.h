#ifndef __GUIMANAGER_H__
#define __GUIMANAGER_H__

#include "Module.h"
#include "GuiControl.h"
#include "Render.h"
#include "Textures.h"

#include "List.h"

struct SDL_Texture;

class GuiManager : public Module
{
public:

	// Constructor
	GuiManager(App* application, bool start_enabled = true);

	// Destructor
	virtual ~GuiManager();

	// Called before the first frame
	bool Start();

	bool Update(float dt);

	bool UpdateAll(float dt,bool logic);

	bool PostUpdate();

	bool Draw();

	// Called before quitting
	bool CleanUp();

	// Additional methods
	GuiControl* CreateGuiControl(Module* observer, GuiControlType type, int id, const char* text, iPoint position, bool drawElement = true, bool smol = false);

public:

	List<GuiControl*> controls;

	float accumulatedTime = 0.0f;
	float updateMsCycle = 0.0f;
	bool doLogic = false;

	SDL_Texture* selector;
	SDL_Texture* clicker;
	bool keyb;
};

#endif // __GUIMANAGER_H__
