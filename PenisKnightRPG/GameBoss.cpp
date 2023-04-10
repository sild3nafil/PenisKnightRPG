#include "GameBoss.h"
#include "GamePlayer.h"
#include "HealthPoint.h"

GameBoss::GameBoss(const char* filename, float x, float y, int hp, int atk, int vw, int n, int wwn, int hhn, int id) : GameMonster(filename, x, y, hp, atk, vw, n, wwn, hhn, id)
{
	speed = 4;
	coin = 1000;
	delete hpbar;
	hpbar = nullptr;
	hpbar = new HealthPoint("assets/hpbar_red.png", 0, 480-32,640,32);
	super_state(1, 0, 0);

	for (int i = 0; i < MAX_HURRICANE; i++)
		hurricane[i] = new Hurricane("assets/fire_hurricane.png", 25);
	for (int i = 0; i < MAX_BANANA; i++)
		banana[i] = new Banana("assets/fire_banana.png", 7);
}
GameBoss::~GameBoss()
{
	close();
}
void GameBoss::update(GamePlayer* player)
{
	checkPlayerDie(player);
	if (!isAlive())
		reload();

	if (alive)
	{
		hpbar->update(this);
		checkStage();
		//printf("%f %f\n", pos.x, pos.y);

		if (stage[0])
			;
		if (stage[1])
		{
			follow(player);
			if (iseffect)
			{
				effect_cd--;
				if (effect_cd <= 0)
				{
					iseffect = false, effect_cd = 200;
					player->SetBonus(0);
				}
			}
			if (stop_cd > 0)
			{
				stop_cd--;
				if (magic_cd == 0)
					magic(player);
				magic_cd = (magic_cd + 1) % 50;
			}
			else
				magic_cd = 50;
		}
		if (stage[2])
		{
			if (stop_cd == 0)
			{
				follow2(player);
			}
			if (show_cd == 0)
			{
				show(player);
			}
			if (stop_cd > 0)
			{
				stop_cd--;
				if (attack_cd == 0)
					attack(player);
				attack_cd = (attack_cd + 1) % 100;
			}

			show_cd = (show_cd + 1) % 200;
		}

		for (int i = 0; i < MAX_HURRICANE; i++)
			hurricane[i]->update(player);
		for (int i = 0; i < MAX_BANANA; i++)
			banana[i]->update(player);

		if (!checkCollision())
			pos += move, realpos += move;
	}
}
void GameBoss::render()
{
	wPic = frame % wn;
	hPic = frame / wn;

	srcRect.x = 50 * wPic;
	srcRect.y = 50 * hPic;
	srcRect.w = 50;
	srcRect.h = 50;
	dRect.x = (int)pos.x;
	dRect.y = (int)pos.y;
	dRect.w = srcRect.w;
	dRect.h = srcRect.h;

	if (alive)
	{
		TM->Draw(monsTex, srcRect, dRect);
		if (super[0])
		{
			TM->DrawCircle(pos.x + 26, pos.y + 26, 55, 255, 0, 0, 255);
		}
		if (super[1])
		{
			TM->DrawCircle(pos.x + 26, pos.y + 26, 55, 255, 153, 51, 255);
		}
		if (super[2])
		{
			TM->DrawCircle(pos.x + 26, pos.y + 26, 55, 255, 255, 255, 255);
		}
		hpbar->render_boss();
	}
	if (effect_cd)
	{
		TM->DrawCircle(effectpos.x, effectpos.y, radius, 255, 0, 0, 255);
		radius += 5;
	}
	for (int i = 0; i < MAX_HURRICANE; i++)
		hurricane[i]->render();
	for (int i = 0; i < MAX_BANANA; i++)
		banana[i]->render();
}
void GameBoss::close()
{
	delete hpbar;
	hpbar = nullptr;
	SDL_DestroyTexture(monsTex);
	monsTex = nullptr;
	SDL_RemoveTimer(timerID);
	for (int i = 0; i < MAX_HURRICANE; i++)
		hurricane[i]->close();
}

void GameBoss::follow(GamePlayer* player)
{
	int xDis, yDis;
	xDis = (int)(pos.x - player->getxpos());
	yDis = (int)(pos.y - player->getypos());
	bool xbiggerthany = (fabs(xDis) >= fabs(yDis));

	if (stop_cd == 0)
	{
		if (xbiggerthany)
		{
			if (xDis < -32)
				Move(1, 0);
			else if (xDis >= -32 && xDis <= 32)
			{
				Move(0, 0), stop_cd = 151, iseffect = true;
				radius = 0;
				effectpos.setXY(pos.x + 26, pos.y + 26);
				player->SetBonus(-1);
			}
			else
				Move(-1, 0);
		}
		else
		{
			if (yDis < -32) {
				Move(0, 1);
			}
			else if (yDis >= -32 && yDis <= 32) {
				Move(0, 0), stop_cd = 151, iseffect = true;
				radius = 0;
				effectpos.setXY(pos.x, pos.y);
				player->SetBonus(-1);
			}
			else {
				Move(0, -1);
			}
		}
	}
}
void GameBoss::rez(float x, float y)
{
	ATKcooldown = 0;
	alive = true;
	HP = HP_MAX;
	setrealXY(x, y);

	super_state(1, 0, 0);
	Move(0, 0);
	for (int i = 0; i < MAX_HURRICANE; i++)
		hurricane[i]->reload();
	for (int i = 0; i < MAX_BANANA; i++)
		banana[i]->reload();
}
void GameBoss::follow2(GamePlayer* player)
{
	int xDis, yDis;
	xDis = (int)(pos.x - player->getxpos());
	yDis = (int)(pos.y - player->getypos());
	bool xbiggerthany = (fabs(xDis) >= fabs(yDis));

	speed = 1;
	if (xbiggerthany)
	{
		if (xDis < -50)
			Move(1, 0);
		else if (xDis >= -50 && xDis <= 50)
		{
			Move(0, 0);
		}
		else
			Move(-1, 0);
	}
	else
	{
		if (yDis < -50) {
			Move(0, 1);
		}
		else if (yDis >= -50 && yDis <= 50) {
			Move(0, 0);
		}
		else {
			Move(0, -1);
		}
	}
	

}

void GameBoss::attack(GamePlayer* player)
{
	int x = player->getxpos(), y = player->getypos();
	vector2 dir;
	dir.setXY(x - pos.x, y - pos.y);
	double rad = dir.getRad();

	for (int c = 0; c < 5; c++)
	{
		for (int i = 0; i < MAX_BANANA; i++)
			if (!banana[i]->Active())
			{
				banana[i]->throw_Banana(realpos.x + 15, realpos.y + 15, rad);
				break;
			}
		rad += M_PI*2 / 5;
	}
}
void GameBoss::magic(GamePlayer* player)
{
	int x = player->getxpos(), y = player->getypos();
	vector2 dir;
	dir.setXY(x - pos.x, y - pos.y);
	double rad = dir.getRad();

	for (int c = 0; c < 4; c++)
	{
		for (int i = 0; i < MAX_HURRICANE; i++)
			if (!hurricane[i]->Active())
			{
				hurricane[i]->summon(realpos.x + 15, realpos.y + 15, rad);
				break;
			}
		rad += M_PI / 2;
	}
}
void GameBoss::show(GamePlayer* player)
{
	stop_cd = 151, iseffect = true;
	radius = 0;
	effectpos.setXY(pos.x, pos.y);
	pos.setXY(player->getxpos(), player->getypos());
	realpos.setXY(player->getrealxpos(), player->getrealypos());
}

void GameBoss::bleeding(int atk)
{
	if (super[0])
	{
		return;
	}
	if (super[1])
	{
		HP -= atk / 3;
	}
	if (super[2])
	{
		HP -= atk / 3 * 2;
	}
	if(!super[0] && !super[1] && !super[2])
	{
		HP -= atk;
	}
	//printf("%d\n", HP);
}

void GameBoss::checkStage()
{
	if (HP <= HP_MAX && HP > HP_MAX / 3 * 2)
		stage[0] = true, stage[1] = stage[2] = false;
	else if (HP < HP_MAX / 3 * 2 && HP > HP_MAX / 3)
		stage[1] = true, stage[0] = stage[2] = false;
	else
		stage[2] = true, stage[0] = stage[1] = false;
}

int GameBoss::getStage()
{
	if (stage[0])
		return 1;
	if (stage[1])
		return 2;
	if (stage[2])
		return 3;
}

Uint32 GameBoss::changeData(Uint32 interval, void* param)
{
	GameBoss* b = (GameBoss*)param;

	if (b->t != 0)
	{
		b->frame = (b->frame + 1) % b->wn + b->frametime;  // image frame	
		return interval;
	}
	else
	{
		return 0;
	}
}