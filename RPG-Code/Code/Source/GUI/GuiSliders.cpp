#include "GuiSliders.h"
#include "Render.h"
#include "App.h"
#include "Audio.h"
#include "Collisions.h"
#include "Render.h"
#include "Textures.h"
#include "GuiManager.h"
#include "Camera.h"
#include "ModuleQFonts.h"

GuiSlider::GuiSlider(uint32 id, SDL_Rect bounds, const char* text, bool autoDraw) : GuiControl(GuiControlType::SLIDER, id)
{
	this->bounds = bounds;
	this->text = text;
	this->autoDraw = autoDraw;

	canClick = true;
	drawBasic = false;
	app->guiManager->keyb = false;

	if (autoDraw)
	{
		sliderTexture = app->tex->Load("Assets/gui/button_default.png");
		sliderIddle.PushBack({ 0, 0, 74, 28 });
		sliderPressed.PushBack({ 74, 0, 74, 28 });

		sliderAnim = &sliderIddle;
	}
}

GuiSlider::~GuiSlider()
{

}

bool GuiSlider::Update(float dt)
{
	if (state != GuiControlState::DISABLED)
	{

		// Update the state of the GUiButton according to the mouse position
		int mouseX, mouseY;
		app->input->GetMousePosition(mouseX, mouseY);

		// Adjust Mouse position to camera
		mouseX -= app->camera->GetPos().x / 2;
		mouseY -= app->camera->GetPos().y / 2;

		if ((mouseX > bounds.x) && (mouseX < (bounds.x + bounds.w)) &&
			(mouseY > bounds.y) && (mouseY < (bounds.y + bounds.h)))
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
			if (!app->guiManager->keyb) state = GuiControlState::NORMAL;
	}


	return false;
}

bool GuiSlider::Draw(Render* render)
{
	if (autoDraw)
	{
		switch (state)
		{
		case GuiControlState::DISABLED: render->DrawRectangle(bounds, 0, 0, 0, 255);
			break;
		case GuiControlState::NORMAL:render->DrawRectangle(bounds, 0, 255, 0, 0);
			break;
		case GuiControlState::FOCUSED:render->DrawRectangle(bounds, 0, 0, 255, 0);
			break;
		case GuiControlState::PRESSED:render->DrawRectangle(bounds, 0, 0, 255, 0);
			sliderRect = { bounds.x, bounds.y,mouseX - bounds.x, bounds.h };
			innerRect.x = sliderRect.w + sliderRect.x;
			innerRect.x -= innerRect.w / 2;
			innerRect.y = sliderRect.y + sliderRect.h / 4;
			innerRect.h = sliderRect.h + sliderRect.h / 2;
			innerRect.w = innerRect.h;
			break;
		case GuiControlState::SELECTED:render->DrawRectangle(bounds, 0, 255, 255, 0);
			break;
		default:
			break;
		}
	}

	else
	{
		switch (state)
		{
		case GuiControlState::DISABLED: render->DrawRectangle(bounds, 0, 0, 0, 255);
			break;
		case GuiControlState::NORMAL:render->DrawRectangle(bounds, 0, 255, 0, 0);
			break;
		case GuiControlState::FOCUSED:render->DrawRectangle(bounds, 0, 0, 255, 0);
			break;
		case GuiControlState::PRESSED:render->DrawRectangle(bounds, 0, 0, 255, 0);
			sliderRect = { bounds.x, bounds.y,mouseX - bounds.x, bounds.h };
			innerRect.x = sliderRect.w + sliderRect.x;
			innerRect.x -= innerRect.w / 2;
			innerRect.y = sliderRect.y + sliderRect.h / 4;
			innerRect.h = sliderRect.h + sliderRect.h / 2;
			innerRect.w = innerRect.h;
			break;
		case GuiControlState::SELECTED:render->DrawRectangle(bounds, 0, 255, 255, 0);
			break;
		default:
			break;
		}
	}

	if (state == GuiControlState::PRESSED)
	{
		value = (int)((float)sliderRect.w / (float)(float)bounds.w / (float)maxValue);
	}

	if (!autoDraw)
	{
		render->DrawRectangle(sliderRect, 0, 0, 255, 255);
		if (sliderRect.x == bounds.x)
		{
			render->DrawRectangle(innerRect, 0, 50, 50, 50);
		}
	}
	else
	{
		render->DrawRectangle(sliderRect, 0, 0, 255, 255);
		if (sliderRect.x == bounds.x)
		{
			render->DrawRectangle(innerRect, 0, 50, 50, 50);
		}
	}
	return false;
}