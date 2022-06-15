#ifndef __GUISLIDER_H__
#define __GUISLIDER_H__

#include "GuiControl.h"
#include "Point.h"
#include "SString.h"
#include "Render.h"
#include "Textures.h"
#include "Animation.h"

struct SDL_Texture;

class GuiSlider : public GuiControl
{
public:

	GuiSlider(uint32 id, SDL_Rect bounds, const char* text, bool autoDraw);
	virtual ~GuiSlider();

	bool Update(float dt);
	bool Draw(Render* render);

	int mouseX, mouseY;
	unsigned int click;

	int minValue;
	int maxValue;

	bool canClick = true;
	bool drawBasic = false;

	bool autoDraw;

	SDL_Texture* sliderTexture;
	Animation sliderIddle, sliderPressed, * sliderAnim;


	SDL_Rect sliderRect = { 0, 0, 0, 0 };
	SDL_Rect innerRect;

	int value;


};






#endif // __GUISLIDER_H__
