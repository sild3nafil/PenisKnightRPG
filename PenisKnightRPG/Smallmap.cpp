#include "smallmap.h"
#include<SDL.h>
#include"constants.h"
#include <SDL2_gfxPrimitives.h>
#include"Game.h"
Smallmap::Smallmap()
{
	boss_logo = TM->LoadTexture("assets/boss_logo.png");
}

void Smallmap::render(GamePlayer *player)
{
	
	SDL_Rect startout;
	startout.x = WIDTH / 4 * 3 - 10;
	startout.y = HEIGHT / 4 * 3 - 10;
	startout.w = WIDTH / 4 + 10;
	startout.h = HEIGHT / 4 + 10;
	int x = WIDTH / 4 * 3 - 10;
	int y = HEIGHT / 4 * 3 - 10;
	int w = WIDTH / 4 + 10;
	int h = HEIGHT / 4 + 10;
	

	TM->DrawFilledRect(x, y, w, h, 0xDD, 0xDD, 0xDD, 0xFF);
	x += 5;
	y += 5;
	w -= 10;
	w /= 5;
	h -= 10;
	h /= 5;
	for (int i = 0; i < 3; i++)
	{
		TM->DrawFilledRect(x, y + h * 6 / 15 + h * i * 2, w * 5, h * 6 / 15, 0xAA, 0xAA, 0xAA, 0xFF);
		TM->DrawFilledRect(x + w * 8 / 20 + i * w * 2, y, w * 6 / 20, h * 5, 0xAA, 0xAA, 0xAA, 0xFF);

	}
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			TM->DrawFilledRect(x + w * i * 2, y + h * j * 2, w, h, 0xAA, 0xAA, 0xAA, 0xFF);
			if (i == 1 && j == 1)
				TM->Draw(boss_logo, { 0,0,16,16 }, { x + w * i * 2, y + h * j * 2, w, h });
		}
	}
	TM->DrawFilledRect(x+(int)(player->getrealxpos()/4/5), y+(int)(player->getrealypos() / 4 / 5), w*8/100, h *6/75, 0xFF, 0x00, 0x00, 0xFF);
}