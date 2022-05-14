#include "App.h"
#include "ModuleQFonts.h"
#include "Log.h"
#include "Render.h"
#include "Textures.h"
#include "Audio.h"

// ============================
//		Novedades e INFO
// ============================

// v1.0.0
// + Increible Modulo hecho por DANI TOLEDO para poner Texto mediante la libreria SDL_TTF. Requiere una fuente .ttf (FONT_PATH)
//
// v2.0.0
// + Novedad: Ahora se puede usar con hacer un Enable()/Disable() desde otro modulo.
// -> Requiere especificar la fuente utilizada en el Start() de ESTE modulo
//
// v3.0.0
// + Novedad: Texto con delay (Limitado a un uso por Scena)
//
// v3.5.0
// + Ahora DrawTextDelayed() se stackea en una lista por lo que se puede imprimir mas de un texto con delay por Scene.
// + Ahora los espacios del texto con delay no suenan
// -> No es compatible con movimientos, en ese caso usar el DrawText() normal. 

#define FONT_PATH "Assets/fonts/DungeonFont.ttf"
#define FONT_SIZE 25

ModuleQFonts::ModuleQFonts(App* application, bool start_enabled) : Module(application, start_enabled)
{
	name.Create("fonts");
}

ModuleQFonts::~ModuleQFonts()
{
}

bool ModuleQFonts::Awake(pugi::xml_node& config) {

	// Load audio effect path from config ?

	return true;
}

bool ModuleQFonts::Start() {

	LOG("Init Module Fonts");
	if (TTF_Init() == -1) {
		LOG("Fonts can't initialize || TTF_Init: %s", TTF_GetError());
		return false;
	}

	app->font->LoadFont(FONT_PATH, FONT_SIZE);

	soundEffect = app->audio->LoadFx("Assets/audio/sfx/fx_select_next_2.wav");

	return true;
}

void ModuleQFonts::LoadFont(const char* fontPath, int size) {

	fontDefault = TTF_OpenFont(fontPath,size);

	if (!fontDefault) {
		LOG("Error loading font || TTF_OpenFont: %s", TTF_GetError());
	}
	else {
		LOG("Default Font loaded");
	}

	/*fontSmol = TTF_OpenFont(fontPath, size / 2);

	if (!fontSmol) {
		LOG("Error loading Smol font || TTF_OpenFont: %s", TTF_GetError());
	}
	else {
		LOG("Smol Font loaded");
	}

	fontBig = TTF_OpenFont(fontPath, size * 2);

	if (!fontBig) {
		LOG("Error loading Big font || TTF_OpenFont: %s", TTF_GetError());
	}
	else {
		LOG("Big Font loaded");
	}*/
}

void ModuleQFonts::AddToList(const char* textToRender, int x, int y) {
	DelayedTexts* txt = new DelayedTexts();

	txt->originalText = textToRender;
	txt->position = { x, y };

	delayedTexts.add(txt);
	txt = nullptr;
	delete txt;
}

// Print a lot of space or texts will fuse and random bullshit 
void ModuleQFonts::DrawText(const char* textToRender, int x, int y, SDL_Color color, bool getScale, int zoom) {
	RenderText("                                                                                             ", 0, 0, color, getScale, zoom);
	RenderText(textToRender, x, y, color, getScale, zoom);
}

void ModuleQFonts::DrawTextDelayed(const char* textToRender , int x, int y, SDL_Color color, bool getScale, int zoom) {
	int cont = 0;
	// Comprueba si el texto ya existe y si no lo añade a la lista
	for (ListItem<DelayedTexts*>* c = delayedTexts.start; c != NULL; c = c->next) {
		if (textToRender == c->data->originalText && x == c->data->position.x && y == c->data->position.y) {
			if (c->data->time <= 0) {

				c->data->length.Create(textToRender);
				sprintf_s(c->data->text, textToRender);

				if (c->data->N < c->data->length.Length()) {

					c->data->textToPrint[c->data->N] = c->data->text[c->data->N];

					DrawText(c->data->textToPrint, x, y, color, getScale ,zoom);

					c->data->time = DELAY_TIME;
					c->data->N++;

					// Mute at spaces
					if (c->data->text[c->data->N] != ' ') {
						app->audio->PlayFx(soundEffect);
					}
				}
				else {
					if (c->data->show_log == true) {
						LOG("Text delay finished");
						c->data->show_log = false;
					}

					// When the delay finishes this allows us to continue seeing the text
					DrawText(c->data->textToPrint, x, y, color, getScale, zoom);
				}
			}
			else {
				c->data->time--;

				// This shows the text while delay time
				DrawText(c->data->textToPrint, x, y, color, getScale, zoom);
			}
			break;
		}
		cont++;
	}
	if (cont == delayedTexts.count()) {
		AddToList(textToRender, x, y);
	}
}

// This method is privated
void ModuleQFonts::RenderText(const char* textToRender, int x, int y, SDL_Color color, bool getScale, int zoom) {

	// Create the text on surface 
	if (!(fontSurface = TTF_RenderText_Blended(fontDefault, textToRender, color))) {	// Blended means more quality than Solid (TTF_RenderText_Solid / TTF_RenderText_Blended )
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
		app->render->DrawTexture(fontTexture, x, y, 0, zoom, getScale);
	}
	SDL_FreeSurface(fontSurface);
}

void ModuleQFonts::CleanFonts() {

	ListItem<DelayedTexts*>* c = delayedTexts.start;

	while (c != NULL) {

		c->data->length.Clear();
		memset(c->data->text, NULL, sizeof c->data->text);
		memset(c->data->textToPrint, NULL, sizeof c->data->textToPrint);

		c->data->time = c->data->N = NULL;

		c = c->next;
	}
	delayedTexts.clear();

	fontTexture = nullptr;
	fontSurface = NULL;
}

void ModuleQFonts::UnloadFonts()
{
	TTF_CloseFont(fontDefault);

	app->tex->UnLoad(fontTexture);

	LOG("Fonts unloaded");
}

bool ModuleQFonts::CleanUp() {
	
	UnloadFonts();
	TTF_Quit();

	return true;
}