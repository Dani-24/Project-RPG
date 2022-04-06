#include "App.h"
#include "ModuleQFonts.h"
#include "Log.h"
#include "Render.h"
#include "Textures.h"
#include "Audio.h"

#define DELAY_TIME 5

// v1.0.0
// + Increible Modulo hecho por DANI para poner Texto, requiere una fuente y varios royos para encenderlo

// v2.0.0
// + Ahora se puede usar con hacer un Enable()/Disable() desde otro modulo
 
// v3.0.0
// + Novedad: Texto con delay

ModuleQFonts::ModuleQFonts(App* application, bool start_enabled) : Module(application, start_enabled)
{
	name.Create("fonts");
}

ModuleQFonts::~ModuleQFonts()
{
}

bool ModuleQFonts::Awake(pugi::xml_node& config) {

	// Load audio effect path from config

	return true;
}

bool ModuleQFonts::Start() {

	LOG("Init Module Fonts");
	if (TTF_Init() == -1) {
		LOG("Fonts can't initialize || TTF_Init: %s", TTF_GetError());
		return false;
	}

	app->font->LoadFont("Assets/fonts/DungeonFont.ttf", 25);

	soundEffect = app->audio->LoadFx("Assets/audio/sfx/fx_select_next_2.wav");

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

void ModuleQFonts::DrawTextDelayed(const char* textToRender , int x, int y, Uint8 r, Uint8 g, Uint8 b) {
	
	if (time <= 0) {

		length.Create(textToRender);
		sprintf_s(text, textToRender);

		if (N < length.Length()) {

			textToPrint[N] = text[N];

			DrawText(textToPrint, x, y, r, g, b);

			time = DELAY_TIME;
			N++;

			app->audio->PlayFx(soundEffect);
		}
		else {
			if (showLOG == true) {
				LOG("Text delay finished");
				showLOG = false;
			}

			// When the delay finishes this allows us to continue seeing the text
			DrawText(textToPrint, x, y, r, g, b);
		}
	}
	else {
		time--;

		// This shows the text while delay time
		DrawText(textToPrint, x, y, r, g, b);
	}
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

void ModuleQFonts::CleanFonts() {
	showLOG = true;

	fontTexture = nullptr;
	fontSurface = NULL;

	length.Clear();
	memset(text, 0, sizeof text);
	memset(textToPrint, 0, sizeof textToPrint);

	time = N = 0;
}

void ModuleQFonts::UnloadFont()
{
	TTF_CloseFont(font);

	app->tex->UnLoad(fontTexture);

	font = NULL; // to be safe..

	LOG("Fonts unloaded");
}

bool ModuleQFonts::CleanUp() {
	
	UnloadFont();
	TTF_Quit();

	return true;
}