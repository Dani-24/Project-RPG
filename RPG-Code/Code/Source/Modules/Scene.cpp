#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "Scene.h"
#include "Map.h"
#include "GuiManager.h"

#include "Defs.h"
#include "Log.h"

Scene::Scene(App* application, bool start_enabled) : Module(application, start_enabled)
{
	name.Create("scene");
}

// Destructor
Scene::~Scene()
{}

// Called before render is available
bool Scene::Awake()
{
	LOG("Loading Scene");
	bool ret = true;

	return ret;
}

// Called before the first frame
bool Scene::Start()
{
	// L03: DONE: Load map
	//app->map->Load("iso_walk.tmx");
	
	// Load music
	app->audio->PlayMusic("Assets/audio/music/music_title.ogg");

	// L14: TODO 2: Declare a GUI Button and create it using the GuiManager
	btn1 = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 1, "Test1", { (app->win->GetWidth() / 2) - 300, app->win->GetWidth() / 10, 160, 40 }, this);
	btn2 = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 2, "Test2", { (app->win->GetWidth() / 2) + 300, app->win->GetWidth() / 10, 160, 40 }, this);

	// Texture
	img = app->tex->Load("Assets/textures/sample.png");

	int N = 0;
	for (int i = 0; i < 54; i++) {
		imgAnim.PushBack({ N,0,195,200 });
		N += 195;
	}
	imgAnim.speed = 0.02f;
	imgAnim.loop = true;

	return true;
}

// Called each loop iteration
bool Scene::PreUpdate()
{
	bool ret = true;

	if (app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN) {
		ret = false;
	}

	return ret;
}

// Called each loop iteration
bool Scene::Update(float dt)
{
    // L02: DONE 3: Request Load / Save when pressing L/S
	if(app->input->GetKey(SDL_SCANCODE_L) == KEY_DOWN)
		app->LoadGameRequest();

	if(app->input->GetKey(SDL_SCANCODE_S) == KEY_DOWN)
		app->SaveGameRequest();

	// L08: TODO 6: Make the camera movement independent of framerate
	float speed = 1; 
	if(app->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT)
		app->render->camera.y -= speed;

	if(app->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)
		app->render->camera.y += speed;

	if(app->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
		app->render->camera.x -= speed;

	if(app->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
		app->render->camera.x += speed;

	// Draw map
	app->map->Draw();

	//Draw GUI
	app->guiManager->Draw();

	// Update Anim
	imgAnim.Update(dt);
	LOG("%f",dt);
	return true;
}

// Called each loop iteration
bool Scene::PostUpdate()
{
	bool ret = true;

	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			app->render->DrawTexture(img, i * 200, j * 200, &imgAnim.GetCurrentFrame());
		}
	}

	return ret;
}


bool Scene::OnGuiMouseClickEvent(GuiControl* control)
{

	switch (control->type)
	{
	case GuiControlType::BUTTON:
	{
		//Checks the GUI element ID
		if (control->id == 1) 
		{
			LOG("Click on button 1");
		}

		if (control->id == 2)
		{
			LOG("Click on button 2");
		}
		
	}
	//Other cases here

	default: break;
	}

	return true;
}

// Called before quitting
bool Scene::CleanUp()
{
	LOG("Freeing scene");

	app->tex->UnLoad(img);

	imgAnim.DeleteAnim();

	return true;
}
