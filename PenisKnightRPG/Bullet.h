#pragma once
#include "WeaponItem.h"

class Bullet : public WeaponItem
{
public:
	Bullet(const char* filname,int a);
	~Bullet();

	void update(vector<GameMonster*> mst);
	void update(GamePlayer* player);
	void render();
	void fire(float, float, double);
	void reload();
	void close();

	bool checkCollision();
	void bounce(int, int, float, float);
	bool harmMons(GameMonster*);
	bool harmPlayer(GamePlayer*);

private:
	SDL_Texture* bulTex;
};

