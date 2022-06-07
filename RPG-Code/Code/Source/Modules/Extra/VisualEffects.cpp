#include "VisualEffects.h"

#include "Render.h"
#include "Textures.h"
#include "Window.h"
#include "Audio.h"
#include "Camera.h"
#include "ModuleQFonts.h"
#include "FadeToBlack.h"
#include "Battle.h"

VisualEffects::VisualEffects(App* application, bool start_enabled) : Module(application, start_enabled)
{
	currentAnim = &loadingAnim;

	int loadX = 64, loadY = 64;

	for (int j = 0; j < 12; j++) {
		for (int i = 0; i < 11; i++ ) {
			currentAnim->PushBack({ i * loadX, j * loadY, loadX, loadY });
		}
	}
	
	currentAnim->loop = false;
	currentAnim->speed = 0.03f;

	currentAnim = &questCAnim;

	for (int i = 0; i < 7; i++) {
		for (int j = 0; j < 6; j++) {
			currentAnim->PushBack({ j * ScreenX, i * ScreenY, ScreenX, ScreenY });

			if (i == 3 && j == 0) {
				for (int rep = 0; rep < 30; rep++) {
					currentAnim->PushBack({ j * ScreenX, i * ScreenY, ScreenX, ScreenY });
				}
			}
		}
	}

	currentAnim->loop = false;
	currentAnim->speed = 0.03f;

	currentAnim = &trans1Anim;

	for (int i = 0; i < 12; i++) {
		for (int j = 0; j < 6; j++) {
			currentAnim->PushBack({ j * ScreenX, i * ScreenY, ScreenX, ScreenY });
		}
	}

	currentAnim->loop = false;
	currentAnim->speed = 0.05f;

	currentAnim = &trans2Anim;

	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 5; j++) {
			currentAnim->PushBack({ j * ScreenX, i * ScreenY, ScreenX, ScreenY });
		}
	}

	currentAnim->loop = false;
	currentAnim->speed = 0.03f;

	currentAnim = nullptr;
}

VisualEffects::~VisualEffects()
{

}

bool VisualEffects::Start()
{
	LOG("Starting Visual effects");

	questFX = app->audio->LoadFx("Assets/audio/sfx/fx_complete.wav");
	trans1FX = app->audio->LoadFx("Assets/audio/sfx/fx_trans1.wav");
	trans2FX = app->audio->LoadFx("Assets/audio/sfx/fx_trans2.wav");

	loadingTex = app->tex->Load("Assets/textures/visualEffects/loading.png");
	questCTex = app->tex->Load("Assets/textures/visualEffects/complete.png");
	trans1Tex = app->tex->Load("Assets/textures/visualEffects/trans1.png");
	trans2Tex = app->tex->Load("Assets/textures/visualEffects/trans2.png");

	return true;
}

bool VisualEffects::Update(float dt)
{
	
	if (currentEffect != Effects::NONE) {
		currentAnim->Update();

		if (currentAnim->HasFinished()) {

			if (currentEffect == Effects::TRANSITION1 || currentEffect == Effects::TRANSITION2) {
				app->battle->Enable();
			}

			currentAnim->Reset();
			currentEffect = Effects::NONE;
		}
	}
	return true;
}

bool VisualEffects::PostUpdate()
{
	int x = -app->camera->GetPos().x / 2,
		y = -app->camera->GetPos().y / 2;

	if (currentEffect != Effects::NONE) {
		switch (currentEffect)
		{
		case Effects::LOADING:
			if (loadingTex != nullptr) {
				app->render->DrawTexture(loadingTex, x + 580, y + 300, &loadingAnim.GetCurrentFrame());

				if (!app->fade->fading) {
					app->font->DrawText("Game Loaded", -app->camera->GetPos().x / app->win->GetScale() + app->win->GetWidth() / 2 - 175,
						-app->camera->GetPos().y / app->win->GetScale() + app->win->GetHeight() / 2 - 40);
				}
			}
			break;
		case Effects::QUESTCOMPLETED:

			if (questCTex != nullptr) {
				app->render->DrawTexture(questCTex, x, y, &questCAnim.GetCurrentFrame());
			}

			break;
		case Effects::TRANSITION1:

			if (trans1Tex != nullptr) {
				app->render->DrawTexture(trans1Tex, x, y, &trans1Anim.GetCurrentFrame());
			}
			break;
		case Effects::TRANSITION2:

			if (trans2Tex != nullptr) {
				app->render->DrawTexture(trans2Tex, x, y, &trans2Anim.GetCurrentFrame());
			}

			break;
		}
	}

	return true;
}

bool VisualEffects::CleanUp()
{
	LOG("Unloading visual effects");

	app->tex->UnLoad(trans1Tex);
	app->tex->UnLoad(trans2Tex);
	app->tex->UnLoad(questCTex);
	app->tex->UnLoad(loadingTex);

	return true;
}

void VisualEffects::DisplayEffect(Effects effect) {
	if (currentEffect == Effects::NONE) {
		currentEffect = effect;

		switch (currentEffect)
		{
		case Effects::LOADING:
			currentAnim = &loadingAnim;
			break;
		case Effects::QUESTCOMPLETED:
			currentAnim = &questCAnim;
			app->audio->PlayFx(questFX);
			break;
		case Effects::TRANSITION1:
			currentAnim = &trans1Anim;
			app->audio->PlayFx(trans1FX);
			break;
		case Effects::TRANSITION2:
			currentAnim = &trans2Anim;
			app->audio->PlayFx(trans2FX);
			break;
		}
	}
}