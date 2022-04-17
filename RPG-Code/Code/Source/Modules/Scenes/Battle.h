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

enum class BattlePhase {

	THINKING,
	SELECTING,

	ATTACKING,
	DEFENDING,
	USING_ITEM,
	ESCAPING,

	WIN,
	LOSE

};

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

	void SetTurnOrder();

	void Attack(DynamicEntity target);

	void Defense();

	void UseItem(DynamicEntity target);

	bool Escape();

	int CountAllies();

	int CountEnemies();

	void CheckWinLose();

private:

	SDL_Texture* playerBattleSprite;
	Animation playerBattleAnimation;

	SDL_Texture* townBattleBackground;

public:

	BattlePhase battlePhase;

	StageIndex  * battleStage;

	bool battlePause;

	Player* player = nullptr;

	DynamicEntity* actualTurnEntity;

	DynamicEntity* entitiesInBattle[8];

	//Buttons

	GuiButton* attackButton; // attack button
	GuiButton* defenseButton; // defense button
	GuiButton* itemButton; // item button
	GuiButton* escapeButton; // escape button

	int battleTurn;
	char battleTurnChar[9] = { "\0" };

	float TurnValue;
	char turnValueChar[20] = { "\0" };

	char nameChar[50] = { "\0" };

	char playerLifeChar[50] = { "\0" };
	char enemyLifeChar[50] = { "\0" };


	bool someoneAttacking;
	bool someoneDefending;
	bool itsPlayerTurn;
	
	int cont;
	int attackTime;
	int defenseTime;
	int itemTime;
	int escapeTime;

	int winTime;
	int loseTime;

	bool gameOver;

	bool canSelect;

	int alliesCount;
	int enemiesCount;

	bool hasStarted;

	bool hasTriedToEscape;
	bool canEscape;

	bool defenseBuffed;

	int defenseBuff;

	int optionPercent;
	
};

#endif // __BATTLE_H__