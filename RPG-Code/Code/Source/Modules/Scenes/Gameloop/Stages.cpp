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

	return ret;
}

bool Stages::Start()
{
	//sfx
	hitfx1 = app->audio->LoadFx("Assets/audio/sfx/fx_attack_hit.wav");
	hitfx2 = app->audio->LoadFx("Assets/audio/sfx/fx_attack_hit_2.wav");
	hitfx3 = app->audio->LoadFx("Assets/audio/sfx/fx_attack_hit_3.wav");
	shieldfx = app->audio->LoadFx("Assets/audio/sfx/fx_shield.wav");
	chdiefx = app->audio->LoadFx("Assets/audio/sfx/fx_character_die.wav");
	doorFx = app->audio->LoadFx("Assets/audio/sfx/fx_open_door.wav");

	//textures
	LoseScreen = app->tex->Load("Assets/textures/winscreen.png");
	WinScreen = app->tex->Load("Assets/textures/winscreen.png");
	
	//buttons
	restart = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 40, "Restart", { (app->win->GetWidth() / 2) - 580, (app->win->GetWidth() / 50) + 250, 74, 32 }, this);
	restartTex= app->tex->Load("Assets/gui/buttons/button_start.png");
	press_restartTex= app->tex->Load("Assets/gui/buttons/pressed_button_start.png");

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
	default:

		break;
	}

	return true;
}

// Render bullshit
bool Stages::PostUpdate()
{
	bool ret = true;

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

			if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN) {
				introductionFase++;
			}
		}

		break;
	case StageIndex::WIN:
	
		break;
	case StageIndex::LOSE:
		app->camera->SetPos({ 0,0 });
		app->render->DrawTexture(LoseScreen,0,0);
		/*playerPtr->canMove = false;*/
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
								if (npcInList->data->spriteText != nullptr) { // CHECK if there is some sprite
									app->render->DrawTexture(npcInList->data->spriteText, npcInList->data->position.x, npcInList->data->position.y, &npcInList->data->spriteRect);
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
							if (NormalEnemyInList->data->position.y + NormalEnemyInList->data->currentAnimation->GetCurrentFrame().h <= playerPtr->position.y + playerPtr->currentAnimation->GetCurrentFrame().h) {
								NormalEnemyInList->data->spriteRect = NormalEnemyInList->data->currentAnimation->GetCurrentFrame();
								if (NormalEnemyInList->data->spriteText != nullptr) { // CHECK if there is some sprite
									app->render->DrawTexture(NormalEnemyInList->data->spriteText, NormalEnemyInList->data->position.x, NormalEnemyInList->data->position.y, &NormalEnemyInList->data->spriteRect);
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
							if (npcInList->data->spriteText != nullptr) { // CHECK if there is some sprite
								app->render->DrawTexture(npcInList->data->spriteText, npcInList->data->position.x, npcInList->data->position.y, &npcInList->data->spriteRect);
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
							if (NormalEnemyInList->data->spriteText != nullptr) { // CHECK if there is some sprite
								app->render->DrawTexture(NormalEnemyInList->data->spriteText, NormalEnemyInList->data->position.x, NormalEnemyInList->data->position.y, &NormalEnemyInList->data->spriteRect);
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
							if (npcInList->data->spriteText != nullptr) { // CHECK if there is some sprite
								app->render->DrawTexture(npcInList->data->spriteText, npcInList->data->position.x, npcInList->data->position.y, &npcInList->data->spriteRect);
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
						if (NormalEnemyInList->data->position.y + NormalEnemyInList->data->currentAnimation->GetCurrentFrame().h > playerPtr->position.y + playerPtr->currentAnimation->GetCurrentFrame().h) {
							NormalEnemyInList->data->spriteRect = NormalEnemyInList->data->currentAnimation->GetCurrentFrame();
							if (NormalEnemyInList->data->spriteText != nullptr) { // CHECK if there is some sprite
								app->render->DrawTexture(NormalEnemyInList->data->spriteText, NormalEnemyInList->data->position.x, NormalEnemyInList->data->position.y, &NormalEnemyInList->data->spriteRect);
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

		////PRINT THE PLAYER ON BATTLE
		//if (playerPtr != nullptr) {
		//	SDL_Rect rect = playerPtr->currentAnimation->GetCurrentFrame();
		//	if (playerPtr->PlayerErection == true) {
		//		app->render->DrawTexture(playerPtr->BattleMTex, playerPtr->position.x, playerPtr->position.y, &rect);
		//	}
		//	if (playerPtr->PlayerErection == false) {
		//		app->render->DrawTexture(playerPtr->BattleFTex, playerPtr->position.x, playerPtr->position.y, &rect);
		//	}
		//}

		//PRINT THE BATTLE ENTITIES
		

		for (int i = 7; i >= 0; i--)
		{
			if (app->battle->entitiesInBattle[i] != nullptr) {

				//IF THEY ARE ENEMIES
				ListItem<NormalEnemy*>* NormalEnemyInList;

				for (NormalEnemyInList = normalEnemyListPtr->start; NormalEnemyInList != NULL && ret == true; NormalEnemyInList = NormalEnemyInList->next)
				{
					if (app->battle->entitiesInBattle[i] == NormalEnemyInList->data) {
						NormalEnemyInList->data->currentAnimation = &NormalEnemyInList->data->battleAnim;
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
						else {
							if (app->battle->battlePhase == BattlePhase::WIN) {
								NormalEnemyInList->data->currentAnimation = &NormalEnemyInList->data->dieAnim;
							}
						}

						NormalEnemyInList->data->spriteRect = NormalEnemyInList->data->currentAnimation->GetCurrentFrame();
						switch (NormalEnemyInList->data->normalEnemyType) {
						case NormalEnemyType::FLYING_EYE:
							app->render->DrawTexture(NormalEnemyInList->data->spriteText, NormalEnemyInList->data->position.x - 1 * NormalEnemyInList->data->spriteRect.w, NormalEnemyInList->data->position.y - 1 * NormalEnemyInList->data->spriteRect.h, &NormalEnemyInList->data->spriteRect, 2);
							break;
						case NormalEnemyType::BAT:
							app->render->DrawTexture(NormalEnemyInList->data->spriteText, NormalEnemyInList->data->position.x - 2 * NormalEnemyInList->data->spriteRect.w, NormalEnemyInList->data->position.y + 1 * NormalEnemyInList->data->spriteRect.h, &NormalEnemyInList->data->spriteRect, 3);
							break;
						case NormalEnemyType::SKELETON:
							app->render->DrawTexture(NormalEnemyInList->data->spriteText, NormalEnemyInList->data->position.x - 1 * NormalEnemyInList->data->spriteRect.w, NormalEnemyInList->data->position.y-1*NormalEnemyInList->data->spriteRect.h, &NormalEnemyInList->data->spriteRect, 2);
							break;
						default:
							app->render->DrawTexture(NormalEnemyInList->data->spriteText, NormalEnemyInList->data->position.x, NormalEnemyInList->data->position.y, &NormalEnemyInList->data->spriteRect);

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
									app->render->DrawTexture(playerPtr->BattleMTex, playerPtr->position.x - 1 * rect.w, playerPtr->position.y - 1 * rect.h, &rect, 2);
									
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
									app->render->DrawTexture(playerPtr->BattleFTex, playerPtr->position.x - 160, playerPtr->position.y - 140, &rect, 2);

									if (playerPtr->isAlive == false) {
										playerPtr-> currentAnimation = &playerPtr->dieF;
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
											playerPtr->currentAnimation = &playerPtr->dieF;
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
							CharacterInList->data->currentAnimation = &CharacterInList->data->idleBattle;
							app->render->DrawTexture(CharacterInList->data->spriteText, CharacterInList->data->position.x, CharacterInList->data->position.y, &CharacterInList->data->spriteRect);

							if (CharacterInList->data->isAlive == false) {
								CharacterInList->data->currentAnimation = &CharacterInList->data->deathAnim;
							}

							if (app->battle->actualTurnEntity->name == "Valion") {
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
									CharacterInList->data->currentAnimation = &CharacterInList->data->deathAnim;
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

						if (app->battle->entitiesInBattle[i]->stats->defenseBuffed == true) {
							switch (i) {

							case 0:
								app->render->DrawTexture(app->battle->shield, app->battle->entitiesInBattle[i]->position.x + app->battle->entitiesInBattle[i]->currentAnimation->GetCurrentFrame().w - 120, app->battle->entitiesInBattle[i]->position.y);
								break;
							case 1:
								app->render->DrawTexture(app->battle->shield, app->battle->entitiesInBattle[i]->position.x + app->battle->entitiesInBattle[i]->currentAnimation->GetCurrentFrame().w - 100, app->battle->entitiesInBattle[i]->position.y + 60);
								break;
							default:
								app->render->DrawTexture(app->battle->shield, app->battle->entitiesInBattle[i]->position.x + app->battle->entitiesInBattle[i]->currentAnimation->GetCurrentFrame().w - 100, app->battle->entitiesInBattle[i]->position.y + 60);
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
		}
	
		
		//switch (app->battle->CurrentEnemyType) {
		//case EnemyInBattleType::NORMAL:
		//	app->battle->normalEnemyInBattle->currentAnimation = &app->battle->normalEnemyInBattle->battleAnim;
		//	SDL_Rect rect = app->battle->normalEnemyInBattle->currentAnimation->GetCurrentFrame();
		//	app->render->DrawTexture(app->battle->normalEnemyInBattle->spriteText, 500, 100, &rect);
		//	break;

		//default:
		//	break;
		//}
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

		
		/*app->audio->PlayMusic("Assets/audio/music/music_intro.ogg");*/

		break;
	case StageIndex::LOSE:

		LOG("Lose Screen");

		/*app->audio->PlayMusic("Assets/audio/music/music_intro.ogg");*/

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
	if (actualStage == StageIndex::LOSE) {
		switch (control->type)
		{
		case GuiControlType::BUTTON:
		{
			//Checks the GUI element ID
			if (control->id == 40)
			{
				LOG("Click on Restart");

				app->LoadGameRequest();

			}
		}
		//Other cases here

		default: break;
		}
	}
	
	return true;
}
