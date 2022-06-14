#include "ModuleParticles.h"

#include "App.h"
#include "Animation.h"
#include "Render.h"
#include "Scene.h"

#include "Textures.h"
#include "Player.h"
#include "Stages.h"
#include <time.h>

#include "SDL/include/SDL_timer.h"

ModuleParticles::ModuleParticles(App* application, bool start_enabled) : Module(application, start_enabled)
{
	name.Create("moduleparticles");
	//Particle
	SmokeParticle.PushBack({ 0,0, 27, 53 });
	SmokeParticle.PushBack({ 29, 0, 24, 53 });
	SmokeParticle.PushBack({ 56,0, 22, 53 });
	SmokeParticle.PushBack({ 83,0, 23, 43 });
	SmokeParticle.PushBack({ 56,0, 22, 53 });
	SmokeParticle.PushBack({ 29, 0, 24, 53 });
	SmokeParticle.loop = true;
	SmokeParticle.speed = 0.01f;

	FireParticle.PushBack({ 2,48, 12,18 });
	FireParticle.PushBack({ 18, 48, 12, 19 });
	FireParticle.PushBack({ 34,48, 12, 18 });
	FireParticle.PushBack({ 51,48, 12, 19 });
	FireParticle.loop = true;
	FireParticle.speed = 0.01f;

	ChickenParticle.PushBack({ 31,0, 14, 15 });
	ChickenParticle.PushBack({ 47,0, 14, 15 });
	ChickenParticle.PushBack({ 61,0, 16, 15 });
	ChickenParticle.PushBack({ 0,0, 15, 15 });
	ChickenParticle.PushBack({ 15,0, 15, 15 });
	ChickenParticle.PushBack({ 0,0, 15, 15 });
	ChickenParticle.PushBack({ 15,0, 15, 15 });
	ChickenParticle.PushBack({ 0,0, 15, 15 });
	ChickenParticle.PushBack({ 61,0, 16, 15 });
	ChickenParticle.PushBack({ 47,0, 14, 15 });
	ChickenParticle.PushBack({ 31,0, 14, 15 });
	ChickenParticle.PushBack({ 31,0, 14, 15 });
	ChickenParticle.PushBack({ 31,0, 14, 15 });
	ChickenParticle.PushBack({ 31,0, 14, 15 });
	ChickenParticle.PushBack({ 31,0, 14, 15 });
	ChickenParticle.loop = true;
	ChickenParticle.speed = 0.019f;

	BirdParticle.PushBack({ 2,3,23,22 });
	BirdParticle.PushBack({ 0,57,25,22 });
	BirdParticle.PushBack({ 27,57,25,22 });
	BirdParticle.PushBack({ 56,57,25,22 });
	BirdParticle.PushBack({ 27,57,25,22 });
	BirdParticle.PushBack({ 0,57,25,22 });
	BirdParticle.PushBack({ 2,3,23,22 });
	BirdParticle.PushBack({ 2,3,23,22 });
	BirdParticle.PushBack({ 2,3,23,22 });
	BirdParticle.PushBack({ 2,3,23,22 });
	BirdParticle.PushBack({ 2,3,23,22 });
	BirdParticle.PushBack({ 2,3,23,22 });
	BirdParticle.PushBack({ 2,3,23,22 });
	BirdParticle.PushBack({ 2,3,23,22 });
	BirdParticle.loop = true;
	BirdParticle.speed = 0.01f;

	BirdFParticleL.PushBack({ 0,27,27,25 });
	BirdFParticleL.PushBack({ 27,27,27,25 });
	BirdFParticleL.PushBack({ 54,27,27,25 });
	BirdFParticleL.PushBack({ 81,27,27,25 });
	BirdFParticleL.PushBack({108,27,27,25 });
	BirdFParticleL.PushBack({ 135,27,28,25 });
	BirdFParticleL.PushBack({ 163,27,27,25 });
	BirdFParticleL.PushBack({ 190,27,27,25 });
	BirdFParticleL.loop = true;
	BirdFParticleL.speed = 0.018f;

	BirdFParticleR.PushBack({ 190,115,27,25 });
	BirdFParticleR.PushBack({ 163,115,27,25 });
	BirdFParticleR.PushBack({ 136,115,28,25 });
	BirdFParticleR.PushBack({ 109,115,27,25 });
	BirdFParticleR.PushBack({ 82,115,27,25 });
	BirdFParticleR.PushBack({ 54,115,28,25 });
	BirdFParticleR.PushBack({ 27,115,27,25 });
	BirdFParticleR.PushBack({ 0,115,27,25 });
	BirdFParticleR.loop = true;
	BirdFParticleR.speed = 0.018f;
}

ModuleParticles::~ModuleParticles()
{

}

bool ModuleParticles::Start()
{
	SmokeTex = app->tex->Load("Assets/particles/smoke_particles.png");
	FireTex = app->tex->Load("Assets/particles/flames_particles.png");
	ChickenTex= app->tex->Load("Assets/particles/chicken_particles.png");
	BirdTex = app->tex->Load("Assets/particles/bird_particles.png");

	BirdPos.x = 2660;
	BirdPos.y = 0;

	return true;
}

bool ModuleParticles::Update(float dt)
{
	bool ret = true;
	srand(time(NULL));


	if (app->stages->actualStage == StageIndex::TOWN) {
		SmokeParticle.Update();
		FireParticle.Update();
		ChickenParticle.Update();
		BirdParticle.Update();
		BirdFParticleL.Update();
		BirdFParticleR.Update();
		if (app->input->GetKey(SDL_SCANCODE_M) == KEY_DOWN) {
			BirdWillSpawn = 1;
		}

		if (BirdcanSpawn == false) {
			BirdWillSpawn = rand() % 15;
		}		

		srand(time(NULL));

		if (BirdWillSpawn > 0 && BirdWillSpawn < 10 && BirdcanSpawn==false) {
			BirdcanSpawn = true;
			BirdSpawn = rand() % 1440;			
			BirdPos.y = BirdSpawn;
		}
	}
	
	return ret;
}

bool ModuleParticles::PostUpdate()
{
	if (app->stages->actualStage == StageIndex::TOWN) {
		//Iterating all particle array and drawing any active particles
		app->render->DrawTexture(SmokeTex, 388, 1010, &SmokeParticle.GetCurrentFrame());
		app->render->DrawTexture(SmokeTex, 355, 1496, &SmokeParticle.GetCurrentFrame());
		app->render->DrawTexture(SmokeTex, 862, 1496, &SmokeParticle.GetCurrentFrame());
		app->render->DrawTexture(SmokeTex, 805, 1020, &SmokeParticle.GetCurrentFrame());
		app->render->DrawTexture(FireTex, 1290, 510, &FireParticle.GetCurrentFrame());
		app->render->DrawTexture(ChickenTex, 11, 910, &ChickenParticle.GetCurrentFrame());
		app->render->DrawTexture(BirdTex, 1460, 1560, &BirdParticle.GetCurrentFrame());
		app->render->DrawTexture(BirdTex, 620, 1300, &BirdParticle.GetCurrentFrame());
		if (BirdcanSpawn == true) {
			BirdPos.x -= 4;
			app->render->DrawTexture(BirdTex, BirdPos.x + 50, BirdPos.y - 1500, &BirdFParticleL.GetCurrentFrame());
			app->render->DrawTexture(BirdTex, BirdPos.x+100, BirdPos.y-1000, &BirdFParticleL.GetCurrentFrame());
			app->render->DrawTexture(BirdTex, BirdPos.x+50, BirdPos.y-500, &BirdFParticleL.GetCurrentFrame());
			app->render->DrawTexture(BirdTex, BirdPos.x, BirdPos.y, &BirdFParticleL.GetCurrentFrame());
			app->render->DrawTexture(BirdTex, BirdPos.x+50, BirdPos.y +500, &BirdFParticleL.GetCurrentFrame());
			app->render->DrawTexture(BirdTex, BirdPos.x+100, BirdPos.y + 1000, &BirdFParticleL.GetCurrentFrame());

			app->render->DrawTexture(BirdTex, -BirdPos.x - 50 + 2560, BirdPos.y - 1700, &BirdFParticleR.GetCurrentFrame());
			app->render->DrawTexture(BirdTex, -BirdPos.x - 100 + 2560, BirdPos.y - 1200, &BirdFParticleR.GetCurrentFrame());
			app->render->DrawTexture(BirdTex, -BirdPos.x - 50 + 2560, BirdPos.y - 700, &BirdFParticleR.GetCurrentFrame());
			app->render->DrawTexture(BirdTex, -BirdPos.x+2560, BirdPos.y-200, &BirdFParticleR.GetCurrentFrame());
			app->render->DrawTexture(BirdTex, -BirdPos.x - 50 + 2560, BirdPos.y + 700, &BirdFParticleR.GetCurrentFrame());
			app->render->DrawTexture(BirdTex, -BirdPos.x - 100 + 2560, BirdPos.y + 1200, &BirdFParticleR.GetCurrentFrame());

			/*LOG("POSICION X: %d", BirdPos.x);
			LOG("ALTURA : %d", BirdPos.y);*/
			if (BirdPos.x <= -50) {
				BirdcanSpawn = false;
				BirdPos.x = 2560;
			}			
		}
	}
			
	return true;
}

bool ModuleParticles::CleanUp()
{
	LOG("Unloading particles");

	// Delete all remaining active particles on application exit 
	app->tex->UnLoad(SmokeTex);
	app->tex->UnLoad(FireTex);
	app->tex->UnLoad(ChickenTex);
	app->tex->UnLoad(BirdTex);
	
	return true;
}