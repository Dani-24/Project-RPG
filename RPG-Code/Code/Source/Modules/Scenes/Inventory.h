#ifndef __INVENTORY_H__
#define __INVENTORY_H__

#include "Module.h"
#include "GuiButton.h"
#include "Animation.h"

#include "Defs.h"
#include "Log.h"

struct SDL_Texture;

class Character;
class Item;

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

private:
	SDL_Texture* inventoryBG;

	bool inventoryOnBattle = false;

	int InventorySlots = 10;
	int InventorySpecialSlots = 5;
	int CharacterSlots = 4;

	int selectedSlot = 1;
	int selectedCharSlot = 1;

	// Lists
	List<Character*>* charactersOnUI;
	List<Item*>* itemsOnUI;

};

#endif // __INVENTORY_H__