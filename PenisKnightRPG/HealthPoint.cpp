#include "HealthPoint.h"
#include "GamePlayer.h"
#include "GameMonster.h"
#include "GameBoss.h"
#include "Snipershot.h"

HealthPoint::HealthPoint(const char* filename, float x, float y) :GameObject(filename, x, y)
{
	hpTex = TM->LoadTexture(filename);
	
	hpline = 10;

	srcRect.x = srcRect.y = 0;
	srcRect.h = 8;
	srcRect.w = 50;
}
HealthPoint::HealthPoint(const char* filename, float x, float y, int w, int h) :GameObject(filename, x, y)
{
	hpTex = TM->LoadTexture(filename);

	hpline = 10;

	srcRect.x = srcRect.y = 0;
	srcRect.h = h;
	srcRect.w = w;
}

HealthPoint::~HealthPoint()
{
	close();
}

void HealthPoint::update(GamePlayer* p)
{
	int hp = p->ShowHP(), hpmax = p->GetMaxHP(), gap = hpmax / 10;
	pos.x = p->getxpos()-9;
	pos.y = p->getypos()+32;

	if (hp >= hpmax)
		hpline = 10;
	else if (hp < hpmax && hp > 0)
		hpline = hp / gap + 1;
	else
		hpline = 0;
}

void HealthPoint::update_mp(GamePlayer* p)
{
	int mp = p->ShowMP(), mpmax = p->GetMaxMP(), gap = mpmax / 10;
	pos.x = p->getxpos() - 9;
	pos.y = p->getypos() + 32 + 8;

	if (mp >= mpmax)
		hpline = 10;
	else if (mp < mpmax && mp > 0)
		hpline = mp / gap + 1;
	else
		hpline = 0;
}

void HealthPoint::update(GameMonster* m)
{
	int hp = m->ShowHP(), hpmax = m->GetMaxHP(), gap = hpmax / 10;
	pos.x = m->getxpos() - 9;
	pos.y = m->getypos() + 32;

	if (hp >= hpmax)
		hpline = 10;
	else if (hp < hpmax && hp > 0)
		hpline = hp / gap + 1;
	else
		hpline = 0;
}
void HealthPoint::update(GameBoss* b)
{
	int hp = b->ShowHP(), hpmax = b->GetMaxHP(), gap = hpmax / 100;
	pos.x = 0;
	pos.y = 480-32;

	if (hp >= hpmax)
		hpline = 100;
	else if (hp < hpmax && hp > 0)
		hpline = hp / gap + 1;
	else
		hpline = 0;
}

void HealthPoint::update(Snipershot* s)
{
	int e = s->getEnergy(), emax = s->getEMAX(), gap = 10;
	pos.x = s->getxpos()-15 - 9;
	pos.y = s->getypos()-15 - 8;

	if (e >= emax)
		hpline = 10;
	else if (e < emax && e > 0)
		hpline = e / gap ;
}

void HealthPoint::render()
{
	srcRect.x = 0;
	srcRect.y = 0;
	srcRect.w = 5 * hpline;
	srcRect.h = 8;

	dRect.x = (int)pos.x;
	dRect.y = (int)pos.y;
	dRect.w = srcRect.w;
	dRect.h = srcRect.h;

	TM->Draw(hpTex, srcRect, dRect);
}
void HealthPoint::render_boss()
{
	srcRect.x = 0;
	srcRect.y = 0;
	srcRect.w = int(6.4 * (float)hpline);
	srcRect.h = 32;

	dRect.x = (int)pos.x;
	dRect.y = (int)pos.y;
	dRect.w = srcRect.w;
	dRect.h = srcRect.h;

	TM->Draw(hpTex, srcRect, dRect);
}

void HealthPoint::close()
{
	SDL_DestroyTexture(hpTex);
	hpTex = nullptr;
}