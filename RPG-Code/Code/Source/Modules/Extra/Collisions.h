#ifndef __COLLISIONS_H__
#define __COLLISIONS_H__

#define MAX_COLLIDERS 5000

#include "Module.h"
#include "Collider.h"

class Collisions : public Module
{
public:

	Collisions(App* application, bool start_enabled = true);

	virtual ~Collisions();

	bool PreUpdate();

	bool Update(float dt);

	bool PostUpdate();
	bool CleanUp();
	Collider* AddCollider(SDL_Rect rect, Collider::Type type, Entity* listener = nullptr);
	void RemoveCollider(Collider* collider);
	void DebugDraw();

private:

	Collider* colliders[MAX_COLLIDERS] = { nullptr };
	bool matrix[Collider::Type::MAX][Collider::Type::MAX];
	bool debug = false;
};

#endif // _COLLISIONS_H__
