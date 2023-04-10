#include "Woman.h"
#include "GamePlayer.h"

Woman::Woman(const char* filename, float x, float y, int hp, int atk, int vw, int n, int wwn, int hhn, int id) : GameMonster(filename,x,y,hp,atk,vw,n,wwn,hhn,id)
{
	speed = 1;
	coin = 10;
}
Woman::~Woman()
{
	close();
}

void Woman::update(GamePlayer* player)
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
			clk = clk % 500 + 1;

			if (clk > 0 && clk <= 100)
				Move(0, 1);
			else if (clk > 100 && clk <= 200)
				Move(1, 0);
			else if (clk > 200 && clk <= 300)
				Move(0, -1);
			else if (clk > 300 && clk <= 400)
				Move(-1, 0);
			else
				Move(0, 0);
		}

		if (!checkCollision())
			pos += move, realpos += move;
		attack(player);
	}
}
void Woman::attack(GamePlayer* player)
{
	int choose, x = player->getxpos(), y = player->getypos();
	ATKcooldown %= 25;

	if (ATKcooldown == 0)
	{
		if (x <= pos.x + 31 + range && x >= pos.x - range && y <= pos.y + 31 + range && y >= pos.y - range)
		{
			player->bleeding(ATK);
			//cout << player->ShowHP() << endl;
		}
		else if (x <= pos.x + 31 + range && x >= pos.x - range && y + 31 <= pos.y + 31 + range && y + 31 >= pos.y - range)
		{
			player->bleeding(ATK);
			//cout << player->ShowHP() << endl;
		}
		else if (x + 31 <= pos.x + 31 + range && x + 31 >= pos.x - range && y <= pos.y + 31 + range && y >= pos.y - range)
		{
			player->bleeding(ATK);
			//cout << player->ShowHP() << endl;
		}
		else if (x + 31 <= pos.x + 31 + range && x + 31 >= pos.x - range && y + 31 <= pos.y + 31 + range && y + 31 >= pos.y - range)
		{
			player->bleeding(ATK);
			//cout << player->ShowHP() << endl;
		}
	}

	ATKcooldown++;
}

void Woman::close()
{
	delete hpbar;
	hpbar = nullptr;
	SDL_DestroyTexture(monsTex);
	monsTex = nullptr;
	SDL_RemoveTimer(timerID);
}