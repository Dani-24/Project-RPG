#ifndef __MODULE_PARTICLES_H__
#define __MODULE_PARTICLES_H__

#include "Module.h"
#include "Collider.h"
#include "Animation.h"
#include "App.h"

//#define MAX_ACTIVE_PARTICLES 100

struct SDL_Texture;

class ModuleParticles : public Module
{
public:
	// Constructor
	// Initializes all the particles in the array to nullptr
	ModuleParticles(App* application, bool start_enabled = true);

	//Destructor
	~ModuleParticles();

	// Called when the module is activated
	// Loads the necessary textures for the particles
	bool Start();

	// Called at the middle of the application loop
	// Iterates all the particles and calls its Update()
	// Removes any "dead" particles
	bool Update(float dt);

	// Called at the end of the application loop
	// Iterates all the particles and draws them
	bool PostUpdate();

	// Called on application exit
	// Destroys all active particles left in the array
	bool CleanUp();

	// Creates a new particle and adds it to the array
	// Param particle	- A template particle from which the new particle will be created
	// Param x, y		- Position x,y in the screen (upper left axis)
	// Param delay		- Delay time from the moment the function is called until the particle is displayed in screen

	
private:
	// Particles spritesheet loaded into an SDL Texture
	SDL_Texture* SmokeTex = nullptr;
	SDL_Texture* FireTex = nullptr;

	//Template particle
	Animation SmokeParticle,
		FireParticle;
	
};

#endif // !__MODULEPARTICLES_H__