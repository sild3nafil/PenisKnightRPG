#pragma once
#include "WeaponItem.h"

class SharkBite : public WeaponItem
{
public:
	SharkBite();
	~SharkBite();
	void update(vector<GameMonster*> mst, GamePlayer* p, float msx, float msy, int w, int h);
	void render();
	void summon();
	void reload();
	void close();
	bool harmMons(GameMonster*);

	void startTimer(Uint32 t);
	void stopTimer();
	static Uint32 changeData(Uint32 interval, void* param);
	
private:
	int range = 200;
	int lasting;
	bool summon_shark;

	int frame = 0;
	int num = 4;
	int hn = 1;
	int wn = 4;
	int wPic;
	int hPic;

	SDL_Texture* sharkTex;
	SDL_TimerID timerID;
	Uint32 time;
};

