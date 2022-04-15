#ifndef _ENEMYMOVEMENT_H_
#define _ENEMYMOVEMENT_H_



#include "Module.h"
#include "Animation.h"

struct SDL_Texture;
struct SDL_Surface;
struct Collider;

class EnemyMovement :public Module
{
public:
	EnemyMovement(App* application, bool start_enabled = true);

	~EnemyMovement();

	// Called before render is available
	bool Awake(pugi::xml_node&);

	// Called before the first frame
	bool Start();

	// Called before all Updates
	bool PreUpdate();

	// Called each loop iteration
	bool Update(float dt);

	// Called before all Updates
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();



private:

	iPoint position;


	//charge enemy textures
	SDL_Texture* EnemyTex = nullptr;


	//enemy animations
	Animation* currentAnimationEnemy = nullptr;
	Animation
		walkAnimR,
		walkAnimL,
		idleAnim;

};


#endif // _ENEMYMOVEMENT_H_