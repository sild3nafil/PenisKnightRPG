#pragma once
#include "Game.h"
#include "GameObject.h"
//#include "GamePlayer.h"
#include "GameMonster.h"
#include "MonsterSpawner.h"
#include "Weapon.h"
#include "TextureManager.h"
class GamePlayer;

class Map
{
public:
	Map();
	~Map();

	void loadRandomMap(int, int, char[15][21]);
	void loadMap(char [MAPY][MAPX]);
	void loadMapProp(const char[MAPY][MAPX]);
	void drawMap(GamePlayer* p);
	void reset();
	void monsloadmap(MonsterSpawner*);
	void playerloadmap(GamePlayer*);
	void weaponloadmap(Weapon*);

	bool getmapupdate();
	void setmapupdate(bool);
	void locktheroom(int, int);
	void unlocktheroom(int, int);
	bool getroomlock();
	bool bosswin();
	void setSpawner(MonsterSpawner*);

	friend bool checkfitornot(int, int, SDL_Point, int, char**);
	void createRandomMap();
private:
	TextureManager* TM;
	SDL_Rect srcRect, dRect;

	char randommap[MAPY][MAPX];
	char map[MAPY][MAPX];
	bool property[MAPY][MAPX];
	bool finished[5][5] = {0};
	int lvl;
	int num;
	int wn;
	int hn;

	bool roomislock;
	bool mapupdate;
	MonsterSpawner* spawner;
};

