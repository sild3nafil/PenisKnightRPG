#pragma once
#include "WeaponItem.h"
#include "Text.h"

class Snipershot : public WeaponItem
{	
public:
	Snipershot();
	~Snipershot();

	void update(float xpos, float ypos, double rad, vector<GameMonster*> mst);
	void render();
	void shot(vector<GameMonster*> mst);
	void reload();
	void aim(float xpos, float ypos, double rad, vector<GameMonster*> mst);
	bool harmMons(GameMonster* mst,int n);
	void turnoff() { active = false, energy = 1; }
	void turnon() { active = true; }
	int getEnergy() { return energy; }
	int getEMAX() { return EMAX; }
	int getBullet() { return bullet; }
	
private:
	bool gettarget;
	int semem_time;
	int bullet;
	HealthPoint* energybar;
	SDL_Texture* semem;
	Text* bullet_num;
	char b_num[2];
};

