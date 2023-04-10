/* Alphar: 2022.02.20 */
#include <stdio.h>
#include "Game.h"
#include "SDL2_gfxPrimitives.h"

Game* game = nullptr;

int main(int argc, char* args[])
{
	const int FPS = 60;
	const int frameDelay = 1000 / FPS; //ºÕ¼Æ

	Uint32 frameStart;
	int frameTime;
	
	game = new Game; // create game
	game->init("PenisKnightBeta", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280/2, 960/2, true); //initialize

	while (game->running())
	{
		frameStart = SDL_GetTicks(); //start time

		game->handleEvent();
		game->update();
		game->render();
		

		frameTime = SDL_GetTicks() - frameStart; 
		//period of whole one procedure,it really quick
		//if we didnt check it 
		//the charactors will move super fast and lag sometimes

		if (frameDelay > frameTime)
			SDL_Delay(frameDelay - frameTime);
		//determine stable fps and uncertern frametime 
		//on theory,fps is much longer than framtime a period time
		//so we can make sure that the frametime afterward is close to fps
		//(frameDelay-frameTime) is similar to frameDelay
		//because frameTime is too quick
	}

	game->clean(); //close the window

	return 0;
}