#include "FadeToBlack.h"
#include "Window.h"
#include "Render.h"
#include "Camera.h"
#include "ModuleQFonts.h"

#include "SDL/include/SDL_render.h"

FadeToBlack::FadeToBlack(App* application, bool start_enabled) : Module(application, start_enabled)
{
	name.Create("fade");
}
FadeToBlack::~FadeToBlack()
{

}
bool FadeToBlack::Start()
{
	LOG("Preparing Fade Screen");

	screenRect = { 0,0, app->win->GetWidth() * (int)app->win->GetScale(), app->win->GetHeight() * (int)app->win->GetScale() };

	SDL_SetRenderDrawBlendMode(app->render->renderer, SDL_BLENDMODE_BLEND);

	fading = false;

	return true;
}

bool FadeToBlack::Update(float dt)
{
	if (currentStep == Fade_Step::NONE)
	{
		return true;
	}

	if (currentStep == Fade_Step::TO_BLACK)
	{
		++frameCount;
		if (frameCount >= maxFadeFrames)
		{
			if (moduleToDisable != nullptr) {
				moduleToDisable->Disable();
				moduleToEnable->Enable();
			}

			currentStep = Fade_Step::FROM_BLACK;
		}
	}
	else
	{
		--frameCount;
		if (frameCount <= 0)
		{
			fading = false;
			currentStep = Fade_Step::NONE;
		}
	}
	return true;
}

bool FadeToBlack::PostUpdate()
{
	if (currentStep == Fade_Step::NONE)
	{
		return true;
	}
	float fadeRatio = (float)frameCount / (float)maxFadeFrames;

	SDL_SetRenderDrawColor(app->render->renderer, 0, 0, 0, (Uint8)(fadeRatio * 255.0f));
	SDL_RenderFillRect(app->render->renderer, &screenRect);

	// Draw Loading text
	app->font->DrawText("Loading . . .", app->camera->GetPos().x + app->win->GetWidth() / app->win->GetScale() - 110, app->camera->GetPos().y + app->win->GetHeight()/app->win->GetScale() - 25);

	return true;
}

bool FadeToBlack::DoFadeToBlack(Module* moduleToDisable, Module* moduleToEnable, float frames)
{
	bool ret = false;

	if (currentStep == Fade_Step::NONE)
	{
		currentStep = Fade_Step::TO_BLACK;
		frameCount = 0;
		maxFadeFrames = frames;

		this->moduleToDisable = moduleToDisable;
		this->moduleToEnable = moduleToEnable;

		fading = true;

		ret = true;
	}
	return ret;
}

bool FadeToBlack::DoFadeToBlack(float frames)
{
	bool ret = false;

	if (currentStep == Fade_Step::NONE)
	{
		currentStep = Fade_Step::TO_BLACK;
		frameCount = 0;
		maxFadeFrames = frames;

		this->moduleToDisable = nullptr;
		this->moduleToEnable = nullptr;

		fading = true;

		ret = true;
	}
	return ret;
}