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
	OUTCOME,

	ATTACKING,
	DEFENDING,
	USING_ITEM,
	ESCAPING,

	WIN,
	LOSE

};

enum class EnemyInBattleType {
	NORMAL,
	BOSS
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

	void Attack(DynamicEntity* target);

	void Defense();

	void UseItem(DynamicEntity target);

	bool Escape();

	int CountAllies();

	int CountEnemies();

	//return true if has win or lost
	bool CheckWinLose();

	void ChangePhase(BattlePhase state);

private:

	SDL_Texture* playerBattleSprite;
	Animation playerBattleAnimation;

	SDL_Texture* townBackground, * dojoBackground;
	Animation dojoAnim;

public:

	BattlePhase battlePhase;

	StageIndex  * battleStage;

	bool battlePause;

	Player* player = nullptr;

	DynamicEntity* actualTurnEntity;
	DynamicEntity* turnsTimeLine[5];
	DynamicEntity* targetEntity;

	DynamicEntity* entitiesInBattle[8];

	NormalEnemy* normalEnemyInBattle;

	EnemyInBattleType CurrentEnemyType;

	//Buttons

	GuiButton* attackButton; // attack button
	GuiButton* defenseButton; // defense button
	GuiButton* itemButton; // item button
	GuiButton* escapeButton; // escape button

	GuiButton* enemyButton1; // enemy 1 button
	GuiButton* enemyButton2; // enemy 2 button
	GuiButton* enemyButton3; // enemy 3 button
	GuiButton* enemyButton4; // enemy 4 button

	SDL_Texture* attackTex;
	SDL_Texture* defenseTex;
	SDL_Texture* itemsTex;
	SDL_Texture* escapeTex;

	SDL_Texture* batButton;
	SDL_Texture* flyingEyeButton;
	SDL_Texture* skeletonButton;

	SDL_Texture* press_attackTex;
	SDL_Texture* press_defenseTex;
	SDL_Texture* press_itemsTex;
	SDL_Texture* press_escapeTex;

	SDL_Texture* press_batButton;
	SDL_Texture* press_flyingEyeButton;
	SDL_Texture* press_skeletonButton;

	SDL_Texture* shield;

	int battleTurn;
	char battleTurnChar[9] = { "\0" };

	char battleInfoChar[50] = {"\0"};

	float turnValue;
	char turnValueChar[20] = { "\0" };

	char nameChar[100] = { "\0" };
	char damageChar[100] = { "\0" };
	char lifeChar[100] = { "\0" };
	char escapeChar[100] = { "\0" };
	char actualTurnChar[50] = { "\0" };

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
	int outcomeTime;

	bool gameOver;

	bool canSelect;

	int alliesCount;
	int enemiesCount;

	bool hasStarted;

	bool hasTriedToEscape;
	bool canEscape;

	//bool defenseBuffed;

	int defenseBuff;

	int optionPercent;

	bool hasToShake;
	int shakePos;
	int changeSide;

	int shakeTime;
	int shakeForce;

	int damageTaken;

	bool hasChangedPhase;


	int startFx;
};

#endif // __BATTLE_H__