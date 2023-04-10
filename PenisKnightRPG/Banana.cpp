#include "Banana.h"

Banana::Banana() : WeaponItem()
{
	bananaTex = TM->LoadTexture("assets/banana.png");
	speed = 5;
	atk = 7*7+7+7;
	reload();

	srcRect.x = srcRect.y = 0;
	srcRect.w = srcRect.h = 32;
	dRect.w = dRect.h = 32;
}
Banana::Banana(const char* filename, int a) : WeaponItem()
{
	bananaTex = TM->LoadTexture(filename);
	speed = 4;
	atk = a;
	reload();

	srcRect.x = srcRect.y = 0;
	srcRect.w = srcRect.h = 32;
	dRect.w = dRect.h = 32;
}
Banana::~Banana()
{
	SDL_RemoveTimer(timerID);
	delete bananaTex;
	bananaTex = NULL;
}

void Banana::update(vector<GameMonster*> mst,GamePlayer* player)
{
	if (active)
	{
		if (checkCollision())
			rebound = true;
		for (int i = 0; i < mst.size(); i++)
		{
			if (harmMons(mst[i]))
			{
				rebound = true;
				break;
			}
		}

		if (cooldown > 0)
		{
			if (!rebound)
			{
				pos += move * speed;
				realpos += move * speed;
				cooldown--;
			}
			else
			{
				pos -= move * speed;
				realpos -= move * speed;
				cooldown = 0;
			}
		}
		else
		{
			if (arrive(player))
				reload();

			vector2 dir;
			double r;
			dir.setXY(player->getxpos() - pos.x, player->getypos() - pos.y);
			r = dir.getRad();
			move.setXY(1, 1);
			move *= r;
			pos += move * speed;
			realpos += move * speed;
		}
	}
}
void Banana::update(GamePlayer* player)
{
	if (active)
	{
		if (checkCollision())
			rebound = true;
	
		if (harmPlayer(player))
		{
			rebound = true;
		}
		
		if (cooldown > 0)
		{
			if (!rebound)
			{
				pos += move * speed;
				realpos += move * speed;
				cooldown--;
			}
			else
			{
				pos -= move * speed;
				realpos -= move * speed;
				cooldown = 0;
			}
		}
		else
		{
			if (arrive())
				reload();

			pos -= move * speed;
			realpos -= move * speed;
		}
	}
}
void Banana::render()
{
	wPic = frame % wn;
	hPic = frame / wn;

	srcRect.x = 32 * wPic;
	srcRect.y = 32 * hPic;
	srcRect.w = 32;
	srcRect.h = 32;
	dRect.x = (int)(pos.x - 15);
	dRect.y = (int)(pos.y - 15);
	dRect.w = srcRect.w;
	dRect.h = srcRect.h;

	if (active)
		TM->Draw(bananaTex, srcRect, dRect);
}
void Banana::throw_Banana(float x, float y, double r)
{
	realpos.setXY(x, y);
	pos.x = (int)realpos.x % 640;
	pos.y = (int)realpos.y % 480;
	originpos.setXY(pos.x, pos.y);
	move.setXY(1, 1);
	move = r * move;

	cooldown = 77;
	startTimer(10);
	active = true;
	rebound = false;
}
void Banana::reload()
{
	stopTimer();
	active = false;
	rebound = false;
}
bool Banana::harmMons(GameMonster* mst)
{
	float x1, x2, y1, y2;
	x1 = pos.x, x2 = pos.x + 31, y1 = pos.y, y2 = pos.y + 31;

	if (x1 >= mst->getxpos() && x1 <= mst->getxpos() + 32 && y1 >= mst->getypos() && y1 <= mst->getypos() + 32)
	{
		mst->bleeding(atk);
		return true;
	}
	if (x2 >= mst->getxpos() && x2 <= mst->getxpos() + 32 && y1 >= mst->getypos() && y1 <= mst->getypos() + 32)
	{
		mst->bleeding(atk);
		return true;
	}
	if (x1 >= mst->getxpos() && x1 <= mst->getxpos() + 32 && y2 >= mst->getypos() && y2 <= mst->getypos() + 32)
	{
		mst->bleeding(atk);
		return true;
	}
	if (x2 >= mst->getxpos() && x2 <= mst->getxpos() + 32 && y2 >= mst->getypos() && y2 <= mst->getypos() + 32)
	{
		mst->bleeding(atk);
		return true;
	}
	return false;
}
bool Banana::harmPlayer(GamePlayer* player)
{
	float x1, x2, y1, y2;
	x1 = pos.x, x2 = pos.x + 31, y1 = pos.y, y2 = pos.y + 31;

	if (x1 >= player->getxpos() && x1 <= player->getxpos() + 32 && y1 >= player->getypos() && y1 <= player->getypos() + 32)
	{
		player->bleeding(atk);
		return true;
	}
	if (x2 >= player->getxpos() && x2 <= player->getxpos() + 32 && y1 >= player->getypos() && y1 <= player->getypos() + 32)
	{
		player->bleeding(atk);
		return true;
	}
	if (x1 >= player->getxpos() && x1 <= player->getxpos() + 32 && y2 >= player->getypos() && y2 <= player->getypos() + 32)
	{
		player->bleeding(atk);
		return true;
	}
	if (x2 >= player->getxpos() && x2 <= player->getxpos() + 32 && y2 >= player->getypos() && y2 <= player->getypos() + 32)
	{
		player->bleeding(atk);
		return true;
	}
	return false;
}

bool Banana::checkCollision()
{
	int Indextop, Indexdown, Indexright, Indexleft;
	float xm, ym, cx, cy;
	Indextop = (int)realpos.y / 32;
	Indexdown = (int)(realpos.y + 7) / 32;
	Indexright = (int)(realpos.x + 7) / 32;
	Indexleft = (int)realpos.x / 32;
	xm = move.x;
	ym = move.y;
	cx = realpos.x + 3;
	cy = realpos.y + 3;
	/*printf("%d %d %d %d\n", Indextop, Indexdown, Indexright, Indexleft);*/

	if (Outta())
		return true;

	if (xm > 0)
	{
		if (ym > 0)
		{
			if (mapProperty[Indexdown][Indexright] == true || mapProperty[Indexdown][Indexleft] == true)
			{
				return true;
			}
		}
		else if (ym < 0)
		{
			if (mapProperty[Indextop][Indexright] == true || mapProperty[Indextop][Indexleft] == true)
			{
				return true;
			}
		}
		else
		{
			if (mapProperty[Indextop][Indexright] == true || mapProperty[Indexdown][Indexright] == true)
			{
				return true;
			}
		}
	}
	else if (xm < 0)
	{
		if (ym > 0)
		{
			if (mapProperty[Indexdown][Indexleft] == true || mapProperty[Indexdown][Indexright] == true)
			{
				return true;
			}
		}
		else if (ym < 0)
		{
			if (mapProperty[Indextop][Indexleft] == true || mapProperty[Indextop][Indexright] == true)
			{
				return true;
			}
		}
		else
		{
			if (mapProperty[Indextop][Indexleft] == true || mapProperty[Indexdown][Indexleft] == true)
			{
				return true;
			}
		}
	}
	else
	{
		if (ym > 0)
		{
			if (mapProperty[Indexdown][Indexleft] == true || mapProperty[Indexdown][Indexright] == true)
			{
				return true;
			}
		}

		else if (ym < 0)
		{
			if (mapProperty[Indextop][Indexleft] == true || mapProperty[Indextop][Indexright] == true)
			{
				return true;
			}
		}
	}

	return false;
}

bool Banana::arrive(GamePlayer* player)
{
	float x1, x2, y1, y2;
	x1 = pos.x, x2 = pos.x + 31, y1 = pos.y, y2 = pos.y + 31;

	if (x1 >= player->getxpos() && x1 <= player->getxpos() + 32 && y1 >= player->getypos() && y1 <= player->getypos() + 32)
	{
		return true;
	}
	if (x2 >= player->getxpos() && x2 <= player->getxpos() + 32 && y1 >= player->getypos() && y1 <= player->getypos() + 32)
	{
		return true;
	}
	if (x1 >= player->getxpos() && x1 <= player->getxpos() + 32 && y2 >= player->getypos() && y2 <= player->getypos() + 32)
	{
		return true;
	}
	if (x2 >= player->getxpos() && x2 <= player->getxpos() + 32 && y2 >= player->getypos() && y2 <= player->getypos() + 32)
	{
		return true;
	}
	return false;
}
bool Banana::arrive()
{
	float x1, x2, y1, y2;
	x1 = pos.x, x2 = pos.x + 31, y1 = pos.y, y2 = pos.y + 31;

	if (x1 >= originpos.x && x1 <= originpos.x + 32 && y1 >= originpos.y && y1 <= originpos.y + 32)
	{
		return true;
	}
	if (x2 >= originpos.x && x2 <= originpos.x + 32 && y1 >= originpos.y && y1 <= originpos.y + 32)
	{
		return true;
	}
	if (x1 >= originpos.x && x1 <= originpos.x + 32 && y2 >= originpos.y && y2 <= originpos.y + 32)
	{
		return true;
	}
	if (x2 >= originpos.x && x2 <= originpos.x + 32 && y2 >= originpos.y && y2 <= originpos.y + 32)
	{
		return true;
	}
	return false;
}

void Banana::startTimer(Uint32 t)
{
	time = t;
	timerID = SDL_AddTimer(time, changeData, this);
}
void Banana::stopTimer()
{
	time = 0;
}
Uint32 Banana::changeData(Uint32 interval, void* param)
{
	Banana* p = (Banana*)param;

	if (p->time != 0)
	{
		p->frame = (p->frame + 1) % p->wn;  // image frame	
		return interval;
	}
	else
	{
		return 0;
	}
}
