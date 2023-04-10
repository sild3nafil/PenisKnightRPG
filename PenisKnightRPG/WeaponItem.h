#pragma once
#include <math.h>
#include "TextureManager.h"
#include "GameMonster.h"
#include "GamePlayer.h"

#define MAPX 101
#define MAPY 75

class WeaponItem
{
public:
	WeaponItem();
	~WeaponItem();
	
	bool Outta();
	bool Active() { return active; }
	void setActive(bool a) { active = a; }

	void loadMap(const char[MAPY][MAPX], const bool[MAPY][MAPX]);
	float getxpos() { return pos.x; }
	float getypos() { return pos.y; }

protected:
	vector2 pos;
	vector2 pos2;
	vector2 pos3;
	vector2 realpos;
	vector2 realpos2;
	vector2 realpos3;
	vector2 move;
	float speed;

	TextureManager* TM;
	SDL_Rect srcRect;
	SDL_Rect dRect;

	int atk;
	int cooldown;
	int energy;
	const int EMAX = 100;
	bool active;
	bool Canrebound;

	bool mapProperty[MAPY][MAPX];
	char mapItem[MAPY][MAPX];

private:
	SDL_Texture* item_Tex;
};

