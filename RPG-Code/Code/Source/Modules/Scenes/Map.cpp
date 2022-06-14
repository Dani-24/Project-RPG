#include "App.h"
#include "Render.h"
#include "Textures.h"
#include "Map.h"
#include "Stages.h"
#include "Player.h"
#include "Defs.h"
#include "Log.h"

#include "Entity.h"
#include "EntityManager.h"

#include <math.h>

using namespace  std;

Map::Map(App* application, bool start_enabled) : Module(application, start_enabled)
{
	name.Create("map");
	
	mapLoaded = false;

	LoadAnimatedTiles();
}

void Map::LoadAnimatedTiles() {
	
	float animSpeed = 0.012f;

	// === Animated Water ===

	// Rock dark water
	Animation* anim = &rockDarkWtopL;
	{
		anim->PushBack({ 5 * TILE_SIZE, 0 * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->PushBack({ 13 * TILE_SIZE, 0 * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->PushBack({ 21 * TILE_SIZE, 0 * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->PushBack({ 29 * TILE_SIZE, 0 * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->PushBack({ 37 * TILE_SIZE, 0 * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->PushBack({ 45 * TILE_SIZE, 0 * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->PushBack({ 53 * TILE_SIZE, 0 * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->PushBack({ 61 * TILE_SIZE, 0 * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->speed = animSpeed;
		anim->loop = true;

		anim = &rockDarkWleft;

		anim->PushBack({ 5 * TILE_SIZE, 1 * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->PushBack({ 13 * TILE_SIZE, 1 * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->PushBack({ 21 * TILE_SIZE, 1 * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->PushBack({ 29 * TILE_SIZE, 1 * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->PushBack({ 37 * TILE_SIZE, 1 * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->PushBack({ 45 * TILE_SIZE, 1 * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->PushBack({ 53 * TILE_SIZE, 1 * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->PushBack({ 61 * TILE_SIZE, 1 * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->speed = animSpeed;
		anim->loop = true;

		anim = &rockDarkWdownL;

		anim->PushBack({ 5 * TILE_SIZE, 2 * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->PushBack({ 13 * TILE_SIZE, 2 * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->PushBack({ 21 * TILE_SIZE, 2 * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->PushBack({ 29 * TILE_SIZE, 2 * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->PushBack({ 37 * TILE_SIZE, 2 * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->PushBack({ 45 * TILE_SIZE, 2 * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->PushBack({ 53 * TILE_SIZE, 2 * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->PushBack({ 61 * TILE_SIZE, 2 * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->speed = animSpeed;
		anim->loop = true;

		anim = &rockDarkWtop;

		anim->PushBack({ 6 * TILE_SIZE, 0 * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->PushBack({ 14 * TILE_SIZE, 0 * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->PushBack({ 22 * TILE_SIZE, 0 * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->PushBack({ 30 * TILE_SIZE, 0 * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->PushBack({ 38 * TILE_SIZE, 0 * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->PushBack({ 46 * TILE_SIZE, 0 * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->PushBack({ 54 * TILE_SIZE, 0 * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->PushBack({ 62 * TILE_SIZE, 0 * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->speed = animSpeed;
		anim->loop = true;

		anim = &rockDarkWmid;

		anim->PushBack({ 6 * TILE_SIZE, 1 * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->PushBack({ 14 * TILE_SIZE, 1 * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->PushBack({ 22 * TILE_SIZE, 1 * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->PushBack({ 30 * TILE_SIZE, 1 * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->PushBack({ 38 * TILE_SIZE, 1 * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->PushBack({ 46 * TILE_SIZE, 1 * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->PushBack({ 54 * TILE_SIZE, 1 * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->PushBack({ 62 * TILE_SIZE, 1 * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->speed = animSpeed;
		anim->loop = true;

		anim = &rockDarkWdown;

		anim->PushBack({ 6 * TILE_SIZE, 2 * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->PushBack({ 14 * TILE_SIZE, 2 * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->PushBack({ 22 * TILE_SIZE, 2 * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->PushBack({ 30 * TILE_SIZE, 2 * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->PushBack({ 38 * TILE_SIZE, 2 * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->PushBack({ 46 * TILE_SIZE, 2 * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->PushBack({ 54 * TILE_SIZE, 2 * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->PushBack({ 62 * TILE_SIZE, 2 * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->speed = animSpeed;
		anim->loop = true;

		anim = &rockDarkWtopR;

		anim->PushBack({ 7 * TILE_SIZE, 0 * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->PushBack({ 15 * TILE_SIZE, 0 * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->PushBack({ 23 * TILE_SIZE, 0 * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->PushBack({ 31 * TILE_SIZE, 0 * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->PushBack({ 39 * TILE_SIZE, 0 * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->PushBack({ 47 * TILE_SIZE, 0 * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->PushBack({ 55 * TILE_SIZE, 0 * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->PushBack({ 63 * TILE_SIZE, 0 * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->speed = animSpeed;
		anim->loop = true;

		anim = &rockDarkWright;

		anim->PushBack({ 7 * TILE_SIZE, 1 * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->PushBack({ 15 * TILE_SIZE, 1 * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->PushBack({ 23 * TILE_SIZE, 1 * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->PushBack({ 31 * TILE_SIZE, 1 * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->PushBack({ 39 * TILE_SIZE, 1 * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->PushBack({ 47 * TILE_SIZE, 1 * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->PushBack({ 55 * TILE_SIZE, 1 * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->PushBack({ 63 * TILE_SIZE, 1 * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->speed = animSpeed;
		anim->loop = true;

		anim = &rockDarkWdownR;

		anim->PushBack({ 7 * TILE_SIZE, 2 * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->PushBack({ 15 * TILE_SIZE, 2 * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->PushBack({ 23 * TILE_SIZE, 2 * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->PushBack({ 31 * TILE_SIZE, 2 * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->PushBack({ 39 * TILE_SIZE, 2 * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->PushBack({ 47 * TILE_SIZE, 2 * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->PushBack({ 55 * TILE_SIZE, 2 * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->PushBack({ 63 * TILE_SIZE, 2 * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->speed = animSpeed;
		anim->loop = true;
	}

	//Clean rock water
	{
	int Y = 6;

		anim = &rockCleanWtopL;

		anim->PushBack({ 5 * TILE_SIZE, Y * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->PushBack({ 13 * TILE_SIZE, Y * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->PushBack({ 21 * TILE_SIZE, Y * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->PushBack({ 29 * TILE_SIZE, Y * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->PushBack({ 37 * TILE_SIZE, Y * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->PushBack({ 45 * TILE_SIZE, Y * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->PushBack({ 53 * TILE_SIZE, Y * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->PushBack({ 61 * TILE_SIZE, Y * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->speed = animSpeed;
		anim->loop = true;

		anim = &rockCleanWleft;

		anim->PushBack({ 5 * TILE_SIZE, (Y + 1) * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->PushBack({ 13 * TILE_SIZE, (Y + 1) * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->PushBack({ 21 * TILE_SIZE, (Y + 1) * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->PushBack({ 29 * TILE_SIZE, (Y + 1) * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->PushBack({ 37 * TILE_SIZE, (Y + 1) * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->PushBack({ 45 * TILE_SIZE, (Y + 1) * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->PushBack({ 53 * TILE_SIZE, (Y + 1) * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->PushBack({ 61 * TILE_SIZE, (Y + 1) * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->speed = animSpeed;
		anim->loop = true;

		anim = &rockCleanWdownL;

		anim->PushBack({ 5 * TILE_SIZE, (Y + 2) * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->PushBack({ 13 * TILE_SIZE, (Y + 2) * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->PushBack({ 21 * TILE_SIZE, (Y + 2) * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->PushBack({ 29 * TILE_SIZE, (Y + 2) * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->PushBack({ 37 * TILE_SIZE, (Y + 2) * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->PushBack({ 45 * TILE_SIZE, (Y + 2) * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->PushBack({ 53 * TILE_SIZE, (Y + 2) * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->PushBack({ 61 * TILE_SIZE, (Y + 2) * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->speed = animSpeed;
		anim->loop = true;

		anim = &rockCleanWtop;

		anim->PushBack({ 6 * TILE_SIZE, Y * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->PushBack({ 14 * TILE_SIZE, Y * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->PushBack({ 22 * TILE_SIZE, Y * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->PushBack({ 30 * TILE_SIZE, Y * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->PushBack({ 38 * TILE_SIZE, Y * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->PushBack({ 46 * TILE_SIZE, Y * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->PushBack({ 54 * TILE_SIZE, Y * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->PushBack({ 62 * TILE_SIZE, Y * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->speed = animSpeed;
		anim->loop = true;

		anim = &rockCleanWmid;

		anim->PushBack({ 6 * TILE_SIZE, (Y + 1) * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->PushBack({ 14 * TILE_SIZE, (Y + 1) * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->PushBack({ 22 * TILE_SIZE, (Y + 1) * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->PushBack({ 30 * TILE_SIZE, (Y + 1) * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->PushBack({ 38 * TILE_SIZE, (Y + 1) * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->PushBack({ 46 * TILE_SIZE, (Y + 1) * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->PushBack({ 54 * TILE_SIZE, (Y + 1) * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->PushBack({ 62 * TILE_SIZE, (Y + 1) * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->speed = animSpeed;
		anim->loop = true;

		anim = &rockCleanWdown;

		anim->PushBack({ 6 * TILE_SIZE, (Y + 2) * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->PushBack({ 14 * TILE_SIZE, (Y + 2) * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->PushBack({ 22 * TILE_SIZE, (Y + 2) * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->PushBack({ 30 * TILE_SIZE, (Y + 2) * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->PushBack({ 38 * TILE_SIZE, (Y + 2) * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->PushBack({ 46 * TILE_SIZE, (Y + 2) * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->PushBack({ 54 * TILE_SIZE, (Y + 2) * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->PushBack({ 62 * TILE_SIZE, (Y + 2) * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->speed = animSpeed;
		anim->loop = true;

		anim = &rockCleanWtopR;

		anim->PushBack({ 7 * TILE_SIZE, Y * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->PushBack({ 15 * TILE_SIZE, Y * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->PushBack({ 23 * TILE_SIZE, Y * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->PushBack({ 31 * TILE_SIZE, Y * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->PushBack({ 39 * TILE_SIZE, Y * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->PushBack({ 47 * TILE_SIZE, Y * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->PushBack({ 55 * TILE_SIZE, Y * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->PushBack({ 63 * TILE_SIZE, Y * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->speed = animSpeed;
		anim->loop = true;

		anim = &rockCleanWright;

		anim->PushBack({ 7 * TILE_SIZE, (Y + 1) * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->PushBack({ 15 * TILE_SIZE, (Y + 1) * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->PushBack({ 23 * TILE_SIZE, (Y + 1) * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->PushBack({ 31 * TILE_SIZE, (Y + 1) * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->PushBack({ 39 * TILE_SIZE, (Y + 1) * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->PushBack({ 47 * TILE_SIZE, (Y + 1) * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->PushBack({ 55 * TILE_SIZE, (Y + 1) * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->PushBack({ 63 * TILE_SIZE, (Y + 1) * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->speed = animSpeed;
		anim->loop = true;

		anim = &rockCleanWdownR;

		anim->PushBack({ 7 * TILE_SIZE, (Y + 2) * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->PushBack({ 15 * TILE_SIZE, (Y + 2) * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->PushBack({ 23 * TILE_SIZE, (Y + 2) * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->PushBack({ 31 * TILE_SIZE, (Y + 2) * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->PushBack({ 39 * TILE_SIZE, (Y + 2) * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->PushBack({ 47 * TILE_SIZE, (Y + 2) * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->PushBack({ 55 * TILE_SIZE, (Y + 2) * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->PushBack({ 63 * TILE_SIZE, (Y + 2) * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->speed = animSpeed;
		anim->loop = true;

		anim = &rockInterTopL;

		anim->PushBack({ 4 * TILE_SIZE, (Y + 3) * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->PushBack({ 12 * TILE_SIZE, (Y + 3) * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->PushBack({ 20 * TILE_SIZE, (Y + 3) * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->PushBack({ 28 * TILE_SIZE, (Y + 3) * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->PushBack({ 36 * TILE_SIZE, (Y + 3) * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->PushBack({ 44 * TILE_SIZE, (Y + 3) * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->PushBack({ 52 * TILE_SIZE, (Y + 3) * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->PushBack({ 60 * TILE_SIZE, (Y + 3) * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->speed = animSpeed;
		anim->loop = true;

		anim = &rockInterDownL;

		anim->PushBack({ 4 * TILE_SIZE, (Y + 4) * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->PushBack({ 12 * TILE_SIZE, (Y + 4) * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->PushBack({ 20 * TILE_SIZE, (Y + 4) * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->PushBack({ 28 * TILE_SIZE, (Y + 4) * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->PushBack({ 36 * TILE_SIZE, (Y + 4) * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->PushBack({ 44 * TILE_SIZE, (Y + 4) * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->PushBack({ 52 * TILE_SIZE, (Y + 4) * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->PushBack({ 60 * TILE_SIZE, (Y + 4) * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->speed = animSpeed;
		anim->loop = true;

		anim = &rockInterTopR;

		anim->PushBack({ 5 * TILE_SIZE, (Y + 3) * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->PushBack({ 13 * TILE_SIZE, (Y + 3) * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->PushBack({ 21 * TILE_SIZE, (Y + 3) * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->PushBack({ 29 * TILE_SIZE, (Y + 3) * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->PushBack({ 37 * TILE_SIZE, (Y + 3) * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->PushBack({ 45 * TILE_SIZE, (Y + 3) * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->PushBack({ 53 * TILE_SIZE, (Y + 3) * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->PushBack({ 61 * TILE_SIZE, (Y + 3) * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->speed = animSpeed;
		anim->loop = true;

		anim = &rockInterDownR;

		anim->PushBack({ 5 * TILE_SIZE, (Y + 4) * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->PushBack({ 13 * TILE_SIZE, (Y + 4) * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->PushBack({ 21 * TILE_SIZE, (Y + 4) * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->PushBack({ 29 * TILE_SIZE, (Y + 4) * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->PushBack({ 37 * TILE_SIZE, (Y + 4) * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->PushBack({ 45 * TILE_SIZE, (Y + 4) * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->PushBack({ 53 * TILE_SIZE, (Y + 4) * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->PushBack({ 61 * TILE_SIZE, (Y + 4) * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->speed = animSpeed;
		anim->loop = true;
	}
		// clean water
	{
		int Y = 30;

		anim = &cleanWtopL;

		anim->PushBack({ 5 * TILE_SIZE, Y * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->PushBack({ 13 * TILE_SIZE, Y * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->PushBack({ 21 * TILE_SIZE, Y * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->PushBack({ 29 * TILE_SIZE, Y * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->PushBack({ 37 * TILE_SIZE, Y * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->PushBack({ 45 * TILE_SIZE, Y * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->PushBack({ 53 * TILE_SIZE, Y * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->PushBack({ 61 * TILE_SIZE, Y * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->speed = animSpeed;
		anim->loop = true;

		anim = &cleanWleft;

		anim->PushBack({ 5 * TILE_SIZE, (Y + 1) * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->PushBack({ 13 * TILE_SIZE, (Y + 1) * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->PushBack({ 21 * TILE_SIZE, (Y + 1) * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->PushBack({ 29 * TILE_SIZE, (Y + 1) * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->PushBack({ 37 * TILE_SIZE, (Y + 1) * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->PushBack({ 45 * TILE_SIZE, (Y + 1) * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->PushBack({ 53 * TILE_SIZE, (Y + 1) * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->PushBack({ 61 * TILE_SIZE, (Y + 1) * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->speed = animSpeed;
		anim->loop = true;

		anim = &cleanWdownL;

		anim->PushBack({ 5 * TILE_SIZE, (Y + 2) * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->PushBack({ 13 * TILE_SIZE, (Y + 2) * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->PushBack({ 21 * TILE_SIZE, (Y + 2) * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->PushBack({ 29 * TILE_SIZE, (Y + 2) * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->PushBack({ 37 * TILE_SIZE, (Y + 2) * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->PushBack({ 45 * TILE_SIZE, (Y + 2) * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->PushBack({ 53 * TILE_SIZE, (Y + 2) * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->PushBack({ 61 * TILE_SIZE, (Y + 2) * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->speed = animSpeed;
		anim->loop = true;

		anim = &cleanWtop;

		anim->PushBack({ 6 * TILE_SIZE, Y * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->PushBack({ 14 * TILE_SIZE, Y * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->PushBack({ 22 * TILE_SIZE, Y * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->PushBack({ 30 * TILE_SIZE, Y * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->PushBack({ 38 * TILE_SIZE, Y * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->PushBack({ 46 * TILE_SIZE, Y * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->PushBack({ 54 * TILE_SIZE, Y * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->PushBack({ 62 * TILE_SIZE, Y * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->speed = animSpeed;
		anim->loop = true;

		anim = &cleanWmid;

		anim->PushBack({ 6 * TILE_SIZE, (Y + 1) * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->PushBack({ 14 * TILE_SIZE, (Y + 1) * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->PushBack({ 22 * TILE_SIZE, (Y + 1) * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->PushBack({ 30 * TILE_SIZE, (Y + 1) * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->PushBack({ 38 * TILE_SIZE, (Y + 1) * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->PushBack({ 46 * TILE_SIZE, (Y + 1) * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->PushBack({ 54 * TILE_SIZE, (Y + 1) * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->PushBack({ 62 * TILE_SIZE, (Y + 1) * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->speed = animSpeed;
		anim->loop = true;

		anim = &cleanWdown;

		anim->PushBack({ 6 * TILE_SIZE, (Y + 2) * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->PushBack({ 14 * TILE_SIZE, (Y + 2) * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->PushBack({ 22 * TILE_SIZE, (Y + 2) * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->PushBack({ 30 * TILE_SIZE,(Y + 2) * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->PushBack({ 38 * TILE_SIZE,(Y + 2) * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->PushBack({ 46 * TILE_SIZE, (Y + 2) * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->PushBack({ 54 * TILE_SIZE,(Y + 2) * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->PushBack({ 62 * TILE_SIZE, (Y + 2) * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->speed = animSpeed;
		anim->loop = true;

		anim = &cleanWtopR;

		anim->PushBack({ 7 * TILE_SIZE, Y * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->PushBack({ 15 * TILE_SIZE, Y * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->PushBack({ 23 * TILE_SIZE, Y * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->PushBack({ 31 * TILE_SIZE, Y * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->PushBack({ 39 * TILE_SIZE, Y * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->PushBack({ 47 * TILE_SIZE, Y * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->PushBack({ 55 * TILE_SIZE, Y * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->PushBack({ 63 * TILE_SIZE, Y * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->speed = animSpeed;
		anim->loop = true;

		anim = &cleanWright;

		anim->PushBack({ 7 * TILE_SIZE,  (Y + 1) * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->PushBack({ 15 * TILE_SIZE,  (Y + 1) * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->PushBack({ 23 * TILE_SIZE,  (Y + 1) * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->PushBack({ 31 * TILE_SIZE, (Y + 1) * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->PushBack({ 39 * TILE_SIZE,  (Y + 1) * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->PushBack({ 47 * TILE_SIZE,  (Y + 1) * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->PushBack({ 55 * TILE_SIZE,  (Y + 1) * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->PushBack({ 63 * TILE_SIZE,  (Y + 1) * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->speed = animSpeed;
		anim->loop = true;

		anim = &cleanWdownR;

		anim->PushBack({ 7 * TILE_SIZE, (Y + 2) * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->PushBack({ 15 * TILE_SIZE,(Y + 2) * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->PushBack({ 23 * TILE_SIZE,(Y + 2) * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->PushBack({ 31 * TILE_SIZE, (Y + 2) * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->PushBack({ 39 * TILE_SIZE, (Y + 2) * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->PushBack({ 47 * TILE_SIZE, (Y + 2) * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->PushBack({ 55 * TILE_SIZE, (Y + 2) * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->PushBack({ 63 * TILE_SIZE, (Y + 2) * TILE_SIZE, TILE_SIZE, TILE_SIZE });
		anim->speed = animSpeed;
		anim->loop = true;

	}

	// WATERFALLS
	
	int X = 5, Y = 0, diff = 8;
	// Dark
	anim = &cascOTopL; 

	anim->PushBack({ (X) * TILE_SIZE, (Y) * TILE_SIZE, TILE_SIZE, TILE_SIZE });
	anim->PushBack({ (X + diff) * TILE_SIZE,(Y) * TILE_SIZE, TILE_SIZE, TILE_SIZE});
	anim->PushBack({ (X + diff*2) * TILE_SIZE,(Y) * TILE_SIZE, TILE_SIZE, TILE_SIZE });
	anim->PushBack({ (X + diff*3) * TILE_SIZE, (Y) * TILE_SIZE, TILE_SIZE, TILE_SIZE });
	anim->speed = animSpeed;
	anim->loop = true;

	anim = &cascOLeft; 

	anim->PushBack({ (X) * TILE_SIZE, (Y + 1)*TILE_SIZE, TILE_SIZE, TILE_SIZE });
	anim->PushBack({ (X + diff) * TILE_SIZE,(Y + 1)*TILE_SIZE, TILE_SIZE, TILE_SIZE });
	anim->PushBack({ (X + diff * 2) * TILE_SIZE,(Y +1)*TILE_SIZE, TILE_SIZE, TILE_SIZE });
	anim->PushBack({ (X + diff * 3) * TILE_SIZE, (Y +1 )*TILE_SIZE, TILE_SIZE, TILE_SIZE });
	anim->speed = animSpeed;
	anim->loop = true;

	anim = &cascODownL; 

	anim->PushBack({ (X)*TILE_SIZE, (Y + 2) * TILE_SIZE, TILE_SIZE, TILE_SIZE });
	anim->PushBack({ (X + diff) * TILE_SIZE,(Y + 2) * TILE_SIZE, TILE_SIZE, TILE_SIZE });
	anim->PushBack({ (X + diff * 2) * TILE_SIZE,(Y + 2) * TILE_SIZE, TILE_SIZE, TILE_SIZE });
	anim->PushBack({ (X + diff * 3) * TILE_SIZE, (Y + 2) * TILE_SIZE, TILE_SIZE, TILE_SIZE });
	anim->speed = animSpeed;
	anim->loop = true;

	anim = &cascOTop; 

	anim->PushBack({ (X + 1)*TILE_SIZE, (Y)*TILE_SIZE, TILE_SIZE, TILE_SIZE });
	anim->PushBack({ (X + diff +1) * TILE_SIZE,(Y)*TILE_SIZE, TILE_SIZE, TILE_SIZE });
	anim->PushBack({ (X + diff * 2 +1) * TILE_SIZE,(Y)*TILE_SIZE, TILE_SIZE, TILE_SIZE });
	anim->PushBack({ (X + diff * 3 +1) * TILE_SIZE, (Y)*TILE_SIZE, TILE_SIZE, TILE_SIZE });
	anim->speed = animSpeed;
	anim->loop = true;

	anim = &cascOMid; 

	anim->PushBack({ (X + 1) * TILE_SIZE, (Y +1)*TILE_SIZE, TILE_SIZE, TILE_SIZE });
	anim->PushBack({ (X + diff + 1) * TILE_SIZE,(Y +1)*TILE_SIZE, TILE_SIZE, TILE_SIZE });
	anim->PushBack({ (X + diff * 2 + 1) * TILE_SIZE,(Y +1)*TILE_SIZE, TILE_SIZE, TILE_SIZE });
	anim->PushBack({ (X + diff * 3 + 1) * TILE_SIZE, (Y +1)*TILE_SIZE, TILE_SIZE, TILE_SIZE });
	anim->speed = animSpeed;
	anim->loop = true;

	anim = &cascODown; 

	anim->PushBack({ (X + 1) * TILE_SIZE, (Y + 2) * TILE_SIZE, TILE_SIZE, TILE_SIZE });
	anim->PushBack({ (X + diff + 1) * TILE_SIZE,(Y + 2) * TILE_SIZE, TILE_SIZE, TILE_SIZE });
	anim->PushBack({ (X + diff * 2 + 1) * TILE_SIZE,(Y + 2) * TILE_SIZE, TILE_SIZE, TILE_SIZE });
	anim->PushBack({ (X + diff * 3 + 1) * TILE_SIZE, (Y + 2) * TILE_SIZE, TILE_SIZE, TILE_SIZE });
	anim->speed = animSpeed;
	anim->loop = true;

	anim = &cascOTopR; 

	anim->PushBack({ (X + 2) * TILE_SIZE, (Y)*TILE_SIZE, TILE_SIZE, TILE_SIZE });
	anim->PushBack({ (X + diff + 2) * TILE_SIZE,(Y)*TILE_SIZE, TILE_SIZE, TILE_SIZE });
	anim->PushBack({ (X + diff * 2 + 2) * TILE_SIZE,(Y)*TILE_SIZE, TILE_SIZE, TILE_SIZE });
	anim->PushBack({ (X + diff * 3 + 2) * TILE_SIZE, (Y)*TILE_SIZE, TILE_SIZE, TILE_SIZE });
	anim->speed = animSpeed;
	anim->loop = true;

	anim = &cascORight; 

	anim->PushBack({ (X + 2) * TILE_SIZE, (Y +1)*TILE_SIZE, TILE_SIZE, TILE_SIZE });
	anim->PushBack({ (X + diff + 2) * TILE_SIZE,(Y +1)*TILE_SIZE, TILE_SIZE, TILE_SIZE });
	anim->PushBack({ (X + diff * 2 + 2) * TILE_SIZE,(Y +1)*TILE_SIZE, TILE_SIZE, TILE_SIZE });
	anim->PushBack({ (X + diff * 3 + 2) * TILE_SIZE, (Y +1)*TILE_SIZE, TILE_SIZE, TILE_SIZE });
	anim->speed = animSpeed;
	anim->loop = true;

	anim = &cascODownR;

	anim->PushBack({ (X + 2) * TILE_SIZE, (Y + 2) * TILE_SIZE, TILE_SIZE, TILE_SIZE });
	anim->PushBack({ (X + diff + 2) * TILE_SIZE,(Y + 2) * TILE_SIZE, TILE_SIZE, TILE_SIZE });
	anim->PushBack({ (X + diff * 2 + 2) * TILE_SIZE,(Y + 2) * TILE_SIZE, TILE_SIZE, TILE_SIZE });
	anim->PushBack({ (X + diff * 3 + 2) * TILE_SIZE, (Y + 2) * TILE_SIZE, TILE_SIZE, TILE_SIZE });
	anim->speed = animSpeed;
	anim->loop = true;

	// Clear

	Y = 6;
	// Dark
	anim = &cascTopL;

	anim->PushBack({ (X)*TILE_SIZE, (Y)*TILE_SIZE, TILE_SIZE, TILE_SIZE });
	anim->PushBack({ (X + diff) * TILE_SIZE,(Y)*TILE_SIZE, TILE_SIZE, TILE_SIZE });
	anim->PushBack({ (X + diff * 2) * TILE_SIZE,(Y)*TILE_SIZE, TILE_SIZE, TILE_SIZE });
	anim->PushBack({ (X + diff * 3) * TILE_SIZE, (Y)*TILE_SIZE, TILE_SIZE, TILE_SIZE });
	anim->speed = animSpeed;
	anim->loop = true;

	anim = &cascLeft;

	anim->PushBack({ (X)*TILE_SIZE, (Y + 1) * TILE_SIZE, TILE_SIZE, TILE_SIZE });
	anim->PushBack({ (X + diff) * TILE_SIZE,(Y + 1) * TILE_SIZE, TILE_SIZE, TILE_SIZE });
	anim->PushBack({ (X + diff * 2) * TILE_SIZE,(Y + 1) * TILE_SIZE, TILE_SIZE, TILE_SIZE });
	anim->PushBack({ (X + diff * 3) * TILE_SIZE, (Y + 1) * TILE_SIZE, TILE_SIZE, TILE_SIZE });
	anim->speed = animSpeed;
	anim->loop = true;

	anim = &cascDownL;

	anim->PushBack({ (X)*TILE_SIZE, (Y + 2) * TILE_SIZE, TILE_SIZE, TILE_SIZE });
	anim->PushBack({ (X + diff) * TILE_SIZE,(Y + 2) * TILE_SIZE, TILE_SIZE, TILE_SIZE });
	anim->PushBack({ (X + diff * 2) * TILE_SIZE,(Y + 2) * TILE_SIZE, TILE_SIZE, TILE_SIZE });
	anim->PushBack({ (X + diff * 3) * TILE_SIZE, (Y + 2) * TILE_SIZE, TILE_SIZE, TILE_SIZE });
	anim->speed = animSpeed;
	anim->loop = true;

	anim = &cascTop;

	anim->PushBack({ (X + 1) * TILE_SIZE, (Y)*TILE_SIZE, TILE_SIZE, TILE_SIZE });
	anim->PushBack({ (X + diff + 1) * TILE_SIZE,(Y)*TILE_SIZE, TILE_SIZE, TILE_SIZE });
	anim->PushBack({ (X + diff * 2 + 1) * TILE_SIZE,(Y)*TILE_SIZE, TILE_SIZE, TILE_SIZE });
	anim->PushBack({ (X + diff * 3 + 1) * TILE_SIZE, (Y)*TILE_SIZE, TILE_SIZE, TILE_SIZE });
	anim->speed = animSpeed;
	anim->loop = true;

	anim = &cascMid;

	anim->PushBack({ (X + 1) * TILE_SIZE, (Y + 1) * TILE_SIZE, TILE_SIZE, TILE_SIZE });
	anim->PushBack({ (X + diff + 1) * TILE_SIZE,(Y + 1) * TILE_SIZE, TILE_SIZE, TILE_SIZE });
	anim->PushBack({ (X + diff * 2 + 1) * TILE_SIZE,(Y + 1) * TILE_SIZE, TILE_SIZE, TILE_SIZE });
	anim->PushBack({ (X + diff * 3 + 1) * TILE_SIZE, (Y + 1) * TILE_SIZE, TILE_SIZE, TILE_SIZE });
	anim->speed = animSpeed;
	anim->loop = true;

	anim = &cascDown;

	anim->PushBack({ (X + 1) * TILE_SIZE, (Y + 2) * TILE_SIZE, TILE_SIZE, TILE_SIZE });
	anim->PushBack({ (X + diff + 1) * TILE_SIZE,(Y + 2) * TILE_SIZE, TILE_SIZE, TILE_SIZE });
	anim->PushBack({ (X + diff * 2 + 1) * TILE_SIZE,(Y + 2) * TILE_SIZE, TILE_SIZE, TILE_SIZE });
	anim->PushBack({ (X + diff * 3 + 1) * TILE_SIZE, (Y + 2) * TILE_SIZE, TILE_SIZE, TILE_SIZE });
	anim->speed = animSpeed;
	anim->loop = true;

	anim = &cascTopR;

	anim->PushBack({ (X + 2) * TILE_SIZE, (Y)*TILE_SIZE, TILE_SIZE, TILE_SIZE });
	anim->PushBack({ (X + diff + 2) * TILE_SIZE,(Y)*TILE_SIZE, TILE_SIZE, TILE_SIZE });
	anim->PushBack({ (X + diff * 2 + 2) * TILE_SIZE,(Y)*TILE_SIZE, TILE_SIZE, TILE_SIZE });
	anim->PushBack({ (X + diff * 3 + 2) * TILE_SIZE, (Y)*TILE_SIZE, TILE_SIZE, TILE_SIZE });
	anim->speed = animSpeed;
	anim->loop = true;

	anim = &cascRight;

	anim->PushBack({ (X + 2) * TILE_SIZE, (Y + 1) * TILE_SIZE, TILE_SIZE, TILE_SIZE });
	anim->PushBack({ (X + diff + 2) * TILE_SIZE,(Y + 1) * TILE_SIZE, TILE_SIZE, TILE_SIZE });
	anim->PushBack({ (X + diff * 2 + 2) * TILE_SIZE,(Y + 1) * TILE_SIZE, TILE_SIZE, TILE_SIZE });
	anim->PushBack({ (X + diff * 3 + 2) * TILE_SIZE, (Y + 1) * TILE_SIZE, TILE_SIZE, TILE_SIZE });
	anim->speed = animSpeed;
	anim->loop = true;

	anim = &cascDownR;

	anim->PushBack({ (X + 2) * TILE_SIZE, (Y + 2) * TILE_SIZE, TILE_SIZE, TILE_SIZE });
	anim->PushBack({ (X + diff + 2) * TILE_SIZE,(Y + 2) * TILE_SIZE, TILE_SIZE, TILE_SIZE });
	anim->PushBack({ (X + diff * 2 + 2) * TILE_SIZE,(Y + 2) * TILE_SIZE, TILE_SIZE, TILE_SIZE });
	anim->PushBack({ (X + diff * 3 + 2) * TILE_SIZE, (Y + 2) * TILE_SIZE, TILE_SIZE, TILE_SIZE });
	anim->speed = animSpeed;
	anim->loop = true;
	
	anim = nullptr;
	delete anim;
}

void Map::UpdateAnimatedTiles() // Optimizar el código está sobrevalorado
{
	switch (app->stages->actualStage)
	{
	case StageIndex::TOWN:
		rockCleanWtopL.Update();
		rockCleanWleft.Update();
		rockCleanWdownL.Update();
		rockCleanWtop.Update();
		rockCleanWmid.Update();
		rockCleanWdown.Update();
		rockCleanWtopR.Update();
		rockCleanWright.Update();
		rockCleanWdownR.Update();

		cleanWtopL.Update();
		cleanWleft.Update();
		cleanWdownL.Update();
		cleanWtop.Update();
		cleanWmid.Update();
		cleanWdown.Update();
		cleanWtopR.Update();
		cleanWright.Update();
		cleanWdownR.Update();

		cascTopL.Update();
		cascLeft.Update();
		cascDownL.Update();
		cascTop.Update();
		cascMid.Update();
		cascDown.Update();
		cascTopR.Update();
		cascRight.Update();
		cascDownR.Update();
		break;
	case StageIndex::TAVERN:
		// Water
		rockDarkWtopL.Update();
		rockDarkWleft.Update();
		rockDarkWdownL.Update();
		rockDarkWtop.Update();
		rockDarkWmid.Update();
		rockDarkWdown.Update();
		rockDarkWtopR.Update();
		rockDarkWright.Update();
		rockDarkWdownR.Update();


		rockInterTopL.Update();
		rockInterTopR.Update();
		rockInterDownL.Update();
		rockInterDownR.Update();

		// Waterfalls
		cascOTopL.Update();
		cascOLeft.Update();
		cascODownL.Update();
		cascOTop.Update();
		cascOMid.Update();
		cascODown.Update();
		cascOTopR.Update();
		cascORight.Update();
		cascODownR.Update();

		break;
	default:
		break;
	}

}

// Destructor
Map::~Map()
{}

template <class T>
T Properties::GetProperty(const char* value, int defaultValue) const
{
	//...

	ListItem<Property*>* item = list.start;

	while (item)
	{

		if (item->data->name == value) {

			ListItem<const char*>* charValueInList;
			charValueInList = app->map->charValues.start;

			for (charValueInList = app->map->charValues.start; charValueInList != NULL; charValueInList = charValueInList->next)
			{
				if (charValueInList->data == value)
				{
					return (T)item->data->charValue.GetString();
				}
			}
			return (T)item->data->intValue;
		}
			
		item = item->next;
	}
	return (T)defaultValue;
}

int Properties::GetPropertyInt(const char* value, int defaultValue) const
{
	//...

	ListItem<Property*>* item = list.start;

	while (item)
	{
		if (item->data->name == value) {

			return item->data->intValue;

		}

		item = item->next;
	}
	return defaultValue;
}

const char* Properties::GetPropertyChar(const char* value, const char* defaultValue) const
{
	//...

	ListItem<Property*>* item = list.start;

	while (item)
	{

		if (item->data->name == value) {

			return item->data->charValue.GetString();

		}

		item = item->next;
	}
	return defaultValue;
}

// Called before render is available
bool Map::Awake(pugi::xml_node& config)
{
	wallsEntity = app->entities->CreateEntity();
    LOG("Loading Map Parser");
    bool ret = true;

    folder.Create(config.child("folder").child_value());

    return ret;
}

bool Map::Start() {

	// Add all the string properties in the list
	charValues.add("Col");
	return true;
}

// Draw the map (all requried layers)
void Map::Draw()
{
	if (mapLoaded == false) return;

	// Prepare the loop to draw all tilesets + DrawTexture()
	ListItem<MapLayer*>* mapLayerItem;
	mapLayerItem = mapData.layers.start;

	UpdateAnimatedTiles();

	// Draw all the layers and not just the first one
	while (mapLayerItem != NULL) {

		if (mapLayerItem->data->isHigh == false) {

			for (int x = 0; x < mapLayerItem->data->width; x++)
			{
				for (int y = 0; y < mapLayerItem->data->height; y++)
				{

					if (mapLayerItem->data->properties.GetProperty<int>("Draw") == 1) {

						int gid = mapLayerItem->data->Get(x, y);

						if (gid > 0) {

							iPoint pos = MapToWorld(x, y);

							TileSet* tileset = GetTilesetFromTileId(gid);
							SDL_Rect r = tileset->GetTileRect(gid);

							app->render->DrawTexture(tileset->texture, pos.x, pos.y, &r);
						}
					}
					else if (mapLayerItem->data->properties.GetProperty<int>("hasWater") == 1) {

						// Complete the draw function
						int gid = mapLayerItem->data->Get(x, y);

						if (gid > 0) {

							iPoint pos = MapToWorld(x, y);
								// Print the specific water animation on each tile
								switch (mapLayerItem->data->properties.GetProperty<int>("water"))
								{
									// Dark
								case 1:
									app->render->DrawTexture(water, pos.x, pos.y, &rockDarkWtopL.GetCurrentFrame());
									break;
								case 2:
									app->render->DrawTexture(water, pos.x, pos.y, &rockDarkWleft.GetCurrentFrame());
									break;
								case 3:
									app->render->DrawTexture(water, pos.x, pos.y, &rockDarkWdownL.GetCurrentFrame());
									break;
								case 4:
									app->render->DrawTexture(water, pos.x, pos.y, &rockDarkWtop.GetCurrentFrame());
									break;
								case 5:
									app->render->DrawTexture(water, pos.x, pos.y, &rockDarkWmid.GetCurrentFrame());
									break;
								case 6:
									app->render->DrawTexture(water, pos.x, pos.y, &rockDarkWdown.GetCurrentFrame());
									break;
								case 7:
									app->render->DrawTexture(water, pos.x, pos.y, &rockDarkWtopR.GetCurrentFrame());
									break;
								case 8:
									app->render->DrawTexture(water, pos.x, pos.y, &rockDarkWright.GetCurrentFrame());
									break;
								case 9:
									app->render->DrawTexture(water, pos.x, pos.y, &rockDarkWdownR.GetCurrentFrame());
									break;

									// Rock Clean
								case 10:
									app->render->DrawTexture(water, pos.x, pos.y, &rockCleanWtopL.GetCurrentFrame());
									break;
								case 11:
									app->render->DrawTexture(water, pos.x, pos.y, &rockCleanWleft.GetCurrentFrame());
									break;
								case 12:
									app->render->DrawTexture(water, pos.x, pos.y, &rockCleanWdownL.GetCurrentFrame());
									break;
								case 13:
									app->render->DrawTexture(water, pos.x, pos.y, &rockCleanWtop.GetCurrentFrame());
									break;
								case 14:
									app->render->DrawTexture(water, pos.x, pos.y, &rockCleanWmid.GetCurrentFrame());
									break;
								case 15:
									app->render->DrawTexture(water, pos.x, pos.y, &rockCleanWdown.GetCurrentFrame());
									break;
								case 16:
									app->render->DrawTexture(water, pos.x, pos.y, &rockCleanWtopR.GetCurrentFrame());
									break;
								case 17:
									app->render->DrawTexture(water, pos.x, pos.y, &rockCleanWright.GetCurrentFrame());
									break;
								case 18:
									app->render->DrawTexture(water, pos.x, pos.y, &rockCleanWdownR.GetCurrentFrame());
									break;

									// Clean
								case 19:
									app->render->DrawTexture(water, pos.x, pos.y, &cleanWtopL.GetCurrentFrame());
									break;
								case 20:
									app->render->DrawTexture(water, pos.x, pos.y, &cleanWleft.GetCurrentFrame());
									break;
								case 21:
									app->render->DrawTexture(water, pos.x, pos.y, &cleanWdownL.GetCurrentFrame());
									break;
								case 22:
									app->render->DrawTexture(water, pos.x, pos.y, &cleanWtop.GetCurrentFrame());
									break;
								case 23:
									app->render->DrawTexture(water, pos.x, pos.y, &cleanWmid.GetCurrentFrame());
									break;
								case 24:
									app->render->DrawTexture(water, pos.x, pos.y, &cleanWdown.GetCurrentFrame());
									break;
								case 25:
									app->render->DrawTexture(water, pos.x, pos.y, &cleanWtopR.GetCurrentFrame());
									break;
								case 26:
									app->render->DrawTexture(water, pos.x, pos.y, &cleanWright.GetCurrentFrame());
									break;
								case 27:
									app->render->DrawTexture(water, pos.x, pos.y, &cleanWdownR.GetCurrentFrame());
									break;

									// rock clean inter
								case 28:
									app->render->DrawTexture(water, pos.x, pos.y, &rockInterTopL.GetCurrentFrame());
									break;
								case 29:
									app->render->DrawTexture(water, pos.x, pos.y, &rockInterDownL.GetCurrentFrame());
									break;
								case 30:
									app->render->DrawTexture(water, pos.x, pos.y, &rockInterTopR.GetCurrentFrame());
									break;
								case 31:
									app->render->DrawTexture(water, pos.x, pos.y, &rockInterDownR.GetCurrentFrame());
									break;

								default:
									break;
								}
						}
					}
					else if (mapLayerItem->data->properties.GetProperty<int>("hasWaterfall") == 1) {
						// Complete the draw function
						int gid = mapLayerItem->data->Get(x, y);

						if (gid > 0) {

							iPoint pos = MapToWorld(x, y);
							// Print the specific water animation on each tile

							switch (mapLayerItem->data->properties.GetProperty<int>("waterfallType"))
							{
							case 1:
								app->render->DrawTexture(waterfall, pos.x, pos.y, &cascOTopL.GetCurrentFrame());
								break;
							case 2:
								app->render->DrawTexture(waterfall, pos.x, pos.y, &cascOLeft.GetCurrentFrame());
								break;
							case 3:
								app->render->DrawTexture(waterfall, pos.x, pos.y, &cascODownL.GetCurrentFrame());
								break;
							case 4:
								app->render->DrawTexture(waterfall, pos.x, pos.y, &cascOTop.GetCurrentFrame());
								break;
							case 5:
								app->render->DrawTexture(waterfall, pos.x, pos.y, &cascOMid.GetCurrentFrame());
								break;
							case 6:
								app->render->DrawTexture(waterfall, pos.x, pos.y, &cascODown.GetCurrentFrame());
								break;
							case 7:
								app->render->DrawTexture(waterfall, pos.x, pos.y, &cascOTopR.GetCurrentFrame());
								break;
							case 8:
								app->render->DrawTexture(waterfall, pos.x, pos.y, &cascORight.GetCurrentFrame());
								break;
							case 9:
								app->render->DrawTexture(waterfall, pos.x, pos.y, &cascODownR.GetCurrentFrame());
								break;
							case 10:
								app->render->DrawTexture(waterfall, pos.x, pos.y, &cascTopL.GetCurrentFrame());
								break;
							case 11:
								app->render->DrawTexture(waterfall, pos.x, pos.y, &cascLeft.GetCurrentFrame());
								break;
							case 12:
								app->render->DrawTexture(waterfall, pos.x, pos.y, &cascDownL.GetCurrentFrame());
								break;
							case 13:
								app->render->DrawTexture(waterfall, pos.x, pos.y, &cascTop.GetCurrentFrame());
								break;
							case 14:
								app->render->DrawTexture(waterfall, pos.x, pos.y, &cascMid.GetCurrentFrame());
								break;
							case 15:
								app->render->DrawTexture(waterfall, pos.x, pos.y, &cascDown.GetCurrentFrame());
								break;
							case 16:
								app->render->DrawTexture(waterfall, pos.x, pos.y, &cascTopR.GetCurrentFrame());
								break;
							case 17:
								app->render->DrawTexture(waterfall, pos.x, pos.y, &cascRight.GetCurrentFrame());
								break;
							case 18:
								app->render->DrawTexture(waterfall, pos.x, pos.y, &cascDownR.GetCurrentFrame());
							}
						}
					}
				}
			}
		}
		mapLayerItem = mapLayerItem->next;
	}

	delete mapLayerItem;
}

void Map::ReDraw()
{
	if (mapLoaded == false) return;

	// Prepare the loop to draw all tilesets + DrawTexture()
	ListItem<MapLayer*>* mapLayerItem;
	mapLayerItem = mapData.layers.start;

	// Draw all the layers and not just the first one
	while (mapLayerItem != NULL) {

		if (mapLayerItem->data->isHigh == true) {

			if ((int)mapLayerItem->data->properties.GetProperty<int>("Draw") == 1) {

				for (int x = 0; x < mapLayerItem->data->width; x++)
				{
					for (int y = 0; y < mapLayerItem->data->height; y++)
					{
						int gid = mapLayerItem->data->Get(x, y);

						if (gid > 0) {

							iPoint pos = MapToWorld(x, y);

								TileSet* tileset = GetTilesetFromTileId(gid);
								SDL_Rect r = tileset->GetTileRect(gid);

								app->render->DrawTexture(tileset->texture, pos.x, pos.y, &r);
						}
					}
				}
			}
		}

		mapLayerItem = mapLayerItem->next;
	}
}

// Create a method that translates x,y coordinates from map positions to world positions
iPoint Map::MapToWorld(int x, int y) const
{
	iPoint ret;

	// Add isometric map to world coordinates
	if (mapData.type == MAPTYPE_ORTHOGONAL)
	{
		ret.x = x * mapData.tileWidth;
		ret.y = y * mapData.tileHeight;
	}
	else if (mapData.type == MAPTYPE_ISOMETRIC)
	{
		ret.x = (x - y) * (mapData.tileWidth / 2);
		ret.y = (x + y) * (mapData.tileHeight / 2);
	}
	else
	{
		LOG("Unknown map type");
		ret.x = x; ret.y = y;
	}

	return ret;
}

// Add orthographic world to map coordinates
iPoint Map::WorldToMap(int x, int y) const
{
	iPoint ret(0, 0);

	// Add the case for isometric maps to WorldToMap
	if (mapData.type == MAPTYPE_ORTHOGONAL)
	{
		ret.x = x / mapData.tileWidth;
		ret.y = y / mapData.tileHeight;
	}
	else if (mapData.type == MAPTYPE_ISOMETRIC)
	{

		float half_width = mapData.tileWidth * 0.5f;
		float half_height = mapData.tileHeight * 0.5f;
		ret.x = int((x / half_width + y / half_height) / 2);
		ret.y = int((y / half_height - (x / half_width)) / 2);
	}
	else
	{
		LOG("Unknown map type");
		ret.x = x; ret.y = y;
	}

	return ret;
}

// Pick the right Tileset based on a tile id
TileSet* Map::GetTilesetFromTileId(int id) const
{
	ListItem<TileSet*>* item = mapData.tilesets.start;
	TileSet* set = item->data;

	while (item)
	{
		if (id < item->data->firstgid)
		{
			set = item->prev->data;
			break;
		}
		set = item->data;
		item = item->next;
	}

	return set;
}

// Get relative Tile rectangle
SDL_Rect TileSet::GetTileRect(int id) const
{
	SDL_Rect rect = { 0 };

	// Get relative Tile rectangle
	int relativeId = id - firstgid;
	rect.w = tileWidth;
	rect.h = tileHeight;
	rect.x = margin + ((rect.w + spacing) * (relativeId % columns));
	rect.y = margin + ((rect.h + spacing) * (relativeId / columns));
	
	return rect;
}

// Load new map
bool Map::Load(const char* filename)
{
    bool ret = true;
    SString tmp("%s%s", folder.GetString(), filename);

	pugi::xml_document mapFile; 
    pugi::xml_parse_result result = mapFile.load_file(tmp.GetString());

    if(result == NULL)
    {
        LOG("Could not load map xml file %s. pugi error: %s", filename, result.description());
        ret = false;
    }

	// load and fill all your map data
    if(ret == true)
    {
		ret = LoadMap(mapFile);
	}

    // Load a tileset
	if (ret == true)
	{
		ret = LoadTileSets(mapFile.child("map"));
	}

	// Load layer info
	if (ret == true)
	{
		ret = LoadAllLayers(mapFile.child("map"));
	}
    
	mapLoaded = ret;

    if(ret == true)
    {
		LoadCol();
		
		water = app->tex->Load("Assets/maps/tiles/[A]Water_pipo.png");
		waterfall = app->tex->Load("Assets/maps/tiles/[A]WaterFall_pipo.png");
    }

	return ret;
}

// Load map general properties
bool Map::LoadMap(pugi::xml_node mapFile)
{
	bool ret = true;
	pugi::xml_node map = mapFile.child("map");

	if (map == NULL)
	{
		LOG("Error parsing map xml file: Cannot find 'map' tag.");
		ret = false;
	}
	else
	{
		// Load map general properties
		mapData.height = map.attribute("height").as_int();
		mapData.width = map.attribute("width").as_int();
		mapData.tileHeight = map.attribute("tileheight").as_int();
		mapData.tileWidth = map.attribute("tilewidth").as_int();

		// Add formula to go from isometric map to world coordinates
		mapData.type = MAPTYPE_UNKNOWN;
		if (strcmp(map.attribute("orientation").as_string(), "isometric") == 0)
		{
			mapData.type = MAPTYPE_ISOMETRIC;
		}
		if (strcmp(map.attribute("orientation").as_string(), "orthogonal") == 0)
		{
			mapData.type = MAPTYPE_ORTHOGONAL;
		}
	}

	return ret;
}

// Implement the LoadTileSet function to load the tileset properties
bool Map::LoadTileSets(pugi::xml_node mapFile) {

	bool ret = true;

	pugi::xml_node tileset;
	for (tileset = mapFile.child("tileset"); tileset && ret; tileset = tileset.next_sibling("tileset"))
	{
		TileSet* set = new TileSet();
		if (ret == true) ret = LoadTilesetDetails(tileset, set);
		if (ret == true) ret = LoadTilesetImage(tileset, set);
		mapData.tilesets.add(set);
	}

	return ret;
}

// Load Tileset attributes
bool Map::LoadTilesetDetails(pugi::xml_node& tileset_node, TileSet* set)
{
	bool ret = true;

	// Load Tileset attributes
	set->name.Create(tileset_node.attribute("name").as_string());
	set->firstgid = tileset_node.attribute("firstgid").as_int();
	set->tileWidth = tileset_node.attribute("tilewidth").as_int();
	set->tileHeight = tileset_node.attribute("tileheight").as_int();
	set->margin = tileset_node.attribute("margin").as_int();
	set->spacing = tileset_node.attribute("spacing").as_int();
	set->tilecount = tileset_node.attribute("tilecount").as_int();
	set->columns = tileset_node.attribute("columns").as_int();

	return ret;
}

// Load Tileset image
bool Map::LoadTilesetImage(pugi::xml_node& tileset_node, TileSet* set)
{
	bool ret = true;
	pugi::xml_node image = tileset_node.child("image");

	if (image == NULL)
	{
		LOG("Error parsing tileset xml file: Cannot find 'image' tag.");
		ret = false;
	}
	else
	{
		// Load Tileset image
		SString tmp("%s%s", folder.GetString(), image.attribute("source").as_string());
		set->texture = app->tex->Load(tmp.GetString());
	}

	return ret;
}

// Implement a function that loads a single layer layer
bool Map::LoadLayer(pugi::xml_node& node, MapLayer* layer)
{
	bool ret = true;

	// Load the attributes
	layer->name = node.attribute("name").as_string();
	layer->width = node.attribute("width").as_int();
	layer->height = node.attribute("height").as_int();
	
	

	// Call Load Propoerties
	LoadProperties(node, layer->properties);

	// Reserve the memory for the tile array
	layer->data = new uint[layer->width * layer->height];
	memset(layer->data, 0, layer->width * layer->height);

	// Iterate over all the tiles and assign the values
	pugi::xml_node tile;
	int i = 0;
	for (tile = node.child("data").child("tile"); tile && ret; tile = tile.next_sibling("tile"))
	{
		layer->data[i] = tile.attribute("gid").as_int();
		i++;
	}

	//LOG("%d", layer->properties.GetProperty<int>("Height"));
	layer->properties.GetProperty<int>("Height") == 1 ? layer->isHigh = true : layer->isHigh = false;
	
	return ret;
}

// Iterate all layers and load each of them
bool Map::LoadAllLayers(pugi::xml_node mapNode) {
	bool ret = true;
	for (pugi::xml_node layerNode = mapNode.child("layer"); layerNode && ret; layerNode = layerNode.next_sibling("layer"))
	{
		// Load the layer
		MapLayer* mapLayer = new MapLayer();
		ret = LoadLayer(layerNode, mapLayer);

		// add the layer to the map
		mapData.layers.add(mapLayer);
	}

	return ret;
}

// Load a group of properties from a node and fill a list with it
bool Map::LoadProperties(pugi::xml_node& node, Properties& properties)
{
	bool ret = false;
	pugi::xml_node data = node.child("properties");

	if (data != NULL) {

		for (pugi::xml_node propertieNode = node.child("properties").child("property"); propertieNode; propertieNode = propertieNode.next_sibling("property"))
		{
			Properties::Property* p = new Properties::Property();
			p->name = propertieNode.attribute("name").as_string();
			p->intValue = propertieNode.attribute("value").as_int();
			p->charValue = propertieNode.attribute("value").as_string();

			properties.list.add(p);
		}
	}
	
	return ret;
}

void Map::LoadCol() {

	if (mapLoaded == false) return;

	// Prepare the loop to draw all tilesets + DrawTexture()
	ListItem<MapLayer*>* mapLayerItem;
	mapLayerItem = mapData.layers.start;

	int wallsCount = 0;
	int entryCount = 0;

	//ListItem<Entries*>* entryInList = mapEntries.start;

	while (mapLayerItem != NULL) {
	
		const char* wallChar = static_cast<const char*>(mapLayerItem->data->properties.GetProperty<const char*>("Col"));
		if (wallChar != nullptr) {

			
			if (wallChar == std::string("wall")) {

				for (int x = 0; x < mapLayerItem->data->width; x++)
				{
					for (int y = 0; y < mapLayerItem->data->height; y++)
					{
						// Complete the col function
						int gid = mapLayerItem->data->Get(x, y);

						if (gid > 0) {

							// Obtain the tile set using GetTilesetFromTileId
							// now we always use the firt tileset in the list
							TileSet* tileset = mapData.tilesets.start->data;

							SDL_Rect r = tileset->GetTileRect(gid);
							iPoint pos = MapToWorld(x, y);

							mapWalls[wallsCount] = app->collisions->AddCollider({ pos.x, pos.y , r.w,  r.h }, Collider::Type::WALL, wallsEntity);
							
							wallsCount++;
						}
					}
				}
			}

			if (wallChar == std::string("instant")) {

				for (int x = 0; x < mapLayerItem->data->width; x++)
				{
					for (int y = 0; y < mapLayerItem->data->height; y++)
					{
						// Complete the col function
						int gid = mapLayerItem->data->Get(x, y);

						if (gid > 0) {

							// Obtain the tile set using GetTilesetFromTileId
							// now we always use the firt tileset in the list
							TileSet* tileset = mapData.tilesets.start->data;

							SDL_Rect r = tileset->GetTileRect(gid);
							iPoint pos = MapToWorld(x, y);

							Entries* entry = new Entries();

							//mapEntries.add(entry);
							mapEntries[entryCount] = entry;
							mapEntries[entryCount]->col = app->collisions->AddCollider({ pos.x, pos.y , r.w,  r.h }, Collider::Type::INSTANT, wallsEntity);
							mapEntries[entryCount]->id = entryCount;

							entryCount++;
								
						}
					}
				}
			}

				
			
			
		}

		//const char* colProperty = static_cast<const char*>(mapLayerItem->data->properties.GetPropertyChar("Col"));

		//if (colProperty != nullptr) {

		//	LOG("%s", colProperty);
		//	if (colProperty == std::string("wall"))
		//	{

		//		for (int x = 0; x < mapLayerItem->data->width; x++)
		//		{
		//			for (int y = 0; y < mapLayerItem->data->height; y++)
		//			{
		//				//Complete the draw function
		//				int gid = mapLayerItem->data->Get(x, y);

		//				if (gid > 0) {

		//					//L06: TODO 4: Obtain the tile set using GetTilesetFromTileId
		//					//now we always use the firt tileset in the list
		//					TileSet* tileset = mapData.tilesets.start->data;

		//					SDL_Rect r = tileset->GetTileRect(gid);
		//					iPoint pos = MapToWorld(x, y);

		//					mapWalls[i] = app->collisions->AddCollider({ pos.x, pos.y , r.w,  r.h }, Collider::Type::WALL, wallsEntity);
		//					i++;
		//				}
		//			}
		//		}

		//	}
		//}

		mapLayerItem = mapLayerItem->next;
	}
}

void Map::RemoveCol() {

	if (mapLoaded == false) return;

	// Prepare the loop to draw all tilesets + DrawTexture()
	ListItem<MapLayer*>* mapLayerItem;
	mapLayerItem = mapData.layers.start;

	int wallsCount = 0;
	int entryCount = 0;

	while (mapLayerItem != NULL) {

		const char* wallChar = static_cast<const char*>(mapLayerItem->data->properties.GetProperty<const char*>("Col"));
		if (wallChar != nullptr) {


			if (wallChar == std::string("wall")) {

				for (int x = 0; x < mapLayerItem->data->width; x++)
				{
					for (int y = 0; y < mapLayerItem->data->height; y++)
					{
						int gid = mapLayerItem->data->Get(x, y);

						if (gid > 0) {

							TileSet* tileset = mapData.tilesets.start->data;

							SDL_Rect r = tileset->GetTileRect(gid);
							iPoint pos = MapToWorld(x, y);

							if (mapWalls[wallsCount] != nullptr) {

								app->collisions->RemoveCollider(mapWalls[wallsCount]);
								mapWalls[wallsCount] = nullptr;
								wallsCount++;
							}

						}

					}
				}
			}

			if (wallChar == std::string("instant")) {

				for (int x = 0; x < mapLayerItem->data->width; x++)
				{
					for (int y = 0; y < mapLayerItem->data->height; y++)
					{
						int gid = mapLayerItem->data->Get(x, y);

						if (gid > 0) {

							TileSet* tileset = mapData.tilesets.start->data;

							SDL_Rect r = tileset->GetTileRect(gid);
							iPoint pos = MapToWorld(x, y);

							if (mapEntries[entryCount] != nullptr) {

								app->collisions->RemoveCollider(mapEntries[entryCount]->col);
								mapEntries[entryCount] = nullptr;
								entryCount++;
							}

						}

					}
				}
			}
		}

		
		mapLayerItem = mapLayerItem->next;
	}

}

// Called before quitting
bool Map::CleanUp()
{
	LOG("Unloading map");

	RemoveCol();

	app->tex->UnLoad(water);
	app->tex->UnLoad(waterfall);

	app->entities->DestroyEntity(wallsEntity);
	wallsEntity = nullptr;
	delete wallsEntity;

	charValues.clear();

	// Make sure you clean up any memory allocated from tilesets/map
	// Remove all tilesets
	ListItem<TileSet*>* item;
	item = mapData.tilesets.start;

	while (item != NULL)
	{
		app->tex->UnLoad(item->data->texture);
		RELEASE(item->data);
		item = item->next;
	}
	mapData.tilesets.clear();

	// Clean up all layer data
	// Remove all layers
	ListItem<MapLayer*>* item2;
	item2 = mapData.layers.start;

	while (item2 != NULL)
	{
		RELEASE(item2->data);
		item2 = item2->next;
	}
	mapData.layers.clear();

	return true;
}
