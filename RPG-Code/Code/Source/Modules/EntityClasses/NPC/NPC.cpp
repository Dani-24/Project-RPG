#include "EntityManager.h"
#include"Animation.h"
#include "Entity.h"
#include "DynamicEntity.h"
#include "NPC.h"
#include "App.h"
#include "Scene.h"
#include "PauseMenu.h"

NPC::NPC(NPCType NPCType, int x, int y) : DynamicEntity(DynamicType::NPC)
{

	position = { x,y };
	this->NpcType = NPCType;
	isInteraction = false;
	name = nullptr;
	switch (NPCType) {
	case NPCType::COCK:

		idleAnim.PushBack({ 2, 66, 28, 28 });
		idleAnim.PushBack({ 34,66,28,28 });
		idleAnim.PushBack({ 66,66,28,28 });
		idleAnim.PushBack({ 98,66,28,28 });
		idleAnim.PushBack({ 66,66,28,28 });
		idleAnim.PushBack({ 34,66,28,28 });
		idleAnim.speed = 0.004f;

		configName = "cock";
		npcID = 1;

		baseCollider = app->collisions->AddCollider({ position.x - 15, position.y - 15 , 60,  60 }, Collider::Type::INTERACT, this);

		break;
	case NPCType::BARKEEPER:
		idleAnim.PushBack({ 9, 9, 34, 47 });
	/*	idleAnim.PushBack({ 60, 7, 34, 47 });
		idleAnim.PushBack({ 114, 9, 32, 47 });*/
		idleAnim.speed = 0.006f;
		
		configName = "barkeeper";

		npcID = 3;

		baseCollider = app->collisions->AddCollider({ position.x - 15, position.y , 60,  100 }, Collider::Type::INTERACT, this);

		break;
	case NPCType::MERCHANT:
		idleAnim.PushBack({ 8,15,30,43 });
	/*	idleAnim.PushBack({ 64,13,27,43 });
		idleAnim.PushBack({ 115,15,30,43 });*/
		idleAnim.speed = 0.006f;

		configName = "merchant";

		npcID = 2;

		baseCollider = app->collisions->AddCollider({ position.x - 15, position.y - 5 , 60,  80 }, Collider::Type::INTERACT, this);

		break;
	case NPCType::TRAINER:
		idleAnim.PushBack({ 7, 16, 30, 43 });
	/*	idleAnim.PushBack({ 60, 14, 30, 43 });
		idleAnim.PushBack({ 114, 16, 29, 43 });*/
		idleAnim.speed = 0.006f;
	
		configName = "trainer";

		npcID = 4;

		baseCollider = app->collisions->AddCollider({ position.x - 15, position.y - 5 , 60,  60 }, Collider::Type::INTERACT, this);

		break;
	case NPCType::EMILIO:
		idleAnim.PushBack({ 4,536,36,33 });
		idleAnim.PushBack({ 45,536,40,33 });
		idleAnim.PushBack({ 89,536,38,33 });
		idleAnim.PushBack({ 45,536,40,33 });
		idleAnim.speed = 0.004f;

		configName = "emilio";

		npcID = 5;

		baseCollider = app->collisions->AddCollider({ position.x - 15, position.y , 60,  60 }, Collider::Type::INTERACT, this);

		break;
	case NPCType::GIROIDE:
		idleAnim.PushBack({ 0,0,32,32 });
		idleAnim.speed = 0;

		configName = "giroide";

		npcID = 6;

		baseCollider = app->collisions->AddCollider({ position.x, position.y, 60,  60 }, Collider::Type::INTERACT, this);

		break;

	case NPCType::FUENTE:
		configName = "fuente";
		
		npcID = 7;

		baseCollider = app->collisions->AddCollider({ position.x, position.y, 160,  160 }, Collider::Type::INTERACT, this);

		break;
	case NPCType::CARTELSUDTOWN:
		configName = "cartel";

		npcID = 8;

		baseCollider = app->collisions->AddCollider({ position.x - 15, position.y, 60,  60 }, Collider::Type::INTERACT, this);
		isInteraction = true;
		break;



	case NPCType::DEAD_TREE:
		configName = "dead_tree";

		npcID = 9;


		baseCollider = app->collisions->AddCollider({ position.x - 15, position.y, 60,  60 }, Collider::Type::INTERACT, this);
		isInteraction = true;
		break;

	

	case NPCType::TREE:
		configName = "tree";

		npcID = 10;


		baseCollider = app->collisions->AddCollider({ position.x - 15, position.y, 60,  60 }, Collider::Type::INTERACT, this);
		isInteraction = true;
		break;



	case NPCType::RIP:
		configName = "rip";

		npcID = 11;


		baseCollider = app->collisions->AddCollider({ position.x - 15, position.y, 60,  60 }, Collider::Type::INTERACT, this);
		isInteraction = true;
		break;

	case NPCType::RIP_2:
		configName = "rip2";

		npcID = 12;

		baseCollider = app->collisions->AddCollider({ position.x - 15, position.y, 60,  60 }, Collider::Type::INTERACT, this);
		isInteraction = true;
		break;
	case NPCType::RIP_3:
		configName = "rip3";

		npcID = 13;


		baseCollider = app->collisions->AddCollider({ position.x - 15, position.y, 60,  60 }, Collider::Type::INTERACT, this);
		isInteraction = true;
		break;

	//case NPCType::ARCHER:
	//	idleAnim.PushBack({ 7, 16, 30, 43 });
	//	/*	idleAnim.PushBack({ 60, 14, 30, 43 });
	//		idleAnim.PushBack({ 114, 16, 29, 43 });*/
	//	idleAnim.speed = 0.006f;

	//
	//	configName = "archer";

	//	npcID = 14;

	//	baseCollider = app->collisions->AddCollider({ position.x - 15, position.y - 5 , 60,  60 }, Collider::Type::INTERACT, this);
	//	break;

	//case NPCType::LANCER:
	//		idleAnim.PushBack({ 7, 16, 30, 43 });
	//	/*	idleAnim.PushBack({ 60, 14, 30, 43 });
	//		idleAnim.PushBack({ 114, 16, 29, 43 });*/
	//	idleAnim.speed = 0.006f;
	//	configName = "lancer";

	//	npcID = 15;
	//	baseCollider = app->collisions->AddCollider({ position.x - 15, position.y - 5 , 60,  60 }, Collider::Type::INTERACT, this);
	//	break;

	//case NPCType::WIZARD:
	//		idleAnim.PushBack({ 7, 16, 30, 43 });
	//	/*	idleAnim.PushBack({ 60, 14, 30, 43 });
	//		idleAnim.PushBack({ 114, 16, 29, 43 });*/
	//	idleAnim.speed = 0.006f;
	//	configName = "wizard";

	//	npcID = 16;
	//	baseCollider = app->collisions->AddCollider({ position.x - 15, position.y - 5 , 60,  60 }, Collider::Type::INTERACT, this);
	//	break;

	/*case NPCType::BIGTREE:
		configName = "rip3";

		npcID = 17;


		baseCollider = app->collisions->AddCollider({ position.x - 15, position.y, 60,  60 }, Collider::Type::INTERACT, this);
		isInteraction = true;*/
	case NPCType::VALION:
		idleAnim.PushBack({ 4,10,14,22 });
		idleAnim.PushBack({ 28,10,14,22 });
		idleAnim.PushBack({ 51,10,14,22 });
		
		idleAnim.speed = 0.004f;

		name = "Valion NPC";
		configName = "valion_npc";

		npcID = 14;

		baseCollider = app->collisions->AddCollider({ position.x -15, position.y -15, 60,  60 }, Collider::Type::INTERACT, this);

		break;
	case NPCType::RAYLA:
		idleAnim.PushBack({ 4,10,14,22 });
		idleAnim.PushBack({ 28,10,14,22 });
		idleAnim.PushBack({ 51,10,14,22 });

		idleAnim.speed = 0.004f;

		name = "Rayla NPC";
		configName = "rayla_npc";

		npcID = 15;

		baseCollider = app->collisions->AddCollider({ position.x - 15, position.y - 15, 60,  60 }, Collider::Type::INTERACT, this);

		break;
	case NPCType::DHION:
		idleAnim.PushBack({ 4,10,14,22 });
		idleAnim.PushBack({ 28,10,14,22 });
		idleAnim.PushBack({ 51,10,14,22 });

		idleAnim.speed = 0.004f;

		name = "Dhion NPC";
		configName = "dhion_npc";

		npcID = 16;

		baseCollider = app->collisions->AddCollider({ position.x - 15, position.y - 15, 60,  60 }, Collider::Type::INTERACT, this);

		break;
	case NPCType::TRUCK_KUN:
		idleAnim.PushBack({ 0,0,128,64 });

		idleAnim.speed = 0.004f;

		name = "Truck-Kun";
		configName = "truck_npc";

		npcID = 69;

		baseCollider = app->collisions->AddCollider({ position.x, position.y, 128, 64 }, Collider::Type::INSTANT, this);

		break;
	default:
		break;
	}
	idleAnim.loop = true;

	//player start with idle anim
	currentAnimation = &idleAnim;

	npcId = app->scene->npcList.count();

	zoom = 1;

}



NPC::~NPC()
{}

bool NPC::Awake(pugi::xml_node& config)
{
	chickenChar = config.child("chicken").attribute("path").as_string();
	tavernChar = config.child("tavern").attribute("path").as_string();
	trainerChar = config.child("trainer").attribute("path").as_string();
	shoperChar = config.child("shoper").attribute("path").as_string();
	emilioChar = config.child("korb").attribute("path").as_string();
	giroideChar = config.child("g").attribute("path").as_string();
	/*archerChar = config.child("archer").attribute("path").as_string();
	lancerChar = config.child("lancer").attribute("path").as_string();
	wizardChar = config.child("wizard").attribute("path").as_string();*/
	wizardChar = "Assets/sprites/characters/wizard/Valion.png";
	archerChar = "Assets/sprites/characters/archer/walk/rayla.png";
	lancerChar = "Assets/sprites/characters/lancer/walk/dhion.png";
	return true;
}

// Called before the first frame
bool NPC::Start()
{
	bool ret = true;

	switch (NpcType) {
	case NPCType::COCK:

		spriteTex = app->tex->Load(chickenChar);
		break;
	case NPCType::BARKEEPER:

		spriteTex = app->tex->Load(tavernChar);
		break;
	case NPCType::MERCHANT:


		spriteTex = app->tex->Load(shoperChar);
		break;
	case NPCType::TRAINER:

		spriteTex = app->tex->Load(trainerChar);

		break;
	case NPCType::EMILIO:

		spriteTex = app->tex->Load(emilioChar);
		break;
	case NPCType::GIROIDE:

		spriteTex = app->tex->Load(giroideChar);
		break;
	case NPCType::FUENTE:

		spriteTex = NULL;

		break;
	case NPCType::CARTELSUDTOWN:

		spriteTex = NULL;

		break;
	/*case NPCType::BIGTREE:

		spriteTex = NULL;
		break;*/
	case NPCType::DEAD_TREE:

		spriteTex = NULL;
		break;
	case NPCType::TREE:

		spriteTex = NULL;
			break;
	case NPCType::RIP:

		spriteTex = NULL;
		break;
	case NPCType::RIP_2:

		spriteTex = NULL;
		break;
	case NPCType::RIP_3:

		spriteTex = NULL;
		break;
	case NPCType::VALION:
		spriteTex = app->tex->Load(wizardChar);
		break;
	case NPCType::RAYLA:
		spriteTex = app->tex->Load(archerChar);
		break;
	case NPCType::DHION:
		spriteTex = app->tex->Load(lancerChar);
		break;
	case NPCType::TRUCK_KUN:
		spriteTex = app->tex->Load("Assets/sprites/truck_kun/camion_kun.png");

		break;
	default:
		break;
	}

	return true;
}

bool NPC::PreUpdate()
{
	return true;
}

// Call modules on each loop iteration
bool NPC::Update(float dt)
{
	bool ret = true;
	if (!app->pauseM->pauseGame) {
		if (currentAnimation != nullptr) {
			currentAnimation->Update(dt);
		}
	}
	//LOG("%d, %d", position.x, position.y);

	return ret;
}

// Call modules after each loop iteration
bool NPC::PostUpdate()
{
	bool ret = true;
	/*SDL_Rect rect = currentAnimation->GetCurrentFrame();
	app->render->DrawTexture(sprite, position.x, position.y, &rect);*/

	return true;
}

// Called before quitting
bool NPC::CleanUp()
{
	if (baseCollider != nullptr) {
		app->collisions->RemoveCollider(baseCollider);
	}
	

	baseCollider = nullptr;
	delete baseCollider;

	app->tex->UnLoad(spriteTex);
	spriteTex = nullptr;
	delete spriteTex;


	chickenChar = nullptr;
	delete chickenChar;

	tavernChar = nullptr;
	delete tavernChar;

	trainerChar = nullptr;
	delete trainerChar;

	shoperChar = nullptr;
	delete shoperChar;

	/*archerChar = nullptr;
	delete archerChar;

	lancerChar = nullptr;
	delete lancerChar;

	wizardChar = nullptr;
	delete wizardChar;

	bigtreeChar = nullptr;
	delete bigtreeChar;*/

	currentAnimation = nullptr;
	delete currentAnimation;

	return true;
}