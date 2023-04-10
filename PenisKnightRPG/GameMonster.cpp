#include "GameMonster.h"
#include "GamePlayer.h"
#include "HealthPoint.h"
#include <time.h>

GameMonster::GameMonster(const char* filename, float x, float y,int hp, int atk,int vw,int id) : GameObject(filename, x, y)
{
	srand(time(NULL));
	monsTex = TM->LoadTexture(filename);
	hpbar = new HealthPoint("assets/hpbar_red.png", pos.x - 9, pos.y + 32);

	pos.x = (int)realpos.x % 640;
	pos.y = (int)realpos.y % 480;

	HP = HP_MAX = hp;
	ATK = atk;
	range = (atk + 1) / 2;
	speed = 1;
	ATKcooldown = 0;
	alive = false;
	view = vw;

	coin = 10;
	code = id;
}

GameMonster::GameMonster(const char* filename, float x, float y,int hp, int atk, int vw, int n, int wwn, int hhn,int id) : GameObject(filename, x, y, n, wwn, hhn)
{
	srand(time(NULL));
	monsTex = TM->LoadTexture(filename);
	hpbar = new HealthPoint("assets/hpbar_red.png", pos.x - 9, pos.y + 32);

	pos.x = (int)realpos.x % 640;
	pos.y = (int)realpos.y % 480;

	HP = HP_MAX = hp;
	ATK = atk;
	range = (atk + 1) / 2;
	speed = 1;
	ATKcooldown = 0;
	alive = false;
	view = vw;

	coin = 10;
	code = id;
}

GameMonster::~GameMonster() {
	close();
}

void GameMonster::update(GamePlayer* player)
{
	int xDis, yDis;
	xDis = (int)(pos.x - player->getxpos());
	yDis = (int)(pos.y - player->getypos());
	bool xbiggerthany = (fabs(xDis) >= fabs(yDis));

	checkPlayerDie(player);
	isAlive();

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

void GameMonster::render()
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
}

void GameMonster::close()
{
	delete hpbar;
	hpbar = nullptr;
	SDL_DestroyTexture(monsTex);
	monsTex = nullptr;
	SDL_RemoveTimer(timerID);
}

void GameMonster::rez(float x, float y)
{
	ATKcooldown = 0;
	alive = true;
	HP = HP_MAX;
	setrealXY(x, y);
}

Uint32 GameMonster::changeData(Uint32 interval, void* param)
{
	GameMonster* m = (GameMonster*)param;

	if (m->t != 0)
	{
		m->frame = (m->frame + 1) % m->wn + m->frametime;  // image frame	
		return interval;
	}
	else
	{
		return 0;
	}
}

void GameMonster::Move(float xx, float yy)
{
	int x, y;
	x = (int)xx, y = (int)yy;
	SDL_RemoveTimer(timerID);

	move.x = xx * speed;
	move.y = yy * speed;
	startTimer(7);
	if (x == 0 && y == 0)
		SDL_RemoveTimer(timerID);
	else if (x > 0 && y == 0)
		frametime = 0;
	else if (x < 0 && y == 0)
		frametime = 4;
	else if (x == 0 && y > 0)
		frametime = 8;
	else if (x == 0 && y < 0)
		frametime = 12;
	else
		;
}

void GameMonster::checkPlayerDie(GamePlayer* player)
{
	if (player->ShowHP() <= 0) {
		alive = false;
		//SDL_RemoveTimer(timerID);
	}
		
}

void GameMonster::attack(GamePlayer* player)
{
	int choose, x = player->getxpos(), y = player->getypos();
	ATKcooldown %= 25;

	if (ATKcooldown == 0)
	{
		if (x <= pos.x + 31 + range && x >= pos.x -range && y <= pos.y + 31 + range && y >= pos.y - range)
		{
			player->bleeding(ATK);
			cout << player->ShowHP() << endl;
		}
		else if (x <= pos.x + 31 + range && x >= pos.x - range && y + 31 <= pos.y + 31 + range && y + 31 >= pos.y - range)
		{
			player->bleeding(ATK);
			cout << player->ShowHP() << endl;
		}
		else if (x + 31 <= pos.x + 31 + range && x + 31 >= pos.x - range && y <= pos.y + 31 + range && y >= pos.y - range)
		{
			player->bleeding(ATK);
			cout << player->ShowHP() << endl;
		}
		else if (x + 31 <= pos.x + 31 + range && x + 31 >= pos.x - range && y + 31 <= pos.y + 31 + range && y + 31 >= pos.y - range)
		{
			player->bleeding(ATK);
			cout << player->ShowHP() << endl;
		}
	}
	
	ATKcooldown++;
}
int GameMonster::getStage()
{
	return -1;
}

