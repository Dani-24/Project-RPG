#ifndef __AUDIO_H__
#define __AUDIO_H__

#include "Module.h"

#define DEFAULT_MUSIC_FADE_TIME 30.0f

struct _Mix_Music;
struct Mix_Chunk;

class Audio : public Module
{
public:

	Audio(App* application, bool start_enabled = true);
	virtual ~Audio();

	bool Awake(pugi::xml_node&);

	bool CleanUp();

	// Play a music file
	bool PlayMusic(const char* path, float fadeTime = DEFAULT_MUSIC_FADE_TIME, bool remember = true, int rar=1);

	

	void PlayLastSong();

	// Load a WAV in memory
	unsigned int LoadFx(const char* path, int rar=0);

	

	// Play a previously loaded WAV
	bool PlayFx(unsigned int fx, int repeat = 0);

	// Change music volume (from 0 to 128)
	void ChangeVolume(int volume = 128);

	// Change sfx volume (from 0 to 128)
	void ChangeFXVolume(int volume = 128);

	// Load / Save
	bool LoadState(pugi::xml_node&);
	bool SaveState(pugi::xml_node&) const;

private:

	_Mix_Music* music;
	List<Mix_Chunk*>	fx;

	const char* lastSongPlayed;

public:

	int vol, volFX;
};

#endif // __AUDIO_H__