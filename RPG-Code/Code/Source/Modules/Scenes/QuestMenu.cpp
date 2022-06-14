#include "QuestMenu.h"
#include "App.h"
#include "Inventory.h"

#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"

#include "Scene.h"
#include "Stages.h"
#include "GuiManager.h"
#include "FadeToBlack.h"
#include "Player.h"
#include "Camera.h"
#include "QuestManager.h"

QuestMenu::QuestMenu(App* application, bool start_enabled) : Module(application, start_enabled)
{
	name.Create("questMenu");
}

QuestMenu::~QuestMenu()
{}

bool QuestMenu::Awake(pugi::xml_node& config)
{
	LOG("Awakening QUESTS MENU");
	bool ret = true;

	return ret;
}

bool QuestMenu::Start()
{
	LOG("Starting QUESTS MENU");

	int x = -app->camera->GetPos().x / 2;
	int y = -app->camera->GetPos().y / 2;

	// Block player movement
	app->scene->player->canMove = false;

	// Buttons
	backButton = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 500, "Back", { x + 20, y + 10, 74, 32 }, this);
	invent = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 501, "invent", { x + 20, y + 45, 74, 32 }, this);
	invent->state = GuiControlState::DISABLED;


	q1 = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 502, "q1", { x + 29, y + 93, 196, 45 }, this);
	q2 = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 503, "q2", { x + 29, y + 143, 196, 45 }, this);
	q3 = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 504, "q3", { x + 29, y + 193, 196, 45 }, this);
	q4 = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 505, "q4", { x + 29, y + 243, 196, 45 }, this);
	
	//q1->state = GuiControlState::DISABLED;
	q2->state = GuiControlState::DISABLED;
	q3->state = GuiControlState::DISABLED;
	q4->state = GuiControlState::DISABLED;

	if (app->questManager->questToPrintList.count() > 1) {
		q2->state = GuiControlState::NORMAL;
	}
	if (app->questManager->questToPrintList.count() > 2) {
		q3->state = GuiControlState::NORMAL;
	}
	if (app->questManager->questToPrintList.count() > 3) {
		q4->state = GuiControlState::NORMAL;
	}

	backButtonText = app->tex->Load("Assets/gui/buttons/back_text.png");
	backButtonPressedText = app->tex->Load("Assets/gui/buttons/pressed_back_text.png");

	qmenu = app->tex->Load("Assets/gui/inventory/ui_quests.png");

	invText = app->tex->Load("Assets/gui/buttons/invent.png");
	presinvText = app->tex->Load("Assets/gui/buttons/pressed_invent.png");

	// SFX
	buttonSfx = app->audio->LoadFx("Assets/audio/sfx/fx_select_confirm.wav");
	backSfx = app->audio->LoadFx("Assets/audio/sfx/fx_select_back.wav");

	Q_pos.Position.x = x + 120;
	Q_pos.Position.y = y;
	Q_pointA = { x + 800, y };
	Q_pointB = { x, y };

	Q_total_iterations = 60;
	Q_iterations = 0;
	Q_easing_active = true;

	Q_pointA_out = { x, y };
	Q_pointB_out = { x - 800, y };

	Q_total_iterations_out = 60;
	Q_iterations_out = 0;
	Q_easing_active_out = false;

	app->scene->showLocation = false;
	
	qselect = 0;

	return true;
}

bool QuestMenu::PreUpdate()
{
	bool ret = true;

	// Get Inputs here
	if (app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_UP) {
		Disable();
	}

	return ret;
}

bool QuestMenu::Update(float dt)
{
	int x = -app->camera->GetPos().x / 2;
	int y = -app->camera->GetPos().y / 2;

	
	
	//app->scene->guiactivate = true;

	return true;
}

// Render bullshit
bool QuestMenu::PostUpdate()
{
	bool ret = true;

	int x = -app->camera->GetPos().x / 2;
	int y = -app->camera->GetPos().y / 2;
	
	if(invent->state == GuiControlState::DISABLED)invent->state = GuiControlState::NORMAL;
	// Draw UI

	if (Q_easing_active == true)
		Q_pos.Position.x = EaseInBetweenPoints(Q_pointA, Q_pointB);

	if (Q_easing_active_out == true)
		Q_pos.Position.x = EaseOutBetweenPoints(Q_pointA_out, Q_pointB_out);

	app->render->DrawTexture(qmenu, Q_pos.Position.x, Q_pos.Position.y+10);

	if (Q_easing_active == false && Q_easing_active_out == false) {
		backButton->state != GuiControlState::PRESSED ? app->render->DrawTexture(backButtonText, backButton->bounds.x, backButton->bounds.y) : app->render->DrawTexture(backButtonPressedText, backButton->bounds.x, backButton->bounds.y);
		invent->state != GuiControlState::PRESSED ? app->render->DrawTexture(invText, invent->bounds.x, invent->bounds.y) : app->render->DrawTexture(presinvText, invent->bounds.x, invent->bounds.y);
		SDL_Color color = { 255, 255, 255 };
		for (int i = 0; i < app->questManager->questToPrintList.count(); i++) {
			
			if (app->questManager->questToPrintList.At(i)->data->toPrint == true) {
				if (app->questManager->questToPrintList.At(i)->data->State == QuestState::ACTIVE) {
					app->font->DrawText(app->questManager->questToPrintList.At(i)->data->questNumber, x + 85, y + 103 + i * 50);
				}
				
			}
			
			if (app->questManager->questToPrintList.At(i)->data->State == QuestState::FINISHED) {
				if (app->questManager->questToPrintList.At(i)->data->toPrintC == true) {
					app->font->DrawText("X", x + 35, y + 100 + i * 50);
					app->font->DrawText(app->questManager->questToPrintList.At(i)->data->questNumber, x + 85, y + 103 + i * 50);
				}
				else {
					app->questManager->questToPrintList.del(app->questManager->questToPrintList.At(i));
				}
			}
		}
		Quests();
		GampadControl();
	}
	
	return ret;
}

float QuestMenu::EaseInBetweenPoints(iPoint posA, iPoint posB) {
	float value = Q_Efunction.sineEaseIn(Q_iterations, posA.x, posB.x - posA.x, Q_total_iterations);


	//speedY = function.linearEaseNull(iterations, 472, 572, 300);

	//App->render->camera.y += speedY;

	if (Q_iterations < Q_total_iterations) {
		Q_iterations++;
	}

	else {
		Q_iterations = 0;
		Q_easing_active = false;
	}

	return value;
}

float QuestMenu::EaseOutBetweenPoints(iPoint posA, iPoint posB) {
	float value = Q_Efunction.sineEaseOut(Q_iterations_out, posA.x, posB.x - posA.x, Q_total_iterations_out);


	//speedY = function.linearEaseNull(iterations, 472, 572, 300);

	//App->render->camera.y += speedY;

	if (Q_iterations_out < Q_total_iterations_out) {
		Q_iterations_out++;
	}

	else {
		Q_iterations_out = 0;
		app->inventory->Enable();
		Disable();
	}

	return value;
}

void QuestMenu::Quests()
{
	int q = qselect;
	int x = -app->camera->GetPos().x / 2,
		y = -app->camera->GetPos().y / 2;
	SDL_Color Gr = { 0,255,30 }, Bl = { 0, 198, 255 }, Yw = { 255, 244, 153 };
	ListItem<Quest*>* ch = app->questManager->questToPrintList.At(q);

	app->font->DrawText(app->questManager->questToPrintList.At(q)->data->questName, x + 290, y + 87);
	//app->font->DrawText(app->questManager->questToPrintList.At(q)->data->questDescription, x + 290, y + 97);

	switch (app->questManager->questToPrintList.At(q)->data->QuestId) {
	case 0:
		app->font->DrawText("Camion-kun has brought you", x + 290, y + 117);
		app->font->DrawText("to this strange world.", x + 290, y + 140);
		app->font->DrawText("Beat him to find the way", x + 290, y + 163);
		app->font->DrawText("and return your home.", x + 290, y + 186);
		break;
	case 1:
		app->font->DrawText("Go talk with the barkeeper", x + 290, y + 117);
		app->font->DrawText("to find some information", x + 290, y + 140);
		app->font->DrawText("of Camion-kun and the tower.", x + 290, y + 163);
		break;
	case 2:
		app->font->DrawText("Go find Emilio to enter", x + 290, y + 117);
		app->font->DrawText("the Tower.", x + 290, y + 140);
		break;
	case 3:
		app->font->DrawText("Beat the 3 enemies of", x + 290, y + 117);
		app->font->DrawText("the dojo and become more", x + 290, y + 140);
		app->font->DrawText("stronger.", x + 290, y + 163);
	case 4:
		app->font->DrawText("Go tell master Luca", x + 290, y + 117);
		app->font->DrawText("you have defeat all the ", x + 290, y + 140);
		app->font->DrawText("enemies of the dojo.", x + 290, y + 163);
		break;
	default:
		break;

	}

	//Gold
	std::string GOLD = std::to_string(app->questManager->questToPrintList.At(q)->data->QuestGold);
	char const* _GOLD = GOLD.c_str();
	app->font->DrawText(_GOLD, x + 475, y + 255, Yw);
	app->font->DrawText("GOLD", x + 525, y + 255, Yw);

	//Exp
	std::string EXP = std::to_string(app->questManager->questToPrintList.At(q)->data->QuestGold);
	char const* _EXP = EXP.c_str();
	app->font->DrawText(_EXP, x + 475, y + 285, Bl);
	app->font->DrawText("EXP", x + 525, y + 285, Bl);

	if (app->questManager->questToPrintList.At(q)->data->State == QuestState::FINISHED) 
	{
		app->font->DrawText("COMPLETED", x + 290, y + 285, Gr);
	}
}

bool QuestMenu::CleanUp()
{
	LOG("Closing QUESTS MENU");

	//// Allow player to move
	app->scene->player->canMove = true;
	
	backButton->state = GuiControlState::DISABLED;
	invent->state = GuiControlState::DISABLED;

	q1->state = GuiControlState::DISABLED;
	q2->state = GuiControlState::DISABLED;
	q3->state = GuiControlState::DISABLED;
	q4->state = GuiControlState::DISABLED;

	////statsButton->state = GuiControlState::DISABLED;

	app->scene->showLocation = true;

	q1 = nullptr;
	delete q1;

	q2 = nullptr;
	delete q2;

	q3 = nullptr;
	delete q3;

	q4 = nullptr;
	delete q4;

	app->tex->UnLoad(backButtonText);
	app->tex->UnLoad(backButtonPressedText);

	app->tex->UnLoad(invText);
	app->tex->UnLoad(presinvText);
	
	return true;
}

bool QuestMenu::OnGuiMouseClickEvent(GuiControl* control)
{
	switch (control->type)
	{
		case GuiControlType::BUTTON:
		{
			
			if (control->id == 500)
			{
				LOG("Click on Back");

				Disable();

			}
			if (control->id == 501)
			{
				LOG("Click on Back");
				Q_easing_active_out = true;
				
				
			}
			if (control->id == 502)
			{
				LOG("Click on q1");

				qselect = 0;

			}
			if (control->id == 503)
			{
				LOG("Click on q2");

				qselect = 1;

			}
			if (control->id == 504)
			{
				LOG("Click on q3");

				qselect = 2;

			}
			if (control->id == 505)
			{
				LOG("Click on q4");

				qselect = 3;

			}
			
		default: break;
		}
	}
	return true;
}

//called on preupdate
void QuestMenu::GampadControl()
{
	GamePad& pad = app->input->pads[0];
	if (!pad.a && !pad.b) _wait = true;
	if (!pad.down && !pad.up) wait = true;
	/*if (backButton->state == GuiControlState::NORMAL && invent->state == GuiControlState::NORMAL &&
		ch1->state == GuiControlState::NORMAL && (ch2->state == GuiControlState::NORMAL&&app->scene->partyList.count()>1) &&
		(ch3->state == GuiControlState::NORMAL && app->scene->partyList.count() > 2) && (ch4->state == GuiControlState::NORMAL && app->scene->partyList.count() > 3) )
	{
		if (app->input->GetKey(SDL_SCANCODE_UP) == KEY_DOWN || app->input->GetKey(SDL_SCANCODE_DOWN) ||
			app->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_DOWN || app->input->GetKey(SDL_SCANCODE_LEFT) == KEY_DOWN ||
			pad.right || pad.left || pad.up || pad.down)
		{
			ch1->state = GuiControlState::FOCUSED;
			app->guiManager->keyb = true;
		}
	}*/
	
	switch (app->scene->partyList.count())
	{
	case 1:
		if (backButton->state == GuiControlState::NORMAL && invent->state == GuiControlState::NORMAL &&
			q1->state == GuiControlState::NORMAL)
		{
			if (app->input->GetKey(SDL_SCANCODE_UP) == KEY_DOWN || app->input->GetKey(SDL_SCANCODE_DOWN) ||
				app->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_DOWN || app->input->GetKey(SDL_SCANCODE_LEFT) == KEY_DOWN ||
				pad.right || pad.left || pad.up || pad.down)
			{
				q1->state = GuiControlState::FOCUSED;
				app->guiManager->keyb = true;
			}
		}
		break;
	case 2:
		if (backButton->state == GuiControlState::NORMAL && invent->state == GuiControlState::NORMAL &&
			q1->state == GuiControlState::NORMAL && q2->state == GuiControlState::NORMAL)
		{
			if (app->input->GetKey(SDL_SCANCODE_UP) == KEY_DOWN || app->input->GetKey(SDL_SCANCODE_DOWN) ||
				app->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_DOWN || app->input->GetKey(SDL_SCANCODE_LEFT) == KEY_DOWN ||
				pad.right || pad.left || pad.up || pad.down)
			{
				q1->state = GuiControlState::FOCUSED;
				app->guiManager->keyb = true;
			}
		}
		break;
	case 3:
		if (backButton->state == GuiControlState::NORMAL && invent->state == GuiControlState::NORMAL &&
			q1->state == GuiControlState::NORMAL && q2->state == GuiControlState::NORMAL && q3->state == GuiControlState::NORMAL)
		{
			if (app->input->GetKey(SDL_SCANCODE_UP) == KEY_DOWN || app->input->GetKey(SDL_SCANCODE_DOWN) ||
				app->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_DOWN || app->input->GetKey(SDL_SCANCODE_LEFT) == KEY_DOWN ||
				pad.right || pad.left || pad.up || pad.down)
			{
				q1->state = GuiControlState::FOCUSED;
				app->guiManager->keyb = true;
			}
		}
		break;
	case 4:
		if (backButton->state == GuiControlState::NORMAL && invent->state == GuiControlState::NORMAL &&
			q1->state == GuiControlState::NORMAL && q2->state == GuiControlState::NORMAL && q3->state == GuiControlState::NORMAL&&
			q4->state == GuiControlState::NORMAL)
		{
			if (app->input->GetKey(SDL_SCANCODE_UP) == KEY_DOWN || app->input->GetKey(SDL_SCANCODE_DOWN) ||
				app->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_DOWN || app->input->GetKey(SDL_SCANCODE_LEFT) == KEY_DOWN ||
				pad.right || pad.left || pad.up || pad.down)
			{
				q1->state = GuiControlState::FOCUSED;
				app->guiManager->keyb = true;
			}
		}
		break;
	}

	if (q1->state == GuiControlState::FOCUSED) {

		if (app->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN || pad.a && _wait)
		{
			q1->state = GuiControlState::PRESSED;
			q1->NotifyObserver();
			q1->state = GuiControlState::NORMAL;
		}
		if (!pad.down && !pad.up) wait = true;

		if (q2 != NULL ) {
			if ((app->input->GetKey(SDL_SCANCODE_DOWN) == KEY_DOWN || pad.down && wait == true) && app->scene->partyList.count() > 1) {
				q2->state = GuiControlState::FOCUSED;
				q1->state = GuiControlState::NORMAL;
				wait = false;
			}
		}
		if (app->input->GetKey(SDL_SCANCODE_UP) == KEY_DOWN || pad.up && wait == true) {
			invent->state = GuiControlState::FOCUSED;
			q1->state = GuiControlState::NORMAL;
			wait = false;
		}
	}
	else if (invent->state == GuiControlState::FOCUSED) {

		if (app->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN || pad.a && _wait)
		{
			invent->state = GuiControlState::PRESSED;
			invent->NotifyObserver();
		}
		if (!pad.down && !pad.up) wait = true;
		if (app->input->GetKey(SDL_SCANCODE_DOWN) == KEY_DOWN || pad.down && wait == true) {
			q1->state = GuiControlState::FOCUSED;
			invent->state = GuiControlState::NORMAL;
			wait = false;
		}

		if (app->input->GetKey(SDL_SCANCODE_UP) == KEY_DOWN || pad.up && wait == true) {
			backButton->state = GuiControlState::FOCUSED;
			invent->state = GuiControlState::NORMAL;
			wait = false;
		}


	}
	
	else if (backButton->state == GuiControlState::FOCUSED) {

		if (app->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN || pad.a && _wait)
		{
			backButton->state = GuiControlState::PRESSED;
			backButton->NotifyObserver();
		}
		if (!pad.down && !pad.up) wait = true;

		if (app->input->GetKey(SDL_SCANCODE_DOWN) == KEY_DOWN || pad.down && wait == true) {
			invent->state = GuiControlState::FOCUSED;
			backButton->state = GuiControlState::NORMAL;
			wait = false;
		}
		if (q4!=NULL) {
			if ((app->input->GetKey(SDL_SCANCODE_UP) == KEY_DOWN || pad.up && wait == true) && app->scene->partyList.count() > 3) {
				q4->state = GuiControlState::FOCUSED;
				backButton->state = GuiControlState::NORMAL;
				wait = false;
			}
		}


	}
	else if (q2 != NULL) {
		 if (q2->state == GuiControlState::FOCUSED && app->scene->partyList.count() > 1) {

			if (app->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN || pad.a && _wait)
			{
				q2->state = GuiControlState::PRESSED;
				q2->NotifyObserver();
				q2->state = GuiControlState::NORMAL;
			}
			if (!pad.down && !pad.up) wait = true;
			if (q3 != NULL) {
				if ((app->input->GetKey(SDL_SCANCODE_DOWN) == KEY_DOWN || pad.down && wait == true) && app->scene->partyList.count() > 2) {
					q2->state = GuiControlState::FOCUSED;
					q3->state = GuiControlState::NORMAL;
					wait = false;
				}
			}
			if (app->input->GetKey(SDL_SCANCODE_UP) == KEY_DOWN || pad.up && wait == true) {
				q1->state = GuiControlState::FOCUSED;
				q2->state = GuiControlState::NORMAL;
				wait = false;
			}
		}
	}
	else if (q3 != NULL) {
		if (q3->state == GuiControlState::FOCUSED && app->scene->partyList.count() > 2) {

			if (app->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN || pad.a && _wait)
			{
				q3->state = GuiControlState::PRESSED;
				q3->NotifyObserver();
				q3->state = GuiControlState::NORMAL;
			}
			if (!pad.down && !pad.up) wait = true;
			if (q4 != NULL) {
				if ((app->input->GetKey(SDL_SCANCODE_DOWN) == KEY_DOWN || pad.down && wait == true) && app->scene->partyList.count() > 3) {
					q4->state = GuiControlState::FOCUSED;
					q3->state = GuiControlState::NORMAL;
					wait = false;
				}
			}
			if (app->input->GetKey(SDL_SCANCODE_UP) == KEY_DOWN || pad.up && wait == true && _wait) {
				q2->state = GuiControlState::FOCUSED;
				q3->state = GuiControlState::NORMAL;
				wait = false;
			}
		}
	}
	else if (q4 != NULL) {
		if (q4->state == GuiControlState::FOCUSED && app->scene->partyList.count() > 3) {

			if (app->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN || pad.a)
			{
				q4->state = GuiControlState::PRESSED;
				q4->NotifyObserver();
				q4->state = GuiControlState::NORMAL;
			}
			if (!pad.down && !pad.up) wait = true;

			if (app->input->GetKey(SDL_SCANCODE_DOWN) == KEY_DOWN || pad.down && wait == true) {
				backButton->state = GuiControlState::FOCUSED;
				q4->state = GuiControlState::NORMAL;
				wait = false;
			}

			if (app->input->GetKey(SDL_SCANCODE_UP) == KEY_DOWN || pad.up && wait == true) {
				q3->state = GuiControlState::FOCUSED;
				q4->state = GuiControlState::NORMAL;
				wait = false;
			}
		}
	}
}