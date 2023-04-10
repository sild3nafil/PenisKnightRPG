#include "Portalring.h"

Portalring::Portalring() : WeaponItem()
{
	reset();
	bluering = TM->LoadTexture("assets/bCircle.png");
	oranring = TM->LoadTexture("assets/dCircle.png");
	
	srcRect.x = srcRect.y = 0;
	srcRect.w = srcRect.h = 32;
	dRect.w = dRect.h = 32;
}
Portalring::~Portalring()
{
	SDL_DestroyTexture(bluering);
	SDL_DestroyTexture(oranring);
	bluering = nullptr;
	oranring = nullptr;
}

void Portalring::update(GamePlayer* p)
{
	if (blue_on)
		if (!checkcollision(realpos.x, realpos.y, 1))
			pos += move1, realpos += move1;

	if (oran_on)
		if (!checkcollision(realpos2.x, realpos2.y, 2))
			pos2 += move2, realpos2 += move2;

	if (blue_reach && oran_reach)
		enter(p);
}
void Portalring::render()
{
	if (blue_on)
		if (!blue_reach)
		{
			dRect.x = (int)pos.x;
			dRect.y = (int)pos.y;
			TM->Draw(bluering, srcRect, dRect);
		}
		
	if (blue_reach)
	{
		dRect.x = ((int)(pos.x-move1.x)/ 32) * 32;
		dRect.y = ((int)(pos.y-move1.y) / 32) * 32;
		TM->Draw(bluering, srcRect, dRect);
	}
		
	if(oran_on)
		if (!oran_reach)
		{
			dRect.x = (int)pos2.x;
			dRect.y = (int)pos2.y;
			TM->Draw(oranring, srcRect, dRect);
		}

	if(oran_reach)
	{
		dRect.x = ((int)(pos2.x - move2.x) / 32) * 32;
		dRect.y = ((int)(pos2.y - move2.y) / 32) * 32;
		TM->Draw(oranring, srcRect, dRect);
	}
}
void Portalring::reset()
{
	blue_on = oran_on = blue_reach = oran_reach = false;
}
bool Portalring::checkcollision(float x, float y, int n)
{
	int IndexX = (int)x / 32, IndexY = (int)y / 32;

	if (mapProperty[IndexY][IndexX] == true)
	{
		if (n == 1&&!blue_reach)
		{
			pos -= move1;
			realpos -= move1;
			blue_reach = true;
			return true;
		}
		if (n == 2 && !oran_reach)
		{
			pos2 -= move2;
			realpos2 -= move2;
			oran_reach = true;
			return true;
		}
	}
	else
	{
		if (n == 1 && !blue_reach)
		{
			blue_reach = false;
			return false;
		}
		if (n == 2 && !oran_reach)
		{

			oran_reach = false;
			return false;
		}
		return true;
	}
}
void Portalring::enter(GamePlayer* p)
{
	if (!p->getin)
	{
		if ((int)(p->getxpos() + 15 )/ 32 == (int)pos.x / 32 && (int)(p->getypos() + 15 )/ 32 == (int)pos.y / 32)
		{
			p->setxpos((int)pos2.x / 32 * 32);
			p->setypos((int)pos2.y / 32 * 32);
			p->setrealxpos((int)realpos2.x / 32 * 32);
			p->setrealypos((int)realpos2.y / 32 * 32);
			p->getin = true;
		}
		else if ((int)(p->getxpos() + 15 )/ 32 == (int)pos2.x / 32 && (int)(p->getypos() + 15 )/ 32 == (int)pos2.y / 32)
		{
			p->setxpos((int)pos.x / 32 * 32);
			p->setypos((int)pos.y / 32 * 32);
			p->setrealxpos((int)realpos.x / 32 * 32);
			p->setrealypos((int)realpos.y / 32 * 32);
			p->getin = true;
		}
		else
			p->getin = false;
	}
	else if (p->getin)
	{
		if ((int)(p->getxpos() + 15 )/ 32 == (int)pos.x / 32 && (int)(p->getypos() + 15 )/ 32 == (int)pos.y / 32)
			p->getin = true;
		else if ((int)(p->getxpos() + 15 )/ 32 == (int)pos2.x / 32 && (int)(p->getypos() + 15)/ 32 == (int)pos2.y / 32)
			p->getin = true;
		else
			p->getin = false;
		/*printf("%d %d %d %d %d\n", p->getin, (int)(p->getrealxpos() + 15) / 32, (int)(p->getrealypos() + 15) / 32, (int)pos.x / 32, (int)pos.y / 32);*/
	}
}
void Portalring::sendblue(float x,float y,double r)
{
	blue_on = true;
	blue_reach = false;
	realpos.x = x;
	realpos.y = y;
	pos.x = (int)realpos.x % 640;
	pos.y = (int)realpos.y % 480;
	move1.setXY(cos(r), sin(r));
	move1 = move1 * 5;
}
void Portalring::sendoran(float x, float y,double r)
{
	oran_on = true;
	oran_reach = false;
	realpos2.x = x;
	realpos2.y = y;
	pos2.x = (int)realpos2.x % 640;
	pos2.y = (int)realpos2.y % 480;
	move2.setXY(cos(r), sin(r));
	move2 = move2 * 5;
}