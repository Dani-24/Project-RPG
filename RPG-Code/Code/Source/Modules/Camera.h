#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "Module.h"
#include "Point.h"
#include "SDL/include/SDL.h"

#include "EntityClasses/Entity.h"

class Entity;

class Camera : public Module
{
public:

	Camera(App* application, bool start_enabled = true);
	virtual ~Camera();

	bool Awake(pugi::xml_node&);
	bool Start();

	bool Update(float dt);

	bool CleanUp();

public:

	// If there is no target use this
	void SetPos(iPoint position);

	// Follow target with delay
	void FollowTarget(float dt);

	// Camera centered on target
	void OnTarget();

	// Set & release target
	bool SetTarget(Entity* target);
	void ReleaseTarget();

	// Load / Save
	bool LoadState(pugi::xml_node&);
	bool SaveState(pugi::xml_node&) const;

public:

	// Camera variables
	SDL_Rect cam;
	iPoint camOffset;
	int speed = 1;
	int speedDelay = 1;

	Entity* target = nullptr;
};

#endif // !__CAMERA_H__