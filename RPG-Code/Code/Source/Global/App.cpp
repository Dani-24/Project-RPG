#include "App.h"
#include "Window.h"
#include "Input.h"
#include "Render.h"
#include "Textures.h"
#include "Audio.h"
#include "Logo.h"
#include "Title.h"
#include "Scene.h"
#include "Map.h"
#include "GuiManager.h"
#include "EntityManager.h"
#include "EnemyMovement.h"
#include "Battle.h"
#include "Stages.h"
#include "Collisions.h"


#include "FadeToBlack.h"
#include "ModuleQFonts.h"
#include "Pathfinder.h"

#include "Defs.h"
#include "Log.h"

#include <iostream>
#include <sstream>

// Constructor
App::App(int argc, char* args[]) : argc(argc), args(args)
{
	win = new Window(this);
	input = new Input(this);
	render = new Render(this);
	tex = new Textures(this);
	audio = new Audio(this);
	fade = new FadeToBlack(this);

	logoScene = new LogoScene(this, true);
	titleScene = new TitleScene(this, false);
	scene = new Scene(this, false);
	battle = new Battle(this, false);
	stages = new Stages(this);

	entities = new EntityManager(this);

	enemyMovement = new EnemyMovement(this, false);

	map = new Map(this);
	guiManager = new GuiManager(this);

	font = new ModuleQFonts(this, false);
	pathfinder = new Pathfinder(this, false);

	collisions = new Collisions(this);

	// Orden de ejecución de los modulos, player y enemigos después de las escenas
	AddModule(win);
	AddModule(input);
	AddModule(tex);
	AddModule(audio);

	
	AddModule(pathfinder);

	AddModule(logoScene);
	AddModule(titleScene);
	AddModule(scene);
	AddModule(stages);
	AddModule(battle);
	AddModule(map);

	AddModule(entities);
	AddModule(enemyMovement);

	AddModule(font);
	AddModule(guiManager);

	AddModule(collisions);

	AddModule(fade);

	// Render last to swap buffer
	AddModule(render);
}

// Destructor
App::~App()
{
	// Release modules
	ListItem<Module*>* item = modules.end;

	while (item != NULL)
	{
		RELEASE(item->data);
		item = item->prev;
	}

	modules.clear();
}

void App::AddModule(Module* module)
{
	module->Init();
	modules.add(module);
}

// Called before render is available
bool App::Awake()
{
	pugi::xml_document configFile;
	pugi::xml_node config;
	pugi::xml_node configApp;

	bool ret = false;

	// ================================
	//      Load config from XML
	// ================================
	config = LoadConfig(configFile);

	if (config.empty() == false)
	{
		ret = true;
		configApp = config.child("app");

		title.Create(configApp.child("title").child_value());
		organization.Create(configApp.child("organization").child_value());
	}

	if (ret == true)
	{
		ListItem<Module*>* item;
		item = modules.start;

		while ((item != NULL) && (ret == true))
		{
			ret = item->data->Awake(config.child(item->data->name.GetString()));
			item = item->next;
		}
	}

	return ret;
}

// Called before the first frame
bool App::Start()
{

	bool ret = true;
	ListItem<Module*>* item;
	item = modules.start;

	while (item != NULL && ret == true)
	{
		if (item->data->isEnabled() == true) {
			ret = item->data->Start();
		}
		item = item->next;
	}

	return ret;
}

// Called each loop iteration
bool App::Update()
{
	bool ret = true;
	PrepareUpdate();

	if (input->GetWindowEvent(WE_QUIT) == true)
		ret = false;

	if (ret == true)
		ret = PreUpdate();

	if (ret == true)
		ret = DoUpdate();

	if (ret == true)
		ret = PostUpdate();

	FinishUpdate();
	return ret;
}


// ---------------------------------------------
void App::PrepareUpdate()
{
	dt = (float)ms_timer.Read();

	if (dt < DESIRED_DELTATIME)
	{
		float difDt = (DESIRED_DELTATIME - dt);
		SDL_Delay(difDt);

		dt = DESIRED_DELTATIME;
	}
	ms_timer.Start();
}

// ---------------------------------------------
void App::FinishUpdate()
{
}

// Call modules before each loop iteration
bool App::PreUpdate()
{
	bool ret = true;

	ListItem<Module*>* item;
	item = modules.start;

	for (item = modules.start; item != NULL && ret == true; item = item->next)
	{
		if (item->data->isEnabled() == true) {
			ret = item->data->PreUpdate();
		}
	}

	return ret;
}

// Call modules on each loop iteration
bool App::DoUpdate()
{
	bool ret = true;
	ListItem<Module*>* item;
	item = modules.start;

	for (item = modules.start; item != NULL && ret == true; item = item->next)
	{
		// Send dt as an argument to all updates
		if (item->data->isEnabled() == true) {
			ret = item->data->Update(dt);
		}
	}

	return ret;
}

// Call modules after each loop iteration
bool App::PostUpdate()
{
	bool ret = true;
	ListItem<Module*>* item;
	item = modules.start;

	for (item = modules.start; item != NULL && ret == true; item = item->next)
	{
		if (item->data->isEnabled() == true) {
			ret = item->data->PostUpdate();
		}
	}

	return ret;
}

// Called before quitting
bool App::CleanUp()
{
	bool ret = true;
	ListItem<Module*>* item;
	item = modules.end;

	while (item != NULL && ret == true)
	{
		if (item->data->isEnabled() == true) {
			ret = item->data->CleanUp();
		}
		item = item->prev;
	}

	return ret;
}

int App::GetArgc() const
{
	return argc;
}

const char* App::GetArgv(int index) const
{
	if (index < argc)
		return args[index];
	else
		return NULL;
}

const char* App::GetTitle() const
{
	return title.GetString();
}

const char* App::GetOrganization() const
{
	return organization.GetString();
}

// ================================
//  		 CONFIG XML
// ================================
pugi::xml_node App::LoadConfig(pugi::xml_document& configFile) const
{
	pugi::xml_node ret;

	pugi::xml_parse_result result = configFile.load_file(CONFIG_FILENAME);

	if (result == NULL) LOG("Could not load xml file: %s. pugi error: %s", CONFIG_FILENAME, result.description());
	else ret = configFile.child("config");

	return ret;
}

// ================================
//  		 SAVE & LOAD
// ================================
void App::LoadGameRequest()
{
	loadGameRequested = true;
}

void App::SaveGameRequest() const
{
	saveGameRequested = true;
}

bool App::LoadGame()
{
	bool ret = true;

	pugi::xml_document gameStateFile;
	pugi::xml_parse_result result = gameStateFile.load_file(SAVE_STATE_FILENAME);

	if (result == NULL)
	{
		LOG("Could not load xml file savegame.xml. pugi error: %s", result.description());
		ret = false;
	}
	else
	{
		ListItem<Module*>* item;
		item = modules.start;

		while (item != NULL && ret == true)
		{
			ret = item->data->LoadState(gameStateFile.child("save_state").child(item->data->name.GetString()));
			item = item->next;
		}
	}

	loadGameRequested = false;

	return ret;
}

bool App::SaveGame() const
{
	bool ret = false;

	pugi::xml_document* saveDoc = new pugi::xml_document();
	pugi::xml_node saveStateNode = saveDoc->append_child("save_state");

	ListItem<Module*>* item;
	item = modules.start;

	while (item != NULL)
	{
		ret = item->data->SaveState(saveStateNode.append_child(item->data->name.GetString()));
		item = item->next;
	}

	ret = saveDoc->save_file(SAVE_STATE_FILENAME);

	saveGameRequested = false;

	return ret;
}