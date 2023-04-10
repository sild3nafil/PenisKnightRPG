#pragma once
#include "GameMonster.h"
#include "Bullet.h"
#include "Mixer.h"
#include "constants.h"

class Tower : public GameMonster
{
public:
	Tower(const char* filename, float x, float y, int hp, int atk, int vw, int id);
	virtual ~Tower();
	void update(GamePlayer*);
	void render();
	void attack(GamePlayer*);
	void close();
	void rez(float, float);
	void shot();
	void recover();
private:
	double rad;
	static const int MAX_BULLET = 40;
	Bullet* bullet[MAX_BULLET];
	Mixer* effect_shot;
	vector2 playerpos;
};

