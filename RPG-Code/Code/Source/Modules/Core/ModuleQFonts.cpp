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
//
// v4.0.0
// + Capacidad de tener varias fuentes con diferentes tamaños
// Ahora LoadFont devuelve una fuente por lo que necesita crear fuente en cada modulo donde se usa

#define FONT_PATH "Assets/fonts/DungeonFont.ttf"

ModuleQFonts::ModuleQFonts(App* application, bool start_enabled) : Module(application, start_enabled)
{
	name.Create("fonts");
}

ModuleQFonts::~ModuleQFonts()
{
}

bool ModuleQFonts::Awake(pugi::xml_node& config) {

	// Load audio effect path from config ?

	LOG("Init Fonts");

	if (TTF_Init() == -1) {
		LOG("Fonts can't initialize || TTF_Init: %s", TTF_GetError());
		return false;
	}

	return true;
}

bool ModuleQFonts::Start() {

	LOG("Start Module Fonts");
	
	soundEffect = app->audio->LoadFx("Assets/audio/sfx/fx_select_next_2.wav");

	return true;
}

TTF_Font* ModuleQFonts::LoadFont(int size) {

	return TTF_OpenFont(FONT_PATH, size);
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
void ModuleQFonts::DrawText(const char* textToRender, int x, int y, TTF_Font* font, SDL_Color color) {
	RenderText("                                                                                             ", 0, 0, font, color);
	RenderText(textToRender, x, y, font, color);
}

void ModuleQFonts::DrawTextDelayed(const char* textToRender , int x, int y, TTF_Font* font, SDL_Color color) {
	int cont = 0;
	// Comprueba si el texto ya existe y si no lo añade a la lista
	for (ListItem<DelayedTexts*>* c = delayedTexts.start; c != NULL; c = c->next) {
		if (textToRender == c->data->originalText && x == c->data->position.x && y == c->data->position.y) {
			if (c->data->time <= 0) {

				c->data->length.Create(textToRender);
				sprintf_s(c->data->text, textToRender);

				if (c->data->N < c->data->length.Length()) {

					c->data->textToPrint[c->data->N] = c->data->text[c->data->N];

					DrawText(c->data->textToPrint, x, y, font, color);

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
					DrawText(c->data->textToPrint, x, y, font, color);
				}
			}
			else {
				c->data->time--;

				// This shows the text while delay time
				DrawText(c->data->textToPrint, x, y, font, color);
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
void ModuleQFonts::RenderText(const char* textToRender, int x, int y, TTF_Font* font, SDL_Color color) {

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

void ModuleQFonts::CleanTexts() {

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

void ModuleQFonts::UnloadFonts(TTF_Font* font)
{
	CleanTexts();

	TTF_CloseFont(font);

	app->tex->UnLoad(fontTexture);

	LOG("Fonts unloaded");
}

bool ModuleQFonts::CleanUp() {
	
	TTF_Quit();

	return true;
}