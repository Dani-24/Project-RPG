#include "ModuleParticles.h"

#include "App.h"
#include "Particle.h"

#include "Animation.h"
#include "Render.h"
#include "Collisions.h"
#include "textures.h"
#include "Player.h"
//#include "ModuleEnemies.h"

#include "SDL/include/SDL_timer.h"

ModuleParticles::ModuleParticles(App* application, bool start_enabled) : Module(application, start_enabled)
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
		particles[i] = nullptr;

}

ModuleParticles::~ModuleParticles()
{

}

bool ModuleParticles::Start()
{
	SmokeTex = app->tex->Load("Assets/particles/smoke_particles.png");

	//Particle
	SmokeParticle.anim.PushBack({ 0,0, 27, 53 });
	SmokeParticle.anim.PushBack({ 31, 0, 22, 53 });
	SmokeParticle.anim.PushBack({ 58,0, 20, 53 });
	SmokeParticle.anim.PushBack({ 85,0, 21, 43 });
	SmokeParticle.anim.loop = true;
	SmokeParticle.anim.speed = 0.5f;
	SmokeParticle.lifetime = 300;

	FireTex = app->tex->Load("Assets/particles/flames_particles.png");

	FireParticle.anim.PushBack({ 2,48, 12,18 });
	FireParticle.anim.PushBack({ 18, 48, 12, 19 });
	FireParticle.anim.PushBack({ 34,48, 12, 18 });
	FireParticle.anim.PushBack({ 51,48, 12, 19 });
	FireParticle.anim.loop = true;
	FireParticle.anim.speed = 0.5f;
	FireParticle.lifetime = 300;
	
	return true;
}

bool ModuleParticles::CleanUp()
{
	LOG("Unloading particles");

	// Delete all remaining active particles on application exit 
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if (particles[i] != nullptr)
		{
			delete particles[i];
			particles[i] = nullptr;
		}
	}

	return true;
}

void ModuleParticles::OnCollision(Collider* c1, Collider* c2)
{
	//for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	//{
	//	/*Always destroy particles that collide*/
	//	if (particles[i] != nullptr && (particles[i]->collider == c1 || particles[i]->collider == c1))
	//	{
	//		/*if ((c1->type == Collider::Type::PLAYERATTACK && c2->type == Collider::Type::ENEMYBOO || c1->type == Collider::Type::ENEMYBOO && c2->type == Collider::Type::PLAYERATTACK) && app->enemies->BooLive == 1)
	//		{
	//			app->enemies->BooLive = 0;
	//			app->player->score += 400;
	//		}*/

	//		

	//		/*if (particles[i]->type == 1) {
	//			AddParticle(shuriken_explosion, particles[i]->position.x, particles[i]->position.y, particles[i]->type);
	//			particles[i]->type == 0;
	//		}

	//		if (particles[i]->type == 2) {
	//			AddParticle(knife_explosion, particles[i]->position.x, particles[i]->position.y, particles[i]->type);
	//			particles[i]->type == 0;
	//		}*/


	//		delete particles[i];
	//		particles[i] = nullptr;
	//	}
	//}
}

bool ModuleParticles::Update(float dt)
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		Particle* particle = particles[i];

		if (particle == nullptr)	continue;

		// Call particle Update. If it has reached its lifetime, destroy it
		if (particle->Update() == false)
		{
			delete particle;
			particles[i] = nullptr;
		}
	}

	return true;
}

bool ModuleParticles::PostUpdate()
{
	//Iterating all particle array and drawing any active particles
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		Particle* particle = particles[i];

		if (particle != nullptr && particle->isAlive)
		{
			if (particle->type == 1)app->render->DrawTexture(SmokeTex, particle->position.x, particle->position.y, &(particle->anim.GetCurrentFrame()));
			if (particle->type == 2)app->render->DrawTexture(FireTex, particle->position.x, particle->position.y, &(particle->anim.GetCurrentFrame()));
			
		}
	}

	return true;
}

void ModuleParticles::AddParticle(const Particle& particle, int x, int y, int type/*, Collider::Type colliderType*/, uint delay)
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		//Finding an empty slot for a new particle
		if (particles[i] == nullptr)
		{
			Particle* p = new Particle(particle);

			p->type = type;
			p->frameCount = -(int)delay;			// We start the frameCount as the negative delay
			p->position.x = x;						// so when frameCount reaches 0 the particle will be activated
			p->position.y = y;

			//Adding the particle's collider

			//if (colliderType != Collider::Type::NONE && p->type == 1)
			//	p->collider = app->coll->AddCollider({ 0, 0, 18, 10 }, colliderType, this);
			///*if (colliderType == Collider::Type::PLAYERATTACK && p->type == 1)
			//	p->collider = app->coll->AddCollider({app->player->position.x,app->player->position.y, 8,8 }, colliderType, this);*/

			//else {
			//	p->collider = app->coll->AddCollider(p->anim.GetCurrentFrame(), colliderType, this);
			//}

			particles[i] = p;
			break;
		}
	}
}