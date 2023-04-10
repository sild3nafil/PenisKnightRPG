#pragma once
#include "WeaponItem.h"
#include "Text.h"

class Poop : public WeaponItem
{
public:
	Poop();
	~Poop();
	void update();
	void render();
	void eat(GamePlayer*);
	void increase();
	void decrease();
	int Getpoopnum() { return poop_num; }

private:
	Text* p_num_t;
	char p_num_s[6];
	const int MAX_POOP_NUM = 99999;
	int poop_num;
};

