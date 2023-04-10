#pragma once
#include "GameMonster.h"
#include "Mixer.h"
#include "constants.h"

class Rat : public GameMonster
{
public:
	Rat(const char* filename, float x, float y, int hp, int atk, int vw, int n, int wwn, int hhn, int id);
	virtual ~Rat();
	void update(GamePlayer*);
	void attack(GamePlayer*);
	void close();
	
private:
	bool boom = false;
	Mixer* effect;
};

