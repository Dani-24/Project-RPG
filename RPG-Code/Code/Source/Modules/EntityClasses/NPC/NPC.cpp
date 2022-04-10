#include "EntityManager.h"
#include"Animation.h"
#include "Entity.h"
#include "DynamicEntity.h"
#include "NPC.h"
#include "App.h"
#include "Scene.h"

NPC::NPC(NPCType NPCType) : DynamicEntity(DynamicType::NPC)
{

	this->NpcType = NPCType;

	switch (NPCType) {
	case NPCType::COCK:

		idleAnim.PushBack({ 2, 2, 28, 28 });
		idleAnim.PushBack({ 32, 2, 30, 28 });
		idleAnim.PushBack({ 66, 2, 28, 28 });
		idleAnim.PushBack({ 96, 2, 30, 28 });

		configName = "cock";

		break;
	case NPCType::BARKEEPER:

		configName = "barkeeper";

		break;
	case NPCType::MERCHANT:

		configName = "merchant";

		break;
	case NPCType::TRAINER:

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

	return true;
}

// Called before the first frame
bool NPC::Start()
{
	bool ret = true;

	spriteText = app->tex->Load("Assets/sprites/npc/Taberna/chicken.png");

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

	currentAnimation->Update(dt);

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
	app->tex->UnLoad(spriteText);

	currentAnimation = nullptr;

	return true;
}