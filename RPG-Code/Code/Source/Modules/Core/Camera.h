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
	
	iPoint GetPos();

	// Limit camera movement when following a target
	void SetLimits(int x, int y, int w, int h);
	void FreeLimits();

	// Follow target with delay
	void FollowTarget();

	// Camera centered on target
	void OnTarget();

	// Set & release target
	bool SetTarget(Entity* target);
	void ReleaseTarget();

private:
	// Load / Save
	bool LoadState(pugi::xml_node&);
	bool SaveState(pugi::xml_node&) const;

	
private:

	// Camera variables
	SDL_Rect cam;

	iPoint camOffset;
	
	// Camera limits
	int limitX, limitY, limitW, limitH;
	bool camLimited = false;

	// Target variables
	Entity* target = nullptr;
	iPoint targetPos;

	iPoint distance;
};

#endif // !__CAMERA_H__