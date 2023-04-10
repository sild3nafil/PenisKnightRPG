#include "Snipershot.h"
#include "HealthPoint.h"

Snipershot::Snipershot()
{
	energybar = new HealthPoint("assets/energybar.png", 0, 0);
	semem = TM->LoadTexture("assets/semen.png");
	bullet_num = new Text("fonts/FFFFORWA.TTF", "5", 32, 2, 15, { 255,255,255 });

	turnoff();
	gettarget = false;
	semem_time = 0;
	energy = 1;
	bullet = 5;
	strcpy_s(b_num, "5");

	atk = 20;
	cooldown = 0;

	srcRect.x = srcRect.y = 0;
	srcRect.w = srcRect.h = 32;
	dRect.w = dRect.h = 32;
}
Snipershot::~Snipershot()
{
	delete energybar;
	energybar = nullptr;
	SDL_DestroyTexture(semem);
	semem = nullptr;
	delete bullet_num;
	bullet_num = nullptr;

}

void Snipershot::update(float xpos, float ypos, double rad, vector<GameMonster*> mst)
{
	if (active)
	{
		aim(xpos, ypos, rad, mst);
		energybar->update(this);
	}
	if (semem_time > 0)
		semem_time--;
}
void Snipershot::render()
{
	if (active)
	{
		TM->DrawLine(pos.x, pos.y, pos2.x, pos2.y, 160, 32, 240, 100);
		if (bullet > 0)
			energybar->render();
	}
	if (semem_time > 0)
	{
		/*printf("su\n");*/
		TM->Draw(semem, srcRect, dRect);
	}
	bullet_num->render();
}
void Snipershot::shot(vector<GameMonster*> mst)
{
	if (bullet > 0)
	{
		bullet--;
		b_num[0]--;
		bullet_num->update(b_num);
	}
	
	for (int i = 0; i < mst.size(); i++)
		if (harmMons(mst[i], 2))
			break;

	dRect.x = (int)pos2.x - 15;
	dRect.y = (int)pos2.y - 15;
	semem_time = 22;
	gettarget = false;
	energy=1;
}
void Snipershot::reload()
{
	bullet = 5;
	b_num[0] = 48 + 5;
	bullet_num->update(b_num);
}
void Snipershot::aim(float xpos, float ypos, double rad, vector<GameMonster*> mst)
{
	int IndexX, IndexY;
	turnon();

	realpos.x = realpos2.x = xpos + 15;
	realpos.y = realpos2.y = ypos + 15;
	pos.x = pos2.x = (int)(xpos + 15) % 640;
	pos.y = pos2.y = (int)(ypos + 15) % 480;
	move.x = (float)cos(rad);
	move.y = (float)sin(rad);

	if (cooldown == 0)
		energy++;
	cooldown++;
	cooldown = cooldown % 3;
	if (energy > EMAX)
		energy = EMAX;

	while (1)
	{
		pos2 += move;
		realpos2 += move;
		IndexX = (int)realpos2.x / 32;
		IndexY = (int)realpos2.y / 32;
		//printf("%d %d\n", IndexX, IndexY);

		for (int i = 0; i < mst.size(); i++)
			if (harmMons(mst[i],1))
				break;
		if (mst.size() == 0)
			gettarget = false;
		if (gettarget)
			break;
		if (mapProperty[IndexY][IndexX] == true)
			break;
		/*system("pause");*/
	}
}
bool Snipershot::harmMons(GameMonster* mst,int n)
{
	if (n == 1)
	{
		if (pos2.x >= mst->getxpos() && pos2.x <= mst->getxpos() + 32 && pos2.y >= mst->getypos() && pos2.y <= mst->getypos() + 32)
		{
			gettarget = true;
			return true;
		}
	}
	if (n == 2)
	{
		if (pos2.x >= mst->getxpos() && pos2.x <= mst->getxpos() + 32 && pos2.y >= mst->getypos() && pos2.y <= mst->getypos() + 32)
		{
			mst->bleeding(atk*energy);
			//printf("%d\n", mst->ShowHP());
			gettarget = true;
			return true;
		}
	}

	gettarget = false;
	return false;
}