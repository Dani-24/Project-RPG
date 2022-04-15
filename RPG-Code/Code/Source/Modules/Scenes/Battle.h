#ifndef __BATTLE_H__
#define __BATTLE_H__

#include "Module.h"
#include "GuiButton.h"
#include "Animation.h"
#include "Stages.h"

struct SDL_Texture;
class Player;
class DynamicEntity;

enum class StageIndex;

class Battle : public Module
{
public:

	Battle(App* application, bool start_enabled = true);

	// Destructor
	virtual ~Battle();

	// Called before render is available
	bool Awake();

	// Called before the first frame
	bool Start();

	// Called before all Updates
	bool PreUpdate();

	// Called each loop iteration
	bool Update(float dt);

	// Called before all Updates
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

	// Define multiple Gui Event methods
	bool OnGuiMouseClickEvent(GuiControl* control);

private:

	SDL_Texture* playerBattleSprite;
	Animation playerBattleAnimation;

	SDL_Texture* townBattleBackground;

public:

	StageIndex  * battleStage;

	bool battlePause;

	Player* player = nullptr;

	DynamicEntity* actualTurn;

	DynamicEntity* entitiesInBattle[8];

	//Buttons

	GuiButton* attackButton; // attack button
	GuiButton* defenseButton; // defense button
	GuiButton* itemButton; // item button
	GuiButton* escapeButton; // escape button

	char battleTurnChar[3] = { "\0" };

	int battleTurn;
	
};

#endif // __BATTLE_H__