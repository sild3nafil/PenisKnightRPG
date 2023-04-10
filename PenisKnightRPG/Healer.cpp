#include "Healer.h"
#include "GamePlayer.h"
#include "HealthPoint.h"

Healer::Healer(const char* filename, float x, float y, int hp, int atk, int vw, int n, int wwn, int hhn, int id) : GameMonster(filename, x, y, hp, atk, vw, n, wwn, hhn, id)
{
	speed = 1;
	coin = 333;
}
Healer::~Healer()
{
	close();
}
void Healer::update(GamePlayer* player)
{
	int xDis, yDis;
	xDis = (int)(pos.x - player->getxpos());
	yDis = (int)(pos.y - player->getypos());
	bool xbiggerthany = (fabs(xDis) >= fabs(yDis));

	checkPlayerDie(player);
	if (!isAlive())
		reload();

	if (alive)
	{
		playerpos.setXY(player->getxpos(), player->getypos());
		if (xbiggerthany)
		{
			if (xDis < -128)
				Move(1, 0);
			else if (xDis >= -128 && xDis <= 128)
			{
				Move(0, 0);
			}
			else
				Move(-1, 0);
		}
		else
		{
			if (yDis < -128) {
				Move(0, 1);
			}
			else if (yDis >= -128 && yDis<= 128) {
				Move(0, 0);
			}
			else {
				Move(0, -1);
			}
		}
		if (recover_cd == 0)
			recover();
		recover_cd = (recover_cd + 1) % 45;
		if (!checkCollision())
			pos += move, realpos += move;
	}
}
void Healer::render()
{
	hpbar->update(this);
	wPic = frame % wn;
	hPic = frame / wn;

	srcRect.x = 32 * wPic;
	srcRect.y = 32 * hPic;
	srcRect.w = 32;
	srcRect.h = 32;
	dRect.x = (int)pos.x;
	dRect.y = (int)pos.y;
	dRect.w = srcRect.w;
	dRect.h = srcRect.h;

	if (alive)
	{
		TM->Draw(monsTex, srcRect, dRect);
		TM->DrawLine(pos.x+15, pos.y+15, playerpos.x+15, playerpos.y+15, 255, 191, 0, 100);
		hpbar->render();
	}
}

void Healer::close()
{
	delete hpbar;
	hpbar = nullptr;
	SDL_DestroyTexture(monsTex);
	monsTex = nullptr;
	SDL_RemoveTimer(timerID);
}
void Healer::recover()
{
	HP += 25;
}
void Healer::bleeding(int atk)
{
	static int i = 0;
	if (i == 0)
	{
		HP -= atk;
	}
	i = (i + 1) % 3;
}
