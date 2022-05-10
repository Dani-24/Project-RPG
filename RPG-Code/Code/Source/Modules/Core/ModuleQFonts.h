#ifndef __MODULE_QFONTS_H__
#define __MODULE_QFONTS_H__

#include "Module.h"
#include "SDL_ttf/include/SDL_ttf.h"
#include "Point.h"
#include "List.h"

#define FONT_SIZE 25

#define TEXT_LENGTH 100
#define DELAY_TIME 2

struct DelayedTexts {

	// Text
	const char* originalText;

	// Position
	iPoint position;

	// Delay variables
	SString length;
	char text[TEXT_LENGTH] = { "" };
	char textToPrint[TEXT_LENGTH] = { "" };

	int time = 0;
	int N = 0;

	bool show_log = true;
};

class ModuleQFonts :public Module {
public:
	ModuleQFonts(App* application, bool start_enabled = true);

	~ModuleQFonts();

	bool Start();

	bool Awake(pugi::xml_node& config);

	bool CleanUp();

public:
	// Load font and set Size
	TTF_Font* LoadFont(int size = FONT_SIZE);

	// Your text, Position: X, Y, color {R,G,B}
	void DrawText(const char* textToRender, int x, int y, TTF_Font* font, SDL_Color color = { 255,255,255 });

	// Your text, Position: X, Y, color {R,G,B}
	void DrawTextDelayed(const char* textToRender, int x, int y, TTF_Font* font, SDL_Color color = { 255,255,255 });

	// Call on each module that uses fonts CleanUp()
	void UnloadFonts(TTF_Font* font);

	// Free Delayed texts used memory
	void CleanTexts();

private:
	void RenderText(const char* textToRender, int x, int y, TTF_Font* font, SDL_Color color);

	void AddToList(const char* textToRender, int x, int y);

private:
	List<DelayedTexts*> delayedTexts;

	SDL_Texture* fontTexture;
	SDL_Surface* fontSurface;

	uint soundEffect;
};

#endif