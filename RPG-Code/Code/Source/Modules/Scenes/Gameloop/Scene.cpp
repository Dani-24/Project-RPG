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
#include "PauseMenu.h"
#include "StatsMenu.h"

#include "Battle.h"
#include "Stages.h"
#include "ModuleQFonts.h"
#include "Camera.h"
#include "ModuleParticles.h"

#include "NormalEnemy.h"
#include "BossEnemy.h"
#include "NPC.h"
#include "EntityManager.h"

#include "Party.h"
#include "Inventory.h"

#include "StaticEntity.h"
#include "Item.h"

#include "Defs.h"
#include "Log.h"

#include <time.h>

Scene::Scene(App* application, bool start_enabled) : Module(application, start_enabled)
{
	name.Create("scene");
}

Scene::~Scene()
{}

bool Scene::Awake(pugi::xml_node& config)
{
	LOG("Loading Scene");
	bool ret = true;

	CharRest = config.child("rest").attribute("path").as_string();
	_CharRest = config.child("prest").attribute("path").as_string();
	CharBackTex = config.child("back").attribute("path").as_string();
	_CharBackTex = config.child("pback").attribute("path").as_string();
	CharLoc = config.child("loc").attribute("path").as_string();
	CharFxBack = config.child("bFx").attribute("path").as_string();
	CharFxLoad = config.child("lFx").attribute("path").as_string();
	CharFxSave = config.child("sFx").attribute("path").as_string();

	return ret;
}

bool Scene::Start()
{
	LOG("Starting Scene");
	
	// Apple just for inventory testing
	AddItem(UsableType::APPLE);

	// Enables & idk
	app->map->Enable();
	app->dialogs->Enable();
	
	// Load textures
	backFx = app->audio->LoadFx(CharFxBack.GetString());
	loadFx = app->audio->LoadFx(CharFxLoad.GetString());
	saveFx = app->audio->LoadFx(CharFxSave.GetString());
	
	mini_map = app->tex->Load("Assets/textures/mini_map.png");

	//buttons
	restart = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 40, "Restart", { 280, 280 , 74, 32 }, this);
	backtoMenu = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 41, "BackToMenu", { 240, 280 , 150, 32 }, this);
	restartTex = app->tex->Load(CharRest.GetString());
	press_restartTex = app->tex->Load(_CharRest.GetString());
	backtoMenuTex = app->tex->Load(CharBackTex.GetString());
	press_backtoMenuTex = app->tex->Load(_CharBackTex.GetString());
	locationUI = app->tex->Load(CharLoc.GetString());

	// Player Entity
	player = (Player*)app->entities->CreateEntity(CharacterType::PLAYER, 950, 1730);

	/*Party* valion = (Party*)app->entities->CreateEntity(PartyType::VALION, 20, 50);
	partyList.add(valion);*/

	app->stages->playerPtr = player;
	app->camera->SetTarget(player);
	partyList.add(player);

	app->stages->partyListPtr = &partyList;

	// NPCs
	iPoint cockPos = { 900, 1400 };
	iPoint barkeeperPos = { 450, 300 };
	iPoint trainerPos = { 290, 160 };
	iPoint merchantPos = { 255, 150 };
	iPoint emilioPos = { 850, 200 };
	iPoint fuentePos = { 380, 1390 };
	iPoint cartelSudTownPos = { 1000, 1764 };

	iPoint bigtreePos = { 1000, 1764 };

	iPoint deadTreePos = { 2690 , 2030 };
	iPoint treePos = { 573 , 332 };
	iPoint ripPos = { 720 , 2700 };
	iPoint rip2Pos = { 2969 , 1970 };
	iPoint rip3Pos = { 2549 , 866 };

	iPoint valionPos = { 400, 400 };
	iPoint raylaPos = { 400, 400 };
	iPoint dhionPos = { 400, 400 };


	NPC* cock = (NPC*)app->entities->CreateEntity(NPCType::COCK, cockPos.x, cockPos.y);
	npcList.add(cock);
	cock->activeOnStage = StageIndex::TOWN;

	NPC* barkeeper = (NPC*)app->entities->CreateEntity(NPCType::BARKEEPER, barkeeperPos.x, barkeeperPos.y);
	npcList.add(barkeeper);
	barkeeper->activeOnStage = StageIndex::TAVERN;

	NPC* trainer = (NPC*)app->entities->CreateEntity(NPCType::TRAINER, trainerPos.x, trainerPos.y);
	npcList.add(trainer);
	trainer->activeOnStage = StageIndex::DOJO;

	NPC* merchant = (NPC*)app->entities->CreateEntity(NPCType::MERCHANT, merchantPos.x, merchantPos.y);
	npcList.add(merchant);
	merchant->activeOnStage = StageIndex::SHOP;

	NPC* emilio = (NPC*)app->entities->CreateEntity(NPCType::EMILIO, emilioPos.x, emilioPos.y);
	npcList.add(emilio);
	emilio->activeOnStage = StageIndex::TOWN;

	NPC* fuente = (NPC*)app->entities->CreateEntity(NPCType::FUENTE, fuentePos.x, fuentePos.y);
	npcList.add(fuente);
	fuente->activeOnStage = StageIndex::TOWN;

	NPC* cartelSudTown = (NPC*)app->entities->CreateEntity(NPCType::CARTELSUDTOWN, cartelSudTownPos.x, cartelSudTownPos.y);
	npcList.add(cartelSudTown);
	cartelSudTown->activeOnStage = StageIndex::TOWN;

	NPC* valion = (NPC*)app->entities->CreateEntity(NPCType::VALION, valionPos.x, valionPos.y);
	npcList.add(valion);
	valion->activeOnStage = StageIndex::TOWER_BOSS_1;

	NPC* rayla = (NPC*)app->entities->CreateEntity(NPCType::RAYLA, raylaPos.x, raylaPos.y);
	npcList.add(rayla);
	rayla->activeOnStage = StageIndex::TOWER_BOSS_2;

	NPC* dhion = (NPC*)app->entities->CreateEntity(NPCType::DHION, dhionPos.x, dhionPos.y);
	npcList.add(dhion);
	dhion->activeOnStage = StageIndex::TOWER_BOSS_3;

	NPC* camionKun = (NPC*)app->entities->CreateEntity(NPCType::TRUCK, 90 * TILE_SIZE, 16 * TILE_SIZE);
	npcList.add(camionKun);
	camionKun->activeOnStage = StageIndex::PROLOGUE;

	/*NPC* cartelSudTown = (NPC*)app->entities->CreateEntity(NPCType::BIGTREE, bigtreePos.x, bigtreePos.y);
	npcList.add(cartelSudTown);
	cartelSudTown->activeOnStage = StageIndex::TOWER_4;*/


	NPC* deadTree = (NPC*)app->entities->CreateEntity(NPCType::DEAD_TREE, deadTreePos.x, deadTreePos.y);
	npcList.add(deadTree);
	deadTree->activeOnStage = StageIndex::TOWER_2;

	NPC* tree = (NPC*)app->entities->CreateEntity(NPCType::TREE, treePos.x, treePos.y);
	npcList.add(tree);
	tree->activeOnStage = StageIndex::TOWER_2;

	NPC* rip = (NPC*)app->entities->CreateEntity(NPCType::RIP, ripPos.x, ripPos.y);
	npcList.add(rip);
	rip->activeOnStage = StageIndex::TOWER_3;

	NPC* rip2 = (NPC*)app->entities->CreateEntity(NPCType::RIP_2, rip2Pos.x, rip2Pos.y);
	npcList.add(rip2);
	rip2->activeOnStage = StageIndex::TOWER_3;

	NPC* rip3 = (NPC*)app->entities->CreateEntity(NPCType::RIP_3, rip3Pos.x, rip3Pos.y);
	npcList.add(rip3);
	rip3->activeOnStage = StageIndex::TOWER_3;

	// ============================

	app->stages->npcListPtr = &npcList;

	{
		//iPoint batPos = { 600, 100 };

		NormalEnemy* eye = (NormalEnemy*)app->entities->CreateEntity(NormalEnemyType::FLYING_EYE, eyePos.x, eyePos.y);
		normalEnemyList.add(eye);
		eye->activeOnStage = StageIndex::DOJO;

		NormalEnemy* bat = (NormalEnemy*)app->entities->CreateEntity(NormalEnemyType::BAT, batPos.x, batPos.y);
		normalEnemyList.add(bat);
		bat->activeOnStage = StageIndex::DOJO;

		NormalEnemy* skeleton = (NormalEnemy*)app->entities->CreateEntity(NormalEnemyType::SKELETON, skeletonPos.x, skeletonPos.y);
		normalEnemyList.add(skeleton);
		skeleton->activeOnStage = StageIndex::DOJO;


		// TOWER ENEMIES 1
		NormalEnemy* batT1 = (NormalEnemy*)app->entities->CreateEntity(NormalEnemyType::BAT, batPosT1.x, batPosT1.y);
		batT1->chasePlayer = true;
		normalEnemyList.add(batT1);
		batT1->activeOnStage = StageIndex::TOWER_1;

		NormalEnemy* batT1_2 = (NormalEnemy*)app->entities->CreateEntity(NormalEnemyType::BAT, batPosT1_2.x, batPosT1_2.y);
		batT1_2->chasePlayer = true;
		normalEnemyList.add(batT1_2);
		batT1_2->activeOnStage = StageIndex::TOWER_1;

		NormalEnemy* skeletonT1 = (NormalEnemy*)app->entities->CreateEntity(NormalEnemyType::SKELETON, skeletonPosT1_2.x, skeletonPosT1_2.y);
		skeletonT1->chasePlayer = true;
		normalEnemyList.add(skeletonT1);
		skeletonT1->activeOnStage = StageIndex::TOWER_1;

		NormalEnemy* skeletonT1_2 = (NormalEnemy*)app->entities->CreateEntity(NormalEnemyType::SKELETON, skeletonPosT1_3.x, skeletonPosT1_3.y);
		skeletonT1_2->chasePlayer = true;
		normalEnemyList.add(skeletonT1_2);
		skeletonT1_2->activeOnStage = StageIndex::TOWER_1;

		NormalEnemy* skeletonT1_3 = (NormalEnemy*)app->entities->CreateEntity(NormalEnemyType::SKELETON, skeletonPosT1.x, skeletonPosT1.y);
		skeletonT1_3->chasePlayer = true;
		normalEnemyList.add(skeletonT1_3);
		skeletonT1_3->activeOnStage = StageIndex::TOWER_1;

		NormalEnemy* eyeT1 = (NormalEnemy*)app->entities->CreateEntity(NormalEnemyType::FLYING_EYE, eyePosT1.x, eyePosT1.y);
		eyeT1->chasePlayer = true;
		normalEnemyList.add(eyeT1);
		eyeT1->activeOnStage = StageIndex::TOWER_1;

		NormalEnemy* eyeT1_2 = (NormalEnemy*)app->entities->CreateEntity(NormalEnemyType::FLYING_EYE, eyePosT1_2.x, eyePosT1_2.y);
		eyeT1_2->chasePlayer = true;
		normalEnemyList.add(eyeT1_2);
		eyeT1_2->activeOnStage = StageIndex::TOWER_1;

		NormalEnemy* eyeT1_3 = (NormalEnemy*)app->entities->CreateEntity(NormalEnemyType::FLYING_EYE, eyePosT1_3.x, eyePosT1_3.y);
		eyeT1_3->chasePlayer = true;
		normalEnemyList.add(eyeT1_3);
		eyeT1_3->activeOnStage = StageIndex::TOWER_1;

		// TOWER ENEMIES 2

		NormalEnemy* batT2 = (NormalEnemy*)app->entities->CreateEntity(NormalEnemyType::BAT, batPosT2.x, batPosT2.y);
		batT2->chasePlayer = true;

		normalEnemyList.add(batT2);
		batT2->activeOnStage = StageIndex::TOWER_2;

		NormalEnemy* batT2_2 = (NormalEnemy*)app->entities->CreateEntity(NormalEnemyType::BAT, batPosT2_2.x, batPosT2_2.y);
		batT2_2->chasePlayer = true;
		normalEnemyList.add(batT2_2);
		batT2_2->activeOnStage = StageIndex::TOWER_2;

		NormalEnemy* skeletonT2 = (NormalEnemy*)app->entities->CreateEntity(NormalEnemyType::SKELETON, skeletonPosT2_2.x, skeletonPosT2_2.y);
		skeletonT2->chasePlayer = true;
		normalEnemyList.add(skeletonT2);
		skeletonT2->activeOnStage = StageIndex::TOWER_2;

		NormalEnemy* skeletonT2_2 = (NormalEnemy*)app->entities->CreateEntity(NormalEnemyType::SKELETON, skeletonPosT2_3.x, skeletonPosT2_3.y);
		skeletonT2_2->chasePlayer = true;
		normalEnemyList.add(skeletonT2_2);
		skeletonT2_2->activeOnStage = StageIndex::TOWER_2;

		NormalEnemy* skeletonT2_3 = (NormalEnemy*)app->entities->CreateEntity(NormalEnemyType::SKELETON, skeletonPosT2.x, skeletonPosT2.y);
		skeletonT2_3->chasePlayer = true;
		normalEnemyList.add(skeletonT2_3);
		skeletonT2_3->activeOnStage = StageIndex::TOWER_2;

		NormalEnemy* eyeT2 = (NormalEnemy*)app->entities->CreateEntity(NormalEnemyType::FLYING_EYE, eyePosT2.x, eyePosT2.y);
		eyeT2->chasePlayer = true;
		normalEnemyList.add(eyeT2);
		eyeT2->activeOnStage = StageIndex::TOWER_2;

		NormalEnemy* eyeT2_2 = (NormalEnemy*)app->entities->CreateEntity(NormalEnemyType::FLYING_EYE, eyePosT2_2.x, eyePosT2_2.y);
		eyeT2_2->chasePlayer = true;
		normalEnemyList.add(eyeT2_2);
		eyeT2_2->activeOnStage = StageIndex::TOWER_2;

		NormalEnemy* eyeT2_3 = (NormalEnemy*)app->entities->CreateEntity(NormalEnemyType::FLYING_EYE, eyePosT2_3.x, eyePosT2_3.y);
		eyeT2_3->chasePlayer = true;
		normalEnemyList.add(eyeT2_3);
		eyeT2_3->activeOnStage = StageIndex::TOWER_2;

		// TOWER ENEMIES 3

		NormalEnemy* batT3 = (NormalEnemy*)app->entities->CreateEntity(NormalEnemyType::BAT, batPosT3.x, batPosT3.y);
		batT3->chasePlayer = true;
		normalEnemyList.add(batT3);
		batT3->activeOnStage = StageIndex::TOWER_3;

		NormalEnemy* batT3_2 = (NormalEnemy*)app->entities->CreateEntity(NormalEnemyType::BAT, batPosT3_2.x, batPosT3_2.y);
		batT3_2->chasePlayer = true;
		normalEnemyList.add(batT3_2);
		batT3_2->activeOnStage = StageIndex::TOWER_3;

		NormalEnemy* skeletonT3 = (NormalEnemy*)app->entities->CreateEntity(NormalEnemyType::SKELETON, skeletonPosT3_2.x, skeletonPosT3_2.y);
		skeletonT3->chasePlayer = true;
		normalEnemyList.add(skeletonT3);
		skeletonT3->activeOnStage = StageIndex::TOWER_3;

		NormalEnemy* skeletonT3_2 = (NormalEnemy*)app->entities->CreateEntity(NormalEnemyType::SKELETON, skeletonPosT3_3.x, skeletonPosT3_3.y);
		skeletonT3_2->chasePlayer = true;
		normalEnemyList.add(skeletonT3_2);
		skeletonT3_2->activeOnStage = StageIndex::TOWER_3;

		NormalEnemy* skeletonT3_3 = (NormalEnemy*)app->entities->CreateEntity(NormalEnemyType::SKELETON, skeletonPosT3.x, skeletonPosT3.y);
		skeletonT3_3->chasePlayer = true;
		normalEnemyList.add(skeletonT3_3);
		skeletonT3_3->activeOnStage = StageIndex::TOWER_3;

		NormalEnemy* eyeT3 = (NormalEnemy*)app->entities->CreateEntity(NormalEnemyType::FLYING_EYE, eyePosT3.x, eyePosT3.y);
		eyeT3->chasePlayer = true;
		normalEnemyList.add(eyeT3);
		eyeT3->activeOnStage = StageIndex::TOWER_3;

		NormalEnemy* eyeT3_2 = (NormalEnemy*)app->entities->CreateEntity(NormalEnemyType::FLYING_EYE, eyePosT3_2.x, eyePosT3_2.y);
		eyeT3_2->chasePlayer = true;
		normalEnemyList.add(eyeT3_2);
		eyeT3_2->activeOnStage = StageIndex::TOWER_3;

		NormalEnemy* eyeT3_3 = (NormalEnemy*)app->entities->CreateEntity(NormalEnemyType::FLYING_EYE, eyePosT3_3.x, eyePosT3_3.y);
		eyeT3_3->chasePlayer = true;
		normalEnemyList.add(eyeT3_3);
		eyeT3_3->activeOnStage = StageIndex::TOWER_3;
	}

	app->stages->normalEnemyListPtr = &normalEnemyList;
	app->stages->bossListPtr = &bossList;


	// TOWN LIMITS for camera
	app->camera->SetLimits(640, 350, 4490, 4200);

	pause = false;
	playing = true;
	godmode = false;

	app->guiManager->Enable();

	if (playloading == true) {
		playloading = false;
		app->LoadGameRequest();
	}

	restart->state = GuiControlState::DISABLED;
	backtoMenu->state = GuiControlState::DISABLED;

	// UI

	characterBG = app->tex->Load("Assets/gui/inventory/ui_inventory_char.png");

	allStages.add(StageIndex::INTRODUCTION);
	allStages.add(StageIndex::PROLOGUE);
	allStages.add(StageIndex::TOWN);
	allStages.add(StageIndex::DOJO);
	allStages.add(StageIndex::SHOP);
	allStages.add(StageIndex::SHOPSUB);
	allStages.add(StageIndex::TAVERN);
	allStages.add(StageIndex::TOWER_0);
	allStages.add(StageIndex::TOWER_1);
	allStages.add(StageIndex::TOWER_3);
	allStages.add(StageIndex::TOWER_4);
	allStages.add(StageIndex::TOWER_BOSS_1);
	allStages.add(StageIndex::TOWER_BOSS_2);
	allStages.add(StageIndex::TOWER_BOSS_3);
	allStages.add(StageIndex::WIN);
	allStages.add(StageIndex::LOSE);
	allStages.add(StageIndex::INTRODUCTION);

	stageSwap = allStages.start;

	joinFx = app->audio->LoadFx("Assets/audio/sfx/fx_join.wav");

	join1T = app->tex->Load("Assets/textures/join_party/valionJOINS.png");
	join2T = app->tex->Load("Assets/textures/join_party/raylaJOINS.png");
	join3T = app->tex->Load("Assets/textures/join_party/dhionJOINS.png");

	return true;
}

bool Scene::PreUpdate()
{
	if (delayForCrashUwU > 0) {
		delayForCrashUwU--;

		if (delayForCrashUwU < 5) {
			app->scene->stageSwap->data = app->stages->actualStage;
		}
	}

	bool ret = true;

	if (app->pauseM->exitg) {
		if (pause == false) {
			pause = true;
			app->audio->PlayFx(backFx);
		}
		app->pauseM->exitg = false;
		
		
		app->fade->DoFadeToBlack(this, (Module*)app->titleScene);
		app->pauseM->CleanUp();
	}
	
	// Hide UI
	guiactivate = false;

	return ret;
}

bool Scene::Update(float dt)
{
	int xm = -app->camera->GetPos().x / 2,
		ym = -app->camera->GetPos().y / 2;
	int xt, yt;
	//variables for textures
	xt = -app->camera->GetPos().x / 2 + app->win->GetWidth() / 2;
	yt = -app->camera->GetPos().y / 2 + app->win->GetHeight() / 2;

	if (app->stmen->isEnabled() || app->inventory->isEnabled())app->scene->player->canMove = false;

	fpsdt = dt*3.75;

	if (app->input->GetKey(SDL_SCANCODE_F11) == KEY_DOWN)
	{
		debugMODE = !debugMODE;

		LOG("Turning on/off Debug Mode");

		stageSwap->data = app->stages->actualStage;
	}
	// ================================
	//			DEBUG KEYS 
	// ================================

	if (app->input->GetKey(SDL_SCANCODE_F10) == KEY_DOWN)
	{
		if (godmode)
		{
			godmode = false;

			for (int i = 0; i < partyList.count(); i++)
			{
				partyList.At(i)->data->stats->LoadStats();
			}

			LOG("GOD MODE OFF");

		}
		else
		{
			for (int i = 0; i < partyList.count(); i++)
			{
				partyList.At(i)->data->stats->SaveStats();
				partyList.At(i)->data->stats->level = 10;
				partyList.At(i)->data->stats->SetStats(9999, 9999, 9999, 9999);
			}

			godmode = true;
			LOG("GOD MODE ON");

		}
	}

	if (debugMODE) 
	{

		if (app->input->GetKey(SDL_SCANCODE_F2) == KEY_DOWN) {
			if (stageSwap->next != NULL) {
				stageSwap = stageSwap->next;
			}
			else {
				stageSwap = allStages.start;
			}
			app->stages->ChangeStage(stageSwap->data);
		}

		if (app->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN) {
			if (stageSwap->prev != NULL) {
				stageSwap = stageSwap->prev;
			}
			else {
				stageSwap = allStages.end;
			}
			app->stages->ChangeStage(stageSwap->data);
		}

		
		if (!godmode)
		{

			// Add ally to the party
			if (app->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN) {

				if (partyList.At(1) == nullptr) {
					int x = 80;
					int y = 130 - 50;
					partyList.add((Party*)app->entities->CreateEntity(PartyType::VALION, x, y));

					/*if (godmode) {

						partyList.At(1)->data->stats->SaveStats();
						partyList.At(1)->data->stats->SetStats(9999, 9999, 9999, 9999);

					}*/

				}
				else {
					partyList.del(partyList.At(1));
				}
				//partyList.At(1) == nullptr ? partyList.add((Party*)app->entities->CreateEntity(PartyType::VALION, 20, 50)) : partyList.del(partyList.At(1));
			}
			if (app->input->GetKey(SDL_SCANCODE_2) == KEY_DOWN) {

				if (partyList.At(2) == nullptr) {
					int x = -200;
					int y = 120 - 50;
					partyList.add((Party*)app->entities->CreateEntity(PartyType::RAYLA, x, y));
				}
				else {
					partyList.del(partyList.At(2));
				}
				//partyList.At(1) == nullptr ? partyList.add((Party*)app->entities->CreateEntity(PartyType::VALION, 20, 50)) : partyList.del(partyList.At(1));
			}
			if (app->input->GetKey(SDL_SCANCODE_3) == KEY_DOWN) {

				if (partyList.At(3) == nullptr) {
					int x = 200;
					int y = 0 - 50;
					partyList.add((Party*)app->entities->CreateEntity(PartyType::DHION, x, y));
				}
				else {
					partyList.del(partyList.At(3));
				}
				//partyList.At(1) == nullptr ? partyList.add((Party*)app->entities->CreateEntity(PartyType::VALION, 20, 50)) : partyList.del(partyList.At(1));
			}
		}
	}

	// Inventory
	if (app->inventory->isEnabled() == false) {
		if (app->input->GetKey(SDL_SCANCODE_I) == KEY_DOWN) {
			app->inventory->Enable();
		}
	}
	// Stats
	if (app->input->GetKey(SDL_SCANCODE_E) == KEY_DOWN) {
		app->stmen->Enable();
	}
	if (app->input->GetKey(SDL_SCANCODE_Q) == KEY_REPEAT) {
		
		app->render->DrawTexture(mini_map, xm+50, ym+50);
	}
	if (app->stages->actualStage == StageIndex::WIN) {
		restart->state = GuiControlState::DISABLED;
		backtoMenu->state = GuiControlState::NORMAL;
	}
	if (app->stages->actualStage == StageIndex::LOSE) {
		backtoMenu->state = GuiControlState::DISABLED;
		restart->state = GuiControlState::NORMAL;
	}
	if (app->stages->actualStage != StageIndex::WIN) {
		backtoMenu->state = GuiControlState::DISABLED;
	}
	if (app->stages->actualStage != StageIndex::LOSE) {
		restart->state = GuiControlState::DISABLED;
	}

	return true;
}

// Render bullshit
bool Scene::PostUpdate()
{
	bool ret = true;
	int w = 45, h = 5, wpm=25;


	std::string fps = std::to_string(fpsdt);
	char const* fpsChar = fps.c_str();
	
	// Variables
	int x = -app->camera->GetPos().x / 2,
		y = -app->camera->GetPos().y / 2;

	if (guiactivate == true && app->stages->actualStage != StageIndex::WIN && app->stages->actualStage != StageIndex::LOSE)
	{
		// Checkear miembros de la party y imprimir sus carteles

		if (app->battle->isEnabled() == false) {
			ShowGUI();
		}
	}
	if (app->collisions->debug)
	{
		app->font->DrawText(fpsChar, x + 10, y + 100);
		
		app->render->Vsync == true?	app->font->DrawText("Vsync: On", x + 10, y + 120): app->font->DrawText("Vsync: Off", x + 10, y + 120);
		
	}
	if (app->stages->actualStage == StageIndex::WIN) {
		backtoMenu->state != GuiControlState::PRESSED ? app->render->DrawTexture(backtoMenuTex, 240, 280) : app->render->DrawTexture(press_backtoMenuTex, 240, 280);
	}
	if (app->stages->actualStage == StageIndex::LOSE) {
		restart->state != GuiControlState::PRESSED ? app->render->DrawTexture(restartTex, 280, 280) : app->render->DrawTexture(press_restartTex, 280, 280);

	}

	x = -app->camera->GetPos().x / 2,
	y = -app->camera->GetPos().y / 2;

	if (godmode) {
		if (showGod > 0) {
			app->font->DrawText("Godmode is Enabled", x, y + 150);
			showGod--;
		}
		dontShowGod = debugMessagesCooldown;
	}
	else {
		if (dontShowGod > 0) {
			app->font->DrawText("Godmode Disabled", x, y + 150);
			dontShowGod--;
		}
		showGod = debugMessagesCooldown;
	}

	if (debugMODE) {
		if (showDebug > 0) {
			app->font->DrawText("Debug mode is Enabled", x, y + 180);
			showDebug--;
		}
		dontShowDebug = debugMessagesCooldown;
	}
	else {
		if (dontShowDebug > 0) {
			app->font->DrawText("Debug mode disabled", x, y + 180);
			dontShowDebug--;
		}
		showDebug = debugMessagesCooldown;
	}

	if (partyList.At(1) != nullptr) {
		if (join1 == joinCooldown) {
			app->audio->PlayFx(joinFx);
		}
		if (join1 > 0) {
			join1--;
			app->render->DrawTexture(join1T, x, y);
		}
	}
	else {
		join1 = joinCooldown;
	}

	if (partyList.At(2) != nullptr) {
		if (join2 == joinCooldown) {
			app->audio->PlayFx(joinFx);
		}
		if (join2 > 0) {
			join2--;
			app->render->DrawTexture(join2T, x, y);
		}
	}
	else {
		join2 = joinCooldown;
	}

	if (partyList.At(3) != nullptr) {
		if (join3 == joinCooldown) {
			app->audio->PlayFx(joinFx);
		}
		if (join3 > 0) {
			join3--;
			app->render->DrawTexture(join3T, x, y);
		}
	}
	else {
		join3 = joinCooldown;
	}

	return ret;
}

bool Scene::OnGuiMouseClickEvent(GuiControl* control)
{
	switch (control->type)
	{
	case GuiControlType::BUTTON:
	{
		//Checks the GUI element ID
		if (control->id == 1)
		{
			LOG("Click on button 1");
		}

		if (control->id == 2)
		{
			LOG("Click on button 2");
		}

		if (app->stages->actualStage == StageIndex::LOSE) {
	
			if (control->id == 40)
			{
				LOG("Click on Restart");
			
				restart->state = GuiControlState::DISABLED;
				backtoMenu->state = GuiControlState::DISABLED;

				app->camera->SetTarget(player);
				app->LoadGameRequest();
				app->scene->player->canMove = true;
				

			}
		}
		if (app->stages->actualStage == StageIndex::WIN) {
			if (control->id == 41)
			{
				LOG("Click on Back to Menu");

				restart->state = GuiControlState::DISABLED;
				backtoMenu->state = GuiControlState::DISABLED;

				app->fade->DoFadeToBlack(this, (Module*)app->titleScene);


			}
		}
	}
	//Other cases here

	default: break;
	}

	return true;
}

// Called before quitting
bool Scene::CleanUp()
{
	LOG("Freeing scene");

	app->font->CleanFonts();

	app->camera->ReleaseTarget();

	app->tex->UnLoad(restartTex);
	app->tex->UnLoad(backtoMenuTex);
	app->tex->UnLoad(press_restartTex);
	app->tex->UnLoad(press_backtoMenuTex);
	app->tex->UnLoad(characterBG);
	app->tex->UnLoad(locationUI);

	//Stages:
	app->entities->DestroyEntity(player);

	restart->state = GuiControlState::DISABLED;
	backtoMenu->state = GuiControlState::DISABLED;

	app->stages->ChangeStage(StageIndex::NONE);

	
	ListItem<Item*>* itemInList;
	for (itemInList = itemList.start; itemInList != NULL; itemInList = itemInList->next)
	{
		itemInList->data->CleanUp();
	}

	ListItem<NPC*>* npcInList;
	for (npcInList = npcList.start; npcInList != NULL; npcInList = npcInList->next)
	{
		npcInList->data->CleanUp();
	}

	ListItem<NormalEnemy*>* normalEnemyInList;
	for (normalEnemyInList = normalEnemyList.start; normalEnemyInList != NULL; normalEnemyInList = normalEnemyInList->next)
	{
		normalEnemyInList->data->CleanUp();
	}

	ListItem<Character*>* characterInList;
	for (characterInList = partyList.start; characterInList != NULL; characterInList = characterInList->next)
	{
		characterInList->data->CleanUp();
	}

	itemList.clear();
	npcList.clear();
	normalEnemyList.clear();
	partyList.clear();

	player = nullptr;
	delete player;

	app->dialogs->Disable();

	app->map->Disable();

	delayForCrashUwU = 60;

	return true;
}

void Scene::ShowGUI() 
{
	int x = -app->camera->GetPos().x / 2,
		y = -app->camera->GetPos().y / 2,
		charX = x + 110,
		charY = y + 5;

	ListItem<Character*>* ch = partyList.start;

	for (ch; ch != NULL; ch = ch->next)
	{
		app->render->DrawTexture(characterBG, charX, charY);

		app->render->DrawTexture(ch->data->spriteFace, charX + 15, charY + 20);

		app->font->DrawText(ch->data->name, charX + 25, charY - 2);
		charX += 130;
	}

	CharBars();

	// Current Stage on UI
	if (showLocation == true) {
		app->render->DrawTexture(locationUI, x + 10, y + 25);

		switch (app->stages->actualStage) {
		case StageIndex::NONE:
			break;
		case StageIndex::TOWN:
			sprintf_s(currentPlace_UI, "Town");

			app->font->DrawText(currentPlace_UI, x + 25, y + 30, { 0, 0, 0 });
			break;
		case StageIndex::DOJO:
			sprintf_s(currentPlace_UI, "Dojo");

			app->font->DrawText(currentPlace_UI, x + 30, y + 30, { 0, 0, 0 });
			break;
		case StageIndex::SHOP:
			sprintf_s(currentPlace_UI, "Shop");

			app->font->DrawText(currentPlace_UI, x + 30, y + 30, { 0, 0, 0 });
			break;
		case StageIndex::SHOPSUB:
			sprintf_s(currentPlace_UI, "Shop -1");

			app->font->DrawText(currentPlace_UI, x + 25, y + 30, { 0, 0, 0 });
			break;
		case StageIndex::TAVERN:
			sprintf_s(currentPlace_UI, "Tavern");

			app->font->DrawText(currentPlace_UI, x + 20, y + 30, { 0, 0, 0 });
			break;
		case StageIndex::TOWER_0:
			sprintf_s(currentPlace_UI, "Tower");

			app->font->DrawText(currentPlace_UI, x + 20, y + 30, { 0, 0, 0 });
			break;
		case StageIndex::TOWER_1:
			sprintf_s(currentPlace_UI, "Floor 1");

			app->font->DrawText(currentPlace_UI, x + 20, y + 30, { 0, 0, 0 });
			break;
		case StageIndex::TOWER_2:
			sprintf_s(currentPlace_UI, "Floor 2");

			app->font->DrawText(currentPlace_UI, x + 20, y + 30, { 0, 0, 0 });
			break;
		case StageIndex::TOWER_4:
			sprintf_s(currentPlace_UI, "Floor 4");

			app->font->DrawText(currentPlace_UI, x + 20, y + 30, { 0, 0, 0 });
			break;
		case StageIndex::TOWER_3:
			sprintf_s(currentPlace_UI, "Floor 3");

			app->font->DrawText(currentPlace_UI, x + 20, y + 30, { 0, 0, 0 });
			break;
		case StageIndex::TOWER_BOSS_1:
			sprintf_s(currentPlace_UI, "Boss 1");

			app->font->DrawText(currentPlace_UI, x + 20, y + 30, { 0, 0, 0 });
			break;
		case StageIndex::TOWER_BOSS_2:
			sprintf_s(currentPlace_UI, "Boss 2");

			app->font->DrawText(currentPlace_UI, x + 20, y + 30, { 0, 0, 0 });
			break; case StageIndex::TOWER_BOSS_3:
				sprintf_s(currentPlace_UI, "Boss 3");

				app->font->DrawText(currentPlace_UI, x + 20, y + 30, { 0, 0, 0 });
				break;
		case StageIndex::PROLOGUE:
			sprintf_s(currentPlace_UI, "The City");

			app->font->DrawText(currentPlace_UI, x + 15, y + 30, { 0, 0, 0 });
			break;
		}
	}
}
void Scene::CharBars()
{
	// Variables
	int w = 35, h = 6, wpm = 25;
	int x = -app->camera->GetPos().x / 2,
		y = -app->camera->GetPos().y / 2,
		barsX = x + 173,
		barsY = y + 28;
	
	if (guiactivate == true && app->stages->actualStage != StageIndex::WIN && app->stages->actualStage != StageIndex::LOSE)
	{
		// Party List
		ListItem<Character*>* ch = partyList.start;

		//// Debug Keys:
		//if (app->input->GetKey(SDL_SCANCODE_H) == KEY_DOWN) {
		//	for (ch; ch != NULL; ch = ch->next) {
		//		ch->data->stats->health += 1;
		//	}
		//}
		//ch = partyList.start;
		//if (app->input->GetKey(SDL_SCANCODE_J) == KEY_DOWN) {
		//	//for (ch; ch != NULL; ch = ch->next) {
		//		partyList.At(0)->data->stats->health -= 1;
		//	//}
		//}
		ch = partyList.start;

		// Barras Stats Party
		for (ch; ch != NULL; ch = ch->next) {
			// HP bars
			if (ch->data->stats != nullptr &&/* ch->data->stats->health != NULL &&*/ ch->data->stats->maxHealth != NULL && ch->data->stats->mana != NULL && ch->data->stats->maxMana != NULL) {
				hpc = ((float)ch->data->stats->health / (float)ch->data->stats->maxHealth) * w;
				SDL_Rect HPrect = { barsX + 7, barsY, hpc, h };

				app->render->DrawRectangle({ barsX + 7, barsY, w, h }, 0, 0, 0);
				app->render->DrawRectangle(HPrect, 0, 255, 0);

				// PM bars
				pmc = ((float)ch->data->stats->mana / (float)ch->data->stats->maxMana) * wpm;
				SDL_Rect  PMrect = { barsX + 7, barsY + h + 1, pmc, h };
				app->render->DrawRectangle({ barsX + 7, barsY + h + 1, wpm, h }, 0, 0, 0);
				app->render->DrawRectangle(PMrect, 0, 78, 255);

				// Life text
				sprintf_s(lifeTextUI, 50, "hp:%2d", ch->data->stats->health);
				app->font->DrawText(lifeTextUI, barsX, barsY + h + 9, { 0,255,30 });
				barsX += 130;
			}
		}
	}
}

bool Scene::AddItem(UsableType type) {
	if (itemList.count() < app->inventory->inventorySlots) {
		Usable* item = (Usable*)app->entities->CreateEntity(type);
		itemList.add(item);

		return true;
	}
	else {
		LOG("Inventory is full");
		return false;
	}
}

void Scene::FixAdd(int i, int x, int y)
{
	if (godmode)
	{

		if (partyList.At(i)->data != nullptr)
		{
			while (partyList.At(i)->data == nullptr)
			{
				partyList.del(partyList.At(i));

				switch (i)
				{
				case 1:

					partyList.add((Party*)app->entities->CreateEntity(PartyType::VALION, x, y));

					break;

				case 2:

					partyList.add((Party*)app->entities->CreateEntity(PartyType::RAYLA, x, y));

					break;

				case 3:

					partyList.add((Party*)app->entities->CreateEntity(PartyType::DHION, x, y));

					break;
				}

				//if (partyList.At(i) != nullptr &&  /*&& partyList.At(i)->data->stats->attack!=9999*/)
				//{


				//}

			/*for (int i = 0; i < partyList.count(); i++)
			{*/
			//}
				LOG("AAAAAAAAAAAAAAAAAAAAA");

			}
		}
		if (!partyList.At(i)->data->stats->firstgod)
		{

			partyList.At(i)->data->stats->SaveStats();
			partyList.At(i)->data->stats->SetStats(9999, 9999, 9999, 9999);
			partyList.At(i)->data->stats->firstgod = true;
		}

	}
}