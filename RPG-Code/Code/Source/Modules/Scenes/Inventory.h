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

#include "List.h"
#include "Point.h"

struct SDL_Texture;

class Character;
class Item;

class Slot {
public:
	Slot(iPoint position, iPoint size, Item* asignedItem = nullptr, bool isEquipment = false) {
		this->position = position;
		this->size = size;

		if (isEquipment) {
			this->isItem = false;
		}
		else {
			this->isItem = true;
		}
		this->isEquipment = isEquipment;
		this->isCharacter = false;

		this->asignedItem = asignedItem;
		this->asignedCharacter = nullptr;
	}
	Slot(iPoint position, iPoint size, Character* asignedCharacter = nullptr) {
		this->position = position;
		this->size = size;
		this->isItem = false;
		this->isCharacter = true;
		this->isEquipment = false;

		this->asignedItem = nullptr;
		this->asignedCharacter = asignedCharacter;
	}
public:
	iPoint	position,
			size;

	bool	isSelected = false,
			activated = false;

	bool	isItem,
			isCharacter,
			isEquipment;

	Item* asignedItem;
	Character* asignedCharacter;
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
				* selectorCharacters,
				* itemInfo;

	iPoint	selectorItemPos,
			selectorCharsPos,
			// for sfx:
			lastItemPos, 
			lastCharPos;

	bool inventoryOnBattle = false;

	int inventorySlots = 10,
		inventorySpecialSlots = 5;

	// Lists
	List<Item*>* items,
			   * specialItems;

	List<Slot*> slots;

	// Assets GUI_buttons
	GuiButton	* backButton,
				* statsButton;

	SDL_Texture	* backButtonTexture,
				* backButtonPressedTexture,
				* statsButtonTexture,
				* statsButtonPressedTexture;

	int buttonSfx, backSfx, moveSfx;
};

#endif // __INVENTORY_H__