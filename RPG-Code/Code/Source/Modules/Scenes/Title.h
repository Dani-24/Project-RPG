#ifndef __TITLE_H__
#define __TITLE_H__

#include "Module.h"
#include "Animation.h"

struct SDL_Texture;

class TitleScene : public Module
{
public:

	TitleScene(App* application, bool start_enabled = true);

	// Destructor
	virtual ~TitleScene();

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

private:

	SDL_Texture* title;
	SDL_Texture* buttonsUI;

};

#endif // !__TITLE_H__