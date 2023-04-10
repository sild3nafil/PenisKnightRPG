#pragma once
#include "vector2.h"
#include "GamePlayer.h"
#include "GameMonster.h"
#include "Woman.h"
#include "Rat.h"
#include "Slime.h"
#include "Tower.h"
#include "Healer.h"
#include "GameBoss.h"
#include "TextureManager.h"

#define MAPX 101
#define MAPY 75
class Map;
class MonsterSpawner
{
public:
	MonsterSpawner();
	~MonsterSpawner();
	
	vector2 setrandomXY();
	void push_back(vector2 tmp);
	void clear();
	void generateMos(int n, int xx, int yy);
	void generateBoss();
	void generateTower(float, float);
	void generateHealer();

	void update(GamePlayer*);
	void render();
	void loadMap(const char[MAPY][MAPX], const bool[MAPY][MAPX]);
	vector<GameMonster*> getmstData() { return mst; }

	int getmstnum() { return mst.size(); }
	void setMap(Map*);

	bool boss_fight = false;
private:
	vector<GameMonster*> mst;
	const int MAX=20;

	static const int WOMAN_MAX = 5;
	static const int RAT_MAX = 5;
	static const int SLIME_MAX = 5;
	static const int TOWER_MAX = 3;
	Woman* woman[WOMAN_MAX];
	Rat* rat[RAT_MAX];
	Slime* slime[SLIME_MAX];
	Tower* tower[TOWER_MAX];
	Healer* healer;
	GameBoss* skull;
	
	int ratdie = 0;
	vector2 ratdiepos;

	bool mapProperty[MAPY][MAPX];
	char mapItem[MAPY][MAPX];
	TextureManager* TM;
	Map* map;
};

