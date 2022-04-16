#ifndef __TITLE_H__
#define __TITLE_H__

#include "Module.h"
#include "GuiButton.h"
#include "Animation.h"


struct SDL_Texture;

class TitleScene : public Module
{
public:

	TitleScene(App* application, bool start_enabled = true);

	// Destructor
	virtual ~TitleScene();

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

public:
	const char* startChar;
	const char* contChar;
	const char* optChar;
	const char* credChar;
	const char* exitChar;
	const char* titlChar;
	const char* mustitlChar;
	const char* fxselChar;

private:

	SDL_Texture* titleBg;

	Animation titleBGAnim;

	int confirmFx;

	bool pause;
	bool exitGame;

	// Buttons

	GuiButton* btn1;
	GuiButton* btn2;
	GuiButton* btn3;
	GuiButton* btn4;
	GuiButton* btn5;

	SDL_Texture* startb;
	SDL_Texture* continueb;
	SDL_Texture* optionsb;
	SDL_Texture* creditsb;
	SDL_Texture* exitb;	
};

#endif // !__TITLE_H__