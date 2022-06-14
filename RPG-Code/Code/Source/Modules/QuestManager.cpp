#include "QuestManager.h"
#include "DynamicEntity.h"
#include "StaticEntity.h"

#include "Character.h"
#include "Player.h"

#include "NPC.h"
#include "NormalEnemy.h"
#include "Camera.h"

#include "Party.h"
#include "Stages.h"
#include "App.h"
#include "Scene.h"

#include "VisualEffects.h"

QuestManager::QuestManager(App* application, bool start_enabled) : Module(application, start_enabled)
{
	name.Create("QuestManager");
}

QuestManager::~QuestManager()
{}

bool QuestManager::Awake(pugi::xml_node& config)
{

	return true;
}

bool QuestManager::Start() 
{
	bool ret = true;
	/*Quest* quest1 = new Quest();
	questList.add(quest1);*/

	const char* availableQ32[DIALOG_LENGHT] = {
	"Do you know the way",
	"Go to the tower",
	"Someone is waiting in the 4rth floor"
	};
	const char* activeQ3[DIALOG_LENGHT] = {
	"..."
	};
	const char* completeQ3[DIALOG_LENGHT] = {
	"...",
	"Welcome adventurer",
	"you have defeated de 4 first floors",
	"Congratulations!!!,",
	"Now, you have to wait to unlock next levels",
	"Thank you so much for helping us,"
	"Take a beer camarada"
	};


	Quest* quest3_1 = new Quest(QuestType::INTERACT, QuestState::ACTIVE, 0, 5, "Complete the Tower", "Quest 1", "go through all the tower to defeat Camion-kun", 30, 30, 0, 0, 0, false, availableQ32, activeQ3, completeQ3, true, true);

	//Quest* quest3_2 = new Quest(QuestType::INTERACT, QuestState::ACTIVE, 5, 0, "Pasate la torre al nivel 4", "pasate la torre", 30, 30, 3, 0, 0, false, available, active, completed);

	questList.add(quest3_1);
	questToPrintList.add(quest3_1);
	
	const char* available[DIALOG_LENGHT] = { 
	"Good morning camarada",
	"You seem confused...",
	"If you want some information",
	"please, talk with the barkeeper"};
	const char* active[DIALOG_LENGHT] = {
	"what are you waiting for?",
	"If you want some information",
	"please, talk with the barkeeper" };
	const char* completed[DIALOG_LENGHT] = {
	"Hello"};
	Quest* quest1_1 = new Quest(QuestType::INTERACT, QuestState::AVAILABLE, 1, 1, "La llegada al nuevo mundo", "Quest 2", "Investiga el pueblo", 20, 20, 3, 1, 1, false,available,active,completed, true, false);
	questList.add(quest1_1);

	const char* completed3[DIALOG_LENGHT] = {
	"Oh!! I'ts good to se new faces here",
	"I supose camion-kun killed you...",
	"Well, the only way for you to revive",
	"is defeating Camion-kun",
	"but in order to do that",
	"you will have to complete the tower",
	"If you want to try, search for Emilio.",
	"He's at the entrance of the tower..." };
	const char* active2[DIALOG_LENGHT] = {
	"If you want to try, search for Emilio.",
	"He's at the entrance of the tower..." };
	const char* completed2[DIALOG_LENGHT] = {
	"What's wrong with you?",
	"poyo",
	"You're crazy, I will not let anyone enter again",
	"poyo",
	"Everybody dies in the first two levels",
	"poyo",
	"Become stronger, you don't have any chances now",
	"poyo" };

	Quest* quest1_2 = new Quest(QuestType::INTERACT, QuestState::AVAILABLE, 2, 3, "La llegada al nuevo mundo", "Quest 2", "Busca a Emilio en la torre", 20, 20, 5, 1, 2, false, completed3, active2, completed2, true, true);
	questList.add(quest1_2);

	const char* availableQ2[DIALOG_LENGHT] = {
	"Welcome to the Dojo, traveler soul",
	"Oh so you need to become stronger?",
	"Ok, I will help you",
	"First, let's learn how to battle:",
	"Once you enter the battle",
	"you will see diferent buttons",
	"you can attack the enemy, or defense yourself.",
	"If you have any item you can us it pressing the",
	"ITEM button.",
	"You can see the turns order in the up-left corner",
	"of the screen, they are based on the velocity.",
	"Now you know the basic, go fight!",
	"If you are able to bet the 3 enemies that are here in",
	"the dojo, you will be able to enter the Tower."
	};
	const char* activeQ2[DIALOG_LENGHT] = {
	"If you are able to bet the 3 enemies that are here in",
	"the dojo, you will be able to enter the Tower." 
	};
	const char* completeQ2[DIALOG_LENGHT] = {
	"Oh, so you bet the 3 enemies,",
	"I can see in your face you're now more stronger",
	"Go talk to Emilio and tell him that you trained here."
	};
	Quest* quest2_1 = new Quest(QuestType::KILL, QuestState::DISABLED, 3, 4, "Becoming Stronger", "Quest 3", "Maybe you can train in the Dojo", 40, 40, 3, 1, 3, false, availableQ2, activeQ2, completeQ2, true, false);
	questList.add(quest2_1);

	const char* availableQ2_2[DIALOG_LENGHT] = {
	"Remember",
	"A tope jefe de equipo"
	};
	const char* activeQ2_2[DIALOG_LENGHT] = {
	"..."
	};
	const char* completeQ2_2[DIALOG_LENGHT] = {
	"...",
	"Oh, I see, so you trained in the dojo",
	"poyo",
	"Ok, I see your determination,",
	"poyo",
	"Alright, I let you pass",
	"poyo",
	"But please, don't die.",
	"poyo"
	};
	Quest* quest2_2 = new Quest(QuestType::INTERACT, QuestState::DISABLED, 4, 4, "Becoming Stronger", "Quest 3", "Maybe you can train in the Dojo", 40, 40, 5, 1, 4, true, availableQ2_2, activeQ2_2, completeQ2_2, true, true);
	questList.add(quest2_2);

	Quest* questFloor1 = new Quest(QuestType::KILL, QuestState::ACTIVE, 6, 0, "Lvl1", "lvl1", "mata a todos los enemigos", 0, 0, 8, 0, 0, false, available, active, completed, false, false);
	questList.add(questFloor1);


	const char* availablefloor2[DIALOG_LENGHT] = {
	"There is somethings graved on the wood:",
	"The little tree is guarding the door.",
	"Maybe this is a clue?"
	};
	const char* activefloor2[DIALOG_LENGHT] = {
	"There is somethings graved on the wood:",
	"The little tree is guarding the door.",
	"Maybe this is a clue?"
	};
	const char* completedFloor2[DIALOG_LENGHT] = {
	"Have something graved on the wood:",
	"You visit my dead friend, you can pass."
	};
		
	Quest* questFloor2 = new Quest(QuestType::INTERACT, QuestState::ACTIVE, 7, 9, "Lvl2", "lvl2", "??", 0, 0, 10, 0, 0, false, availablefloor2, activefloor2, completedFloor2, false, false);
	questList.add(questFloor2);

	const char* completedFloor3[DIALOG_LENGHT] = {
	"There is a key fragment on the tombstone"
	};
	Quest* questFloor3_1 = new Quest(QuestType::INTERACT, QuestState::ACTIVE, 8, 0, "Lvl2", "lvl2", "??", 0, 0, 11, 0, 0, false, availablefloor2, activefloor2, completedFloor3, false, false);
	questList.add(questFloor3_1);

	Quest* questFloor3_2 = new Quest(QuestType::INTERACT, QuestState::ACTIVE, 9, 0, "Lvl2", "lvl2", "??", 0, 0, 12, 0, 0, false, availablefloor2, activefloor2, completedFloor3, false, false);
	questList.add(questFloor3_2);

	Quest* questFloor3_3 = new Quest(QuestType::INTERACT, QuestState::ACTIVE, 10, 0, "Lvl2", "lvl2", "??", 0, 0, 13, 0, 0, false, availablefloor2, activefloor2, completedFloor3, false, false);
	questList.add(questFloor3_3);


	return ret;
}

bool QuestManager::PreUpdate()
{
	bool ret = true;

	

	return ret;
}

bool QuestManager::Update(float dt)
{
	bool ret = true;
	
	ListItem<Quest*>* QuestInList;

	for (QuestInList = questList.start; QuestInList != NULL; QuestInList = QuestInList->next)
	{
		/*if (QuestInList->data->QuestId == 2 && QuestInList->data->State == QuestState::FINISHED)
		{
			q2 = true;
		}

		if(q2)
		{
			if (QuestInList->data->QuestId == 3 && QuestInList->data->State == QuestState::DISABLED)
			{
				QuestInList->data->State = QuestState::AVAILABLE;
			}
		}*/

		if (QuestInList->data->QuestId == 3 && QuestInList->data->State == QuestState::ACTIVE) {
			if (app->scene->player->winCount == QuestInList->data->objectiveNum) {
				QuestInList->data->State = QuestState::COMPLETED;
				app->scene->player->winCount = 0;
				//app->scene->player->TowerKey = true;
				
			}
		}
		if (app->scene->player != nullptr) {
			if (QuestInList->data->QuestId == 6 && QuestInList->data->State == QuestState::ACTIVE) {
				if (app->scene->player->winCount == QuestInList->data->objectiveNum) {
					QuestInList->data->State = QuestState::FINISHED;
					app->scene->player->winCount = 0;
					app->scene->player->Floor1Key = true;
					//app->scene->player->TowerKey = true;
				}
			}
		}
		

		/*if (QuestInList->data->QuestId == 4 && QuestInList->data->State == QuestState::COMPLETED) {
			if (app->scene->player->TowerKey == false) {
				app->scene->player->TowerKey = true;
			}
		}*/

		if (QuestInList->data->State == QuestState::COMPLETED) {
			if (QuestInList->data->completedAnimation) {
				QuestInList->data->completedAnimation = !QuestInList->data->completedAnimation;
				app->visualEffects->DisplayEffect(Effects::QUESTCOMPLETED);
			}
		}
	}

	return ret;
}

bool QuestManager::PostUpdate()
{
	bool ret = true;

	return ret;
}

bool QuestManager::CleanUp() 
{
	bool ret = true;

	questList.clear();

	return ret;
}

void QuestManager::CheckQuest(int NPCid)
{
	bool n = false;
	ListItem<Quest*>* QuestInList;

	for (QuestInList = questList.start; QuestInList != NULL; QuestInList = QuestInList->next)
	{
		if (QuestInList->data->NPCId == NPCid) 
		{
			n = true;
			CheckState(QuestInList->data->QuestId);
		}
		else if (QuestInList->data->questType == QuestType::INTERACT) {
			if (QuestInList->data->NPCinteractId == NPCid)
			{

				//CompleteInteract(QuestInList->data->QuestId);
				if (QuestInList->data->State == QuestState::ACTIVE)
				{
					n = true;
					QuestInList->data->State = QuestState::COMPLETED;
					
					InteractComplete(QuestInList->data->QuestId);
				}
				/*else {
					n = false;
				}*/

			}
		}
		

	}
	
		
	

	if (n == false) {
		switch (NPCid)
		{
		case 1:
			app->scene->player->Interact(NPCType::COCK, app->scene->player->cockDialog);
			break;
		case 2:
			app->scene->player->Interact(NPCType::MERCHANT, app->scene->player->merchantDialog);
			break;
		case 3:
			app->scene->player->Interact(NPCType::BARKEEPER, app->scene->player->barkeeperDialog);
			break;
		case 4:
			app->scene->player->Interact(NPCType::TRAINER, app->scene->player->trainerDialog);
			break;
		case 5:
			app->scene->player->Interact(NPCType::EMILIO, app->scene->player->emilioDialog);
			break;
		case 7:
			app->scene->player->Interact(NPCType::FUENTE, app->scene->player->fuenteDialog);
			break;
		case 8:
			app->scene->player->Interact(NPCType::CARTELSUDTOWN, app->scene->player->cartelSudTownDialog);
			break;
		case 9:
			app->scene->player->Interact(NPCType::DEAD_TREE, app->scene->player->deadTreeDialog);
			break;
		case 10:
			app->scene->player->Interact(NPCType::TREE, app->scene->player->TreeDialog);
			break;
		case 11:
			app->scene->player->Interact(NPCType::RIP, app->scene->player->RipDialog);
			break;
		case 12:
			app->scene->player->Interact(NPCType::RIP_2, app->scene->player->RipDialog);
			break;
		case 13:
			app->scene->player->Interact(NPCType::RIP_3, app->scene->player->RipDialog);
			break;
		case 14:
			if (app->scene->player->valionDefeated == false) {
				app->scene->player->Interact(NPCType::VALION, app->scene->player->ValionDialog);
			}
			else {
				app->scene->player->Interact(NPCType::VALION, app->scene->player->ValionDialog2);
			}
			break;
		case 15:
			if (app->scene->player->raylaDefeated == false) {
				app->scene->player->Interact(NPCType::RAYLA, app->scene->player->RaylaDialog);
			}
			else {
				app->scene->player->Interact(NPCType::RAYLA, app->scene->player->RaylaDialog2);
			}
			break;
		case 16:
			if (app->scene->player->dhionDefeated == false) {
				app->scene->player->Interact(NPCType::DHION, app->scene->player->DhionDialog);
			}
			else {
				app->scene->player->Interact(NPCType::DHION, app->scene->player->DhionDialog2);
			}
			break;
		default:
			break;
		}
	}
}

void QuestManager::InteractComplete(int id){
	ListItem<Quest*>* QuestInList;
	for (QuestInList = questList.start; QuestInList != NULL; QuestInList = QuestInList->next)
	{
		if (QuestInList->data->QuestId == id) {
			
		switch (QuestInList->data->NPCinteractId)
		{
		case 1:
			app->scene->player->Interact(NPCType::COCK, QuestInList->data->completedDialog);
			break;
		case 2:
			app->scene->player->Interact(NPCType::MERCHANT, QuestInList->data->completedDialog);
			break;
		case 3:
			app->scene->player->Interact(NPCType::BARKEEPER, QuestInList->data->completedDialog);
			break;
		case 4:
			app->scene->player->Interact(NPCType::TRAINER, QuestInList->data->completedDialog);
			break;
		case 5:
			app->scene->player->Interact(NPCType::EMILIO, QuestInList->data->completedDialog);
			break;
		case 7:
			app->scene->player->Interact(NPCType::FUENTE, QuestInList->data->completedDialog);
			break;
		case 8:
			app->scene->player->Interact(NPCType::CARTELSUDTOWN, QuestInList->data->completedDialog);
			break;
		case 9:
			app->scene->player->Interact(NPCType::DEAD_TREE, QuestInList->data->completedDialog);
			break;
		case 10:
			app->scene->player->Interact(NPCType::TREE, QuestInList->data->completedDialog);
			break;
		case 11:
			app->scene->player->Interact(NPCType::RIP, QuestInList->data->completedDialog);
			break;
		case 12:
			app->scene->player->Interact(NPCType::RIP_2, QuestInList->data->completedDialog);
			break;
		case 13:
			app->scene->player->Interact(NPCType::RIP_3, QuestInList->data->completedDialog);
			break;
		case 14:
			app->scene->player->Interact(NPCType::VALION, QuestInList->data->completedDialog);
			break;
		default:
			break;
		}
		GiveReward(QuestInList->data->QuestId);
		QuestInList->data->State = QuestState::FINISHED;
		if (QuestInList->data->QuestId == 4) {
			app->scene->player->TowerKey = true;
		}
		if (QuestInList->data->QuestId == 7) {
			app->scene->player->Floor2Key = true;
		}
		if (QuestInList->data->QuestId == 8) {
			app->scene->player->Key1 = true;
		}
		if (QuestInList->data->QuestId == 9) {
			app->scene->player->Key2 = true;
		}
		if (QuestInList->data->QuestId == 10) {
			app->scene->player->Key3 = true;
		}

		CheckChain(QuestInList->data->QuestId);
		}
		
	}
}

void QuestManager::CheckState(int Id)
{
	ListItem<Quest*>* QuestInList;
	for (QuestInList = questList.start; QuestInList != NULL; QuestInList = QuestInList->next)
	{
		if (QuestInList->data->QuestId == Id) {
			switch (QuestInList->data->State)
			{
			case QuestState::DISABLED:
				switch (QuestInList->data->NPCId)
				{
				case 1:
					app->scene->player->Interact(NPCType::COCK, app->scene->player->cockDialog);
					break;
				case 2:
					app->scene->player->Interact(NPCType::MERCHANT, app->scene->player->merchantDialog);
					break;
				case 3:
					app->scene->player->Interact(NPCType::BARKEEPER, app->scene->player->barkeeperDialog);
					break;
				case 4:
					app->scene->player->Interact(NPCType::TRAINER, app->scene->player->trainerDialog);
					break;
				case 5:
					app->scene->player->Interact(NPCType::EMILIO, app->scene->player->emilioDialog);
					break;
				case 7:
					app->scene->player->Interact(NPCType::FUENTE, app->scene->player->fuenteDialog);
					break;
				case 8:
					app->scene->player->Interact(NPCType::CARTELSUDTOWN, app->scene->player->cartelSudTownDialog);
					break;
				case 9:
					app->scene->player->Interact(NPCType::DEAD_TREE, app->scene->player->deadTreeDialog);
					break;
				case 10:
					app->scene->player->Interact(NPCType::TREE, app->scene->player->TreeDialog);
					break;
				case 11:
					app->scene->player->Interact(NPCType::RIP, app->scene->player->RipDialog);
					break;
				case 12:
					app->scene->player->Interact(NPCType::RIP_2, app->scene->player->RipDialog);
					break;
				case 13:
					app->scene->player->Interact(NPCType::RIP_3, app->scene->player->RipDialog);
					break;
				case 14:
					app->scene->player->Interact(NPCType::VALION, app->scene->player->ValionDialog);
					break;
				default:
					break;
				}
				break;
			case QuestState::AVAILABLE:
				switch (QuestInList->data->NPCId)
				{
				case 1:
					app->scene->player->Interact(NPCType::COCK, QuestInList->data->availableDialog);
					break;
				case 2:
					app->scene->player->Interact(NPCType::MERCHANT, QuestInList->data->availableDialog);
					break;
				case 3:
					app->scene->player->Interact(NPCType::BARKEEPER, QuestInList->data->availableDialog);
					break;
				case 4:
					app->scene->player->Interact(NPCType::TRAINER, QuestInList->data->availableDialog);
					break;
				case 5:
					app->scene->player->Interact(NPCType::EMILIO, QuestInList->data->availableDialog);
					break;
				case 7:
					app->scene->player->Interact(NPCType::FUENTE, QuestInList->data->availableDialog);
					break;
				case 8:
					app->scene->player->Interact(NPCType::CARTELSUDTOWN, QuestInList->data->availableDialog);
					break;
				case 9:
					app->scene->player->Interact(NPCType::DEAD_TREE, QuestInList->data->availableDialog);
					break;
				case 10:
					app->scene->player->Interact(NPCType::TREE, QuestInList->data->availableDialog);
					break;
				case 11:
					app->scene->player->Interact(NPCType::RIP, QuestInList->data->availableDialog);
					break;
				case 12:
					app->scene->player->Interact(NPCType::RIP_2, QuestInList->data->completedDialog);
					break;
				case 13:
					app->scene->player->Interact(NPCType::RIP_3, QuestInList->data->completedDialog);
					break;
				case 14:
					app->scene->player->Interact(NPCType::VALION, QuestInList->data->completedDialog);
					break;
				default:
					break;
				}
				CheckChain(QuestInList->data->QuestId);
				QuestInList->data->State = QuestState::ACTIVE;
				if (QuestInList->data->toPrint == true) {
					questToPrintList.add(QuestInList->data);
				}
				break;
			case QuestState::ACTIVE:
				switch (QuestInList->data->NPCId)
				{
				case 1:
					app->scene->player->Interact(NPCType::COCK, QuestInList->data->activeDialog);
					break;
				case 2:
					app->scene->player->Interact(NPCType::MERCHANT, QuestInList->data->activeDialog);
					break;
				case 3:
					app->scene->player->Interact(NPCType::BARKEEPER, QuestInList->data->activeDialog);
					break;
				case 4:
					app->scene->player->Interact(NPCType::TRAINER, QuestInList->data->activeDialog);
					break;
				case 5:
					app->scene->player->Interact(NPCType::EMILIO, QuestInList->data->activeDialog);
					break;
				case 7:
					app->scene->player->Interact(NPCType::FUENTE, QuestInList->data->activeDialog);
					break;
				case 8:
					app->scene->player->Interact(NPCType::CARTELSUDTOWN, QuestInList->data->activeDialog);
					break;
				case 9:
					app->scene->player->Interact(NPCType::DEAD_TREE, QuestInList->data->availableDialog);
					break;
				case 10:
					app->scene->player->Interact(NPCType::TREE, QuestInList->data->availableDialog);
					break;
				case 11:
					app->scene->player->Interact(NPCType::RIP, QuestInList->data->availableDialog);
					break;
				case 12:
					app->scene->player->Interact(NPCType::RIP_2, QuestInList->data->completedDialog);
					break;
				case 13:
					app->scene->player->Interact(NPCType::RIP_3, QuestInList->data->completedDialog);
					break;
				case 14:
					app->scene->player->Interact(NPCType::VALION, QuestInList->data->completedDialog);
					break;
				default:
					break;
				}
				break;
			case QuestState::COMPLETED:
				switch (QuestInList->data->NPCId)
				{
				case 1:
					app->scene->player->Interact(NPCType::COCK, QuestInList->data->completedDialog);
					break;
				case 2:
					app->scene->player->Interact(NPCType::MERCHANT, QuestInList->data->completedDialog);
					break;
				case 3:
					app->scene->player->Interact(NPCType::BARKEEPER, QuestInList->data->completedDialog);
					break;
				case 4:
					app->scene->player->Interact(NPCType::TRAINER, QuestInList->data->completedDialog);
					break;
				case 5:
					app->scene->player->Interact(NPCType::EMILIO, QuestInList->data->completedDialog);
					break;
				case 7:
					app->scene->player->Interact(NPCType::FUENTE, QuestInList->data->completedDialog);
					break;
				case 8:
					app->scene->player->Interact(NPCType::CARTELSUDTOWN, QuestInList->data->completedDialog);
					break;
				case 9:
					app->scene->player->Interact(NPCType::DEAD_TREE, QuestInList->data->completedDialog);
					break;
				case 10:
					app->scene->player->Interact(NPCType::TREE, QuestInList->data->completedDialog);
					break;
				case 11:
					app->scene->player->Interact(NPCType::RIP, QuestInList->data->completedDialog);
					break;
				case 12:
					app->scene->player->Interact(NPCType::RIP_2, QuestInList->data->completedDialog);
					break;
				case 13:
					app->scene->player->Interact(NPCType::RIP_3, QuestInList->data->completedDialog);
					break;
				case 14:
					app->scene->player->Interact(NPCType::VALION, QuestInList->data->completedDialog);
					break;
				default:
					break;
				}
				GiveReward(QuestInList->data->QuestId);
				QuestInList->data->State = QuestState::FINISHED;
				if (QuestInList->data->QuestId == 4) {
					app->scene->player->TowerKey = true;
				}
				if (QuestInList->data->QuestId == 7) {
					app->scene->player->Floor2Key = true;
				}
				CheckChain(QuestInList->data->QuestId);
				break;
			case QuestState::FINISHED:
				switch (QuestInList->data->NPCId)
				{
				case 1:
					app->scene->player->Interact(NPCType::COCK, app->scene->player->cockDialog);
					break;
				case 2:
					app->scene->player->Interact(NPCType::MERCHANT, app->scene->player->merchantDialog);
					break;
				case 3:
					app->scene->player->Interact(NPCType::BARKEEPER, app->scene->player->barkeeperDialog);
					break;
				case 4:
					app->scene->player->Interact(NPCType::TRAINER, app->scene->player->trainerDialog);
					break;
				case 5:
					app->scene->player->Interact(NPCType::EMILIO, app->scene->player->emilioDialog);
					break;
				case 7:
					app->scene->player->Interact(NPCType::FUENTE, app->scene->player->fuenteDialog);
					break;
				case 8:
					app->scene->player->Interact(NPCType::CARTELSUDTOWN, app->scene->player->cartelSudTownDialog);
					break;
				case 9:
					app->scene->player->Interact(NPCType::DEAD_TREE, app->scene->player->deadTreeDialog);
					break;
				case 10:
					app->scene->player->Interact(NPCType::TREE, app->scene->player->TreeDialog);
					break;
				case 11:
					app->scene->player->Interact(NPCType::RIP, app->scene->player->RipDialog);
					break;
				case 12:
					app->scene->player->Interact(NPCType::RIP_2, app->scene->player->RipDialog);
					break;
				case 13:
					app->scene->player->Interact(NPCType::RIP_3, app->scene->player->RipDialog);
					break;
				case 14:
					app->scene->player->Interact(NPCType::VALION, QuestInList->data->completedDialog);
					break;
				default:
					break;
				}
				break;
			default:
				break;
			}

		}
	}

}

void QuestManager::GiveReward(int Id) {
	ListItem<Quest*>* QuestInList;
	for (QuestInList = questList.start; QuestInList != NULL; QuestInList = QuestInList->next)
	{
		if (QuestInList->data->QuestId == Id) {
			for (int i = 0; i < app->scene->partyList.count(); i++) {
				app->scene->partyList.At(i)->data->stats->lvlup(QuestInList->data->QuestExp);
			}
		}

		if (QuestInList->data->QuestId == Id) {
			app->scene->player->PlayerMoney += QuestInList->data->QuestGold;
		}
	}
}

void QuestManager::CheckChain(int Id)
{
	int ChainId = 0, InChainId = 0;
	bool PreFinish = false, NextAv = false;
	ListItem<Quest*>* QuestInList;
	ListItem<Quest*>* QuestInList2;
	for (QuestInList = questList.start; QuestInList != NULL; QuestInList = QuestInList->next)
	{
		for (QuestInList2 = questList.start; QuestInList2 != NULL; QuestInList2 = QuestInList2->next)
		{
			if (QuestInList2->data->QuestId == Id && QuestInList2->data->State == QuestState::AVAILABLE)
			{
				if (QuestInList2->data->QuestChain)
				{
					if (QuestInList2->data->QuestLastChain)
					{
						ChainId = QuestInList2->data->QuestChain;
						InChainId = QuestInList2->data->QuestInChainId;
						PreFinish = true;
					}
					else
					{
						if (QuestInList2->data->QuestInChainId != 1) 
						{
							ChainId = QuestInList2->data->QuestChain;
							InChainId = QuestInList2->data->QuestInChainId;
							PreFinish = true;
						}
					}
				}
			}

			if (QuestInList2->data->QuestId == Id && QuestInList2->data->State == QuestState::FINISHED) 
			{
				if (QuestInList2->data->QuestChain)
				{
					if (!QuestInList2->data->QuestLastChain)
					{
						ChainId = QuestInList2->data->QuestChain;
						InChainId = QuestInList2->data->QuestInChainId;
						NextAv = true;
					}

				}
			}
		}

		if (PreFinish) {
			if (QuestInList->data->QuestChain == ChainId && QuestInList->data->QuestInChainId == InChainId - 1 && QuestInList->data->State != QuestState::FINISHED)
			{
				GiveReward(QuestInList->data->QuestId);
				QuestInList->data->State = QuestState::FINISHED;
			}
		}
		if (NextAv) {
			if (QuestInList->data->QuestChain == ChainId && QuestInList->data->QuestInChainId == InChainId + 1)
			{
				QuestInList->data->State = QuestState::AVAILABLE;
			}
		}
	}
}