#include "ModuleParticles.h"

#include "App.h"
#include "Animation.h"
#include "Render.h"
#include "Scene.h"

#include "Textures.h"
#include "Player.h"
#include "Stages.h"

#include "SDL/include/SDL_timer.h"

ModuleParticles::ModuleParticles(App* application, bool start_enabled) : Module(application, start_enabled)
{
	name.Create("moduleparticles");
	//Particle
	SmokeParticle.PushBack({ 0,0, 27, 53 });
	SmokeParticle.PushBack({ 29, 0, 24, 53 });
	SmokeParticle.PushBack({ 56,0, 22, 53 });
	SmokeParticle.PushBack({ 83,0, 23, 43 });
	//SmokeParticle.PushBack({ 58,0, 20, 53 });
	//SmokeParticle.PushBack({ 31, 0, 22, 53 });
	SmokeParticle.loop = true;
	SmokeParticle.speed = 0.008f;

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

	BirdFParticle.PushBack({ 0,27,27,25 });
	BirdFParticle.PushBack({ 27,27,27,25 });
	BirdFParticle.PushBack({ 54,27,27,25 });
	BirdFParticle.PushBack({ 81,27,27,25 });
	BirdFParticle.PushBack({108,27,27,25 });
	BirdFParticle.PushBack({ 135,27,27,25 });
	BirdFParticle.PushBack({ 162,27,27,25 });
	BirdFParticle.PushBack({ 189,27,27,25 });
	BirdFParticle.loop = true;
	BirdFParticle.speed = 0.01f;
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
	return true;
}



bool ModuleParticles::Update(float dt)
{
	bool ret = true;
	SmokeParticle.Update();
	FireParticle.Update();
	ChickenParticle.Update();
	BirdParticle.Update();
	BirdFParticle.Update();
	return ret;
}

bool ModuleParticles::PostUpdate()
{
	if (app->stages->actualStage == StageIndex::TOWN) {
		//Iterating all particle array and drawing any active particles
		app->render->DrawTexture(SmokeTex, 388, 1010, &SmokeParticle.GetCurrentFrame());
		app->render->DrawTexture(SmokeTex, 355, 1496, &SmokeParticle.GetCurrentFrame());
		app->render->DrawTexture(SmokeTex, 862, 1496, &SmokeParticle.GetCurrentFrame());
		app->render->DrawTexture(FireTex, 1290, 510, &FireParticle.GetCurrentFrame());
		app->render->DrawTexture(ChickenTex, 11, 910, &ChickenParticle.GetCurrentFrame());
		app->render->DrawTexture(BirdTex, 1460, 1560, &BirdParticle.GetCurrentFrame());
		app->render->DrawTexture(BirdTex, 1100, 1560, &BirdFParticle.GetCurrentFrame());
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

//void ModuleParticles::AddParticle(const Animation& particle, int x, int y, int type/*, Collider::Type colliderType*/, uint delay)
//{
//	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
//	{
//		//Finding an empty slot for a new particle
//		if (particles[i] == nullptr)
//		{
//			Animation* p = new Animation(particle);
//
//			p->type = type;
//			p->frameCount = -(int)delay;			// We start the frameCount as the negative delay
//			p->position.x = x;						// so when frameCount reaches 0 the particle will be activated
//			p->position.y = y;
//
//			//Adding the particle's collider
//
//			//if (colliderType != Collider::Type::NONE && p->type == 1)
//			//	p->collider = app->coll->AddCollider({ 0, 0, 18, 10 }, colliderType, this);
//			///*if (colliderType == Collider::Type::PLAYERATTACK && p->type == 1)
//			//	p->collider = app->coll->AddCollider({app->player->position.x,app->player->position.y, 8,8 }, colliderType, this);*/
//
//			//else {
//			//	p->collider = app->coll->AddCollider(p->anim.GetCurrentFrame(), colliderType, this);
//			//}
//
//			particles[i] = p;
//			break;
//		}
//	}
//}