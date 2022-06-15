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
#include "EasingFunctions.h"

#include "List.h"
#include "Point.h"

struct SDL_Texture;
struct I_Pos
{
	iPoint Position;
};

class Character;
class Item;

class Slot {
public:
	Slot(iPoint position, iPoint size, Item* asignedItem = nullptr, bool isEquipment = false, bool isSpecial = false) {
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
			isEquipment,
			isSpecial;

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

	float EaseInBetweenPoints(iPoint posA, iPoint posB);

	float EaseOutBetweenPoints(iPoint posA, iPoint posB);

	bool OnGuiMouseClickEvent(GuiControl* control);

	void AddStats(Character* character, Usable* item);

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

public:

	int inventorySlots = 15;

private:

	bool inventoryOnBattle = false;
	// List Slots

	List<Slot*> slots;

	// anim

	I_Pos I_pos;

	iPoint I_pointA;
	iPoint I_pointB;

	int I_iterations;
	int I_total_iterations;
	bool I_easing_active;
	EasingFunctions I_Efunction;

	I_Pos I_pos_out;

	iPoint I_pointA_out;
	iPoint I_pointB_out;

	int I_iterations_out;
	int I_total_iterations_out;
	bool I_easing_active_out;

	// Assets GUI_buttons
	GuiButton	* backButton,
				* statsButton,
				* itemUseButton,
				* itemBackButon,
				* itemInfoButton,
				* itemInfoCloseButton;

	SDL_Texture	* backButtonTexture,
				* backButtonPressedTexture,
				* statsButtonTexture,
				* statsButtonPressedTexture;

	int buttonSfx, backSfx, moveSfx, useSfx;
};

#endif // __INVENTORY_H__