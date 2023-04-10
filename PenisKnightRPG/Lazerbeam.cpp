#include "Lazerbeam.h"

Lazerbeam::Lazerbeam() : WeaponItem()
{
	turnoff();
	Canrebound = true;
	gettarget = false;
	energy = 1;
	cooldown = 0;
	atk = 1;
}
Lazerbeam::~Lazerbeam()
{}

void Lazerbeam::render()
{
	if (active)
	{
		TM->DrawLine(pos.x, pos.y, pos2.x, pos2.y, 252, 76, 2, 100);
		if (Canrebound)
			TM->DrawLine(pos2.x, pos2.y, pos3.x, pos3.y, 252, 76, 2, 100);
	}
}

void Lazerbeam::update(float xpos,float ypos,double rad, vector<GameMonster*> mst)
{
	if (active)
		launch(xpos, ypos, rad, mst);
	else
		energy = 1;
}

void Lazerbeam::launch(float xpos,float ypos,double rad, vector<GameMonster*> mst)
{
	int IndexX, IndexY;
	active = true;
	if(cooldown==0)
		energy*=2;
	cooldown++;
	cooldown %= 200;
	if (energy > EMAX)
		energy = EMAX;
	realpos.x = realpos2.x = xpos + 15;
	realpos.y = realpos2.y = ypos + 15;
	pos.x = (int)realpos.x % 640, pos.y = (int)realpos.y % 480;
	pos2.x = (int)realpos2.x % 640, pos2.y = (int)realpos2.y % 480;
	move.x = (float)cos(rad);
	move.y = (float)sin(rad);

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
		{
			Canrebound = true;
			gettarget = false;
		}
		if (gettarget)
			break;
		if (mapProperty[IndexY][IndexX] == true)
			break;
		/*system("pause");*/
	}
	/*printf("%d\n",Canrebound);*/
	if (Canrebound)
		launchrebound(IndexX, IndexY, mst);
}

void Lazerbeam::launchrebound(int ix, int iy,vector<GameMonster*> mst)
{
	realpos3.setXY(realpos2.x, realpos2.y);
	pos3.x = (int)realpos2.x % 640, pos3.y = (int)realpos2.y % 480;

	int ixx = (int)(realpos2.x - move.x) / 32, iyy = (int)(realpos2.y - move.y) / 32;

	ixx -= ix, iyy -= iy;

	if (ixx > 0)
	{
		if (iyy > 0)
			move.multiply(-1, -1);
		else if (iyy == 0)
			move.multiply(-1, 1);
		else
			move.multiply(-1, -1);
	}
	else if (ixx == 0)
	{
		if (iyy > 0)
			move.multiply(1, -1);
		else if (iyy == 0)
			;
		else
			move.multiply(1, -1);
	}
	else
	{
		if (iyy > 0)
			move.multiply(-1, -1);
		else if (iyy == 0)
			move.multiply(-1, 1);
		else
			move.multiply(-1, -1);
	}

	while (1)
	{
		realpos3 = move.x < realpos3;
		realpos3 = move.y > realpos3;
		pos3 = move.x < pos3;
		pos3 = move.y > pos3;
		int IndexX = (int)realpos3.x / 32;
		int IndexY = (int)realpos3.y / 32;
		for (int i = 0; i < mst.size(); i++)
			if (harmMons(mst[i],2))
				break;
		if (mst.size() == 0)
		{
			Canrebound = true;
			gettarget = false;
		}
		if (gettarget)
			break;
		if (mapProperty[IndexY][IndexX])
			break;
	}
}

bool Lazerbeam::harmMons(GameMonster* mst,int n)
{
	if (n == 1)
	{
		if (pos2.x >= mst->getxpos() && pos2.x <= mst->getxpos() + 32 && pos2.y >= mst->getypos() && pos2.y <= mst->getypos() + 32)
		{
		
			mst->bleeding(atk*energy);
			Canrebound = false;
			gettarget = true;
			return true;
		}
	}

	if (n == 2)
	{
		if (pos3.x >= mst->getxpos() && pos3.x <= mst->getxpos() + 32 && pos3.y >= mst->getypos() && pos3.y <= mst->getypos() + 32)
		{
			
			mst->bleeding(atk*energy);
			//printf("%d\n", mst->ShowHP());
			cooldown++;
			gettarget = true;
			return true;
		}
	}

	Canrebound = true;
	gettarget = false;
	return false;
}