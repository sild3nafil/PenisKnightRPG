#pragma once
#include <SDL_mixer.h>

class Mixer
{
	public:
		Mixer();
		Mixer(const char* p, int t);
		void close();
		bool load();
		void setPath(const char* p);
		void setType(int t);

		bool isPlaying();
		void play(int n);
		bool isPaused();
		void resume();
		void pause(); 
		void stop();
		void playEffect(int n);
		void playEffect(int n, int c);
		void stopEffect(int n);

	private:
		// The SDL_mixer data type for music is Mix_Music
		// https://www.libsdl.org/projects/SDL_mixer/docs/SDL_mixer_86.html
		// The music that will be played
		Mix_Music* music;

		// The SDL_mixer data type for short sounds is Mix_Chunk.
		// https://www.libsdl.org/projects/SDL_mixer/docs/SDL_mixer_85.html
		// The sound effects that will be used
		Mix_Chunk* effect;

		char* path;
		int type;
};

