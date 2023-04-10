#include "Rat.h"
#include "GamePlayer.h"
#include <SDL2_gfxPrimitives.h>

Rat::Rat(const char* filename, float x, float y, int hp, int atk, int vw, int n, int wwn, int hhn,int id) : GameMonster(filename, x, y, hp, atk, vw, n, wwn, hhn,id)
{
	speed = 2;
	coin = 1;
	effect = new Mixer("audio/boom.mp3", EFFECT);
}
Rat::~Rat()
{
	close();
}

void Rat::update(GamePlayer* player)
{
	int xDis, yDis;
	static int clock = 0;
	xDis = (int)(pos.x - player->getxpos());
	yDis = (int)(pos.y - player->getypos());
	bool xbiggerthany = (fabs(xDis) >= fabs(yDis));

	checkPlayerDie(player);
	if (!isAlive())
		reload();

	if (alive&&!boom)
	{
		clock %= 3;
		if(clock!=0)
		{
			if (xbiggerthany)
			{
				if (xDis < 0)
					Move(1, 0);
				else if (xDis == 1)
					Move(0, 0);
				else
					Move(-1, 0);
			}
			else
			{
				if (yDis < 0) {
					Move(0, 1);
				}
				else if (yDis == 0) {
					Move(0, 0);
				}
				else {
					Move(0, -1);
				}
			}
		}
		else
		{
			switch (rand() % 5)
			{
			case 0:
				Move(0, 1);
				break;
			case 1:
				Move(1, 0);
				break;
			case 2:
				Move(0, -1);
				break;
			case 3:
				Move(-1, 0);
				break;
			case 4:
				Move(0, 0);
				break;
			}
		}

		if (!checkCollision())
			pos += move, realpos += move;
		clock++;
	}
	else if(!alive && !boom)
	{
		attack(player);
		boom = true;
	}
}

void Rat::attack(GamePlayer* player)
{
	effect->playEffect(ONE, -1);
	float xc = player->getxpos() + 15;
	float yc = player->getypos() + 15;
	double dis = sqrt(pow(xc - pos.x, 2) + pow(yc - pos.y, 2));
	if(dis<=view)
		player->bleeding(ATK);
	//TM->DrawCircle(pos.x + 15, pos.y + 15, view, 220, 0, 0, 180);
}

void Rat::close()
{
	delete hpbar;
	hpbar = nullptr;
	effect->close();
	delete effect;
	effect = nullptr;
	SDL_DestroyTexture(monsTex);
	monsTex = nullptr;
	SDL_RemoveTimer(timerID);
}

