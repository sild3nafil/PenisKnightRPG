#pragma once
#include "WeaponItem.h"

class Banana : public WeaponItem
{
public:
	Banana();
	Banana(const char* filename, int a);
	~Banana();

	void update(vector<GameMonster*> mst,GamePlayer* player);
	void update(GamePlayer* player);
	void render();
	void throw_Banana(float, float, double);
	void reload();
	bool harmMons(GameMonster*);
	bool harmPlayer(GamePlayer*);
	bool checkCollision();
	bool arrive(GamePlayer*);
	bool arrive();

	void startTimer(Uint32 t);
	void stopTimer();
	static Uint32 changeData(Uint32 interval, void* param);
private:
	int cooldown;
	bool rebound;

	int frame = 0;
	int num = 4;
	int hn = 1;
	int wn = 4;
	int wPic;
	int hPic;

	SDL_Texture* bananaTex;
	SDL_TimerID timerID;
	Uint32 time;
	vector2 originpos;
};

