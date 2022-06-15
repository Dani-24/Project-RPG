#ifndef __MODULE_VISUALEFFECTS_H__
#define __MODULE_VISUALEFFECTS_H__

#include "Module.h"
#include "Animation.h"
#include "App.h"

#define ScreenX 1280/2
#define ScreenY 720/2

struct SDL_Texture;

enum class Effects {
	LOADING,
	QUESTCOMPLETED,
	TRANSITION1,
	TRANSITION2,
	NONE
};

class VisualEffects : public Module
{
public:
	VisualEffects(App* application, bool start_enabled = true);
	~VisualEffects();

	bool Start();
	bool Update(float dt);
	bool PostUpdate();
	bool CleanUp();

	void DisplayEffect(Effects effect);

private:

	Effects currentEffect = Effects::NONE;

	SDL_Texture* loadingTex,
		* questCTex,
		* trans1Tex,
		* trans2Tex;

	Animation* currentAnim,
		loadingAnim,
		questCAnim,
		trans1Anim,
		trans2Anim;

	int questFX, trans1FX, trans2FX;
};

#endif // !__VISUALEFFECTS_H__