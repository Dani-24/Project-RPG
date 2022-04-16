#include "EntityManager.h"
#include"Animation.h"
#include "Entity.h"
#include "DynamicEntity.h"
#include "NPC.h"
#include "App.h"
#include "Scene.h"

NPC::NPC(NPCType NPCType, int x, int y) : DynamicEntity(DynamicType::NPC)
{

	position = { x,y };
	this->NpcType = NPCType;

	switch (NPCType) {
	case NPCType::COCK:

		idleAnim.PushBack({ 2, 2, 28, 28 });
		idleAnim.PushBack({ 32, 2, 30, 28 });
		idleAnim.PushBack({ 66, 2, 28, 28 });
		idleAnim.PushBack({ 96, 2, 30, 28 });

		configName = "cock";

		baseCollider = app->collisions->AddCollider({ position.x, position.y , 30,  24 }, Collider::Type::INSTANT, this);


		break;
	case NPCType::BARKEEPER:
		idleAnim.PushBack({ 9, 9, 34, 47 });
		idleAnim.PushBack({ 60, 7, 34, 47 });
		idleAnim.PushBack({ 114, 9, 32, 47 });
		
		configName = "barkeeper";

		break;
	case NPCType::MERCHANT:
		idleAnim.PushBack({ 8,15,30,43 });
		idleAnim.PushBack({ 64,13,27,43 });
		idleAnim.PushBack({ 115,15,30,43 });

		configName = "merchant";

		break;
	case NPCType::TRAINER:
		idleAnim.PushBack({ 7, 16, 30, 43 });
		idleAnim.PushBack({ 60, 14, 30, 43 });
		idleAnim.PushBack({ 114, 16, 29, 43 });
	
		configName = "trainer";

		break;

	default:
		break;
	}

	//player start with idle anim
	currentAnimation = &idleAnim;

	npcId = app->scene->npcList.count();

}



NPC::~NPC()
{}

bool NPC::Awake(pugi::xml_node& config)
{
	chickenChar = config.child("chicken").attribute("path").as_string();
	tavernChar = config.child("tavern").attribute("path").as_string();
	trainerChar = config.child("trainer").attribute("path").as_string();
	shoperChar = config.child("shoper").attribute("path").as_string();

	return true;
}

// Called before the first frame
bool NPC::Start()
{
	bool ret = true;

	switch (NpcType) {
	case NPCType::COCK:

		spriteText = app->tex->Load(chickenChar);
		break;
	case NPCType::BARKEEPER:

		spriteText = app->tex->Load("Assets/sprites/npc/tavern/npc_tavern.png");
		break;
	case NPCType::MERCHANT:


		spriteText = app->tex->Load("Assets/sprites/npc/shop/npc_shop.png");
		break;
	case NPCType::TRAINER:

		spriteText = app->tex->Load("Assets/sprites/npc/training/npc_training.png");

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

	if (currentAnimation != nullptr) {
		currentAnimation->Update(dt);
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

	app->tex->UnLoad(spriteText);
	spriteText = nullptr;
	delete spriteText;


	chickenChar = nullptr;
	delete chickenChar;

	tavernChar = nullptr;
	delete tavernChar;

	trainerChar = nullptr;
	delete trainerChar;

	shoperChar = nullptr;
	delete shoperChar;

	currentAnimation = nullptr;
	delete currentAnimation;

	return true;
}