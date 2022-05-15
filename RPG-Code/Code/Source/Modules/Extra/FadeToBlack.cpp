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
void Fade::SceneChange()
{
	preScene->Disable();
	postScene->Enable();
}



void ModuleTransitions::Squared()
{
	int percentage = ((float)step / (float)transitionTime) * 40.0f;
	int w = SCREEN_WIDTH / 10;
	int h = SCREEN_HEIGHT / 10;

	if (step * 2 >= transitionTime)
		percentage = 40 - percentage;

	for (int j = 0; j < percentage; ++j) {
		for (int i = 0; i < percentage; ++i) {
			App->renderer->DrawQuad(SDL_Rect{ w * i, h * (10 - j + i), w, h }, 0, 0, 0, 255);
		}
	}
}

void ModuleTransitions::Circle()
{
	if (sprite == nullptr)
		sprite = App->textures->Load("Assets/circle.png");

	float percentage = ((float)step / (float)transitionTime) * 2.0f;

	if (step * 2 >= transitionTime)
		percentage = 2.0f - percentage;

	float scale = 5.0f * percentage;

	App->renderer->DrawTexture(sprite, SCREEN_WIDTH / 2.0f - 150.0f * scale, SCREEN_HEIGHT / 2.0f - 150.0f * scale, scale);
}

void ModuleTransitions::Slash()
{
	if (sprite == nullptr)
		sprite = App->textures->Load("Assets/slash.png");

	float percentage = ((float)step / (float)transitionTime) * 200.0f;

	if (step * 2 >= transitionTime)
		percentage = 200 - percentage;

	int scale = 3;

	App->renderer->DrawTexture(sprite, ((SCREEN_WIDTH / 2) * ((100.0f - percentage) / 100.0f)) + ((SCREEN_WIDTH - (600 * scale)) / 2),
		(SCREEN_HEIGHT - (300 * scale)) / 2, scale);

	App->renderer->DrawTexture(sprite, ((SCREEN_WIDTH - (600 * scale)) / 2) - ((SCREEN_WIDTH / 2) * ((100.0f - percentage) / 100.0f)),
		(SCREEN_HEIGHT - (300 * scale)) / 2, scale, true);
}

void ModuleTransitions::Theatre()
{
	if (sprite == nullptr)
		sprite = App->textures->Load("Assets/semicircle.png");

	float percentage = ((float)step / (float)transitionTime) * 360.0f;

	int scale = 7;

	App->renderer->DrawTexture(sprite, ((SCREEN_WIDTH - (300 * scale)) / 2), SCREEN_HEIGHT, scale, false, NULL, 1.0f, percentage, 150 * scale, 0);
}

void ModuleTransitions::Dissolve()
{
	//If screenshot is made, load it
	if (App->renderer->screenshot) {
		sprite = App->textures->Load("Assets/screenshot.bmp");
	}

	//Call for screenshot
	if (sprite == nullptr) {
		App->renderer->pendingToScreenshot = true;
		return;
	}

	float percentage = ((float)step / (float)transitionTime) * 255.0f;

	SDL_SetTextureBlendMode(sprite, SDL_BLENDMODE_BLEND);
	SDL_SetTextureAlphaMod(sprite, 255.0f - percentage);

	App->renderer->DrawTexture(sprite, 0, 0);
}

void ModuleTransitions::Zoom()
{
	//If screenshot is made, load it
	if (App->renderer->screenshot) {
		sprite = App->textures->Load("Assets/screenshot.bmp");
	}

	//Call for screenshot
	if (sprite == nullptr) {
		App->renderer->pendingToScreenshot = true;
		return;
	}

	float percentage = ((float)step / (float)transitionTime) * 5.0f;

	App->renderer->DrawTexture(sprite, 0, 0, 1.0f + percentage);

}

//TODO 6: Defineix la funció de transició
void ModuleTransitions::Cut() {
	//If screenshot is made, load it
	if (App->renderer->screenshot) {
		sprite = App->textures->Load("Assets/screenshot.bmp");
	}

	//Call for screenshot
	if (sprite == nullptr) {
		App->renderer->pendingToScreenshot = true;
		return;
	}

	float percentage = ((float)step / (float)transitionTime) * ((float)SCREEN_HEIGHT / 2.0f);

	SDL_Rect top = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT / 2 };
	SDL_Rect bot = { 0, SCREEN_HEIGHT / 2, SCREEN_WIDTH, SCREEN_HEIGHT / 2 };
	App->renderer->DrawTexture(sprite, 0, -percentage, 1.0f, false, &top);
	App->renderer->DrawTexture(sprite, 0, SCREEN_HEIGHT / 2 + percentage, 1.0f, false, &bot);
}
//

