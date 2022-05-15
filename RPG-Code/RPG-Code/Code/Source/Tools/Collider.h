#ifndef __COLLIDER_H__
#define __COLLIDER_H__

#include "SDL/include/SDL_Rect.h"

#define MAX_LISTENERS 10

class Entity;

struct Collider
{
	enum Type
	{
		NONE = -1,
		PLAYER,
		WALL,
		INSTANT,
		INTERACT,
		BATTLE,

		MAX
	};


	Collider(SDL_Rect rectangle, Type type, Entity* listener = nullptr);

	void SetPos(int x, int y);
	bool Intersects(const SDL_Rect& r) const;
	void AddListener(Entity* listener);

	SDL_Rect rect;
	bool pendingToDelete = false;
	Type type;
	Entity* listeners[MAX_LISTENERS] = { nullptr };
};


#endif // !__COLLIDER_H__

