#ifndef __BATTLE_H__
#define __BATTLE_H__

#include "Module.h"
#include "GuiButton.h"
#include "Animation.h"
#include "Stages.h"
#include "Party.h"

struct SDL_Texture;
class Player;
class DynamicEntity;
class Items;
class Usable;

enum class StageIndex;
enum class PartyType;

#define BUTTONS_SPACE_HOR 10
#define BUTTONS_BOTTOM_SPACE 50
#define BUTTONS_W 74
#define BUTTONS_H 32
#define NUM_BUTTONS 4
#define LATERAL_MOVE 25

#define LIFE_DISTANCE_HOR 120
#define LIFE_DISTANCE 25

#define BACK_HEIGH 100
#define INFO_SPACE_X 20
#define INFO_SPACE_Y 200

#define TEXT_INFO_X 150
#define TEXT_INFO_Y 110
#define SEPARATION 10
#define BIG_SEPARATION 17

enum class BattlePhase {

	THINKING,
	SELECTING,
	CHOOSE_ATTACK,

	ATTACKING,
	DEFENDING,
	USING_ITEM,
	ESCAPING,

	SPECIAL,

	OUTCOME,

	REWARD,
	LOOT,

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

	void skillsup();

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

	//manage the control of ui with keyboard/gamepad
	void GampadControl();

private:
	List<GuiButton*> think;
	ListItem<GuiButton*>* t ;


	List<GuiButton*> selCH;
	List<GuiButton*>* CH;

	List<GuiButton*> selVL;
	ListItem<GuiButton*>* VL;

	List<GuiButton*> selRAY;
	ListItem<GuiButton*>* RAY;

	List<GuiButton*> selDH;
	ListItem<GuiButton*>* DH;


	List<GuiButton*> choos;


	bool _wait, wait;

	

	int uplimSL , dowlimSL = 0;

	bool p3, p6, p10,
		v3, v6, v10,
		v;


	int TK, SL, CA;
	SDL_Texture* playerBattleSprite;
	Animation playerBattleAnimation;

	SDL_Texture* townBackground, * dojoBackground;
	Animation dojoAnim;

public:
	bool gamepad1 = false, gamepad2 = false, gamepad3 = false;

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

	//Back
	GuiButton* backButton; // back button

	//Thinking
	GuiButton* attackButton; // attack button
	GuiButton* defenseButton; // defense button
	GuiButton* itemButton; // item button
	GuiButton* escapeButton; // escape button

	//Choose attack
	GuiButton* normalAttackButton; 

	GuiButton* playerSpecialButton1; 
	GuiButton* playerSpecialButton2; 
	GuiButton* playerSpecialButton3; 

	GuiButton* valionSpecialButton1; 
	GuiButton* valionSpecialButton2; 
	GuiButton* valionSpecialButton3; 

	GuiButton* raylaSpecialButton1; 
	GuiButton* raylaSpecialButton2; 
	GuiButton* raylaSpecialButton3; 

	GuiButton* dhionSpecialButton1; 
	GuiButton* dhionSpecialButton2; 
	GuiButton* dhionSpecialButton3; 

	//Selecting
	GuiButton* enemyButton1; // enemy 1 button
	GuiButton* enemyButton2; // enemy 2 button
	GuiButton* enemyButton3; // enemy 3 button
	GuiButton* enemyButton4; // enemy 4 button

	//Button textures

	//Thinking

	SDL_Texture* backButtonTex;
	SDL_Texture* attackTex;
	SDL_Texture* defenseTex;
	SDL_Texture* itemsTex;
	SDL_Texture* escapeTex;

	//Choose attack
	SDL_Texture* normalAttackButtonTex;

	SDL_Texture* playerSpecialButton1Tex;
	SDL_Texture* playerSpecialButton2Tex;
	SDL_Texture* playerSpecialButton3Tex;

	SDL_Texture* valionSpecialButton1Tex;
	SDL_Texture* valionSpecialButton2Tex;
	SDL_Texture* valionSpecialButton3Tex;

	SDL_Texture* raylaSpecialButton1Tex;
	SDL_Texture* raylaSpecialButton2Tex;
	SDL_Texture* raylaSpecialButton3Tex;

	SDL_Texture* dhionSpecialButton1Tex;
	SDL_Texture* dhionSpecialButton2Tex;
	SDL_Texture* dhionSpecialButton3Tex;

	//Selecting
	SDL_Texture* batButtonTex;
	SDL_Texture* flyingEyeButtonTex;
	SDL_Texture* skeletonButtonTex;


	//Button pressed textures

	//Thinking
	SDL_Texture* press_backTex;
	SDL_Texture* press_attackTex;
	SDL_Texture* press_defenseTex;
	SDL_Texture* press_itemsTex;
	SDL_Texture* press_escapeTex;

	//Choose attack
	SDL_Texture* press_normalAttackButtonTex;

	SDL_Texture* press_playerSpecialButton1Tex;
	SDL_Texture* press_playerSpecialButton2Tex;
	SDL_Texture* press_playerSpecialButton3Tex;

	SDL_Texture* press_valionSpecialButton1Tex;
	SDL_Texture* press_valionSpecialButton2Tex;
	SDL_Texture* press_valionSpecialButton3Tex;

	SDL_Texture* press_raylaSpecialButton1Tex;
	SDL_Texture* press_raylaSpecialButton2Tex;
	SDL_Texture* press_raylaSpecialButton3Tex;

	SDL_Texture* press_dhionSpecialButton1Tex;
	SDL_Texture* press_dhionSpecialButton2Tex;
	SDL_Texture* press_dhionSpecialButton3Tex;

	//Selecting
	SDL_Texture* press_batButtonTex;
	SDL_Texture* press_flyingEyeButtonTex;
	SDL_Texture* press_skeletonButtonTex;


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
	char lootChar[100] = { "\0" };
	char rewardChar[150] = { "\0" };

	char playerLifeChar[50] = { "\0" };
	char enemyLifeChar[50] = { "\0" };

	char enemyName1[50] = { "\0" };
	char enemyName2[50] = { "\0" };
	char enemyName3[50] = { "\0" };
	char enemyName4[50] = { "\0" };

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

	//sfx
	int startFx;

	int explosionfx;

	int goldCount;
	int expCount;

	Usable* itemCount[4];

	int skill;
	int selectCount;
	int selectTime;

	int selectedTime;

	float localdt;

	//SKILLS
		
	SDL_Texture* FlechaS_EspadaS_EscudoS = nullptr;
	SDL_Texture* FlechaS = nullptr;
	SDL_Texture* FlechaAcido = nullptr;
	SDL_Texture* Cataclismo = nullptr;
	SDL_Texture* Ciervo = nullptr;
	SDL_Texture* FlechaT = nullptr;
	SDL_Texture* TripleL = nullptr;
	SDL_Texture* Juicio = nullptr;
	SDL_Texture* Pedrada = nullptr;
	SDL_Texture* HalconElectro = nullptr;
	SDL_Texture* AquaE = nullptr;


	Animation 
		
		EscudoS_a, 
		EspadaS_a,
		AquaE_a,

		Pedrada_a,
		Cataclismo_a,
		Ciervo_a,

		FlechaT_a,
		FlechaAcido_a,
		FlechaS_a,

		Juicio_a,
		HalconElectro_a,
		TripleL_a;

	bool castSkill;

};

#endif // __BATTLE_H__