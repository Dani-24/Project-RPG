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
#include "Stages.h"
#include "Defs.h"
#include "Log.h"
#include "DynamicEntity.h"
#include "NPC.h"
#include "NormalEnemy.h"
#include "BossEnemy.h"
#include "Camera.h"
#include "Pathfinder.h"
#include "ModuleParticles.h"

Stages::Stages(App* application, bool start_enabled) : Module(application, start_enabled)
{
	name.Create("stages");

	actualStage = StageIndex::NONE;
	playerPtr = nullptr;

	onBattle = pause = false;

	carRedL.PushBack({ 0, 32, 64, 32 });
	carRedR.PushBack({ 0, 0, 64, 32 });
	carBlueL.PushBack({ 64, 32, 64, 32 });
	carBlueR.PushBack({ 64, 0, 64, 32 });
	carGreenL.PushBack({ 128, 32, 64, 32 });
	carGreenR.PushBack({ 128, 0, 64, 32 });
	carPinkL.PushBack({ 192, 32, 64, 32 });
	carPinkR.PushBack({ 192, 0, 64, 32 });
	carGreyL.PushBack({ 256, 32, 64, 32 });
	carGreyR.PushBack({ 256, 0, 64, 32 });

}

Stages::~Stages()
{}

bool Stages::Awake(pugi::xml_node& config)
{
	LOG("Loading Stages.cpp");
	bool ret = true;

	LoseScreenChar = config.child("losescreen").attribute("path").as_string();
	WinScreenChar = config.child("winscreen").attribute("path").as_string();
	LoseTextChar = config.child("losetext").attribute("path").as_string();
	WinTextChar = config.child("wintext").attribute("path").as_string();
	Hitfx1Char = config.child("hit1fx").attribute("path").as_string();
	Hitfx2Char = config.child("hit2fx").attribute("path").as_string();
	Hitfx3Char = config.child("hit3fx").attribute("path").as_string();
	ShieldfxChar = config.child("shieldfx").attribute("path").as_string();
	ChDiefxChar = config.child("chdiefx").attribute("path").as_string();
	DoorChar = config.child("doorfx").attribute("path").as_string();
	LosefxChar = config.child("losefx").attribute("path").as_string();

	return ret;
}

bool Stages::Start()
{
	//sfx
	hitfx1 = app->audio->LoadFx(Hitfx1Char.GetString());
	hitfx2 = app->audio->LoadFx(Hitfx2Char.GetString());
	hitfx3 = app->audio->LoadFx(Hitfx3Char.GetString());
	shieldfx = app->audio->LoadFx(ShieldfxChar.GetString());
	chdiefx = app->audio->LoadFx(ChDiefxChar.GetString());
	doorFx = app->audio->LoadFx(DoorChar.GetString());
	loseFx = app->audio->LoadFx(LosefxChar.GetString());

	//textures
	LoseScreen = app->tex->Load(LoseScreenChar.GetString());
	WinScreen = app->tex->Load(WinScreenChar.GetString());
	WinMessage = app->tex->Load(WinTextChar.GetString());
	LoseMessage = app->tex->Load(LoseTextChar.GetString());

	_wait = false;
	elect = true;

	srand(SDL_GetTicks());

	return true;
}

bool Stages::PreUpdate()
{
	bool ret = true;

	switch (actualStage)
	{
	case StageIndex::NONE:
		intStage = 1;
		break;
	case StageIndex::TOWN:
		intStage = 2;
		break;
	case StageIndex::TAVERN:
		intStage = 3;
		break;
	case StageIndex::DOJO:
		intStage = 4;
		break;
	case StageIndex::SHOP:
		intStage = 5;
		break;
	case StageIndex::SHOPSUB:
		intStage = 6;
		break;
	case StageIndex::INTRODUCTION:
		intStage = 7;
		break;
	case StageIndex::WIN:
		intStage = 8;
		break;
	case StageIndex::LOSE:
		intStage = 9;
		break;
	case StageIndex::TOWER_0:
		intStage = 10;
		break;
	case StageIndex::TOWER_1:
		intStage = 11;
		break;
	case StageIndex::TOWER_2:
		intStage = 12;
		break;
	case StageIndex::TOWER_FINAL_BOSS:
		intStage = 13;
		break;
	case StageIndex::TOWER_3:
		intStage = 14;
		break;
	case StageIndex::TOWER_BOSS_1:
		intStage = 15;
		break;
	case StageIndex::TOWER_BOSS_2:
		intStage = 16;
		break;
	case StageIndex::TOWER_BOSS_3:
		intStage = 17;
		break;
	case StageIndex::PROLOGUE:
		intStage = 18;
		break;
	default:
		break;
	}

	return ret;
}

bool Stages::Update(float dt)
{
	// Movimiento enemigos en el mapa

	if (!app->scene->godmode)
	{
		if (actualStage != StageIndex::NONE) {
			if (normalEnemyListPtr != nullptr && !app->battle->isEnabled()) {
				ListItem<NormalEnemy*>* NormalEnemyInList;
				NormalEnemyInList = normalEnemyListPtr->start;
				for (NormalEnemyInList = normalEnemyListPtr->start; NormalEnemyInList != NULL; NormalEnemyInList = NormalEnemyInList->next)
				{
					if (NormalEnemyInList->data->activeOnStage == app->stages->actualStage && playerPtr != nullptr) {
						// "" Chase player ""
						if (NormalEnemyInList->data->chasePlayer) {
							int chaseDist = 300;

							if (abs(NormalEnemyInList->data->position.x - playerPtr->position.x) < chaseDist && abs(NormalEnemyInList->data->position.y - playerPtr->position.y) < chaseDist)
							{
								if (NormalEnemyInList->data->position.x > playerPtr->position.x) {
									NormalEnemyInList->data->position.x -= NormalEnemyInList->data->chaseSpeed;
								}
								else {
									NormalEnemyInList->data->position.x += NormalEnemyInList->data->chaseSpeed;
								}
								if (NormalEnemyInList->data->position.y > playerPtr->position.y + 30) {
									NormalEnemyInList->data->position.y -= NormalEnemyInList->data->chaseSpeed;
								}
								else {
									NormalEnemyInList->data->position.y += NormalEnemyInList->data->chaseSpeed;
								}

								// Move enemy collider
								NormalEnemyInList->data->baseCollider->SetPos(NormalEnemyInList->data->position.x, NormalEnemyInList->data->position.y);

								// ""Pathfinding""
								iPoint origin = app->map->WorldToMap(NormalEnemyInList->data->position.x, NormalEnemyInList->data->position.y);
								iPoint destination = app->map->WorldToMap(playerPtr->position.x, playerPtr->position.y);
								int path = app->pathfinder->CreatePath(origin, destination);
							}
						}
					}
				}
			}
		}
	}

	// Movimiento truck kun

	// Above the player
	if (actualStage == StageIndex::PROLOGUE) {

		if (npcListPtr != nullptr) {
			ListItem<NPC*>* npcInList;
			npcInList = npcListPtr->start;
			for (npcInList = npcListPtr->start; npcInList != NULL; npcInList = npcInList->next)
			{
				if (npcInList->data->activeOnStage == app->stages->actualStage && playerPtr != nullptr) {
					if (npcInList->data->npcID == 69) {

						if (abs(playerPtr->position.x - npcInList->data->position.x) < 500) {

							if (playerPtr->position.x < npcInList->data->position.x) {
								npcInList->data->position.x-= 2;
							}
							else {
								npcInList->data->position.x+= 2;
							}

							if (playerPtr->position.y < npcInList->data->position.y) {
								npcInList->data->position.y-= 2;
							}
							else {
								npcInList->data->position.y+= 2;
							}

							npcInList->data->baseCollider->SetPos(npcInList->data->position.x, npcInList->data->position.y);
						}
					}
				}
			}
		}
	}

	return true;
}

// Render bullshit
bool Stages::PostUpdate()
{
	bool ret = true;
	GamePad& pad = app->input->pads[0];
	int xm = -app->camera->GetPos().x / 2,
		ym = -app->camera->GetPos().y / 2;
	switch (actualStage)
	{
	case StageIndex::NONE:

		break;
	/*case StageIndex::TOWN:
		if (app->input->GetKey(SDL_SCANCODE_Q) == KEY_REPEAT) {

			app->render->DrawTexture(app->scene->mini_map, xm + 150, ym + 50);
		}
		break;
	case StageIndex::DOJO:
		if (app->input->GetKey(SDL_SCANCODE_Q) == KEY_REPEAT) {

			app->render->DrawTexture(app->scene->mini_map, xm + 150, ym + 50);
		}
		break;
	case StageIndex::SHOP:
		if (app->input->GetKey(SDL_SCANCODE_Q) == KEY_REPEAT) {

			app->render->DrawTexture(app->scene->mini_map, xm + 150, ym + 50);
		}
		break;
	case StageIndex::SHOPSUB:
		if (app->input->GetKey(SDL_SCANCODE_Q) == KEY_REPEAT) {

			app->render->DrawTexture(app->scene->mini_map, xm + 150, ym + 50);
		}
		break;
	case StageIndex::TAVERN:
		if (app->input->GetKey(SDL_SCANCODE_Q) == KEY_REPEAT) {

			app->render->DrawTexture(app->scene->mini_map, xm + 150, ym + 50);
		}
		break;*/
	case StageIndex::INTRODUCTION:

		if (app->fade->fading == false) {
			int epilogX = -app->camera->GetPos().x / app->win->GetScale() + 200;
			int epilogY = -app->camera->GetPos().y / app->win->GetScale() + app->win->GetHeight() / app->win->GetScale() - 300;

			switch (introductionFase)
			{
			case 0:
				app->font->DrawTextDelayed("Hello, traveler soul", epilogX + 35, epilogY);
				break;
			case 1:
				app->font->DrawTextDelayed("Canonically, a truck have just ran over you", epilogX - 100, epilogY);
				break;
			case 2:
				app->font->DrawTextDelayed("Camion-kun, who rules this world", epilogX - 40, epilogY);
				break;
			case 3:
				app->font->DrawTextDelayed("he runs over people and bring their souls here", epilogX - 110, epilogY);
				break;
			case 4:
				app->font->DrawTextDelayed("with the goal of fighting at the tower", epilogX - 50, epilogY + 25, { 255,0,0 });
				break;
			case 5:
				app->font->DrawTextDelayed("But well, I came to ask you some things", epilogX - 60, epilogY);
				break;
			case 6:
				app->font->DrawTextDelayed("and asume your gender with them", epilogX - 50, epilogY);
				break;
			case 7:

				app->font->DrawTextDelayed("Well, as Oak says, are you a boy or a girl?", epilogX - 70, epilogY);
				break;
			case 8:

				app->font->DrawText("Choose with TAB and confirm with Space / Enter", epilogX - 90, epilogY);
				break;
			case 9:
				switch (playerPtr->PlayerErection)
				{
				case 1:
					app->font->DrawTextDelayed("OH! So you want to be a boy-like thing", epilogX - 40, epilogY);
					break;
				case 2:
					app->font->DrawTextDelayed("OH! So you're a girl-like thing", epilogX - 40, epilogY);
					break;
				case 3:
					app->font->DrawTextDelayed("OH! So you're an Apache combat Helicopter", epilogX - 65, epilogY);
					break;
				}

				break;
			case 10:
				app->font->DrawTextDelayed("An amazing adventure awaits you", epilogX - 50, epilogY);
				break;
			case 11:
				app->font->DrawTextDelayed("But first, remember your death", epilogX - 50, epilogY);
				break;
			case 12:
				app->fade->DoFadeToBlack(StageIndex::PROLOGUE);
				break;
			default:
				break;
			}

			if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN || app->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN || pad.a && _wait || pad.b && _wait) {

				if (elect) introductionFase++;
				if (introductionFase == 8) elect = false;
				_wait = false;
			}
			if (!pad.a && !pad.b) _wait = true;
		}

		break;
	case StageIndex::WIN:
		app->camera->SetPos({ 0,0 });
		app->render->DrawTexture(WinScreen, 0, 0);
		app->render->DrawTexture(WinMessage, 0, 0);
		app->scene->player->canMove = false;
		/*restart->state = GuiControlState::DISABLED;*/


		break;
	case StageIndex::LOSE:
		app->camera->SetPos({ 0,0 });
		app->render->DrawTexture(LoseScreen, 0, 0);
		app->render->DrawTexture(LoseMessage, 0, 40);
		app->scene->player->canMove = false;
		/*backtoMenu->state = GuiControlState::DISABLED;*/

		break;

	case StageIndex::TOWER_0:

		break;
	case StageIndex::TOWER_1:
		break;
	case StageIndex::TOWER_2:
		break;
	case StageIndex::TOWER_FINAL_BOSS:
		break;
	case StageIndex::TOWER_3:
		break;
	case StageIndex::TOWER_BOSS_1:
		break;
	case StageIndex::TOWER_BOSS_2:
		break;
	case StageIndex::TOWER_BOSS_3:
		break;
	case StageIndex::PROLOGUE:

		break;
	}

	// NPC & ENEMIES DRAWING
	if (onBattle == false && actualStage != StageIndex::NONE) {

		// Below de player
		if (actualStage != StageIndex::INTRODUCTION) {
			app->map->Draw();
			app->guiManager->Draw();

			if (playerPtr != nullptr) {
				//PRINT THE NPCs BELOW THE PLAYER
				if (npcListPtr != nullptr) {
					ListItem<NPC*>* npcInList;
					npcInList = npcListPtr->start;
					for (npcInList = npcListPtr->start; npcInList != NULL && ret == true; npcInList = npcInList->next)
					{
						if (npcInList->data->activeOnStage == app->stages->actualStage && playerPtr != nullptr) {

							if (npcInList->data->position.y + npcInList->data->currentAnimation->GetCurrentFrame().h <= playerPtr->position.y + playerPtr->currentAnimation->GetCurrentFrame().h) {
								npcInList->data->spriteRect = npcInList->data->currentAnimation->GetCurrentFrame();
								if (npcInList->data->spriteTex != nullptr) { // CHECK if there is some sprite
									if (npcInList->data->npcID == 69) {
										app->render->DrawTexture(npcInList->data->spriteTex, npcInList->data->position.x, npcInList->data->position.y, &npcInList->data->spriteRect, npcInList->data->zoom, 2);
									}
									else {
										app->render->DrawTexture(npcInList->data->spriteTex, npcInList->data->position.x, npcInList->data->position.y, &npcInList->data->spriteRect, npcInList->data->zoom);
									}
								}
							}
						}
					}
				}

				//PRINT THE Enemies BELOW THE PLAYER
				if (normalEnemyListPtr != nullptr) {
					ListItem<NormalEnemy*>* NormalEnemyInList;
					NormalEnemyInList = normalEnemyListPtr->start;
					for (NormalEnemyInList = normalEnemyListPtr->start; NormalEnemyInList != NULL && ret == true; NormalEnemyInList = NormalEnemyInList->next)
					{
						if (NormalEnemyInList->data->activeOnStage == app->stages->actualStage && playerPtr != nullptr) {
							if (NormalEnemyInList->data->baseCollider->rect.y + NormalEnemyInList->data->baseCollider->rect.h <= playerPtr->baseCollider->rect.y) {
								NormalEnemyInList->data->spriteRect = NormalEnemyInList->data->currentAnimation->GetCurrentFrame();
								if (NormalEnemyInList->data->spriteTex != nullptr) { // CHECK if there is some sprite
									app->render->DrawTexture(NormalEnemyInList->data->spriteTex, NormalEnemyInList->data->position.x - NormalEnemyInList->data->SpriteEdges.x, NormalEnemyInList->data->position.y - NormalEnemyInList->data->SpriteEdges.y, &NormalEnemyInList->data->spriteRect, 1, true);
								}
							}
						}
					}
				}
			}
			else {
				//PRINT ONLY THE NPCs
				if (npcListPtr != nullptr) {
					ListItem<NPC*>* npcInList;
					npcInList = npcListPtr->start;
					for (npcInList = npcListPtr->start; npcInList != NULL && ret == true; npcInList = npcInList->next)
					{
						if (npcInList->data->activeOnStage == app->stages->actualStage && playerPtr != nullptr) {
							npcInList->data->spriteRect = npcInList->data->currentAnimation->GetCurrentFrame();
							if (npcInList->data->spriteTex != nullptr) { // CHECK if there is some sprite
								app->render->DrawTexture(npcInList->data->spriteTex, npcInList->data->position.x, npcInList->data->position.y, &npcInList->data->spriteRect, npcInList->data->zoom);
							}
						}
					}
				}

				//PRINT ONLY THE Enemies
				if (normalEnemyListPtr != nullptr) {
					ListItem<NormalEnemy*>* NormalEnemyInList;
					NormalEnemyInList = normalEnemyListPtr->start;
					for (NormalEnemyInList = normalEnemyListPtr->start; NormalEnemyInList != NULL && ret == true; NormalEnemyInList = NormalEnemyInList->next)
					{
						if (NormalEnemyInList->data->activeOnStage == app->stages->actualStage && playerPtr != nullptr) {
							NormalEnemyInList->data->spriteRect = NormalEnemyInList->data->currentAnimation->GetCurrentFrame();
							if (NormalEnemyInList->data->spriteTex != nullptr) { // CHECK if there is some sprite
								app->render->DrawTexture(NormalEnemyInList->data->spriteTex, NormalEnemyInList->data->position.x, NormalEnemyInList->data->position.y, &NormalEnemyInList->data->spriteRect);
							}
						}
					}
				}
			}
		}

		//PRINT THE PLAYER 
		if (playerPtr != nullptr) {
			SDL_Rect rect = playerPtr->currentAnimation->GetCurrentFrame();

			switch (playerPtr->PlayerErection)
			{
			case 1:
				if (playerPtr->PlayerMTex != nullptr) {
					app->render->DrawTexture(playerPtr->PlayerMTex, playerPtr->position.x, playerPtr->position.y, &rect);
				}
				break;
			case 2:
				if (playerPtr->PlayerFTex != nullptr) {
					app->render->DrawTexture(playerPtr->PlayerFTex, playerPtr->position.x, playerPtr->position.y, &rect);
				}
				break;
			case 3:
				if (playerPtr->HeliTex != nullptr) {
					app->render->DrawTexture(playerPtr->HeliTex, playerPtr->position.x - 30, playerPtr->position.y + 8, &rect);
				}
				break;
			}
		}

		// Above the player
		if (actualStage != StageIndex::INTRODUCTION) {
			//PRINT THE NPCs ABOVE THE PLAYER
			if (npcListPtr != nullptr) {
				ListItem<NPC*>* npcInList;
				npcInList = npcListPtr->start;
				for (npcInList = npcListPtr->start; npcInList != NULL && ret == true; npcInList = npcInList->next)
				{
					if (npcInList->data->activeOnStage == app->stages->actualStage && playerPtr != nullptr) {
						if (npcInList->data->position.y + npcInList->data->currentAnimation->GetCurrentFrame().h > playerPtr->position.y + playerPtr->currentAnimation->GetCurrentFrame().h) {
							npcInList->data->spriteRect = npcInList->data->currentAnimation->GetCurrentFrame();
							if (npcInList->data->spriteTex != nullptr) { // CHECK if there is some sprite
								if (npcInList->data->npcID == 69) {
									app->render->DrawTexture(npcInList->data->spriteTex, npcInList->data->position.x, npcInList->data->position.y, &npcInList->data->spriteRect, npcInList->data->zoom, 2);
								}
								else {
									app->render->DrawTexture(npcInList->data->spriteTex, npcInList->data->position.x, npcInList->data->position.y, &npcInList->data->spriteRect, npcInList->data->zoom);
								}
							}
						}
					}
				}
			}

			//PRINT THE Enemies ABOVE THE PLAYER
			if (normalEnemyListPtr != nullptr) {
				ListItem<NormalEnemy*>* NormalEnemyInList;
				NormalEnemyInList = normalEnemyListPtr->start;
				for (NormalEnemyInList = normalEnemyListPtr->start; NormalEnemyInList != NULL && ret == true; NormalEnemyInList = NormalEnemyInList->next)
				{
					if (NormalEnemyInList->data->activeOnStage == app->stages->actualStage && playerPtr != nullptr) {
						if (NormalEnemyInList->data->baseCollider->rect.y + NormalEnemyInList->data->baseCollider->rect.h > playerPtr->baseCollider->rect.y) {
							NormalEnemyInList->data->spriteRect = NormalEnemyInList->data->currentAnimation->GetCurrentFrame();
							if (NormalEnemyInList->data->spriteTex != nullptr) { // CHECK if there is some sprite
								app->render->DrawTexture(NormalEnemyInList->data->spriteTex, NormalEnemyInList->data->position.x - NormalEnemyInList->data->SpriteEdges.x, NormalEnemyInList->data->position.y - NormalEnemyInList->data->SpriteEdges.y, &NormalEnemyInList->data->spriteRect, 1, true);
							}
						}
					}
				}
			}

			app->map->ReDraw();
		}

		if (actualStage == StageIndex::PROLOGUE) {
			CarManagement();
			TrafficLightSystem();
		}
	}

	//PRINT THE BATTLE SPRITES
	if (onBattle == true) {

		//PRINT THE BATTLE ENTITIES

		for (int i = 0; i < 8; i++)
		{

			switch (i) {
			case 0:
				i = 3;
				break;
			case 1:
				i = 1;
				break;
			case 2:
				i = 0;
				break;
			case 3:
				i = 2;
				break;
			}

			if (app->battle->entitiesInBattle[i] != nullptr) {

				//IF THEY ARE ENEMIES
				ListItem<NormalEnemy*>* NormalEnemyInList;

				for (NormalEnemyInList = normalEnemyListPtr->start; NormalEnemyInList != NULL && ret == true; NormalEnemyInList = NormalEnemyInList->next)
				{
					if (app->battle->entitiesInBattle[i] == NormalEnemyInList->data) {
						NormalEnemyInList->data->currentAnimation = &NormalEnemyInList->data->battleAnim;
						if (app->battle->actualTurnEntity == NormalEnemyInList->data) {
							if (app->battle->actualTurnEntity->dynamicType == DynamicType::ENEMY) {
								switch (app->battle->battlePhase) {
								case BattlePhase::THINKING:
									NormalEnemyInList->data->currentAnimation = &NormalEnemyInList->data->battleAnim;
									NormalEnemyInList->data->attackAnim.Reset();
									NormalEnemyInList->data->attackAnim2.Reset();
									NormalEnemyInList->data->attackAnim3.Reset();
									NormalEnemyInList->data->protectAnim.Reset();
									NormalEnemyInList->data->walkAnim.Reset();

									for (int i = 0; i < 8; i++) {
										if (app->battle->entitiesInBattle[i] != nullptr) {
											if (app->battle->entitiesInBattle[i]->isAlive == true)
												if (app->battle->entitiesInBattle[i]->takesDamage == false) {
													app->battle->entitiesInBattle[i]->hitAnim.Reset();
												}
										}
									}

									if (playerPtr->isAlive == true) {
										if (playerPtr->PlayerErection == 1) {
											if (playerPtr->takesDamage == false) {
												playerPtr->hitM.Reset();
											}
										}
										else if (playerPtr->PlayerErection == 2) {
											if (playerPtr->takesDamage == false) {
												playerPtr->hitF.Reset();
											}
										}
									}
									break;
								case BattlePhase::ATTACKING:
									if (eAnim == 1) {
										NormalEnemyInList->data->currentAnimation = &NormalEnemyInList->data->attackAnim;
									}
									if (eAnim == 2) {
										NormalEnemyInList->data->currentAnimation = &NormalEnemyInList->data->attackAnim2;
									}
									if (eAnim == 3) {
										NormalEnemyInList->data->currentAnimation = &NormalEnemyInList->data->attackAnim3;
									}
									if (fxbool == true) {
										fxbool = false;
										app->audio->PlayFx(hitfx1);
									}

									break;
								case BattlePhase::DEFENDING:
									NormalEnemyInList->data->currentAnimation = &NormalEnemyInList->data->protectAnim;
									if (fxbool == true) {
										fxbool = false;
										app->audio->PlayFx(shieldfx);
									}

									break;
								case BattlePhase::OUTCOME:
									if (NormalEnemyInList->data->takesDamage == true) {
										NormalEnemyInList->data->currentAnimation = &NormalEnemyInList->data->hitAnim;
									}
									break;
								case BattlePhase::ESCAPING:

									if (fxbool == true) {
										fxbool = false;

									}
									NormalEnemyInList->data->currentAnimation = &NormalEnemyInList->data->walkAnim;
									break;
								default:
									break;

								}
							}
						}

						if (app->battle->battlePhase == BattlePhase::OUTCOME) {
							if (NormalEnemyInList->data->takesDamage == true) {
								NormalEnemyInList->data->currentAnimation = &NormalEnemyInList->data->hitAnim;
							}
						}

						if (NormalEnemyInList->data->isAlive == false) {
							NormalEnemyInList->data->currentAnimation = &NormalEnemyInList->data->dieAnim;
						}

						NormalEnemyInList->data->spriteRect = NormalEnemyInList->data->currentAnimation->GetCurrentFrame();
						switch (NormalEnemyInList->data->normalEnemyType) {
						case NormalEnemyType::FLYING_EYE:
							if (NormalEnemyInList->data->isSelected == true) {
								app->render->DrawTexture(NormalEnemyInList->data->spriteTex, NormalEnemyInList->data->position.x, NormalEnemyInList->data->position.y, &NormalEnemyInList->data->spriteRect, 2, false, { 255,150,0});
							}
							else {
								app->render->DrawTexture(NormalEnemyInList->data->spriteTex, NormalEnemyInList->data->position.x, NormalEnemyInList->data->position.y, &NormalEnemyInList->data->spriteRect, 2, false);
							}
							break;
						case NormalEnemyType::BAT:
							if (NormalEnemyInList->data->isSelected == true) {
							app->render->DrawTexture(NormalEnemyInList->data->spriteTex, NormalEnemyInList->data->position.x, NormalEnemyInList->data->position.y-30, &NormalEnemyInList->data->spriteRect, 3, false, { 255,150,0 });
							}
							else {
								app->render->DrawTexture(NormalEnemyInList->data->spriteTex, NormalEnemyInList->data->position.x, NormalEnemyInList->data->position.y - 30, &NormalEnemyInList->data->spriteRect, 3, false);
							}
							break;
						case NormalEnemyType::SKELETON:
							if (NormalEnemyInList->data->isSelected == true) {
							app->render->DrawTexture(NormalEnemyInList->data->spriteTex, NormalEnemyInList->data->position.x, NormalEnemyInList->data->position.y, &NormalEnemyInList->data->spriteRect, 2, false, { 255,150,0 });
							}
							else {
								app->render->DrawTexture(NormalEnemyInList->data->spriteTex, NormalEnemyInList->data->position.x, NormalEnemyInList->data->position.y, &NormalEnemyInList->data->spriteRect, 2, false);
							}
							break;
						default:
							if (NormalEnemyInList->data->isSelected == true) {
								app->render->DrawTexture(NormalEnemyInList->data->spriteTex, NormalEnemyInList->data->position.x, NormalEnemyInList->data->position.y, &NormalEnemyInList->data->spriteRect, 1,true,{ 255,150,0 });
							}
							else {
								app->render->DrawTexture(NormalEnemyInList->data->spriteTex, NormalEnemyInList->data->position.x, NormalEnemyInList->data->position.y, &NormalEnemyInList->data->spriteRect);
							}
							break;
						}

						//SHIELDS IN ENEMIES
						if (app->battle->entitiesInBattle[i]->stats->defenseBuffed == true) {
							
							switch (NormalEnemyInList->data->normalEnemyType) {
							case NormalEnemyType::FLYING_EYE:
								if (NormalEnemyInList->data->isSelected == true) {
									app->render->DrawTexture(app->battle->shield, app->battle->entitiesInBattle[i]->position.x - 10, app->battle->entitiesInBattle[i]->position.y + 110, 0, 2, false, { 255,150,0 });
								}
								else {
									app->render->DrawTexture(app->battle->shield, app->battle->entitiesInBattle[i]->position.x - 10, app->battle->entitiesInBattle[i]->position.y + 110, 0, 2, false);
								}
								break;
							case NormalEnemyType::BAT:
								if (NormalEnemyInList->data->isSelected == true) {
									app->render->DrawTexture(app->battle->shield, app->battle->entitiesInBattle[i]->position.x, app->battle->entitiesInBattle[i]->position.y + 130, 0, 2, false, { 255,150,0 });
								}
								else {
									app->render->DrawTexture(app->battle->shield, app->battle->entitiesInBattle[i]->position.x, app->battle->entitiesInBattle[i]->position.y + 130, 0, 2, false);
								}
								break;
							case NormalEnemyType::SKELETON:
								if (NormalEnemyInList->data->isSelected == true) {
									app->render->DrawTexture(app->battle->shield, app->battle->entitiesInBattle[i]->position.x - 20, app->battle->entitiesInBattle[i]->position.y + 100, 0, 2, false, { 255,150,0 });
								}
								else {
									app->render->DrawTexture(app->battle->shield, app->battle->entitiesInBattle[i]->position.x - 20, app->battle->entitiesInBattle[i]->position.y + 100, 0, 2, false);
								}
								break;
							default:
								if (NormalEnemyInList->data->isSelected == true) {
									app->render->DrawTexture(app->battle->shield, app->battle->entitiesInBattle[i]->position.x, app->battle->entitiesInBattle[i]->position.y + 90, 0, 2, false, { 255,150,0 });
								}
								else {
									app->render->DrawTexture(app->battle->shield, app->battle->entitiesInBattle[i]->position.x, app->battle->entitiesInBattle[i]->position.y + 90, 0, 2, false);
								}
								break;
							}

							
						}


					
					}

				}

				//IF THEY ARE BOSSES
				ListItem<BossEnemy*>* BossInList;

				for (BossInList = bossListPtr->start; BossInList != NULL && ret == true; BossInList = BossInList->next)
				{
					if (app->battle->entitiesInBattle[i] == BossInList->data) {
						BossInList->data->currentAnimation = &BossInList->data->battleAnim;
						if (app->battle->actualTurnEntity == BossInList->data) {
							if (app->battle->actualTurnEntity->dynamicType == DynamicType::ENEMY) {
								switch (app->battle->battlePhase) {
								case BattlePhase::THINKING:
									BossInList->data->currentAnimation = &BossInList->data->battleAnim;
									BossInList->data->attackAnim.Reset();
									BossInList->data->attackAnim2.Reset();
									BossInList->data->attackAnim3.Reset();
									BossInList->data->protectAnim.Reset();
									BossInList->data->walkAnim.Reset();

									for (int i = 0; i < 8; i++) {
										if (app->battle->entitiesInBattle[i] != nullptr) {
											if (app->battle->entitiesInBattle[i]->isAlive == true)
												if (app->battle->entitiesInBattle[i]->takesDamage == false) {
													app->battle->entitiesInBattle[i]->hitAnim.Reset();
												}
										}
									}

									if (playerPtr->isAlive == true) {
										if (playerPtr->PlayerErection == 1) {
											if (playerPtr->takesDamage == false) {
												playerPtr->hitM.Reset();
											}
										}
										else if (playerPtr->PlayerErection == 2) {
											if (playerPtr->takesDamage == false) {
												playerPtr->hitF.Reset();
											}
										}
									}
									break;
								case BattlePhase::ATTACKING:
									if (eAnim == 1) {
										BossInList->data->currentAnimation = &BossInList->data->attackAnim;
									}
									if (eAnim == 2) {
										BossInList->data->currentAnimation = &BossInList->data->attackAnim2;
									}
									if (eAnim == 3) {
										BossInList->data->currentAnimation = &BossInList->data->attackAnim3;
									}
									if (fxbool == true) {
										fxbool = false;
										app->audio->PlayFx(hitfx1);
									}

									break;
								case BattlePhase::DEFENDING:
									BossInList->data->currentAnimation = &BossInList->data->protectAnim;
									if (fxbool == true) {
										fxbool = false;
										app->audio->PlayFx(shieldfx);
									}

									break;
								case BattlePhase::OUTCOME:
									if (BossInList->data->takesDamage == true) {
										BossInList->data->currentAnimation = &BossInList->data->hitAnim;
									}
									break;
								case BattlePhase::ESCAPING:

									if (fxbool == true) {
										fxbool = false;

									}
									BossInList->data->currentAnimation = &BossInList->data->walkAnim;
									break;

								default:
									break;

								}
							}
						}

						if (app->battle->battlePhase == BattlePhase::OUTCOME) {
							if (BossInList->data->takesDamage == true) {
								BossInList->data->currentAnimation = &BossInList->data->hitAnim;
							}
						}

						if (BossInList->data->isAlive == false) {
							BossInList->data->currentAnimation = &BossInList->data->dieAnim;
						}

						BossInList->data->spriteRect = BossInList->data->currentAnimation->GetCurrentFrame();
						switch (BossInList->data->bossType) {
						case BossType::VALION:
							if (BossInList->data->isSelected == true) {
								app->render->DrawTexture(BossInList->data->spriteTex, BossInList->data->position.x, BossInList->data->position.y, &BossInList->data->spriteRect, BossInList->data->zoom, false, { 255, 150, 0 });
							}
							else {
								app->render->DrawTexture(BossInList->data->spriteTex, BossInList->data->position.x, BossInList->data->position.y, &BossInList->data->spriteRect, BossInList->data->zoom, false);
							}
							break;
						case BossType::TRUCK:
							if (BossInList->data->isSelected == true) {
								app->render->DrawTexture(BossInList->data->spriteTex, BossInList->data->position.x - 150, BossInList->data->position.y , &BossInList->data->spriteRect, BossInList->data->zoom, false, { 255, 150, 0 });
							}
							else {
								app->render->DrawTexture(BossInList->data->spriteTex, BossInList->data->position.x - 150, BossInList->data->position.y, &BossInList->data->spriteRect, BossInList->data->zoom, false);
							}

							if (BossInList->data->stats->defenseBuffed) {
								app->render->DrawTexture(app->battle->shield, app->battle->entitiesInBattle[i]->position.x - 500, app->battle->entitiesInBattle[i]->position.y + 20);
							}

							break;
						default:
							if (BossInList->data->isSelected == true) {
								app->render->DrawTexture(BossInList->data->spriteTex, BossInList->data->position.x, BossInList->data->position.y - 100, &BossInList->data->spriteRect, BossInList->data->zoom, false, { 255, 150, 0 });
							}
							else {
								app->render->DrawTexture(BossInList->data->spriteTex, BossInList->data->position.x, BossInList->data->position.y - 100, &BossInList->data->spriteRect, BossInList->data->zoom, false);
							}
							break;
						}
					}
				}

				//SHIELDS IN BOSSES
				if (app->battle->entitiesInBattle[i]->stats->defenseBuffed == true) {
					switch (i) {
					//	//Player
					//case 0:
					//	app->render->DrawTexture(app->battle->shield, app->battle->entitiesInBattle[i]->position.x + app->battle->entitiesInBattle[i]->currentAnimation->GetCurrentFrame().w - 50, app->battle->entitiesInBattle[i]->position.y + 70);
					//	break;
					//	//Rayla
					//case 1:
					//	app->render->DrawTexture(app->battle->shield, app->battle->entitiesInBattle[i]->position.x + app->battle->entitiesInBattle[i]->currentAnimation->GetCurrentFrame().w - 140, app->battle->entitiesInBattle[i]->position.y + 20);
					//	break;
					//	//Valion
					//case 2:
					//	app->render->DrawTexture(app->battle->shield, app->battle->entitiesInBattle[i]->position.x + app->battle->entitiesInBattle[i]->currentAnimation->GetCurrentFrame().w + 90, app->battle->entitiesInBattle[i]->position.y + 70);
					//	break;
					//	//Dhion
					//case 3:
					//	app->render->DrawTexture(app->battle->shield, app->battle->entitiesInBattle[i]->position.x + app->battle->entitiesInBattle[i]->currentAnimation->GetCurrentFrame().w - 130, app->battle->entitiesInBattle[i]->position.y + 130);
					//	break;
					default:
						if (i != 0 && i != 1 && i != 2 && i != 3) {
							//app->render->DrawTexture(app->battle->shield, app->battle->entitiesInBattle[i]->position.x + app->battle->entitiesInBattle[i]->currentAnimation->GetCurrentFrame().w, app->battle->entitiesInBattle[i]->position.y);
						}
					break;
					}
				}

				//IF THEY ARE ALLIES
				ListItem<Character*>* CharacterInList;

				for (CharacterInList = partyListPtr->start; CharacterInList != NULL && ret == true; CharacterInList = CharacterInList->next)
				{
					if (app->battle->entitiesInBattle[i] == CharacterInList->data) {

						if (i == 0)
						{
							SDL_Rect rect = playerPtr->currentAnimation->GetCurrentFrame();

							switch (playerPtr->PlayerErection)
							{
							case 1:
								playerPtr->currentAnimation = &playerPtr->idleBattleM;
								app->render->DrawTexture(playerPtr->BattleMTex, playerPtr->position.x, playerPtr->position.y, &rect, 3, false);

								if (app->battle->battlePhase == BattlePhase::OUTCOME) {
									if (playerPtr->takesDamage == true) {
										playerPtr->currentAnimation = &playerPtr->hitM;
									}
								}

								if (playerPtr->isAlive == false) {
									playerPtr->currentAnimation = &playerPtr->dieM;
								}

								if (app->battle->actualTurnEntity == partyListPtr->At(0)->data) {
									switch (app->battle->battlePhase) {
									case BattlePhase::THINKING:
										playerPtr->currentAnimation = &playerPtr->idleBattleM;
										playerPtr->attackM.Reset();
										playerPtr->dieM.Reset();
										
										app->stages->playerPtr->runM.Reset();

										for (int i = 0; i < 8; i++) {
											if (app->battle->entitiesInBattle[i] != nullptr) {
												if (app->battle->entitiesInBattle[i]->isAlive == true)
													if (app->battle->entitiesInBattle[i]->takesDamage == false) {
														app->battle->entitiesInBattle[i]->hitAnim.Reset();
													}
											}
										}

										if (playerPtr->isAlive == true) {
											if (playerPtr->PlayerErection == 1) {
												if (playerPtr->takesDamage == false) {
													playerPtr->hitM.Reset();
												}
											}
											else if (playerPtr->PlayerErection == 2) {
												if (playerPtr->takesDamage == false) {
													playerPtr->hitF.Reset();
												}
											}
										}
										break;
									case BattlePhase::ATTACKING:
										playerPtr->currentAnimation = &playerPtr->attackM;

										if (fxbool == true) {
											fxbool = false;
											app->audio->PlayFx(hitfx2);
										}
										break;
									case BattlePhase::DEFENDING:
										playerPtr->currentAnimation = &playerPtr->protectM;
										if (fxbool == true) {
											fxbool = false;
											app->audio->PlayFx(shieldfx);
										}
										break;
									case BattlePhase::LOSE:

										if (fxbool == true) {
											fxbool = false;
											app->audio->PlayFx(chdiefx);
										}
										break;
									case BattlePhase::ESCAPING:

										if (fxbool == true) {
											fxbool = false;

										}
										playerPtr->currentAnimation = &playerPtr->runM;
										break;

									default:
										break;

									}
								}
								break;
							case 2:
								playerPtr->currentAnimation = &playerPtr->idleBattleF;
								app->render->DrawTexture(playerPtr->BattleFTex, playerPtr->position.x, playerPtr->position.y, &rect, 3, false);

								if (app->battle->battlePhase == BattlePhase::OUTCOME) {
									if (playerPtr->takesDamage == true) {
										playerPtr->currentAnimation = &playerPtr->hitM;
									}
								}

								if (playerPtr->isAlive == false) {
									playerPtr->currentAnimation = &playerPtr->dieF;
								}

								if (app->battle->actualTurnEntity == partyListPtr->At(0)->data) {
									switch (app->battle->battlePhase) {
									case BattlePhase::THINKING:
										playerPtr->currentAnimation = &playerPtr->idleBattleF;
										playerPtr->attackF.Reset();
										playerPtr->attackF2.Reset();
										playerPtr->attackChainF.Reset();
										playerPtr->dieF.Reset();
										playerPtr->hitF.Reset();
										playerPtr->runF.Reset();

										for (int i = 0; i < 8; i++) {
											if (app->battle->entitiesInBattle[i] != nullptr) {
												if (app->battle->entitiesInBattle[i]->isAlive == true)
													if (app->battle->entitiesInBattle[i]->takesDamage == false) {
														app->battle->entitiesInBattle[i]->hitAnim.Reset();
													}
											}
										}

										if (playerPtr->isAlive == true) {
											if (playerPtr->PlayerErection == 1) {
												if (playerPtr->takesDamage == false) {
													playerPtr->hitM.Reset();
												}
											}
											else if (playerPtr->PlayerErection == 2) {
												if (playerPtr->takesDamage == false) {
													playerPtr->hitF.Reset();
												}
											}
										}
										break;
									case BattlePhase::ATTACKING:
										if (pAnim == 1) {
											playerPtr->currentAnimation = &playerPtr->attackF;
										}
										if (pAnim == 2) {
											playerPtr->currentAnimation = &playerPtr->attackF2;
										}
										if (pAnim == 3) {
											playerPtr->currentAnimation = &playerPtr->attackChainF;
										}
										if (fxbool == true) {
											fxbool = false;
											app->audio->PlayFx(hitfx2);
										}
										break;
									case BattlePhase::DEFENDING:
										playerPtr->currentAnimation = &playerPtr->protectF;
										if (fxbool == true) {
											fxbool = false;
											app->audio->PlayFx(shieldfx);
										}
										break;
									case BattlePhase::LOSE:
										//playerPtr->currentAnimation = &playerPtr->dieF;
										if (fxbool == true) {
											fxbool = false;
											app->audio->PlayFx(chdiefx);
										}
										break;
									case BattlePhase::ESCAPING:

										if (fxbool == true) {
											fxbool = false;

										}
										playerPtr->currentAnimation = &playerPtr->runF;
										break;

									
									default:
										break;

									}
								}

								break;
							case 3:
								playerPtr->currentAnimation = &playerPtr->heliBattleIdle;
								app->render->DrawTexture(playerPtr->BattleHeliTex, playerPtr->position.x, playerPtr->position.y, &rect, 3, false);

								if (playerPtr->isAlive == false) {
									playerPtr->currentAnimation = &playerPtr->andThenHeliDies;
								}

								if (app->battle->actualTurnEntity == partyListPtr->At(0)->data) {
									switch (app->battle->battlePhase) {
									case BattlePhase::THINKING:
										playerPtr->currentAnimation = &playerPtr->heliBattleIdle;

										playerPtr->heliAttack.Reset();
										playerPtr->andThenHeliDies.Reset();

										for (int i = 0; i < 8; i++) {
											if (app->battle->entitiesInBattle[i] != nullptr) {
												if (app->battle->entitiesInBattle[i]->isAlive == true)
													if (app->battle->entitiesInBattle[i]->takesDamage == false) {
														app->battle->entitiesInBattle[i]->hitAnim.Reset();
													}
											}
										}

										if (playerPtr->isAlive == true) {
											if (playerPtr->PlayerErection == 1) {
												if (playerPtr->takesDamage == false) {
													playerPtr->hitM.Reset();
												}
											}
											else if (playerPtr->PlayerErection == 2) {
												if (playerPtr->takesDamage == false) {
													playerPtr->hitF.Reset();
												}
											}
										}
										
										break;
									case BattlePhase::ATTACKING:
										playerPtr->currentAnimation = &playerPtr->heliAttack;
										if (fxbool == true) {
											fxbool = false;
											app->audio->PlayFx(hitfx2);
										}
										break;
									case BattlePhase::DEFENDING:
										playerPtr->currentAnimation = &playerPtr->heliProtect;
										if (fxbool == true) {
											fxbool = false;
											app->audio->PlayFx(shieldfx);
										}
										break;
									case BattlePhase::LOSE:
										playerPtr->currentAnimation = &playerPtr->andThenHeliDies;
										if (fxbool == true) {
											fxbool = false;
											app->audio->PlayFx(chdiefx);
										}
										break;
									
									default:
										break;

									}
								}
								
								break;
							}
						}
						else {


							//CharacterInList->data->currentAnimation = &CharacterInList->data->battleAnim;
							CharacterInList->data->spriteRect = CharacterInList->data->currentAnimation->GetCurrentFrame();

							app->render->DrawTexture(CharacterInList->data->spriteTex, CharacterInList->data->position.x, CharacterInList->data->position.y, &CharacterInList->data->spriteRect, CharacterInList->data->zoom, false);

						
							if (CharacterInList->data->isAlive == false) {
								CharacterInList->data->currentAnimation = &CharacterInList->data->deathAnim;
							}


							if (app->battle->actualTurnEntity == CharacterInList->data) {
								switch (app->battle->battlePhase) {
								case BattlePhase::THINKING:
									CharacterInList->data->currentAnimation = &CharacterInList->data->idleBattle;
									CharacterInList->data->attackAnim1.Reset();
									CharacterInList->data->attackAnim2.Reset();
									CharacterInList->data->dieAnim.Reset();

									for (int i = 0; i < 8; i++) {
										if (app->battle->entitiesInBattle[i] != nullptr) {
											if (app->battle->entitiesInBattle[i]->isAlive == true)
												if (app->battle->entitiesInBattle[i]->takesDamage == false) {
													app->battle->entitiesInBattle[i]->hitAnim.Reset();
												}
										}
									}

									if (playerPtr->isAlive == true) {
										if (playerPtr->PlayerErection == 1) {
											if (playerPtr->takesDamage == false) {
												playerPtr->hitM.Reset();
											}
										}
										else if (playerPtr->PlayerErection == 2) {
											if (playerPtr->takesDamage == false) {
												playerPtr->hitF.Reset();
											}
										}
									}
									break;
								case BattlePhase::ATTACKING:
									if (vAnim == 1) {
										CharacterInList->data->currentAnimation = &CharacterInList->data->attackAnim1;
									}
									if (vAnim == 2) {
										CharacterInList->data->currentAnimation = &CharacterInList->data->attackAnim2;
									}

									if (fxbool == true) {
										fxbool = false;
										app->audio->PlayFx(hitfx2);
									}
									break;
								case BattlePhase::DEFENDING:
									CharacterInList->data->currentAnimation = &CharacterInList->data->protectedAnim;
									if (fxbool == true) {
										fxbool = false;
										app->audio->PlayFx(shieldfx);
									}

									break;
								case BattlePhase::LOSE:
									//CharacterInList->data->currentAnimation = &CharacterInList->data->deathAnim;
									if (fxbool == true) {
										fxbool = false;
										app->audio->PlayFx(chdiefx);
									}
									break;
								case BattlePhase::ESCAPING:
									
									if (fxbool == true) {
										fxbool = false;
										
									}
									CharacterInList->data->currentAnimation = &CharacterInList->data->runAnim;
									break;
									
								default:
									//CharacterInList->data->currentAnimation = &CharacterInList->data->idleBattle;
									break;

								}
							}
							else if (app->battle->battlePhase == BattlePhase::OUTCOME) {
								if (CharacterInList->data->takesDamage == true) {
									CharacterInList->data->currentAnimation = &CharacterInList->data->hitAnim;
								}
							}
							else{
								CharacterInList->data->currentAnimation = &CharacterInList->data->idleBattle;
								CharacterInList->data->attackAnim1.Reset();
								CharacterInList->data->attackAnim2.Reset();
								CharacterInList->data->dieAnim.Reset();
								CharacterInList->data->hitAnim.Reset();
								CharacterInList->data->runAnim.Reset();
							}

							if (CharacterInList->data->isAlive == false) {
								CharacterInList->data->currentAnimation = &CharacterInList->data->deathAnim;
							}

						}

						//SHIELDS IN ALLIES
						if (app->battle->entitiesInBattle[i]->stats->defenseBuffed == true) {
							switch (i) {

								//Player
							case 0:
								app->render->DrawTexture(app->battle->shield, app->battle->entitiesInBattle[i]->position.x + app->battle->entitiesInBattle[i]->currentAnimation->GetCurrentFrame().w - 50, app->battle->entitiesInBattle[i]->position.y + 70);
								break;
								//Rayla
							case 1:
								app->render->DrawTexture(app->battle->shield, app->battle->entitiesInBattle[i]->position.x + app->battle->entitiesInBattle[i]->currentAnimation->GetCurrentFrame().w - 140, app->battle->entitiesInBattle[i]->position.y + 20);
								break;
								//Valion
							case 2:
								app->render->DrawTexture(app->battle->shield, app->battle->entitiesInBattle[i]->position.x + app->battle->entitiesInBattle[i]->currentAnimation->GetCurrentFrame().w + 90, app->battle->entitiesInBattle[i]->position.y + 70);
								break;
								//Dhion
							case 3:
								app->render->DrawTexture(app->battle->shield, app->battle->entitiesInBattle[i]->position.x + app->battle->entitiesInBattle[i]->currentAnimation->GetCurrentFrame().w - 130, app->battle->entitiesInBattle[i]->position.y + 130);
								break;
							default:
								app->render->DrawTexture(app->battle->shield, app->battle->entitiesInBattle[i]->position.x + app->battle->entitiesInBattle[i]->currentAnimation->GetCurrentFrame().w, app->battle->entitiesInBattle[i]->position.y);
								break;
							}
						}

					}
					/*if (app->battle->entitiesInBattle[i]->isAlive == false) {
						for(int i =)
						if(app->battle->entitiesInBattle[i]==)
						CharacterInList->data->currentAnimation = &CharacterInList->data->deathAnim;
						app->battle->entitiesInBattle[i]->currentAnimation = &app->battle->entitiesInBattle[i]->dieF;
					}*/


				}

			}

			switch (i) {
			case 0:
				i = 2;
				break;
			case 1:
				i = 1;
				break;
			case 2:
				i = 3;
				break;
			case 3:
				i = 0;
				break;
			}
		}

		//if (app->battle->battlePhase == BattlePhase::OUTCOME) {
		//}

		switch (app->battle->skill) {
		case 110:
			app->render->DrawTexture(app->battle->FlechaS_EspadaS_EscudoS,  app->win->GetWidth() / 2 / 2 - app->battle->EscudoS_a.GetCurrentFrame().w / 2, app->win->GetHeight() / 2 / 2 - app->battle->EscudoS_a.GetCurrentFrame().h/2, &app->battle->EscudoS_a.GetCurrentFrame(),3,false);
			break;
		case 111:
			app->render->DrawTexture(app->battle->FlechaS_EspadaS_EscudoS, 100, 100, &app->battle->EspadaS_a.GetCurrentFrame(), 3, false);
			break;
		case 112:
			app->render->DrawTexture(app->battle->AquaE, 100, 100, &app->battle->AquaE_a.GetCurrentFrame(), 3, false);
			break;

		case 120:
			app->render->DrawTexture(app->battle->Pedrada, 100, 100, &app->battle->Pedrada_a.GetCurrentFrame(), 3, false);
			break;
		case 121:
			app->render->DrawTexture(app->battle->Cataclismo, 100, 100, &app->battle->Cataclismo_a.GetCurrentFrame(), 3, false);
			break;
		case 122:
			app->render->DrawTexture(app->battle->FlechaT_Ciervo, 100, 100, &app->battle->Ciervo_a.GetCurrentFrame(), 3, false);
			break;

		case 130:
			app->render->DrawTexture(app->battle->FlechaT_Ciervo, 100, 100, &app->battle->FlechaT_a.GetCurrentFrame(), 3, false);
			break;
		case 131:
			app->render->DrawTexture(app->battle->FlechaAcido, 100, 100, &app->battle->FlechaAcido_a.GetCurrentFrame(), 3, false);
			break;
		case 132:
			app->render->DrawTexture(app->battle->FlechaS_EspadaS_EscudoS, 100, 100, &app->battle->FlechaS_a.GetCurrentFrame(), 3, false);
			break;

		case 140:
			app->render->DrawTexture(app->battle->TripleL_Juicio, 100, 100, &app->battle->Juicio_a.GetCurrentFrame(), 3, false);
			break;
		case 141:
			app->render->DrawTexture(app->battle->HalconElectro, 100, 100, &app->battle->HalconElectro_a.GetCurrentFrame(), 3, false);
			break;
		case 142:
			app->render->DrawTexture(app->battle->TripleL_Juicio, 100, 100, &app->battle->TripleL_a.GetCurrentFrame(), 3, false);
			break;

		default:
				app->battle->EscudoS_a.Reset();
				app->battle->EspadaS_a.Reset();
				app->battle->AquaE_a.Reset();

				app->battle->Pedrada_a.Reset();
				app->battle->Cataclismo_a.Reset();
				app->battle->Ciervo_a.Reset();

				app->battle->FlechaT_a.Reset();
				app->battle->FlechaAcido_a.Reset();
				app->battle->FlechaS_a.Reset();

				app->battle->Juicio_a.Reset();
				app->battle->HalconElectro_a.Reset();
				app->battle->TripleL_a.Reset();
			break;
		}


		//switch (app->battle->CurrentEnemyType) {
		//case EnemyInBattleType::NORMAL:
		//	app->battle->normalEnemyInBattle->currentAnimation = &app->battle->normalEnemyInBattle->battleAnim;
		//	SDL_Rect rect = app->battle->normalEnemyInBattle->currentAnimation->GetCurrentFrame();
		//	app->render->DrawTexture(app->battle->normalEnemyInBattle->spriteTex, 500, 100, &rect);
		//	break;

		//default:
		//	break;
		//}
	}

	// Debug DRAW Pathfinding
	if (app->collisions->debug) {
		if (normalEnemyListPtr != nullptr) {
			ListItem<NormalEnemy*>* NormalEnemyInList;
			NormalEnemyInList = normalEnemyListPtr->start;
			for (NormalEnemyInList = normalEnemyListPtr->start; NormalEnemyInList != NULL; NormalEnemyInList = NormalEnemyInList->next)
			{
				if (NormalEnemyInList->data->activeOnStage == app->stages->actualStage && playerPtr != nullptr) {
					// Draw
					if (NormalEnemyInList->data->chasePlayer) {
						const DynArray<iPoint>* path = app->pathfinder->GetLastPath();

						for (uint i = 0; i < path->Count(); ++i)
						{
							iPoint pos = app->map->MapToWorld(path->At(i)->x, path->At(i)->y);
							app->render->DrawTexture(app->pathfinder->pathTexture, pos.x, pos.y);
						}

						iPoint originScreen = app->map->MapToWorld(NormalEnemyInList->data->position.x, NormalEnemyInList->data->position.y);
						app->render->DrawTexture(app->pathfinder->pathOriginTexture, originScreen.x, originScreen.y);
					}
				}
			}
		}
	}
	switch (actualStage)
	{
	case StageIndex::NONE:

		break;
	case StageIndex::TOWN:
		if (app->input->GetKey(SDL_SCANCODE_M) == KEY_REPEAT) {

			app->render->DrawTexture(app->scene->mini_map, xm + 150, ym + 50);
		}
		break;
	case StageIndex::DOJO:
		if (app->input->GetKey(SDL_SCANCODE_M) == KEY_REPEAT) {

			app->render->DrawTexture(app->scene->mini_map, xm + 150, ym + 50);
		}
		break;
	case StageIndex::SHOP:
		if (app->input->GetKey(SDL_SCANCODE_M) == KEY_REPEAT) {

			app->render->DrawTexture(app->scene->mini_map, xm + 150, ym + 50);
		}
		break;
	case StageIndex::SHOPSUB:
		if (app->input->GetKey(SDL_SCANCODE_M) == KEY_REPEAT) {

			app->render->DrawTexture(app->scene->mini_map, xm + 150, ym + 50);
		}
		break;
	case StageIndex::TAVERN:
		if (app->input->GetKey(SDL_SCANCODE_M) == KEY_REPEAT) {

			app->render->DrawTexture(app->scene->mini_map, xm + 150, ym + 50);
		}
		break;
	}
	return ret;
}

void Stages::ChangeStage(StageIndex newStage) {
	introductionFase = 0;

	if (app->scene->delayForCrashUwU <= 0) {
		app->scene->stageSwap->data = newStage;
	}

	// Door sfx
	if (actualStage != StageIndex::NONE && actualStage != StageIndex::INTRODUCTION && newStage != StageIndex::WIN && newStage != StageIndex::LOSE && newStage != StageIndex::PROLOGUE) {
		app->audio->PlayFx(doorFx);
	}

	// Reset map.cpp
	if (app->map->isEnabled() == true) {
		app->map->Disable();
		app->map->Enable();
		app->camera->FreeLimits();
	}

	if (actualStage == StageIndex::PROLOGUE) {
		// Clean prologue memory
		for(ListItem<Car*>* c = cars.start; c != NULL; c= c->next){
			app->tex->UnLoad(c->data->sprite);
			c->data->collider->pendingToDelete = true;
		}
		cars.clear();
		app->tex->UnLoad(TLVertical.sprite);
		app->tex->UnLoad(TLVertical.lightSprite);
		app->tex->UnLoad(TLPeIzq.sprite);
		app->tex->UnLoad(TLPeIzq.lightSprite);
		app->tex->UnLoad(TLPeDer.sprite);
		app->tex->UnLoad(TLPeDer.lightSprite);
		app->tex->UnLoad(TLIzq.sprite);
		app->tex->UnLoad(TLIzq.lightSprite);
		app->tex->UnLoad(TLDer.sprite);
		app->tex->UnLoad(TLDer.lightSprite);
	}

	if (actualStage != StageIndex::TOWN) {
		app->particlesM->CleanUp();
	}

	switch (newStage)
	{
	case StageIndex::NONE:

		playerPtr = nullptr;
		delete playerPtr;

		npcListPtr = nullptr;
		delete npcListPtr;

		normalEnemyListPtr = nullptr;
		delete normalEnemyListPtr;

		break;

	case StageIndex::TOWN:

		// Load Map
		if (app->map->isEnabled() == true) {

			app->map->Load("initial_town_map.tmx");

			playerPtr->position = playerPtr->townPos;
			playerPtr->canMove = true;

			app->camera->OnTarget();
			app->camera->SetLimits(640, 350, 4490, 4200);
			LOG("Loading Town map");

			app->particlesM->SmokeTex = app->tex->Load("Assets/particles/smoke_particles.png");
			app->particlesM->FireTex = app->tex->Load("Assets/particles/flames_particles.png");
			app->particlesM->ChickenTex = app->tex->Load("Assets/particles/chicken_particles.png");
			app->particlesM->BirdTex = app->tex->Load("Assets/particles/bird_particles.png");

			app->audio->PlayMusic("Assets/audio/music/music_town.ogg");
		}

		break;
	case StageIndex::DOJO:

		// Load Map
		if (app->map->isEnabled() == true) {
			app->map->Load("initial_town_dojo.tmx");

			playerPtr->position = { 415, 270 };
			app->camera->OnTarget();

			LOG("Loading Dojo map");

			app->audio->PlayMusic("Assets/audio/music/music_dojo.ogg");
		}

		break;
	case StageIndex::SHOP:

		// Load Map
		if (app->map->isEnabled() == true) {
			app->map->Load("initial_town_shop.tmx");

			if (playerPtr->shopPosOn == false) {
				playerPtr->position = { 255, 425 };
			}
			else {
				playerPtr->position = playerPtr->shopPos;
				playerPtr->shopPosOn = false;
			}
			app->camera->OnTarget();

			LOG("Loading Shop map");

			if (actualStage != StageIndex::SHOPSUB) {
				app->audio->PlayMusic("Assets/audio/music/music_shop.ogg");
			}
		}

		break;
	case StageIndex::SHOPSUB:

		// Load Map
		if (app->map->isEnabled() == true) {
			app->map->Load("initial_town_under_shop.tmx");

			playerPtr->position = { 255, 80 };
			app->camera->OnTarget();

			LOG("Loading Shop lower floor map");

			if (actualStage != StageIndex::SHOP) {
				app->audio->PlayMusic("Assets/audio/music/music_shop.ogg");
			}
			app->audio->ChangeVolume(app->audio->vol / 3);
		}

		break;
	case StageIndex::TAVERN:

		// Load Map
		if (app->map->isEnabled() == true) {
			app->map->Load("initial_town_tavern.tmx");

			playerPtr->position = { 240, 550 };
			app->camera->OnTarget();

			LOG("Loading Tavern map");

			app->audio->PlayMusic("Assets/audio/music/music_tavern.ogg");
		}

		break;
	case StageIndex::INTRODUCTION:

		LOG("Introduction");

		app->audio->PlayMusic("Assets/audio/music/music_intro.ogg");

		break;
	case StageIndex::WIN:

		LOG("Win Screen");

		app->audio->PlayMusic("Assets/audio/music/music_tutorial.ogg");

		break;
	case StageIndex::LOSE:

		LOG("Lose Screen");
		app->audio->PlayFx(loseFx);
		app->audio->PlayMusic("Assets/audio/music/music_die.ogg");

		break;
	case StageIndex::TOWER_0:

		// Load Map
		if (app->map->isEnabled() == true) {
			app->map->Load("tower_B.tmx");

			playerPtr->position = playerPtr->tower0Pos;
			app->camera->OnTarget();
			app->camera->FreeLimits();
			LOG("Loading Tower map");
			app->audio->PlayMusic("Assets/audio/music/music_floors_top.ogg");
			//app->audio->PlayMusic("Assets/audio/music/");
		}

		break;

	case StageIndex::TOWER_1:

		// Load Map
		if (app->map->isEnabled() == true) {
			app->map->Load("tower_floor_1.tmx");

			playerPtr->position = playerPtr->tower1Pos;
			app->camera->OnTarget();
			app->camera->FreeLimits();
			LOG("Loading Floor 1 map");
			app->audio->PlayMusic("Assets/audio/music/music_floors_top.ogg");
			//app->audio->PlayMusic("Assets/audio/music/");
		}

		break;
	case StageIndex::TOWER_2:

		// Load Map
		if (app->map->isEnabled() == true) {
			app->map->Load("tower_floor_2.tmx");

			playerPtr->position = playerPtr->tower2Pos;
			app->camera->OnTarget();
			app->camera->FreeLimits();

			LOG("Loading Floor 2 map");
			app->audio->PlayMusic("Assets/audio/music/music_floors_top.ogg");
			//app->audio->PlayMusic("Assets/audio/music/");
		}

		break;
	case StageIndex::TOWER_FINAL_BOSS:

		// Load Map
		if (app->map->isEnabled() == true) {
			app->map->Load("tower_boss_1.tmx");

			playerPtr->position = playerPtr->tower3Pos;
			app->camera->OnTarget();
			app->camera->FreeLimits();
			LOG("Loading Floor 3 map");
			app->audio->PlayMusic("Assets/audio/music/music_battle_boss.ogg");
			//app->audio->PlayMusic("Assets/audio/music/");
		}

		break;
	case StageIndex::TOWER_3:

		// Load Map
		if (app->map->isEnabled() == true) {
			app->map->Load("tower_floor_5.tmx");

			playerPtr->position = playerPtr->tower4Pos;
			app->camera->OnTarget();
			app->camera->FreeLimits();
			LOG("Loading Floor 4 map");
			app->audio->PlayMusic("Assets/audio/music/music_floors_top.ogg");
			//app->audio->PlayMusic("Assets/audio/music/");
		}
		break;
	case StageIndex::TOWER_BOSS_1:

		// Load Map
		if (app->map->isEnabled() == true) {
			app->map->Load("tower_boss_2.tmx");

			playerPtr->position = playerPtr->tower3Pos;
			app->camera->OnTarget();
			app->camera->FreeLimits();
			LOG("Loading Boss Floor 1 map");
			app->audio->PlayMusic("Assets/audio/music/music_floors_mid.ogg");
			//app->audio->PlayMusic("Assets/audio/music/");
		}

		break;
	case StageIndex::TOWER_BOSS_2:

		// Load Map
		if (app->map->isEnabled() == true) {
			app->map->Load("tower_boss_2.tmx");

			playerPtr->position = playerPtr->tower3Pos;
			app->camera->OnTarget();
			app->camera->FreeLimits();
			LOG("Loading Boss Floor 2 map");
			app->audio->PlayMusic("Assets/audio/music/music_floors_mid.ogg");
			//app->audio->PlayMusic("Assets/audio/music/");
		}

	break; case StageIndex::TOWER_BOSS_3:

		// Load Map
		if (app->map->isEnabled() == true) {
			app->map->Load("tower_boss_2.tmx");

			playerPtr->position = playerPtr->tower3Pos;
			app->camera->OnTarget();
			app->camera->FreeLimits();
			LOG("Loading Boss Floor 3 map");
			app->audio->PlayMusic("Assets/audio/music/music_floors_mid.ogg");
			//app->audio->PlayMusic("Assets/audio/music/");
		}

		break;
	case StageIndex::PROLOGUE:
		if (app->map->isEnabled() == true) {

			LOG("Loading Prologue map");

			app->map->Load("prologue.tmx");

			// Recolocar al player
			playerPtr->position ={ 10 * TILE_SIZE, 15 * TILE_SIZE };

			// Camera
			app->camera->OnTarget();
			//app->camera->SetLimits(0, 0, 3152, 736);

			// Audio
			app->audio->PlayMusic("Assets/audio/music/music_city.ogg");

			fxCar1 = app->audio->LoadFx("Assets/audio/sfx/fx_car1.wav");
			fxCar2 = app->audio->LoadFx("Assets/audio/sfx/fx_car2.wav");
			fxCar3 = app->audio->LoadFx("Assets/audio/sfx/fx_car3.wav");
			fxCar4 = app->audio->LoadFx("Assets/audio/sfx/fx_car4.wav");

			// Load Semáforos
			{
				TLVertical.state = TLState::STOP;
				TLVertical.sprite = app->tex->Load("Assets/sprites/trafficLights/vertical.png");
				TLVertical.lightSprite = app->tex->Load("Assets/sprites/trafficLights/luces.png");
				TLVertical.animStop.PushBack({ 0, 0, 5, 5 });
				TLVertical.animPass.PushBack({ 6, 0, 5, 5 });
				TLVertical.animCaution.PushBack({ 12, 0, 5, 5 });
				TLVertical.position = { 57 * TILE_SIZE, 11 * TILE_SIZE };

				TLPeIzq.state = TLState::STOP;
				TLPeIzq.sprite = app->tex->Load("Assets/sprites/trafficLights/peaton.png");
				TLPeIzq.lightSprite = app->tex->Load("Assets/sprites/trafficLights/luces.png");
				TLPeIzq.animStop.PushBack({ 0, 6, 7, 10 });
				TLPeIzq.animPass.PushBack({ 8, 6, 7, 9 });
				TLPeIzq.animCaution.PushBack({ 16, 6, 7, 9 });
				TLPeIzq.position = { 51 * TILE_SIZE, 11 * TILE_SIZE };

				TLPeDer.state = TLState::STOP;
				TLPeDer.sprite = app->tex->Load("Assets/sprites/trafficLights/peaton.png");
				TLPeDer.lightSprite = app->tex->Load("Assets/sprites/trafficLights/luces.png");
				TLPeDer.animStop.PushBack({ 0, 6, 7, 10 });
				TLPeDer.animPass.PushBack({ 8, 6, 7, 9 });
				TLPeDer.animCaution.PushBack({ 16, 6, 7, 9 });
				TLPeDer.position = { 62 * TILE_SIZE, 11 * TILE_SIZE };

				TLIzq.state = TLState::PASS;
				TLIzq.sprite = app->tex->Load("Assets/sprites/trafficLights/horizontal_izquierda.png");
				TLIzq.lightSprite = app->tex->Load("Assets/sprites/trafficLights/luces.png");
				TLIzq.animStop.PushBack({ 0, 0, 5, 5 });
				TLIzq.animPass.PushBack({ 6, 0, 5, 5 });
				TLIzq.animCaution.PushBack({ 12, 0, 5, 5 });
				TLIzq.position = { 51 * TILE_SIZE, 19 * TILE_SIZE };
				TLIzq.hitbox.x = TLIzq.position.x - 32;
				TLIzq.hitbox.y = TLIzq.position.y - 100;
				TLIzq.hitbox.w = 64;
				TLIzq.hitbox.h = 200;

				TLDer.state = TLState::PASS;
				TLDer.sprite = app->tex->Load("Assets/sprites/trafficLights/horizontal_derecha.png");
				TLDer.lightSprite = app->tex->Load("Assets/sprites/trafficLights/luces.png");
				TLDer.animStop.PushBack({ 0, 0, 5, 5 });
				TLDer.animPass.PushBack({ 6, 0, 5, 5 });
				TLDer.animCaution.PushBack({ 12, 0, 5, 5 });
				TLDer.position = { 67 * TILE_SIZE, 11 * TILE_SIZE };
				TLDer.hitbox.x = TLDer.position.x;
				TLDer.hitbox.y = TLDer.position.y;
				TLDer.hitbox.w = 64;
				TLDer.hitbox.h = 200;
			}

			changeTL = TRAFFIC_LIGHT_TIME;
			tlOrder = TLOrder::HORIZONTAL;
		}
		break;
	default:

		break;
	}

	if (actualStage == StageIndex::SHOPSUB && newStage != StageIndex::SHOPSUB) {
		app->audio->ChangeVolume(app->audio->vol * 3);
	}
	// Change actual stage to newStage at the end
	actualStage = newStage;
}

// Called before quitting
bool Stages::CleanUp()
{
	playerPtr = nullptr;
	delete playerPtr;

	npcListPtr = nullptr;
	delete npcListPtr;

	normalEnemyListPtr = nullptr;
	delete normalEnemyListPtr;

	return true;
}

void Stages::TrafficLightSystem() {
	if (changeTL <= 0) {
		// === Cambiar ciclo semaforos ===

		// Reiniciar Contadores
		changeTL = TRAFFIC_LIGHT_TIME;
		cautionTL = TRAFFIC_LIGHT_TIME / 5;

		bool tlChanged = false;

		// --- Prio Horizontal --- 
		if (tlOrder == TLOrder::UNGAUNGAS) {
			TLPeDer.state = TLState::CAUTION;
			TLPeIzq.state = TLState::CAUTION;

			tlOrder = TLOrder::HORIZONTAL;
			tlChanged = true;
		}

		// --- Prio Peatones --- 
		if (tlOrder == TLOrder::VERTICAL && tlChanged == false) {
			TLVertical.state = TLState::CAUTION;

			tlOrder = TLOrder::UNGAUNGAS;
			tlChanged = true;
		}

		// --- Prio Vertical --- 
		if (tlOrder == TLOrder::HORIZONTAL && tlChanged == false) {
			TLDer.state = TLState::CAUTION;
			TLIzq.state = TLState::CAUTION;

			tlOrder = TLOrder::VERTICAL;
		}
	}
	else {
		// Se pasa un tiempo en ambar hasta q cambia a rojo y cambia el ciclo
		if (cautionTL <= 0) {

			if (TLDer.state == TLState::CAUTION && TLIzq.state == TLState::CAUTION) {		// Prio Vertical
				TLDer.state = TLState::STOP;
				TLIzq.state = TLState::STOP;

				TLVertical.state = TLState::PASS;
			}
			if (TLVertical.state == TLState::CAUTION) {										// Prio Peatones
				TLVertical.state = TLState::STOP;

				TLPeDer.state = TLState::PASS;
				TLPeIzq.state = TLState::PASS;
			}
			if (TLPeDer.state == TLState::CAUTION && TLPeIzq.state == TLState::CAUTION) {	// Prio Horizontal
				TLPeDer.state = TLState::STOP;
				TLPeIzq.state = TLState::STOP;

				TLDer.state = TLState::PASS;
				TLIzq.state = TLState::PASS;
			}

			// El contador del semaforo empieza en cuanto acaba el contador del ambar
			changeTL--;
		}
		else {
			cautionTL--;
		}
	}

	// Imprimir semaforos
	app->render->DrawTexture(TLVertical.sprite, TLVertical.position.x, TLVertical.position.y);
	app->render->DrawTexture(TLDer.sprite, TLDer.position.x, TLDer.position.y);
	app->render->DrawTexture(TLIzq.sprite, TLIzq.position.x, TLIzq.position.y);
	app->render->DrawTexture(TLPeDer.sprite, TLPeDer.position.x, TLPeDer.position.y);
	app->render->DrawTexture(TLPeIzq.sprite, TLPeIzq.position.x, TLPeIzq.position.y);
	app->render->DrawTexture(TLPeDer.sprite, TLPeDer.position.x + 5 * TILE_SIZE, TLPeDer.position.y + 8 * TILE_SIZE);
	app->render->DrawTexture(TLPeIzq.sprite, TLPeIzq.position.x + 5 * TILE_SIZE, TLPeIzq.position.y + 8 * TILE_SIZE);

	// Hitboxes
	if (app->collisions->debug) {
		app->render->DrawRectangle(TLDer.hitbox, 0, 0, 255, 100);
		app->render->DrawRectangle(TLIzq.hitbox, 0, 0, 255, 100);
	}

	// Imprimir luces
	{
		TrafficLight semaforo = TLVertical;

		switch (semaforo.state)
		{
		case TLState::CAUTION:
			app->render->DrawTexture(semaforo.lightSprite, semaforo.position.x + 47, semaforo.position.y + 5, &semaforo.animCaution.GetCurrentFrame());
			break;
		case TLState::PASS:
			app->render->DrawTexture(semaforo.lightSprite, semaforo.position.x + 39, semaforo.position.y + 5, &semaforo.animPass.GetCurrentFrame());
			break;
		case TLState::STOP:
			app->render->DrawTexture(semaforo.lightSprite, semaforo.position.x + 55, semaforo.position.y + 5, &semaforo.animStop.GetCurrentFrame());
			break;
		}

		semaforo = TLDer;

		switch (semaforo.state)
		{
		case TLState::CAUTION:
			app->render->DrawTexture(semaforo.lightSprite, semaforo.position.x + 15, semaforo.position.y + 20, &semaforo.animCaution.GetCurrentFrame());
			break;
		case TLState::PASS:
			app->render->DrawTexture(semaforo.lightSprite, semaforo.position.x + 15, semaforo.position.y + 26, &semaforo.animPass.GetCurrentFrame());
			break;
		case TLState::STOP:
			app->render->DrawTexture(semaforo.lightSprite, semaforo.position.x + 15, semaforo.position.y + 14, &semaforo.animStop.GetCurrentFrame());
			break;
		}
		semaforo = TLIzq;

		switch (semaforo.state)
		{
		case TLState::CAUTION:
			app->render->DrawTexture(semaforo.lightSprite, semaforo.position.x + 9, semaforo.position.y + 20, &semaforo.animCaution.GetCurrentFrame());
			break;
		case TLState::PASS:
			app->render->DrawTexture(semaforo.lightSprite, semaforo.position.x + 9, semaforo.position.y + 26, &semaforo.animPass.GetCurrentFrame());
			break;
		case TLState::STOP:
			app->render->DrawTexture(semaforo.lightSprite, semaforo.position.x + 9, semaforo.position.y + 14, &semaforo.animStop.GetCurrentFrame());
			break;
		}

		semaforo = TLPeDer;

		switch (semaforo.state)
		{
		case TLState::CAUTION:
			app->render->DrawTexture(semaforo.lightSprite, semaforo.position.x + 13, semaforo.position.y + 20, &semaforo.animCaution.GetCurrentFrame());

			app->render->DrawTexture(semaforo.lightSprite, semaforo.position.x + 13 + 5 * TILE_SIZE, semaforo.position.y + 20 + 8 * TILE_SIZE, &semaforo.animCaution.GetCurrentFrame());
			break;
		case TLState::PASS:
			app->render->DrawTexture(semaforo.lightSprite, semaforo.position.x + 13, semaforo.position.y + 20, &semaforo.animPass.GetCurrentFrame());

			app->render->DrawTexture(semaforo.lightSprite, semaforo.position.x + 13 + 5 * TILE_SIZE, semaforo.position.y + 20 + 8 * TILE_SIZE, &semaforo.animPass.GetCurrentFrame());
			break;
		case TLState::STOP:
			app->render->DrawTexture(semaforo.lightSprite, semaforo.position.x + 13, semaforo.position.y + 8, &semaforo.animStop.GetCurrentFrame());

			app->render->DrawTexture(semaforo.lightSprite, semaforo.position.x + 13 + 5 * TILE_SIZE, semaforo.position.y + 20 + 8 * TILE_SIZE, &semaforo.animStop.GetCurrentFrame());
			break;
		}
		semaforo = TLPeIzq;

		switch (semaforo.state)
		{
		case TLState::CAUTION:
			app->render->DrawTexture(semaforo.lightSprite, semaforo.position.x + 13, semaforo.position.y + 20, &semaforo.animCaution.GetCurrentFrame());

			app->render->DrawTexture(semaforo.lightSprite, semaforo.position.x + 13 + 5 * TILE_SIZE, semaforo.position.y + 20 + 8 * TILE_SIZE, &semaforo.animCaution.GetCurrentFrame());
			break;
		case TLState::PASS:
			app->render->DrawTexture(semaforo.lightSprite, semaforo.position.x + 13, semaforo.position.y + 20, &semaforo.animPass.GetCurrentFrame());

			app->render->DrawTexture(semaforo.lightSprite, semaforo.position.x + 13 + 5 * TILE_SIZE, semaforo.position.y + 20 + 8 * TILE_SIZE, &semaforo.animPass.GetCurrentFrame());
			break;
		case TLState::STOP:
			app->render->DrawTexture(semaforo.lightSprite, semaforo.position.x + 13, semaforo.position.y + 8, &semaforo.animStop.GetCurrentFrame());

			app->render->DrawTexture(semaforo.lightSprite, semaforo.position.x + 13 + 5 * TILE_SIZE, semaforo.position.y + 20 + 8 * TILE_SIZE, &semaforo.animStop.GetCurrentFrame());
			break;
		}
	}
}

void Stages::CarManagement() {

	// Car generator
	if (randomCarCount <= 0)
	{
		randomCarCount = rand() % 300 + 60;
		int direction = rand() % 2;

		// Create new Car
		if (direction == 1) {
			Car* randomCar = new Car(true, { -2 * TILE_SIZE, 18 * TILE_SIZE });

			int color = rand() % 5;

			switch (color) {
			case 0:
				randomCar->carType = &carBlueR;
				break;
			case 1:
				randomCar->carType = &carGreenR;
				break;
			case 2:
				randomCar->carType = &carGreyR;
				break;
			case 3:
				randomCar->carType = &carRedR;
				break;
			case 4:
				randomCar->carType = &carPinkR;
				break;
			}

			randomCar->hitbox.x = randomCar->position.x;
			randomCar->hitbox.y = randomCar->position.y;
			randomCar->hitbox.w = 64 * 2;
			randomCar->hitbox.h = 32 * 2;

			randomCar->collider = app->collisions->AddCollider(randomCar->hitbox, Collider::Type::WALL);

			LOG("Car created circulating to east");
			cars.add(randomCar);

			randomCar = nullptr;
			delete randomCar;

		}
		else {
			Car* randomCar = new Car(false, { 101 * TILE_SIZE, 15 * TILE_SIZE });

			int color = rand() % 5;

			switch (color) {
			case 0:
				randomCar->carType = &carBlueL;
				break;
			case 1:
				randomCar->carType = &carGreenL;
				break;
			case 2:
				randomCar->carType = &carGreyL;
				break;
			case 3:
				randomCar->carType = &carRedL;
				break;
			case 4:
				randomCar->carType = &carPinkL;
				break;
			}

			randomCar->hitbox.x = randomCar->position.x;
			randomCar->hitbox.y = randomCar->position.y;
			randomCar->hitbox.w = 64 * 2;
			randomCar->hitbox.h = 32 * 2;

			randomCar->collider = app->collisions->AddCollider(randomCar->hitbox, Collider::Type::WALL);

			LOG("Car created circulating to weast");
			cars.add(randomCar);

			randomCar = nullptr;
			delete randomCar;
		}
	}
	else {
		randomCarCount--;
	}

	// Car management
	for (ListItem<Car*>* c = cars.start; c != nullptr; c = c->next) {

		// === Move ===
		if (c->data->speed < c->data->maxSpeed) {
			c->data->speed += c->data->acceleration;
		}

		c->data->position.x += c->data->speed * c->data->direction;
		c->data->hitbox.x = c->data->position.x;
		c->data->hitbox.y = c->data->position.y;
		c->data->collider->SetPos(c->data->position.x, c->data->position.y);

		// === Collisions ===

		int colliderFix = 64;

		// --- Collision with other cars ---
		for (ListItem<Car*>* c2 = cars.start; c2 != nullptr; c2 = c2->next) {

			// Cant move Left
			if (c2->data->hitbox.x + c2->data->hitbox.w > c->data->hitbox.x &&
				c2->data->hitbox.x + c2->data->hitbox.w < c->data->hitbox.x + c->data->hitbox.w &&
				c->data->hitbox.y < c2->data->hitbox.y + c2->data->hitbox.h &&
				c->data->hitbox.y + c->data->hitbox.h > c2->data->hitbox.y)
			{
				c->data->position.x = c2->data->hitbox.x + c2->data->hitbox.w;
				c->data->speed = 0;
			}

			// Cant move Right
			if (c2->data->hitbox.x > c->data->hitbox.x &&
				c2->data->hitbox.x < c->data->hitbox.x + c->data->hitbox.w &&
				c->data->hitbox.y < c2->data->hitbox.y + c2->data->hitbox.h &&
				c->data->hitbox.y + c2->data->hitbox.h > c2->data->hitbox.y)
			{
				c->data->position.x = c2->data->hitbox.x - c2->data->hitbox.w;
				c->data->speed = 0;
			}
		}

		// --- Collision with TL ---
		{
			if (c->data->direction == -1) {
				// Stop at TL going to weast
				if (TLDer.hitbox.x + TLDer.hitbox.w > c->data->hitbox.x &&
					TLDer.hitbox.x + TLDer.hitbox.w < c->data->hitbox.x + c->data->hitbox.w &&
					c->data->hitbox.y < TLDer.hitbox.y + TLDer.hitbox.h &&
					c->data->hitbox.y + c->data->hitbox.h > TLDer.hitbox.y && TLDer.state == TLState::STOP)
				{
					c->data->position.x = TLDer.hitbox.x + TLDer.hitbox.w;
					c->data->speed = 0;
				}
			}
			else {
				// Stop at TL going to east
				if (TLIzq.hitbox.x > c->data->hitbox.x &&
					TLIzq.hitbox.x < c->data->hitbox.x + c->data->hitbox.w &&
					c->data->hitbox.y < TLIzq.hitbox.y + TLIzq.hitbox.h &&
					c->data->hitbox.y + TLIzq.hitbox.h > TLIzq.hitbox.y && TLIzq.state == TLState::STOP)
				{
					c->data->position.x = TLIzq.hitbox.x - TLIzq.hitbox.w - colliderFix;
					c->data->speed = 0;
				}
			}
		}

		// --- Collision with player --- 

		if (playerPtr->baseCollider->Intersects(c->data->hitbox))
		{
			if(c->data->claxonCooldown < 0){
				c->data->claxonCooldown = 60;

				int sound = rand() % 4;
				switch (sound)
				{
				case 1:
					app->audio->PlayFx(fxCar1);
					break;
				case 2:
					app->audio->PlayFx(fxCar2);
					break;
				case 3:
					app->audio->PlayFx(fxCar3);
					break;
				case 4:
					app->audio->PlayFx(fxCar4);
					break;
				}
			}
			else {
				c->data->claxonCooldown--;
			}
		}

		// === Print ===
		app->render->DrawTexture(c->data->sprite, c->data->position.x, c->data->position.y, &c->data->carType->GetCurrentFrame(), 2);

		/*if (app->collisions->debug) {
			app->render->DrawRectangle(c->data->hitbox, 255, 0, 0, 100);
		}*/

		// === Delete ===
		if (c->data->direction == 1 && c->data->position.x > 101 * TILE_SIZE) {
			DeleteCars(c);
		}
		else if (c->data->direction == -1 && c->data->position.x < -2 * TILE_SIZE) {
			DeleteCars(c);
		}
	}
}

bool Stages::DeleteCars(ListItem<Car*>* c) {
	for (ListItem<Car*>* ca = cars.start; ca != nullptr; ca = ca->next) {
		if (ca == c) {
			app->tex->UnLoad(ca->data->sprite);
			ca->data->collider->pendingToDelete = true;
			cars.del(ca);
			LOG("Car deleted");
			return true;
		}
	}
}