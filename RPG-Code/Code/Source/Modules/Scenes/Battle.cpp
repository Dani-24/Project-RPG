#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "Scene.h"
#include "Map.h"
#include "GuiManager.h"
#include "FadeToBlack.h"
#include "Player.h"
#include "EntityManager.h"
#include "Battle.h"
#include "Camera.h"
#include "ModuleQFonts.h"
#include "Title.h"
#include "Inventory.h"
#include "Configuration.h"
#include "Item.h"
#include "Usable.h"
#include "Equipment.h"

#include <time.h>

#include "Defs.h"
#include "Log.h"

Battle::Battle(App* application, bool start_enabled) : Module(application, start_enabled)
{

	//SKILLS
	//______________________________
	EscudoS_a.PushBack({ 563,771,60,85});
	EscudoS_a.PushBack({ 733,771,60,85 });
	EscudoS_a.PushBack({ 903,771,60,85 });

	EscudoS_a.PushBack({ 1073,771,60,85 });
	EscudoS_a.PushBack({ 1243,771,60,85 });
	EscudoS_a.PushBack({ 1413,771,60,85 });

	EscudoS_a.PushBack({ 1583,771,60,85 });
	EscudoS_a.PushBack({ 54,913,60,85 });
	EscudoS_a.PushBack({ 223,913,60,85 });

	EscudoS_a.PushBack({ 180 * 100,180 * 100,180,180 });
	EscudoS_a.loop = false;
	EscudoS_a.speed = 0.015f;
	//_____________________________
	EspadaS_a.PushBack({ 563,422,60,142 });
	EspadaS_a.PushBack({ 733,422,60,142 });
	EspadaS_a.PushBack({ 903,422,60,142 });
	EspadaS_a.PushBack({ 1073,422,60,142 });
	EspadaS_a.PushBack({ 1243,422,60,142 });
	EspadaS_a.PushBack({ 1413,422,60,142 });
	EspadaS_a.PushBack({ 1583,422,60,142 });

	EspadaS_a.PushBack({ 54,565,60,142 });
	EspadaS_a.PushBack({ 223,565,60,142 });
	EspadaS_a.PushBack({ 393,565,60,142 });
	EspadaS_a.PushBack({ 563,565,60,142 });
	EspadaS_a.PushBack({ 733,565,60,142 });
	EspadaS_a.PushBack({ 903,565,60,142 });
	EspadaS_a.PushBack({ 1073,565,60,142 });
	EspadaS_a.PushBack({ 1243,565,60,142 });
	EspadaS_a.PushBack({ 1413,565,60,142 }); 
	EspadaS_a.PushBack({ 1583,565,60,142 });

	EspadaS_a.PushBack({ 54,708,60,142 });
	EspadaS_a.PushBack({ 223,708,60,142 });

	EspadaS_a.PushBack({ 180 * 100,180 * 100,180,180 });
	EspadaS_a.loop = false;
	EspadaS_a.speed = 0.015f;
	//_____________________________
	AquaE_a.PushBack({ 64 * 0,80 * 0,64,80 });
	AquaE_a.PushBack({ 64 * 1,80 * 0,64,80 });
	AquaE_a.PushBack({ 64 * 2,80 * 0,64,80 });
	AquaE_a.PushBack({ 64 * 3,80 * 0,64,80 });
	AquaE_a.PushBack({ 64 * 4,80 * 0,64,80 });

	AquaE_a.PushBack({ 64 * 0,80 * 1,64,80 });
	AquaE_a.PushBack({ 64 * 1,80 * 1,64,80 });
	AquaE_a.PushBack({ 64 * 2,80 * 1,64,80 });
	AquaE_a.PushBack({ 64 * 3,80 * 1,64,80 });
	AquaE_a.PushBack({ 64 * 4,80 * 1,64,80 });

	AquaE_a.PushBack({ 64 * 0,80 * 2,64,80 });
	AquaE_a.PushBack({ 64 * 1,80 * 2,64,80 });
	AquaE_a.PushBack({ 64 * 2,80 * 2,64,80 });
	AquaE_a.PushBack({ 64 * 3,80 * 2,64,80 });
	AquaE_a.PushBack({ 64 * 4,80 * 2,64,80 });

	AquaE_a.PushBack({ 180 * 100,180 * 100,180,180 });
	AquaE_a.loop = false;
	AquaE_a.speed = 0.015f;
	//_____________
	//_____________
	Pedrada_a.PushBack({ 48 * 0,48 * 0,48,48 });
	Pedrada_a.PushBack({ 48 * 1,48 * 0,48,48 });
	Pedrada_a.PushBack({ 48 * 2,48 * 0,48,48 });
	Pedrada_a.PushBack({ 48 * 3,48 * 0,48,48 });
	Pedrada_a.PushBack({ 48 * 4,48 * 0,48,48 });
	Pedrada_a.PushBack({ 48 * 5,48 * 0,48,48 });

	Pedrada_a.PushBack({ 48 * 0,48 * 1,48,48 });
	Pedrada_a.PushBack({ 48 * 1,48 * 1,48,48 });
	Pedrada_a.PushBack({ 48 * 2,48 * 1,48,48 });
	Pedrada_a.PushBack({ 48 * 3,48 * 1,48,48 });
	Pedrada_a.PushBack({ 48 * 4,48 * 1,48,48 });
	Pedrada_a.PushBack({ 48 * 5,48 * 1,48,48 });

	Pedrada_a.PushBack({ 180 * 100,180 * 100,180,180 });
	Pedrada_a.loop = false;
	Pedrada_a.speed = 0.015f;
	//_____________________________
	Cataclismo_a.PushBack({ 250 * 0,250 * 0,250,250 });
	Cataclismo_a.PushBack({ 250 * 1,250 * 0,250,250 });
	Cataclismo_a.PushBack({ 250 * 2,250 * 0,250,250 });
	Cataclismo_a.PushBack({ 250 * 3,250 * 0,250,250 });
	Cataclismo_a.PushBack({ 250 * 4,250 * 0,250,250 });
	Cataclismo_a.PushBack({ 250 * 5,250 * 0,250,250 });

	Cataclismo_a.PushBack({ 250 * 0,250 * 1,250,250 });
	Cataclismo_a.PushBack({ 250 * 1,250 * 1,250,250 });
	Cataclismo_a.PushBack({ 250 * 2,250 * 1,250,250 });
	Cataclismo_a.PushBack({ 250 * 3,250 * 1,250,250 });
	Cataclismo_a.PushBack({ 250 * 4,250 * 1,250,250 });
	Cataclismo_a.PushBack({ 250 * 5,250 * 1,250,250 });

	Cataclismo_a.PushBack({ 250 * 0,250 * 2,250,250 });
	Cataclismo_a.PushBack({ 250 * 1,250 * 2,250,250 });
	Cataclismo_a.PushBack({ 250 * 2,250 * 2,250,250 });
	Cataclismo_a.PushBack({ 250 * 3,250 * 2,250,250 });
	Cataclismo_a.PushBack({ 250 * 4,250 * 2,250,250 });
	Cataclismo_a.PushBack({ 250 * 5,250 * 2,250,250 });

	Cataclismo_a.PushBack({ 250 * 0,250 * 3,250,250 });
	Cataclismo_a.PushBack({ 250 * 1,250 * 3,250,250 });

	Cataclismo_a.PushBack({ 180 * 100,180 * 100,180,180 });
	Cataclismo_a.loop = false;
	Cataclismo_a.speed = 0.015f;
	//_____________________________
	Ciervo_a.PushBack({ 45,1141,108,108 });//vacio
	Ciervo_a.PushBack({ 178,1141,108,108 });
	Ciervo_a.PushBack({ 332,1141,108,108 });
	Ciervo_a.PushBack({ 492,1141,108,108 });
	Ciervo_a.PushBack({ 648,1141,108,108 });
	Ciervo_a.PushBack({ 802,1141,108,108 });
	Ciervo_a.PushBack({ 956,1141,108,108 });
	Ciervo_a.PushBack({ 1111,1141,108,108 });
	Ciervo_a.PushBack({ 1269,1141,108,108 });
	Ciervo_a.PushBack({ 1425,1141,108,108 });

	Ciervo_a.PushBack({ 21,1245,60,142 });
	Ciervo_a.PushBack({ 177,1245,60,142 });

	Ciervo_a.PushBack({ 180 * 100,180 * 100,180,180 });
	Ciervo_a.loop = false;
	Ciervo_a .speed = 0.015f;
	//_____________
	//_____________
	FlechaT_a.PushBack({ 180 * 0,180 * 0,180,180 });
	FlechaT_a.PushBack({ 180 * 1,180 * 0,180,180 });
	FlechaT_a.PushBack({ 180 * 2,180 * 0,180,180 });
	FlechaT_a.PushBack({ 180 * 3,180 * 0,180,180 });
	FlechaT_a.PushBack({ 180 * 4,180 * 0,180,180 });
	FlechaT_a.PushBack({ 180 * 5,180 * 0,180,180 });
	FlechaT_a.PushBack({ 180 * 6,180 * 0,180,180 });
	FlechaT_a.PushBack({ 180 * 7,180 * 0,180,180 });
	FlechaT_a.PushBack({ 180 * 8,180 * 0,180,180 });
	FlechaT_a.PushBack({ 180 * 9,180 * 0,180,180 });

	FlechaT_a.PushBack({ 180 * 10,180 * 0,180,180 });
	FlechaT_a.PushBack({ 180 * 11,180 * 0,180,180 });
	FlechaT_a.PushBack({ 180 * 12,180 * 0,180,180 });
	FlechaT_a.PushBack({ 180 * 13,180 * 0,180,180 });
	FlechaT_a.PushBack({ 180 * 14,180 * 0,180,180 });
	FlechaT_a.PushBack({ 180 * 15,180 * 0,180,180 });
	FlechaT_a.PushBack({ 180 * 16,180 * 0,180,180 });
	FlechaT_a.PushBack({ 180 * 17,180 * 0,180,180 });

	FlechaT_a.PushBack({ 180 * 100,180 * 100,180,180 });
	FlechaT_a.loop = false;
	FlechaT_a.speed = 0.02f;
	//_____________________________
	FlechaAcido_a.PushBack({ 180 * 0,180 * 0,180,180 });
	FlechaAcido_a.PushBack({ 180 * 1,180 * 0,180,180 });
	FlechaAcido_a.PushBack({ 180 * 2,180 * 0,180,180 });
	FlechaAcido_a.PushBack({ 180 * 3,180 * 0,180,180 });
	FlechaAcido_a.PushBack({ 180 * 4,180 * 0,180,180 });
	FlechaAcido_a.PushBack({ 180 * 5,180 * 0,180,180 });
	FlechaAcido_a.PushBack({ 180 * 6,180 * 0,180,180 });
	FlechaAcido_a.PushBack({ 180 * 7,180 * 0,180,180 });
	FlechaAcido_a.PushBack({ 180 * 8,180 * 0,180,180 });
	FlechaAcido_a.PushBack({ 180 * 9,180 * 0,180,180 });

	FlechaAcido_a.PushBack({ 180 * 10,180 * 1,180,180 });

	FlechaAcido_a.PushBack({ 180 * 100,180 * 100,180,180 });
	FlechaAcido_a.loop = false;
	FlechaAcido_a.speed = 0.015f;
	//_____________________________
	FlechaS_a.PushBack({ 180 * 0,180 * 0,180,180 });
	FlechaS_a.PushBack({ 180 * 1,180 * 0,180,180 });
	FlechaS_a.PushBack({ 180 * 2,180 * 0,180,180 });
	FlechaS_a.PushBack({ 180 * 3,180 * 0,180,180 });
	FlechaS_a.PushBack({ 180 * 4,180 * 0,180,180 });
	FlechaS_a.PushBack({ 180 * 5,180 * 0,180,180 });
	FlechaS_a.PushBack({ 180 * 6,180 * 0,180,180 });
	FlechaS_a.PushBack({ 180 * 7,180 * 0,180,180 });
	FlechaS_a.PushBack({ 180 * 8,180 * 0,180,180 });
	FlechaS_a.PushBack({ 180 * 9,180 * 0,180,180 });

	FlechaS_a.PushBack({ 180 * 100,180 * 100,180,180 });
	FlechaS_a.loop = false;
	FlechaS_a.speed = 0.015f;
	//_____________
	//_____________
	Juicio_a.PushBack({ 300 * 0,180 * 0,300,300 });
	Juicio_a.PushBack({ 300 * 1,180 * 0,300,300 });
	Juicio_a.PushBack({ 300 * 2,180 * 0,300,300 });
	Juicio_a.PushBack({ 300 * 3,180 * 0,300,300 });
	Juicio_a.PushBack({ 300 * 4,180 * 0,300,300 });
	Juicio_a.PushBack({ 300 * 5,180 * 0,300,300 });
	Juicio_a.PushBack({ 300 * 6,180 * 0,300,300 });
	Juicio_a.PushBack({ 300 * 7,180 * 0,300,300 });
	Juicio_a.PushBack({ 300 * 8,180 * 0,300,300 });
	Juicio_a.PushBack({ 300 * 9,180 * 0,300,300 });

	Juicio_a.PushBack({ 300 * 100,300 * 100,300,300 });
	Juicio_a.loop = false;
	Juicio_a.speed = 0.015f;
	//_____________________________
	HalconElectro_a.PushBack({ 180 * 0,180 * 0,180,180 });
	HalconElectro_a.PushBack({ 180 * 1,180 * 0,180,180 });
	HalconElectro_a.PushBack({ 180 * 2,180 * 0,180,180 });
	HalconElectro_a.PushBack({ 180 * 3,180 * 0,180,180 });
	HalconElectro_a.PushBack({ 180 * 4,180 * 0,180,180 });
	HalconElectro_a.PushBack({ 180 * 5,180 * 0,180,180 });
	HalconElectro_a.PushBack({ 180 * 6,180 * 0,180,180 });
	HalconElectro_a.PushBack({ 180 * 7,180 * 0,180,180 });
	HalconElectro_a.PushBack({ 180 * 8,180 * 0,180,180 });
	HalconElectro_a.PushBack({ 180 * 9,180 * 0,180,180 });

	HalconElectro_a.PushBack({ 180 * 10,180 * 0,180,180 });
	HalconElectro_a.PushBack({ 180 * 11,180 * 0,180,180 });
	HalconElectro_a.PushBack({ 180 * 12,180 * 0,180,180 });
	HalconElectro_a.PushBack({ 180 * 13,180 * 0,180,180 });
	HalconElectro_a.PushBack({ 180 * 14,180 * 0,180,180 });
	HalconElectro_a.PushBack({ 180 * 15,180 * 0,180,180 });

	HalconElectro_a.PushBack({ 180 * 100,180 * 100,180,180 });
	HalconElectro_a.loop = false;
	HalconElectro_a.speed = 0.015f;
	//_____________________________
	TripleL_a.PushBack({ 197 * 0,200 * 0,197,200 });
	TripleL_a.PushBack({ 197 * 1,200 * 0,197,200 });
	TripleL_a.PushBack({ 197 * 2,200 * 0,197,200 });
	TripleL_a.PushBack({ 197 * 3,200 * 0,197,200 });
	TripleL_a.PushBack({ 197 * 4,200 * 0,197,200 });
	TripleL_a.PushBack({ 197 * 5,200 * 0,197,200 });
	TripleL_a.PushBack({ 197 * 6,200 * 0,197,200 });


	TripleL_a.PushBack({ 197 * 100,200 * 100,197,200 });
	TripleL_a.loop = false;
	TripleL_a.speed = 0.015f;
	//_____________
	//_____________
	name.Create("battle");

	battlePause = false;
	playerBattleSprite = nullptr;
	townBackground = nullptr;
	dojoBackground = nullptr;
	battleStage = nullptr;
	targetEntity = nullptr;

	actualTurnEntity = nullptr;

	someoneAttacking = false;
	someoneDefending = false;
	itsPlayerTurn = false;
	canSelect = false;
	hasToShake = false;
	hasChangedPhase = false;

	//Battle stages time
	//1000 - 2000 its ok
	attackTime = 1500;
	defenseTime = 1500;
	itemTime = 1500;
	escapeTime = 1500;

	winTime = 1500;
	loseTime = 1500;

	outcomeTime = 2000;

	//Battle shake time - 100 its ok
	shakeTime = 100;

	//Higher it is -> Less shake in screen - 500 its ok
	shakeForce = 500;

	defenseBuff = 5;

	selectTime = 300;
	selectedTime = 80;

	//Dojoanim
	int w = 640, h = 489;
	for (int i = 0; i < 6; i++) {
		dojoAnim.PushBack({ w * i, 25, w, h });
		
	}

	dojoAnim.speed = 0.01f;
	dojoAnim.loop = true;


	ChangePhase(BattlePhase::THINKING);

}

Battle::~Battle()
{}

bool Battle::Awake()
{
	bool ret = true;
	
	return ret;
}

bool Battle::Start()
{
	app->scene->player->toggleGui = false;

	// initial fx
	startFx = app->audio->LoadFx("Assets/audio/sfx/fx_battle.wav");
	app->audio->PlayFx(startFx);

	ChangePhase(BattlePhase::THINKING);
	hasStarted = false;
	hasTriedToEscape = false;
	canEscape = false;
	gameOver = false;
	hasToShake = false;
	hasChangedPhase = false;
	damageTaken = 0;
	shakePos = 0;
	changeSide = 0;
	cont = 0;
	battleTurn = 0;
	turnValue = 321.123f;
	expCount = 0;
	goldCount = 0;
	skill = 0;
	selectCount = 0;
	localdt = 0;
	castSkill = false;

	LOG("Loading Battle");
	
	battleStage = &app->stages->actualStage;

	for (int i = 0; i < 8; i++) {
		if (entitiesInBattle[i] != nullptr) {
			if (entitiesInBattle[i]->hasStarted == false) {
				entitiesInBattle[i]->Start();
				entitiesInBattle[i]->hasStarted = true;

			}

			if (entitiesInBattle[i]->stats->defenseBuffed == true) {
				entitiesInBattle[i]->stats->defense -= defenseBuff;
				entitiesInBattle[i]->stats->defenseBuffed = false;
			}

			if (entitiesInBattle[i]->stats->attackMulti !=1){
				entitiesInBattle[i]->stats->attackMulti =1;
			}

			if (entitiesInBattle[i]->stats->defMulti != 1) {
				entitiesInBattle[i]->stats->defMulti = 1;
			}

			if (entitiesInBattle[i]->stats->isStunned == true) {
				entitiesInBattle[i]->stats->defMulti = false;
			}
			
		}
	}

	switch (*battleStage) {
	case StageIndex::NONE:
		break;
	case StageIndex::TOWN:
		townBackground = app->tex->Load("Assets/textures/forest_big.png");
		dojoBackground = app->tex->Load("Assets/textures/dojo3.png");
		break;
	case StageIndex::DOJO:
		townBackground = app->tex->Load("Assets/textures/forest_big.png");
		dojoBackground = app->tex->Load("Assets/textures/dojo3.png");
		break;
	case StageIndex::TOWER_0:
		townBackground = app->tex->Load("Assets/textures/forest_big.png");
		dojoBackground = app->tex->Load("Assets/textures/dojo3.png");
		break;
	case StageIndex::TOWER_1:
		townBackground = app->tex->Load("Assets/textures/forest_big.png");
		dojoBackground = app->tex->Load("Assets/textures/dojo3.png");
		break;
	case StageIndex::TOWER_2:
		townBackground = app->tex->Load("Assets/textures/forest_big.png");
		dojoBackground = app->tex->Load("Assets/textures/dojo3.png");
		break;
	case StageIndex::TOWER_3:
		townBackground = app->tex->Load("Assets/textures/forest_big.png");
		dojoBackground = app->tex->Load("Assets/textures/dojo3.png");
		break;
	case StageIndex::TOWER_FINAL_BOSS:
		townBackground = app->tex->Load("Assets/textures/forest_big.png");
		dojoBackground = app->tex->Load("Assets/textures/dojo3.png");
		break;
	case StageIndex::TOWER_BOSS_1:
		townBackground = app->tex->Load("Assets/textures/forest_big.png");
		dojoBackground = app->tex->Load("Assets/textures/dojo3.png");
		break;
	case StageIndex::TOWER_BOSS_2:
		townBackground = app->tex->Load("Assets/textures/forest_big.png");
		dojoBackground = app->tex->Load("Assets/textures/dojo3.png");
		break;
	case StageIndex::TOWER_BOSS_3:
		townBackground = app->tex->Load("Assets/textures/forest_big.png");
		dojoBackground = app->tex->Load("Assets/textures/dojo3.png");
		break;
	case StageIndex::PROLOGUE:
		townBackground = app->tex->Load("Assets/textures/cityBG.jpg");
		break;
	default:
		townBackground = app->tex->Load("Assets/textures/forest_big.png");
		dojoBackground = app->tex->Load("Assets/textures/dojo3.png");
		break;
	}

	//Load GUI textures
	backButtonTex = app->tex->Load("Assets/gui/buttons/back.png");

	attackTex = app->tex->Load("Assets/gui/buttons/attack.png");
	defenseTex = app->tex->Load("Assets/gui/buttons/defense.png");
	itemsTex = app->tex->Load("Assets/gui/buttons/items.png");
	escapeTex = app->tex->Load("Assets/gui/buttons/escape.png");

	batButtonTex =app->tex->Load("Assets/gui/buttons/bat.png");
	flyingEyeButtonTex = app->tex->Load("Assets/gui/buttons/flying_eye.png");
	skeletonButtonTex = app->tex->Load("Assets/gui/buttons/skeleton.png");

	press_backTex = app->tex->Load("Assets/gui/buttons/pressed_back.png");

	press_attackTex = app->tex->Load("Assets/gui/buttons/pressed_attack.png");
	press_defenseTex = app->tex->Load("Assets/gui/buttons/pressed_defense.png");
	press_itemsTex = app->tex->Load("Assets/gui/buttons/pressed_items.png");
	press_escapeTex = app->tex->Load("Assets/gui/buttons/pressed_escape.png");

	press_batButtonTex = app->tex->Load("Assets/gui/buttons/pressed_bat.png");
	press_flyingEyeButtonTex = app->tex->Load("Assets/gui/buttons/pressed_flying_eye.png");
	press_skeletonButtonTex = app->tex->Load("Assets/gui/buttons/pressed_skeleton.png");

	shield = app->tex->Load("Assets/textures/shield.png");

	//Load Sfx
	explosionfx = app->audio->LoadFx("Assets/audio/sfx/fx_attack_explosion.wav");

	//Load Skills
	FlechaS_EspadaS_EscudoS = app->tex->Load("Assets/sprites/ataques/flecha_sagrada_espada_sagrada_escudo_sagrado.png");
	FlechaS = app->tex->Load("Assets/sprites/ataques/flecha_sagrada.png");
	FlechaAcido = app->tex->Load("Assets/sprites/ataques/flecha_acido.png");
	Cataclismo = app->tex->Load("Assets/sprites/ataques/cataclismo-only.png");
	Ciervo = app->tex->Load("Assets/sprites/ataques/flecha_tronco_ciervo_de_madera.png");
	FlechaT = app->tex->Load("Assets/sprites/ataques/flecha_tronco.png");
	TripleL = app->tex->Load("Assets/sprites/ataques/triple_lanza_explosiva.png");
	Juicio = app->tex->Load("Assets/sprites/ataques/el_juicio_del_cielo.png");
	Pedrada = app->tex->Load("Assets/sprites/ataques/pedrada.png");
	HalconElectro = app->tex->Load("Assets/sprites/ataques/halcon_electro.png");
	AquaE = app->tex->Load("Assets/sprites/ataques/estocada_acuatica.png");


	app->map->RemoveCol();
	app->stages->onBattle = true;
	
	//Saving player State before battle
	//Position
	app->stages->playerPtr->mapPosition = app->stages->playerPtr->position;
	app->stages->playerPtr->position = app->stages->playerPtr->battlePosition;

	//Animation
	app->stages->playerPtr->mapAnimation = app->stages->playerPtr->currentAnimation;

	switch (app->stages->playerPtr->PlayerErection)
	{
	case 1:
		app->stages->playerPtr->currentAnimation = &app->stages->playerPtr->idleBattleM;
		break;
	case 2:
		app->stages->playerPtr->currentAnimation = &app->stages->playerPtr->idleBattleF;
		break;
	}

	//app->stages->playerPtr->currentAnimation->currentFrame = 1.0f;
	
	app->stages->playerPtr->canMove = false;


	//Enemies

	

	/*if (entitiesInBattle[5] != nullptr) {
		entitiesInBattle[5]->mapPosition = entitiesInBattle[5]->position;
		entitiesInBattle[5]->position = { 550, 100 };
		entitiesInBattle[5]->mapAnimation = entitiesInBattle[5]->currentAnimation;
	}*/


	for (int i = 0; i < 8; i++) {
		if (entitiesInBattle[i] != nullptr) {
			if (entitiesInBattle[i]->isAlive == true) {
				entitiesInBattle[i]->stats->localTurn = 1;
				if (i > 3) {
					entitiesInBattle[i]->mapPosition = entitiesInBattle[i]->position;
					entitiesInBattle[i]->position = { 700 + 25 * i, 25 * i };
					entitiesInBattle[i]->mapAnimation = entitiesInBattle[i]->currentAnimation;
				}
			
			}
		}
		
	}

	app->camera->SetPos({ 0, 0 });
	
	//GUI
	backButton = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 100, "Back", { app->win->GetWidth() / 2 / 2 - (BUTTONS_W * NUM_BUTTONS + BUTTONS_SPACE_HOR * 3) / 2 - 20 , app->win->GetHeight() / 2 - BUTTONS_BOTTOM_SPACE , 34, 32 }, this);
	selCH.add(backButton);
	selVL.add(backButton);
	selRAY.add(backButton);
	selDH.add(backButton);
	choos.add(backButton);
	attackButton = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 101, "Attack", { app->win->GetWidth() / 2 / 2 - (BUTTONS_W * NUM_BUTTONS + BUTTONS_SPACE_HOR * 3) / 2 + LATERAL_MOVE , app->win->GetHeight() / 2 - BUTTONS_BOTTOM_SPACE , BUTTONS_W, BUTTONS_H }, this);
	defenseButton = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 102, "Defense", { app->win->GetWidth() / 2 / 2 - (BUTTONS_W * NUM_BUTTONS + BUTTONS_SPACE_HOR * 3) / 2 + BUTTONS_W + BUTTONS_SPACE_HOR + LATERAL_MOVE,app->win->GetHeight() / 2 - BUTTONS_BOTTOM_SPACE , BUTTONS_W, BUTTONS_H }, this);
	itemButton = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 103, "Item", { app->win->GetWidth() / 2 / 2 - (BUTTONS_W * NUM_BUTTONS + BUTTONS_SPACE_HOR * 3) / 2 + BUTTONS_W * 2 + BUTTONS_SPACE_HOR * 2 + LATERAL_MOVE,app->win->GetHeight() / 2 - BUTTONS_BOTTOM_SPACE , BUTTONS_W, BUTTONS_H }, this);
	escapeButton = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 104, "Escape", { app->win->GetWidth() / 2 / 2 - (BUTTONS_W * NUM_BUTTONS + BUTTONS_SPACE_HOR * 3) / 2 + BUTTONS_W * 3 + BUTTONS_SPACE_HOR * 3 + LATERAL_MOVE, app->win->GetHeight() / 2 - BUTTONS_BOTTOM_SPACE , BUTTONS_W, BUTTONS_H }, this);
	think.add(attackButton);
	think.add(defenseButton);
	think.add(itemButton);
	think.add(escapeButton);

	normalAttackButton = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 105, "Attack", { app->win->GetWidth() / 2 / 2 - (BUTTONS_W * NUM_BUTTONS + BUTTONS_SPACE_HOR * 3) / 2 + LATERAL_MOVE, app->win->GetHeight() / 2 - BUTTONS_BOTTOM_SPACE , BUTTONS_W, BUTTONS_H }, this, true);
	selCH.add(normalAttackButton);
	selVL.add(normalAttackButton);
	selRAY.add(normalAttackButton);
	selDH.add(normalAttackButton);

	playerSpecialButton1 = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 110, " Shield", { app->win->GetWidth() / 2 / 2 - (BUTTONS_W * NUM_BUTTONS + BUTTONS_SPACE_HOR * 3) / 2 + BUTTONS_W + BUTTONS_SPACE_HOR + LATERAL_MOVE,app->win->GetHeight() / 2 - BUTTONS_BOTTOM_SPACE , BUTTONS_W, BUTTONS_H }, this, true);
	
	playerSpecialButton2 = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 111, " Sword", { app->win->GetWidth() / 2 / 2 - (BUTTONS_W * NUM_BUTTONS + BUTTONS_SPACE_HOR * 3) / 2 + BUTTONS_W * 2 + BUTTONS_SPACE_HOR * 2 + LATERAL_MOVE,app->win->GetHeight() / 2 - BUTTONS_BOTTOM_SPACE , BUTTONS_W, BUTTONS_H }, this, true);
	
	playerSpecialButton3 = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 112, " Aqua", { app->win->GetWidth() / 2 / 2 - (BUTTONS_W * NUM_BUTTONS + BUTTONS_SPACE_HOR * 3) / 2 + BUTTONS_W * 3 + BUTTONS_SPACE_HOR * 3 + LATERAL_MOVE, app->win->GetHeight() / 2 - BUTTONS_BOTTOM_SPACE , BUTTONS_W, BUTTONS_H }, this, true);
	if(app->scene->partyList.At(0)->data->stats->level >= 3)selCH.add(playerSpecialButton1);
	if(app->scene->partyList.At(0)->data->stats->level >= 6)selCH.add(playerSpecialButton2);
	if(app->scene->partyList.At(0)->data->stats->level >= 10)selCH.add(playerSpecialButton3);


	
	valionSpecialButton1 = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 120, " Stoned ", { app->win->GetWidth() / 2 / 2 - (BUTTONS_W * NUM_BUTTONS + BUTTONS_SPACE_HOR * 3) / 2 + BUTTONS_W + BUTTONS_SPACE_HOR + LATERAL_MOVE,app->win->GetHeight() / 2 - BUTTONS_BOTTOM_SPACE , BUTTONS_W, BUTTONS_H }, this, true);
	valionSpecialButton2 = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 121, " Catacl.", { app->win->GetWidth() / 2 / 2 - (BUTTONS_W * NUM_BUTTONS + BUTTONS_SPACE_HOR * 3) / 2 + BUTTONS_W * 2 + BUTTONS_SPACE_HOR * 2 + LATERAL_MOVE,app->win->GetHeight() / 2 - BUTTONS_BOTTOM_SPACE , BUTTONS_W, BUTTONS_H }, this, true);
	valionSpecialButton3 = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 122, "  Deer ", { app->win->GetWidth() / 2 / 2 - (BUTTONS_W * NUM_BUTTONS + BUTTONS_SPACE_HOR * 3) / 2 + BUTTONS_W * 3 + BUTTONS_SPACE_HOR * 3 + LATERAL_MOVE, app->win->GetHeight() / 2 - BUTTONS_BOTTOM_SPACE , BUTTONS_W, BUTTONS_H }, this, true);
	
	if (app->scene->partyList.count()>1)
	{
		if (app->scene->partyList.At(1)->data->stats->level >= 3)selVL.add(valionSpecialButton1);
		if (app->scene->partyList.At(1)->data->stats->level >= 6)selVL.add(valionSpecialButton2);
		if (app->scene->partyList.At(1)->data->stats->level >= 10)selVL.add(valionSpecialButton3);
	}

	raylaSpecialButton1 = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 130, "   Log  ", { app->win->GetWidth() / 2 / 2 - (BUTTONS_W * NUM_BUTTONS + BUTTONS_SPACE_HOR * 3) / 2 + BUTTONS_W + BUTTONS_SPACE_HOR + LATERAL_MOVE,app->win->GetHeight() / 2 - BUTTONS_BOTTOM_SPACE , BUTTONS_W, BUTTONS_H }, this, true);
	raylaSpecialButton2 = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 131, " Acid  ", { app->win->GetWidth() / 2 / 2 - (BUTTONS_W * NUM_BUTTONS + BUTTONS_SPACE_HOR * 3) / 2 + BUTTONS_W * 2 + BUTTONS_SPACE_HOR * 2 + LATERAL_MOVE,app->win->GetHeight() / 2 - BUTTONS_BOTTOM_SPACE , BUTTONS_W, BUTTONS_H }, this, true);
	raylaSpecialButton3 = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 132, " Sacred", { app->win->GetWidth() / 2 / 2 - (BUTTONS_W * NUM_BUTTONS + BUTTONS_SPACE_HOR * 3) / 2 + BUTTONS_W * 3 + BUTTONS_SPACE_HOR * 3 + LATERAL_MOVE, app->win->GetHeight() / 2 - BUTTONS_BOTTOM_SPACE , BUTTONS_W, BUTTONS_H }, this, true);
	
	if (app->scene->partyList.count() > 2)
	{
		if (app->scene->partyList.At(2)->data->stats->level >= 3)selRAY.add(raylaSpecialButton1);
		if (app->scene->partyList.At(2)->data->stats->level >= 6)selRAY.add(raylaSpecialButton2);
		if (app->scene->partyList.At(2)->data->stats->level >= 10)selRAY.add(raylaSpecialButton3);
	}


	dhionSpecialButton1 = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 140, " Judge", { app->win->GetWidth() / 2 / 2 - (BUTTONS_W * NUM_BUTTONS + BUTTONS_SPACE_HOR * 3) / 2 + BUTTONS_W + BUTTONS_SPACE_HOR + LATERAL_MOVE,app->win->GetHeight() / 2 - BUTTONS_BOTTOM_SPACE , BUTTONS_W, BUTTONS_H }, this, true);
	dhionSpecialButton2 = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 141, " Electro", { app->win->GetWidth() / 2 / 2 - (BUTTONS_W * NUM_BUTTONS + BUTTONS_SPACE_HOR * 3) / 2 + BUTTONS_W * 2 + BUTTONS_SPACE_HOR * 2 + LATERAL_MOVE,app->win->GetHeight() / 2 - BUTTONS_BOTTOM_SPACE , BUTTONS_W, BUTTONS_H }, this, true);
	dhionSpecialButton3 = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 142, "  Expl.", { app->win->GetWidth() / 2 / 2 - (BUTTONS_W * NUM_BUTTONS + BUTTONS_SPACE_HOR * 3) / 2 + BUTTONS_W * 3 + BUTTONS_SPACE_HOR * 3 + LATERAL_MOVE, app->win->GetHeight() / 2 - BUTTONS_BOTTOM_SPACE , BUTTONS_W, BUTTONS_H }, this, true);
	
	if (app->scene->partyList.count() > 3)
	{
		if (app->scene->partyList.At(3)->data->stats->level >= 3)selDH.add(dhionSpecialButton1);
		if (app->scene->partyList.At(3)->data->stats->level >= 6)selDH.add(dhionSpecialButton2);
		if (app->scene->partyList.At(3)->data->stats->level >= 10)selDH.add(dhionSpecialButton3);
	}



	//Enemy 1
	if (entitiesInBattle[4] == nullptr) {
		enemyButton1 = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 150, "Enemy1", { app->win->GetWidth() / 2 / 2 - (BUTTONS_W * NUM_BUTTONS + BUTTONS_SPACE_HOR * 3) / 2 + LATERAL_MOVE, app->win->GetHeight() / 2 - BUTTONS_BOTTOM_SPACE , BUTTONS_W, BUTTONS_H }, this, true);
		//choos.add(enemyButton1);
	}
	else if (entitiesInBattle[4]->isAlive == false) {
		enemyButton1 = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 150, "Enemy1", { app->win->GetWidth() / 2 / 2 - (BUTTONS_W * NUM_BUTTONS + BUTTONS_SPACE_HOR * 3) / 2 + LATERAL_MOVE, app->win->GetHeight() / 2 - BUTTONS_BOTTOM_SPACE , BUTTONS_W, BUTTONS_H }, this, true);
		choos.add(enemyButton1);
	}
	else {
		enemyButton1 = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 150, entitiesInBattle[4]->battleName, { app->win->GetWidth() / 2 / 2 - (BUTTONS_W * NUM_BUTTONS + BUTTONS_SPACE_HOR * 3) / 2 + LATERAL_MOVE, app->win->GetHeight() / 2 - BUTTONS_BOTTOM_SPACE , BUTTONS_W, BUTTONS_H }, this, true);
		choos.add(enemyButton1);
	}

	//Enemy 2
	if (entitiesInBattle[5] == nullptr) {
		enemyButton2 = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 151, "Enemy2", { app->win->GetWidth() / 2 / 2 - (BUTTONS_W * NUM_BUTTONS + BUTTONS_SPACE_HOR * 3) / 2 + BUTTONS_W + BUTTONS_SPACE_HOR + LATERAL_MOVE ,app->win->GetHeight() / 2 - BUTTONS_BOTTOM_SPACE , BUTTONS_W, BUTTONS_H }, this, true);
		//choos.add(enemyButton2);
	}
	else if (entitiesInBattle[5]->isAlive == false) {
		enemyButton2 = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 151, "Enemy2", { app->win->GetWidth() / 2 / 2 - (BUTTONS_W * NUM_BUTTONS + BUTTONS_SPACE_HOR * 3) / 2 + BUTTONS_W + BUTTONS_SPACE_HOR + LATERAL_MOVE ,app->win->GetHeight() / 2 - BUTTONS_BOTTOM_SPACE , BUTTONS_W, BUTTONS_H }, this, true);
		choos.add(enemyButton2);
	}
	else {
		enemyButton2 = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 151, entitiesInBattle[5]->battleName, { app->win->GetWidth() / 2 / 2 - (BUTTONS_W * NUM_BUTTONS + BUTTONS_SPACE_HOR * 3) / 2 + BUTTONS_W + BUTTONS_SPACE_HOR + LATERAL_MOVE ,app->win->GetHeight() / 2 - BUTTONS_BOTTOM_SPACE , BUTTONS_W, BUTTONS_H }, this, true);
		choos.add(enemyButton2);
	}

	//Enemy 3
	if (entitiesInBattle[6] == nullptr) {
		enemyButton3 = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 152, "Enemy3", { app->win->GetWidth() / 2 / 2 - (BUTTONS_W * NUM_BUTTONS + BUTTONS_SPACE_HOR * 3) / 2 + BUTTONS_W * 2 + BUTTONS_SPACE_HOR * 2 + LATERAL_MOVE,app->win->GetHeight() / 2 - BUTTONS_BOTTOM_SPACE , BUTTONS_W, BUTTONS_H }, this, true);
		//choos.add(enemyButton3);
	}
	else if (entitiesInBattle[6]->isAlive == false) {
		enemyButton3 = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 152, "Enemy3", { app->win->GetWidth() / 2 / 2 - (BUTTONS_W * NUM_BUTTONS + BUTTONS_SPACE_HOR * 3) / 2 + BUTTONS_W * 2 + BUTTONS_SPACE_HOR * 2 + LATERAL_MOVE,app->win->GetHeight() / 2 - BUTTONS_BOTTOM_SPACE , BUTTONS_W, BUTTONS_H }, this, true);
		choos.add(enemyButton3);
	}
	else {
		enemyButton3 = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 152, entitiesInBattle[6]->battleName, { app->win->GetWidth() / 2 / 2 - (BUTTONS_W * NUM_BUTTONS + BUTTONS_SPACE_HOR * 3) / 2 + BUTTONS_W * 2 + BUTTONS_SPACE_HOR * 2 + LATERAL_MOVE,app->win->GetHeight() / 2 - BUTTONS_BOTTOM_SPACE , BUTTONS_W, BUTTONS_H }, this, true);
		choos.add(enemyButton3);
	}

	//Enemy 4
	if (entitiesInBattle[7] == nullptr) {
		enemyButton4 = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 153, "Enemy4", { app->win->GetWidth() / 2 / 2 - (BUTTONS_W * NUM_BUTTONS + BUTTONS_SPACE_HOR * 3) / 2 + BUTTONS_W * 3 + BUTTONS_SPACE_HOR * 3 + LATERAL_MOVE, app->win->GetHeight() / 2 - BUTTONS_BOTTOM_SPACE , BUTTONS_W, BUTTONS_H }, this, true);
		//choos.add(enemyButton4);
	}
	else if (entitiesInBattle[7]->isAlive == false) {
		enemyButton4 = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 153, "Enemy4", { app->win->GetWidth() / 2 / 2 - (BUTTONS_W * NUM_BUTTONS + BUTTONS_SPACE_HOR * 3) / 2 + BUTTONS_W * 3 + BUTTONS_SPACE_HOR * 3 + LATERAL_MOVE, app->win->GetHeight() / 2 - BUTTONS_BOTTOM_SPACE , BUTTONS_W, BUTTONS_H }, this, true);
		choos.add(enemyButton4);
	}
	else {
		enemyButton4 = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 153, entitiesInBattle[7]->battleName, { app->win->GetWidth() / 2 / 2 - (BUTTONS_W * NUM_BUTTONS + BUTTONS_SPACE_HOR * 3) / 2 + BUTTONS_W * 3 + BUTTONS_SPACE_HOR * 3 + LATERAL_MOVE, app->win->GetHeight() / 2 - BUTTONS_BOTTOM_SPACE , BUTTONS_W, BUTTONS_H }, this, true);
		choos.add(enemyButton4);
	}
	

	SetTurnOrder();

	app->audio->PlayMusic("Assets/audio/music/music_battle.ogg");

	return true;
}

bool Battle::PreUpdate()
{
	bool ret = true;
	

	return ret;
}

void Battle::skillsup()
{

	for (int e = 0; e < selCH.count(); e++)
	{
		if (app->scene->partyList.count() > 0)
		{
			bool lvl = false;
			if (app->scene->partyList.At(0)->data->stats->level >= 3 )
			{
				ListItem<GuiButton*>* BUTInList;
				BUTInList = selCH.start;
				for (BUTInList = selCH.start; BUTInList != NULL ; BUTInList = BUTInList->next)
				{
					if (BUTInList->data->id == playerSpecialButton1->id && !lvl) {

						selCH.add(playerSpecialButton1);
						lvl = true;
					}
				}
			}
			if (app->scene->partyList.At(0)->data->stats->level >= 6 && selCH.At(e)->data->id != playerSpecialButton2->id)
			{
				selCH.add(playerSpecialButton2);
			}
			if (app->scene->partyList.At(0)->data->stats->level >= 10 && selCH.At(e)->data->id != playerSpecialButton3->id)
			{
				selCH.add(playerSpecialButton3);
			}

		}
	}

	for (int e =0; e < selVL.count(); e++)
	{
		if (app->scene->partyList.count() > 1)
		{
			if (app->scene->partyList.At(1)->data->stats->level >= 3 && selVL.At(e)->data->id != playerSpecialButton1->id)
			{
				selCH.add(valionSpecialButton1);
			}
			if (app->scene->partyList.At(1)->data->stats->level >= 6 && selVL.At(e)->data->id != playerSpecialButton2->id)
			{
				selCH.add(valionSpecialButton2);
			}
			if (app->scene->partyList.At(1)->data->stats->level >= 10 && selVL.At(e)->data->id != playerSpecialButton3->id)
			{
				selCH.add(valionSpecialButton3);
			}
		}
	}
	for (int e =0 ; e < selRAY.count(); e++)
	{
		if (app->scene->partyList.count() > 2)
		{
			if (app->scene->partyList.At(2)->data->stats->level >= 3 && selRAY.At(e)->data != raylaSpecialButton1)
			{
				selCH.add(raylaSpecialButton1);
			}
			if (app->scene->partyList.At(2)->data->stats->level >= 6 && selRAY.At(e)->data != raylaSpecialButton2)
			{
				selCH.add(raylaSpecialButton2);
			}
			if (app->scene->partyList.At(2)->data->stats->level >= 10 && selRAY.At(e)->data != raylaSpecialButton3)
			{
				selCH.add(raylaSpecialButton3);
			}
		}
	}
	for (int e = 0; e < selDH.count(); e++)
	{
		if (app->scene->partyList.count() > 3)
		{
			if (app->scene->partyList.At(3)->data->stats->level >= 3 && selDH.At(e)->data != dhionSpecialButton1)
			{
				selCH.add(dhionSpecialButton1);
			}
			if (app->scene->partyList.At(3)->data->stats->level >= 6 && selDH.At(e)->data != dhionSpecialButton2)
			{
				selCH.add(dhionSpecialButton2);
			}
			if (app->scene->partyList.At(3)->data->stats->level >= 10 && selDH.At(e)->data != dhionSpecialButton3)
			{
				selCH.add(dhionSpecialButton3);
			}
		}
	}
}

bool Battle::Update(float dt)
{	
	localdt = dt;
	GamePad& pad = app->input->pads[0];
	if (!pad.a && !pad.b) _wait = true;
	//skillsup();
	if (battlePause == false) {

		//if (app->input->GetKey(SDL_SCANCODE_H) == KEY_DOWN) {
			dojoAnim.Update(dt);
			//EscudoS_a.Update(dt);
			//EspadaS_a.Update(dt);
			//AquaE_a.Update(dt);

			//Pedrada_a.Update(dt);
			//Cataclismo_a.Update(dt);
			//Ciervo_a.Update(dt);

			//FlechaT_a.Update(dt);
			//FlechaAcido_a.Update(dt);
			//FlechaS_a.Update(dt);

			//Juicio_a.Update(dt);
			//HalconElectro_a.Update(dt);
			//TripleL_a.Update(dt);
		//}
			switch (skill) {
			case 110:
				if (app->battle->battlePhase == BattlePhase::DEFENDING) {
					EscudoS_a.Update(dt);
				}
				break;
			case 111:
				if (app->battle->battlePhase == BattlePhase::ATTACKING) {
				EspadaS_a.Update(dt);
				}
				break;
			case 112:
				if (app->battle->battlePhase == BattlePhase::ATTACKING) {
				AquaE_a.Update(dt);
				}
				break;

			case 120:
				if (app->battle->battlePhase == BattlePhase::ATTACKING) {
				Pedrada_a.Update(dt);
				}
				break;
			case 121:
				if (app->battle->battlePhase == BattlePhase::ATTACKING) {
				Cataclismo_a.Update(dt);
				}
				break;
			case 122:
				if (app->battle->battlePhase == BattlePhase::DEFENDING) {
				Ciervo_a.Update(dt);
				}
				break;

			case 130:
				if (app->battle->battlePhase == BattlePhase::ATTACKING) {
				FlechaT_a.Update(dt);
				}
				break;
			case 131:
				if (app->battle->battlePhase == BattlePhase::ATTACKING) {
				FlechaAcido_a.Update(dt);
				}
				break;
			case 132:
				if (app->battle->battlePhase == BattlePhase::ATTACKING) {
				FlechaS_a.Update(dt);
				}
				break;

			case 140:
				if (app->battle->battlePhase == BattlePhase::ATTACKING) {
				Juicio_a.Update(dt);
				}
				break;
			case 141:
				if (app->battle->battlePhase == BattlePhase::ATTACKING) {
				HalconElectro_a.Update(dt);
				}
				break;
			case 142:
				if (app->battle->battlePhase == BattlePhase::ATTACKING) {
					TripleL_a.Update(dt);
				}
				break;

			default:

				break;
			}

			if (battlePhase != BattlePhase::CHOOSE_ATTACK && battlePhase != BattlePhase::SELECTING)backButton->state = GuiControlState::DISABLED;
			if(battlePhase != BattlePhase::SELECTING && battlePhase != BattlePhase::CHOOSE_ATTACK)backButton->state = GuiControlState::DISABLED;
			//	if (battlePhase != BattlePhase::SELECTING)backButton->state = GuiControlState::DISABLED;

			if (!gamepad1)
			{
				attackButton->state = GuiControlState::DISABLED;
				defenseButton->state = GuiControlState::DISABLED;
				itemButton->state = GuiControlState::DISABLED;
				escapeButton->state = GuiControlState::DISABLED;
			}
			if (!gamepad2)
			{

				normalAttackButton->state = GuiControlState::DISABLED;

				playerSpecialButton1->state = GuiControlState::DISABLED;
				playerSpecialButton2->state = GuiControlState::DISABLED;
				playerSpecialButton3->state = GuiControlState::DISABLED;

				valionSpecialButton1->state = GuiControlState::DISABLED;
				valionSpecialButton2->state = GuiControlState::DISABLED;
				valionSpecialButton3->state = GuiControlState::DISABLED;

				raylaSpecialButton1->state = GuiControlState::DISABLED;
				raylaSpecialButton2->state = GuiControlState::DISABLED;
				raylaSpecialButton3->state = GuiControlState::DISABLED;

				dhionSpecialButton1->state = GuiControlState::DISABLED;
				dhionSpecialButton2->state = GuiControlState::DISABLED;
				dhionSpecialButton3->state = GuiControlState::DISABLED;
			}
			if ( (battlePhase != BattlePhase::SELECTING))
			{

				enemyButton1->state = GuiControlState::DISABLED;
				enemyButton2->state = GuiControlState::DISABLED;
				enemyButton3->state = GuiControlState::DISABLED;
				enemyButton4->state = GuiControlState::DISABLED;

			}

		//Player turn
		if (actualTurnEntity->dynamicType == DynamicType::CHARACTER) {

			switch (battlePhase) {
			case BattlePhase::THINKING:
				 gamepad2 = false, gamepad3 = false;
				//Debuff if protected las turn
				if (actualTurnEntity->stats->defenseBuffed == true) {
					actualTurnEntity->stats->defense -= defenseBuff;
					actualTurnEntity->stats->defenseBuffed = false;
				}
				if (actualTurnEntity->stats->attackMulti != 1) {
					actualTurnEntity->stats->attackMulti = 1;
				}
				if (actualTurnEntity->stats->defMulti != 1) {
					actualTurnEntity->stats->defMulti = 1;
				}

				if (!gamepad1)
				{
					attackButton->state = GuiControlState::NORMAL;
					defenseButton->state = GuiControlState::NORMAL;
					itemButton->state = GuiControlState::NORMAL;
					escapeButton->state = GuiControlState::NORMAL;
					//t = think.start;
					gamepad1 = true;
				}
				
				canSelect = true;
				skill = 0;
				GampadControl();
				break;
			case BattlePhase::CHOOSE_ATTACK:
				gamepad1 = false,  gamepad3 = false;
					skill = 0;
				if (!gamepad2)
				{
					backButton->state = GuiControlState::NORMAL;
					normalAttackButton->state = GuiControlState::NORMAL;
					for (int i = 0; i < 8; i++) {
						if (entitiesInBattle[i] == actualTurnEntity) {

							switch (i) {
							case 0:
								if (entitiesInBattle[i]->stats->level >= 3) {
									playerSpecialButton1->state = GuiControlState::NORMAL;
								}
								if (entitiesInBattle[i]->stats->level >= 6) {
									playerSpecialButton2->state = GuiControlState::NORMAL;
								}
								if (entitiesInBattle[i]->stats->level >= 10) {
									playerSpecialButton3->state = GuiControlState::NORMAL;
								}
								break;
							case 1:
								if (entitiesInBattle[i]->stats->level >= 3) {
									valionSpecialButton1->state = GuiControlState::NORMAL;
								}
								if (entitiesInBattle[i]->stats->level >= 6) {
									valionSpecialButton2->state = GuiControlState::NORMAL;
								}
								if (entitiesInBattle[i]->stats->level >= 10) {
									valionSpecialButton3->state = GuiControlState::NORMAL;
								}

								break;
							case 2:
								if (entitiesInBattle[i]->stats->level >= 3) {
									raylaSpecialButton1->state = GuiControlState::NORMAL;
								}
								if (entitiesInBattle[i]->stats->level >= 6) {
									raylaSpecialButton2->state = GuiControlState::NORMAL;
								}
								if (entitiesInBattle[i]->stats->level >= 10) {
									raylaSpecialButton3->state = GuiControlState::NORMAL;
								}

								break;
							case 3:
								if (entitiesInBattle[i]->stats->level >= 3) {
									dhionSpecialButton1->state = GuiControlState::NORMAL;
								}
								if (entitiesInBattle[i]->stats->level >= 6) {
									dhionSpecialButton2->state = GuiControlState::NORMAL;
								}
								if (entitiesInBattle[i]->stats->level >= 10) {
									dhionSpecialButton3->state = GuiControlState::NORMAL;
								}
								break;
							}
							

							//gamepad2 = true;
						}
					}
				}
				canSelect = true;
				GampadControl();
				break;
			case BattlePhase::SELECTING:
				gamepad1 = false, gamepad2 = false;
				if (!gamepad3)
				{

					backButton->state = GuiControlState::NORMAL;
					if (entitiesInBattle[4] != nullptr) {
						if (entitiesInBattle[4]->isAlive == true) {
							enemyButton1->state = GuiControlState::NORMAL;
						}

					}
					if (entitiesInBattle[5] != nullptr) {
						if (entitiesInBattle[5]->isAlive == true) {
							enemyButton2->state = GuiControlState::NORMAL;
						}
					}
					if (entitiesInBattle[6] != nullptr) {
						if (entitiesInBattle[6]->isAlive == true) {
							enemyButton3->state = GuiControlState::NORMAL;
						}
					}
					if (entitiesInBattle[7] != nullptr) {
						if (entitiesInBattle[7]->isAlive == true) {
							enemyButton4->state = GuiControlState::NORMAL;
						}
					}
					
					
				}

				if (targetEntity != nullptr) {
					ChangePhase(BattlePhase::ATTACKING);
				}
				GampadControl();
				canSelect = true;
				break;
			case BattlePhase::OUTCOME:
				if (cont < outcomeTime) {
					cont += dt;
					skill = 0;
				}
				//OUTCOME
				else {
					cont = 0;
					hasToShake = false;
					if (CheckWinLose() == true) {

					}
					else {
						if (actualTurnEntity->stats->isStunned == true) {
							actualTurnEntity->stats->isStunned = false;
						}
						if (targetEntity->takesDamage == true) {
							targetEntity->takesDamage = false;
						}

						SetTurnOrder();
						battleTurn++;
						ChangePhase(BattlePhase::THINKING);
					}
				}
				break;
			case BattlePhase::ATTACKING:
				if (cont < attackTime) {
					cont += dt;
				}
				//ATTACK
				else {
					cont = 0;
					app->stages->pAnim = rand() % 3 + 1;
					app->stages->vAnim = rand() % 2 + 1;
					Attack(targetEntity);
					/*app->audio->PlayFx(hit1fx);*/
					ChangePhase(BattlePhase::OUTCOME);
					
				}
				break;
			case BattlePhase::DEFENDING:
				if (cont < defenseTime) {
					cont += dt;
				}
				//DEFENSE
				else {
					cont = 0;
					Defense();
					SetTurnOrder();
					battleTurn++;
					ChangePhase(BattlePhase::THINKING);
				}
				break;
			case BattlePhase::USING_ITEM:
				if (cont < itemTime) {
					cont += dt;
				}
				//USING ITEM
				else {
					cont = 0;
					//UseItem();
					//actualTurnEntity = entitiesInBattle[4];
					//battleTurn++;
					ChangePhase(BattlePhase::THINKING);
				}
				break;
			case BattlePhase::ESCAPING:
				//ESCAPING
				//1rst message (trying)
				if(cont < escapeTime) {
					cont += dt;
				}
				//Tries to escape
				else if (cont < escapeTime * 2 && hasTriedToEscape == false) {
					cont += dt;
					canEscape = Escape();
					hasTriedToEscape = true;
				}
				else if (cont < escapeTime * 2 && hasTriedToEscape == true) {
					cont += dt;
				}
				else if (cont < escapeTime * 3 && hasTriedToEscape == true) {
					cont = 0;
					if (canEscape == true) {
						//app->fade->DoFadeToBlack(this, (Module*)app->titleScene);
						this->Disable();
					}
					else {
						hasTriedToEscape = false;
						SetTurnOrder();
						battleTurn++;
						ChangePhase(BattlePhase::THINKING);
					}
				}
				break;

			case BattlePhase::SPECIAL:
				switch (skill) {
					//Special Attacks
				case 110:
					
					break;
				case 111:
					
					break;
				case 112:
					
					break;
				case 120:
					
					break;
				case 121:
					
					break;
				case 122:
					
					break;

				case 130:
					
					break;
				case 131:
					
					break;
				case 132:
					
					break;
				case 140:
					
					break;
				case 141:
					
					break;
				case 142:
					
					break;
				default:
					break;
				
				}
			case BattlePhase::WIN:
				

				if (cont < winTime) {
					cont += dt;
				}
				//WINNING
				else {
					if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN || pad.a&&_wait || pad.b&&_wait) {
						cont = 0;
						ChangePhase(BattlePhase::REWARD);
						_wait = false;
					}
				}
				break;
			case BattlePhase::REWARD:
				

				if (cont < winTime) {
					cont += dt;
				}
				//REWARD
				else {
					if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN || pad.a && _wait || pad.b && _wait) {
						if (itemCount[0]!=nullptr) {
							cont = 0;
							ChangePhase(BattlePhase::LOOT);
						}
						else {
							this->Disable();
						}
						_wait = false;
					}
				}
				break;
			case BattlePhase::LOOT:
				if (cont < winTime) {
					cont += dt;
				}
				
				//LOOT
				else {
					if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN || pad.a && _wait || pad.b && _wait) {

						app->scene->AddItem(itemCount[0]->usableType);
						itemCount[0] = nullptr;
						for (int i = 0; i < 4; i++) {
							itemCount[i] = itemCount[i + 1];
						}

						if (itemCount[0] != nullptr) {
							cont = 0;
							ChangePhase(BattlePhase::LOOT);
						}
						else {
							this->Disable();
						}
					}
				}
				break;


			case BattlePhase::LOSE:
				if (cont < loseTime) {
					cont += dt;
				}
				//LOSING
				else {
					if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN || pad.a && _wait || pad.b && _wait) {
						//app->fade->DoFadeToBlack(this, (Module*)app->titleScene);
						this->Disable();
						_wait = false;
					}
				}
				break;
			}

		}
		//Enemy turn
		else if (actualTurnEntity->dynamicType == DynamicType::ENEMY) {
			switch (battlePhase) {
			case BattlePhase::THINKING:
				
				//Debuff if protected las turn
				if (actualTurnEntity->stats->defenseBuffed == true) {
					actualTurnEntity->stats->defense -= defenseBuff;
					actualTurnEntity->stats->defenseBuffed = false;
				}

				if (actualTurnEntity->stats->isStunned == true) {
					ChangePhase(BattlePhase::OUTCOME);
				}
				else {


					optionPercent = 0;
					srand(time(NULL));
					optionPercent = (rand() % (100 - 0)) + 0;
					//If the enemy is a BOSS, can't be afraid
					if (actualTurnEntity->name == "Valion" || actualTurnEntity->name == "Rayla" || actualTurnEntity->name == "Dhion" || actualTurnEntity->name == "Truck-kun") {
						if (optionPercent < 70) {//70

							DynamicEntity* targets[4];

							int n = 0;
							for (int i = 0; i < 4; i++) {
								if (entitiesInBattle[i] != nullptr) {
									if (entitiesInBattle[i]->isAlive == true) {
										targets[n] = entitiesInBattle[i];
										n++;
									}
								}
							}

							int targetNum = (rand() % n);

							/*while (entitiesInBattle[targetNum]->isAlive == false) {
								targetNum = (rand() % 4);
							}*/

							targetEntity = targets[targetNum];

							ChangePhase(BattlePhase::ATTACKING);
						}
						else {
							ChangePhase(BattlePhase::DEFENDING);
						}
					}
					//If the enemy is NOT afraid
					else if (actualTurnEntity->stats->health >= actualTurnEntity->stats->maxHealth / 2) {
						if (optionPercent <70) {//70

							DynamicEntity* targets[4];

							int n = 0;
							for (int i = 0; i < 4; i++) {
								if (entitiesInBattle[i] != nullptr) {
									if (entitiesInBattle[i]->isAlive == true) {
										targets[n] = entitiesInBattle[i];
										n++;
									}
								}
							}

							int targetNum = (rand() % n);

							/*while (entitiesInBattle[targetNum]->isAlive == false) {
								targetNum = (rand() % 4);
							}*/

							targetEntity = targets[targetNum];

							ChangePhase(BattlePhase::ATTACKING);
						}
						else {
							ChangePhase(BattlePhase::DEFENDING);
						}

					}
					//If the enemy IS afraid
					else {
						if (optionPercent < 60) {//60

							int n = 0;
							for (int i = 0; i < 4; i++) {
								if (entitiesInBattle[i] != nullptr) {
									if (entitiesInBattle[i]->isAlive == true) {
										n++;
									}
								}
							}

							int targetNum = (rand() % n);

							while (entitiesInBattle[targetNum]->isAlive == false) {
								targetNum = (rand() % n);
							}
							targetEntity = entitiesInBattle[targetNum];
							ChangePhase(BattlePhase::ATTACKING);
						}
						else if (optionPercent < 90) {//85
							ChangePhase(BattlePhase::DEFENDING);
						}
						else {
							ChangePhase(BattlePhase::ESCAPING);
						}
					}
				}
				
				break;
			case BattlePhase::OUTCOME:
				if (cont < outcomeTime) {
					cont += dt;
					skill = 0;
				}
				//OUTCOME
				else {
					cont = 0;
					hasToShake = false;
					if (CheckWinLose() == true) {

					}
					else {
						if (actualTurnEntity->stats->isStunned == true) {
							actualTurnEntity->stats->isStunned = false;
						}

						if (targetEntity->takesDamage == true) {
							targetEntity->takesDamage = false;
						}

						SetTurnOrder();
						battleTurn++;
						ChangePhase(BattlePhase::THINKING);
					}
				}
				break;
			case BattlePhase::ATTACKING:
				if (cont < attackTime) {
					cont += dt;
				}
				
				//ATTACK
				else {
					cont = 0;
					app->stages->eAnim = rand() % 3 + 1;
					Attack(targetEntity);
					ChangePhase(BattlePhase::OUTCOME);

				}
				break;
			case BattlePhase::DEFENDING:
				if (cont < defenseTime) {
					cont += dt;
				}
				//DEFENSE
				else {
					cont = 0;
					Defense();
					SetTurnOrder();
					battleTurn++;
					ChangePhase(BattlePhase::THINKING);
				}
				break;
			case BattlePhase::USING_ITEM:
				
				break;
			case BattlePhase::ESCAPING:
				//ESCAPING
				//1rst message (trying)
				if (cont < escapeTime) {
					cont += dt;
				}
				//Tries to escape
				else if (cont < escapeTime * 2 && hasTriedToEscape == false) {
					cont += dt;
					canEscape = Escape();
					hasTriedToEscape = true;
				}
				else if (cont < escapeTime * 2 && hasTriedToEscape == true) {
					cont += dt;
				}
				else if (cont < escapeTime * 3 && hasTriedToEscape == true) {
					cont = 0;
					if (canEscape == true) {
						//app->fade->DoFadeToBlack(this, (Module*)app->titleScene);
						if (CountEnemies() == 1) {
							this->Disable();
						}
						else {


							for (int i = 0; i < 8; i++) {
								if (entitiesInBattle[i] == actualTurnEntity) {
									entitiesInBattle[i] = nullptr;
								}
							}
							app->entities->DestroyEntity(actualTurnEntity);
							app->scene->normalEnemyList.del(app->scene->normalEnemyList.At(app->scene->normalEnemyList.find((NormalEnemy*)actualTurnEntity)));

							hasTriedToEscape = false;
							SetTurnOrder();
							battleTurn++;
							ChangePhase(BattlePhase::THINKING);
						}

					}
					else {
						hasTriedToEscape = false;
						SetTurnOrder();
						battleTurn++;
						ChangePhase(BattlePhase::THINKING);
					}
				}
				break;

			case BattlePhase::WIN:
				if (cont < winTime) {
					cont += dt;
				}
				//WINNING
				else {
					if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN) {
						//app->fade->DoFadeToBlack(this, (Module*)app->titleScene);
						this->Disable();
					}
				}
				break;

			case BattlePhase::LOSE:
				if (cont < loseTime) {
					cont += dt;
				}
				//LOSING
				else {
					if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN) {
						//app->fade->DoFadeToBlack(this, (Module*)app->titleScene);
						this->Disable();
					}
				}
				break;
			}

		}
		
			
		
		if (app->stages->actualStage!=StageIndex::NONE) {
			app->stages->playerPtr->currentAnimation->Update(dt);
		}

		/*if (entitiesInBattle[4] != nullptr) {
			if (entitiesInBattle[4]->isAlive == true) {
				if (enemyButton1->state == GuiControlState::FOCUSED) {
					if (entitiesInBattle[4]->isSelected == true) {
						if (selectCount < selectedTime) {
							selectCount += dt;
						}
						else {
							selectCount = 0;
							entitiesInBattle[4]->isSelected = false;
						}
					}
					else {
						if (selectCount < selectTime) {
							selectCount += dt;
						}
						else {
							selectCount = 0;
							entitiesInBattle[4]->isSelected = true;
						}
					}
				}
			}
		}*/
		
	}

	/*if (gameOver == true) {
		if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN) {
			app->fade->DoFadeToBlack(this, (Module*)app->titleScene);
		}

	}*/
	if (battleStage != nullptr) {
		switch (*battleStage) {
		case StageIndex::NONE:
			break;
		case StageIndex::PROLOGUE:
			app->render->DrawTexture(townBackground, 0, 0, 0, 1);
			break;
		case StageIndex::TOWN:
			//app->render->DrawTexture(townBackground, -200, -250);
			if (hasToShake == false) {
				app->render->DrawTexture(dojoBackground, 0, 0, &dojoAnim.GetCurrentFrame());
				changeSide = 0;
			}
			else {

				if (shakePos > shakeTime * damageTaken) {
					hasToShake = false;
				}

				if (shakePos < -shakeTime * damageTaken) {
					hasToShake = false;
				}

				float shakeTotal = shakeForce / damageTaken;
				if (shakeTotal < 0.001f) {
					shakeTotal = 0.001f;
				}

				if (shakePos == 0) {
					shakePos += dt;
					changeSide += dt;
					app->render->DrawTexture(dojoBackground, (int)shakePos / shakeTotal, 0, &dojoAnim.GetCurrentFrame());
				}
				else if (shakePos > 0) {
					shakePos += dt;
					changeSide += dt;
					if (changeSide >= 50) {
						changeSide = 0;
						shakePos = shakePos * -1;
					}
					app->render->DrawTexture(dojoBackground, (int)shakePos / shakeTotal, 0, &dojoAnim.GetCurrentFrame());
				}
				else if (shakePos < 0) {
					shakePos -= dt;
					changeSide += dt;
					if (changeSide >= 50) {
						changeSide = 0;
						shakePos = shakePos * -1;
					}
					app->render->DrawTexture(dojoBackground, (int)shakePos / shakeTotal, 0, &dojoAnim.GetCurrentFrame());
				}
				
			}
		case StageIndex::DOJO:
			//app->render->DrawTexture(townBackground, -200, -250);
			if (hasToShake == false) {
				app->render->DrawTexture(dojoBackground, 0, 0, &dojoAnim.GetCurrentFrame());
				changeSide = 0;
			}
			else {

				if (shakePos > shakeTime * damageTaken) {
					hasToShake = false;
				}

				if (shakePos < -shakeTime * damageTaken) {
					hasToShake = false;
				}

				int totalShake = shakeForce / damageTaken;
				if (totalShake < 1) {
					totalShake = 1;
				}

				if (shakePos == 0) {
					shakePos += dt;
					changeSide += dt;
					app->render->DrawTexture(dojoBackground, (int)shakePos / totalShake, 0, &dojoAnim.GetCurrentFrame());
				}
				else if (shakePos > 0) {
					shakePos += dt;
					changeSide += dt;
					if (changeSide >= 50) {
						changeSide = 0;
						shakePos = shakePos * -1;
					}
					app->render->DrawTexture(dojoBackground, (int)shakePos / totalShake, 0, &dojoAnim.GetCurrentFrame());
				}
				else if (shakePos < 0) {
					shakePos -= dt;
					changeSide += dt;
					if (changeSide >= 50) {
						changeSide = 0;
						shakePos = shakePos * -1;
					}
					app->render->DrawTexture(dojoBackground, (int)shakePos / totalShake
						, 0, &dojoAnim.GetCurrentFrame());
				}

			}

			break;
		case StageIndex::TOWER_1:
			//app->render->DrawTexture(townBackground, -200, -250);
			if (hasToShake == false) {
				app->render->DrawTexture(dojoBackground, 0, 0, &dojoAnim.GetCurrentFrame());
				changeSide = 0;
			}
			else {

				if (shakePos > shakeTime * damageTaken) {
					hasToShake = false;
				}

				if (shakePos < -shakeTime * damageTaken) {
					hasToShake = false;
				}

				int totalShake = shakeForce / damageTaken;
				if (totalShake < 1) {
					totalShake = 1;
				}

				if (shakePos == 0) {
					shakePos += dt;
					changeSide += dt;
					app->render->DrawTexture(dojoBackground, (int)shakePos / totalShake, 0, &dojoAnim.GetCurrentFrame());
				}
				else if (shakePos > 0) {
					shakePos += dt;
					changeSide += dt;
					if (changeSide >= 50) {
						changeSide = 0;
						shakePos = shakePos * -1;
					}
					app->render->DrawTexture(dojoBackground, (int)shakePos / totalShake, 0, &dojoAnim.GetCurrentFrame());
				}
				else if (shakePos < 0) {
					shakePos -= dt;
					changeSide += dt;
					if (changeSide >= 50) {
						changeSide = 0;
						shakePos = shakePos * -1;
					}
					app->render->DrawTexture(dojoBackground, (int)shakePos / totalShake
						, 0, &dojoAnim.GetCurrentFrame());
				}

			}

			break;
		case StageIndex::TOWER_2:
			//app->render->DrawTexture(townBackground, -200, -250);
			if (hasToShake == false) {
				app->render->DrawTexture(dojoBackground, 0, 0, &dojoAnim.GetCurrentFrame());
				changeSide = 0;
			}
			else {

				if (shakePos > shakeTime * damageTaken) {
					hasToShake = false;
				}

				if (shakePos < -shakeTime * damageTaken) {
					hasToShake = false;
				}

				int totalShake = shakeForce / damageTaken;
				if (totalShake < 1) {
					totalShake = 1;
				}

				if (shakePos == 0) {
					shakePos += dt;
					changeSide += dt;
					app->render->DrawTexture(dojoBackground, (int)shakePos / totalShake, 0, &dojoAnim.GetCurrentFrame());
				}
				else if (shakePos > 0) {
					shakePos += dt;
					changeSide += dt;
					if (changeSide >= 50) {
						changeSide = 0;
						shakePos = shakePos * -1;
					}
					app->render->DrawTexture(dojoBackground, (int)shakePos / totalShake, 0, &dojoAnim.GetCurrentFrame());
				}
				else if (shakePos < 0) {
					shakePos -= dt;
					changeSide += dt;
					if (changeSide >= 50) {
						changeSide = 0;
						shakePos = shakePos * -1;
					}
					app->render->DrawTexture(dojoBackground, (int)shakePos / totalShake
						, 0, &dojoAnim.GetCurrentFrame());
				}

			}

			break;
		case StageIndex::TOWER_3:
			//app->render->DrawTexture(townBackground, -200, -250);
			if (hasToShake == false) {
				app->render->DrawTexture(dojoBackground, 0, 0, &dojoAnim.GetCurrentFrame());
				changeSide = 0;
			}
			else {

				if (shakePos > shakeTime * damageTaken) {
					hasToShake = false;
				}

				if (shakePos < -shakeTime * damageTaken) {
					hasToShake = false;
				}

				int totalShake = shakeForce / damageTaken;
				if (totalShake < 1) {
					totalShake = 1;
				}

				if (shakePos == 0) {
					shakePos += dt;
					changeSide += dt;
					app->render->DrawTexture(dojoBackground, (int)shakePos / totalShake, 0, &dojoAnim.GetCurrentFrame());
				}
				else if (shakePos > 0) {
					shakePos += dt;
					changeSide += dt;
					if (changeSide >= 50) {
						changeSide = 0;
						shakePos = shakePos * -1;
					}
					app->render->DrawTexture(dojoBackground, (int)shakePos / totalShake, 0, &dojoAnim.GetCurrentFrame());
				}
				else if (shakePos < 0) {
					shakePos -= dt;
					changeSide += dt;
					if (changeSide >= 50) {
						changeSide = 0;
						shakePos = shakePos * -1;
					}
					app->render->DrawTexture(dojoBackground, (int)shakePos / totalShake
						, 0, &dojoAnim.GetCurrentFrame());
				}

			}

			break;
		case StageIndex::TOWER_FINAL_BOSS:
			//app->render->DrawTexture(townBackground, -200, -250);
			if (hasToShake == false) {
				app->render->DrawTexture(dojoBackground, 0, 0, &dojoAnim.GetCurrentFrame());
				changeSide = 0;
			}
			else {

				if (shakePos > shakeTime * damageTaken) {
					hasToShake = false;
				}

				if (shakePos < -shakeTime * damageTaken) {
					hasToShake = false;
				}

				int totalShake = shakeForce / damageTaken;
				if (totalShake < 1) {
					totalShake = 1;
				}

				if (shakePos == 0) {
					shakePos += dt;
					changeSide += dt;
					app->render->DrawTexture(dojoBackground, (int)shakePos / totalShake, 0, &dojoAnim.GetCurrentFrame());
				}
				else if (shakePos > 0) {
					shakePos += dt;
					changeSide += dt;
					if (changeSide >= 50) {
						changeSide = 0;
						shakePos = shakePos * -1;
					}
					app->render->DrawTexture(dojoBackground, (int)shakePos / totalShake, 0, &dojoAnim.GetCurrentFrame());
				}
				else if (shakePos < 0) {
					shakePos -= dt;
					changeSide += dt;
					if (changeSide >= 50) {
						changeSide = 0;
						shakePos = shakePos * -1;
					}
					app->render->DrawTexture(dojoBackground, (int)shakePos / totalShake
						, 0, &dojoAnim.GetCurrentFrame());
				}

			}

			break;
		case StageIndex::TOWER_BOSS_1:
			//app->render->DrawTexture(townBackground, -200, -250);
			if (hasToShake == false) {
				app->render->DrawTexture(dojoBackground, 0, 0, &dojoAnim.GetCurrentFrame());
				changeSide = 0;
			}
			else {

				if (shakePos > shakeTime * damageTaken) {
					hasToShake = false;
				}

				if (shakePos < -shakeTime * damageTaken) {
					hasToShake = false;
				}

				int totalShake = shakeForce / damageTaken;
				if (totalShake < 1) {
					totalShake = 1;
				}

				if (shakePos == 0) {
					shakePos += dt;
					changeSide += dt;
					app->render->DrawTexture(dojoBackground, (int)shakePos / totalShake, 0, &dojoAnim.GetCurrentFrame());
				}
				else if (shakePos > 0) {
					shakePos += dt;
					changeSide += dt;
					if (changeSide >= 50) {
						changeSide = 0;
						shakePos = shakePos * -1;
					}
					app->render->DrawTexture(dojoBackground, (int)shakePos / totalShake, 0, &dojoAnim.GetCurrentFrame());
				}
				else if (shakePos < 0) {
					shakePos -= dt;
					changeSide += dt;
					if (changeSide >= 50) {
						changeSide = 0;
						shakePos = shakePos * -1;
					}
					app->render->DrawTexture(dojoBackground, (int)shakePos / totalShake
						, 0, &dojoAnim.GetCurrentFrame());
				}

			}

			break;
		case StageIndex::TOWER_BOSS_2:
			//app->render->DrawTexture(townBackground, -200, -250);
			if (hasToShake == false) {
				app->render->DrawTexture(dojoBackground, 0, 0, &dojoAnim.GetCurrentFrame());
				changeSide = 0;
			}
			else {

				if (shakePos > shakeTime * damageTaken) {
					hasToShake = false;
				}

				if (shakePos < -shakeTime * damageTaken) {
					hasToShake = false;
				}

				int totalShake = shakeForce / damageTaken;
				if (totalShake < 1) {
					totalShake = 1;
				}

				if (shakePos == 0) {
					shakePos += dt;
					changeSide += dt;
					app->render->DrawTexture(dojoBackground, (int)shakePos / totalShake, 0, &dojoAnim.GetCurrentFrame());
				}
				else if (shakePos > 0) {
					shakePos += dt;
					changeSide += dt;
					if (changeSide >= 50) {
						changeSide = 0;
						shakePos = shakePos * -1;
					}
					app->render->DrawTexture(dojoBackground, (int)shakePos / totalShake, 0, &dojoAnim.GetCurrentFrame());
				}
				else if (shakePos < 0) {
					shakePos -= dt;
					changeSide += dt;
					if (changeSide >= 50) {
						changeSide = 0;
						shakePos = shakePos * -1;
					}
					app->render->DrawTexture(dojoBackground, (int)shakePos / totalShake
						, 0, &dojoAnim.GetCurrentFrame());
				}

			}

			break;
		case StageIndex::TOWER_BOSS_3:
			//app->render->DrawTexture(townBackground, -200, -250);
			if (hasToShake == false) {
				app->render->DrawTexture(dojoBackground, 0, 0, &dojoAnim.GetCurrentFrame());
				changeSide = 0;
			}
			else {

				if (shakePos > shakeTime * damageTaken) {
					hasToShake = false;
				}

				if (shakePos < -shakeTime * damageTaken) {
					hasToShake = false;
				}

				int totalShake = shakeForce / damageTaken;
				if (totalShake < 1) {
					totalShake = 1;
				}

				if (shakePos == 0) {
					shakePos += dt;
					changeSide += dt;
					app->render->DrawTexture(dojoBackground, (int)shakePos / totalShake, 0, &dojoAnim.GetCurrentFrame());
				}
				else if (shakePos > 0) {
					shakePos += dt;
					changeSide += dt;
					if (changeSide >= 50) {
						changeSide = 0;
						shakePos = shakePos * -1;
					}
					app->render->DrawTexture(dojoBackground, (int)shakePos / totalShake, 0, &dojoAnim.GetCurrentFrame());
				}
				else if (shakePos < 0) {
					shakePos -= dt;
					changeSide += dt;
					if (changeSide >= 50) {
						changeSide = 0;
						shakePos = shakePos * -1;
					}
					app->render->DrawTexture(dojoBackground, (int)shakePos / totalShake
						, 0, &dojoAnim.GetCurrentFrame());
				}

			}

			break;
		default:
			break;
		}
	}
	
	return true;
}

// Render bullshit
bool Battle::PostUpdate()
{
	bool ret = true;
	
	app->render->DrawRectangle({app->camera->GetPos().x,app->camera->GetPos().y,app->win->GetWidth()/2,50 }, 0, 0, 0, 200);
	app->render->DrawRectangle({app->camera->GetPos().x,app->camera->GetPos().y + app->win->GetHeight()/2 - 120 ,app->win->GetWidth(),125 }, 0, 0, 0, 200);


		
		//app->map->Draw();
		//app->guiManager->Draw();

		//PRINT THE PLAYER
		/*SDL_Rect rect = player->currentAnimation->GetCurrentFrame();
		if (player->PlayerErection == true) {
			app->render->DrawTexture(player->PlayerMTex, player->position.x, player->position.y, &rect);
		}
		if (player->PlayerErection == false) {
			app->render->DrawTexture(player->PlayerFTex, player->position.x, player->position.y, &rect);
		}*/
	//}

	if (battleTurn > 99) {
		battleTurn = 99;
	}

	//Print battle Turn
	sprintf_s(battleTurnChar, 9, "Turn: %02d", battleTurn);
	app->font->DrawText(battleTurnChar, app->win->GetWidth() / 2 - 100, 15);

	//Print turn value (depending on entities speed)
	/*sprintf_s(turnValueChar, 20, "Turn Value: %.2f", turnValue);

	if (actualTurnEntity->dynamicType == DynamicType::CHARACTER) {
		app->font->DrawText(turnValueChar, 50, app->win->GetHeight() / 2 - 30);
	}
	else if (actualTurnEntity->dynamicType == DynamicType::ENEMY) {
		app->font->DrawText(turnValueChar, app->win->GetWidth() / 2 - 200, app->win->GetHeight() / 2 - 30);
	}*/

	if(battlePhase != BattlePhase::WIN && battlePhase != BattlePhase::LOSE && battlePhase != BattlePhase::REWARD && battlePhase != BattlePhase::LOOT)
	if (turnsTimeLine[0]!=nullptr && turnsTimeLine[1] != nullptr && turnsTimeLine[2] != nullptr &&  turnsTimeLine[3] != nullptr && turnsTimeLine[4] != nullptr) {
		sprintf_s(nameChar, 100, "%s -> %s -> %s -> %s -> %s", turnsTimeLine[0]->name, turnsTimeLine[1]->name, turnsTimeLine[2]->name, turnsTimeLine[3]->name, turnsTimeLine[4]->name);
		app->font->DrawText(nameChar, 40, 15, {255,255,255}, false);
		sprintf_s(actualTurnChar, 100, "%s", turnsTimeLine[0]->name);
		app->font->DrawText(actualTurnChar, 40, 15, {150 ,150,255 }, false);
	}

	
	
	//Print battle messages
	switch (battlePhase) {
		case BattlePhase::THINKING:
			if (hasChangedPhase == true) {
				app->font->CleanFonts();
				hasChangedPhase = false;
				for (int i = 4; i < 8; i++) {
					if (entitiesInBattle[i] != nullptr) {
						entitiesInBattle[i]->isSelected = false;
					}
				}
			}
			else if (actualTurnEntity->dynamicType == DynamicType::CHARACTER) {
				sprintf_s(battleInfoChar, 50, "It's %s's turn", actualTurnEntity->name);
				app->font->DrawTextDelayed(battleInfoChar, 10,25);

				attackButton->state != GuiControlState::PRESSED ? app->render->DrawTexture(attackTex, app->win->GetWidth() / 2 / 2 - (BUTTONS_W * NUM_BUTTONS + BUTTONS_SPACE_HOR * 3) / 2 + LATERAL_MOVE, app->win->GetHeight() / 2 - BUTTONS_BOTTOM_SPACE) : app->render->DrawTexture(press_attackTex, app->win->GetWidth() / 2 / 2 - (BUTTONS_W * NUM_BUTTONS + BUTTONS_SPACE_HOR * 3) / 2 + LATERAL_MOVE, app->win->GetHeight() / 2 - BUTTONS_BOTTOM_SPACE);
				defenseButton->state != GuiControlState::PRESSED ? app->render->DrawTexture(defenseTex, app->win->GetWidth() / 2 / 2 - (BUTTONS_W * NUM_BUTTONS + BUTTONS_SPACE_HOR * 3) / 2 + BUTTONS_W + BUTTONS_SPACE_HOR + LATERAL_MOVE, app->win->GetHeight() / 2 - BUTTONS_BOTTOM_SPACE) : app->render->DrawTexture(press_defenseTex, app->win->GetWidth() / 2 / 2 - (BUTTONS_W * NUM_BUTTONS + BUTTONS_SPACE_HOR * 3) / 2 + BUTTONS_W + BUTTONS_SPACE_HOR + LATERAL_MOVE, app->win->GetHeight() / 2 - BUTTONS_BOTTOM_SPACE);
				itemButton->state != GuiControlState::PRESSED ? app->render->DrawTexture(itemsTex, app->win->GetWidth() / 2 / 2 - (BUTTONS_W * NUM_BUTTONS + BUTTONS_SPACE_HOR * 3) / 2 + BUTTONS_W * 2 + BUTTONS_SPACE_HOR * 2 + LATERAL_MOVE, app->win->GetHeight() / 2 - BUTTONS_BOTTOM_SPACE) : app->render->DrawTexture(press_itemsTex, app->win->GetWidth() / 2 / 2 - (BUTTONS_W * NUM_BUTTONS + BUTTONS_SPACE_HOR * 3) / 2 + BUTTONS_W * 2 + BUTTONS_SPACE_HOR * 2 + LATERAL_MOVE, app->win->GetHeight() / 2 - BUTTONS_BOTTOM_SPACE);
				escapeButton->state != GuiControlState::PRESSED ? app->render->DrawTexture(escapeTex, app->win->GetWidth() / 2 / 2 - (BUTTONS_W * NUM_BUTTONS + BUTTONS_SPACE_HOR * 3) / 2 + BUTTONS_W * 3 + BUTTONS_SPACE_HOR * 3 + LATERAL_MOVE, app->win->GetHeight() / 2 - BUTTONS_BOTTOM_SPACE) : app->render->DrawTexture(press_escapeTex, app->win->GetWidth() / 2 / 2 - (BUTTONS_W * NUM_BUTTONS + BUTTONS_SPACE_HOR * 3) / 2 + BUTTONS_W * 3 + BUTTONS_SPACE_HOR * 3 + LATERAL_MOVE, app->win->GetHeight() / 2 - BUTTONS_BOTTOM_SPACE);

			}
			break;
			
		case BattlePhase::CHOOSE_ATTACK:
			if (hasChangedPhase == true) {
				app->font->CleanFonts();
				hasChangedPhase = false;
				for (int i = 4; i < 8; i++) {
					if (entitiesInBattle[i] != nullptr) {
						entitiesInBattle[i]->isSelected = false;
					}
				}
			}
			else {
				app->font->DrawText("Select an attack", 10, 25);

				backButton->state != GuiControlState::PRESSED ? app->render->DrawTexture(backButtonTex, app->win->GetWidth() / 2 / 2 - (BUTTONS_W * NUM_BUTTONS + BUTTONS_SPACE_HOR * 3) / 2 - 20, app->win->GetHeight() / 2 - BUTTONS_BOTTOM_SPACE) : app->render->DrawTexture(press_backTex, app->win->GetWidth() / 2 / 2 - (BUTTONS_W * NUM_BUTTONS + BUTTONS_SPACE_HOR * 3) / 2 - 20, app->win->GetHeight() / 2 - BUTTONS_BOTTOM_SPACE);
				normalAttackButton->state != GuiControlState::PRESSED ? app->render->DrawTexture(attackTex, app->win->GetWidth() / 2 / 2 - (BUTTONS_W * NUM_BUTTONS + BUTTONS_SPACE_HOR * 3) / 2 + LATERAL_MOVE, app->win->GetHeight() / 2 - BUTTONS_BOTTOM_SPACE) : app->render->DrawTexture(press_attackTex, app->win->GetWidth() / 2 / 2 - (BUTTONS_W * NUM_BUTTONS + BUTTONS_SPACE_HOR * 3) / 2 + LATERAL_MOVE, app->win->GetHeight() / 2 - BUTTONS_BOTTOM_SPACE);
				if (normalAttackButton->state == GuiControlState::FOCUSED) {
					//app->render->DrawRectangle({ app->win->GetWidth() / 2 / 2 - (BUTTONS_W * NUM_BUTTONS + BUTTONS_SPACE_HOR * 3) / 2 - 20 - INFO_SPACE_X , app->win->GetHeight() / 2 - BUTTONS_BOTTOM_SPACE - INFO_SPACE_Y , app->win->GetWidth() / 2 / 2 - (BUTTONS_W * NUM_BUTTONS + BUTTONS_SPACE_HOR * 3) / 2 - 20 + INFO_SPACE_X * 2, INFO_SPACE_Y - 10 }, 0, 0, 0, 200);
					app->font->DrawText("A normal attack", TEXT_INFO_X, app->win->GetHeight() / 2 - TEXT_INFO_Y);
				}
				for (int i = 0; i < 8; i++) {
					if (entitiesInBattle[i] == actualTurnEntity) {
						switch (i) {
						case 0:
							if (entitiesInBattle[i]->stats->level >= 3) {
								playerSpecialButton1->state != GuiControlState::PRESSED ? app->render->DrawTexture(attackTex, app->win->GetWidth() / 2 / 2 - (BUTTONS_W * NUM_BUTTONS + BUTTONS_SPACE_HOR * 3) / 2 + BUTTONS_W + BUTTONS_SPACE_HOR + LATERAL_MOVE, app->win->GetHeight() / 2 - BUTTONS_BOTTOM_SPACE) : app->render->DrawTexture(press_attackTex, app->win->GetWidth() / 2 / 2 - (BUTTONS_W * NUM_BUTTONS + BUTTONS_SPACE_HOR * 3) / 2 + BUTTONS_W + BUTTONS_SPACE_HOR + LATERAL_MOVE, app->win->GetHeight() / 2 - BUTTONS_BOTTOM_SPACE);
								if (playerSpecialButton1->state == GuiControlState::FOCUSED) {
									//app->render->DrawRectangle({ app->win->GetWidth() / 2 / 2 - (BUTTONS_W * NUM_BUTTONS + BUTTONS_SPACE_HOR * 3) / 2 + BUTTONS_W + BUTTONS_SPACE_HOR + LATERAL_MOVE - INFO_SPACE_X , app->win->GetHeight() / 2 - BUTTONS_BOTTOM_SPACE - INFO_SPACE_Y , app->win->GetWidth() / 2 / 2 - (BUTTONS_W * NUM_BUTTONS + BUTTONS_SPACE_HOR * 3) / 2 - 20 + INFO_SPACE_X*2, INFO_SPACE_Y - 10 }, 0, 0, 0, 200);
									app->font->DrawText("Sacred Shield", TEXT_INFO_X, app->win->GetHeight() / 2 - TEXT_INFO_Y);
									app->font->DrawText("Magic Points: 2", TEXT_INFO_X * app->win->GetScale(), (app->win->GetHeight() / 2 - TEXT_INFO_Y + SEPARATION + BIG_SEPARATION)* app->win->GetScale(), { 255,255,255 }, false, 1);
									app->font->DrawText("Protects the user with twice the efficiency of a normal defense.", TEXT_INFO_X* app->win->GetScale(), (app->win->GetHeight() / 2 - TEXT_INFO_Y + SEPARATION*2 + BIG_SEPARATION)* app->win->GetScale(), { 255,255,255 }, false, 1);
								}
							}
							if (entitiesInBattle[i]->stats->level >= 6 ) {
								playerSpecialButton2->state != GuiControlState::PRESSED ? app->render->DrawTexture(attackTex, app->win->GetWidth() / 2 / 2 - (BUTTONS_W * NUM_BUTTONS + BUTTONS_SPACE_HOR * 3) / 2 + BUTTONS_W * 2 + BUTTONS_SPACE_HOR * 2 + LATERAL_MOVE, app->win->GetHeight() / 2 - BUTTONS_BOTTOM_SPACE) : app->render->DrawTexture(press_attackTex, app->win->GetWidth() / 2 / 2 - (BUTTONS_W * NUM_BUTTONS + BUTTONS_SPACE_HOR * 3) / 2 + BUTTONS_W * 2 + BUTTONS_SPACE_HOR * 2 + LATERAL_MOVE, app->win->GetHeight() / 2 - BUTTONS_BOTTOM_SPACE);
								if (playerSpecialButton2->state == GuiControlState::FOCUSED) {
								//	app->render->DrawRectangle({ app->win->GetWidth() / 2 / 2 - (BUTTONS_W * NUM_BUTTONS + BUTTONS_SPACE_HOR * 3) / 2 + BUTTONS_W * 2 + BUTTONS_SPACE_HOR * 2 + LATERAL_MOVE - INFO_SPACE_X , app->win->GetHeight() / 2 - BUTTONS_BOTTOM_SPACE - INFO_SPACE_Y , app->win->GetWidth() / 2 / 2 - (BUTTONS_W * NUM_BUTTONS + BUTTONS_SPACE_HOR * 3) / 2 - 20 + INFO_SPACE_X * 2, INFO_SPACE_Y - 10 }, 0, 0, 0, 200);
									app->font->DrawText("Holy Greatsword", TEXT_INFO_X, app->win->GetHeight() / 2 - TEXT_INFO_Y);
									app->font->DrawText("Magic Points: 4", TEXT_INFO_X * app->win->GetScale(),( app->win->GetHeight() / 2 - TEXT_INFO_Y + SEPARATION + BIG_SEPARATION)* app->win->GetScale(), { 255,255,255 }, false, 1);
									app->font->DrawText("Does twice the damage of a normal attack", TEXT_INFO_X * app->win->GetScale(),( app->win->GetHeight() / 2 - TEXT_INFO_Y + SEPARATION * 2 + BIG_SEPARATION)* app->win->GetScale(), { 255,255,255 }, false, 1);
								}
							}
							if (entitiesInBattle[i]->stats->level >= 10) {
								playerSpecialButton3->state != GuiControlState::PRESSED ? app->render->DrawTexture(attackTex, app->win->GetWidth() / 2 / 2 - (BUTTONS_W * NUM_BUTTONS + BUTTONS_SPACE_HOR * 3) / 2 + BUTTONS_W * 3 + BUTTONS_SPACE_HOR * 3 + LATERAL_MOVE, app->win->GetHeight() / 2 - BUTTONS_BOTTOM_SPACE) : app->render->DrawTexture(press_attackTex, app->win->GetWidth() / 2 / 2 - (BUTTONS_W * NUM_BUTTONS + BUTTONS_SPACE_HOR * 3) / 2 + BUTTONS_W * 3 + BUTTONS_SPACE_HOR * 3 + LATERAL_MOVE, app->win->GetHeight() / 2 - BUTTONS_BOTTOM_SPACE);
								if (playerSpecialButton3->state == GuiControlState::FOCUSED) {
								//	app->render->DrawRectangle({ app->win->GetWidth() / 2 / 2 - (BUTTONS_W * NUM_BUTTONS + BUTTONS_SPACE_HOR * 3) / 2 + BUTTONS_W * 3 + BUTTONS_SPACE_HOR * 3 + LATERAL_MOVE - INFO_SPACE_X , app->win->GetHeight() / 2 - BUTTONS_BOTTOM_SPACE - INFO_SPACE_Y , app->win->GetWidth() / 2 / 2 - (BUTTONS_W * NUM_BUTTONS + BUTTONS_SPACE_HOR * 3) / 2 - 20 + INFO_SPACE_X * 2, INFO_SPACE_Y - 10 }, 0, 0, 0, 200);
									app->font->DrawText("Aquatic Thrust", TEXT_INFO_X, app->win->GetHeight() / 2 - TEXT_INFO_Y);
									app->font->DrawText("Magic Points: 6", TEXT_INFO_X * app->win->GetScale(),( app->win->GetHeight() / 2 - TEXT_INFO_Y + SEPARATION + BIG_SEPARATION)* app->win->GetScale(), { 255,255,255 }, false, 1);
									app->font->DrawText("Does 3 times the damage of a normal attack", TEXT_INFO_X * app->win->GetScale(),( app->win->GetHeight() / 2 - TEXT_INFO_Y + SEPARATION * 2 + BIG_SEPARATION)* app->win->GetScale(), { 255,255,255 }, false, 1);
								}
							}
							break;
						case 1:
							if (entitiesInBattle[i]->stats->level >= 3) {
								valionSpecialButton1->state != GuiControlState::PRESSED ? app->render->DrawTexture(attackTex, app->win->GetWidth() / 2 / 2 - (BUTTONS_W * NUM_BUTTONS + BUTTONS_SPACE_HOR * 3) / 2 + BUTTONS_W + BUTTONS_SPACE_HOR + LATERAL_MOVE, app->win->GetHeight() / 2 - BUTTONS_BOTTOM_SPACE) : app->render->DrawTexture(press_attackTex, app->win->GetWidth() / 2 / 2 - (BUTTONS_W * NUM_BUTTONS + BUTTONS_SPACE_HOR * 3) / 2 + BUTTONS_W + BUTTONS_SPACE_HOR + LATERAL_MOVE, app->win->GetHeight() / 2 - BUTTONS_BOTTOM_SPACE);
								if (valionSpecialButton1->state == GuiControlState::FOCUSED) {
									//app->render->DrawRectangle({ app->win->GetWidth() / 2 / 2 - (BUTTONS_W * NUM_BUTTONS + BUTTONS_SPACE_HOR * 3) / 2 + BUTTONS_W + BUTTONS_SPACE_HOR + LATERAL_MOVE - INFO_SPACE_X , app->win->GetHeight() / 2 - BUTTONS_BOTTOM_SPACE - INFO_SPACE_Y , app->win->GetWidth() / 2 / 2 - (BUTTONS_W * NUM_BUTTONS + BUTTONS_SPACE_HOR * 3) / 2 - 20 + INFO_SPACE_X*2, INFO_SPACE_Y - 10 }, 0, 0, 0, 200);
									app->font->DrawText("Pedrada", TEXT_INFO_X, app->win->GetHeight() / 2 - TEXT_INFO_Y);
									app->font->DrawText("Magic Points: 2", TEXT_INFO_X * app->win->GetScale(), (app->win->GetHeight() / 2 - TEXT_INFO_Y + SEPARATION + BIG_SEPARATION)* app->win->GetScale(), { 255,255,255 }, false, 1);
									app->font->DrawText("Does twice the damage of a normal attack", TEXT_INFO_X * app->win->GetScale(), (app->win->GetHeight() / 2 - TEXT_INFO_Y + SEPARATION * 2 + BIG_SEPARATION)* app->win->GetScale(), { 255,255,255 }, false, 1);
								}
							}
							if (entitiesInBattle[i]->stats->level >= 6) {
								valionSpecialButton2->state != GuiControlState::PRESSED ? app->render->DrawTexture(attackTex, app->win->GetWidth() / 2 / 2 - (BUTTONS_W * NUM_BUTTONS + BUTTONS_SPACE_HOR * 3) / 2 + BUTTONS_W * 2 + BUTTONS_SPACE_HOR * 2 + LATERAL_MOVE, app->win->GetHeight() / 2 - BUTTONS_BOTTOM_SPACE) : app->render->DrawTexture(press_attackTex, app->win->GetWidth() / 2 / 2 - (BUTTONS_W * NUM_BUTTONS + BUTTONS_SPACE_HOR * 3) / 2 + BUTTONS_W * 2 + BUTTONS_SPACE_HOR * 2 + LATERAL_MOVE, app->win->GetHeight() / 2 - BUTTONS_BOTTOM_SPACE);
								if (valionSpecialButton2->state == GuiControlState::FOCUSED) {
									//app->render->DrawRectangle({ app->win->GetWidth() / 2 / 2 - (BUTTONS_W * NUM_BUTTONS + BUTTONS_SPACE_HOR * 3) / 2 + BUTTONS_W + BUTTONS_SPACE_HOR + LATERAL_MOVE - INFO_SPACE_X , app->win->GetHeight() / 2 - BUTTONS_BOTTOM_SPACE - INFO_SPACE_Y , app->win->GetWidth() / 2 / 2 - (BUTTONS_W * NUM_BUTTONS + BUTTONS_SPACE_HOR * 3) / 2 - 20 + INFO_SPACE_X*2, INFO_SPACE_Y - 10 }, 0, 0, 0, 200);
									app->font->DrawText("Cataclysm", TEXT_INFO_X, app->win->GetHeight() / 2 - TEXT_INFO_Y);
									app->font->DrawText("Magic Points: 4", TEXT_INFO_X * app->win->GetScale(), (app->win->GetHeight() / 2 - TEXT_INFO_Y + SEPARATION + BIG_SEPARATION)* app->win->GetScale(), { 255,255,255 }, false, 1);
									app->font->DrawText("Does 3 times the damage of a normal attack", TEXT_INFO_X * app->win->GetScale(), (app->win->GetHeight() / 2 - TEXT_INFO_Y + SEPARATION * 2 + BIG_SEPARATION)* app->win->GetScale(), { 255,255,255 }, false, 1);
								}
							}
							if (entitiesInBattle[i]->stats->level >= 10) {
								valionSpecialButton3->state != GuiControlState::PRESSED ? app->render->DrawTexture(attackTex, app->win->GetWidth() / 2 / 2 - (BUTTONS_W * NUM_BUTTONS + BUTTONS_SPACE_HOR * 3) / 2 + BUTTONS_W * 3 + BUTTONS_SPACE_HOR * 3 + LATERAL_MOVE, app->win->GetHeight() / 2 - BUTTONS_BOTTOM_SPACE) : app->render->DrawTexture(press_attackTex, app->win->GetWidth() / 2 / 2 - (BUTTONS_W * NUM_BUTTONS + BUTTONS_SPACE_HOR * 3) / 2 + BUTTONS_W * 3 + BUTTONS_SPACE_HOR * 3 + LATERAL_MOVE, app->win->GetHeight() / 2 - BUTTONS_BOTTOM_SPACE);
								if (valionSpecialButton3->state == GuiControlState::FOCUSED) {
									//app->render->DrawRectangle({ app->win->GetWidth() / 2 / 2 - (BUTTONS_W * NUM_BUTTONS + BUTTONS_SPACE_HOR * 3) / 2 + BUTTONS_W + BUTTONS_SPACE_HOR + LATERAL_MOVE - INFO_SPACE_X , app->win->GetHeight() / 2 - BUTTONS_BOTTOM_SPACE - INFO_SPACE_Y , app->win->GetWidth() / 2 / 2 - (BUTTONS_W * NUM_BUTTONS + BUTTONS_SPACE_HOR * 3) / 2 - 20 + INFO_SPACE_X*2, INFO_SPACE_Y - 10 }, 0, 0, 0, 200);
									app->font->DrawText("Wood Deer", TEXT_INFO_X, app->win->GetHeight() / 2 - TEXT_INFO_Y);
									app->font->DrawText("Magic Points: 6", TEXT_INFO_X * app->win->GetScale(), (app->win->GetHeight() / 2 - TEXT_INFO_Y + SEPARATION + BIG_SEPARATION)* app->win->GetScale(), { 255,255,255 }, false, 1);
									app->font->DrawText("Protects the user with twice the efficiency of a normal defense.", TEXT_INFO_X * app->win->GetScale(), (app->win->GetHeight() / 2 - TEXT_INFO_Y + SEPARATION * 2 + BIG_SEPARATION)* app->win->GetScale(), { 255,255,255 }, false, 1);
								}
							}
							
							break;
						case 2:
							if (entitiesInBattle[i]->stats->level >= 3) {
								raylaSpecialButton1->state != GuiControlState::PRESSED ? app->render->DrawTexture(attackTex, app->win->GetWidth() / 2 / 2 - (BUTTONS_W * NUM_BUTTONS + BUTTONS_SPACE_HOR * 3) / 2 + BUTTONS_W + BUTTONS_SPACE_HOR + LATERAL_MOVE, app->win->GetHeight() / 2 - BUTTONS_BOTTOM_SPACE) : app->render->DrawTexture(press_attackTex, app->win->GetWidth() / 2 / 2 - (BUTTONS_W * NUM_BUTTONS + BUTTONS_SPACE_HOR * 3) / 2 + BUTTONS_W + BUTTONS_SPACE_HOR + LATERAL_MOVE, app->win->GetHeight() / 2 - BUTTONS_BOTTOM_SPACE);
								if (raylaSpecialButton1->state == GuiControlState::FOCUSED) {
									//app->render->DrawRectangle({ app->win->GetWidth() / 2 / 2 - (BUTTONS_W * NUM_BUTTONS + BUTTONS_SPACE_HOR * 3) / 2 + BUTTONS_W + BUTTONS_SPACE_HOR + LATERAL_MOVE - INFO_SPACE_X , app->win->GetHeight() / 2 - BUTTONS_BOTTOM_SPACE - INFO_SPACE_Y , app->win->GetWidth() / 2 / 2 - (BUTTONS_W * NUM_BUTTONS + BUTTONS_SPACE_HOR * 3) / 2 - 20 + INFO_SPACE_X*2, INFO_SPACE_Y - 10 }, 0, 0, 0, 200);
									app->font->DrawText("Log arrow", TEXT_INFO_X, app->win->GetHeight() / 2 - TEXT_INFO_Y);
									app->font->DrawText("Magic Points: 2", TEXT_INFO_X * app->win->GetScale(), (app->win->GetHeight() / 2 - TEXT_INFO_Y + SEPARATION + BIG_SEPARATION)* app->win->GetScale(), { 255,255,255 }, false, 1);
									app->font->DrawText("Does twice the damage of a normal attack", TEXT_INFO_X * app->win->GetScale(), (app->win->GetHeight() / 2 - TEXT_INFO_Y + SEPARATION * 2 + BIG_SEPARATION)* app->win->GetScale(), { 255,255,255 }, false, 1);
								}
							}
							if (entitiesInBattle[i]->stats->level >= 6) {
								raylaSpecialButton2->state != GuiControlState::PRESSED ? app->render->DrawTexture(attackTex, app->win->GetWidth() / 2 / 2 - (BUTTONS_W * NUM_BUTTONS + BUTTONS_SPACE_HOR * 3) / 2 + BUTTONS_W * 2 + BUTTONS_SPACE_HOR * 2 + LATERAL_MOVE, app->win->GetHeight() / 2 - BUTTONS_BOTTOM_SPACE) : app->render->DrawTexture(press_attackTex, app->win->GetWidth() / 2 / 2 - (BUTTONS_W * NUM_BUTTONS + BUTTONS_SPACE_HOR * 3) / 2 + BUTTONS_W * 2 + BUTTONS_SPACE_HOR * 2 + LATERAL_MOVE, app->win->GetHeight() / 2 - BUTTONS_BOTTOM_SPACE);
								if (raylaSpecialButton2->state == GuiControlState::FOCUSED) {
									//app->render->DrawRectangle({ app->win->GetWidth() / 2 / 2 - (BUTTONS_W * NUM_BUTTONS + BUTTONS_SPACE_HOR * 3) / 2 + BUTTONS_W + BUTTONS_SPACE_HOR + LATERAL_MOVE - INFO_SPACE_X , app->win->GetHeight() / 2 - BUTTONS_BOTTOM_SPACE - INFO_SPACE_Y , app->win->GetWidth() / 2 / 2 - (BUTTONS_W * NUM_BUTTONS + BUTTONS_SPACE_HOR * 3) / 2 - 20 + INFO_SPACE_X*2, INFO_SPACE_Y - 10 }, 0, 0, 0, 200);
									app->font->DrawText("Acid Arrow", TEXT_INFO_X, app->win->GetHeight() / 2 - TEXT_INFO_Y);
									app->font->DrawText("Magic Points: 4", TEXT_INFO_X* app->win->GetScale(), (app->win->GetHeight() / 2 - TEXT_INFO_Y + SEPARATION + BIG_SEPARATION)* app->win->GetScale(), { 255,255,255 }, false, 1);
									app->font->DrawText("Attacks and stuns the enemy for 1 turn", TEXT_INFO_X* app->win->GetScale(), (app->win->GetHeight() / 2 - TEXT_INFO_Y + SEPARATION * 2 + BIG_SEPARATION)* app->win->GetScale(), { 255,255,255 }, false, 1);
								}
							}
							if (entitiesInBattle[i]->stats->level >= 10) {
								raylaSpecialButton3->state != GuiControlState::PRESSED ? app->render->DrawTexture(attackTex, app->win->GetWidth() / 2 / 2 - (BUTTONS_W * NUM_BUTTONS + BUTTONS_SPACE_HOR * 3) / 2 + BUTTONS_W * 3 + BUTTONS_SPACE_HOR * 3 + LATERAL_MOVE, app->win->GetHeight() / 2 - BUTTONS_BOTTOM_SPACE) : app->render->DrawTexture(press_attackTex, app->win->GetWidth() / 2 / 2 - (BUTTONS_W * NUM_BUTTONS + BUTTONS_SPACE_HOR * 3) / 2 + BUTTONS_W * 3 + BUTTONS_SPACE_HOR * 3 + LATERAL_MOVE, app->win->GetHeight() / 2 - BUTTONS_BOTTOM_SPACE);
								if (raylaSpecialButton3->state == GuiControlState::FOCUSED) {
									//app->render->DrawRectangle({ app->win->GetWidth() / 2 / 2 - (BUTTONS_W * NUM_BUTTONS + BUTTONS_SPACE_HOR * 3) / 2 + BUTTONS_W + BUTTONS_SPACE_HOR + LATERAL_MOVE - INFO_SPACE_X , app->win->GetHeight() / 2 - BUTTONS_BOTTOM_SPACE - INFO_SPACE_Y , app->win->GetWidth() / 2 / 2 - (BUTTONS_W * NUM_BUTTONS + BUTTONS_SPACE_HOR * 3) / 2 - 20 + INFO_SPACE_X*2, INFO_SPACE_Y - 10 }, 0, 0, 0, 200);
									app->font->DrawText("Sacred arrow", TEXT_INFO_X, app->win->GetHeight() / 2 - TEXT_INFO_Y);
									app->font->DrawText("Magic Points: 6", TEXT_INFO_X * app->win->GetScale(), (app->win->GetHeight() / 2 - TEXT_INFO_Y + SEPARATION + BIG_SEPARATION)* app->win->GetScale(), { 255,255,255 }, false, 1);
									app->font->DrawText("Does 3 times the damage of a normal arrow", TEXT_INFO_X * app->win->GetScale(), (app->win->GetHeight() / 2 - TEXT_INFO_Y + SEPARATION * 2 + BIG_SEPARATION)* app->win->GetScale(), { 255,255,255 }, false, 1);
								}
							}
							
							break;
						case 3:
							if (entitiesInBattle[i]->stats->level >= 3) {
								dhionSpecialButton1->state != GuiControlState::PRESSED ? app->render->DrawTexture(attackTex, app->win->GetWidth() / 2 / 2 - (BUTTONS_W * NUM_BUTTONS + BUTTONS_SPACE_HOR * 3) / 2 + BUTTONS_W + BUTTONS_SPACE_HOR + LATERAL_MOVE, app->win->GetHeight() / 2 - BUTTONS_BOTTOM_SPACE) : app->render->DrawTexture(press_attackTex, app->win->GetWidth() / 2 / 2 - (BUTTONS_W * NUM_BUTTONS + BUTTONS_SPACE_HOR * 3) / 2 + BUTTONS_W + BUTTONS_SPACE_HOR + LATERAL_MOVE, app->win->GetHeight() / 2 - BUTTONS_BOTTOM_SPACE);
								if (dhionSpecialButton1->state == GuiControlState::FOCUSED) {
									//app->render->DrawRectangle({ app->win->GetWidth() / 2 / 2 - (BUTTONS_W * NUM_BUTTONS + BUTTONS_SPACE_HOR * 3) / 2 + BUTTONS_W + BUTTONS_SPACE_HOR + LATERAL_MOVE - INFO_SPACE_X , app->win->GetHeight() / 2 - BUTTONS_BOTTOM_SPACE - INFO_SPACE_Y , app->win->GetWidth() / 2 / 2 - (BUTTONS_W * NUM_BUTTONS + BUTTONS_SPACE_HOR * 3) / 2 - 20 + INFO_SPACE_X*2, INFO_SPACE_Y - 10 }, 0, 0, 0, 200);
									app->font->DrawText("Electrifying Spears Rain", TEXT_INFO_X, app->win->GetHeight() / 2 - TEXT_INFO_Y);
									app->font->DrawText("Magic Points: 2", TEXT_INFO_X* app->win->GetScale(), (app->win->GetHeight() / 2 - TEXT_INFO_Y + SEPARATION + BIG_SEPARATION)* app->win->GetScale(), { 255,255,255 }, false, 1);
									app->font->DrawText("Does twice the damage of a normal attack", TEXT_INFO_X* app->win->GetScale(), (app->win->GetHeight() / 2 - TEXT_INFO_Y + SEPARATION * 2 + BIG_SEPARATION)* app->win->GetScale(), { 255,255,255 }, false, 1);
								}
							}
							if (entitiesInBattle[i]->stats->level >= 6) {
								dhionSpecialButton2->state != GuiControlState::PRESSED ? app->render->DrawTexture(attackTex, app->win->GetWidth() / 2 / 2 - (BUTTONS_W * NUM_BUTTONS + BUTTONS_SPACE_HOR * 3) / 2 + BUTTONS_W * 2 + BUTTONS_SPACE_HOR * 2 + LATERAL_MOVE, app->win->GetHeight() / 2 - BUTTONS_BOTTOM_SPACE) : app->render->DrawTexture(press_attackTex, app->win->GetWidth() / 2 / 2 - (BUTTONS_W * NUM_BUTTONS + BUTTONS_SPACE_HOR * 3) / 2 + BUTTONS_W * 2 + BUTTONS_SPACE_HOR * 2 + LATERAL_MOVE, app->win->GetHeight() / 2 - BUTTONS_BOTTOM_SPACE);
								if (dhionSpecialButton2->state == GuiControlState::FOCUSED) {
									//app->render->DrawRectangle({ app->win->GetWidth() / 2 / 2 - (BUTTONS_W * NUM_BUTTONS + BUTTONS_SPACE_HOR * 3) / 2 + BUTTONS_W + BUTTONS_SPACE_HOR + LATERAL_MOVE - INFO_SPACE_X , app->win->GetHeight() / 2 - BUTTONS_BOTTOM_SPACE - INFO_SPACE_Y , app->win->GetWidth() / 2 / 2 - (BUTTONS_W * NUM_BUTTONS + BUTTONS_SPACE_HOR * 3) / 2 - 20 + INFO_SPACE_X*2, INFO_SPACE_Y - 10 }, 0, 0, 0, 200);
									app->font->DrawText("Electric Hawk", TEXT_INFO_X, app->win->GetHeight() / 2 - TEXT_INFO_Y);
									app->font->DrawText("Magic Points: 4", TEXT_INFO_X* app->win->GetScale(), (app->win->GetHeight() / 2 - TEXT_INFO_Y + SEPARATION + BIG_SEPARATION)* app->win->GetScale(), { 255,255,255 }, false, 1);
									app->font->DrawText("Attacks and stuns the enemy for 1 turn", TEXT_INFO_X* app->win->GetScale(), (app->win->GetHeight() / 2 - TEXT_INFO_Y + SEPARATION * 2 + BIG_SEPARATION)* app->win->GetScale(), { 255,255,255 }, false, 1);
								}
							}
							if (entitiesInBattle[i]->stats->level >= 10) {
								dhionSpecialButton3->state != GuiControlState::PRESSED ? app->render->DrawTexture(attackTex, app->win->GetWidth() / 2 / 2 - (BUTTONS_W * NUM_BUTTONS + BUTTONS_SPACE_HOR * 3) / 2 + BUTTONS_W * 3 + BUTTONS_SPACE_HOR * 3 + LATERAL_MOVE, app->win->GetHeight() / 2 - BUTTONS_BOTTOM_SPACE) : app->render->DrawTexture(press_attackTex, app->win->GetWidth() / 2 / 2 - (BUTTONS_W * NUM_BUTTONS + BUTTONS_SPACE_HOR * 3) / 2 + BUTTONS_W * 3 + BUTTONS_SPACE_HOR * 3 + LATERAL_MOVE, app->win->GetHeight() / 2 - BUTTONS_BOTTOM_SPACE);
								if (dhionSpecialButton3->state == GuiControlState::FOCUSED) {
									//app->render->DrawRectangle({ app->win->GetWidth() / 2 / 2 - (BUTTONS_W * NUM_BUTTONS + BUTTONS_SPACE_HOR * 3) / 2 + BUTTONS_W + BUTTONS_SPACE_HOR + LATERAL_MOVE - INFO_SPACE_X , app->win->GetHeight() / 2 - BUTTONS_BOTTOM_SPACE - INFO_SPACE_Y , app->win->GetWidth() / 2 / 2 - (BUTTONS_W * NUM_BUTTONS + BUTTONS_SPACE_HOR * 3) / 2 - 20 + INFO_SPACE_X*2, INFO_SPACE_Y - 10 }, 0, 0, 0, 200);
									app->font->DrawText("Triple Explosive Spear", TEXT_INFO_X, app->win->GetHeight() / 2 - TEXT_INFO_Y);
									app->font->DrawText("Magic Points: 6", TEXT_INFO_X* app->win->GetScale(), (app->win->GetHeight() / 2 - TEXT_INFO_Y + SEPARATION + BIG_SEPARATION)* app->win->GetScale(), { 255,255,255 }, false, 1);
									app->font->DrawText("Does 3 times the damage of a normal attack", TEXT_INFO_X* app->win->GetScale(), (app->win->GetHeight() / 2 - TEXT_INFO_Y + SEPARATION * 2 + BIG_SEPARATION)* app->win->GetScale(), { 255,255,255 }, false, 1);
								}
							}
						
							break;
						}
					}
				}
			}

			break;
			
		case BattlePhase::SELECTING:
			if (hasChangedPhase == true) {
				app->font->CleanFonts();
				hasChangedPhase = false;
				for (int i = 4; i < 8; i++) {
					if (entitiesInBattle[i] != nullptr) {
						entitiesInBattle[i]->isSelected = false;
					}
				}
			}
			else {
				app->font->DrawText("Select a target", 10, 25);

				backButton->state != GuiControlState::PRESSED ? app->render->DrawTexture(backButtonTex, app->win->GetWidth() / 2 / 2 - (BUTTONS_W * NUM_BUTTONS + BUTTONS_SPACE_HOR * 3) / 2 - 20, app->win->GetHeight() / 2 - BUTTONS_BOTTOM_SPACE) : app->render->DrawTexture(press_backTex, app->win->GetWidth() / 2 / 2 - (BUTTONS_W * NUM_BUTTONS + BUTTONS_SPACE_HOR * 3) / 2 - 20, app->win->GetHeight() / 2 - BUTTONS_BOTTOM_SPACE);


				if (entitiesInBattle[4] != nullptr) {
					if (entitiesInBattle[4]->isAlive == true) {

						//app->guiManager->ChangeButtonText(150, entitiesInBattle[4]->name);
						enemyButton1->state != GuiControlState::PRESSED ? app->render->DrawTexture(attackTex, app->win->GetWidth() / 2 / 2 - (BUTTONS_W * NUM_BUTTONS + BUTTONS_SPACE_HOR * 3) / 2 + LATERAL_MOVE, app->win->GetHeight() / 2 - BUTTONS_BOTTOM_SPACE) : app->render->DrawTexture(press_attackTex, app->win->GetWidth() / 2 / 2 - (BUTTONS_W * NUM_BUTTONS + BUTTONS_SPACE_HOR * 3) / 2 + LATERAL_MOVE, app->win->GetHeight() / 2 - BUTTONS_BOTTOM_SPACE);
						if (entitiesInBattle[4] != nullptr) {
							if (entitiesInBattle[4]->isAlive == true) {
								if (enemyButton1->state == GuiControlState::FOCUSED) {
									if (entitiesInBattle[4]->isSelected == true) {
										if (selectCount < selectedTime) {
											selectCount += localdt;
										}
										else {
											selectCount = 0;
											entitiesInBattle[4]->isSelected = false;
										}
									}
									else {
										if (selectCount < selectTime) {
											selectCount += localdt;
										}
										else {
											selectCount = 0;
											entitiesInBattle[4]->isSelected = true;
										}
									}
								}
								else {
									entitiesInBattle[4]->isSelected = false;
								}
							}
						}
						
					}
				}
				if (entitiesInBattle[5] != nullptr) {
					if (entitiesInBattle[5]->isAlive == true) {
						
							enemyButton2->state != GuiControlState::PRESSED ? app->render->DrawTexture(attackTex, app->win->GetWidth() / 2 / 2 - (BUTTONS_W * NUM_BUTTONS + BUTTONS_SPACE_HOR * 3) / 2 + BUTTONS_W + BUTTONS_SPACE_HOR + LATERAL_MOVE, app->win->GetHeight() / 2 - BUTTONS_BOTTOM_SPACE) : app->render->DrawTexture(press_attackTex, app->win->GetWidth() / 2 / 2 - (BUTTONS_W * NUM_BUTTONS + BUTTONS_SPACE_HOR * 3) / 2 + BUTTONS_W + BUTTONS_SPACE_HOR + LATERAL_MOVE, app->win->GetHeight() / 2 - BUTTONS_BOTTOM_SPACE);
							if (entitiesInBattle[5] != nullptr) {
								if (entitiesInBattle[5]->isAlive == true) {
									if (enemyButton2->state == GuiControlState::FOCUSED) {
										if (entitiesInBattle[5]->isSelected == true) {
											if (selectCount < selectedTime) {
												selectCount += localdt;
											}
											else {
												selectCount = 0;
												entitiesInBattle[5]->isSelected = false;
											}
										}
										else {
											if (selectCount < selectTime) {
												selectCount += localdt;
											}
											else {
												selectCount = 0;
												entitiesInBattle[5]->isSelected = true;
											}
										}
									}
									else {
										entitiesInBattle[5]->isSelected = false;
									}
								}
							}
					}
				}
				if (entitiesInBattle[6] != nullptr) {
					if (entitiesInBattle[6]->isAlive == true) {
						
								enemyButton3->state != GuiControlState::PRESSED ? app->render->DrawTexture(attackTex, app->win->GetWidth() / 2 / 2 - (BUTTONS_W * NUM_BUTTONS + BUTTONS_SPACE_HOR * 3) / 2 + BUTTONS_W * 2 + BUTTONS_SPACE_HOR * 2 + LATERAL_MOVE, app->win->GetHeight() / 2 - BUTTONS_BOTTOM_SPACE) : app->render->DrawTexture(press_attackTex, app->win->GetWidth() / 2 / 2 - (BUTTONS_W * NUM_BUTTONS + BUTTONS_SPACE_HOR * 3) / 2 + BUTTONS_W * 2 + BUTTONS_SPACE_HOR * 2 + LATERAL_MOVE, app->win->GetHeight() / 2 - BUTTONS_BOTTOM_SPACE);
								if (entitiesInBattle[6] != nullptr) {
									if (entitiesInBattle[6]->isAlive == true) {
										if (enemyButton3->state == GuiControlState::FOCUSED) {
											if (entitiesInBattle[6]->isSelected == true) {
												if (selectCount < selectedTime) {
													selectCount += localdt;
												}
												else {
													selectCount = 0;
													entitiesInBattle[6]->isSelected = false;
												}
											}
											else {
												if (selectCount < selectTime) {
													selectCount += localdt;
												}
												else {
													selectCount = 0;
													entitiesInBattle[6]->isSelected = true;
												}
											}
										}
										else {
											entitiesInBattle[6]->isSelected = false;
										}
									}
								}
					}
				}
				if (entitiesInBattle[7] != nullptr) {
					if (entitiesInBattle[7]->isAlive == true) {
					
								enemyButton4->state != GuiControlState::PRESSED ? app->render->DrawTexture(attackTex, app->win->GetWidth() / 2 / 2 - (BUTTONS_W * NUM_BUTTONS + BUTTONS_SPACE_HOR * 3) / 2 + BUTTONS_W * 3 + BUTTONS_SPACE_HOR * 3 + LATERAL_MOVE, app->win->GetHeight() / 2 - BUTTONS_BOTTOM_SPACE) : app->render->DrawTexture(press_attackTex, app->win->GetWidth() / 2 / 2 - (BUTTONS_W * NUM_BUTTONS + BUTTONS_SPACE_HOR * 3) / 2 + BUTTONS_W * 3 + BUTTONS_SPACE_HOR * 3 + LATERAL_MOVE, app->win->GetHeight() / 2 - BUTTONS_BOTTOM_SPACE);
								if (entitiesInBattle[7] != nullptr) {
									if (entitiesInBattle[7]->isAlive == true) {
										if (enemyButton4->state == GuiControlState::FOCUSED) {
											if (entitiesInBattle[7]->isSelected == true) {
												if (selectCount < selectedTime) {
													selectCount += localdt;
												}
												else {
													selectCount = 0;
													entitiesInBattle[7]->isSelected = false;
												}
											}
											else {
												if (selectCount < selectTime) {
													selectCount += localdt;
												}
												else {
													selectCount = 0;
													entitiesInBattle[7]->isSelected = true;
												}
											}
										}
										else {
											entitiesInBattle[7]->isSelected = false;
										}
									}
								}
					}
				}
					
			}
			
			break;
		case BattlePhase::OUTCOME:
			if (hasChangedPhase == true) {
				app->font->CleanFonts();
				hasChangedPhase = false;
				for (int i = 4; i < 8; i++) {
					if (entitiesInBattle[i] != nullptr) {
						entitiesInBattle[i]->isSelected = false;
					}
				}
			}
			else {
				if (actualTurnEntity->stats->isStunned == true) {
					sprintf_s(damageChar, 100, "%s is stunned and can't move!", actualTurnEntity->name);
					app->font->DrawTextDelayed(damageChar, 10, 25);
				}
				else {
					if (damageTaken == 1) {
						sprintf_s(nameChar, 100, "%s takes  1 ", targetEntity->name);
						app->font->DrawTextDelayed(nameChar, 10, 25, { 255,100,0 });
						sprintf_s(damageChar, 100, "%s takes    point of damage!", targetEntity->name);
						app->font->DrawTextDelayed(damageChar, 10, 25);
					}
					else {
						sprintf_s(nameChar, 100, "%s takes %i", targetEntity->name, (int)damageTaken);
						app->font->DrawTextDelayed(nameChar, 10, 25, { 255,100,0 });
						sprintf_s(damageChar, 100, "%s takes     points of damage!", targetEntity->name);
						app->font->DrawTextDelayed(damageChar, 10, 25);
					}
				}
				
			}
			break;
		case BattlePhase::ATTACKING:
			if (hasChangedPhase == true) {
				app->font->CleanFonts();
				hasChangedPhase = false;
				for (int i = 4; i < 8; i++) {
					if (entitiesInBattle[i] != nullptr) {
						entitiesInBattle[i]->isSelected = false;
					}
				}
			}
			else {
				sprintf_s(nameChar, 100, "%s is attacking %s!", actualTurnEntity->name, targetEntity->name);
				app->font->DrawTextDelayed(nameChar, 10, 25);
			}
			break;

		case BattlePhase::DEFENDING:
			if (hasChangedPhase == true) {
				app->font->CleanFonts();
				hasChangedPhase = false;
			}
			else {
				sprintf_s(nameChar, 50, "%s is protected!", actualTurnEntity->name);
				app->font->DrawTextDelayed(nameChar, 10, 25);
			}
			
			break;

		case BattlePhase::USING_ITEM:
			if (hasChangedPhase == true) {
				app->font->CleanFonts();
				hasChangedPhase = false;
			}
			else {
				/*if (app->scene->itemList.count() == 0) {
					app->font->DrawTextDelayed("You have no items left!", 10, 25);
				}
				else {*/
					app->inventory->Enable();
				//}
			}
			break;

		case BattlePhase::ESCAPING:
			if (hasChangedPhase == true) {
				app->font->CleanFonts();
				hasChangedPhase = false;
			}
			else {
				if (hasTriedToEscape == false) {
					sprintf_s(nameChar, 50, "%s is trying to escape...", actualTurnEntity->name);
					app->font->DrawTextDelayed(nameChar, 10, 25);
				}
				else if (canEscape == false) {
					sprintf_s(escapeChar, 50, "%s could not escape!", actualTurnEntity->name);
					app->font->DrawTextDelayed(escapeChar, 10, 25);
				}
				else if (canEscape == true) {
					sprintf_s(escapeChar, 50, "%s could escape successfully!", actualTurnEntity->name);
					app->font->DrawTextDelayed(escapeChar, 10, 25);
				}
			}
			
			break;

			
		case BattlePhase::WIN:
			if (hasChangedPhase == true) {
				app->font->CleanFonts();
				hasChangedPhase = false;
				for (int i = 4; i < 8; i++) {
					if (entitiesInBattle[i] != nullptr) {
						entitiesInBattle[i]->isSelected = false;
					}
				}
			}
			else {
				app->font->DrawTextDelayed("Victory! All the enemies have been defeated", 10, 25, { 255,200,0 });
				break;
			}

		case BattlePhase::REWARD:
			if (hasChangedPhase == true) {
				app->font->CleanFonts();
				hasChangedPhase = false;
				for (int i = 4; i < 8; i++) {
					if (entitiesInBattle[i] != nullptr) {
						entitiesInBattle[i]->isSelected = false;
					}
				}
				for (int i = 0; i < app->scene->partyList.count(); i++) {
					app->scene->partyList.At(i)->data->stats->lvlup(expCount);
				}
			}
			else {
				sprintf_s(rewardChar, 150, "All the team members receive %i EXP and %i gold!", expCount, goldCount);
				app->font->DrawTextDelayed(rewardChar, 10, 25);
				
				break;
			}
			
		case BattlePhase::LOOT:
			if (hasChangedPhase == true) {
				app->font->CleanFonts();
				hasChangedPhase = false;
				for (int i = 4; i < 8; i++) {
					if (entitiesInBattle[i] != nullptr) {
						entitiesInBattle[i]->isSelected = false;
					}
				}
			}
			else {
				if (itemCount[0] != nullptr) {
					sprintf_s(lootChar, 100, "The enemies have dropped %s", itemCount[0]->name);
					app->font->DrawTextDelayed(lootChar, 10, 25);
				}
				
				break;
			}

		case BattlePhase::LOSE:
			if (hasChangedPhase == true) {
				app->font->CleanFonts();
				hasChangedPhase = false;
				for (int i = 4; i < 8; i++) {
					if (entitiesInBattle[i] != nullptr) {
						entitiesInBattle[i]->isSelected = false;
					}
				}
			}
			else {
				app->font->DrawTextDelayed("Game over! Press SPACE", 10, 25, { 255,30,10 });
			}
			break;
	}

	//Allies health
	for (int i = 3; i >=0; i--) {
		if (entitiesInBattle[i] != nullptr) {
			if (entitiesInBattle[i] != nullptr) {
				if (entitiesInBattle[i]->stats->health == 0) {
					sprintf_s(lifeChar, 50, "%s's health: %2d", entitiesInBattle[i]->name, (int)entitiesInBattle[i]->stats->health);
					app->font->DrawText(lifeChar, 10 * app->win->GetScale(), (app->win->GetHeight() / 2 - 30 - LIFE_DISTANCE * (3-i)) * app->win->GetScale(), { 255,30,0 }, false, 1);
					sprintf_s(nameChar, 50, "%s's health:", entitiesInBattle[i]->name, (int)entitiesInBattle[i]->stats->health);
					app->font->DrawText(nameChar, 10 * app->win->GetScale(), (app->win->GetHeight() / 2 - 30 - LIFE_DISTANCE * (3 - i)) * app->win->GetScale(), { 255,255,255 }, false, 1);

				}
				else if (entitiesInBattle[i]->stats->health <= 5) {


					sprintf_s(lifeChar, 50, "%s's health: %2d", entitiesInBattle[i]->name, (int)entitiesInBattle[i]->stats->health);
					app->font->DrawText(lifeChar, 10 * app->win->GetScale(), (app->win->GetHeight() / 2 - 30 - LIFE_DISTANCE * (3 - i)) * app->win->GetScale(), { 180,0,0 }, false, 1);
					sprintf_s(nameChar, 50, "%s's health:", entitiesInBattle[i]->name, (int)entitiesInBattle[i]->stats->health);
					app->font->DrawText(nameChar, 10 * app->win->GetScale(), (app->win->GetHeight() / 2 - 30 - LIFE_DISTANCE * (3 - i)) * app->win->GetScale(), { 255,255,255 }, false, 1);
				}
				else {
					sprintf_s(lifeChar, 50, "%s's health: %2d", entitiesInBattle[i]->name, (int)entitiesInBattle[i]->stats->health);
					app->font->DrawText(lifeChar, 10 * app->win->GetScale(), (app->win->GetHeight() / 2 - 30 - LIFE_DISTANCE * (3 - i)) * app->win->GetScale(), { 100,255,0 }, false, 1);
					sprintf_s(nameChar, 50, "%s's health:", entitiesInBattle[i]->name, (int)entitiesInBattle[i]->stats->health);
					app->font->DrawText(nameChar, 10 * app->win->GetScale(), (app->win->GetHeight() / 2 - 30 - LIFE_DISTANCE * (3 - i)) * app->win->GetScale(), { 255,255,255 }, false, 1);
					
				}
			}
		}
		
	}

	//Allies mana
	for (int i = 3; i >= 0; i--) {
		if (entitiesInBattle[i] != nullptr) {
			if (entitiesInBattle[i] != nullptr) {
				if (entitiesInBattle[i]->stats->health == 0) {
					sprintf_s(lifeChar, 50, "%s's Magic points: %2d", entitiesInBattle[i]->name, (int)entitiesInBattle[i]->stats->mana);
					app->font->DrawText(lifeChar, 10 * app->win->GetScale(), (app->win->GetHeight() / 2 - 20 - LIFE_DISTANCE * (3 - i)) * app->win->GetScale(), { 255,30,0 }, false, 1);
					sprintf_s(nameChar, 50, "%s's Magic points:", entitiesInBattle[i]->name, (int)entitiesInBattle[i]->stats->mana);
					app->font->DrawText(nameChar, 10 * app->win->GetScale(), (app->win->GetHeight() / 2 - 20 - LIFE_DISTANCE * (3 - i)) * app->win->GetScale(), { 255,255,255 }, false, 1);

				}
				else if (entitiesInBattle[i]->stats->health <= 5) {


					sprintf_s(lifeChar, 50, "%s's Magic points: %2d", entitiesInBattle[i]->name, (int)entitiesInBattle[i]->stats->mana);
					app->font->DrawText(lifeChar, 10 * app->win->GetScale(), (app->win->GetHeight() / 2 - 20 - LIFE_DISTANCE * (3 - i)) * app->win->GetScale(), { 180,0,0 }, false, 1);
					sprintf_s(nameChar, 50, "%s's Magic points:", entitiesInBattle[i]->name, (int)entitiesInBattle[i]->stats->mana);
					app->font->DrawText(nameChar, 10 * app->win->GetScale(), (app->win->GetHeight() / 2 - 20 - LIFE_DISTANCE * (3 - i)) * app->win->GetScale(), { 255,255,255 }, false, 1);
				}
				else {
					sprintf_s(lifeChar, 50, "%s's Magic points: %2d", entitiesInBattle[i]->name, (int)entitiesInBattle[i]->stats->mana);
					app->font->DrawText(lifeChar, 10 * app->win->GetScale(), (app->win->GetHeight() / 2 - 20 - LIFE_DISTANCE * (3 - i)) * app->win->GetScale(), { 100,255,0 }, false, 1);
					sprintf_s(nameChar, 50, "%s's Magic points:", entitiesInBattle[i]->name, (int)entitiesInBattle[i]->stats->mana);
					app->font->DrawText(nameChar, 10 * app->win->GetScale(), (app->win->GetHeight() / 2 - 20 - LIFE_DISTANCE * (3 - i)) * app->win->GetScale(), { 255,255,255 }, false, 1);

				}
			}
		}

	}

	//Enemies health
	for (int i = 7; i >= 4; i--) {
		if (entitiesInBattle[i] != nullptr) {
			if (entitiesInBattle[i] != nullptr) {
				if (entitiesInBattle[i]->stats->health == 0) {
					sprintf_s(lifeChar, 50, "%s's health: %2d", entitiesInBattle[i]->name, (int)entitiesInBattle[i]->stats->health);
					app->font->DrawText(lifeChar, (app->win->GetWidth() / 2 - LIFE_DISTANCE_HOR)* app->win->GetScale(), (app->win->GetHeight() / 2 - 30 - 15 * (3 - (i-4))) * app->win->GetScale(), { 255,30,0 }, false, 1);
					sprintf_s(nameChar, 50, "%s's health:", entitiesInBattle[i]->name, (int)entitiesInBattle[i]->stats->health);
					app->font->DrawText(nameChar, (app->win->GetWidth() / 2 - LIFE_DISTANCE_HOR)* app->win->GetScale(), (app->win->GetHeight() / 2 - 30 - 15 * (3 - (i - 4))) * app->win->GetScale(), { 255,255,255 }, false, 1);

				}
				else if (entitiesInBattle[i]->stats->health <= 5) {


					sprintf_s(lifeChar, 50, "%s's health: %2d", entitiesInBattle[i]->name, (int)entitiesInBattle[i]->stats->health);
					app->font->DrawText(lifeChar, (app->win->GetWidth() / 2 - LIFE_DISTANCE_HOR)* app->win->GetScale(), (app->win->GetHeight() / 2 - 30 - 15 * (3 - (i - 4))) * app->win->GetScale(), { 180,0,0 }, false, 1);
					sprintf_s(nameChar, 50, "%s's health:", entitiesInBattle[i]->name, (int)entitiesInBattle[i]->stats->health);
					app->font->DrawText(nameChar, (app->win->GetWidth() / 2 - LIFE_DISTANCE_HOR)* app->win->GetScale(), (app->win->GetHeight() / 2 - 30 - 15 * (3 - (i - 4)))* app->win->GetScale(), { 255,255,255 }, false, 1);
				}
				else {
					sprintf_s(lifeChar, 50, "%s's health: %2d", entitiesInBattle[i]->name, (int)entitiesInBattle[i]->stats->health);
					app->font->DrawText(lifeChar, (app->win->GetWidth() / 2 - LIFE_DISTANCE_HOR)* app->win->GetScale(), (app->win->GetHeight() / 2 - 30 - 15 * (3 - (i - 4))) * app->win->GetScale(), { 100,255,0 }, false, 1);
					sprintf_s(nameChar, 50, "%s's health:", entitiesInBattle[i]->name, (int)entitiesInBattle[i]->stats->health);
					app->font->DrawText(nameChar, (app->win->GetWidth() / 2 - LIFE_DISTANCE_HOR)* app->win->GetScale(), (app->win->GetHeight() / 2 - 30 - 15 * (3 - (i - 4))) * app->win->GetScale(), { 255,255,255 }, false, 1);

				}
			}
		}

	}

	return ret;
}

bool Battle::OnGuiMouseClickEvent(GuiControl* control)
{
	if (canSelect == true && actualTurnEntity->isAlive == true && (
		actualTurnEntity == entitiesInBattle[0] || actualTurnEntity == entitiesInBattle[1] ||
		actualTurnEntity == entitiesInBattle[2] || actualTurnEntity == entitiesInBattle[3])) {

		if (!app->inventory->isEnabled()) {
			switch (control->type)
			{
			case GuiControlType::BUTTON:

				switch (control->id) {
					//Thinking
				case 100:
					switch (battlePhase) {
					case BattlePhase::CHOOSE_ATTACK:
						ChangePhase(BattlePhase::THINKING);
						app->stages->fxbool = true;
						canSelect = false;
						app->audio->PlayFx(app->conf->btnSelection);
						break;
					case BattlePhase::SELECTING:
						ChangePhase(BattlePhase::CHOOSE_ATTACK);
						app->stages->fxbool = true;
						canSelect = false;
						app->audio->PlayFx(app->conf->btnSelection);
						switch (skill) {
						case 105:
							break;
							//Special Attacks
						case 110:
							actualTurnEntity->stats->mana += 2;
							break;
						case 111:
							actualTurnEntity->stats->mana += 4;
							break;
						case 112:
							actualTurnEntity->stats->mana += 6;
							break;
						case 120:
							actualTurnEntity->stats->mana += 2;
							break;
						case 121:
							actualTurnEntity->stats->mana += 4;
							break;
						case 122:
							actualTurnEntity->stats->mana += 6;
							break;
						case 130:
							actualTurnEntity->stats->mana += 2;
							break;
						case 131:
							actualTurnEntity->stats->mana += 4;
							break;
						case 132:
							actualTurnEntity->stats->mana += 6;
							break;
						case 140:
							actualTurnEntity->stats->mana += 2;
							break;
						case 141:
							actualTurnEntity->stats->mana += 4;
							break;
						case 142:
							actualTurnEntity->stats->mana += 6;
							break;
						default:
							break;
						}
						break;
					}
					break;
				case 101:
					ChangePhase(BattlePhase::CHOOSE_ATTACK);
					app->stages->fxbool = true;
					canSelect = false;
					app->audio->PlayFx(app->conf->btnSelection);

					break;
				case 102:

					ChangePhase(BattlePhase::DEFENDING);
					app->stages->fxbool = true;
					canSelect = false;
					app->audio->PlayFx(app->conf->btnSelection);
					break;
				case 103:

					ChangePhase(BattlePhase::USING_ITEM);
					app->stages->fxbool = true;
					canSelect = false;
					app->audio->PlayFx(app->conf->btnSelection);

					break;
				case 104:
					app->audio->PlayFx(app->conf->btnSelection);
					ChangePhase(BattlePhase::ESCAPING);
					app->stages->fxbool = true;
					canSelect = false;

					break;

					//Normal Attack
				case 105:
					skill = control->id;
					targetEntity = nullptr;
					ChangePhase(BattlePhase::SELECTING);
					app->stages->fxbool = true;
					canSelect = false;
					app->audio->PlayFx(app->conf->btnSelection);
					break;

					//Special Attacks
				case 110:
					if (actualTurnEntity->stats->mana >= 2) {
						actualTurnEntity->stats->mana -= 2;

						skill = control->id;
						targetEntity = nullptr;
						ChangePhase(BattlePhase::DEFENDING);
						app->stages->fxbool = true;
						canSelect = false;
						app->audio->PlayFx(app->conf->btnSelection);
					}
					
					break;
				case 111:
					if (actualTurnEntity->stats->mana >= 4) {
						actualTurnEntity->stats->mana -= 4;
						skill = control->id;
						targetEntity = nullptr;
						ChangePhase(BattlePhase::SELECTING);
						app->stages->fxbool = true;
						canSelect = false;
						app->audio->PlayFx(app->conf->btnSelection);
					}
					break;
				case 112:
					if (actualTurnEntity->stats->mana >= 6) {
						actualTurnEntity->stats->mana -= 6;
						skill = control->id;
						targetEntity = nullptr;
						ChangePhase(BattlePhase::SELECTING);
						app->stages->fxbool = true;
						canSelect = false;
						app->audio->PlayFx(app->conf->btnSelection);
					}
					break;

				case 120:
					if (actualTurnEntity->stats->mana >= 2) {
						actualTurnEntity->stats->mana -= 2;
						skill = control->id;
						targetEntity = nullptr;
						ChangePhase(BattlePhase::SELECTING);
						app->stages->fxbool = true;
						canSelect = false;
						app->audio->PlayFx(app->conf->btnSelection);
					}
					break;
				case 121:
					if (actualTurnEntity->stats->mana >= 4) {
						actualTurnEntity->stats->mana -= 4;
						skill = control->id;
						targetEntity = nullptr;
						ChangePhase(BattlePhase::SELECTING);
						app->stages->fxbool = true;
						canSelect = false;
						app->audio->PlayFx(app->conf->btnSelection);
					}
					break;
				case 122:
					if (actualTurnEntity->stats->mana >= 6) {
						actualTurnEntity->stats->mana -= 6;
						skill = control->id;
						targetEntity = nullptr;
						ChangePhase(BattlePhase::DEFENDING);
						app->stages->fxbool = true;
						canSelect = false;
						app->audio->PlayFx(app->conf->btnSelection);
					}
					break;

				case 130:
					if (actualTurnEntity->stats->mana >= 2) {
						actualTurnEntity->stats->mana -= 2;
						skill = control->id;
						targetEntity = nullptr;
						ChangePhase(BattlePhase::SELECTING);
						app->stages->fxbool = true;
						canSelect = false;
						app->audio->PlayFx(app->conf->btnSelection);
					}
					break;
				case 131:
					if (actualTurnEntity->stats->mana >= 4) {
						actualTurnEntity->stats->mana -= 4;
						skill = control->id;
						targetEntity = nullptr;
						ChangePhase(BattlePhase::SELECTING);
						app->stages->fxbool = true;
						canSelect = false;
						app->audio->PlayFx(app->conf->btnSelection);
					}
					break;
				case 132:
					if (actualTurnEntity->stats->mana >= 6) {
						actualTurnEntity->stats->mana -= 6;
						skill = control->id;
						targetEntity = nullptr;
						ChangePhase(BattlePhase::SELECTING);
						app->stages->fxbool = true;
						canSelect = false;
						app->audio->PlayFx(app->conf->btnSelection);
					}
					break;

				case 140:
					if (actualTurnEntity->stats->mana >= 2) {
						actualTurnEntity->stats->mana -= 2;
						skill = control->id;
						targetEntity = nullptr;
						ChangePhase(BattlePhase::SELECTING);
						app->stages->fxbool = true;
						canSelect = false;
						app->audio->PlayFx(app->conf->btnSelection);
					}
					break;
				case 141:
					if (actualTurnEntity->stats->mana >= 4) {
						actualTurnEntity->stats->mana -= 4;
						skill = control->id;
						targetEntity = nullptr;
						ChangePhase(BattlePhase::SELECTING);
						app->stages->fxbool = true;
						canSelect = false;
						app->audio->PlayFx(app->conf->btnSelection);
					}
					break;
				case 142:
					if (actualTurnEntity->stats->mana >= 6) {
						actualTurnEntity->stats->mana -= 6;
						skill = control->id;
						targetEntity = nullptr;
						ChangePhase(BattlePhase::SELECTING);
						app->stages->fxbool = true;
						canSelect = false;
						app->audio->PlayFx(app->conf->btnSelection);
					}
					break;

					//Selecting
				case 150:
					targetEntity = entitiesInBattle[4];
					app->stages->fxbool = true;
					canSelect = false;
					app->audio->PlayFx(app->conf->btnSelection);
					break;
				case 151:
					targetEntity = entitiesInBattle[5];
					app->stages->fxbool = true;
					canSelect = false;
					app->audio->PlayFx(app->conf->btnSelection);
					break;
				case 152:
					targetEntity = entitiesInBattle[6];
					app->stages->fxbool = true;
					canSelect = false;
					app->audio->PlayFx(app->conf->btnSelection);
					break;
				case 153:
					targetEntity = entitiesInBattle[7];
					app->stages->fxbool = true;
					canSelect = false;
					app->audio->PlayFx(app->conf->btnSelection);
					break;
				}

				break;

				//Other cases here
			default:
				break;
			}
		}
	}
		
	return true;
}

void Battle::SetTurnOrder() 
{
	//TURN ORDER: PLAYER - ENEMY
	//if (hasStarted == false) {

	//	if (entitiesInBattle[0]->stats->speed >= entitiesInBattle[4]->stats->speed) {
	//		actualTurnEntity = entitiesInBattle[0];
	//	}
	//	else {
	//		actualTurnEntity = entitiesInBattle[4];
	//	}

	//	hasStarted = true;
	//}
	//else {
	//	if (actualTurnEntity == entitiesInBattle[0]) {
	//		actualTurnEntity = entitiesInBattle[4];
	//		
	//	}
	//	else if (actualTurnEntity == entitiesInBattle[4]) {
	//		actualTurnEntity = entitiesInBattle[0];
	//	}
	//}

	//TURN ORDER: TURN VALUE
	//Set the minor turn value from all entities in battle

	if (hasStarted == false) {
		for (int h = 0; h < 5; h++) {
			turnValue = 0.0f;
			for (int i = 0; i < 8; i++) {
				if (entitiesInBattle[i] != nullptr) {
					if (entitiesInBattle[i]->isAlive == true) {
						if (turnValue == 0) {
							turnValue = entitiesInBattle[i]->stats->TurnValue();
						}
						else if (entitiesInBattle[i]->stats->TurnValue() < turnValue)
						{
							turnValue = entitiesInBattle[i]->stats->TurnValue();
						}
					}
				}

			}

			//Compare if more than one entities have the same turn value
			DynamicEntity* equalTurnValue[8];

			int equalValues = 0;
			for (int j = 0; j < 8; j++) {
				if (entitiesInBattle[j] != nullptr) {
					if (entitiesInBattle[j]->isAlive == true) {
						if (entitiesInBattle[j]->stats->TurnValue() == turnValue) {
							equalTurnValue[equalValues] = entitiesInBattle[j];
							equalValues++;
						}
					}
				}
			}

			//Choose a random one and set turn
			if (equalValues > 1) {
				srand(time(NULL));
				int chosenValue = (rand() % equalValues);

				turnsTimeLine[h] = equalTurnValue[chosenValue];
				equalTurnValue[chosenValue]->stats->localTurn++;
			}
			else {
				turnsTimeLine[h] = equalTurnValue[0];
				equalTurnValue[0]->stats->localTurn++;
			}

		}

		actualTurnEntity = turnsTimeLine[0];

		hasStarted = true;
	}
	else {
		turnValue = 0.0f;
		for (int i = 0; i < 8; i++) {
			if (entitiesInBattle[i] != nullptr) {
				if (entitiesInBattle[i]->isAlive == true) {
					if (turnValue == 0) {
						turnValue = entitiesInBattle[i]->stats->TurnValue();
					}
					else if (entitiesInBattle[i]->stats->TurnValue() < turnValue)
					{
						turnValue = entitiesInBattle[i]->stats->TurnValue();
					}
				}
			}

		}

		//Compare if more than one entities have the same turn value
		DynamicEntity* equalTurnValue[8];

		int equalValues = 0;
		for (int j = 0; j < 8; j++) {
			if (entitiesInBattle[j] != nullptr) {
				if (entitiesInBattle[j]->isAlive == true) {
					if (entitiesInBattle[j]->stats->TurnValue() == turnValue) {
						equalTurnValue[equalValues] = entitiesInBattle[j];
						equalValues++;
					}
				}
			}
		}

		bool noNull = true;

		for (int k = 0; k < 5; k++) {
			if(turnsTimeLine[k]==nullptr){


				noNull = false;
				//Choose a random one and set turn
				if (equalValues > 1) {
					srand(time(NULL));
					int chosenValue = (rand() % equalValues);

					turnsTimeLine[k] = equalTurnValue[chosenValue];
					turnsTimeLine[k]->stats->localTurn++;
				}
				else {
					turnsTimeLine[k] = equalTurnValue[0];
					turnsTimeLine[k]->stats->localTurn++;
				}

				//actualTurnEntity = turnsTimeLine[0];

				break;

			}
			
		}

		if (noNull == true) {
			turnsTimeLine[0] = turnsTimeLine[1];
			turnsTimeLine[1] = turnsTimeLine[2];
			turnsTimeLine[2] = turnsTimeLine[3];
			turnsTimeLine[3] = turnsTimeLine[4];


			//Choose a random one and set turn
			if (equalValues > 1) {
				srand(time(NULL));
				int chosenValue = (rand() % equalValues);

				turnsTimeLine[4] = equalTurnValue[chosenValue];
				turnsTimeLine[4]->stats->localTurn++;
			}
			else {
				turnsTimeLine[4] = equalTurnValue[0];
				turnsTimeLine[4]->stats->localTurn++;
			}
		}
		
		

		actualTurnEntity = turnsTimeLine[0];

	}
	


}

void Battle::Attack(DynamicEntity *target) {

	damageTaken = 0;
	/*switch (skill) {
	case 0:
		actualTurnEntity->stats->attack += 0;
		break;
	case 1:
		actualTurnEntity->stats->attack += 3;
		actualTurnEntity->stats->mana -= 2;
		break;
	case 2:
		actualTurnEntity->stats->attack += 6;
		actualTurnEntity->stats->mana -= 4;
		break;
	case 3:
		actualTurnEntity->stats->attack += 10;
		actualTurnEntity->stats->mana -= 6;
		break;
	default:
		actualTurnEntity->stats->attack += 0;
		break;
	}*/
	switch (skill) {
		//Special Attacks
	case 110:
		actualTurnEntity->stats->attackMulti = 1;
		break;
	case 111:
		actualTurnEntity->stats->attackMulti = 2;
		break;
	case 112:
		actualTurnEntity->stats->attackMulti = 3;
		break;

	case 120:
		actualTurnEntity->stats->attackMulti = 2;
		break;
	case 121:
		actualTurnEntity->stats->attackMulti = 3;
		break;
	case 122:
		actualTurnEntity->stats->attackMulti = 1;
		break;

	case 130:
		actualTurnEntity->stats->attackMulti = 2;
		break;
	case 131:
		actualTurnEntity->stats->attackMulti = 1;
		target->stats->isStunned = true;
		break;
	case 132:
		actualTurnEntity->stats->attackMulti = 3;
		break;

	case 140:
		actualTurnEntity->stats->attackMulti = 2;
		break;
	case 141:
		actualTurnEntity->stats->attackMulti = 1;
		target->stats->isStunned = true;
		break;
	case 142:
		actualTurnEntity->stats->attackMulti = 3;
		break;

	default:
		actualTurnEntity->stats->attackMulti = 1;
		break;
	}

	if (target == entitiesInBattle[4])
	{
		choos.del(choos.At(1));
	}
	if (target == entitiesInBattle[5])
	{
		choos.del(choos.At(2));
	}
	if (target == entitiesInBattle[6])
	{
		choos.del(choos.At(3));
	}
	if (target == entitiesInBattle[7])
	{
		choos.del(choos.At(4));
	}

	if ((int)target->stats->defense * actualTurnEntity->stats->defMulti < (int)actualTurnEntity->stats->attack * actualTurnEntity->stats->attackMulti) {
		damageTaken = (int)actualTurnEntity->stats->attack * actualTurnEntity->stats->attackMulti - (int)target->stats->defense * actualTurnEntity->stats->defMulti;
		target->stats->health = (int)target->stats->health + (int)target->stats->defense * actualTurnEntity->stats->defMulti - (int)actualTurnEntity->stats->attack * actualTurnEntity->stats->attackMulti;
		hasToShake = true;
		app->audio->PlayFx(explosionfx);
		shakePos = 0;
		target->takesDamage = true;
	}
	
	if (target->stats->health <= 0) {
		target->stats->health = 0;
		target->stats->defense -= defenseBuff;
		target->stats->defenseBuffed = false;
		target->stats->attackMulti = 1;
		target->stats->defMulti = 1;
		target->stats->isStunned = false;
		target->isAlive = false;

		DynamicEntity* newTimeLine[5] = { nullptr,nullptr, nullptr, nullptr, nullptr };

		//Select each living entity in timeline
		for (int i = 0; i < 5; i++) {
			if (turnsTimeLine[i]->isAlive == true) {
				//Introduce it to a new array in order
				for (int j = 0; j < 5; j++) {
					if (newTimeLine[j] == nullptr) {
						newTimeLine[j] = turnsTimeLine[i];
						break;
					}

				}
			}
		}

		int emptySpots = 0;

		//Replace the old timeline with the new one
		for (int k = 0; k < 5; k++) {
			if (newTimeLine[k] != nullptr) {
				turnsTimeLine[k] = newTimeLine[k];
			}
			else {
				turnsTimeLine[k] = nullptr;
				emptySpots++;
			}

		}

		/*LOG("%d aaaaaaaaaaaaaaaaaaa", awa);*/
		//Fill the new timeline
		for (int k = 0; k < emptySpots; k++) {

			SetTurnOrder();
		}

		if (target == entitiesInBattle[4] || target == entitiesInBattle[5] || target == entitiesInBattle[6] || target == entitiesInBattle[7]) {


			if (target->name == "Bat")
			{
				expCount += 20;
				goldCount += 2;
				app->scene->player->PlayerMoney += 2;

			}
			if (target->name == "Flying eye")
			{
				expCount += 50;
				goldCount += 6;
				app->scene->player->PlayerMoney += 6;
			}
			if (target->name == "Skeleton")
			{
				expCount += 100;
				goldCount += 10;
				app->scene->player->PlayerMoney += 10;
			}
			if (target->battleName == " Valion")
			{
				expCount += 100;
				goldCount += 10;
				app->scene->player->PlayerMoney += 10;
			}
			if (target->battleName == " Rayla")
			{
				expCount += 100;
				goldCount += 10;
				app->scene->player->PlayerMoney += 10;
			}
			if (target->battleName == " Dhion")
			{
				expCount += 100;
				goldCount += 10;
				app->scene->player->PlayerMoney += 10;
			}
			/*if (!app->scene->godmode) {
				for (int i = 0; i < app->scene->partyList.count(); i++) {
					if (target->name == "Bat")
					{
						LOG("aaaaaaaaaaaaaaaaaaa");
						app->scene->partyList.At(i)->data->stats->lvlup(20);

					}
					if (target->name == "Flying eye")
					{
						LOG("oooooooooooooooooooo");
						app->scene->partyList.At(i)->data->stats->lvlup(50);
					}
					if (target->name == "Skeleton")
					{
						LOG("eeeeeeeeeeeeeeeeeeeeeee");
						app->scene->partyList.At(i)->data->stats->lvlup(100);

					}
					if (target->battleName == " Valion")
					{
						app->scene->partyList.At(i)->data->stats->lvlup(100);
					}
					if (target->battleName == " Rayla")
					{
						app->scene->partyList.At(i)->data->stats->lvlup(100);
					}
					if (target->battleName == " Dhion")
					{
						app->scene->partyList.At(i)->data->stats->lvlup(100);
					}
				}
			}*/

			if (target->name != "Valion" && target->name != "Rayla" && target->name != "Dhion" && target->name != "Truck-kun") {
				optionPercent = 0;
					srand(time(NULL));
					optionPercent = rand() % 100;

					if (optionPercent <= 20) {
						for (int i = 0; i < 4; i++) {
							if (itemCount[i] == nullptr) {

								optionPercent = 0;
									srand(time(NULL));
									optionPercent = rand() % 24;
								itemCount[i] = new Usable(UsableType(optionPercent));

								break;
							}

						}
					}
			}
		}
	
		
	}
	
}

void Battle::Defense() {
	switch (skill) {
		//Special Attacks
	case 110:
		actualTurnEntity->stats->defMulti = 2;
		break;
	case 111:
		actualTurnEntity->stats->defMulti = 1;
		break;
	case 112:
		actualTurnEntity->stats->defMulti = 1;
		break;

	case 120:
		actualTurnEntity->stats->defMulti = 1;
		break;
	case 121:
		actualTurnEntity->stats->defMulti = 1;
		break;
	case 122:
		actualTurnEntity->stats->defMulti = 2;
		break;

	case 130:
		actualTurnEntity->stats->defMulti = 1;
		break;
	case 131:
		actualTurnEntity->stats->defMulti = 1;
		break;
	case 132:
		actualTurnEntity->stats->defMulti = 2;
		break;

	case 140:
		actualTurnEntity->stats->defMulti = 1;
		break;
	case 141:
		actualTurnEntity->stats->defMulti = 1;
		break;
	case 142:
		actualTurnEntity->stats->defMulti = 1;
		break;

	default:
		actualTurnEntity->stats->defMulti = 1;
		break;
	}

	actualTurnEntity->stats->defense += defenseBuff * actualTurnEntity->stats->defMulti;
	actualTurnEntity->stats->defenseBuffed = true;
}

void Battle::UseItem(DynamicEntity target) {
	
}

bool Battle::Escape() {

	bool ret;

	srand(time(NULL));
	int percent = (rand() % (100 - 0)) + 0;

	if (percent > 70) {
		ret = true;
	}
	else {
		ret = false;
	}
	
	if (entitiesInBattle[4]->name == "Truck-kun" || entitiesInBattle[4]->name == "Valion" || entitiesInBattle[4]->name == "Rayla" || entitiesInBattle[4]->name == "Dhion") {
		ret = false;
	}

	if (actualTurnEntity->activeOnStage == StageIndex::DOJO) {
		ret = false;
	}

	return ret;
}

int Battle::CountAllies() {

	int allies = 0;

	for (int i = 0; i < 4; i++) {
		if (entitiesInBattle[i] != nullptr) {
			if (entitiesInBattle[i]->isAlive == true) {
				allies++;
			}
		}
	}

	return allies;
}

int Battle::CountEnemies() {

	int enemies = 0;

	for (int i = 4; i < 8; i++) {
		if (entitiesInBattle[i] != nullptr) {
			if (entitiesInBattle[i]->isAlive == true) {
				enemies++;
			}
		}
	}

	return enemies;
}


bool Battle::CheckWinLose() {

	bool ret = false;

	alliesCount = CountAllies();
	enemiesCount = CountEnemies();

	if (alliesCount <= 0) {
		ChangePhase(BattlePhase::LOSE);
		ret = true;
	}
	else if (enemiesCount <= 0) {
		ChangePhase(BattlePhase::WIN);
		ret = true;
	}

	return ret;
}

void Battle::ChangePhase(BattlePhase phase) {
	hasChangedPhase = true;
	battlePhase = phase;
}

// Called before quitting
bool Battle::CleanUp()
{
	//Buttons

	backButton->state = GuiControlState::DISABLED;

	attackButton->state = GuiControlState::DISABLED;
	defenseButton->state = GuiControlState::DISABLED;
	itemButton->state = GuiControlState::DISABLED;
	escapeButton->state = GuiControlState::DISABLED;

	enemyButton1->state = GuiControlState::DISABLED;
	enemyButton2->state = GuiControlState::DISABLED;
	enemyButton3->state = GuiControlState::DISABLED;
	enemyButton4->state = GuiControlState::DISABLED;

	normalAttackButton->state = GuiControlState::DISABLED;

	playerSpecialButton1->state = GuiControlState::DISABLED;
	playerSpecialButton2->state = GuiControlState::DISABLED;
	playerSpecialButton3->state = GuiControlState::DISABLED;

	valionSpecialButton1->state = GuiControlState::DISABLED;
	valionSpecialButton2->state = GuiControlState::DISABLED;
	valionSpecialButton3->state = GuiControlState::DISABLED;

	raylaSpecialButton1->state = GuiControlState::DISABLED;
	raylaSpecialButton2->state = GuiControlState::DISABLED;
	raylaSpecialButton3->state = GuiControlState::DISABLED;

	dhionSpecialButton1->state = GuiControlState::DISABLED;
	dhionSpecialButton2->state = GuiControlState::DISABLED;
	dhionSpecialButton3->state = GuiControlState::DISABLED;



	backButton = nullptr;
	delete backButton;

	attackButton = nullptr;
	delete attackButton;

	defenseButton = nullptr;
	delete defenseButton;

	itemButton = nullptr;
	delete itemButton;

	escapeButton = nullptr;
	delete escapeButton;

	//Skills

	normalAttackButton = nullptr;
	delete normalAttackButton;

	playerSpecialButton1 = nullptr;
	delete playerSpecialButton1;

	playerSpecialButton2 = nullptr;
	delete playerSpecialButton2;

	playerSpecialButton3 = nullptr;
	delete playerSpecialButton3;


	valionSpecialButton1 = nullptr;
	delete valionSpecialButton1;

	valionSpecialButton2 = nullptr;
	delete valionSpecialButton2;

	valionSpecialButton3 = nullptr;
	delete valionSpecialButton3;


	raylaSpecialButton1 = nullptr;
	delete raylaSpecialButton1;
	raylaSpecialButton2 = nullptr;
	delete raylaSpecialButton2;
	raylaSpecialButton3 = nullptr;
	delete raylaSpecialButton3;


	dhionSpecialButton1 = nullptr;
	delete dhionSpecialButton1;
	dhionSpecialButton2 = nullptr;
	delete dhionSpecialButton2;
	dhionSpecialButton3 = nullptr;
	delete dhionSpecialButton3;

	//Textures

	backButtonTex = nullptr;
	delete backButtonTex;

	attackTex = nullptr;
	delete attackTex;

	defenseTex = nullptr;
	delete defenseTex;

	itemsTex = nullptr;
	delete itemsTex;

	press_escapeTex = nullptr;
	delete press_escapeTex;

	press_attackTex = nullptr;
	delete press_attackTex;

	press_defenseTex = nullptr;
	delete press_defenseTex;

	press_itemsTex = nullptr;
	delete press_itemsTex;

	press_escapeTex = nullptr;
	delete press_escapeTex;


	batButtonTex = nullptr;
	delete batButtonTex;

	flyingEyeButtonTex = nullptr;
	delete flyingEyeButtonTex;

	skeletonButtonTex = nullptr;
	delete skeletonButtonTex;

	press_batButtonTex = nullptr;
	delete press_batButtonTex;

	press_flyingEyeButtonTex = nullptr;
	delete press_flyingEyeButtonTex;

	press_skeletonButtonTex = nullptr;
	delete press_skeletonButtonTex;


	shield = nullptr;
	delete shield;

	for (int i = 0; i < 8; i++) {
		if (entitiesInBattle[i] != nullptr) {

			if (entitiesInBattle[i]->stats->defenseBuffed == true) {
				entitiesInBattle[i]->stats->defense -= defenseBuff;
				entitiesInBattle[i]->stats->defenseBuffed = false;
			}

			if (entitiesInBattle[i]->stats->attackMulti != 1) {
				entitiesInBattle[i]->stats->attackMulti = 1;
			}

			if (entitiesInBattle[i]->stats->defMulti != 1) {
				entitiesInBattle[i]->stats->defMulti = 1;
			}

			if (entitiesInBattle[i]->stats->isStunned == true) {
				entitiesInBattle[i]->stats->defMulti = false;
			}
		}
	}

	switch(battlePhase) {
	case BattlePhase::REWARD:
		
		if (entitiesInBattle[4]->name == "Valion") {
			app->scene->player->valionDefeated = true;
			app->scene->player->autoTalk = true;
		}
		if (entitiesInBattle[4]->name == "Rayla") {
			app->scene->player->raylaDefeated = true;
			app->scene->player->autoTalk = true;
		}
		if (entitiesInBattle[4]->name == "Dhion") {
			app->scene->player->dhionDefeated = true;
			app->scene->player->autoTalk = true;
		}

		//Destroy enemy
		for (int i = 4; i < 8; i++) {
			if (entitiesInBattle[i] != nullptr) {
				app->entities->DestroyEntity(entitiesInBattle[i]);
				app->scene->normalEnemyList.del(app->scene->normalEnemyList.At(app->scene->normalEnemyList.find((NormalEnemy*)entitiesInBattle[i])));
			}
		}

		app->stages->playerPtr->winCount += 1;
		
		//Take back player position
		app->stages->playerPtr->position = app->stages->playerPtr->mapPosition;
		app->camera->SetTarget(app->stages->playerPtr);
		app->camera->OnTarget();
		//app->camera->SetLimits(640, 350, 4490, 4200);

		//Take back player animation
		app->stages->playerPtr->currentAnimation = app->stages->playerPtr->mapAnimation;

		app->stages->playerPtr->canMove = true;
		app->map->LoadCol();
		app->stages->onBattle = false;

		switch (app->stages->actualStage) {
		case StageIndex::NONE:
			break;
		case StageIndex::TOWN:
			app->audio->PlayMusic("Assets/audio/music/music_town.ogg");
			break;
		case StageIndex::DOJO:
			app->audio->PlayMusic("Assets/audio/music/music_dojo.ogg");
			break;
		case StageIndex::SHOP:
			app->audio->PlayMusic("Assets/audio/music/music_shop.ogg");
			break;
		case StageIndex::SHOPSUB:
			app->audio->PlayMusic("Assets/audio/music/music_shopsub.ogg");
			break;
		case StageIndex::TAVERN:
			app->audio->PlayMusic("Assets/audio/music/music_tavern.ogg");
			break;
		case StageIndex::TOWER_0:
			app->audio->PlayMusic("Assets/audio/music/music_floors_top.ogg");
			break;
		case StageIndex::TOWER_1:
			app->audio->PlayMusic("Assets/audio/music/music_floors_top.ogg");
			break;
		case StageIndex::TOWER_2:
			app->audio->PlayMusic("Assets/audio/music/music_floors_top.ogg");
			break;
		case StageIndex::TOWER_3:
			app->audio->PlayMusic("Assets/audio/music/music_floors_top.ogg");
			break;
		case StageIndex::TOWER_FINAL_BOSS:
			app->stages->ChangeStage(StageIndex::WIN);
			break;
		case StageIndex::TOWER_BOSS_1:
			app->audio->PlayMusic("Assets/audio/music/music_floors_mid.ogg");
			break;
		case StageIndex::TOWER_BOSS_2:
			app->audio->PlayMusic("Assets/audio/music/music_floors_mid.ogg");
			break; 
		case StageIndex::TOWER_BOSS_3:
				app->audio->PlayMusic("Assets/audio/music/music_floors_mid.ogg");
				break;
		}

		app->scene->player->toggleGui = true;

		break;
	case BattlePhase::LOOT:

		if (entitiesInBattle[4]->name == "Valion") {
			int newX = 80;
			int newY = 130 - 50;
			if (app->scene->partyList.At(1) == nullptr) {
				app->scene->partyList.add((Party*)app->entities->CreateEntity(PartyType::VALION, newX, newY));
			}
			else {
				app->scene->partyList.del(app->scene->partyList.At(1));
				app->scene->partyList.add((Party*)app->entities->CreateEntity(PartyType::VALION, newX, newY));
			}
		}
		if (entitiesInBattle[4]->name == "Rayla") {
			int newX = -200;
			int newY = 120 - 50;
			if (app->scene->partyList.At(2) == nullptr) {
				app->scene->partyList.add((Party*)app->entities->CreateEntity(PartyType::RAYLA, newX, newY));
			}
			else {
				app->scene->partyList.del(app->scene->partyList.At(2));
				app->scene->partyList.add((Party*)app->entities->CreateEntity(PartyType::RAYLA, newX, newY));
			}
		}
		if (entitiesInBattle[4]->name == "Dhion") {
			int newX = 200;
			int newY = 0 - 50;
			if (app->scene->partyList.At(3) == nullptr) {
				app->scene->partyList.add((Party*)app->entities->CreateEntity(PartyType::DHION, newX, newY));
			}
			else {
				app->scene->partyList.del(app->scene->partyList.At(3));
				app->scene->partyList.add((Party*)app->entities->CreateEntity(PartyType::RAYLA, newX, newY));
			}
		}

		//Destroy enemy
		for (int i = 4; i < 8; i++) {
			if (entitiesInBattle[i] != nullptr) {
				app->entities->DestroyEntity(entitiesInBattle[i]);
				app->scene->normalEnemyList.del(app->scene->normalEnemyList.At(app->scene->normalEnemyList.find((NormalEnemy*)entitiesInBattle[i])));
			}
		}

		app->stages->playerPtr->winCount += 1;

		//Take back player position
		app->stages->playerPtr->position = app->stages->playerPtr->mapPosition;
		app->camera->SetTarget(app->stages->playerPtr);
		app->camera->OnTarget();
		//app->camera->SetLimits(640, 350, 4490, 4200);

		//Take back player animation
		app->stages->playerPtr->currentAnimation = app->stages->playerPtr->mapAnimation;

		app->stages->playerPtr->canMove = true;
		app->map->LoadCol();
		app->stages->onBattle = false;

		switch (app->stages->actualStage) {
		case StageIndex::NONE:
			break;
		case StageIndex::TOWN:
			app->audio->PlayMusic("Assets/audio/music/music_town.ogg");
			break;
		case StageIndex::DOJO:
			app->audio->PlayMusic("Assets/audio/music/music_dojo.ogg");
			break;
		case StageIndex::SHOP:
			app->audio->PlayMusic("Assets/audio/music/music_shop.ogg");
			break;
		case StageIndex::SHOPSUB:
			app->audio->PlayMusic("Assets/audio/music/music_shopsub.ogg");
			break;
		case StageIndex::TAVERN:
			app->audio->PlayMusic("Assets/audio/music/music_tavern.ogg");
			break;
		}

		app->scene->player->toggleGui = true;

		break;
	case BattlePhase::LOSE:
		
		//Destroy enemy
		for (int i = 4; i < 8; i++) {
			if (entitiesInBattle[i] != nullptr) {
				app->entities->DestroyEntity(entitiesInBattle[i]);
				app->scene->normalEnemyList.del(app->scene->normalEnemyList.At(app->scene->normalEnemyList.find((NormalEnemy*)entitiesInBattle[i])));
			}
		}
	
		//Take back player position
		app->stages->playerPtr->position = app->stages->playerPtr->mapPosition;
		app->camera->SetTarget(app->stages->playerPtr);
		app->camera->OnTarget();
		//app->camera->SetLimits(640, 350, 4490, 4200);

		//Take back player animation
		app->stages->playerPtr->currentAnimation = app->stages->playerPtr->mapAnimation;

		app->stages->onBattle = false;

	/*	app->scene->Disable();
		app->titleScene->Enable();*/
		
		if (app->stages->actualStage == StageIndex::PROLOGUE) {
			app->stages->playerPtr->stats->health = app->stages->playerPtr->stats->maxHealth;
			app->stages->playerPtr->isAlive = true;
			app->stages->ChangeStage(StageIndex::TOWN);
		}
		else {
			app->stages->ChangeStage(StageIndex::LOSE);
		}

		break;

	case BattlePhase::ESCAPING:
		if (actualTurnEntity->dynamicType == DynamicType::CHARACTER) {

			//Destroy enemy
			for (int i = 5; i < 8; i++) {
				if (entitiesInBattle[i] != nullptr ) {
					app->entities->DestroyEntity(entitiesInBattle[i]);
					app->scene->normalEnemyList.del(app->scene->normalEnemyList.At(app->scene->normalEnemyList.find((NormalEnemy*)entitiesInBattle[i])));
				}
			}

			entitiesInBattle[4]->isAlive = true;

			ListItem<NormalEnemy*>* NormalEnemyInList;
			NormalEnemyInList = app->stages->normalEnemyListPtr->start;
			for (NormalEnemyInList = app->stages->normalEnemyListPtr->start; NormalEnemyInList != NULL; NormalEnemyInList = NormalEnemyInList->next)
			{
				if (NormalEnemyInList->data == entitiesInBattle[4]) {
					NormalEnemyInList->data->chasePlayer = false;
				}
			}
			//Take back enemy position
			entitiesInBattle[4]->position = entitiesInBattle[4]->mapPosition;
			//Take back enemy animation
			entitiesInBattle[4]->currentAnimation = entitiesInBattle[4]->mapAnimation;


			//Take back player position
			app->stages->playerPtr->position = { app->stages->playerPtr->mapPosition.x ,entitiesInBattle[4]->baseCollider->rect.y + entitiesInBattle[4]->baseCollider->rect.h +1 - app->stages->playerPtr->colDownDistance };
			app->camera->SetTarget(app->stages->playerPtr);
			app->camera->OnTarget();
			//app->camera->SetLimits(640, 350, 4490, 4200);

			//Take back player animation
			app->stages->playerPtr->currentAnimation = app->stages->playerPtr->mapAnimation;

			app->stages->playerPtr->canMove = true;
			app->map->LoadCol();
			app->stages->onBattle = false;

			switch (app->stages->actualStage) {
			case StageIndex::NONE:
				break;
			case StageIndex::TOWN:
				app->audio->PlayMusic("Assets/audio/music/music_town.ogg");
				break;
			case StageIndex::DOJO:
				app->audio->PlayMusic("Assets/audio/music/music_dojo.ogg");
				break;
			case StageIndex::SHOP:
				app->audio->PlayMusic("Assets/audio/music/music_shop.ogg");
				break;
			case StageIndex::SHOPSUB:
				app->audio->PlayMusic("Assets/audio/music/music_shopsub.ogg");
				break;
			case StageIndex::TAVERN:
				app->audio->PlayMusic("Assets/audio/music/music_tavern.ogg");
				break;
			}

			app->scene->player->toggleGui = true;

		}
		if (actualTurnEntity->dynamicType == DynamicType::ENEMY) {

			//Destroy enemy
			for (int i = 4; i < 8; i++) {
				if (entitiesInBattle[i] != nullptr) {
					app->entities->DestroyEntity(entitiesInBattle[i]);
					app->scene->normalEnemyList.del(app->scene->normalEnemyList.At(app->scene->normalEnemyList.find((NormalEnemy*)entitiesInBattle[i])));
				}
			}
			
			app->stages->playerPtr->winCount += 1;
			//Take back player position
			app->stages->playerPtr->position = app->stages->playerPtr->mapPosition;
			app->camera->SetTarget(app->stages->playerPtr);
			app->camera->OnTarget();
			//app->camera->SetLimits(640, 350, 4490, 4200);

			//Take back player animation
			app->stages->playerPtr->currentAnimation = app->stages->playerPtr->mapAnimation;

			app->stages->playerPtr->canMove = true;
			app->map->LoadCol();
			app->stages->onBattle = false;

			switch (app->stages->actualStage) {
			case StageIndex::NONE:
				break;
			case StageIndex::TOWN:
				app->audio->PlayMusic("Assets/audio/music/music_town.ogg");
				break;
			case StageIndex::DOJO:
				app->audio->PlayMusic("Assets/audio/music/music_dojo.ogg");
				break;
			case StageIndex::SHOP:
				app->audio->PlayMusic("Assets/audio/music/music_shop.ogg");
				break;
			case StageIndex::SHOPSUB:
				app->audio->PlayMusic("Assets/audio/music/music_shopsub.ogg");
				break;
			case StageIndex::TAVERN:
				app->audio->PlayMusic("Assets/audio/music/music_tavern.ogg");
				break;
			}

			app->scene->player->toggleGui = true;
		}

		break;
	}

	app->scene->player->battleSet = false;

	//app->entities->DestroyEntity(entitiesInBattle[app->scene->normalEnemyList.find((NormalEnemy*)entitiesInBattle[4])]);

	//Music

	

	return true;
}


void Battle::GampadControl()
{

	

	GamePad& pad = app->input->pads[0];
	if (!pad.a && !pad.b) _wait = true;
	switch (battlePhase)
	{
	case (BattlePhase::THINKING):


		/*if (!gamepad1)
		{*/
		if (attackButton->state == GuiControlState::NORMAL && defenseButton->state == GuiControlState::NORMAL &&
			itemButton->state == GuiControlState::NORMAL && escapeButton->state == GuiControlState::NORMAL)
		{
			if (app->input->GetKey(SDL_SCANCODE_UP) == KEY_DOWN || app->input->GetKey(SDL_SCANCODE_DOWN) ||
				app->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_DOWN || app->input->GetKey(SDL_SCANCODE_LEFT) == KEY_DOWN || pad.right || pad.left || pad.up || pad.down)
			{
				t = NULL;
				t = think.start;
				t->data->state = GuiControlState::FOCUSED;
				TK = 0;
				app->guiManager->keyb = true;

			}
		}
		/*}*/
		if (t != nullptr)
		{

			if (t->data->state == GuiControlState::FOCUSED) {

				if (app->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN || pad.a && _wait)
				{

					t->data->state = GuiControlState::PRESSED;
					t->data->state = GuiControlState::FOCUSED;
					t->data->state = GuiControlState::NORMAL;
					t->data->NotifyObserver();
					_wait = false;
				}

				//AAAAAAA
				if (!pad.left && !pad.right) wait = true;

				if (app->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_DOWN || pad.right && wait == true) {
					if (t != think.end /*&& TK != uplimSL*/)
					{
						t->data->state = GuiControlState::NORMAL;
						t = t->next;
						t->data->state = GuiControlState::FOCUSED;
						TK++;
					}
					else
					{
						t->data->state = GuiControlState::NORMAL;
						t = think.start;
						t->data->state = GuiControlState::FOCUSED;
						TK = dowlimSL;

					}
					wait = false;
				}
				if (app->input->GetKey(SDL_SCANCODE_LEFT) == KEY_DOWN || pad.left && wait == true) {
					if (t != think.start /*&& TK != dowlimSL*/)
					{
						t->data->state = GuiControlState::NORMAL;
						TK--;
						t = t->prev;
						t->data->state = GuiControlState::FOCUSED;

					}
					else
					{
						t->data->state = GuiControlState::NORMAL;
						t = think.end;
						t->data->state = GuiControlState::FOCUSED;
						TK = uplimSL;
					}
					wait = false;
				}
			}

		}
		break;
	case (BattlePhase::CHOOSE_ATTACK):
	{
		/*if (!gamepad1)
		{*/
		//LOG("%d", selCH.count());
		if (normalAttackButton->state == GuiControlState::NORMAL || playerSpecialButton1->state == GuiControlState::NORMAL ||
			playerSpecialButton2->state == GuiControlState::NORMAL || playerSpecialButton3->state == GuiControlState::NORMAL ||
			valionSpecialButton1->state == GuiControlState::NORMAL || valionSpecialButton2->state == GuiControlState::NORMAL ||
			valionSpecialButton3->state == GuiControlState::NORMAL || normalAttackButton->state == GuiControlState::NORMAL ||
			normalAttackButton->state == GuiControlState::NORMAL || raylaSpecialButton1->state == GuiControlState::NORMAL ||
			raylaSpecialButton2->state == GuiControlState::NORMAL || raylaSpecialButton3->state == GuiControlState::NORMAL ||
			dhionSpecialButton1->state == GuiControlState::NORMAL || dhionSpecialButton2->state == GuiControlState::NORMAL ||
			dhionSpecialButton3->state == GuiControlState::NORMAL)
		{
			if (app->input->GetKey(SDL_SCANCODE_UP) == KEY_DOWN || app->input->GetKey(SDL_SCANCODE_DOWN) ||
				app->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_DOWN || app->input->GetKey(SDL_SCANCODE_LEFT) == KEY_DOWN || pad.right || pad.left || pad.up || pad.down)
			{
				if (!gamepad2)
				{
					t = NULL;
					if (actualTurnEntity == entitiesInBattle[0]) uplimSL = selCH.count() - 1, t = selCH.start;
					if (actualTurnEntity == entitiesInBattle[1]) uplimSL = selVL.count() - 1, t = selVL.start;
					if (actualTurnEntity == entitiesInBattle[2]) uplimSL = selRAY.count() - 1, t = selRAY.start;
					if (actualTurnEntity == entitiesInBattle[3]) uplimSL = selDH.count() - 1, t = selDH.start;
					t->data->state = GuiControlState::FOCUSED;
					TK = 0;
					app->guiManager->keyb = true;
					gamepad2 = true;
				}
			}
		}
		/*}*/
		if (t != nullptr)
		{
			if (t->data->state == GuiControlState::FOCUSED) {

				if (app->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN || pad.a && _wait)
				{

					t->data->state = GuiControlState::PRESSED;
					t->data->state = GuiControlState::FOCUSED;
					t->data->state = GuiControlState::NORMAL;
					t->data->NotifyObserver();
					_wait = false;

				}

				//AAAAAAA
				if (!pad.left && !pad.right) wait = true;

				if (app->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_DOWN || pad.right && wait == true) {
					if (t != think.end /*&& t->next!=nullptr*/ && TK != uplimSL)
					{
						t->data->state = GuiControlState::NORMAL;
						t = t->next;
						t->data->state = GuiControlState::FOCUSED;
						TK++;
					}
					/*else
					{
						t->data->state = GuiControlState::NORMAL;
						t = think.start;
						t->data->state = GuiControlState::FOCUSED;
						TK = dowlimSL;

					}*/
					wait = false;
				}
				if (app->input->GetKey(SDL_SCANCODE_LEFT) == KEY_DOWN || pad.left && wait == true) {
					if (t != think.start && TK != dowlimSL /*&& t->prev != nullptr*/)
					{
						t->data->state = GuiControlState::NORMAL;
						TK--;
						t = t->prev;
						t->data->state = GuiControlState::FOCUSED;

					}
					/*else
					{
						t->data->state = GuiControlState::NORMAL;
						t = think.end;
						t->data->state = GuiControlState::FOCUSED;
						TK = uplimSL;
					}*/
					wait = false;
				}

			}
		}
	}
	break;

	case (BattlePhase::SELECTING):
	{
		LOG("%d", choos.count());
		/*if (!gamepad1)
		{*/
		if (enemyButton1->state == GuiControlState::NORMAL || enemyButton2->state == GuiControlState::NORMAL || enemyButton3->state == GuiControlState::NORMAL
			|| enemyButton4->state == GuiControlState::NORMAL)
		{
			if (app->input->GetKey(SDL_SCANCODE_UP) == KEY_DOWN || app->input->GetKey(SDL_SCANCODE_DOWN) ||
				app->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_DOWN || app->input->GetKey(SDL_SCANCODE_LEFT) == KEY_DOWN || pad.right || pad.left || pad.up || pad.down)
			{

				/*t = NULL;
				t = choos.start;
				CH = choos.;*/
				/*choos.At(TK)->data*/
				if (!gamepad3)
				{
					uplimSL = choos.count() - 1;
					t = NULL;
					t = choos.start;
					TK = 0;
					t->data->state = GuiControlState::FOCUSED;
					app->guiManager->keyb = true;
					gamepad3 = true;
				}
			}
		}
		/*LOG("%d", TK);
		LOG("%d", uplimSL);*/
		/*if (choos.At(TK) != nullptr)
		{*/

		//if (choos.At(TK)!=nullptr  )
		//{
		//	if (choos.At(TK)->data->state == GuiControlState::FOCUSED) {

		//		if (app->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN || pad.a && _wait)
		//		{

		//			choos.At(TK)->data->state = GuiControlState::PRESSED;
		//			choos.At(TK)->data->state = GuiControlState::FOCUSED;
		//			choos.At(TK)->data->state = GuiControlState::NORMAL;
		//			choos.At(TK)->data->NotifyObserver();
		//			_wait = false;
		//		}

		//		//AAAAAAA
		//		if (!pad.left && !pad.right) wait = true;

		//		if (app->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_DOWN || pad.right && wait == true) {

		//			
		//				if (/*t != think.end &&*/ TK != uplimSL)
		//				{
		//					choos.At(TK)->data->state = GuiControlState::NORMAL;
		//					//t = t->next;
		//					TK += 1;
		//					choos.At(TK)->data->state = GuiControlState::FOCUSED;

		//				}
		//				else
		//				{
		//					choos.At(TK)->data->state = GuiControlState::NORMAL;
		//					//t = t->next;
		//					TK = dowlimSL;
		//					choos.At(TK)->data->state = GuiControlState::FOCUSED;
		//				}
		//			
		//			wait = false;
		//		}
		//		if (app->input->GetKey(SDL_SCANCODE_LEFT) == KEY_DOWN || pad.left && wait == true) {
		//			if (/*t != think.start &&*/ TK != dowlimSL)
		//			{
		//				choos.At(TK)->data->state = GuiControlState::NORMAL;
		//				/*t = t->prev;*/
		//				TK--;
		//				choos.At(TK)->data->state = GuiControlState::FOCUSED;

		//			}
		//			else
		//			{
		//				choos.At(TK)->data->state = GuiControlState::NORMAL;
		//				/*t = t->prev;*/
		//				TK = uplimSL;
		//				choos.At(TK)->data->state = GuiControlState::FOCUSED;

		//			}
		//			wait = false;
		//		}

		//	}
		//}
		//}
		if (t != nullptr)
		{

			if (t->data->state == GuiControlState::FOCUSED) {

				if (app->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN || pad.a && _wait)
				{

					t->data->state = GuiControlState::PRESSED;
					t->data->state = GuiControlState::FOCUSED;
					t->data->state = GuiControlState::NORMAL;
					t->data->NotifyObserver();
					_wait = false;
				}

				//AAAAAAA
				if (!pad.left && !pad.right) wait = true;

				if (app->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_DOWN || pad.right && wait == true) {
					if (t != think.end && TK != uplimSL)
					{
						t->data->state = GuiControlState::NORMAL;
						t = t->next;
						t->data->state = GuiControlState::FOCUSED;
						TK++;
					}
					/*else
					{
						t->data->state = GuiControlState::NORMAL;
						t = think.start;
						t->data->state = GuiControlState::FOCUSED;
						TK = dowlimSL;

					}*/
					wait = false;
				}
				if (app->input->GetKey(SDL_SCANCODE_LEFT) == KEY_DOWN || pad.left && wait == true) {
					if (t != think.start && TK != dowlimSL)
					{
						t->data->state = GuiControlState::NORMAL;
						TK--;
						t = t->prev;
						t->data->state = GuiControlState::FOCUSED;

					}
					/*else
					{
						t->data->state = GuiControlState::NORMAL;
						t = think.end;
						t->data->state = GuiControlState::FOCUSED;
						TK = uplimSL;
					}*/
					wait = false;
				}
			}


		}

		break;
	}
	}
}