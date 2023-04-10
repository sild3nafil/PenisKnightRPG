#pragma once
#include "WeaponItem.h"

class Lazerbeam : public WeaponItem
{
public:
	Lazerbeam();
	~Lazerbeam();

	void render();
	void update(float, float, double, vector<GameMonster*> mst);
	void launch(float, float, double, vector<GameMonster*> mst);
	void launchrebound(int, int, vector<GameMonster*> mst);
	bool harmMons(GameMonster* mst,int n);
	void turnoff() { active = false; }
	void turnon() { active = true; }

private:
	bool gettarget;
	int energy;
};

