#include "Collider.h"

Collider::Collider(SDL_Rect rectangle, Type type, Entity* listener) : rect(rectangle), type(type)
{
	listeners[0] = listener;
}

void Collider::SetPos(int x, int y)
{
	rect.x = x;
	rect.y = y;
}

bool Collider::Intersects(const SDL_Rect& r) const
{
	return (rect.x < r.x + r.w &&
		rect.x + rect.w > r.x &&
		rect.y < r.y + r.h &&
		rect.h + rect.y > r.y);
}

void Collider::AddListener(Entity* listener)
{
	for (int i = 0; i < MAX_LISTENERS; ++i)
	{
		if (listeners[i] == nullptr)
		{
			listeners[i] = listener;
			break;
		}

		else if (listeners[i] == listener)
			break;
	}
}