#include "GuiManager.h"
#include "App.h"
#include "Textures.h"
#include "Render.h"

#include "GuiButton.h"
#include "Audio.h"

GuiManager::GuiManager(App* application, bool start_enabled) : Module(application, start_enabled)
{
	name.Create("guiManager");
}

GuiManager::~GuiManager() {}

bool GuiManager::Start()
{
	selector = app->tex->Load("Assets/gui/controllers/selector.png");
	clicker = app->tex->Load("Assets/gui/controllers/click.png");
	return true;
}

GuiControl* GuiManager::CreateGuiControl(GuiControlType type, int id, const char* text, SDL_Rect bounds, Module* observer, bool autoDraw, SDL_Rect sliderBounds)
{
	// Create a GUI control and add it to the list of controls

	GuiControl* control = nullptr;

	// Call the constructor according to the GuiControlType
	switch (type)
	{
	case GuiControlType::BUTTON:
		control = new GuiButton(id, bounds, text, autoDraw);
		break;
	case GuiControlType::SLIDER:
		control = new GuiButton(id, bounds, text, autoDraw);
		break;
	// More Gui Controls can go here

	default:
		break;
	}

	//Set the observer
	control->SetObserver(observer);
	//control->SetTexture(texture);

	// Created GuiControls are added to the list of controls
	if (control != nullptr) controls.add(control);

	return control;
}

bool GuiManager::Update(float dt)
{	
	accumulatedTime += dt;
	if (accumulatedTime >= updateMsCycle) doLogic = true;

	UpdateAll(dt,doLogic);

	if (doLogic == true)
	{
		accumulatedTime = 0.0f;
		doLogic = false;
	}
	
	return true;
}

bool GuiManager::UpdateAll(float dt, bool doLogic) {

	if (doLogic) {

		ListItem<GuiControl*>* control = controls.start;

		while (control != nullptr)
		{
			control->data->Update(dt);
			control = control->next;
		}
	}
	return true; 

}

bool GuiManager::PostUpdate() {
	Draw();
	return true;
}

bool GuiManager::Draw() {

	ListItem<GuiControl*>* control = controls.start;

	while (control != nullptr)
	{
		control->data->Draw(app->render);
		control = control->next;
	}

	return true;

}

bool GuiManager::CleanUp()
{
	ListItem<GuiControl*>* control = controls.start;

	while (control != nullptr)
	{
		RELEASE(control);
	}

	return true;

	return false;
}

void GuiManager::ChangeButtonText(int id, const char* newText) {
	ListItem<GuiControl*>* control = controls.start;

	for (control; control != NULL; control = control->next) {
		if (control->data->id == id) {

			LOG("Changed %d button text from %s to %s", id, control->data->text.GetString(), newText);

			control->data->text.Clear();
			control->data->text.Create(newText);
			break;
		}
	}

}