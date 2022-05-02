#ifndef __INVENTORY_H__
#define __INVENTORY_H__

#include "Module.h"
#include "GuiButton.h"
#include "Animation.h"

struct SDL_Texture;

class Inventory : public Module
{
public:

	Inventory(App* application, bool start_enabled = true);
	virtual ~Inventory();

	bool Awake(pugi::xml_node& config);

	bool Start();

	bool PreUpdate();

	bool Update(float dt);

	bool PostUpdate();

	bool CleanUp();

public:

};

#endif // __INVENTORY_H__