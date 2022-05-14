#ifndef __INVENTORY_H__
#define __INVENTORY_H__

#include "Module.h"
#include "GuiButton.h"
#include "Animation.h"

#include "Defs.h"
#include "Log.h"

#include "Item.h"
#include "Equipment.h"
#include "Usable.h"

struct SDL_Texture;

class Character;
class Item;

class Slot {
	SDL_Rect* bounds;
	bool isSelected;
	bool activated;
};

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

	bool OnGuiMouseClickEvent(GuiControl* control);

private:
	SDL_Texture	* inventoryBG,
				* weaponType,
				* selectorItems,
				* selectorCharacters;

	iPoint	selectorItemPos,
			selectorCharsPos;

	bool inventoryOnBattle = false;

	int inventorySlots = 10,
		inventorySpecialSlots = 5;

	// Lists
	List<Item*>* items,
			   * specialItems;

	List<Slot*>  * slots;

	// Assets GUI_buttons
	GuiButton	* backButton,
				* statsButton;

	SDL_Texture	* backButtonTexture,
				* backButtonPressedTexture,
				* statsButtonTexture,
				* statsButtonPressedTexture;

	int buttonSfx, backSfx;
};

#endif // __INVENTORY_H__