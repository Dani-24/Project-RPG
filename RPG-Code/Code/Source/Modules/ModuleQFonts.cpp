#include "App.h"
#include "ModuleQFonts.h"
#include "Log.h"
#include "Render.h"
#include "Textures.h"

// Increible Modulo hecho por Dani para poner Texto, requiere una fuente y varios royos para encenderlo

ModuleQFonts::ModuleQFonts(App* application, bool start_enabled) : Module(application, start_enabled)
{
	name.Create("fonts");
}

ModuleQFonts::~ModuleQFonts()
{
}

bool ModuleQFonts::Start() {
	LOG("Init Module Fonts");
	if (TTF_Init() == -1) {
		LOG("Fonts can't initialize || TTF_Init: %s", TTF_GetError());
		return false;
	}

	return true;
}

void ModuleQFonts::LoadFont(const char* fontPath, int size) {
	font = TTF_OpenFont(fontPath, size);
	if (!font) {
		LOG("Error loading font || TTF_OpenFont: %s", TTF_GetError());
	}
	else {
		LOG("Fonts loaded");
	}
}

// Print a lot of space or texts will fuse and random bullshit 
void ModuleQFonts::DrawText(const char* textToRender, int x, int y, Uint8 r, Uint8 g, Uint8 b) {
	RenderText("                                                                   ", 0, 0);
	RenderText(textToRender, x, y, r, g, b);
}

// This method is private
void ModuleQFonts::RenderText(const char* textToRender, int x, int y, Uint8 r , Uint8 g , Uint8 b) {
	// Text Color
	color = { r,g,b };

	// Create the text on surface
	if (!(fontSurface = TTF_RenderText_Blended(font, textToRender, color))) {	// Blended means more quality than Solid (TTF_RenderText_Solid / TTF_RenderText_Blended )
		LOG("Error Rendering Text || TTF_OpenFont: %s", TTF_GetError());
	}
	else {
		if (fontTexture == nullptr) {
			// Transform the text surface to texture
			fontTexture = SDL_CreateTextureFromSurface(app->render->renderer, fontSurface);
		}
		else {
			SDL_UpdateTexture(fontTexture, nullptr, fontSurface->pixels, fontSurface->pitch);
		}

		// Draw the text at X, Y
		app->render->DrawTexture(fontTexture, x, y);
	}
	SDL_FreeSurface(fontSurface);
}

void ModuleQFonts::UnloadFont()
{
	TTF_CloseFont(font);

	app->tex->UnLoad(fontTexture);

	font = NULL; // to be safe..

	LOG("Fonts unloaded");
}

bool ModuleQFonts::CleanUp() {

	TTF_Quit();

	fontTexture = nullptr;
	fontSurface = NULL;

	return true;
}