#include "Bullet.h"
#include <math.h>

Bullet::Bullet(const char* filename,int a) : WeaponItem()
{
	bulTex = TM->LoadTexture(filename); //assets/bullet.png
	speed = 2.5;
	atk = a;
	reload();

	srcRect.x = srcRect.y = 0;
	srcRect.w = srcRect.h = 8;
	dRect.w = dRect.h = 8;
}

Bullet::~Bullet()
{
	delete bulTex;
	bulTex = NULL;
}

void Bullet::fire(float x, float y,double r)
{
	realpos.setXY(x, y);
	pos.x = (int)realpos.x % 640;
	pos.y = (int)realpos.y % 480;
	move.setXY(1, 1);
	move = r * move;

	active = true;
	Canrebound = true;
}
void Bullet::reload()
{
	active = false;
}
void Bullet::close()
{
	SDL_DestroyTexture(bulTex);
	bulTex = nullptr;
}

void Bullet::update(vector<GameMonster*> mst)
{
	if (active)
	{
		if (checkCollision())
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
	}
}

void Bullet::update(GamePlayer* player)
{
	if (active)
	{
		if (checkCollision())
			reload();
		if (harmPlayer(player))
			reload();
	}
		
	realpos += move * speed;
	pos += move * speed;
}

void Bullet::render()
{
	dRect.x = (int)pos.x;
	dRect.y = (int)pos.y;
	if (active)
		TM->Draw(bulTex, srcRect, dRect);
}

bool Bullet::checkCollision()
{
	int Indextop, Indexdown, Indexright, Indexleft;
	float xm, ym,cx,cy;
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
				if (!Canrebound)
					return true;
				else
				{
					mapProperty[Indexdown][Indexleft] == true ? bounce(Indexdown, Indexleft,realpos.y+3,realpos.x+3) : bounce(Indexdown, Indexright, realpos.y + 3, realpos.x + 3);
					return false;
				}
			}
		}
		else if (ym < 0)
		{
			if (mapProperty[Indextop][Indexright] == true || mapProperty[Indextop][Indexleft] == true)
			{
				if (!Canrebound)
					return true;
				else
				{
					mapProperty[Indextop][Indexleft] == true ? bounce(Indextop, Indexleft, realpos.y + 3, realpos.x + 3) : bounce(Indextop, Indexright, realpos.y + 3, realpos.x + 3);
					return false;
				}
			}
		}
		else
		{
			if (mapProperty[Indextop][Indexright] == true || mapProperty[Indexdown][Indexright] == true)
			{
				if (!Canrebound)
					return true;
				else
				{
					mapProperty[Indextop][Indexright] == true ? bounce(Indextop, Indexright, realpos.y + 3, realpos.x + 3) : bounce(Indexdown, Indexright, realpos.y + 3, realpos.y + 3);
					return false;
				}
			}
		}
	}
	else if (xm < 0)
	{
		if (ym > 0)
		{
			if (mapProperty[Indexdown][Indexleft] == true || mapProperty[Indexdown][Indexright] == true)
			{
				if (!Canrebound)
					return true;
				else
				{
					mapProperty[Indexdown][Indexleft] == true ? bounce(Indexdown, Indexleft, realpos.y + 3, realpos.x + 3) : bounce(Indexdown, Indexright, realpos.y + 3, realpos.x + 3);
					return false;
				}
			}
		}
		else if (ym < 0)
		{
			if (mapProperty[Indextop][Indexleft] == true || mapProperty[Indextop][Indexright] == true)
			{
				if (!Canrebound)
					return true;
				else
				{
					mapProperty[Indextop][Indexleft] == true ? bounce(Indextop, Indexleft, realpos.y + 3, realpos.x + 3) : bounce(Indextop, Indexright, realpos.y + 3, realpos.x + 3);
					return false;
				}
			}
		}
		else
		{
			if (mapProperty[Indextop][Indexleft] == true || mapProperty[Indexdown][Indexleft] == true)
			{
				if (!Canrebound)
					return true;
				else
				{
					mapProperty[Indextop][Indexleft] == true ? bounce(Indextop, Indexleft, realpos.y + 3, realpos.x + 3) : bounce(Indexdown, Indexleft, realpos.y + 3, realpos.x + 3);
					return false;
				}
			}
		}
	}
	else
	{
		if (ym > 0)
		{
			if (mapProperty[Indexdown][Indexleft] == true || mapProperty[Indexdown][Indexright] == true)
			{
				if (!Canrebound)
					return true;
				else
				{
					mapProperty[Indexdown][Indexleft] == true ? bounce(Indexdown, Indexleft, realpos.y + 3, realpos.x + 3) : bounce(Indexdown, Indexright, realpos.y + 3, realpos.x + 3);
					return false;
				}
			}
		}

		else if (ym < 0)
		{
			if (mapProperty[Indextop][Indexleft] == true || mapProperty[Indextop][Indexright] == true)
			{
				if (!Canrebound)
					return true;
				else
				{
					mapProperty[Indextop][Indexleft] == true ? bounce(Indextop, Indexleft, realpos.y + 3, realpos.x + 3) : bounce(Indextop, Indexright, realpos.y + 3, realpos.x + 3);
					return false;
				}
			}
		}
	}

	return false;
	//since using the if else if statement
	//the charactor now only can move on either x or y direction
}

void Bullet::bounce(int iy,int ix,float cy,float cx)
{
	int ixx, iyy;
	float checkx = move.x * -0.1, checky = move.y * -0.1;
	vector2 c;
	Canrebound = false;
	c.setXY(cx, cy);

	/*printf("%f %f // %f %f\n", xpos - xmove * speed, ypos - ymove * speed, xpos, ypos);*/
	while (1)
	{
		c = checkx < c;
		c = checky > c;
		if ((int)c.x / 32 != ix || (int)c.y / 32 != iy)
		{
			ixx = (int)c.x / 32, iyy = (int)c.y / 32;
			break;
		}
	}
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
	else if(ixx==0)
	{
		if (iyy > 0)
			move.multiply(1, -1);
		else if (iyy == 0)
			pos.setXY(cx, cy);
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
	

	/*cx -= (ox * 32 + 15);
	cy -= (oy * 32 + 15);*/
	/*printf("%f %f\n", cx, cy);
	cx = cx * cos(M_PI / 4) - cy * sin(M_PI / 4);
	cy = cx * sin(M_PI / 4) + cy * cos(M_PI / 4);*/
	/*if (cx > 0 && cy > 0)
	{
		ymove *= -1;
		printf("down\n");
	}
	else if (cx > 0 && cy < 0)
	{
		ymove *= -1;
		printf("right\n");
	}
	else if (cx < 0 && cy < 0)
	{
		ymove *= -1;
		printf("up\n");
	}
	else if (cx < 0 && cy>0)
	{
		ymove *= -1;
		printf("left\n");
	}
	else;*/

}

bool Bullet::harmMons(GameMonster *mst)
{
	float x1, x2, y1, y2;
	x1 = pos.x, x2 = pos.x + 7, y1 = pos.y, y2 = pos.y + 7;

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

bool Bullet::harmPlayer(GamePlayer* player)
{
	float x1, x2, y1, y2;
	x1 = pos.x, x2 = pos.x + 7, y1 = pos.y, y2 = pos.y + 7;

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

