#ifndef __GUIBUTTON_H__
#define __GUIBUTTON_H__

#include "GuiControl.h"

#include "Point.h"
#include "SString.h"
#include "Render.h"
#include "Textures.h"
#include "Animation.h"

struct SDL_Texture;

class GuiButton : public GuiControl
{
public:

	GuiButton(uint32 id, SDL_Rect bounds, const char* text, bool autoDraw);
	virtual ~GuiButton();


	bool Update(float dt);
	bool Draw(Render* render);

	int mouseX, mouseY;
	unsigned int click;

	bool canClick = true;
	bool drawBasic = false;

	bool autoDraw;

	SDL_Texture* buttonTexture;
	Animation buttonIddle, buttonPressed, *buttonAnim;
};

#endif // __GUIBUTTON_H__