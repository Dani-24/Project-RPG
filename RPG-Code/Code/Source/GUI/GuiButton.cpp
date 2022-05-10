#include "GuiButton.h"
#include "Render.h"
#include "App.h"
#include "Audio.h"
#include "Collisions.h"
#include "Render.h"
#include "Textures.h"
#include "GuiManager.h"

GuiButton::GuiButton(uint32 id, iPoint position, const char* text, bool smol, bool drawButton) : GuiControl(GuiControlType::BUTTON, id)
{
	this->position = position;

	this->bounds.x = position.x;
	this->bounds.y = position.y;

	this->text = text;

	canClick = true;
	this->drawButton = drawButton;

	app->guiManager->keyb = false;

	if (smol == true) {
		// Smol button
		buttonTexture = app->tex->Load("Assets/gui/inventory/button_mini.png");

		buttonIddle.PushBack({ 0, 0, 41, 28 });
		buttonPressed.PushBack({ 41, 0, 41, 28 });

		bounds.w = 41;
		bounds.h = 28;

		font = app->font->LoadFont(15);
	}
	else {
		// Default button
		buttonTexture = app->tex->Load("Assets/gui/inventory/button_default.png");

		buttonIddle.PushBack({ 0, 0, 74, 28 });
		buttonPressed.PushBack({ 74, 0, 74, 28 });

		bounds.w = 74;
		bounds.h = 28;

		font = app->font->LoadFont();
	}

	buttonIddle.loop = false;
	buttonPressed.loop = false;

	buttonAnim = &buttonIddle;
}

GuiButton::~GuiButton()
{
	app->font->UnloadFonts(font);
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
	// ==========================================
	//  Draw the right button depending on state
	// ==========================================
	if (drawButton) {
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

			if (buttonAnim != &buttonIddle) {
				buttonAnim = &buttonIddle;
			}
			render->DrawTexture(buttonTexture, bounds.x, bounds.y, &buttonAnim->GetCurrentFrame());

			// Selector
			render->DrawTexture(app->guiManager->selector, bounds.x - 15, bounds.y + bounds.h / 2 - 6);

			break;
		case GuiControlState::PRESSED:

			if (buttonAnim != &buttonPressed) {
				buttonAnim = &buttonPressed;
			}
			render->DrawTexture(buttonTexture, bounds.x, bounds.y, &buttonAnim->GetCurrentFrame());

			// Clicker
			render->DrawTexture(app->guiManager->clicker, bounds.x + bounds.w / 2 - 6, bounds.y + bounds.h / 2 + 6);

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

	}

	if (state != GuiControlState::DISABLED) {
		if (state == GuiControlState::FOCUSED) {
			app->font->DrawText(text.GetString(), bounds.x, bounds.y, font, { 255,255,255 });	// White
		}
		else {
			app->font->DrawText(text.GetString(), bounds.x, bounds.y, font, { 0,0,0 });	// Black
		}
	}
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

	return false;
}