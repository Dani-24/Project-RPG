#ifndef __LOGO_H__
#define __LOGO_H__

#include "Module.h"
#include "Animation.h"

struct SDL_Texture;

class LogoScene : public Module
{
public:

	LogoScene(App* application, bool start_enabled = true);

	// Destructor
	virtual ~LogoScene();

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
	SDL_Texture* logo;

	int cont;

	int logofx;
};

#endif // !_LOGO_H_