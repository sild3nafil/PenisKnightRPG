#pragma once
#include "WeaponItem.h"

class Portalring : public WeaponItem
{
public:
	Portalring();
	~Portalring();

	void update(GamePlayer*);
	void render();
	void reset();
	bool checkcollision(float ,float,int n);
	void enter(GamePlayer*);
	void sendblue(float,float,double r);
	void sendoran(float,float,double r);

private:
	vector2 move1;
	vector2 move2;
	bool blue_on;
	bool oran_on;
	bool blue_reach;
	bool oran_reach;
	SDL_Texture* bluering;
	SDL_Texture* oranring;

};

