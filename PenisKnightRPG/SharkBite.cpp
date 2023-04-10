#include "SharkBite.h"

SharkBite::SharkBite()
{
	sharkTex = TM->LoadTexture("assets/shark.png");
	atk = 10;
	reload();
	cooldown = 0;
}
SharkBite::~SharkBite()
{
	close();
}
void SharkBite::update(vector<GameMonster*> mst, GamePlayer* p, float msx, float msy,int w,int h)
{
	vector2 dir;
	double rad;
	float cx = (p->getxpos() + 15) * w / 640.0, cy = (p->getypos() + 15) * h / 480.0;
	/*printf("%f %f\n", msx, msy);*/

	if (active)
	{
		if (sqrt((cx - msx) * (cx - msx) + (cy - msy) * (cy - msy)) <= range * h / 480.0)
			pos.x = msx / (w / 640.0), pos.y = msy / (h / 480.0);
		else
		{
			dir.setXY(msx - cx, msy - cy);
			rad = dir.getRad();
			pos.setXY(1, 1);
			pos *= rad;
			pos = pos * range ;
			pos << p->getxpos() + 15;
			pos >> p->getypos() + 15;
		}

		if (lasting > 0)
		{
			for (int i = 0; i < mst.size(); i++)
				if (harmMons(mst[i]))
					break;
			lasting--;
		}
		if (lasting == 0)
		{
			stopTimer();
			summon_shark = false;
		}
		if(cooldown>0)
			cooldown--;
	}
}
void SharkBite::render()
{
	if (active)
	{
		TM->DrawFilledCircle(pos.x, pos.y, 16, 0, 158, 177, 175);

		if (lasting > 0 && summon_shark)
		{
			wPic = frame % wn;
			hPic = frame / wn;

			srcRect.x = 32 * wPic;
			srcRect.y = 32 * hPic;
			srcRect.w = 32;
			srcRect.h = 32;
			dRect.x = (int)(pos2.x);
			dRect.y = (int)(pos2.y);
			dRect.w = srcRect.w;
			dRect.h = srcRect.h;

			TM->Draw(sharkTex, srcRect, dRect);
		}
	}
}
void SharkBite::summon()
{
	stopTimer();
	startTimer(60);
	lasting = 100;
	pos2.x = pos.x-15;
	pos2.y = pos.y-15;
	summon_shark = true;
}
void SharkBite::reload()
{
	active = false;
	lasting = 0;
	summon_shark = false;
	stopTimer();
}
void SharkBite::close()
{
	SDL_DestroyTexture(sharkTex);
	sharkTex = nullptr;
	SDL_RemoveTimer(timerID);
}
bool SharkBite::harmMons(GameMonster* mst)
{
	float x1, x2, y1, y2;
	x1 = pos2.x, x2 = pos2.x + 31, y1 = pos2.y, y2 = pos2.y + 31;

	if (x1 >= mst->getxpos() && x1 <= mst->getxpos() + 32 && y1 >= mst->getypos() && y1 <= mst->getypos() + 32)
	{
		cooldown = 50;
		mst->bleeding(atk);
		return true;
	}
	if (x2 >= mst->getxpos() && x2 <= mst->getxpos() + 32 && y1 >= mst->getypos() && y1 <= mst->getypos() + 32)
	{
		cooldown = 50;
		mst->bleeding(atk);
		return true;
	}
	if (x1 >= mst->getxpos() && x1 <= mst->getxpos() + 32 && y2 >= mst->getypos() && y2 <= mst->getypos() + 32)
	{
		cooldown = 50;
		mst->bleeding(atk);
		return true;
	}
	if (x2 >= mst->getxpos() && x2 <= mst->getxpos() + 32 && y2 >= mst->getypos() && y2 <= mst->getypos() + 32)
	{
		cooldown = 50;
		mst->bleeding(atk);
		return true;
	}
	return false;
}
void SharkBite::startTimer(Uint32 t)
{
	time = t;
	timerID = SDL_AddTimer(time, changeData, this);
}
void SharkBite::stopTimer()
{
	time = 0;
}
Uint32 SharkBite::changeData(Uint32 interval, void* param)
{
	SharkBite* p = (SharkBite*)param;

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
