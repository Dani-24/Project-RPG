#ifndef __APP_H__
#define __APP_H__

#include "Module.h"
#include "PerfTimer.h"
#include "Timer.h"
#include "List.h"
#include "PugiXml/src/pugixml.hpp"
#include "Log.h"

#define CONFIG_FILENAME		"config.xml"
#define SAVE_STATE_FILENAME "save_game.xml"

#define DESIRED_DELTATIME 16

// Modules
class Window;
class Input;
class Render;
class Textures;
class Audio;
class LogoScene;
class TitleScene;
class Scene;
class Configuration;
class Map;
class GuiManager;
class EntityManager;
class QuestManager;
class EnemyMovement;
class PauseMenu;

class Camera;
class FadeToBlack;
class Pathfinder;
class ModuleQFonts;

class Stages;
class Battle;
class Collisions;

class DialogSystem;
class Inventory;


class App
{
public:

	// Constructor
	App(int argc, char* args[]);

	// Destructor
	virtual ~App();

	// Called before render is available
	bool Awake();

	// Called before the first frame
	bool Start();

	// Called each loop iteration
	bool Update();

	// Called before quitting
	bool CleanUp();

	// Add a new module to handle
	void AddModule(Module* module);

	// Exposing some properties for reading
	int GetArgc() const;
	const char* GetArgv(int index) const;
	const char* GetTitle() const;
	const char* GetOrganization() const;

	// L02: DONE 1: Create methods to request Load / Save
	void LoadGameRequest();
	void SaveGameRequest() const;

	// Load config file
	// NOTE: It receives config document
	pugi::xml_node LoadConfig(pugi::xml_document&) const;

private:

	// Call modules before each loop iteration
	void PrepareUpdate();

	// Call modules before each loop iteration
	void FinishUpdate();

	// Call modules before each loop iteration
	bool PreUpdate();

	// Call modules on each loop iteration
	bool DoUpdate();

	// Call modules after each loop iteration
	bool PostUpdate();

	// Load / Save
	bool LoadGame();
	bool SaveGame() const;

public:

	// Modules
	Window* win;
	Input* input;
	Render* render;
	Textures* tex;
	Audio* audio;
	LogoScene* logoScene;
	TitleScene* titleScene;
	Scene* scene;
	Configuration* conf;
	Stages* stages;
	Battle* battle;
	Map* map;
	GuiManager* guiManager;
	EntityManager* entities;
	QuestManager* questManager;
	EnemyMovement* enemyMovement;
	Camera* camera;
	PauseMenu* pauseM;

	ModuleQFonts* font;
	FadeToBlack* fade;
	Pathfinder* pathfinder;
	Collisions* collisions;

	DialogSystem* dialogs;
	Inventory* inventory;

private:

	int argc;
	char** args;
	SString title;
	SString organization;

	List<Module*> modules;

private:

	// =================
	//	   DeltaTime
	// =================

	Timer	ms_timer;
	float	dt;
};

extern App* app;

#endif	// __APP_H__