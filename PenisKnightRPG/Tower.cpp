#include "Tower.h"
#include "GamePlayer.h"
#include "HealthPoint.h"

Tower::Tower(const char* filename, float x, float y, int hp, int atk, int vw, int id) : GameMonster(filename, x, y, hp, atk, vw, id)
{
	speed = 0;
	coin = 50;

	for (int i = 0; i < MAX_BULLET; i++)
		bullet[i] = new Bullet("assets/fireball.png", 15);
	effect_shot = new Mixer("audio/fireball.mp3", EFFECT);
}
Tower::~Tower()
{
	close();
}
void Tower::update(GamePlayer* player)
{
	checkPlayerDie(player);
	if(!isAlive())
		reload();
	recover();
	if (alive)
	{
		attack(player);
		playerpos.setXY(player->getxpos(), player->getypos());
	}
	for (int i = 0; i < MAX_BULLET; i++)
		bullet[i]->update(player);
}
void Tower::render()
{
	hpbar->update(this);

	srcRect.x = 0;
	srcRect.y = 0;
	srcRect.w = 32;
	srcRect.h = 32;
	dRect.x = (int)pos.x;
	dRect.y = (int)pos.y;
	dRect.w = srcRect.w;
	dRect.h = srcRect.h;

	if (alive)
	{
		TM->Draw(monsTex, srcRect, dRect);
		TM->DrawLine(pos.x+15, pos.y+15, playerpos.x+15, playerpos.y+15, 255, 0, 0, 100);
		hpbar->render();
	}
	for (int i = 0; i < MAX_BULLET; i++)
		bullet[i]->render();
}
void Tower::attack(GamePlayer* player)
{
	int x = player->getxpos(), y = player->getypos();
	vector2 dir;
	ATKcooldown%=100;

	if (ATKcooldown == 0)
	{
		dir.setXY(x - pos.x, y - pos.y);
		rad = dir.getRad();
		shot();
	}
	ATKcooldown++;
}
void Tower::close()
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
void Tower::rez(float x, float y)
{
	ATKcooldown = 0;
	alive = true;
	HP = HP_MAX;
	setrealXY(x, y);

	for (int i = 0; i < MAX_BULLET; i++)
		bullet[i]->reload();
}
void Tower::shot()
{
	effect_shot->playEffect(ONE, -1);
	for (int c = 0; c < 8; c++)
	{
		for (int i = 0; i < MAX_BULLET; i++)
		{
			if (!bullet[i]->Active())
			{
				bullet[i]->loadMap(mapItem, mapProperty);
				bullet[i]->fire(realpos.x + 15, realpos.y + 15, rad);
				break;
			}
		}
		rad += M_PI / 4;
	}
}
void Tower::recover()
{
	static int cd=0;
	if (cd == 0)
	{
		HP += 5;
	}
	cd = (cd + 1) % 5;
}
