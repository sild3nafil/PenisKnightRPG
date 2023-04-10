#include "Mixer.h"
#include <stdio.h>
#include <string.h>
#include "constants.h"

Mixer::Mixer()
{
}

Mixer::Mixer(const char *p, int t)
{
	setPath(p);
	setType(t);
	load();
}

void Mixer::close()
{
	// Free the sound effects	
	// https://www.libsdl.org/projects/SDL_mixer/docs/SDL_mixer_24.html
	Mix_FreeChunk(effect);

	// Free the music
	// https://www.libsdl.org/projects/SDL_mixer/docs/SDL_mixer_56.html
	Mix_FreeMusic(music);
}

bool Mixer::load()
{	
	if (type == MUSIC)
	{
		// Load music
		// https://www.libsdl.org/projects/SDL_mixer/docs/SDL_mixer_55.html
		// This can load WAVE, MOD, MIDI, OGG, MP3, FLAC, and any file that you use a command to play with.
		music = Mix_LoadMUS(path);
		if (music == NULL)
		{
			printf("Failed to load music! SDL_mixer Error: %s\n", Mix_GetError());
			return false;
		}
	}
	
	if (type == EFFECT)
	{
		// Load sound effects
		// https://www.libsdl.org/projects/SDL_mixer/docs/SDL_mixer_19.html
		// This can load WAVE, AIFF, RIFF, OGG, and VOC files.
		effect = Mix_LoadWAV(path);
		if (effect == NULL)
		{
			printf("Failed to load sound effect! SDL_mixer Error: %s\n", Mix_GetError());
			return false;
		}
	}	

	return true;
}

void Mixer::setPath(const char* p)
{
	path = new char[strlen(p) + 1];
	strcpy_s(path, strlen(p) + 1, p);
}

void Mixer::setType(int t)
{
	type = t;
}

bool Mixer::isPlaying()
{
	// Tells you if music is actively playing, or not.
	// Returns: Zero if the music is not playing, or 1 if it is playing.
	// https://www.libsdl.org/projects/SDL_mixer/docs/SDL_mixer_71.html
	return Mix_PlayingMusic();
}

void Mixer::play(int n)
{
	// Play the music
	// The second parameter:
	// number of times to play through the music.
	// 0 repeat playing the music zero times...
	// -1 plays the music forever(or as close as it can get to that)
	// https://www.libsdl.org/projects/SDL_mixer/docs/SDL_mixer_57.html
	Mix_VolumeMusic(30);
	Mix_PlayMusic(music, n);
}

/* The following functions cannot indicate specified Music, */
/* it only control current Music. */

bool Mixer::isPaused()
{
	// Tells you if music is paused, or not.
	// Returns : Zero if music is not paused. 1 if it is paused
	// https://www.libsdl.org/projects/SDL_mixer/docs/SDL_mixer_72.html
	return Mix_PausedMusic();
}

void Mixer::resume()
{
	// Resume the music
	// https://www.libsdl.org/projects/SDL_mixer/docs/SDL_mixer_63.html
	Mix_ResumeMusic();
}
		
void Mixer::pause()
{
	// Pause the music
	// https://www.libsdl.org/projects/SDL_mixer/docs/SDL_mixer_62.html
	Mix_PauseMusic();
}
	
void Mixer::stop()
{
	// Stop the music
	// https://www.libsdl.org/projects/SDL_mixer/docs/SDL_mixer_67.html
	Mix_HaltMusic();
}


/* The following functions for Effect/Chunk can indicate specified Effect/Chunk. */

void Mixer::playEffect(int n)
{
	// https://www.libsdl.org/projects/SDL_mixer/docs/SDL_mixer_28.html
	// The first argument is the channel you want to use to play it. 
	// Since we don't care which channel it comes out of, 
	// we set the channel to -1 which will use the nearest available channel. 
	// The second argument is the sound effect and last argument is the number of times to repeat the effect. 
	// We only want it to play once per button press, so we have it repeat 0 times.
	Mix_Volume(-1, 25);
	Mix_PlayChannel(-1, effect, n);
}

void Mixer::playEffect(int n, int c)
{	
	Mix_Volume(-1, 25);
	Mix_PlayChannel(c, effect, n);
}

void Mixer::stopEffect(int n)
{
	// https://www.libsdl.org/projects/SDL_mixer/docs/SDL_mixer_34.html#SEC34
	// halt playback on channel n
	// if n=-1, halt playback on all channels
	Mix_HaltChannel(n);
}