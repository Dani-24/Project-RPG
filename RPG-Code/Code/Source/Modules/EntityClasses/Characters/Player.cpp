#include "Player.h"

#include "App.h"
#include "Render.h"
#include "Audio.h"
#include "Camera.h"
#include "Textures.h"
#include "Input.h"
#include "Player.h"
#include "Log.h"
#include "Window.h"
#include "Scene.h"
#include "Map.h"
#include "Stages.h"
#include "Battle.h"
#include "FadeToBlack.h"
#include "Shop.h"
#include "QuestManager.h"

#include <time.h>

Player::Player( int x, int y) : Character(CharacterType::PLAYER)
{

	position = {x,y};

	//----------------------------------------------------------------------------------Overworld------------------------------------

	/*walkAnimDown.PushBack({ 9,10,31,46 });
	walkAnimDown.PushBack({ 62,8,31,46 });
	walkAnimDown.PushBack({ 114,10,31,46 });
	walkAnimDown.loop = true;
	walkAnimDown.speed = 0.006f;

	walkAnimUp.PushBack({ 9,218,31,46 });
	walkAnimUp.PushBack({ 62,221,31,46 });
	walkAnimUp.PushBack({ 114,218,31,47 });
	walkAnimUp.loop = true;
	walkAnimUp.speed = 0.006f;

	walkAnimL.PushBack({ 11,82,26,44 });
	walkAnimL.PushBack({ 64,80,26,45 });
	walkAnimL.PushBack({ 116,82,27,44 });
	walkAnimL.loop = true;
	walkAnimL.speed = 0.006f;

	walkAnimR.PushBack({ 11,153,27,44 });
	walkAnimR.PushBack({ 64,150,27,44 });
	walkAnimR.PushBack({ 116,153,27,44 });
	walkAnimR.loop = true;
	walkAnimR.speed = 0.006f;

	idleAnimR.PushBack({ 64,150,27,44 });
	idleAnimL.PushBack({ 64,80,26,45 });
	idleAnimUp.PushBack({ 62,221,31,46 });
	idleAnimDown.PushBack({ 62,8,31,46 });*/

	walkAnimDown.PushBack({ 0,0,48,64 });
	walkAnimDown.PushBack({ 48,0,48,64 });
	walkAnimDown.PushBack({ 96,0,48,64 });
	walkAnimDown.loop = true;
	walkAnimDown.speed = 0.006f;

	walkAnimUp.PushBack({ 0,192,48,64 });
	walkAnimUp.PushBack({ 48,192,48,64 });
	walkAnimUp.PushBack({ 96, 192,48,64 });
	walkAnimUp.loop = true;
	walkAnimUp.speed = 0.006f;

	walkAnimL.PushBack({ 0,64,48,64 });
	walkAnimL.PushBack({ 48,64,48,64 });
	walkAnimL.PushBack({ 96,64,48,64 });
	walkAnimL.loop = true;
	walkAnimL.speed = 0.006f;

	walkAnimR.PushBack({ 0,128,48,64 });
	walkAnimR.PushBack({ 48,128,48,64 });
	walkAnimR.PushBack({ 96,128,48,64 });
	walkAnimR.loop = true;
	walkAnimR.speed = 0.006f;

	idleAnimR.PushBack({ 48,128,48,64 });
	idleAnimL.PushBack({ 48,64,48,64 });
	idleAnimUp.PushBack({ 48,192,48,64 });
	idleAnimDown.PushBack({ 48,0,48,64 });

	//----------------------------------------------------------------------------------Battle Male------------------------------------

	attackM.PushBack({ 0 * BATTLE_SIZE , 0 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
	attackM.PushBack({ 1 * BATTLE_SIZE , 0 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
	attackM.PushBack({ 2 * BATTLE_SIZE , 0 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
	attackM.PushBack({ 3 * BATTLE_SIZE , 0 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
	attackM.PushBack({ 4 * BATTLE_SIZE , 0 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
	attackM.PushBack({ 5 * BATTLE_SIZE , 0 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });

	attackM.loop = false;
	attackM.speed = 0.008f;

	protectM.PushBack({ 0 * BATTLE_SIZE , 1 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
	protectM.PushBack({ 1 * BATTLE_SIZE , 1 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
	protectM.PushBack({ 2 * BATTLE_SIZE , 1 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
	protectM.PushBack({ 3 * BATTLE_SIZE , 1 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
	protectM.loop = true;
	protectM.speed = 0.006f;

	dieM.PushBack({ 0 * BATTLE_SIZE , 2 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
	dieM.PushBack({ 1 * BATTLE_SIZE , 2 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
	dieM.PushBack({ 2 * BATTLE_SIZE , 2 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
	dieM.PushBack({ 3 * BATTLE_SIZE , 2 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
	dieM.PushBack({ 4 * BATTLE_SIZE , 2 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
	dieM.PushBack({ 5 * BATTLE_SIZE , 2 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
	dieM.PushBack({ 6 * BATTLE_SIZE , 2 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
	dieM.PushBack({ 7 * BATTLE_SIZE , 2 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
	dieM.PushBack({ 8 * BATTLE_SIZE , 2 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
	dieM.loop = false;
	dieM.speed = 0.006f;

	idleBattleM.PushBack({ 0 * BATTLE_SIZE , 4 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
	idleBattleM.PushBack({ 1 * BATTLE_SIZE , 4 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
	idleBattleM.PushBack({ 2 * BATTLE_SIZE , 4 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
	idleBattleM.PushBack({ 3 * BATTLE_SIZE , 4 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
	idleBattleM.PushBack({ 4 * BATTLE_SIZE , 4 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
	idleBattleM.PushBack({ 5 * BATTLE_SIZE , 4 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
	idleBattleM.PushBack({ 6 * BATTLE_SIZE , 4 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
	idleBattleM.PushBack({ 7 * BATTLE_SIZE , 4 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
	idleBattleM.PushBack({ 8 * BATTLE_SIZE , 4 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
	idleBattleM.PushBack({ 9 * BATTLE_SIZE , 4 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
	idleBattleM.PushBack({ 10 * BATTLE_SIZE , 4 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
	idleBattleM.loop = true;
	idleBattleM.speed = 0.015f;

	hitM.PushBack({ 0 * BATTLE_SIZE , 7 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
	hitM.PushBack({ 1 * BATTLE_SIZE , 7 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
	hitM.PushBack({ 2 * BATTLE_SIZE , 7 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
	hitM.PushBack({ 3 * BATTLE_SIZE , 7 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
	hitM.loop = true;
	hitM.speed = 0.006f;

	//----------------------------------------------------------------------------------Battle Female------------------------------------

	attackF.PushBack({ 0 * BATTLE_SIZE , 0 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
	attackF.PushBack({ 1 * BATTLE_SIZE , 0 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
	attackF.PushBack({ 2 * BATTLE_SIZE , 0 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
	attackF.PushBack({ 3 * BATTLE_SIZE , 0 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
	attackF.PushBack({ 4 * BATTLE_SIZE , 0 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
	attackF.PushBack({ 5 * BATTLE_SIZE , 0 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
	attackF.PushBack({ 6 * BATTLE_SIZE , 0 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });

	attackF.PushBack({ 0 * BATTLE_SIZE , 4 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
	attackF.PushBack({ 1 * BATTLE_SIZE , 4 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
	attackF.PushBack({ 2 * BATTLE_SIZE , 4 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
	attackF.PushBack({ 3 * BATTLE_SIZE , 4 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
	attackF.PushBack({ 4 * BATTLE_SIZE , 4 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
	attackF.PushBack({ 5 * BATTLE_SIZE , 4 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
	attackF.PushBack({ 6 * BATTLE_SIZE , 4 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
	attackF.PushBack({ 7 * BATTLE_SIZE , 4 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
	attackF.PushBack({ 8 * BATTLE_SIZE , 4 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
	attackF.PushBack({ 9 * BATTLE_SIZE , 4 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
	attackF.PushBack({ 10 * BATTLE_SIZE , 4 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });

	attackF.loop = false;
	attackF.speed = 0.008f;

	attackF2.PushBack({ 0 * BATTLE_SIZE , 1 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
	attackF2.PushBack({ 1 * BATTLE_SIZE , 1 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
	attackF2.PushBack({ 2 * BATTLE_SIZE , 1 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
	attackF2.PushBack({ 3 * BATTLE_SIZE , 1 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
	attackF2.PushBack({ 4 * BATTLE_SIZE , 1 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
	attackF2.PushBack({ 5 * BATTLE_SIZE , 1 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
	attackF2.PushBack({ 6 * BATTLE_SIZE , 1 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });

	attackF2.PushBack({ 0 * BATTLE_SIZE , 4 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
	attackF2.PushBack({ 1 * BATTLE_SIZE , 4 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
	attackF2.PushBack({ 2 * BATTLE_SIZE , 4 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
	attackF2.PushBack({ 3 * BATTLE_SIZE , 4 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
	attackF2.PushBack({ 4 * BATTLE_SIZE , 4 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
	attackF2.PushBack({ 5 * BATTLE_SIZE , 4 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
	attackF2.PushBack({ 6 * BATTLE_SIZE , 4 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
	attackF2.PushBack({ 7 * BATTLE_SIZE , 4 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
	attackF2.PushBack({ 8 * BATTLE_SIZE , 4 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
	attackF2.PushBack({ 9 * BATTLE_SIZE , 4 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
	attackF2.PushBack({ 10 * BATTLE_SIZE , 4 * BATTLE_SIZE, BATTLE_SIZE , BATTLE_SIZE });

	attackF2.loop = false;
	attackF2.speed = 0.009f;

	attackChainF.PushBack({ 0 * BATTLE_SIZE , 0 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
	attackChainF.PushBack({ 1 * BATTLE_SIZE , 0 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
	attackChainF.PushBack({ 2 * BATTLE_SIZE , 0 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
	attackChainF.PushBack({ 3 * BATTLE_SIZE , 0 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
	attackChainF.PushBack({ 4 * BATTLE_SIZE , 0 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
	attackChainF.PushBack({ 5 * BATTLE_SIZE , 0 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
	attackChainF.PushBack({ 6 * BATTLE_SIZE , 0 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
	attackChainF.PushBack({ 0 * BATTLE_SIZE , 1 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
	attackChainF.PushBack({ 1 * BATTLE_SIZE , 1 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
	attackChainF.PushBack({ 2 * BATTLE_SIZE , 1 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
	attackChainF.PushBack({ 3 * BATTLE_SIZE , 1 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
	attackChainF.PushBack({ 4 * BATTLE_SIZE , 1 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
	attackChainF.PushBack({ 5 * BATTLE_SIZE , 1 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
	attackChainF.PushBack({ 6 * BATTLE_SIZE , 1 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });

	idleBattleF.PushBack({ 0 * BATTLE_SIZE , 4 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
	idleBattleF.PushBack({ 1 * BATTLE_SIZE , 4 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
	idleBattleF.PushBack({ 2 * BATTLE_SIZE , 4 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
	idleBattleF.PushBack({ 3 * BATTLE_SIZE , 4 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
	idleBattleF.PushBack({ 4 * BATTLE_SIZE , 4 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
	idleBattleF.PushBack({ 5 * BATTLE_SIZE , 4 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
	idleBattleF.PushBack({ 6 * BATTLE_SIZE , 4 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
	idleBattleF.PushBack({ 7 * BATTLE_SIZE , 4 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
	idleBattleF.PushBack({ 8 * BATTLE_SIZE , 4 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
	idleBattleF.PushBack({ 9 * BATTLE_SIZE , 4 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
	idleBattleF.PushBack({ 10 * BATTLE_SIZE , 4 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });

	attackChainF.loop = false;
	attackChainF.speed = 0.009f;


	dieF.PushBack({ 0 * BATTLE_SIZE , 2 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
	dieF.PushBack({ 1 * BATTLE_SIZE , 2 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
	dieF.PushBack({ 2 * BATTLE_SIZE , 2 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
	dieF.PushBack({ 3 * BATTLE_SIZE , 2 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
	dieF.PushBack({ 4 * BATTLE_SIZE , 2 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
	dieF.PushBack({ 5 * BATTLE_SIZE , 2 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
	dieF.PushBack({ 6 * BATTLE_SIZE , 2 * BATTLE_SIZE,  BATTLE_SIZE , BATTLE_SIZE });
	dieF.PushBack({ 7 * BATTLE_SIZE , 2 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
	dieF.PushBack({ 8 * BATTLE_SIZE , 2 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
	dieF.PushBack({ 9 * BATTLE_SIZE , 2 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
	dieF.PushBack({ 10 * BATTLE_SIZE , 2 * BATTLE_SIZE, BATTLE_SIZE , BATTLE_SIZE });

	dieF.loop = false;
	dieF.speed = 0.006f;

	protectF.PushBack({ 3 * BATTLE_SIZE, 2 * BATTLE_SIZE, BATTLE_SIZE , BATTLE_SIZE });
	protectF.loop = true;

	idleBattleF.PushBack({ 0 * BATTLE_SIZE , 4 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
	idleBattleF.PushBack({ 1 * BATTLE_SIZE , 4 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
	idleBattleF.PushBack({ 2 * BATTLE_SIZE , 4 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
	idleBattleF.PushBack({ 3 * BATTLE_SIZE , 4 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
	idleBattleF.PushBack({ 4 * BATTLE_SIZE , 4 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
	idleBattleF.PushBack({ 5 * BATTLE_SIZE , 4 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
	idleBattleF.PushBack({ 6 * BATTLE_SIZE , 4 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
	idleBattleF.PushBack({ 7 * BATTLE_SIZE , 4 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
	idleBattleF.PushBack({ 8 * BATTLE_SIZE , 4 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
	idleBattleF.PushBack({ 9 * BATTLE_SIZE , 4 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
	idleBattleF.PushBack({ 10 * BATTLE_SIZE , 4 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });

	idleBattleF.loop = true;
	idleBattleF.speed = 0.015f;

	hitF.PushBack({ 0 * BATTLE_SIZE , 7 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
	hitF.PushBack({ 1 * BATTLE_SIZE , 7 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
	hitF.PushBack({ 2 * BATTLE_SIZE , 7 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
	hitF.PushBack({ 3 * BATTLE_SIZE , 7 * BATTLE_SIZE , BATTLE_SIZE , BATTLE_SIZE });
	hitF.loop = true;
	hitF.speed = 0.006f;

	// Helicopter Animations

	Animation* susAnim = &heliWalkUpAnim;

	susAnim->PushBack({ 0, 64*3, 107, 64 });
	susAnim->PushBack({ 107, 64*3, 107, 64 });
	susAnim->PushBack({ 107*2, 64*3, 107, 64 });
	susAnim->loop = true;
	susAnim->speed = 0.006f;

	susAnim = &heliWalkDownAnim;

	susAnim->PushBack({ 0, 0, 107, 64 });
	susAnim->PushBack({ 107, 0, 107, 64 });
	susAnim->PushBack({ 107 *2, 0, 107, 64 });
	susAnim->loop = true;
	susAnim->speed = 0.006f;

	susAnim = &heliWalkLeftAnim;

	susAnim->PushBack({ 0, 64, 107, 64 });
	susAnim->PushBack({ 107, 64, 107, 64 });
	susAnim->PushBack({ 107 *2, 64, 107, 64 });
	susAnim->loop = true;
	susAnim->speed = 0.006f;

	susAnim = &heliWalkRightAnim;

	susAnim->PushBack({ 0, 64*2, 107, 64 });
	susAnim->PushBack({ 107, 64*2, 107, 64 });
	susAnim->PushBack({ 107 *2, 64*2, 107, 64 });
	susAnim->loop = true;
	susAnim->speed = 0.006f;

	susAnim = &heliIdleUp;

	susAnim->PushBack({ 0, 64*3, 107, 64 });
	susAnim->loop = true;
	susAnim->speed = 0.006f;

	susAnim = &heliIdleDown;

	susAnim->PushBack({ 0, 0, 107, 64 });
	susAnim->loop = true;
	susAnim->speed = 0.006f;

	susAnim = &heliIdleR;

	susAnim->PushBack({ 0, 64*2, 107, 64 });
	susAnim->loop = true;
	susAnim->speed = 0.006f;

	susAnim = &heliIdleL;

	susAnim->PushBack({ 0, 64, 107, 64 });
	susAnim->loop = true;
	susAnim->speed = 0.006f;

	susAnim = &heliBattleIdle;

	susAnim->PushBack({ 0 * BATTLE_SIZE, 0 * BATTLE_SIZE, BATTLE_SIZE, BATTLE_SIZE });
	susAnim->PushBack({ 1 * BATTLE_SIZE, 0 * BATTLE_SIZE, BATTLE_SIZE, BATTLE_SIZE });
	susAnim->PushBack({ 2 * BATTLE_SIZE, 0 * BATTLE_SIZE, BATTLE_SIZE, BATTLE_SIZE });
	susAnim->PushBack({ 3 * BATTLE_SIZE, 0 * BATTLE_SIZE, BATTLE_SIZE, BATTLE_SIZE });
	susAnim->PushBack({ 4 * BATTLE_SIZE, 0 * BATTLE_SIZE, BATTLE_SIZE, BATTLE_SIZE });
	susAnim->PushBack({ 5 * BATTLE_SIZE, 0 * BATTLE_SIZE, BATTLE_SIZE, BATTLE_SIZE });
	susAnim->PushBack({ 6 * BATTLE_SIZE, 0 * BATTLE_SIZE, BATTLE_SIZE, BATTLE_SIZE });
	susAnim->PushBack({ 7 * BATTLE_SIZE, 0 * BATTLE_SIZE, BATTLE_SIZE, BATTLE_SIZE });
	susAnim->PushBack({ 8 * BATTLE_SIZE, 0 * BATTLE_SIZE, BATTLE_SIZE, BATTLE_SIZE });
	susAnim->PushBack({ 9 * BATTLE_SIZE, 0 * BATTLE_SIZE, BATTLE_SIZE, BATTLE_SIZE });
	susAnim->loop = true;
	susAnim->speed = 0.006f;

	susAnim = &heliAttack;

	susAnim->PushBack({ 0 * BATTLE_SIZE, 1 * BATTLE_SIZE, BATTLE_SIZE, BATTLE_SIZE });
	susAnim->PushBack({ 1 * BATTLE_SIZE, 1 * BATTLE_SIZE, BATTLE_SIZE, BATTLE_SIZE });
	susAnim->PushBack({ 2 * BATTLE_SIZE, 1 * BATTLE_SIZE, BATTLE_SIZE, BATTLE_SIZE });
	susAnim->PushBack({ 3 * BATTLE_SIZE, 1 * BATTLE_SIZE, BATTLE_SIZE, BATTLE_SIZE });
	susAnim->PushBack({ 4 * BATTLE_SIZE, 1 * BATTLE_SIZE, BATTLE_SIZE, BATTLE_SIZE });
	susAnim->PushBack({ 5 * BATTLE_SIZE, 1 * BATTLE_SIZE, BATTLE_SIZE, BATTLE_SIZE });
	susAnim->PushBack({ 6 * BATTLE_SIZE, 1 * BATTLE_SIZE, BATTLE_SIZE, BATTLE_SIZE });
	susAnim->PushBack({ 7 * BATTLE_SIZE, 1 * BATTLE_SIZE, BATTLE_SIZE, BATTLE_SIZE });
	susAnim->loop = false;
	susAnim->speed = 0.006f;

	susAnim = &heliProtect;

	susAnim->PushBack({ 0 * BATTLE_SIZE, 2 * BATTLE_SIZE, BATTLE_SIZE, BATTLE_SIZE });
	susAnim->PushBack({ 1 * BATTLE_SIZE, 2 * BATTLE_SIZE, BATTLE_SIZE, BATTLE_SIZE });
	susAnim->PushBack({ 2 * BATTLE_SIZE, 2 * BATTLE_SIZE, BATTLE_SIZE, BATTLE_SIZE });
	susAnim->PushBack({ 3 * BATTLE_SIZE, 2 * BATTLE_SIZE, BATTLE_SIZE, BATTLE_SIZE });
	susAnim->PushBack({ 4 * BATTLE_SIZE, 2 * BATTLE_SIZE, BATTLE_SIZE, BATTLE_SIZE });
	susAnim->PushBack({ 5 * BATTLE_SIZE, 2 * BATTLE_SIZE, BATTLE_SIZE, BATTLE_SIZE });
	susAnim->PushBack({ 6 * BATTLE_SIZE, 2 * BATTLE_SIZE, BATTLE_SIZE, BATTLE_SIZE });
	susAnim->PushBack({ 7 * BATTLE_SIZE, 2 * BATTLE_SIZE, BATTLE_SIZE, BATTLE_SIZE });
	susAnim->PushBack({ 8 * BATTLE_SIZE, 2 * BATTLE_SIZE, BATTLE_SIZE, BATTLE_SIZE });
	susAnim->PushBack({ 9 * BATTLE_SIZE, 2 * BATTLE_SIZE, BATTLE_SIZE, BATTLE_SIZE });
	susAnim->loop = false;
	susAnim->speed = 0.006f;

	susAnim = &butMostImportantlyHeliHit;

	susAnim->PushBack({ 0 * BATTLE_SIZE, 3 * BATTLE_SIZE, BATTLE_SIZE, BATTLE_SIZE });
	susAnim->PushBack({ 1 * BATTLE_SIZE, 3 * BATTLE_SIZE, BATTLE_SIZE, BATTLE_SIZE });
	susAnim->PushBack({ 2 * BATTLE_SIZE, 3 * BATTLE_SIZE, BATTLE_SIZE, BATTLE_SIZE });
	susAnim->PushBack({ 3 * BATTLE_SIZE, 3 * BATTLE_SIZE, BATTLE_SIZE, BATTLE_SIZE });
	susAnim->PushBack({ 4 * BATTLE_SIZE, 3 * BATTLE_SIZE, BATTLE_SIZE, BATTLE_SIZE });
	susAnim->PushBack({ 5 * BATTLE_SIZE, 3 * BATTLE_SIZE, BATTLE_SIZE, BATTLE_SIZE });
	susAnim->PushBack({ 6 * BATTLE_SIZE, 3 * BATTLE_SIZE, BATTLE_SIZE, BATTLE_SIZE });
	susAnim->PushBack({ 7 * BATTLE_SIZE, 3 * BATTLE_SIZE, BATTLE_SIZE, BATTLE_SIZE });
	susAnim->PushBack({ 8 * BATTLE_SIZE, 3 * BATTLE_SIZE, BATTLE_SIZE, BATTLE_SIZE });
	susAnim->PushBack({ 9 * BATTLE_SIZE, 3 * BATTLE_SIZE, BATTLE_SIZE, BATTLE_SIZE });
	susAnim->loop = true;
	susAnim->speed = 0.006f;

	susAnim = &andThenHeliDies;

	susAnim->PushBack({ 0 * BATTLE_SIZE, 4 * BATTLE_SIZE, BATTLE_SIZE, BATTLE_SIZE });
	susAnim->PushBack({ 1 * BATTLE_SIZE, 4 * BATTLE_SIZE, BATTLE_SIZE, BATTLE_SIZE });
	susAnim->PushBack({ 2 * BATTLE_SIZE, 4 * BATTLE_SIZE, BATTLE_SIZE, BATTLE_SIZE });
	susAnim->PushBack({ 3 * BATTLE_SIZE, 4 * BATTLE_SIZE, BATTLE_SIZE, BATTLE_SIZE });
	susAnim->PushBack({ 4 * BATTLE_SIZE, 4 * BATTLE_SIZE, BATTLE_SIZE, BATTLE_SIZE });
	susAnim->PushBack({ 5 * BATTLE_SIZE, 4 * BATTLE_SIZE, BATTLE_SIZE, BATTLE_SIZE });
	susAnim->PushBack({ 6 * BATTLE_SIZE, 4 * BATTLE_SIZE, BATTLE_SIZE, BATTLE_SIZE });
	susAnim->PushBack({ 7 * BATTLE_SIZE, 4 * BATTLE_SIZE, BATTLE_SIZE, BATTLE_SIZE });
	susAnim->PushBack({ 8 * BATTLE_SIZE, 4 * BATTLE_SIZE, BATTLE_SIZE, BATTLE_SIZE });
	susAnim->PushBack({ 9 * BATTLE_SIZE, 4 * BATTLE_SIZE, BATTLE_SIZE, BATTLE_SIZE });
	susAnim->loop = false;
	susAnim->speed = 0.006f;

	susAnim = nullptr;
	delete susAnim;

	currentAnimation = &idleAnimR; //player start with idle anim

	name = "Rhen";
	configName = "player";

	margin = 10;
	colDownDistance = 47;
	colRightDistance = 9;

	baseCollider = app->collisions->AddCollider({ position.x + colRightDistance, position.y+ colDownDistance , 30,  24 }, Collider::Type::PLAYER, this);

	zoom = 3;

	mapPosition = { 0,0 };
	int xt = 80;
	int yt = 100 - 50;
	battlePosition = { xt, yt};

	isAlive = true;

	interactionButtonJustSpace.PushBack({ 83, 41, 36, 16 });
	interactionButtonJustSpace.loop = false;
}

// Destructor
Player::~Player()
{}

bool Player::Awake(pugi::xml_node& config)
{
	LOG("Init Image library, ta guapa la libreria de imagenes llamada player");
	bool ret = true;
	LOG("Num in config: %d",config.child("exampleNumber").attribute("num").as_int());

	MaleChar = config.child("male").attribute("path").as_string();
	FemaleChar = config.child("female").attribute("path").as_string();
	electionfxChar = config.child("election").attribute("path").as_string();
	WalkfxChar = config.child("walkFx").attribute("path").as_string();
	interactionButtonChar = config.child("interactionButton").attribute("path").as_string();

	return ret;
}

bool Player::Start()
{
	LOG("start Player");
	bool ret = true;

	erectionFx = app->audio->LoadFx(electionfxChar.GetString());
	walkFx = app->audio->LoadFx(WalkfxChar.GetString());

	PlayerMTex = app->tex->Load(MaleChar.GetString());
	PlayerFTex = app->tex->Load(FemaleChar.GetString());
	BattleMTex = app->tex->Load("Assets/sprites/MainCh/MainChM/Combat/m_battle_spritesheet.png");
	/*BattleFTex = app->tex->Load("Assets/sprites/main_ch/mainChF/battle/fBattlesprite.png");*/
	BattleFTex = app->tex->Load("Assets/sprites/MainCh/MainChF/Combat/f_battle_spritesheet.png");
	interactionButton = app->tex->Load(interactionButtonChar.GetString());

	male_character_face_gui = app->tex->Load("Assets/sprites/faces/mrotamasc_gui.png");
	female_character_face_gui = app->tex->Load("Assets/sprites/faces/ProtaFem_gui.png");

	// Helicopter

	HeliTex = app->tex->Load("Assets/sprites/MainCh/helicopter/heliSprite.png");
	BattleHeliTex = app->tex->Load("Assets/sprites/MainCh/helicopter/battle.png");
	helicopter_character_face_gui = app->tex->Load("Assets/sprites/MainCh/helicopter/gui_face_heli.png");

	//player start with idle anim
	currentAnimation = &idleAnimDown;
	PlayerErection = 1;

	canMove = true;

	/*stats = new Stats(1, 20, 8 , 5, 5, 20);*/
	stats = new Stats(1, 20, 8, 5, 10, 20);

	wait, _wait = false;

	timeWalkingVer = 0;
	timeWalkingHor = 0;

	entityTalking = nullptr;

	valionDefeated = false;
	raylaDefeated = false;
	dhionDefeated = false;

	autoTalk = false;

	return ret;
}

bool Player::PreUpdate()
{
	// DEBUG PLAYER POSITION
	if (app->scene->godmode) {
		if (app->input->GetKey(SDL_SCANCODE_P) == KEY_REPEAT) {
			LOG("position x %d y %d", position.x, position.y);
		}
	}

	// Show GUI if player isn't moving
	if (toggleGui == true && app->stages->actualStage != StageIndex::INTRODUCTION) {
		if (lastFramePos == position) {
			showGuiCont++;
			if (showGuiCont >= 30) {
				app->scene->guiactivate = true;
			}
		}
		else {
			showGuiCont = 0;
		}

		lastFramePos = position;
	}

	switch (PlayerErection)
	{
	case 1:
		spriteFace = male_character_face_gui;
		break;
	case 2:
		spriteFace = female_character_face_gui;
		break;
	case 3:
		spriteFace = helicopter_character_face_gui;
		break;
	}

	return true;
}

bool Player::Update(float dt) {
	bool ret = true;
	GamePad& pad = app->input->pads[0];
	
	if (!pad.r3 && !pad.l3)_wait = true;
	if (app->scene->pause == false && canMove == true && app->dialogs->dialoging == false) {

		if ((app->input->GetKey(SDL_SCANCODE_TAB) == KEY_DOWN) || pad.l3 && _wait && app->stages->actualStage==StageIndex::INTRODUCTION) {
			if (PlayerErection < 3) {
				PlayerErection++;
			}
			else {
				PlayerErection = 1;
			}

			switch (PlayerErection)
			{
			case 1:
				name = "Rhen";
				currentAnimation = &idleAnimDown;
				break;
			case 2:
				name = "Briar";
				currentAnimation = &idleAnimDown;
				break;
			case 3:
				name = "Heli";
				currentAnimation = &heliIdleDown;
				break;
			}

			app->audio->PlayFx(erectionFx);
			app->stages->elect = true;
			_wait = false;
		}

		if (app->fade->fading == false && app->stages->actualStage != StageIndex::INTRODUCTION) {
			MovementPlayer(dt);
		}
	}

	baseCollider->rect.x = position.x + colRightDistance;
	baseCollider->rect.y = position.y + colDownDistance;

	return ret;
}

bool Player::PostUpdate()
{
	bool ret = true;

	if (printInteractionButt == true) {
		app->render->DrawTexture(interactionButton, position.x + 5, position.y, &interactionButtonJustSpace.GetCurrentFrame());
	}
	printInteractionButt = false;

	return true;
}

bool Player::CleanUp() {

	//Collisions
	app->collisions->RemoveCollider(baseCollider);
	app->collisions->RemoveCollider(battleCollider);

	baseCollider = nullptr;
	delete baseCollider;

	//Animations
	currentAnimation = nullptr;
	delete currentAnimation;

	//Textures
	app->tex->UnLoad(spriteTex);
	app->tex->UnLoad(PlayerFTex);
	app->tex->UnLoad(PlayerMTex);

	return true;
}

void Player::MovementPlayer(float dt) {
	if(app->input->GetKey(SDL_SCANCODE_LCTRL) == KEY_REPEAT || app->input->GetKey(SDL_SCANCODE_RCTRL) == KEY_REPEAT || app->input->GetKey(SDL_SCANCODE_LSHIFT) == KEY_REPEAT || app->input->GetKey(SDL_SCANCODE_RSHIFT) == KEY_REPEAT)speed = 0.28 * dt;
	else if(app->scene->godmode)speed = 0.35 * dt;
	else speed = 0.2 * dt;
	
	GamePad& pad = app->input->pads[0];

	walkFxCooldown -= dt;
	int cooldown = 450;

	if (app->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT || app->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT || pad.left_y < -0.5f || pad.up) {
		
		if (app->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT || app->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT || pad.left_x < -0.5f || pad.left) {
			//MOV A
			if (timeWalkingHor < timeWalkingVer) {
				position.x -= speed;

				if (PlayerErection != 3) {
					if (currentAnimation != &walkAnimL) {
						currentAnimation = &walkAnimL;

					}
				}
				else {
					currentAnimation = &heliWalkLeftAnim;
				}

				if (walkFxCooldown < 0) {
					app->audio->PlayFx(walkFx);
					walkFxCooldown = cooldown;
				}
			}
			//MOV W
			else {
					position.y -= speed;
					if (PlayerErection != 3) {
						if (currentAnimation != &walkAnimUp) {
							currentAnimation = &walkAnimUp;
						}
					}
					else {
						currentAnimation = &heliWalkUpAnim;
					}

					if (walkFxCooldown < 0) {
						app->audio->PlayFx(walkFx);
						walkFxCooldown = cooldown;
					}
				
			}
		}
		
		else if (app->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT || app->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT || pad.left_x > 0.5f || pad.right) {
			//MOV D
			if (timeWalkingHor < timeWalkingVer) {
				position.x += speed;
				if (PlayerErection != 3) {
					if (currentAnimation != &walkAnimR) {
						currentAnimation = &walkAnimR;
					}
				}
				else {
					currentAnimation = &heliWalkRightAnim;
				}

				if (walkFxCooldown < 0) {
					app->audio->PlayFx(walkFx);
					walkFxCooldown = cooldown;
				}
			}
			//MOV W
			else {
					position.y -= speed;
					if (PlayerErection != 3) {
						if (currentAnimation != &walkAnimUp) {
							currentAnimation = &walkAnimUp;
						}
					}
					else {
						currentAnimation = &heliWalkUpAnim;
					}

					if (walkFxCooldown < 0) {
						app->audio->PlayFx(walkFx);
						walkFxCooldown = cooldown;
					}
				
			}
		}
		//MOV W
		else {
			position.y -= speed;
			timeWalkingVer++;
			timeWalkingHor = 0;

			if (PlayerErection != 3) {
				if (currentAnimation != &walkAnimUp) {
					currentAnimation = &walkAnimUp;
				}
			}
			else {
				currentAnimation = &heliWalkUpAnim;
			}

			if (walkFxCooldown < 0) {
				app->audio->PlayFx(walkFx);
				walkFxCooldown = cooldown;
			}
		}
	}
	else if (app->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT || app->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT || pad.left_y > 0.5f || pad.down) {

		if (app->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT || app->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT || pad.left_x < -0.5f || pad.left) {
			//MOV A
			if (timeWalkingHor < timeWalkingVer) {
				position.x -= speed;
				timeWalkingHor++;
				timeWalkingVer++;
				if (PlayerErection != 3) {
					if (currentAnimation != &walkAnimL) {
						currentAnimation = &walkAnimL;
					}
				}
				else {
					currentAnimation = &heliWalkLeftAnim;
				}

				if (walkFxCooldown < 0) {
					app->audio->PlayFx(walkFx);
					walkFxCooldown = cooldown;
				}
			}
			//MOV S
			else {
				position.y += speed;
				if (PlayerErection != 3) {
					if (currentAnimation != &walkAnimDown) {
						currentAnimation = &walkAnimDown;
					}
				}
				else {
					currentAnimation = &heliIdleDown;
				}

				if (walkFxCooldown < 0) {
					app->audio->PlayFx(walkFx);
					walkFxCooldown = cooldown;
				}
			}
		}
		else if (app->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT || app->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT || pad.left_x > 0.5f || pad.right) {
			//MOV D
			if (timeWalkingHor < timeWalkingVer) {
				position.x += speed;
				timeWalkingHor++;
				timeWalkingVer++;

				if (PlayerErection != 3) {
					if (currentAnimation != &walkAnimR) {
						currentAnimation = &walkAnimR;
					}
				}
				else {
					currentAnimation = &heliWalkRightAnim;
				}

				if (walkFxCooldown < 0) {
					app->audio->PlayFx(walkFx);
					walkFxCooldown = cooldown;
				}
			}
			//MOV S
			else {
				position.y += speed;
				if (PlayerErection != 3) {
					if (currentAnimation != &walkAnimDown) {
						currentAnimation = &walkAnimDown;
					}
				}
				else {
					currentAnimation = &heliWalkDownAnim;
				}

				if (walkFxCooldown < 0) {
					app->audio->PlayFx(walkFx);
					walkFxCooldown = cooldown;
				}
			}
		}
		//MOV S
		else {
			position.y += speed;
			timeWalkingVer++;
			timeWalkingHor = 0;

			if (PlayerErection != 3) {
				if (currentAnimation != &walkAnimDown) {
					currentAnimation = &walkAnimDown;
				}
			}
			else {
				currentAnimation = &heliWalkDownAnim;
			}

			if (walkFxCooldown < 0) {
				app->audio->PlayFx(walkFx);
				walkFxCooldown = cooldown;
			}
		}
	}
	else if (app->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT || app->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT || pad.left_x < -0.5f || pad.left) {
		position.x -= speed;
		timeWalkingVer = 0;
		timeWalkingHor++;

		if (PlayerErection != 3) {
			if (currentAnimation != &walkAnimL) {
				currentAnimation = &walkAnimL;
			}
		}
		else {
			currentAnimation = &heliWalkLeftAnim;
		}

		if (walkFxCooldown < 0) {
			app->audio->PlayFx(walkFx);
			walkFxCooldown = cooldown;
		}
	}
	else if (app->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT || app->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT || pad.left_x > 0.5f || pad.right) {
		position.x += speed;
		timeWalkingVer = 0;
		timeWalkingHor++;

		if (PlayerErection != 3) {
			if (currentAnimation != &walkAnimR) {
				currentAnimation = &walkAnimR;
			}
		}
		else {
			currentAnimation = &heliWalkRightAnim;
		}

		if (walkFxCooldown < 0) {
			app->audio->PlayFx(walkFx);
			walkFxCooldown = cooldown;
		}
	}
	else {
		if (currentAnimation == &walkAnimR) {
			currentAnimation = &idleAnimR;
		}
		else if(currentAnimation == &walkAnimL) {
			currentAnimation = &idleAnimL;
		}
		else if (currentAnimation == &walkAnimUp) {
			currentAnimation = &idleAnimUp;
		}
		else if (currentAnimation == &walkAnimDown) {
			currentAnimation = &idleAnimDown;
		}
		else if (currentAnimation == &heliWalkDownAnim) {
			currentAnimation = &heliIdleDown;
		}
		else if (currentAnimation == &heliWalkUpAnim) {
			currentAnimation = &heliIdleUp;
		}
		else if (currentAnimation == &heliWalkRightAnim) {
			currentAnimation = &heliIdleR;
		}
		else if (currentAnimation == &heliWalkLeftAnim) {
			currentAnimation = &heliIdleL;
		}

		timeWalkingHor = 0;
		timeWalkingVer = 0;
	}

	currentAnimation->Update(dt);
}

void Player::OnCollision(Collider* col1, Collider* col2) {

	if (col1 == baseCollider && col2->type == Collider::WALL && !app->scene->godmode) {

		//Cant move Left
		if (col2->rect.x + col2->rect.w > col1->rect.x					&&
			col2->rect.x + col2->rect.w < col1->rect.x + col1->rect.w	&&
			col1->rect.y < col2->rect.y + col2->rect.h - margin			&&
			col1->rect.y + col1->rect.h > col2->rect.y + margin) {
		
			this->position.x = col2->rect.x + col2->rect.w - colRightDistance;
		}

		//Cant move Right
		if (col2->rect.x > col1->rect.x									&&
			col2->rect.x < col1->rect.x + col1->rect.w					&&
			col1->rect.y < col2->rect.y + col2->rect.h - margin			&&
			col1->rect.y + col1->rect.h > col2->rect.y + margin) {
			
			this->position.x = col2->rect.x - col1->rect.w - colRightDistance;
		}

		//Cant move Up
		if (col2->rect.y + col2->rect.h > col1->rect.y					&&
			col2->rect.y + col2->rect.h < col1->rect.y + col1->rect.h	&&
			col1->rect.x + col1->rect.w > col2->rect.x + margin			&&
			col1->rect.x < col2->rect.x + col2->rect.w - margin) {
			
			this->position.y = col2->rect.y + col2->rect.h - colDownDistance;
		}
		//Cant move Down
		if (col2->rect.y < col1->rect.y + col1->rect.h					&&
			col2->rect.y > col1->rect.y									&&
			col1->rect.x + col1->rect.w > col2->rect.x + margin			&&
			col1->rect.x < col2->rect.x + col2->rect.w - margin) {
			
			this->position.y = col2->rect.y - col1->rect.h - colDownDistance;
		}
	}

	if (col1 == baseCollider && col2->type == Collider::INSTANT) {

		//Collision with enemy

		ListItem<NormalEnemy*>* normalEnemyInList;

		for (normalEnemyInList = app->scene->normalEnemyList.start; normalEnemyInList != NULL; normalEnemyInList = normalEnemyInList->next)
		{
			if (normalEnemyInList->data->activeOnStage == app->stages->actualStage) {
				if (normalEnemyInList->data->GetCollider() != nullptr) {
					if (normalEnemyInList->data->GetCollider() == col2 && app->battle->isEnabled() == false) {

						app->battle->entitiesInBattle[0] = this;
						app->battle->entitiesInBattle[4] = normalEnemyInList->data;

						int alliesCount = 1;
						int enemiesCount = 1;

						for (int i = 1; i < app->stages->partyListPtr->count(); i++) {
							if (app->stages->partyListPtr->At(i) != nullptr) {
								app->battle->entitiesInBattle[alliesCount] = app->stages->partyListPtr->At(i)->data;
								alliesCount++;
								srand(time(NULL));
								int enemySpawnChance = (rand() % 100);

								if (enemySpawnChance >= 25) {
									srand(time(NULL));
									int enemyType = (rand() % 3);
									if (enemyType == 0) {
										NormalEnemy* bat = (NormalEnemy*)app->entities->CreateEntity(NormalEnemyType::BAT, 0, 0);
										bat->onlyInBattle = true;
										app->scene->normalEnemyList.add(bat);
										app->battle->entitiesInBattle[4 + enemiesCount] = bat;
									}
									else if (enemyType == 1) {

										NormalEnemy* flyingEye = (NormalEnemy*)app->entities->CreateEntity(NormalEnemyType::FLYING_EYE, 0, 0);
										flyingEye->onlyInBattle = true;
										app->scene->normalEnemyList.add(flyingEye);
										app->battle->entitiesInBattle[4 + enemiesCount] = flyingEye;
									}
									else if (enemyType == 2) {
										NormalEnemy* skeleton = (NormalEnemy*)app->entities->CreateEntity(NormalEnemyType::SKELETON, 0, 0);
										skeleton->onlyInBattle = true;
										app->scene->normalEnemyList.add(skeleton);
										app->battle->entitiesInBattle[4 + enemiesCount] = skeleton;

									}

									enemiesCount++;




								}
							}
						}
						//app->battle->normalEnemyInBattle = normalEnemyInList->data;
						//app->battle->CurrentEnemyType = EnemyInBattleType::NORMAL;
						app->battle->Enable();
					}
				}
			}
		}

		//Collision with entrance
		for (int i = 0; i < MAX_ENTRIES; i++) {
			if (app->map->mapEntries[i] != nullptr) {
				if (app->map->mapEntries[i]->col == col2) {

					switch (app->map->mapEntries[i]->id) 
					{
						case 0:

							switch (app->stages->actualStage)
							{
							case StageIndex::NONE:

								break;
							case StageIndex::TOWN:

								LOG("Loading Shop map");
								townPos = { position.x, position.y + townPosYAxisfix };
								app->fade->DoFadeToBlack(StageIndex::SHOP);

								break;
							case StageIndex::DOJO:

								LOG("Loading town map");
								app->fade->DoFadeToBlack(StageIndex::TOWN);

								break;
							case StageIndex::SHOP:

								LOG("Loading Shop sub level map");
								app->fade->DoFadeToBlack(StageIndex::SHOPSUB);

								break;
							case StageIndex::SHOPSUB:

								LOG("Loading Shop map");
								shopPosOn = true;
								app->fade->DoFadeToBlack(StageIndex::SHOP);

								break;
							case StageIndex::TAVERN:

								LOG("Loading town map");
								app->fade->DoFadeToBlack(StageIndex::TOWN);

								break;
							case StageIndex::TOWER_0:

								LOG("Loading floor 1 map");
								tower0Pos = { position.x, position.y + tower0PosYAxisfix };
								app->fade->DoFadeToBlack(StageIndex::TOWER_1);

								break;
							case StageIndex::TOWER_1:

								LOG("Loading tower map");
								tower1Pos = { position.x, position.y - tower1PosYAxisfix };
								app->fade->DoFadeToBlack(StageIndex::TOWER_0);

								break;
							case StageIndex::TOWER_2:
								if (Floor2Key == true) {
									LOG("Loading floor 4 map");
									tower2Pos = { position.x, position.y + tower2PosYAxisfix };
									app->fade->DoFadeToBlack(StageIndex::TOWER_3);
								}
								break;
							case StageIndex::TOWER_4:

								LOG("Loading floor 2 map");
								tower3Pos = { position.x, position.y - tower3PosYAxisfix };
								app->fade->DoFadeToBlack(StageIndex::TOWER_3);

								break;
							case StageIndex::TOWER_3:
								if (Key1 == true && Key2 == true && Key3 == true) {
									LOG("Loading floor 3 map");
									tower4Pos = { position.x, position.y + tower4PosYAxisfix };
									app->fade->DoFadeToBlack(StageIndex::TOWER_4);
								}
								break;
							}

							break;
						case 1:

							switch (app->stages->actualStage)
							{
							case StageIndex::NONE:

								break;
							case StageIndex::TOWN:
								if (TowerKey == true){
									LOG("Loading Tower map");
									townPos = { position.x, position.y + townPosYAxisfix };
									app->fade->DoFadeToBlack(StageIndex::TOWER_0);
								}

								break;
							case StageIndex::DOJO:

								LOG("Returning to town");
								app->fade->DoFadeToBlack(StageIndex::TOWN);

								break;
							case StageIndex::SHOP:

								LOG("Loading town map");
								app->fade->DoFadeToBlack(StageIndex::TOWN);

								break;
							case StageIndex::TAVERN:

								LOG("Loading town map");
								app->fade->DoFadeToBlack(StageIndex::TOWN);

								break;
							case StageIndex::TOWER_0:

								LOG("Loading town map");
								tower0Pos = { position.x, position.y - tower0PosYAxisfix };
								app->fade->DoFadeToBlack(StageIndex::TOWN);

								break;
							case StageIndex::TOWER_1:

								LOG("Loading tower map");
								tower1Pos = { position.x, position.y - tower1PosYAxisfix };
								app->fade->DoFadeToBlack(StageIndex::TOWER_0);

								break;
							case StageIndex::TOWER_2:

								LOG("Loading floor 1 map");
								tower2Pos = { position.x, position.y - tower2PosYAxisfix };
								app->fade->DoFadeToBlack(StageIndex::TOWER_1);

								break;
							case StageIndex::TOWER_4:

								LOG("Loading floor 2 map");
								tower3Pos = { position.x, position.y - tower3PosYAxisfix };
								app->fade->DoFadeToBlack(StageIndex::TOWER_3);

								break;
							case StageIndex::TOWER_3:

								if (Key1 == true && Key2 == true && Key3 == true) {
									LOG("Loading floor 3 map");
									tower4Pos = { position.x, position.y + tower4PosYAxisfix };
									app->fade->DoFadeToBlack(StageIndex::TOWER_4);
								}

								break;
							}
							break;
						case 2:

							switch (app->stages->actualStage)
							{
							case StageIndex::NONE:

								break;
							case StageIndex::TOWN:
								if (TowerKey == true) {
									LOG("Loading Tower map");
									townPos = { position.x, position.y + townPosYAxisfix };
									app->fade->DoFadeToBlack(StageIndex::TOWER_0);
								}
								break;
							case StageIndex::DOJO:

								LOG("Returning to town");
								app->fade->DoFadeToBlack(StageIndex::TOWN);

								break;
							case StageIndex::SHOP:

								LOG("Loading town map");
								app->fade->DoFadeToBlack(StageIndex::TOWN);

								break;
							case StageIndex::TOWER_0:

								LOG("Loading floor 1 map");
								tower0Pos = { position.x, position.y + tower0PosYAxisfix };
								app->fade->DoFadeToBlack(StageIndex::TOWER_1);

								break;
							case StageIndex::TOWER_1:

								LOG("Loading tower map");
								tower1Pos = { position.x, position.y - tower1PosYAxisfix };
								app->fade->DoFadeToBlack(StageIndex::TOWER_0);

								break;
							case StageIndex::TOWER_3:

								if (Key1 == true && Key2 == true && Key3 == true) {
									LOG("Loading floor 3 map");
									tower4Pos = { position.x, position.y + tower4PosYAxisfix };
									app->fade->DoFadeToBlack(StageIndex::TOWER_4);
								}

								break;
							}

							break;
						case 3:
							switch (app->stages->actualStage)
							{
							case StageIndex::NONE:

								break;
							case StageIndex::TOWN:

								LOG("Loading Tavern map");
								townPos = { position.x, position.y + townPosYAxisfix };
								app->fade->DoFadeToBlack(StageIndex::TAVERN);

								break;
							case StageIndex::DOJO:

								LOG("Returning to town");
								app->fade->DoFadeToBlack(StageIndex::TOWN);

								break;
							case StageIndex::SHOP:

								LOG("Loading town map");
								app->fade->DoFadeToBlack(StageIndex::TOWN);

								break;
							case StageIndex::TOWER_0:

								LOG("Loading town map");
								tower0Pos = { position.x, position.y - tower0PosYAxisfix };
								app->fade->DoFadeToBlack(StageIndex::TOWN);

								break;
							case StageIndex::TOWER_1:
								if (Floor1Key == true) {
									LOG("Loading floor 2 map");
									tower1Pos = { position.x, position.y + tower1PosYAxisfix };
									app->fade->DoFadeToBlack(StageIndex::TOWER_2);
								}
								break;
							case StageIndex::TOWER_2:

								LOG("Loading floor 1 map");
								tower2Pos = { position.x, position.y - tower2PosYAxisfix };
								app->fade->DoFadeToBlack(StageIndex::TOWER_1);

								break;
							case StageIndex::TOWER_3:

								if (Key1 == true && Key2 == true && Key3 == true) {
									LOG("Loading floor 3 map");
									tower4Pos = { position.x, position.y + tower4PosYAxisfix };
									app->fade->DoFadeToBlack(StageIndex::TOWER_4);
								}

								break;
							}
							
							break;
						case 4:
							switch (app->stages->actualStage)
							{
							case StageIndex::TOWN:

								LOG("Loading Tavern map");
								townPos = { position.x, position.y + townPosYAxisfix };
								app->fade->DoFadeToBlack(StageIndex::TAVERN);

								break;
							case StageIndex::TOWER_1:

								if (Floor1Key == true) {
									LOG("Loading floor 2 map");
									tower1Pos = { position.x, position.y + tower1PosYAxisfix };
									app->fade->DoFadeToBlack(StageIndex::TOWER_2);
								}
								break;
							case StageIndex::TOWER_3:

								LOG("Loading floor 2 map");
								tower4Pos = { position.x, position.y - tower4PosYAxisfix };
								app->fade->DoFadeToBlack(StageIndex::TOWER_2);
								break;
							}

							break;
						default:
							if (app->stages->actualStage == StageIndex::DOJO) {
								LOG("Returning to town");
								app->fade->DoFadeToBlack(StageIndex::TOWN);
							}
							if (app->stages->actualStage == StageIndex::TOWN) {
								LOG("going to dojo");
								townPos = { position.x, position.y + townPosYAxisfix };
								app->fade->DoFadeToBlack(StageIndex::DOJO);
							}
							if (app->stages->actualStage == StageIndex::TOWER_3)
							{

								LOG("Loading floor 2 map");
								tower4Pos = { position.x, position.y - tower4PosYAxisfix };
								app->fade->DoFadeToBlack(StageIndex::TOWER_2);
							}
							break;
					}
				}
			}
		}
	}

	if (col1 == baseCollider && col2->type == Collider::INTERACT) {

		// NPC COLLISIONS (Press Space)

		if (app->dialogs->dialoging == false) {
	
			for (ListItem<Entity*>* entityInList = app->entities->entityList.start; entityInList != NULL; entityInList = entityInList->next)
			{
				if (entityInList->data->activeOnStage == app->stages->actualStage) {
					
					if (entityInList->data->GetCollider() != nullptr) {
						if (entityInList->data->GetCollider() == col2) {
							GamePad& pad = app->input->pads[0];

							if (!pad.a) wait = true;

							if (autoTalk == true) {
								entityTalking = entityInList->data;
								app->questManager->CheckQuest(entityInList->data->npcID);
								autoTalk = false;
							}else if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN || app->input->GetKey(SDL_SCANCODE_RETURN) == KEY_REPEAT || pad.a && wait == true) {

								entityTalking = entityInList->data;
								app->questManager->CheckQuest(entityInList->data->npcID);
								/*switch (entityInList->data->npcID)
								{
								case 1:
									Interact(NPCType::COCK, cockDialog);
									break;
								case 2:
									Interact(NPCType::MERCHANT, merchantDialog);
									break;
								case 3:
									Interact(NPCType::BARKEEPER, barkeeperDialog);
									break;
								case 4:
									Interact(NPCType::TRAINER, trainerDialog);
									break;
								case 5:
									Interact(NPCType::EMILIO, emilioDialog);
									break;
								case 7:
									Interact(NPCType::FUENTE, fuenteDialog);
									break;
								case 8:
									Interact(NPCType::CARTELSUDTOWN, cartelSudTownDialog);
								default:
									break;
								}*/
								wait = false;
							}
							printInteractionButt = true;
							
						}
					}
				}
			}
		}
	}
}

void Player::Interact(NPCType npc, const char* dialog[DIALOG_LENGHT]) {

	app->dialogs->CreateDialog(npc, dialog);
	if (npc == NPCType::FUENTE) {
		for (ListItem<Character*>* characterList = app->scene->partyList.start; characterList != NULL; characterList = characterList->next) {
			characterList->data->stats->health = characterList->data->stats->maxHealth;
			characterList->data->isAlive = true;
			dieM.Reset();
			dieF.Reset();
			characterList->data->deathAnim.Reset();
		}
			
	}
	if (npc == NPCType::MERCHANT) {
		app->shop->Enable();
	}
}