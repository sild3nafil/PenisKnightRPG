#pragma once
#include "GameMonster.h"
#include "Bullet.h"
#include "Mixer.h"
#include "constants.h"

class Slime : public GameMonster
{
public:
	Slime(const char* filename, float x, float y, int hp, int atk, int vw, int n, int wwn, int hhn, int id);
	virtual ~Slime();
	void update(GamePlayer*);
	void render();
	void attack(GamePlayer*);
	void close();
	void rez(float, float);
	void shot();
private:
	static const int MAX_BULLET = 10;
	int sword_cooldown = 0;
	Bullet* bullet[MAX_BULLET];
	Mixer* effect_shot;
	bool stopMoving;
	double rad;
};

