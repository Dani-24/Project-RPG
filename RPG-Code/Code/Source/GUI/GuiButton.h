#ifndef __GUIBUTTON_H__
#define __GUIBUTTON_H__

#include "GuiControl.h"

#include "Point.h"
#include "SString.h"
#include "Render.h"
#include "Textures.h"
#include "Animation.h"
#include "ModuleQFonts.h"

struct SDL_Texture;

class GuiButton : public GuiControl
{
public:

	GuiButton(uint32 id, iPoint position, const char* text, bool smol = false, bool drawButton = true);
	virtual ~GuiButton();

	bool Update(float dt);
	bool Draw(Render* render);

	int mouseX, mouseY;
	unsigned int click;

	bool canClick = true;
	bool drawButton;

	SDL_Texture* buttonTexture;
	Animation buttonIddle;
	Animation buttonPressed;
	Animation* buttonAnim;
};

#endif // __GUIBUTTON_H__