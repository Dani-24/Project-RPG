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

	bool OnGuiMouseClickEvent(GuiControl* control);

private:
	SDL_Texture	* inventoryBG,
				* weaponType;

	bool inventoryOnBattle = false;

	int InventorySlots = 10,
		InventorySpecialSlots = 5,
		CharacterSlots = 4,
		selectedSlot = 1,
		selectedCharSlot = 1;

	// Lists
	List<Character*>* charactersOnUI;
	List<Item*>* itemsOnUI;

	// Assets GUI_buttons
	GuiButton	* backButton,
				* statsButton;

	SDL_Texture	* backButtonTexture,
				* backButtonPressedTexture,
				* statsButtonTexture,
				* statsButtonPressedTexture;

	List<GuiButton*>* itemsButtons,
					* specialItemsButtons,
					* charactersButtons;

	int buttonsIDCount = 300;

	int buttonSfx, backSfx;
};

#endif // __INVENTORY_H__