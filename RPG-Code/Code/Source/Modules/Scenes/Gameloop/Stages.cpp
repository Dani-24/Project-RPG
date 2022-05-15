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
#include "Camera.h"
#include "Pathfinder.h"

Stages::Stages(App* application, bool start_enabled) : Module(application, start_enabled)
{
	name.Create("stages");

	actualStage = StageIndex::NONE;
	playerPtr = nullptr;

	onBattle = false;

	pause = false;
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
	hitfx1 = app->audio->LoadFx(Hitfx1Char);
	hitfx2 = app->audio->LoadFx(Hitfx2Char);
	hitfx3 = app->audio->LoadFx(Hitfx3Char);
	shieldfx = app->audio->LoadFx(ShieldfxChar);
	chdiefx = app->audio->LoadFx(ChDiefxChar);
	doorFx = app->audio->LoadFx(DoorChar);
	loseFx = app->audio->LoadFx(LosefxChar);

	//textures
	LoseScreen = app->tex->Load(LoseScreenChar);
	WinScreen = app->tex->Load(WinScreenChar);
	WinMessage = app->tex->Load(WinTextChar);
	LoseMessage = app->tex->Load(LoseTextChar);

	_wait = false;
	elect = true;
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
	case StageIndex::TOWER_4:
		intStage = 13;
		break;
	case StageIndex::TOWER_3:
		intStage = 14;
		break;
	default:
		break;
	}

	return ret;
}

bool Stages::Update(float dt)
{
	switch (actualStage)
	{
	case StageIndex::NONE:
		break;

	case StageIndex::TOWN:

		break;
	case StageIndex::DOJO:

		break;
	case StageIndex::SHOP:

		break;
	case StageIndex::SHOPSUB:

		break;
	case StageIndex::TAVERN:

		break;
	case StageIndex::INTRODUCTION:
		break;
	case StageIndex::WIN:
		break;
	case StageIndex::LOSE:
		break;
	case StageIndex::TOWER_0:
		break;
	case StageIndex::TOWER_1:
		break;
	case StageIndex::TOWER_2:
		break;
	case StageIndex::TOWER_4:
		break;
	case StageIndex::TOWER_3:
		break;
	default:

		break;
	}

	if (normalEnemyListPtr != nullptr) {
		ListItem<NormalEnemy*>* NormalEnemyInList;
		NormalEnemyInList = normalEnemyListPtr->start;
		for (NormalEnemyInList = normalEnemyListPtr->start; NormalEnemyInList != NULL; NormalEnemyInList = NormalEnemyInList->next)
		{
			if (NormalEnemyInList->data->activeOnStage == app->stages->actualStage && playerPtr != nullptr) {
				// "" Chase player ""
				if (NormalEnemyInList->data->chasePlayer) {
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

	return true;
}

// Render bullshit
bool Stages::PostUpdate()
{
	bool ret = true;
	GamePad& pad = app->input->pads[0];

	switch (actualStage)
	{
	case StageIndex::NONE:

		break;
	case StageIndex::TOWN:

		break;
	case StageIndex::DOJO:

		break;
	case StageIndex::SHOP:

		break;
	case StageIndex::SHOPSUB:

		break;
	case StageIndex::TAVERN:

		break;
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
				app->font->DrawTextDelayed("with the goal of fighting at the tower", epilogX - 50, epilogY + 25, {255,0,0});
				break;
			case 5:
				app->font->DrawTextDelayed("But well, I came to ask you some things", epilogX - 60, epilogY);
				break;
			case 6:
				app->font->DrawTextDelayed("and asume your gender with them", epilogX - 50, epilogY);
				break;
			case 7:
				
				app->font->DrawTextDelayed("Well, as Oak says, you are a boy or a girl?", epilogX - 70, epilogY);
				break;
			case 8:
				
				app->font->DrawTextDelayed("Choose with 1 or 2 and confirm with Space", epilogX - 65, epilogY);
				break;
			case 9:
				if (playerPtr->PlayerErection == true) {
					app->font->DrawTextDelayed("OH! So you're a boy", epilogX + 20 , epilogY);
				}
				else {
					app->font->DrawTextDelayed("OH! So you're a girl", epilogX + 20, epilogY);
				}
				break;
			case 10:
				app->font->DrawTextDelayed("(You can still change your gender with 1 or 2 )", epilogX - 100, epilogY);
				break;
			case 11:
				app->font->DrawTextDelayed("An amazing adventure is waiting for you", epilogX - 60, epilogY);
				break;
			case 12:
				ChangeStage(StageIndex::TOWN);
				break;
			default:
				break;
			}

			if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN || pad.a && _wait || pad.b && _wait) {
				
				if(elect) introductionFase++;
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
		app->render->DrawTexture(LoseScreen,0,0);
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
	case StageIndex::TOWER_4:
		break;
	case StageIndex::TOWER_3:
		break;
	}

	
	// Si me pones este if solo dentro de town el resto de mapas no se me imprimen :( -> Fixeado con el actualStage != NONE
	//oka doka
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
									app->render->DrawTexture(npcInList->data->spriteTex, npcInList->data->position.x, npcInList->data->position.y, &npcInList->data->spriteRect);
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
									app->render->DrawTexture(NormalEnemyInList->data->spriteTex, NormalEnemyInList->data->position.x- NormalEnemyInList->data->SpriteEdges.x, NormalEnemyInList->data->position.y - NormalEnemyInList->data->SpriteEdges.y, &NormalEnemyInList->data->spriteRect, 1, true);
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
								app->render->DrawTexture(npcInList->data->spriteTex, npcInList->data->position.x, npcInList->data->position.y, &npcInList->data->spriteRect);
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
			if (playerPtr->PlayerErection == true) {
				if (playerPtr->PlayerMTex != nullptr) {
					app->render->DrawTexture(playerPtr->PlayerMTex, playerPtr->position.x, playerPtr->position.y, &rect);
				}
			}
			if (playerPtr->PlayerErection == false) {
				if (playerPtr->PlayerFTex != nullptr) {
					app->render->DrawTexture(playerPtr->PlayerFTex, playerPtr->position.x, playerPtr->position.y, &rect);
				}
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
								app->render->DrawTexture(npcInList->data->spriteTex, npcInList->data->position.x, npcInList->data->position.y, &npcInList->data->spriteRect);
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
						if (NormalEnemyInList->data->baseCollider->rect.y + NormalEnemyInList->data->baseCollider->rect.h >playerPtr->baseCollider->rect.y) {
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
	}

	//PRINT THE BATTLE SPRITES
	if (onBattle == true) {

		//PRINT THE BATTLE ENTITIES

		for (int i = 0; i <8; i++)
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
								default:
									break;

								}
							}


						}

						if (NormalEnemyInList->data->isAlive == false) {
							NormalEnemyInList->data->currentAnimation = &NormalEnemyInList->data->dieAnim;
						}

						NormalEnemyInList->data->spriteRect = NormalEnemyInList->data->currentAnimation->GetCurrentFrame();
						switch (NormalEnemyInList->data->normalEnemyType) {
						case NormalEnemyType::FLYING_EYE:
							app->render->DrawTexture(NormalEnemyInList->data->spriteTex, NormalEnemyInList->data->position.x, NormalEnemyInList->data->position.y, &NormalEnemyInList->data->spriteRect, 2, false);
							break;
						case NormalEnemyType::BAT:
							app->render->DrawTexture(NormalEnemyInList->data->spriteTex, NormalEnemyInList->data->position.x, NormalEnemyInList->data->position.y, &NormalEnemyInList->data->spriteRect, 3, false);
							break;
						case NormalEnemyType::SKELETON:
							app->render->DrawTexture(NormalEnemyInList->data->spriteTex, NormalEnemyInList->data->position.x, NormalEnemyInList->data->position.y, &NormalEnemyInList->data->spriteRect, 2, false);
							break;
						default:
							app->render->DrawTexture(NormalEnemyInList->data->spriteTex, NormalEnemyInList->data->position.x, NormalEnemyInList->data->position.y, &NormalEnemyInList->data->spriteRect);

							break;
						}


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


							if (playerPtr->PlayerErection == true) {
								playerPtr->currentAnimation = &playerPtr->idleBattleM;
								app->render->DrawTexture(playerPtr->BattleMTex, playerPtr->position.x, playerPtr->position.y, &rect, 3, false);

								if (playerPtr->isAlive == false) {
									playerPtr->currentAnimation = &playerPtr->dieM;
								}

								if (app->battle->actualTurnEntity == partyListPtr->At(0)->data) {
									switch (app->battle->battlePhase) {
									case BattlePhase::THINKING:
										playerPtr->currentAnimation = &playerPtr->idleBattleM;
										app->stages->playerPtr->attackM.Reset();
										app->stages->playerPtr->dieM.Reset();
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
									default:
										break;

									}
								}
							}
							if (playerPtr->PlayerErection == false) {
								playerPtr->currentAnimation = &playerPtr->idleBattleF;
								app->render->DrawTexture(playerPtr->BattleFTex, playerPtr->position.x, playerPtr->position.y, &rect, 3, false);

								if (playerPtr->isAlive == false) {
									playerPtr->currentAnimation = &playerPtr->dieF;
								}

								if (app->battle->actualTurnEntity == partyListPtr->At(0)->data) {
									switch (app->battle->battlePhase) {
									case BattlePhase::THINKING:
										playerPtr->currentAnimation = &playerPtr->idleBattleF;
										app->stages->playerPtr->attackF.Reset();
										app->stages->playerPtr->attackF2.Reset();
										app->stages->playerPtr->attackChainF.Reset();
										app->stages->playerPtr->dieF.Reset();
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
									default:
										break;

									}
								}
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
								default:
									break;

								}
							}
							else {
								CharacterInList->data->currentAnimation = &CharacterInList->data->idleBattle;
								CharacterInList->data->attackAnim1.Reset();
								CharacterInList->data->attackAnim2.Reset();
								CharacterInList->data->dieAnim.Reset();
							}
						}

						if (app->battle->entitiesInBattle[i]->stats->defenseBuffed == true) {
							switch (i) {

							case 0:
								app->render->DrawTexture(app->battle->shield, app->battle->entitiesInBattle[i]->position.x + app->battle->entitiesInBattle[i]->currentAnimation->GetCurrentFrame().w - 50, app->battle->entitiesInBattle[i]->position.y + 70);
								break;
							case 1:
								app->render->DrawTexture(app->battle->shield, app->battle->entitiesInBattle[i]->position.x + app->battle->entitiesInBattle[i]->currentAnimation->GetCurrentFrame().w - 140, app->battle->entitiesInBattle[i]->position.y + 20);
								break;
							case 2:
								app->render->DrawTexture(app->battle->shield, app->battle->entitiesInBattle[i]->position.x + app->battle->entitiesInBattle[i]->currentAnimation->GetCurrentFrame().w + 90, app->battle->entitiesInBattle[i]->position.y + 70);
								break;
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

	return ret;
}

void Stages::ChangeStage(StageIndex newStage) {
	introductionFase = 0;

	// Door sfx
	if (actualStage != StageIndex::NONE && actualStage != StageIndex::INTRODUCTION && newStage != StageIndex::WIN && newStage != StageIndex::LOSE) {
		app->audio->PlayFx(doorFx);
	}

	// Reset map.cpp
	if (app->map->isEnabled() == true) {
		app->map->Disable();
		app->map->Enable();
		app->camera->FreeLimits();
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
			app->camera->OnTarget();
			app->camera->SetLimits(640, 350, 4490, 4200);
			LOG("Loading Town map");

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

		app->audio->PlayMusic("Assets/audio/music/music_happy.ogg");

		break;
	case StageIndex::LOSE:

		LOG("Lose Screen");
		app->audio->PlayFx(loseFx);
		app->audio->PlayMusic("Assets/audio/music/music_lose.ogg");

		break;
	case StageIndex::TOWER_0:

		// Load Map
		if (app->map->isEnabled() == true) {
			app->map->Load("tower_B.tmx");

			playerPtr->position = playerPtr->tower0Pos;
			app->camera->OnTarget();

			LOG("Loading Tower map");

			//app->audio->PlayMusic("Assets/audio/music/");
		}

		break;

	case StageIndex::TOWER_1:

		// Load Map
		if (app->map->isEnabled() == true) {
			app->map->Load("tower_floor_1.tmx");

			playerPtr->position = playerPtr->tower1Pos;
			app->camera->OnTarget();

			LOG("Loading Floor 1 map");

			//app->audio->PlayMusic("Assets/audio/music/");
		}

		break;
	case StageIndex::TOWER_2:

		// Load Map
		if (app->map->isEnabled() == true) {
			app->map->Load("tower_floor_2.tmx");

			playerPtr->position = playerPtr->tower2Pos;
			app->camera->OnTarget();

			LOG("Loading Floor 2 map");

			//app->audio->PlayMusic("Assets/audio/music/");
		}

		break;
	case StageIndex::TOWER_4:

		// Load Map
		if (app->map->isEnabled() == true) {
			app->map->Load("tower_boss_1.tmx");

			playerPtr->position = playerPtr->tower3Pos;
			app->camera->OnTarget();

			LOG("Loading Floor 3 map");

			//app->audio->PlayMusic("Assets/audio/music/");
		}

		break;
	case StageIndex::TOWER_3:

		// Load Map
		if (app->map->isEnabled() == true) {
			app->map->Load("tower_floor_5.tmx");

			playerPtr->position = playerPtr->tower4Pos;
			app->camera->OnTarget();

			LOG("Loading Floor 4 map");

			//app->audio->PlayMusic("Assets/audio/music/");
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

//bool Stages::SaveState(pugi::xml_node& data) const
//{
//	pugi::xml_node stage = data.append_child("stages");
//
//	stage.append_attribute("actualstage") = intStage;
//
//	//Saved.attribute("saved").set_value(saved);
//
//	return false;
//}
//
//bool Stages::LoadState(pugi::xml_node& data)
//{
//	intStage = data.child("actualStage").attribute("actualstage").as_int();
//
//	//saved= data.child("Saved").attribute("saved").as_bool();
//
//	return false;
//}

bool Stages::OnGuiMouseClickEvent(GuiControl* control)
{
	
	return true;
}
