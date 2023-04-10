#pragma once
#include "WeaponItem.h"
class Hurricane : public WeaponItem
{
public:
	Hurricane();
	Hurricane(const char* filename, int a);
	~Hurricane();

	void update(vector<GameMonster*> mst);
	void update(GamePlayer* player);
	void render();
	void summon(float,float,double);
	void reload();
	bool harmMons(GameMonster*);
	bool harmPlayer(GamePlayer*);
	double getMonsdis(GameMonster*);
	void close();

	void startTimer(Uint32 t);
	void stopTimer();
	static Uint32 changeData(Uint32 interval, void* param);

private:
	vector2 gravity;

	int frame = 0;
	int num = 4;
	int hn = 1;
	int wn = 4;
	int wPic;
	int hPic;

	SDL_Texture* hurricaneTex;
	SDL_TimerID timerID;
	Uint32 time;
};

