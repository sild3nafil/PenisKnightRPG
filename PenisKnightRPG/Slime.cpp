#include "Slime.h"
#include "HealthPoint.h"

Slime::Slime(const char* filename, float x, float y, int hp, int atk, int vw, int n, int wwn, int hhn, int id) : GameMonster(filename, x, y, hp, atk, vw, n, wwn, hhn, id)
{
	speed = 2;
	coin = 5;
	stopMoving = false;

	for (int i = 0; i < MAX_BULLET; i++)
		bullet[i] = new Bullet("assets/beanshot.png", 10);
	effect_shot = new Mixer("audio/slimeshot.mp3", EFFECT);
}
Slime::~Slime()
{
	close();
}
void Slime::update(GamePlayer* player)
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
		attack(player);
		if (!stopMoving)
		{
			if (xDis <= view && yDis <= view)
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
				clk = clk % 250 + 1;

				if (clk > 0 && clk <= 50)
					Move(0, 1);
				else if (clk > 50 && clk <= 100)
					Move(1, 0);
				else if (clk > 100 && clk <= 150)
					Move(0, -1);
				else if (clk > 150 && clk <= 200)
					Move(-1, 0);
				else
					Move(0, 0);
			}

			if (!checkCollision())
				pos += move, realpos += move;
		}
	}
	for (int i = 0; i < MAX_BULLET; i++)
		bullet[i]->update(player);
}
void Slime::render()
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
		hpbar->render();
	}
	for (int i = 0; i < MAX_BULLET; i++)
		bullet[i]->render();
}
void Slime::attack(GamePlayer* player)
{
	int x = player->getxpos(), y = player->getypos();
	vector2 dir;
	ATKcooldown %= 25;

	if (ATKcooldown == 0)
	{
		if (x <= pos.x + 31 + view && x >= pos.x - view && y <= pos.y + 31 + view && y >= pos.y - view)
		{
			dir.setXY(x - pos.x, y - pos.y);
			rad = dir.getRad();
			stopMoving = true;
			shot();
		}
		else if (x <= pos.x + 31 + view && x >= pos.x - view && y + 31 <= pos.y + 31 + view && y + 31 >= pos.y - view)
		{
			dir.setXY(x - pos.x, y - pos.y);
			rad = dir.getRad();
			stopMoving = true;
			shot();
		}
		else if (x + 31 <= pos.x + 31 + view && x + 31 >= pos.x - view && y <= pos.y + 31 + view && y >= pos.y - view)
		{
			dir.setXY(x - pos.x, y - pos.y);
			rad = dir.getRad();
			stopMoving = true;
			shot();
		}
		else if (x + 31 <= pos.x + 31 + view && x + 31 >= pos.x - view && y + 31 <= pos.y + 31 + view && y + 31 >= pos.y - view)
		{
			dir.setXY(x - pos.x, y - pos.y);
			rad = dir.getRad();
			stopMoving = true;
			shot();
		}
		else
			stopMoving = false;
	}

	ATKcooldown++;
}
void Slime::close()
{
	delete hpbar;
	hpbar = nullptr;
	SDL_DestroyTexture(monsTex);
	monsTex = nullptr;
	SDL_RemoveTimer(timerID);
	effect_shot->close();
	delete effect_shot;
	effect_shot = nullptr; 
	for (int i = 0; i < MAX_BULLET; i++)
		bullet[i]->close();
}
void Slime::rez(float x, float y)
{
	ATKcooldown = 0;
	alive = true;
	HP = HP_MAX;
	setrealXY(x, y);
	stopMoving = false;

	for (int i = 0; i < MAX_BULLET; i++)
		bullet[i]->reload();
}
void Slime::shot()
{
	effect_shot->playEffect(ONE, -1);
	for (int i = 0; i < MAX_BULLET; i++)
	{
		if (!bullet[i]->Active())
		{
			bullet[i]->loadMap(mapItem, mapProperty);
			bullet[i]->fire(realpos.x + 15, realpos.y + 15, rad);
			break;
		}
	}
}
