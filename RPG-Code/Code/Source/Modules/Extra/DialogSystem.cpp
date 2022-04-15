#include "DialogSystem.h"

#include "App.h"
#include "Textures.h"

DialogSystem::DialogSystem(App* application, bool start_enabled) : Module(application, start_enabled) {
	name.Create("dialogSystem");
}

DialogSystem::~DialogSystem() {

}

bool DialogSystem::Awake(pugi::xml_node& config) {
	return true;
}

bool DialogSystem::Start() {
	return true;
}

bool DialogSystem::PreUpdate() {

	if (dialoging == true) {

		// GET INPUTS

	}

	return true;
}

bool DialogSystem::Update(float dt) {

	if (dialoging == true) {

		// CHECK LIST

	}

	return true;
}

bool DialogSystem::PostUpdate() {

	if (dialoging == true) {

		// PRINT TEXT, CHARACTER IMAGE & STUFF

	}

	return true;
}

bool DialogSystem::CleanUp() {

	app->tex->UnLoad(currentChara);

	dialoging = false;

	return true;
}

void DialogSystem::CreateDialog(NPCType charaType, const char* text[DIALOG_LENGHT]) {

	// Asign Image
	switch (charaType)
	{
	case NPCType::COCK:
		//currentChara = cockFace;
		break;
	case NPCType::BARKEEPER:
		//currentChara = barkeeperFace;
		break;
	case NPCType::MERCHANT:
		//currentChara = merchantFace;
		break;
	case NPCType::TRAINER:
		//currentChara = trainerFace;
		break;
	default:
		break;
	}

	// Get all texts
	for (int i = 0; i < DIALOG_LENGHT; i++) {
		dialogList.add(text[i]);
	}

	wait = false;
	dialoging = true;
}