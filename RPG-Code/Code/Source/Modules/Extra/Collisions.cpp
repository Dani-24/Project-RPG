#include "Collisions.h"

#include "App.h"

#include "Render.h"
#include "Input.h"
#include "Title.h"
#include "Stages.h"
#include "Module.h"
#include "EntityClasses/Entity.h"

#include "SDL/include/SDL_Scancode.h"

#include "NPC.h"

Collisions::Collisions(App* application, bool start_enabled) : Module(application, start_enabled)
{
	name.Create("collisions");

	for (uint i = 0; i < MAX_COLLIDERS; ++i)
		colliders[i] = nullptr;

	matrix[Collider::Type::PLAYER][Collider::Type::PLAYER] = false;
	matrix[Collider::Type::PLAYER][Collider::Type::WALL] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::INSTANT] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::INTERACT] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::BATTLE] = false;

	matrix[Collider::Type::WALL][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::WALL][Collider::Type::WALL] = false;
	matrix[Collider::Type::WALL][Collider::Type::INSTANT] = false;
	matrix[Collider::Type::WALL][Collider::Type::INTERACT] = false;
	matrix[Collider::Type::WALL][Collider::Type::BATTLE] = false;

	matrix[Collider::Type::INSTANT][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::INSTANT][Collider::Type::WALL] = false;
	matrix[Collider::Type::INSTANT][Collider::Type::INSTANT] = false;
	matrix[Collider::Type::INSTANT][Collider::Type::INTERACT] = false;
	matrix[Collider::Type::INSTANT][Collider::Type::BATTLE] = false;

	matrix[Collider::Type::INTERACT][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::INTERACT][Collider::Type::WALL] = false;
	matrix[Collider::Type::INTERACT][Collider::Type::INSTANT] = false;
	matrix[Collider::Type::INTERACT][Collider::Type::INTERACT] = false;
	matrix[Collider::Type::INTERACT][Collider::Type::BATTLE] = false;

	matrix[Collider::Type::BATTLE][Collider::Type::PLAYER] = false;
	matrix[Collider::Type::BATTLE][Collider::Type::WALL] = false;
	matrix[Collider::Type::BATTLE][Collider::Type::INSTANT] = false;
	matrix[Collider::Type::BATTLE][Collider::Type::INTERACT] = false;
	matrix[Collider::Type::BATTLE][Collider::Type::BATTLE] = true;
}

Collisions::~Collisions()
{
}

bool Collisions::PreUpdate()
{

	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] != nullptr && colliders[i]->pendingToDelete == true)
		{
			delete colliders[i];
			colliders[i] = nullptr;
		}
	}

	Collider* c1;
	Collider* c2;

	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{

		if (colliders[i] == nullptr)
			continue;

		c1 = colliders[i];

		for (uint k = i + 1; k < MAX_COLLIDERS; ++k)
		{

			if (colliders[k] == nullptr)
				continue;

			c2 = colliders[k];

			if (matrix[c1->type][c2->type] && c1->Intersects(c2->rect))
			{
				for (uint i = 0; i < MAX_LISTENERS; ++i)
					if (c1->listeners[i] != nullptr) c1->listeners[i]->OnCollision(c1, c2);

				for (uint i = 0; i < MAX_LISTENERS; ++i)
					if (c2->listeners[i] != nullptr) c2->listeners[i]->OnCollision(c2, c1);
			}
		}
	}
	return true;
}

bool Collisions::Update(float dt)
{
	if (app->input->GetKey(SDL_SCANCODE_F9) == KEY_DOWN) {
		debug==true? debug = false: debug = true;
		int u = 9;
	}
	
	//debug ? LOG("DEBUG ACTIVADO") : LOG("DEBUG DESACTIVADO");
	return true;
}

bool Collisions::PostUpdate()
{
	if (debug) {
		DebugDraw();
	}

	return true;
}

void Collisions::DebugDraw()
{
	Uint8 alpha = 80;
	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		int t = 8;
		if (colliders[i] == nullptr) {
			continue;
		}
			
		if (app->stages->actualStage != StageIndex::NONE) {

			switch (colliders[i]->type)
			{
			case Collider::Type::NONE: // white
				app->render->DrawRectangle(colliders[i]->rect, 255, 255, 255, alpha);
				break;

			case Collider::Type::PLAYER: // blue
				app->render->DrawRectangle(colliders[i]->rect, 0, 0, 255, alpha);
				break;
			case Collider::Type::WALL: // green
				app->render->DrawRectangle(colliders[i]->rect, 0, 255, 0, alpha);
				break;

			case Collider::Type::INSTANT: // yellow
				app->render->DrawRectangle(colliders[i]->rect, 255, 255, 0, alpha);
				break;
			case Collider::Type::INTERACT: // red

				// Only print interaction colliders if they are activated
				if (app->stages->npcListPtr != nullptr) {

					for (ListItem<NPC*>* npcInList = app->stages->npcListPtr->start; npcInList != NULL; npcInList = npcInList->next)
					{
						if (npcInList->data->activeOnStage == app->stages->actualStage && app->stages->playerPtr != nullptr) {
							if(colliders[i] == npcInList->data->GetCollider())
							app->render->DrawRectangle(colliders[i]->rect, 255, 0, 0, alpha);
						}
					}
				}

				break;

			case Collider::Type::BATTLE: // light yellow
				app->render->DrawRectangle(colliders[i]->rect, 150, 150, 0, alpha);
				break;
			
			default:
				app->render->DrawRectangle(colliders[i]->rect, 255, 255, 255, alpha);
				break;
			}
		}
	}
}

bool Collisions::CleanUp()
{
	//LOG("Freeing all colliders");

	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] != nullptr)
		{
			delete colliders[i];
			colliders[i] = nullptr;
		}
	}

	return true;
}

Collider* Collisions::AddCollider(SDL_Rect rect, Collider::Type type, Entity* listener)
{
	Collider* ret = nullptr;

	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] == nullptr)
		{
			ret = colliders[i] = new Collider(rect, type, listener);
			break;
		}
	}
	return ret;
}

void Collisions::RemoveCollider(Collider* collider)
{
	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] == collider)
		{
			delete colliders[i];
			colliders[i] = nullptr;
		}
	}
}