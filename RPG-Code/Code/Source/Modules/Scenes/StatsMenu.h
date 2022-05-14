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

private:
	SDL_Texture* backButtonTexture,
		* backButtonPressedTexture;

	// Lists
	List<Character*>* charactersOnUI;
	
	//  GUI_buttons
	GuiButton* gui;

	int buttonSfx, backSfx;
};

#endif