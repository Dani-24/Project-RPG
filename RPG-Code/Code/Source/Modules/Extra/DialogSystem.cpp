#include "DialogSystem.h"

#include "App.h"
#include "Textures.h"
#include "Input.h"
#include "Camera.h"
#include "Window.h"
#include "Scene.h"
#include "Player.h"
#include "Battle.h"

#include "Entity.h"
#include "DynamicEntity.h"
#include "Enemy.h"
#include "BossEnemy.h"

DialogSystem::DialogSystem(App* application, bool start_enabled) : Module(application, start_enabled) {
	name.Create("dialogSystem");
}

DialogSystem::~DialogSystem() {

}

bool DialogSystem::Awake(pugi::xml_node& config) {
	return true;
}

bool DialogSystem::Start() {

	dialogueBox = app->tex->Load("Assets/gui/dialogue_box.png");
	_waitpad = false;
	return true;
}

bool DialogSystem::PreUpdate() {

	GamePad& pad = app->input->pads[0];

	if (!pad.a) _waitpad = true;

	if (dialoging == true) {

		// Inputs
		if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN || pad.a && _waitpad == true) {
			wait = false;
			_waitpad = false;
		}
		app->scene->player->toggleGui = false;
	}

	return true;
}

bool DialogSystem::PostUpdate() {

	if (dialoging == true) {

		int x = -app->camera->GetPos().x / app->win->GetScale();
		int y = -app->camera->GetPos().y / app->win->GetScale() + app->win->GetHeight() / app->win->GetScale() - 64;

		// PRINT TEXT, CHARACTER IMAGE & STUFF
		int n = 0;
		for (ListItem<const char*>* t = dialogList.start; t != NULL; t = t->next) {
			if (displayed == n) {
				if (wait == true) {

					app->render->DrawTexture(dialogueBox, x, y);

					switch (npcType)
					{
					case NPCType::COCK:
						app->font->DrawTextDelayed("Kukock :", x + 150, y + 5, {0,0,0});
						break;
					case NPCType::BARKEEPER:
						app->font->DrawTextDelayed("Dolores Delano :", x + 150, y + 5, {92, 0, 117});
						break;
					case NPCType::MERCHANT:
						app->font->DrawTextDelayed("Vincen� :", x + 150, y + 5, { 255, 255, 92 });
						break;
					case NPCType::TRAINER:
						app->font->DrawTextDelayed("Luca :", x + 150, y + 5, { 18, 117, 0 });
						break;
					case NPCType::EMILIO:
						app->font->DrawTextDelayed("Emilio :", x + 150, y + 5, { 247, 92, 255 });
						break;
					case NPCType::FUENTE:
						app->font->DrawTextDelayed("Town Fountain :", x + 150, y + 5, { 66, 78, 245 });
						break;
					case NPCType::CARTELSUDTOWN:
						app->font->DrawTextDelayed("Welcome Sign ( Post your text here ):", x + 150, y + 5, { 41, 2, 9 });
						break;
					case NPCType::DEAD_TREE:
						app->font->DrawTextDelayed("Dead Tree:", x + 150, y + 5, { 41, 2, 9 });
						break;
					case NPCType::TREE:
						app->font->DrawTextDelayed("Tree:", x + 150, y + 5, { 41, 2, 9 });
						break;
					case NPCType::RIP:
						app->font->DrawTextDelayed("Tombstone:", x + 150, y + 5, { 41, 2, 9 });
						break;
					case NPCType::RIP_2:
						app->font->DrawTextDelayed("Tombstone:", x + 150, y + 5, { 41, 2, 9 });
						break;
					case NPCType::RIP_3:
						app->font->DrawTextDelayed("Tombstone:", x + 150, y + 5, { 41, 2, 9 });
						break;
					case NPCType::VALION:
						app->font->DrawTextDelayed("Valion:", x + 150, y + 5, { 0, 0, 0 });
						break;
					default:
						break;
					}

					app->font->DrawTextDelayed(t->data, x + 120, y + 33);
					if(currentChara != nullptr)
					{
						app->render->DrawTexture(currentChara, x, y);
					}
					

					break;
				}
				else {
					wait = true;
					displayed++;
				}
			}
			n++;
		}
		if (n == dialogList.count()) {
			dialoging = false;
			dialogList.clear();
			app->scene->player->toggleGui = true;
			if (app->scene->player->entityTalking->name != nullptr) {
				if (app->scene->player->entityTalking->name == std::string("Valion NPC")) {
					if (app->battle->isEnabled() == false) {

						app->battle->entitiesInBattle[0] = app->scene->player;
						BossEnemy* EvilValion = (BossEnemy*)app->entities->CreateEntity(BossType::VALION);
						app->scene->normalEnemyList.add((NormalEnemy*)EvilValion);
						app->battle->entitiesInBattle[4] = EvilValion;

						int alliesCount = 1;
						int enemiesCount = 1;

						
						app->battle->Enable();
					}
				}
			}
			app->scene->player->entityTalking = nullptr;
		}
	}

	return true;
}

bool DialogSystem::CleanUp() {

	app->tex->UnLoad(currentChara);
	app->tex->UnLoad(dialogueBox);

	dialoging = false;

	dialogList.clear();

	app->font->CleanFonts();

	return true;
}

void DialogSystem::CreateDialog(NPCType charaType, const char* text[DIALOG_LENGHT]) {

	app->tex->UnLoad(currentChara);

	npcType = charaType;

	// Asign Texture
	switch (charaType)
	{
	case NPCType::COCK:
		currentChara = app->tex->Load("Assets/sprites/faces/chicken.png");
		break;
	case NPCType::BARKEEPER:
		currentChara = app->tex->Load("Assets/sprites/faces/barkeeper.png");
		break;
	case NPCType::MERCHANT:
		currentChara = app->tex->Load("Assets/sprites/faces/shop.png");
		break;
	case NPCType::TRAINER:
		currentChara = app->tex->Load("Assets/sprites/faces/trainer.png");
		break;
	case NPCType::EMILIO:
		currentChara = app->tex->Load("Assets/sprites/faces/emilio.png");
		break;
	case NPCType::VALION:
		currentChara = app->tex->Load("Assets/sprites/faces/wizard.png");
		break;
	default:
		break;
	}

	// Get all texts
	for (int i = 0; i < DIALOG_LENGHT; i++) {
		if (text[i] != NULL) {
			dialogList.add(text[i]);
		}
	}

	wait = true;
	dialoging = true;
	displayed = 0;

	LOG("Creating a dialog with %d texts", dialogList.count());
}