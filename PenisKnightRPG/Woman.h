#pragma once
#include "GameMonster.h"

class Woman : public GameMonster
{
public:
	Woman(const char* filename, float x, float y, int hp, int atk, int vw, int n, int wwn, int hhn, int id);
	virtual ~Woman();
	void update(GamePlayer*);
	void attack(GamePlayer*);
	void close();
private:
};

