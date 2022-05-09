#include "PartyStats.h"
#include "PauseMenu.h"
#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "Title.h"
#include "FadeToBlack.h"
#include "ModuleQFonts.h"
#include "Stages.h"
#include "Scene.h"
#include "GuiManager.h"
#include "Camera.h"
#include "Player.h"
#include "Defs.h"
#include "Log.h"
#include "GuiButton.h"
#include "Configuration.h"
#include "Battle.h"

PartyStats::PartyStats(App* application, bool start_enabled) : Module(application, start_enabled)
{
	name.Create("PartyStats");

}

// Destructor
PartyStats::~PartyStats()
{}

// Called before render is available
bool PartyStats::Awake(pugi::xml_node& config)
{
	LOG("Loading PartyStats");
	bool ret = true;



	return ret;
}

// Called before the first frame
bool PartyStats::Start()
{


	// GUI
	/*party = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 21, "Start", { (app->win->GetWidth() / 2) - 580, (app->win->GetWidth() / 50) + 250, 74, 20 }, this);
	invent = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 22, "Albert", { (app->win->GetWidth() / 2) - 470, (app->win->GetWidth() / 50) + 250, 74, 20 }, this);
	town = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 23, "sos", { (app->win->GetWidth() / 2) - 360, (app->win->GetWidth() / 50) + 250, 74, 20 }, this);
	resume = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 24, "putaso", { (app->win->GetWidth() / 2) - 250, (app->win->GetWidth() / 50) + 250, 74, 20 }, this);
	config = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 25, "comoLaAbuela", { (app->win->GetWidth() / 2) - 140, (app->win->GetWidth() / 50) + 250, 74, 20 }, this);
	save = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 26, "comoLaAbuela", { (app->win->GetWidth() / 2) - 140, (app->win->GetWidth() / 50) + 250, 74, 20 }, this);
	load = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 27, "comoLaAbuela", { (app->win->GetWidth() / 2) - 140, (app->win->GetWidth() / 50) + 250, 74, 20 }, this);
	exit = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 28, "comoLaAbuela", { (app->win->GetWidth() / 2) - 140, (app->win->GetWidth() / 50) + 250, 74, 20 }, this);*/

	/*party->state = GuiControlState::DISABLED;
	invent->state = GuiControlState::DISABLED;
	town->state = GuiControlState::DISABLED;
	resume->state = GuiControlState::DISABLED;
	config->state = GuiControlState::DISABLED;
	save->state = GuiControlState::DISABLED;
	load->state = GuiControlState::DISABLED;
	exit->state = GuiControlState::DISABLED;*/
	// Load Assets

	// Audio 

	confirmFx = app->audio->LoadFx("Assets/audio/sfx/fx_select_confirm.wav");

	
	
	return true;
}


bool PartyStats::OnGuiMouseClickEvent(GuiControl* control)
{
	if (!app->conf->isEnabled()) {
		switch (control->type)
		{
		case GuiControlType::BUTTON:
		{
			//Checks the GUI element ID

			if (control->id == 21)
			{
				LOG("owo");
			}
			
		}
		//Other cases here

		default: break;
		}
	}
	return true;
}


// Called each loop iteration
bool PartyStats::PreUpdate()
{
	bool ret = true;
	//ret = exitg;
	int xt, yt, xc, yc;

	//variables for textures
	xt = -app->camera->GetPos().x / 2 + app->win->GetWidth() / 2;
	yt = -app->camera->GetPos().y / 2 + app->win->GetHeight() / 2;

	//variables for text
	xc = -app->camera->GetPos().x / app->win->GetScale() + app->win->GetWidth() / 2;
	yc = -app->camera->GetPos().y / app->win->GetScale() + app->win->GetHeight() / 2;

	
	return ret;
}

// Called each loop iteration
bool PartyStats::Update(float dt)
{

	int xt, yt, xc, yc;

	//variables for textures
	xt = -app->camera->GetPos().x / 2 + app->win->GetWidth() / 2;
	yt = -app->camera->GetPos().y / 2 + app->win->GetHeight() / 2;

	//variables for text
	xc = -app->camera->GetPos().x / app->win->GetScale() + app->win->GetWidth() / 2;
	yc = -app->camera->GetPos().y / app->win->GetScale() + app->win->GetHeight() / 2;



	return true;
}

// Called each loop iteration
bool PartyStats::PostUpdate()
{
	bool ret = true;

	int xt, yt, xc, yc;

	//variables for textures
	xt = -app->camera->GetPos().x / 2 + app->win->GetWidth() / 2;
	yt = -app->camera->GetPos().y / 2 + app->win->GetHeight() / 2;

	//variables for text
	xc = -app->camera->GetPos().x / app->win->GetScale() + app->win->GetWidth() / 2;
	yc = -app->camera->GetPos().y / app->win->GetScale() + app->win->GetHeight() / 2;


	return ret;
}

// Called before quitting
bool PartyStats::CleanUp()
{
	LOG("Freeing PartyStats scene");


	return true;
}