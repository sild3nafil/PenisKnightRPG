#pragma once
#include "GameMonster.h"

class Healer : public GameMonster
{
public:
	Healer(const char* filename, float x, float y, int hp, int atk, int vw, int n, int wwn, int hhn, int id);
	virtual ~Healer();
	void update(GamePlayer*);
	void render();
	void close();
	void recover();
	void bleeding(int atk);
private:
	int recover_cd = 0;
	vector2 playerpos;
};

