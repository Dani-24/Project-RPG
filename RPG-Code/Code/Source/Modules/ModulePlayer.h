#ifndef __MODULEPLAYER_H__
#define __MODULEPLAYER_H__

#include "Module.h"
#include "Animation.h"

struct SDL_Texture;
struct SDL_Surface;
struct Collider;

class ModulePlayer :public Module {
public:
	ModulePlayer(App* application, bool start_enabled = true);

	~ModulePlayer();

	//// Called before render is available
	//bool Awake(pugi::xml_node&);

	//// Called before the first frame
	//bool Start();

	//// Called before all Updates
	//bool PreUpdate();

	//// Called each loop iteration
	//bool Update(float dt);

	//// Called before all Updates
	//bool PostUpdate();

	//// Called before quitting
	//bool CleanUp();

	// Load / Save
	//bool LoadState(pugi::xml_node&);
	//bool SaveState(pugi::xml_node&) const;

private:
	//cargar textura del jugador
	SDL_Texture* texture = nullptr;

	//player animations
	Animation* currentAnimation = nullptr;
	Animation 
		walkAnimUp,
		walkAnimDown,
		walkAnimR,
		walkAnimL;
};
#endif