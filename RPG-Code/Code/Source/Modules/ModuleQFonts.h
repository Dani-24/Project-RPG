#ifndef __MODULE_QFONTS_H__
#define __MODULE_QFONTS_H__

#include "Module.h"
#include "SDL_ttf/include/SDL_ttf.h"

class ModuleQFonts :public Module {
public:
	ModuleQFonts(App* application, bool start_enabled = true);

	~ModuleQFonts();

	bool Start();

	bool Awake(pugi::xml_node& config);

	void LoadFont(const char* fontPath, int size = 30);

	void UnloadFont();

	void DrawText(const char* textToRender, int x, int y, Uint8 r = 255, Uint8 g = 255, Uint8 b = 255);

	void DrawTextDelayed(const char* textToRender, int x, int y, Uint8 r = 255, Uint8 g = 255, Uint8 b = 255);

private:
	void RenderText(const char* textToRender,int x, int y, Uint8 r = 255, Uint8 g = 255, Uint8 b = 255);

public:
	bool CleanUp();
	
private:
	SDL_Color color;
	TTF_Font* font;

	SDL_Texture* fontTexture;
	SDL_Surface* fontSurface;

	// ====================
	//		 DELAY
	// ====================

	SString length;
	char text[100] = { "" };
	char textToPrint[100] = { "" };

	int time = 0;
	int N = 0;

	bool showLOG = true;
	uint soundEffect;
};

#endif