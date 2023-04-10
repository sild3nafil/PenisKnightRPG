#pragma once
#include "WeaponItem.h"
class Musicring : public WeaponItem
{
public:
	Musicring();
	~Musicring();
	void update(float x, float y);
	void render();
	void reset();
	void play(float, float);
private:
	int radius;
	SDL_Color rainbow[7] = { {255,0,0},{255,127,0},{255,255,0},{0,255,0},{0,0,255},{75,0,130},{148,0,211} };
	int color_index;
};

