#include "StatsMenu.h"
#include "App.h"
#include "Inventory.h"
#include "QuestMenu.h"

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

StatsMenu::StatsMenu(App* application, bool start_enabled) : Module(application, start_enabled)
{
	name.Create("stmen");
}

StatsMenu::~StatsMenu()
{}

bool StatsMenu::Awake(pugi::xml_node& config)
{
	LOG("Awakening STATS MENU");
	bool ret = true;

	return ret;
}

bool StatsMenu::Start()
{
	LOG("Starting STATS MENU");

	int x = -app->camera->GetPos().x / 2;
	int y = -app->camera->GetPos().y / 2;

	// Block player movement
	app->scene->player->canMove = false;

	// Buttons
	backButton = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 400, "Back", { x + 20, y + 10, 74, 32 }, this);
	quests = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 401, "quests", { x + 20, y + 45, 74, 32 }, this);
	quests->state = GuiControlState::DISABLED;


	ch1 = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 402, "ch1", { x + 29, y + 93, 196, 45 }, this);
	ch2 = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 403, "ch2", { x + 29, y + 143, 196, 45 }, this);
	ch3 = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 404, "ch3", { x + 29, y + 193, 196, 45 }, this);
	ch4 = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 405, "ch4", { x + 29, y + 243, 196, 45 }, this);
	
	//ch1->state = GuiControlState::DISABLED;
	ch2->state = GuiControlState::DISABLED;
	ch3->state = GuiControlState::DISABLED;
	ch4->state = GuiControlState::DISABLED;

	if (app->scene->partyList.count() > 1) {
		ch2->state = GuiControlState::NORMAL;
	}
	if (app->scene->partyList.count() > 2) {
		ch3->state = GuiControlState::NORMAL;
	}
	if (app->scene->partyList.count() > 3) {
		ch4->state = GuiControlState::NORMAL;
	}

	backButtonTexture = app->tex->Load("Assets/gui/buttons/back_text.png");
	backButtonPressedTexture = app->tex->Load("Assets/gui/buttons/pressed_back_text.png");

	gui = app->tex->Load("Assets/gui/inventory/UI_stats.png",0);

	questsTex = app->tex->Load("Assets/gui/buttons/quest.png");
	presQuestsTex = app->tex->Load("Assets/gui/buttons/pressed_quest.png");

	// SFX
	buttonSfx = app->audio->LoadFx("Assets/audio/sfx/fx_select_confirm.wav");
	backSfx = app->audio->LoadFx("Assets/audio/sfx/fx_select_back.wav");

	S_pos.Position.x = x + 120;
	S_pos.Position.y = y;
	S_pointA = { x + 800, y };
	S_pointB = { x, y };

	S_total_iterations = 60;
	S_iterations = 0;
	S_easing_active = true;

	S_pointA_out = { x, y };
	S_pointB_out = { x - 800, y };

	S_total_iterations_out = 60;
	S_iterations_out = 0;
	S_easing_active_out = false;

	app->scene->showLocation = false;
	
	chselect = 0;

	return true;
}

bool StatsMenu::PreUpdate()
{
	bool ret = true;

	// Get Inputs here
	if (app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_UP) {
		Disable();
	}

	return ret;
}

bool StatsMenu::Update(float dt)
{
	int x = -app->camera->GetPos().x / 2;
	int y = -app->camera->GetPos().y / 2;

	
	
	//app->scene->guiactivate = true;

	return true;
}

// Render bullshit
bool StatsMenu::PostUpdate()
{
	bool ret = true;

	int x = -app->camera->GetPos().x / 2;
	int y = -app->camera->GetPos().y / 2;
	
	if(quests->state == GuiControlState::DISABLED)quests->state = GuiControlState::NORMAL;
	// Draw UI

	if (S_easing_active == true)
		S_pos.Position.x = EaseInBetweenPoints(S_pointA, S_pointB);

	if (S_easing_active_out == true)
		S_pos.Position.x = EaseOutBetweenPoints(S_pointA_out, S_pointB_out);

	app->render->DrawTexture(gui, S_pos.Position.x, S_pos.Position.y+10);

	if (S_easing_active == false && S_easing_active_out == false) {
		backButton->state != GuiControlState::PRESSED ? app->render->DrawTexture(backButtonTexture, backButton->bounds.x, backButton->bounds.y) : app->render->DrawTexture(backButtonPressedTexture, backButton->bounds.x, backButton->bounds.y);
		quests->state != GuiControlState::PRESSED ? app->render->DrawTexture(questsTex, quests->bounds.x, quests->bounds.y) : app->render->DrawTexture(presQuestsTex, quests->bounds.x, quests->bounds.y);

		for (int i = 0; i < app->scene->partyList.count(); i++)
		{
			////FACEES
			app->render->DrawTexture(app->scene->partyList.At(i)->data->spriteFace, x + 33, y + 94 + i * 50);
			app->font->DrawText(app->scene->partyList.At(i)->data->name, x + 85, y + 103 + i * 50);


		}
		Statss();
		GampadControl();
	}
	
	return ret;
}

float StatsMenu::EaseInBetweenPoints(iPoint posA, iPoint posB) {
	float value = S_Efunction.sineEaseIn(S_iterations, posA.x, posB.x - posA.x, S_total_iterations);


	//speedY = function.linearEaseNull(iterations, 472, 572, 300);

	//App->render->camera.y += speedY;

	if (S_iterations < S_total_iterations) {
		S_iterations++;
	}

	else {
		S_iterations = 0;
		S_easing_active = false;
	}

	return value;
}

float StatsMenu::EaseOutBetweenPoints(iPoint posA, iPoint posB) {
	float value = S_Efunction.sineEaseOut(S_iterations_out, posA.x, posB.x - posA.x, S_total_iterations_out);


	//speedY = function.linearEaseNull(iterations, 472, 572, 300);

	//App->render->camera.y += speedY;

	if (S_iterations_out < S_total_iterations_out) {
		S_iterations_out++;
	}

	else {
		S_iterations_out = 0;
		app->questMenu->Enable();
		Disable();
	}

	return value;
}

bool StatsMenu::CleanUp()
{
	LOG("Closing STATS MENU");

	//// Allow player to move
	app->scene->player->canMove = true;
	
	backButton->state = GuiControlState::DISABLED;
	quests->state = GuiControlState::DISABLED;

	ch1->state = GuiControlState::DISABLED;
	if (app->scene->partyList.count() > 1 && ch2->state == GuiControlState::NORMAL)ch2->state = GuiControlState::DISABLED;
	if (app->scene->partyList.count() > 2 && ch3->state == GuiControlState::NORMAL)ch3->state = GuiControlState::DISABLED;
	if (app->scene->partyList.count() > 3 && ch4->state == GuiControlState::NORMAL)ch4->state = GuiControlState::DISABLED;

	////statsButton->state = GuiControlState::DISABLED;

	app->scene->showLocation = true;

	app->tex->UnLoad(backButtonTexture);
	app->tex->UnLoad(backButtonPressedTexture);

	app->tex->UnLoad(questsTex);
	app->tex->UnLoad(presQuestsTex);
	
	return true;
}

bool StatsMenu::OnGuiMouseClickEvent(GuiControl* control)
{
	switch (control->type)
	{
		case GuiControlType::BUTTON:
		{
			
			if (control->id == 400)
			{
				LOG("Click on Back");

				Disable();

			}
			if (control->id == 401)
			{
				LOG("Click on Back");
				S_easing_active_out = true;
				
				
			}
			if (control->id == 402)
			{
				LOG("Click on CH1");

				chselect = 0;

			}
			if (control->id == 403)
			{
				LOG("Click on CH2");

				chselect = 1;

			}
			if (control->id == 404)
			{
				LOG("Click on CH3");

				chselect = 2;

			}
			if (control->id == 405)
			{
				LOG("Click on CH4");

				chselect = 3;

			}
			
		default: break;
		}
	}
	return true;
}

void StatsMenu::Statss()
{
	int by = chselect;
	SDL_Color Gr = { 0,255,30 }, Bl = { 0, 198, 255 }, Yw = { 255, 244, 153 };
	// Variables
	int w = 80, h = 8, wpm = 65;
	int x = -app->camera->GetPos().x / 2,
		y = -app->camera->GetPos().y / 2,
		barsX = x + 173,
		barsY = y + 28;
	ListItem<Character*>* ch = app->scene->partyList.At(by);

	app->font->DrawText(app->scene->partyList.At(by)->data->name, x + 340, y + 89);
	if (ch->data->name == "Rhen" || ch->data->name == "Briar" || ch->data->name == "Hellie")app->font->DrawText("Paladin", x + 490, y + 89);
	else if (ch->data->name == "Valion")app->font->DrawText("Mage", x + 490, y + 89);
	else if (ch->data->name == "Rayla")app->font->DrawText("Archer", x + 490, y + 89);
	else if (ch->data->name == "Dhion")app->font->DrawText("Lancer", x + 490, y + 89);

	int py = 10;
	/////////////HABILITIES
	if (ch->data->stats->level >= 1)
	{
		
		if (ch->data->name == "Rhen" || ch->data->name == "Briar" || ch->data->name == "Hellie")
		{
			app->font->DrawText("Attack", x + 461, y + 140 );
		}
		else if (ch->data->name == "Valion")
		{
			app->font->DrawText("Attack", x + 461, y + 140 );
		}
		else if (ch->data->name == "Rayla")
		{
			app->font->DrawText("Attack", x + 461, y + 140  );
		}
		else if (ch->data->name == "Dhion")
		{
			app->font->DrawText("Attack", x + 461, y + 140 );
		}
	}
	if (ch->data->stats->level >= 3)
	{

		if (ch->data->name == "Rhen" || ch->data->name == "Briar" || ch->data->name == "Hellie")
		{
			app->font->DrawText("Shield", x + 461, y + 165);
		}
		else if (ch->data->name == "Valion")
		{
			app->font->DrawText("Stoned", x + 461, y + 165 );

		}
		else if (ch->data->name == "Rayla")
		{
			app->font->DrawText("Log", x + 461, y + 165 );

		}
		else if (ch->data->name == "Dhion")
		{
			app->font->DrawText("Judge", x + 461, y + 165);

		}
	}
	if (ch->data->stats->level >= 6)
	{

		if (ch->data->name == "Rhen" || ch->data->name == "Briar" || ch->data->name == "Heli")
		{
			app->font->DrawText("Sword", x + 461, y + 190 );
		}
		else if (ch->data->name == "Valion")
		{
			app->font->DrawText("Stoned", x + 461, y + 190);
		}
		else if (ch->data->name == "Rayla")
		{
			app->font->DrawText("Acid", x + 461, y + 190);
		}
		else if (ch->data->name == "Dhion")
		{
			app->font->DrawText("Electro", x + 461, y + 190);
		}
	}
	if (ch->data->stats->level >= 10)
	{

		if (ch->data->name == "Rhen" || ch->data->name == "Briar" || ch->data->name == "Heli")
		{
			app->font->DrawText("Aqua", x + 461, y + 215);
		}
		else if (ch->data->name == "Valion")
		{
			app->font->DrawText("Deer", x + 461, y + 215);
		}
		else if (ch->data->name == "Rayla")
		{
			app->font->DrawText("Sacred", x + 461, y + 215);
		}
		else if (ch->data->name == "Dhion")
		{
			app->font->DrawText("Explosion", x + 461, y + 215);
		}
	}
	

	////////////LVL
	std::string lvl = std::to_string((int)ch->data->stats->level);
	char const* _lvlc = lvl.c_str();

	app->font->DrawText(_lvlc, x + 360, y + 112 + 8);

    /////////EXPPPPPPPP

	std::string EX = std::to_string((int)ch->data->stats->exp);
	char const* _EXc = EX.c_str();

	app->font->DrawText(_EXc, x + 360 , y + 135 + 8 ,Yw);
	app->font->DrawText("/", x + 402, y + 135 + 8);


	std::string EXm = std::to_string((int)ch->data->stats->nexp);
	char const* EXc = EXm.c_str();

	app->font->DrawText(EXc, x + 410, y + 135 + 8, Yw);

	///////////hppppppp
	std::string hp = std::to_string((int)ch->data->stats->health);
	char const* _hpc = hp.c_str();

	app->font->DrawText(_hpc, x + 360, y + 175 + 4,Gr);
	app->font->DrawText("/", x + 402, y + 175 + 4);


	std::string hpm = std::to_string((int)ch->data->stats->maxHealth);
	char const* hpmc = hpm.c_str();

	app->font->DrawText(hpmc, x + 410, y + 175 + 4, Gr);

	///////PMMMM
	std::string pm = std::to_string((int)ch->data->stats->mana);
	char const* _pmc = pm.c_str();

	app->font->DrawText(_pmc, x + 360, y + 215 + 4, Bl);
	app->font->DrawText("/", x + 402, y + 215 + 4);


	std::string pmm = std::to_string((int)ch->data->stats->maxMana);
	char const* pmmc = pmm.c_str();

	app->font->DrawText(pmmc, x + 410, y + 215 + 4, Bl);

	////////////ATKKKKKK
	std::string ATK = std::to_string((int)ch->data->stats->attack);
	char const* _ATK = ATK.c_str();

	app->font->DrawText(_ATK, x + 360, y + 250 );

	////////////defeseewe
	std::string DF = std::to_string((int)ch->data->stats->defense);
	char const* _DF = DF.c_str();

	app->font->DrawText(_DF, x + 360, y + 273 );

	////////////spedddd
	std::string SP = std::to_string((int)ch->data->stats->speed);
	char const* _SP = SP.c_str();

	app->font->DrawText(_SP, x + 360, y + 295 );

	/*app->font->DrawText(app->scene->partyList.At(by)->data->stats, x, y);
	app->font->DrawText(app->scene->partyList.At(by)->data->stats, x, y);
	app->font->DrawText(app->scene->partyList.At(by)->data->stats, x, y);
	app->font->DrawText(app->scene->partyList.At(by)->data->stats, x, y);*/



// ////////Barras Stats Part
		
	// HP bars
			
	hpc = ((float)ch->data->stats->health / (float)ch->data->stats->maxHealth) * w;
	SDL_Rect HPrect = { x + 360, y + 200 + 2, hpc, h };

	app->render->DrawRectangle({ x + 360, y + 200 + 2, w, h }, 0, 0, 0);
	app->render->DrawRectangle(HPrect, 0, 255, 0);

	// PM bars
	pmc = ((float)ch->data->stats->mana / (float)ch->data->stats->maxMana) * wpm;
	SDL_Rect  PMrect = { x + 360, y + 240 , pmc, h };
	app->render->DrawRectangle({ x + 360, y + 240 , wpm, h }, 0, 0, 0);
	app->render->DrawRectangle(PMrect, 0, 78, 255);

	// exp bars
	expc = ((float)ch->data->stats->exp / (float)ch->data->stats->nexp) * w;
	SDL_Rect  EXPrect = { x + 360, y + 160 + 5, expc, h };
	app->render->DrawRectangle({ x + 360, y + 160 + 5, w, h }, 0, 0, 0);
	app->render->DrawRectangle(EXPrect, 255, 244, 153);
	
		
	
}

//called on preupdate
void StatsMenu::GampadControl()
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
		if (backButton->state == GuiControlState::NORMAL && quests->state == GuiControlState::NORMAL &&
			ch1->state == GuiControlState::NORMAL)
		{
			if (app->input->GetKey(SDL_SCANCODE_UP) == KEY_DOWN || app->input->GetKey(SDL_SCANCODE_DOWN) ||
				app->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_DOWN || app->input->GetKey(SDL_SCANCODE_LEFT) == KEY_DOWN ||
				pad.right || pad.left || pad.up || pad.down)
			{
				ch1->state = GuiControlState::FOCUSED;
				app->guiManager->keyb = true;
			}
		}
		break;
	case 2:
		if (backButton->state == GuiControlState::NORMAL && quests->state == GuiControlState::NORMAL &&
			ch1->state == GuiControlState::NORMAL && ch2->state == GuiControlState::NORMAL)
		{
			if (app->input->GetKey(SDL_SCANCODE_UP) == KEY_DOWN || app->input->GetKey(SDL_SCANCODE_DOWN) ||
				app->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_DOWN || app->input->GetKey(SDL_SCANCODE_LEFT) == KEY_DOWN ||
				pad.right || pad.left || pad.up || pad.down)
			{
				ch1->state = GuiControlState::FOCUSED;
				app->guiManager->keyb = true;
			}
		}
		break;
	case 3:
		if (backButton->state == GuiControlState::NORMAL && quests->state == GuiControlState::NORMAL &&
			ch1->state == GuiControlState::NORMAL && ch2->state == GuiControlState::NORMAL && ch3->state == GuiControlState::NORMAL)
		{
			if (app->input->GetKey(SDL_SCANCODE_UP) == KEY_DOWN || app->input->GetKey(SDL_SCANCODE_DOWN) ||
				app->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_DOWN || app->input->GetKey(SDL_SCANCODE_LEFT) == KEY_DOWN ||
				pad.right || pad.left || pad.up || pad.down)
			{
				ch1->state = GuiControlState::FOCUSED;
				app->guiManager->keyb = true;
			}
		}
		break;
	case 4:
		if (backButton->state == GuiControlState::NORMAL && quests->state == GuiControlState::NORMAL &&
			ch1->state == GuiControlState::NORMAL && ch2->state == GuiControlState::NORMAL && ch3->state == GuiControlState::NORMAL&&
			ch4->state == GuiControlState::NORMAL)
		{
			if (app->input->GetKey(SDL_SCANCODE_UP) == KEY_DOWN || app->input->GetKey(SDL_SCANCODE_DOWN) ||
				app->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_DOWN || app->input->GetKey(SDL_SCANCODE_LEFT) == KEY_DOWN ||
				pad.right || pad.left || pad.up || pad.down)
			{
				ch1->state = GuiControlState::FOCUSED;
				app->guiManager->keyb = true;
			}
		}
		break;
	}

	if (ch1->state == GuiControlState::FOCUSED) {

		if (app->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN || pad.a && _wait)
		{
			ch1->state = GuiControlState::PRESSED;
			ch1->NotifyObserver();
			ch1->state = GuiControlState::NORMAL;
		}
		if (!pad.down && !pad.up) wait = true;

		if (ch2 != NULL ) {
			if ((app->input->GetKey(SDL_SCANCODE_DOWN) == KEY_DOWN || pad.down && wait == true) && app->scene->partyList.count() > 1) {
				ch2->state = GuiControlState::FOCUSED;
				ch1->state = GuiControlState::NORMAL;
				wait = false;
			}
		}
		if (app->input->GetKey(SDL_SCANCODE_UP) == KEY_DOWN || pad.up && wait == true) {
			quests->state = GuiControlState::FOCUSED;
			ch1->state = GuiControlState::NORMAL;
			wait = false;
		}
	}
	else if (quests->state == GuiControlState::FOCUSED) {

		if (app->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN || pad.a && _wait)
		{
			quests->state = GuiControlState::PRESSED;
			quests->NotifyObserver();
		}
		if (!pad.down && !pad.up) wait = true;
		if (app->input->GetKey(SDL_SCANCODE_DOWN) == KEY_DOWN || pad.down && wait == true) {
			ch1->state = GuiControlState::FOCUSED;
			quests->state = GuiControlState::NORMAL;
			wait = false;
		}

		if (app->input->GetKey(SDL_SCANCODE_UP) == KEY_DOWN || pad.up && wait == true) {
			backButton->state = GuiControlState::FOCUSED;
			quests->state = GuiControlState::NORMAL;
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
			quests->state = GuiControlState::FOCUSED;
			backButton->state = GuiControlState::NORMAL;
			wait = false;
		}
		if (ch4!=NULL) {
			if ((app->input->GetKey(SDL_SCANCODE_UP) == KEY_DOWN || pad.up && wait == true) && app->scene->partyList.count() > 3) {
				ch4->state = GuiControlState::FOCUSED;
				backButton->state = GuiControlState::NORMAL;
				wait = false;
			}
		}


	}
	else if (ch2 != NULL) {
		 if (ch2->state == GuiControlState::FOCUSED && app->scene->partyList.count() > 1) {

			if (app->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN || pad.a && _wait)
			{
				ch2->state = GuiControlState::PRESSED;
				ch2->NotifyObserver();
				ch2->state = GuiControlState::NORMAL;
			}
			if (!pad.down && !pad.up) wait = true;
			if (ch3 != NULL) {
				if ((app->input->GetKey(SDL_SCANCODE_DOWN) == KEY_DOWN || pad.down && wait == true) && app->scene->partyList.count() > 2) {
					ch2->state = GuiControlState::FOCUSED;
					ch3->state = GuiControlState::NORMAL;
					wait = false;
				}
			}
			if (app->input->GetKey(SDL_SCANCODE_UP) == KEY_DOWN || pad.up && wait == true) {
				ch1->state = GuiControlState::FOCUSED;
				ch2->state = GuiControlState::NORMAL;
				wait = false;
			}
		}
	}
	else if (ch3 != NULL) {
		if (ch3->state == GuiControlState::FOCUSED && app->scene->partyList.count() > 2) {

			if (app->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN || pad.a && _wait)
			{
				ch3->state = GuiControlState::PRESSED;
				ch3->NotifyObserver();
				ch3->state = GuiControlState::NORMAL;
			}
			if (!pad.down && !pad.up) wait = true;
			if (ch4 != NULL) {
				if ((app->input->GetKey(SDL_SCANCODE_DOWN) == KEY_DOWN || pad.down && wait == true) && app->scene->partyList.count() > 3) {
					ch4->state = GuiControlState::FOCUSED;
					ch3->state = GuiControlState::NORMAL;
					wait = false;
				}
			}
			if (app->input->GetKey(SDL_SCANCODE_UP) == KEY_DOWN || pad.up && wait == true && _wait) {
				ch2->state = GuiControlState::FOCUSED;
				ch3->state = GuiControlState::NORMAL;
				wait = false;
			}
		}
	}
	else if (ch4 != NULL) {
		if (ch4->state == GuiControlState::FOCUSED && app->scene->partyList.count() > 3) {

			if (app->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN || pad.a)
			{
				ch4->state = GuiControlState::PRESSED;
				ch4->NotifyObserver();
				ch4->state = GuiControlState::NORMAL;
			}
			if (!pad.down && !pad.up) wait = true;

			if (app->input->GetKey(SDL_SCANCODE_DOWN) == KEY_DOWN || pad.down && wait == true) {
				backButton->state = GuiControlState::FOCUSED;
				ch4->state = GuiControlState::NORMAL;
				wait = false;
			}

			if (app->input->GetKey(SDL_SCANCODE_UP) == KEY_DOWN || pad.up && wait == true) {
				ch3->state = GuiControlState::FOCUSED;
				ch4->state = GuiControlState::NORMAL;
				wait = false;
			}
		}
	}
}