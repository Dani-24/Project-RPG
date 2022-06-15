#include "GuiButton.h"
#include "Render.h"
#include "App.h"
#include "Audio.h"
#include "Collisions.h"
#include "Render.h"
#include "Textures.h"
#include "GuiManager.h"
#include "Camera.h"
#include "ModuleQFonts.h"
#include "Battle.h"
GuiButton::GuiButton(uint32 id, SDL_Rect bounds, const char* text, bool autoDraw) : GuiControl(GuiControlType::BUTTON, id)
{
	this->bounds = bounds;
	this->text = text;
	this->autoDraw = autoDraw;

	canClick = true;
	drawBasic = false;
	app->guiManager->keyb = false;

	if (autoDraw) {
		buttonTexture = app->tex->Load("Assets/gui/button_default.png");

		buttonIddle.PushBack({ 0, 0, 74, 28 });
		buttonPressed.PushBack({ 74, 0, 74, 28 });

		buttonAnim = &buttonIddle;
	}
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

		// Adjust Mouse position to camera
		mouseX -= app->camera->GetPos().x / 2;
		mouseY -= app->camera->GetPos().y / 2;

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
			if(app->battle->isEnabled())app->battle->gamepad3 = false, app->battle->gamepad2=false, app->battle->gamepad1=false;
		}
		else 
			if(!app->guiManager->keyb) state = GuiControlState::NORMAL;
	}

	

	if (cont % 3 == 0) {

		if (xp)xd++;
		else if (!xp)xd--;
	}
	if (xd <= 0)xp = true;
	else if (xd >= 3)xp = false;
	
	cont ++;
	if (cont >500)cont = 0;

	return false;
}

bool GuiButton::Draw(Render* render)
{

	if (autoDraw) {
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
			//render->DrawTexture(app->guiManager->selector, bounds.x - 15, bounds.y + bounds.h / 2 - 6);

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

		// Text
		if (state != GuiControlState::DISABLED) {
			if (state != GuiControlState::PRESSED) {
				app->font->DrawText(text.GetString(), bounds.x, bounds.y, { 0,0,0 });	// Black
			}
			else {
				app->font->DrawText(text.GetString(), bounds.x, bounds.y + 1, { 0,0,0 });	// Black
			}
		}
	}

	// COLLIDER DEBUG BOX: Draw the right button depending on state
	 
		switch (state)
		{
		case GuiControlState::DISABLED:
		{
			if (app->collisions->debug)render->DrawRectangle(bounds, 0, 0, 0, 0);
		} break;

		case GuiControlState::NORMAL:
		{
			if (app->collisions->debug)render->DrawRectangle(bounds, 255, 0, 0, 100);

		} break;

		case GuiControlState::FOCUSED:
		{
			if (app->collisions->debug)render->DrawRectangle(bounds, 255, 255, 255, 100);

			//render->DrawRectangle({bounds.x-100,bounds.y,bounds.w,bounds.h}, 255, 255, 255, 100);
			render->DrawTexture(app->guiManager->selector, bounds.x - 15 - xd, bounds.y + bounds.h/2-6 );
			
	//		LOG("%f", xd);

		} break;

		case GuiControlState::PRESSED:
		{
			if (app->collisions->debug)render->DrawRectangle(bounds, 255, 255, 255, 150);
			render->DrawTexture(app->guiManager->clicker, bounds.x + bounds.w / 2 -6, bounds.y + bounds.h / 2 + 6);
		} break;

		case GuiControlState::SELECTED:if (app->collisions->debug) render->DrawRectangle(bounds, 0, 255, 0, 100);
			break;

		default:
			break;
		}
		
	
	return false;
}