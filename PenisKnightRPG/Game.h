#pragma once
#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <vector>
using namespace std;

class Game
{
public:
	Game();
	~Game();

	void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
	void handleEvent();
	void update();
	void render();
	void reset();
	void clear();
	void clean();
	void weapon_turn_on() { isAttack = true;}
	void weapon_turn_off() { isAttack = false; }

	bool running() { return isRunning;}
	bool getisAttack() { return isAttack; }
	static SDL_Renderer* renderer;
	bool isRunning = 1;
	
	bool opening = 1;
	bool play = 0;
	bool weapon_select = 0;
	bool pause = 0;
	bool win = 0;
	bool intro = 0;
	bool shop = 0;
	bool die = 0;

	bool smap_on = 0;

	SDL_Window* getWin() { return window; }
private:
	SDL_Window* window;
	SDL_Texture* cointex;
	int game_coin;
	char game_coin_s[10];
	bool isAttack;
};

