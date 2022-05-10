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
	const char* titlChar;
	const char* mustitlChar;
	const char* fxselChar;
	const char* fxtitleChar;

private:

	SDL_Texture* titleBg;
	SDL_Texture* titleLogo;

	// title bullshit
	iPoint titleBgPos = {-650, -200};
	float rotateSpeed = 0.1f;
	float radius = 600;
	fPoint centre = {-650, -800};
	float angle = 0;

	int confirmFx, titleFx;

	bool pause;
	bool exitGame;

	// Buttons

	GuiButton* btn1;
	GuiButton* btn2;
	GuiButton* btn3;
	GuiButton* btn4;
	GuiButton* btn5;

	//variable para que no pete con mando
	bool wait;
};

#endif // !__TITLE_H__