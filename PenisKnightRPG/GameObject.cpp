#include "GameObject.h"
#include "Map.h"

GameObject::GameObject(const char* filename, float x, float y)
{
	objTex = TM->LoadTexture(filename);

	pos.x = x;
	pos.y = y;
	alive = true;

	num = 1;
	wn = 1;
	hn = 1;
	frame = 0;

	roomornot = 1;
	realpos.x = x;
	realpos.y = y;

	srcRect.h = 32;
	srcRect.w = 32;
	srcRect.x = 0;
	srcRect.y = 0;
}
//Base class default constructor

GameObject::GameObject(const char* filename, float x, float y, int n, int wwn, int hhn)
{
	objTex = TM->LoadTexture(filename);

	pos.x = x;
	pos.y = y;
	alive = true;

	num = n;
	wn = wwn;
	hn = hhn;
	frame = 0;

	roomornot = 1;
	realpos.x = x;
	realpos.y = y;

	srcRect.h = 32;
	srcRect.w = 32;
	srcRect.x = 0;
	srcRect.y = 0;
}

GameObject::~GameObject() {
	close();
}

void GameObject::render() 
{
	wPic = frame % wn;
	hPic = frame / wn;

	srcRect.x = 32 * wPic;
	srcRect.y = 32 * hPic;
	srcRect.w = 32;
	srcRect.h = 32;
	dRect.x = (int)pos.x;
	dRect.y = (int)pos.y;
	dRect.w = srcRect.w;
	dRect.h = srcRect.h;

	TM->Draw(objTex, srcRect, dRect);
}

void GameObject::close()
{
	SDL_DestroyTexture(objTex);
	objTex = nullptr;
	SDL_RemoveTimer(timerID);
}

void GameObject::loadMap(const char map[MAPY][MAPX], const bool tmp[MAPY][MAPX]) {
	for (int i = 0; i < MAPY; i++)
		for (int j = 0; j < MAPX; j++)
			mapItem[i][j] = map[i][j];
	
	for (int i = 0; i < MAPY; i++)
		for (int j = 0; j < MAPX; j++)
			mapProperty[i][j] = tmp[i][j];
}
//get properties of map,but didnt use it

bool GameObject::checkCollision()
{
	int Indextop, Indexdown, Indexright, Indexleft;
	/*Indextop = realypos / 32;
	Indexdown = (realypos + 31) / 32;
	Indexright = (realxpos + 31) / 32;
	Indexleft = realxpos / 32;*/
	Indextop = ((int)realpos.y + 2) / 32;
	Indexdown = (int)(realpos.y + 29) / 32;
	Indexright = (int)(realpos.x + 29) / 32;
	Indexleft = (int)(realpos.x + 2) / 32;

	checkroomornot();
	/*if (!getroomornot())
	{

		return false;
	}*/
	if (move.x > 0)
	{
		/*if (ymove > 0)
		{

			if (mapProperty[Indexdown][Indexright] == '1')
				return true;
		}
		if (ymove < 0)
		{
			if (mapProperty[Indextop][Indexright] == '1')
				return true;
		}*/
		//if (ymove == 0)
		if (mapProperty[Indextop][Indexright + 1] == true || mapProperty[Indexdown][Indexright + 1] == true)
		{
			if (realpos.x + 35 >= (Indexright + 1) * 32)
				return true;
			else
				return false;
		}
	}
	if (move.x < 0)
	{
		/*if (ymove > 0)
		{
			if (mapProperty[Indexdown + 1][Indexleft - 1] == '1')
			{
				return true;
			}
		}
		if (ymove < 0)
		{
			if (mapProperty[Indextop-1][Indexleft-1] == '1')
				return true;
		}*/
		//if (ymove == 0)
		if (mapProperty[Indextop][Indexleft - 1] == true || mapProperty[Indexdown][Indexleft - 1] == true)
		{
			if (realpos.x - 3 <= Indexleft * 32)
				return true;
			else
				return false;
		}
	}
	if (move.x == 0)
	{
		if (move.y > 0)
		{

			if (mapProperty[Indexdown + 1][Indexleft] == true || mapProperty[Indexdown + 1][Indexright] == true)
			{
				//printf("realpos.y=%lf, Indexdown=%d\n", realpos.y, Indexdown*32);
				if (realpos.y + 35 >= (Indexdown + 1) * 32)
					return true;
			}
		}

		if (move.y < 0)
			if (mapProperty[Indextop - 1][Indexleft] == true || mapProperty[Indextop - 1][Indexright] == true)
			{
				if (realpos.y - 3 <= Indextop * 32)
					return true;
			}
	}

	return false;
	//since using the if else if statement
	//the charactor now only can move on either x or y direction
}
//check the boundary and the properties of the object on map

bool GameObject::checkEffect()
{
	int Indextop, Indexdown, Indexright, Indexleft;
	static int c = 0;

	Indextop = (int)(realpos.y+4) / 32;
	Indexdown = (int)(realpos.y + 27) / 32;
	Indexright = (int)(realpos.x + 27) / 32;
	Indexleft = (int)(realpos.x+4) / 32;
	//mapItem[Indextop][Indexright]||mapItem[Indextop][Indexleft]||mapItem[Indexdown][Indexright]||mapItem[Indexdown][Indexleft]
	if (mapItem[Indextop][Indexright] == '2' || mapItem[Indextop][Indexleft] == '2' || mapItem[Indexdown][Indexright] == '2' || mapItem[Indexdown][Indexleft] == '2')
	{
		bonus = waterFriction;
		return true;
	}
	if (mapItem[Indextop][Indexright] == '4' || mapItem[Indextop][Indexleft] == '4' || mapItem[Indexdown][Indexright] == '4' || mapItem[Indexdown][Indexleft] == '4')
	{
		bonus = grassFriction;
		return true;
	}
	if (mapItem[Indextop][Indexright] == '8' || mapItem[Indextop][Indexleft] == '8' || mapItem[Indexdown][Indexright] == '8' || mapItem[Indexdown][Indexleft] == '8')
	{
		bonus = 0;
		if(c%10==0)
			HP++;
		c++, c %= 10;
		return true;
	}
	if (mapItem[Indextop][Indexright] == '9' || mapItem[Indextop][Indexleft] == '9' || mapItem[Indexdown][Indexright] == '9' || mapItem[Indexdown][Indexleft] == '9')
	{
		bonus = 0;
		if (c % 10 == 0)
			MP+=2;
		c++, c %= 10;
		return true;
	}
	if (mapItem[Indextop][Indexright] == 'd' || mapItem[Indextop][Indexleft] == 'd' || mapItem[Indexdown][Indexright] == 'd' || mapItem[Indexdown][Indexleft] == 'd')
	{
		bonus = 0;
		if (c % 10 == 0)
			HP--;
		c++, c %= 10;
		return true;
	}
	else
		bonus = 0;
		return false;
}

bool GameObject::checkOut()
{
	if (pos.x <= 32)
		return true;
	if (pos.x+31 >= 640 - 32)
		return true;
	if (pos.y <= 32)
		return true;
	if (pos.y+31 >= 480 - 32)
		return true;
	return false;
}

bool GameObject::isAlive() 
{ 
	if (HP <= 0)
	{
		return false;
	}
	if (checkOut())
	{
		return false;
	}
	
	return true;
}

void GameObject::startTimer(Uint32 tt)
{
	t = tt;
	timerID = SDL_AddTimer(t, changeData, this); // Set Timer callback
}

void GameObject::stopTimer()
{
	t = 0;
}

Uint32 GameObject::changeData(Uint32 interval, void* param)
{
	GameObject* p = (GameObject*)param;

	if (p->t != 0)
	{
		p->frame = (p->frame + 1) % p->wn + p->frametime;  // image frame	
		return interval;
	}
	else
	{
		return 0;
	}
}

bool GameObject::getroomornot()
{
	return roomornot;
}
void GameObject::checkroomornot()
{

	if ((int)realpos.x / 640 % 2 == 1 || (int)realpos.y / 480 % 2 == 1)
		roomornot = 0;
	else
		roomornot = 1;
}

void GameObject::setMap(Map* mmap)
{
	map = mmap;
}

void GameObject::setrealXY(float xx, float yy)
{
	realpos.setXY(xx, yy);
	pos.setXY((int)xx % 640, (int)yy % 480);
}

void GameObject::AddHP(int h)
{
	if (alive)
	{
		if (HP < HP_MAX)
		{
			HP += h;
			if (HP > HP_MAX)
				HP = HP_MAX;
		}
	}
}
void GameObject::AddMP(int m)
{
	if (alive)
	{
		if (MP < MP_MAX)
		{
			MP += m;
			if (MP > MP_MAX)
				MP = MP_MAX;
		}
	}
}




