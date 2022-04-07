#pragma once
#ifndef __FADETOBLACK_H__
#define __FADETOBLACK_H__

#include "App.h"
#include "Module.h"
#include "SDL/include/SDL_rect.h"

class FadeToBlack : public Module
{
public:
	FadeToBlack(App* application, bool start_enabled = true);

	~FadeToBlack();

	bool Start() override;

	bool Update(float dt) override;

	bool PostUpdate() override;

	//call another module and starts the proces to fade
	bool DoFadeToBlack(Module* toDisable, Module* toEnable, float frames = 60);

private:

	enum Fade_Step
	{
		NONE,
		TO_BLACK,
		FROM_BLACK
	}
	currentStep = Fade_Step::NONE;
	//frame count
	Uint32 frameCount = 0;
	Uint32 maxFadeFrames = 0;
	//rectangle of the screen
	SDL_Rect screenRect;

	Module* moduleToEnable = nullptr;
	Module* moduleToDisable = nullptr;
};

#endif //__FADETOBLACK_H__