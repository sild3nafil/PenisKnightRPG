#pragma once
#include "Game.h"
#include "TextureManager.h"
#include "vector2.h"
#include <stdio.h>
#include <math.h>

#define MAPX 101
#define MAPY 75

class Map;

class GameObject
{
public:
	GameObject(const char* filename,float x,float y);
	GameObject(const char* filename, float x, float y, int n, int wwn, int hhn);
	virtual ~GameObject();
	virtual void render();
	virtual void close();
	virtual void Move(float x, float y) { move.x = x * speed; move.y = y * speed; }
	void loadMap(const char[MAPY][MAPX], const bool[MAPY][MAPX]);

	bool checkCollision();
	bool checkEffect();
	bool checkOut();
	bool isAlive();
	void startTimer(Uint32 tt);
	void stopTimer();
	static Uint32 changeData(Uint32 interval, void* param);

	bool getroomornot();
	void checkroomornot();
	void setMap(Map*);

	void setrealXY(float, float);

	void setxpos(float x) { pos.x = x; }
	void setypos(float y) { pos.y = y; }
	float getxpos() { return pos.x; }
	float getypos() { return pos.y; }
	void setrealxpos(float x) { realpos.x = x; }
	void setrealypos(float y) { realpos.y = y; }
	float getrealxpos() { return realpos.x ; }
	float getrealypos() { return realpos.y ; }

	void Speed(int x) { speed = x; }
	void SetBonus(int b) { bonus = -1; }
	virtual void bleeding(int atk) { HP -= atk;}
	void AddHP(int h);
	void onethreeHP() { HP = HP_MAX / 3; }
	void AddMP(int m);
	void SetCoin(int c) { coin = c; }
	void AddCoin(int c) { coin += c; }

	int ShowHP() { return HP; }
	int ShowMP() { return MP; }
	int GetMaxHP() { return HP_MAX; }
	int GetMaxMP() { return MP_MAX; }
	int GetCoin() { return coin; }
	
	int clk=0;
	TextureManager* TM;
	Map* map;
	SDL_Rect srcRect, dRect;
	SDL_Point rad;
	SDL_TimerID timerID;
	Uint32 t;

protected:
	bool alive;

	int frame;
	int frametime;
	int num;
	int wn;
	int hn;
	int wPic;
	int hPic;

	int HP;
	int HP_MAX;
	int MP;
	int MP_MAX;
	int ATK;
	double speed;
	double bonus;
	double waterFriction = -0.1;
	double grassFriction = 0.7;
	int coin;

	bool mapProperty[MAPY][MAPX];
	char mapItem[MAPY][MAPX];

	int roomornot;
	vector2 pos;
	vector2 move;
	vector2 realpos;

private:
	SDL_Texture* objTex;
};