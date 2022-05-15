#pragma once
#ifndef __FADETOBLACK_H__
#define __FADETOBLACK_H__

#include "App.h"
#include "Module.h"
#include "SDL/include/SDL_rect.h"

#include "Stages.h"



class FadeToBlack : public Module
{
public:
	
	FadeToBlack(App* application, bool start_enabled = true);

	~FadeToBlack();

	bool Start() override;

	bool Update(float dt) override;

	bool PostUpdate() override;

	// Call another module and starts the proces to fade
	bool DoFadeToBlack(Module* toDisable, Module* toEnable, float frames = 60);

	// Fade without disabling modules
	bool DoFadeToBlack(float frames = 60);

	// Fade Between stages
	bool DoFadeToBlack(StageIndex stage, float frames = 60);
	
private:
	enum class Fade_Step {
		NONE,
		TO_BLACK,
		FROM_BLACK,
		SQUARED,
		CIRCLE,
		SLASH,
		THEATRE,
		DISSOLVE,
		ZOOM,

		//TODO 1: Crea un nou tipus de transisió
		CUT
		//

	} currentStep = Fade_Step::NONE;
	
	
	//frame count
	Uint32 frameCount = 0;
	Uint32 maxFadeFrames = 0;
	//rectangle of the screen
	SDL_Rect screenRect;

	Module* moduleToEnable = nullptr;
	Module* moduleToDisable = nullptr;
	int step;
	int transitionTime;
	Fade_Step transitionType;
	SDL_Texture* sprite = nullptr;
	Module* preScene;
	Module* postScene;

public:
	bool fading;
	void Transition(Module* preScene, Module* postScene, int transitionTime, Fade_Step transitionType)
	{
		//The module is already transitioning
		if (transitionTime < 0) {
			LOG("ERROR: INVALID TRANSITION TIME");
			return;
		}

		//The module is already transitioning
		if (isEnabled()) {
			LOG("ERROR: ALREADY TRANSITIONING");
			return;
		}

		Enable();
		this->preScene = preScene;
		this->postScene = postScene;
		this->transitionTime = transitionTime;
		this->transitionType = transitionType;
	}

private:
	//void SceneChange();

	//TransitionModules
	void Squared();
	void Circle();
	void Slash();
	void Theatre();
	void Dissolve();
	void Zoom();

	//TODO 3: Declara la funció per transicionar.
	void Cut();
	bool changeStage;
	StageIndex stageToChange;
	
};

#endif //__FADETOBLACK_H__