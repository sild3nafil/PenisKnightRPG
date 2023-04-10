#include "Map.h"
#include "MapSource.h"
#include "GamePlayer.h"
//map source code

Map::Map() {
	mapTex = TM->LoadTexture("assets/map_item_1.png");
	//load the map

	srcRect.w = dRect.w = 32;
	srcRect.h = dRect.h = 32;
}
//map initialized

Map::~Map() {
	SDL_DestroyTexture(mapTex);
	mapTex = nullptr;
}

//void Map::createRandomMap()
//{
//	int x, y,room=0,v;
//	srand(time(NULL));
//
//	for (y = 0; y < 5; y++)
//	{
//		for (x = 0; x < 5; x++)
//		{
//			v = rand() % 3;
//			if (room == 0)
//				loadRandomMap(x, y, T1[v]);
//			else if (room == 2)
//				loadRandomMap(x, y, T2[v]);
//			else if (room == 4)
//				loadRandomMap(x, y, T3[v]);
//			else if (room == 10)
//				loadRandomMap(x, y, M1[v]);
//			else if (room == 12)
//				loadRandomMap(x, y, M2[v]);
//			else if (room == 14)
//				loadRandomMap(x, y, M3[v]);
//			else if (room == 20)
//				loadRandomMap(x, y, B1[v]);
//			else if (room == 22)
//				loadRandomMap(x, y, B2[v]);
//			else if (room == 24)
//				loadRandomMap(x, y, B3[v]);
//			else if (y % 2 == 0 && x % 2 == 1)
//				loadRandomMap(x, y, Hpath);
//			else if (y % 2 == 1 && x % 2 == 0)
//				loadRandomMap(x, y, Vpath);
//			else if (y % 2 == 1 && x % 2 == 1)
//				loadRandomMap(x, y, Black);
//			else;
//
//			room++;
//		}
//	}
//	for (int i = 0; i < MAPY; i++)
//		randommap[i][MAPX - 1] = '\0';
//}

void Map::loadRandomMap(int x, int y, char tmp[15][21])
{
	int i, j;
	for (i = 0; i < 15; i++)
		for (j = 0; j < 20; j++)
			randommap[y * 15 + i][x * 20 + j] = tmp[i][j];
}

void Map::loadMap(char marr[MAPY][MAPX])
{
	for (int i = 0; i < MAPY; i++)
		for (int j = 0; j < MAPX; j++)
			map[i][j] = marr[i][j];

	loadMapProp(map);
}
//load map

void Map::loadMapProp(const char tmap[MAPY][MAPX])
{
	for (int i = 0; i < MAPY; i++)
		for (int j = 0; j < MAPX; j++)
		{
			char type = tmap[i][j]; //use switch case to determine the charactor
			switch (type)
			{
			case '0':
				property[i][j] = false;
				break;
			case '1':
				property[i][j] = true;
				break;
			case '2':
				property[i][j] = false;
				break;
			case '3':
				property[i][j] = true;
				break;
			case '4':
				property[i][j] = false;
				break;
			case '5':
				property[i][j] = false;
				break;
			case '6':
				property[i][j] = false;
				break;
			case '7':
				property[i][j] = false;
				break;
			case '8':
				property[i][j] = false;
				break;
			case '9':
				property[i][j] = false;
				break;
			case 'a':
				property[i][j] = false;
				break;
			case 'b':
				property[i][j] = false;
				break;
			case 'c':
				property[i][j] = false;
				break;
			case 'd':
				property[i][j] = false;
				break;
			case 'e':
				property[i][j] = false;
				break;
			case 'D':
				if(roomislock)
					property[i][j] = true;
				else
					property[i][j] = false;
				break;
			case 'F':
				property[i][j] = false;
				break;
			case 'X':
				property[i][j] = true;
				break;
			default:
				property[i][j] = false;
				break;
			}
		}

	/*for (int i = 0; i < MAPY; i++)
	{
		for (int j = 0; j < MAPX; j++)
		{
			if (property[i][j] == true)
				cout << "1";
			if (property[i][j] == false)
				cout << "0";
		}
		cout << endl;
	}*/
	//check if the function executed successfully
}
//get properties from map

void Map::drawMap(GamePlayer* p)
{
	int xstart, ystart;
	char type = '0';
	p->checkroomornot();

	int x = p->getrealxpos();
	int y = p->getrealypos();

	if (p->getroomornot())
	{
		xstart = x / 640;
		xstart *= 20;
		ystart = y / 480;
		ystart *= 15;
		for (int i = ystart; i < ystart + 15; i++)
		{
			for (int j = xstart; j < xstart + 20; j++)
			{
				type = map[i][j];
				dRect.x = (j - xstart) * 32;
				dRect.y = (i - ystart) * 32;

				switch (type)
				{
				case '0':
					srcRect.x = srcRect.y = 0;
					TM->Draw(mapTex, srcRect, dRect);
					break;
				case '1':
					srcRect.x = 2 * 32, srcRect.y = 0 * 32;
					TM->Draw(mapTex, srcRect, dRect);
					break;
				case '2':
					srcRect.x = 1 * 32, srcRect.y = 0 * 32;
					TM->Draw(mapTex, srcRect, dRect);
					break;
				case '3':
					srcRect.x = 3 * 32, srcRect.y = 0 * 32;
					TM->Draw(mapTex, srcRect, dRect);
					break;
				case '4':
					srcRect.x = 4 * 32, srcRect.y = 0 * 32;
					TM->Draw(mapTex, srcRect, dRect);
					break;
				case '5':
					srcRect.x = 0 * 32, srcRect.y = 1 * 32;
					TM->Draw(mapTex, srcRect, dRect);
					break;
				case '6':
					srcRect.x = 1 * 32, srcRect.y = 1 * 32;
					TM->Draw(mapTex, srcRect, dRect);
					break;
				case '7':
					srcRect.x = 2 * 32, srcRect.y = 1 * 32;
					TM->Draw(mapTex, srcRect, dRect);
					break;
				case '8':
					srcRect.x = 3 * 32, srcRect.y = 1 * 32;
					TM->Draw(mapTex, srcRect, dRect);
					break;
				case '9':
					srcRect.x = 4 * 32, srcRect.y = 1 * 32;
					TM->Draw(mapTex, srcRect, dRect);
					break;
				case 'a':
					srcRect.x = 0 * 32, srcRect.y = 2 * 32;
					TM->Draw(mapTex, srcRect, dRect);
					break;
				case 'b':
					srcRect.x = 1 * 32, srcRect.y = 2 * 32;
					TM->Draw(mapTex, srcRect, dRect);
					break;
				case 'c':
					srcRect.x = 2 * 32, srcRect.y = 2 * 32;
					TM->Draw(mapTex, srcRect, dRect);
					break;
				case 'd':
					srcRect.x = 3 * 32, srcRect.y = 2 * 32;
					TM->Draw(mapTex, srcRect, dRect);
					break;
				case 'e':
					srcRect.x = 4 * 32, srcRect.y = 2 * 32;
					TM->Draw(mapTex, srcRect, dRect);
					break;
				case 'D':
					if (roomislock)
					{
						srcRect.x = 2 * 32, srcRect.y = 0 * 32;
						TM->Draw(mapTex, srcRect, dRect);
					}
					else
					{
						srcRect.x = srcRect.y = 0;
						TM->Draw(mapTex, srcRect, dRect);
					}
					break;
				case 'F':
					srcRect.x = 2 * 32, srcRect.y = 0 * 32;
					TM->Draw(mapTex, srcRect, dRect);
					break;
				default:
					break;
				}
			}
		}
	}
	else
	{
		xstart = x / 32 - 10;
		ystart = y / 32 - 7;
		//ystart *= 32;
	
		for (int i = ystart; i < ystart + 15; i++)
		{
			for (int j = xstart; j < xstart + 20; j++)
			{
				type = map[i][j];
				dRect.x = (j - xstart) * 32-x%32;
				dRect.y = (i - ystart) * 32-y%32;

				switch (type)
				{
				case '0':
					srcRect.x = srcRect.y = 0;
					TM->Draw(mapTex, srcRect, dRect);
					break;
				case '1':
					srcRect.x = 2 * 32, srcRect.y = 0 * 32;
					TM->Draw(mapTex, srcRect, dRect);
					break;
				case '2':
					srcRect.x = 1 * 32, srcRect.y = 0 * 32;
					TM->Draw(mapTex, srcRect, dRect);
					break;
				case '3':
					srcRect.x = 3 * 32, srcRect.y = 0 * 32;
					TM->Draw(mapTex, srcRect, dRect);
					break;
				case '4':
					srcRect.x = 4 * 32, srcRect.y = 0 * 32;
					TM->Draw(mapTex, srcRect, dRect);
					break;
				case '5':
					srcRect.x = 0 * 32, srcRect.y = 1 * 32;
					TM->Draw(mapTex, srcRect, dRect);
					break;
				case '6':
					srcRect.x = 1 * 32, srcRect.y = 1 * 32;
					TM->Draw(mapTex, srcRect, dRect);
					break;
				case '7':
					srcRect.x = 2 * 32, srcRect.y = 1 * 32;
					TM->Draw(mapTex, srcRect, dRect);
					break;
				case '8':
					srcRect.x = 3 * 32, srcRect.y = 1 * 32;
					TM->Draw(mapTex, srcRect, dRect);
					break;
				case '9':
					srcRect.x = 4 * 32, srcRect.y = 1 * 32;
					TM->Draw(mapTex, srcRect, dRect);
					break;
				case 'a':
					srcRect.x = 0 * 32, srcRect.y = 2 * 32;
					TM->Draw(mapTex, srcRect, dRect);
					break;
				case 'b':
					srcRect.x = 1 * 32, srcRect.y = 2 * 32;
					TM->Draw(mapTex, srcRect, dRect);
					break;
				case 'c':
					srcRect.x = 2 * 32, srcRect.y = 2 * 32;
					TM->Draw(mapTex, srcRect, dRect);
					break;
				case 'd':
					srcRect.x = 3 * 32, srcRect.y = 2 * 32;
					TM->Draw(mapTex, srcRect, dRect);
					break;
				case 'e':
					srcRect.x = 4 * 32, srcRect.y = 2 * 32;
					TM->Draw(mapTex, srcRect, dRect);
					break;
				case 'D':
					if (roomislock)
					{
						srcRect.x = 2 * 32, srcRect.y = 0 * 32;
						TM->Draw(mapTex, srcRect, dRect);
					}
					else
					{
						srcRect.x = srcRect.y = 0;
						TM->Draw(mapTex, srcRect, dRect);
					}
					break;
				case 'F':
					srcRect.x = 2 * 32, srcRect.y = 0 * 32;
					TM->Draw(mapTex, srcRect, dRect);
					break;
				default:
					break;
				}
			}
		}
	}
}

void Map::reset() {
	createRandomMap();
	loadMap(randommap);
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			if (i == 0 && j==0)
				finished[i][j] = 1;
			else
				finished[i][j] = 0;
		}
	}
	roomislock = true;
}

void Map::playerloadmap(GamePlayer* tmp) {
	tmp->loadMap(map, property);
}
//give player the propertes of map

void Map::monsloadmap(MonsterSpawner* tmp) {
	/*for(int i=0;i<tmp.size();i++)
		tmp[i]->loadMap(map, property);*/
	tmp->loadMap(map, property);
}
//give monster the properties of map

void Map::weaponloadmap(Weapon* tmp) {
	tmp->loadMap(map, property);
}

void Map::locktheroom(int xx, int yy)
{
	if (finished[yy][xx] == false)
	{
		roomislock = true;
		mapupdate = true;
		loadMapProp(map);
		monsloadmap(spawner);
		if (xx == 2 && yy == 2)
			spawner->generateBoss();
		else
		{
			spawner->generateMos(10, xx, yy);
		}
	}
}
bool Map::getmapupdate()
{
	return mapupdate;
}
void Map::unlocktheroom(int xx,int yy)
{
	finished[yy][xx] = true;
	roomislock = false;
	mapupdate = true;
	loadMapProp(map);
}
void Map::setmapupdate(bool b)
{
	mapupdate = b;
}
bool Map::getroomlock()
{
	return roomislock;
}
bool Map::bosswin()
{
	if (finished[2][2])
		return true;
	else
		return false;
}
void Map::setSpawner(MonsterSpawner* s)
{
	spawner = s;
}
SDL_Point createdir(int n)
{
	SDL_Point dir;
	if (n == 5)
	{
		dir.x = rand() % 3 - 1;
		dir.y = rand() % 3 - 1;
	}
	else
	{
		switch (rand() % 8)
		{
		case 0:
			dir.x = 0;
			dir.y = 1;
			break;
		case 1:
			dir.x = 1;
			dir.y = 1;
			break;
		case 2:
			dir.x = 1;
			dir.y = 0;
			break;
		case 3:
			dir.x = 1;
			dir.y = -1;
			break;
		case 4:
			dir.x = 0;
			dir.y = -1;
			break;
		case 5:
			dir.x = -1;
			dir.y = -1;
			break;
		case 6:
			dir.x = -1;
			dir.y = 0;
			break;
		case 7:
			dir.x = -1;
			dir.y = 1;
			break;
		}
	}
	return dir;
}
bool checkfitornot(int x, int y, SDL_Point dir, int n, char** room)
{
	if (dir.x != 0 || dir.y != 0)
	{
		if (y + dir.y * (n - 1) < 0 || y + dir.y * (n - 1) > 14 || x + dir.x * (n - 1) < 0 || x + dir.x * (n - 1) > 19)
			return false;
		for (int i = 0; i < n; i++)
		{
			if (room[y + dir.y * i][x + dir.x * i] == '1' || room[y + dir.y * i + 1][x + dir.x * i] == '1' || room[y + dir.y * i - 1][x + dir.x * i] == '1' || room[y + dir.y * i][x + dir.x * i + 1] == '1' || room[y + dir.y * i][x + dir.x * i - 1] == '1')
				return false;
			if (room[y + dir.y * i][x + dir.x * i] == '2' || room[y + dir.y * i + 1][x + dir.x * i] == '2' || room[y + dir.y * i - 1][x + dir.x * i] == '2' || room[y + dir.y * i][x + dir.x * i + 1] == '2' || room[y + dir.y * i][x + dir.x * i - 1] == '2')
				return false;
		}
	}
	else
	{
		if (room[y][x] == '1' || room[y + 1][x] == '1' || room[y + 1][x - 1] == '1' || room[y + 1][x + 1] == '1' || room[y][x - 1] == '1' || room[y][x + 1] == '1' || room[y + 1][x] == '1' || room[y + 1][x - 1] == '1' || room[y + 1][x + 1] == '1')
			return false;
		if (room[y + 2][x] == '1' || room[y - 2][x] == '1' || room[y][x + 2] == '1' || room[y][x - 2] == '1')
			return false;
		if (room[y][x] == '2' || room[y + 1][x] == '2' || room[y + 1][x - 1] == '2' || room[y + 1][x + 1] == '2' || room[y][x - 1] == '2' || room[y][x + 1] == '2' || room[y + 1][x] == '2' || room[y + 1][x - 1] == '2' || room[y + 1][x + 1] == '2')
			return false;
		if (room[y + 2][x] == '2' || room[y - 2][x] == '2' || room[y][x + 2] == '2' || room[y][x - 2] == '2')
			return false;
	}
	return true;
}
void placethewall(int x, int y, SDL_Point dir, int n, char** room)
{
	if (dir.x != 0 || dir.y != 0)
	{
		for (int i = 0; i < n; i++)
		{
			room[y + i * dir.y + 1][x + i * dir.x] = '2';
			room[y + i * dir.y - 1][x + i * dir.x] = '2';
			room[y + i * dir.y][x + i * dir.x + 1] = '2';
			room[y + i * dir.y][x + i * dir.x - 1] = '2';
			room[y + i * dir.y][x + i * dir.x] = '1';
		}
		for (int i = 0; i < n; i++)
		{
			room[y + i * dir.y][x + i * dir.x] = '3';
		}

	}
	else
	{
		room[y - 2][x] = '2';
		room[y + 2][x] = '2';
		room[y][x - 2] = '2';
		room[y][x + 2] = '2';
		room[y - 1][x - 1] = '2';
		room[y - 1][x + 1] = '2';
		room[y + 1][x - 1] = '2';
		room[y + 1][x + 1] = '2';
		room[y - 1][x] = '3';
		room[y + 1][x] = '3';
		room[y][x - 1] = '3';
		room[y][x + 1] = '3';
		room[y][x] = '3';
	}
}
void placeice(char** room)
{
	int x, y, size, num;
	bool fit = 0;
	num = rand() % 4;
	//printf("num=%d\n", num);
	for (int k = 0; k < num; k++)
	{
		size = rand() % 2 + 2;
		fit = 0;
		while (!fit)
		{
			x = rand() % (19 - size) + 1;
			y = rand() % (14 - size) + 1;
			if (size == 2)
			{
				if (room[y][x] == '0' && room[y + 1][x] == '0' && room[y][x + 1] == '0' && room[y + 1][x + 1] == '0')
					fit = 1;
			}
			else if (size == 3)
			{
				if (room[y + 1][x] == '0' && room[y][x + 1] == '0' && room[y + 1][x + 1] == '0' && room[y + 2][x + 1] == '0' && room[y + 1][x + 2] == '0')
					fit = 1;
			}
		}
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				if (room[y + i][x + j] == '0')
					room[y + i][x + j] = '2';

			}
		}
	}
}
void placeheart(char** room)
{
	int num = rand() % 4;
	bool fit = 0;
	int x, y;
	if (num == 1)
	{
		fit = 0;
		while (!fit)
		{
			x = rand() % 17 + 1;
			y = rand() % 12 + 1;

			if (room[y][x] == '0' && room[y + 1][x] == '0' && room[y][x + 1] == '0' && room[y + 1][x + 1] == '0')
				fit = 1;
		}
		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				room[y + i][x + j] = '8';
			}
		}
	}
}
void placeswamp(char** room)
{
	int num = rand() % 2;
	bool fit = 0;
	int x, y;
	if (num == 1)
	{
		fit = 0;
		while (!fit)
		{
			x = rand() % 17 + 1;
			y = rand() % 12 + 1;

			if (room[y][x] == '0' && room[y + 1][x] == '0' && room[y][x + 1] == '0' && room[y + 1][x + 1] == '0')
				fit = 1;
		}
		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				room[y + i][x + j] = '4';
			}
		}
	}
}
void placerecovery(char** room)
{
	int num = rand() % 2;
	bool fit = 0;
	int x, y;
	if (num == 1)
	{
		fit = 0;
		while (!fit)
		{
			x = rand() % 17 + 1;
			y = rand() % 12 + 1;

			if (room[y][x] == '0' && room[y + 1][x] == '0' && room[y][x + 1] == '0' && room[y + 1][x + 1] == '0')
				fit = 1;
		}
		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				room[y + i][x + j] = '9';
			}
		}
	}
}
void Map::createRandomMap()
{
	for (int i = 0; i < MAPY; i++)
	{
		for (int j = 0; j < MAPX; j++)
		{
			if (j != 100)
				randommap[i][j] = ' ';
			else
				randommap[i][j] = '\0';
		}
	}
	for (int i = 0; i < MAPY; i++)
	{
		for (int j = 0; j < MAPX; j++)
		{
			if (i % 30 == 0 || i % 30 == 14)
			{
				if (j % 40 < 20)
					randommap[i][j] = '1';
			}
			else if (i % 30 == 5 || i % 30 == 10)
			{
				if (j % 40 > 19)
					randommap[i][j] = '1';
			}
			if (j % 40 == 0 || j % 40 == 19)
			{
				if (i % 30 < 15)
					randommap[i][j] = '1';
			}
			else if (j % 40 == 7 || j % 40 == 12)
			{
				if (i % 30 > 14)
					randommap[i][j] = '1';
			}
			if (j % 40 >= 1 && j % 40 <= 18 && i % 30 >= 1 && i % 30 <= 13)
				randommap[i][j] = '0';
			if (j % 40 > 19 && i % 30 >= 6 && i % 30 <= 9)
				randommap[i][j] = '0';
			if (i % 30 > 14 && j % 40 >= 8 && j % 40 <= 11)
				randommap[i][j] = '0';
			if (j == 19 || j == 40 || j == 59 || j == 80)
			{
				if (i % 30 >= 6 && i % 30 <= 9)
					randommap[i][j] = 'D';
			}
			if (i == 14 || i == 30 || i == 44 || i == 60)
			{
				if (j % 40 >= 8 && j % 40 <= 11)
					randommap[i][j] = 'D';
			}

		}
	}
	for (int r = 0; r < 9; r++)
	{
		int n = rand() % 3;
		n += 3;
		int* arr;
		arr = new int[n];
		char** room;
		room = new char* [15];
		for (int i = 0; i < 15; i++)
			room[i] = new char[20];
		for (int i = 0; i < 15; i++)
		{
			for (int j = 0; j < 20; j++)
			{
				if (i == 0 || i == 14 || j == 0 || j == 19)
					room[i][j] = '1';
				else
					room[i][j] = '0';
			}
		}
		for (int i = 0; i < n; i++)
		{
			arr[i] = rand() % 3 + 3;
		}
		for (int i = 0; i < n; i++)
		{
			int x, y;
			SDL_Point dir;
			bool fit = 0;
			while (!fit)
			{

				x = rand() % 16 + 2;
				y = rand() % 11 + 2;
				dir = createdir(arr[i]);
				//printf("%d, %d\n", dir.x, dir.y);

				fit = checkfitornot(x, y, dir, arr[i], room);
				if (fit)
				{
					placethewall(x, y, dir, arr[i], room);
				}

			}
		}
		//copythewalltorandimmap
		for (int i = 1; i < 14; i++)
		{
			for (int j = 1; j < 19; j++)
			{
				if (room[i][j] == '2')
					room[i][j] = '0';
			}
		}
		//placeotherobject
		placeice(room);
		placeheart(room);
		placeswamp(room);
		placerecovery(room);
		//copythewalltorandimmap
		for (int i = 1; i < 14; i++)
		{
			for (int j = 1; j < 19; j++)
			{
				//if (room[i][j] != '2')
				if (r == 4 && room[i][j] == '3')
				{
					randommap[r / 3 * 30 + i][r % 3 * 40 + j] = '0';
				}
				else
					randommap[r / 3 * 30 + i][r % 3 * 40 + j] = room[i][j];
				//else
					//randommap[r / 3 * 30 + i][r % 3 * 40 + j] = '0';
			}
		}
	}
	/*for (int i = 0; i < MAPY; i++)
	{
		for (int j = 0; j < MAPX - 1; j++)
		{
			printf("%c", randommap[i][j]);
		}
		printf("\n");
	}*/
}