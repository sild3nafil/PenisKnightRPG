#include "Hurricane.h"

Hurricane::Hurricane()
{
	hurricaneTex = TM->LoadTexture("assets/hurricane.png");
	speed = 1;
	atk = 100;
	reload();

	gravity.setXY(0, 0);
	cooldown = 100;

	srcRect.x = srcRect.y = 0;
	srcRect.w = srcRect.h = 32;
	dRect.w = dRect.h = 32;
}
Hurricane::Hurricane(const char* filename, int a)
{
	hurricaneTex = TM->LoadTexture(filename);
	speed = 1;
	atk = a;
	reload();

	gravity.setXY(0, 0);
	cooldown = 100;

	srcRect.x = srcRect.y = 0;
	srcRect.w = srcRect.h = 32;
	dRect.w = dRect.h = 32;
}
Hurricane::~Hurricane()
{
	SDL_RemoveTimer(timerID);
	delete hurricaneTex;
	hurricaneTex = NULL;
}

void Hurricane::update(vector<GameMonster*> mst)
{
	double dis = 100000, r;
	int c=0;
	vector2 dir;

	if (active)
	{
		cooldown--;
		if (cooldown < 0)
			cooldown = 0;
		if (Outta())
			reload();
		
		for (int i = 0; i < mst.size(); i++)
		{
			if (harmMons(mst[i]))
			{
				reload();
				break;
			}
		}

		realpos += move * speed;
		pos += move * speed;

		if (mst.size() > 0 && cooldown==0)
		{

			for (int i = 0; i < mst.size(); i++)
				if (getMonsdis(mst[i]) < dis)
				{
					dis = getMonsdis(mst[i]);
					c = i;
				}
			gravity.setXY(0.03, 0.03);
			dir.setXY(mst[c]->getxpos() - pos.x, mst[c]->getypos() - pos.y);
			r = dir.getRad();
			gravity = r * gravity;

			/*else
			{
				gettarget = false;
				gravity.setXY(0, 0);
			}*/
		}
		else
			gravity.setXY(0, 0);

		move += gravity;
	}
}
void Hurricane::update(GamePlayer* player)
{
	double r;
	int c = 0;
	vector2 dir;

	if (active)
	{
		cooldown--;
		if (cooldown < 0)
			cooldown = 0;
		if (Outta())
			reload();

	
		if (harmPlayer(player))
		{
			reload();
		}

		realpos += move * speed;
		pos += move * speed;

		if (player->isAlive() && cooldown == 0)
		{
			gravity.setXY(0.03, 0.03);
			dir.setXY(player->getxpos() - pos.x, player->getypos() - pos.y);
			r = dir.getRad();
			gravity = r * gravity;
		}
		else
			gravity.setXY(0, 0);

		move += gravity;
	}
}

void Hurricane::render()
{
	wPic = frame % wn;
	hPic = frame / wn;

	srcRect.x = 32 * wPic;
	srcRect.y = 32 * hPic;
	srcRect.w = 32;
	srcRect.h = 32;
	dRect.x = (int)(pos.x-15);
	dRect.y = (int)(pos.y-15);
	dRect.w = srcRect.w;
	dRect.h = srcRect.h;

	if (active)
		TM->Draw(hurricaneTex, srcRect, dRect);
}
void Hurricane::summon(float x, float y, double r)
{
	realpos.setXY(x, y);
	pos.x = (int)realpos.x % 640;
	pos.y = (int)realpos.y % 480;
	move.setXY(1, 1);
	move = r * move;

	cooldown = 100;
	startTimer(60);
	active = true;
}
void Hurricane::reload()
{
	stopTimer();
	active = false;
}

bool Hurricane::harmMons(GameMonster* mst)
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
bool Hurricane::harmPlayer(GamePlayer* player)
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

double Hurricane::getMonsdis(GameMonster* mst)
{
	double dis;
	dis = sqrt(pow((mst->getxpos() - pos.x), 2) + pow((mst->getypos() - pos.y), 2));
	return dis;
}

void Hurricane::startTimer(Uint32 t)
{
	time = t;
	timerID = SDL_AddTimer(time, changeData, this); // Set Timer callback
}
void Hurricane::stopTimer()
{
	time = 0;
}
Uint32 Hurricane::changeData(Uint32 interval, void* param)
{
	Hurricane *p = (Hurricane*)param;

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
void Hurricane::close()
{
	SDL_DestroyTexture(hurricaneTex);
	hurricaneTex = nullptr;
}