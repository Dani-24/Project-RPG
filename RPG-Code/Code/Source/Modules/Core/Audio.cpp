#include "App.h"
#include "Audio.h"
#include "AssetsManager.h"

#include "Defs.h"
#include "Log.h"

#include "SDL/include/SDL.h"
#include "SDL_mixer/include/SDL_mixer.h"

Audio::Audio(App* application, bool start_enabled) : Module(application, start_enabled)
{
	music = NULL;
	name.Create("audio");
}

// Destructor
Audio::~Audio()
{}

// Called before render is available
bool Audio::Awake(pugi::xml_node& config)
{
	LOG("Loading Audio Mixer");
	bool ret = true;
	SDL_Init(0);

	if (SDL_InitSubSystem(SDL_INIT_AUDIO) < 0)
	{
		LOG("SDL_INIT_AUDIO could not initialize! SDL_Error: %s\n", SDL_GetError());
		active = false;
		ret = true;
	}

	int flags = MIX_INIT_OGG;
	int init = Mix_Init(flags);

	if ((init & flags) != flags)
	{
		LOG("Could not initialize Mixer lib. Mix_Init: %s", Mix_GetError());
		active = false;
		ret = true;
	}

	// Initialize SDL_mixer
	if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		LOG("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
		active = false;
		ret = true;
	}

	// LOAD VOLUME FROM CONFIG

	vol = config.child("music").attribute("value").as_int();
	volFX = config.child("sfx").attribute("value").as_int();

	ChangeVolume(vol);
	ChangeFXVolume(volFX);

	return ret;
}

// Called before quitting
bool Audio::CleanUp()
{
	if (!active)
		return true;

	LOG("Freeing sound FX, closing Mixer and Audio subsystem");

	if (music != NULL)
	{
		Mix_FreeMusic(music);
	}

	ListItem<Mix_Chunk*>* item;
	for (item = fx.start; item != NULL; item = item->next)
		Mix_FreeChunk(item->data);

	fx.clear();

	Mix_CloseAudio();
	Mix_Quit();
	SDL_QuitSubSystem(SDL_INIT_AUDIO);

	return true;
}

// Play a music file
bool Audio::PlayMusic(const char* path, float fade_time, bool remember, int rar)
{
	bool ret = true;
	

	if (remember) {
		lastSongPlayed = path;
	}

	if (!active)
		return false;

	if (music != NULL)
	{
		if (fade_time > 0.0f)
		{
			Mix_FadeOutMusic(int(fade_time * 50.0f));
		}
		else
		{
			Mix_HaltMusic();
		}

		// this call blocks until fade out is done
		Mix_FreeMusic(music);
	}

	if(rar==0)music = Mix_LoadMUS(path);
	else if(rar==1) music = Mix_LoadMUS_RW(app->assman->Load(path), 1);

	if (music == NULL)
	{
		LOG("Cannot load music %s. Mix_GetError(): %s\n", path, Mix_GetError());
		ret = false;
	}
	else
	{
		if (fade_time > 0.0f)
		{
			if (Mix_FadeInMusic(music, -1, (int)(fade_time * 50.0f)) < 0)
			{
				LOG("Cannot fade in music %s. Mix_GetError(): %s", path, Mix_GetError());
				ret = false;
			}
		}
		else
		{
			if (Mix_PlayMusic(music, -1) < 0)
			{
				LOG("Cannot play in music %s. Mix_GetError(): %s", path, Mix_GetError());
				ret = false;
			}
		}
	}

	LOG("Successfully playing %s", path);
	return ret;
}

void Audio::PlayLastSong() {
	PlayMusic(lastSongPlayed, 5);
}

// Load WAV
unsigned int Audio::LoadFx(const char* path, int rar)
{
	unsigned int ret = 0;
	

	if (!active)
		return 0;

	Mix_Chunk* chunk;

	if(rar==0) chunk = Mix_LoadWAV(path);
	else if(rar==1) chunk = Mix_LoadWAV_RW(app->assman->Load(path), 1);

	if (chunk == NULL)
	{
		LOG("Cannot load wav %s. Mix_GetError(): %s", path, Mix_GetError());
	}
	else
	{
		fx.add(chunk);
		ret = fx.count();
	}

	return ret;
}

// Play WAV
bool Audio::PlayFx(unsigned int id, int repeat)
{
	bool ret = false;

	if (!active)
		return false;

	if (id > 0 && id <= fx.count())
	{
		Mix_PlayChannel(-1, fx[id - 1], repeat);
	}

	return ret;
}

// Play a music file from rar
bool Audio::_PlayMusic(const char* path, float fade_time, bool remember)
{
	bool ret = true;

	if (remember) {
		lastSongPlayed = path;
	}

	if (!active)
		return false;

	if (music != NULL)
	{
		if (fade_time > 0.0f)
		{
			Mix_FadeOutMusic(int(fade_time * 50.0f));
		}
		else
		{
			Mix_HaltMusic();
		}

		// this call blocks until fade out is done
		Mix_FreeMusic(music);
	}

	/*music = Mix_LoadMUS(path);*/
	music = Mix_LoadMUS_RW(app->assman->Load(path), 1);

	if (music == NULL)
	{
		LOG("Cannot load music %s. Mix_GetError(): %s\n", path, Mix_GetError());
		ret = false;
	}
	else
	{
		if (fade_time > 0.0f)
		{
			if (Mix_FadeInMusic(music, -1, (int)(fade_time * 50.0f)) < 0)
			{
				LOG("Cannot fade in music %s. Mix_GetError(): %s", path, Mix_GetError());
				ret = false;
			}
		}
		else
		{
			if (Mix_PlayMusic(music, -1) < 0)
			{
				LOG("Cannot play in music %s. Mix_GetError(): %s", path, Mix_GetError());
				ret = false;
			}
		}
	}

	LOG("Successfully playing %s", path);
	return ret;
}

// Load WAV from rar
unsigned int Audio::_LoadFx(const char* path)
{
	unsigned int ret = 0;

	if (!active)
		return 0;

	Mix_Chunk* chunk = Mix_LoadWAV_RW(app->assman->Load(path), 1);

	if (chunk == NULL)
	{
		LOG("Cannot load wav %s. Mix_GetError(): %s", path, Mix_GetError());
	}
	else
	{
		fx.add(chunk);
		ret = fx.count();
	}

	return ret;
}

// Change Music volume
void Audio::ChangeVolume(int volume) {
	Mix_VolumeMusic(volume);
}

// Change Sound Effects volume
void Audio::ChangeFXVolume(int volume) {
	Mix_Volume(-1, volume);
}

// Load Game State
bool Audio::LoadState(pugi::xml_node& data)
{
	vol = data.child("music").attribute("value").as_int();
	volFX = data.child("sfx").attribute("value").as_int();

	ChangeVolume(vol);
	ChangeFXVolume(volFX);

	return true;
}

// Save Game State
bool Audio::SaveState(pugi::xml_node& data) const
{
	data.append_child("music").append_attribute("value") = vol;
	data.append_child("sfx").append_attribute("value") = volFX;

	return true;
}