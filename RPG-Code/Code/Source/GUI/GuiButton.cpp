#include "GuiButton.h"
#include "Render.h"
#include "App.h"
#include "Audio.h"
#include "Collisions.h"
#include "Render.h"
#include "Textures.h"
#include "GuiManager.h"

GuiButton::GuiButton(uint32 id, SDL_Rect bounds, const char* text, bool smol) : GuiControl(GuiControlType::BUTTON, id)
{
	this->bounds = bounds;
	this->text = text;

	canClick = true;
	drawBasic = false;
	app->guiManager->keyb = false;

	if (smol == true) {
		// Smol button
		buttonTexture = app->tex->Load("Assets/gui/inventory/button_mini.png");

		buttonIddle.PushBack({ 0, 28, 74, 28 });
		buttonPressed.PushBack({ 74, 28, 74, 28 });
	}
	else {
		// Default button
		buttonTexture = app->tex->Load("Assets/gui/inventory/button_default.png");

		buttonIddle.PushBack({ 0, 28, 41, 28 });
		buttonPressed.PushBack({ 41, 28, 41, 28 });
	}

	buttonIddle.loop = false;
	buttonPressed.loop = false;

	buttonAnim = &buttonIddle;
}

GuiButton::~GuiButton()
{
//a
}

bool GuiButton::Update(float dt)
{
	if (state != GuiControlState::DISABLED)
	{
		// Update the state of the GUiButton according to the mouse position
		int mouseX, mouseY;
		app->input->GetMousePosition(mouseX, mouseY);

		if ((mouseX > bounds.x ) && (mouseX < (bounds.x + bounds.w )) &&
			(mouseY > bounds.y ) && (mouseY < (bounds.y + bounds.h )))
		{
			app->guiManager->keyb = false;
			state = GuiControlState::FOCUSED;

			if (app->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KeyState::KEY_REPEAT)
			{
				state = GuiControlState::PRESSED;
			}

			// If mouse button pressed -> Generate event!
			if (app->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KeyState::KEY_UP)
			{
				NotifyObserver();
			}
		}
		else 
			if(!app->guiManager->keyb) state = GuiControlState::NORMAL;
	}
	
	return false;
}

bool GuiButton::Draw(Render* render)
{

	// =================
	//  DEBUG COLLIDERS
	// =================
	if (app->collisions->debug) {
		switch (state)
		{
		case GuiControlState::DISABLED:
			render->DrawRectangle(bounds, 0, 0, 0, 0);
			break;

		case GuiControlState::NORMAL:
			render->DrawRectangle(bounds, 255, 0, 0, 100);
			break;

		case GuiControlState::FOCUSED:
			render->DrawRectangle(bounds, 255, 255, 255, 100);
			break;

		case GuiControlState::PRESSED:
			render->DrawRectangle(bounds, 255, 255, 255, 150);
			break;

		case GuiControlState::SELECTED:
			render->DrawRectangle(bounds, 0, 255, 0, 100);
			break;

		default:
			break;
		}
	}

	// ==========================================
	//  Draw the right button depending on state
	// ==========================================
	switch (state)
	{
	case GuiControlState::DISABLED:
		break;
	case GuiControlState::NORMAL:

		if (buttonAnim != &buttonIddle) {
			buttonAnim = &buttonIddle;
		}
		render->DrawTexture(buttonTexture, bounds.x, bounds.y, &buttonAnim->GetCurrentFrame());

		break;
	case GuiControlState::FOCUSED:

		render->DrawTexture(app->guiManager->selector, bounds.x - 15, bounds.y + bounds.h / 2 - 6);

		if (buttonAnim != &buttonIddle) {
			buttonAnim = &buttonIddle;
		}
		render->DrawTexture(buttonTexture, bounds.x, bounds.y, &buttonAnim->GetCurrentFrame());

		break;
	case GuiControlState::PRESSED:

		render->DrawTexture(app->guiManager->clicker, bounds.x + bounds.w / 2 - 6, bounds.y + bounds.h / 2 + 6);

		if (buttonAnim != &buttonPressed) {
			buttonAnim = &buttonPressed;
		}
		render->DrawTexture(buttonTexture, bounds.x, bounds.y, &buttonAnim->GetCurrentFrame());

		break;
	case GuiControlState::SELECTED:

		if (buttonAnim != &buttonIddle) {
			buttonAnim = &buttonIddle;
		}
		render->DrawTexture(buttonTexture, bounds.x, bounds.y, &buttonAnim->GetCurrentFrame());

		break;
	default:
		break;
	}

	if (state != GuiControlState::DISABLED) {
		app->font->DrawText(text.GetString(), bounds.x, bounds.y, {0,0,0});
	}

	return false;
}