#include "FadeToBlack.h"
#include "Window.h"
#include "Render.h"
#include "Camera.h"
#include "ModuleQFonts.h"

#include "SDL/include/SDL_render.h"

#include "Logo.h"

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

	fading = changeStage = false;

	return true;
}

bool FadeToBlack::Update(float dt)
{
	step++;
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

			if (changeStage == true) {
				app->stages->ChangeStage(stageToChange);
				changeStage = false;
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
	if (app->logoScene->isEnabled() == false) {	// Desactivado en el logo pa q quede bonico
		app->font->DrawText("Loading . . .", -app->camera->GetPos().x / app->win->GetScale() + app->win->GetWidth() / 2 - 110,
			-app->camera->GetPos().y / app->win->GetScale() + app->win->GetHeight() / 2 - 25);
	}
	switch (transitionType) {
	case  Fade_Step::TO_BLACK:
		DoFadeToBlack();
		break;
	case  Fade_Step::FROM_BLACK:
		DoFadeToBlack();
		break;
	case  Fade_Step::SQUARED:
		Squared();
		break;

	case  Fade_Step::CIRCLE:
		Circle();
		break;

	case  Fade_Step::SLASH:
		Slash();
		break;

	case  Fade_Step::THEATRE:
		Theatre();
		break;

	case  Fade_Step::DISSOLVE:
		Dissolve();
		break;

	case  Fade_Step::ZOOM:
		Zoom();
		break;

		//TODO 4: Executa la funció de la transisió
	case  Fade_Step::CUT:
		Cut();
		break;
		//

	}

	//CHANGING SCENE SWITCH
	switch (transitionType) {

		//TODO 5: Assigna el tipus de transisió perquè faci el canvi de mòdul al principi.
	case  Fade_Step::CUT:
		//

	case  Fade_Step::ZOOM:
	case Fade_Step::DISSOLVE:
		if (step >= 1)
			SceneChange();
		break;

	default:
		if (2 * step >= transitionTime)
			SceneChange();
		break;
	}

	if (step >= transitionTime)
		Disable();
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

bool FadeToBlack::DoFadeToBlack(StageIndex stage, float frames)
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

		changeStage = true;

		stageToChange = stage;

		ret = true;
	}
	return ret;
}
void FadeToBlack::SceneChange()
{
	preScene->Disable();
	postScene->Enable();
}



void FadeToBlack::Squared()
{
	int percentage = ((float)step / (float)transitionTime) * 40.0f;
	int w = app->win->screenSurface->w / 10;
	int h = app->win->screenSurface->h / 10;

	if (step * 2 >= transitionTime)
		percentage = 40 - percentage;

	for (int j = 0; j < percentage; ++j) {
		for (int i = 0; i < percentage; ++i) {
			app->render->DrawRectangle(SDL_Rect{ w * i, h * (10 - j + i), w, h }, 0, 0, 0, 255);
		}
	}
}

void FadeToBlack::Circle()
{
	if (sprite == nullptr)
		sprite = app->tex->Load("Assets/circle.png");

	float percentage = ((float)step / (float)transitionTime) * 2.0f;

	if (step * 2 >= transitionTime)
		percentage = 2.0f - percentage;

	float scale = 5.0f * percentage;

	app->render->DrawTexture2(sprite, app->win->screenSurface->w / 2.0f - 150.0f * scale, app->win->screenSurface->h / 2.0f - 150.0f * scale, scale);
}

void FadeToBlack::Slash()
{
	if (sprite == nullptr)
		sprite = app->tex->Load("Assets/slash.png");

	float percentage = ((float)step / (float)transitionTime) * 200.0f;

	if (step * 2 >= transitionTime)
		percentage = 200 - percentage;

	int scale = 3;

	app->render->DrawTexture2(sprite, ((app->win->screenSurface->h / 2) * ((100.0f - percentage) / 100.0f)) + ((app->win->screenSurface->w - (600 * scale)) / 2),
		(app->win->screenSurface->h - (300 * scale)) / 2, scale);

	app->render->DrawTexture2(sprite, ((app->win->screenSurface->w - (600 * scale)) / 2) - ((app->win->screenSurface->w / 2) * ((100.0f - percentage) / 100.0f)),
		(app->win->screenSurface->h - (300 * scale)) / 2, scale, true);
}

void FadeToBlack::Theatre()
{
	if (sprite == nullptr)
		sprite = app->tex->Load("Assets/semicircle.png");

	float percentage = ((float)step / (float)transitionTime) * 360.0f;

	int scale = 7;

	app->render->DrawTexture2(sprite, ((app->win->screenSurface->w - (300 * scale)) / 2), app->win->screenSurface->h, 1.0f, scale, false, NULL,  percentage, 150 * scale, 0);
}

void FadeToBlack::Dissolve()
{
	//If screenshot is made, load it
	if (app->render->screenshot) {
		sprite = app->tex->Load("Assets/screenshot.bmp");
	}

	//Call for screenshot
	if (sprite == nullptr) {
		app->render->pendingToScreenshot = true;
		return;
	}

	float percentage = ((float)step / (float)transitionTime) * 255.0f;

	SDL_SetTextureBlendMode(sprite, SDL_BLENDMODE_BLEND);
	SDL_SetTextureAlphaMod(sprite, 255.0f - percentage);

	app->render->DrawTexture2(sprite, 0, 0, 1.0f);
}

void FadeToBlack::Zoom()
{
	//If screenshot is made, load it
	if (app->render->screenshot) {
		sprite = app->tex->Load("Assets/screenshot.bmp");
	}

	//Call for screenshot
	if (sprite == nullptr) {
		app->render->pendingToScreenshot = true;
		return;
	}

	float percentage = ((float)step / (float)transitionTime) * 5.0f;

	app->render->DrawTexture2(sprite, 0, 0, 1.0f + percentage);

}

//TODO 6: Defineix la funció de transició
void FadeToBlack::Cut() {
	//If screenshot is made, load it
	if (app->render->screenshot) {
		sprite = app->tex->Load("Assets/screenshot.bmp");
	}

	//Call for screenshot
	if (sprite == nullptr) {
		app->render->pendingToScreenshot = true;
		return;
	}

	float percentage = ((float)step / (float)transitionTime) * ((float)app->win->screenSurface->h / 2.0f);

	SDL_Rect top = { 0, 0, app->win->screenSurface->w, app->win->screenSurface->h / 2 };
	SDL_Rect bot = { 0, app->win->screenSurface->h / 2, app->win->screenSurface->w, app->win->screenSurface->h / 2 };
	app->render->DrawTexture2(sprite, 0, -percentage, 1.0f, false, &top);
	app->render->DrawTexture2(sprite, 0, app->win->screenSurface->h / 2 + percentage, 1.0f, false, &bot);
}
//

