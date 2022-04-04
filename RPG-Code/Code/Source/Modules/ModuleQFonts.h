#ifndef __MODULE_QFONTS_H__
#define __MODULE_QFONTS_H__

#include "Module.h"
#include "SDL_ttf/include/SDL_ttf.h"

class ModuleQFonts :public Module {
public:
	ModuleQFonts(App* application, bool start_enabled = true);

	~ModuleQFonts();

	bool Start();

	void LoadFont(const char* fontPath, int size = 30);

	void UnloadFont();

	void DrawText(const char* textToRender, int x, int y, Uint8 r = 255, Uint8 g = 255, Uint8 b = 255);

private:
	void RenderText(const char* textToRender,int x, int y, Uint8 r = 255, Uint8 g = 255, Uint8 b = 255);

public:
	bool CleanUp();
	
private:
	SDL_Color color;
	TTF_Font* font;

	SDL_Texture* fontTexture;
	SDL_Surface* fontSurface;
};

#endif