#pragma once
#include "GameMonster.h"
#include "Hurricane.h"
#include "Banana.h"

class GameBoss : public GameMonster
{
public:
	GameBoss(const char* filename, float x, float y, int hp, int atk, int vw, int n, int wwn, int hhn, int id);
	virtual ~GameBoss();
	void update(GamePlayer* player);
	void render();
	void close();
	void rez(float, float);

	void follow(GamePlayer*);
	void follow2(GamePlayer*);
	void attack(GamePlayer*);
	void magic(GamePlayer*);
	void show(GamePlayer*);
	void checkStage();

	void bleeding(int atk);

	void supermode_On(int n) { super[n-1] = true; }
	void supermode_Off(int n) { super[n-1] = false; }
	int getStage();
private:
	int stop_cd = 0;
	int magic_cd = 50;
	int attack_cd = 100;
	int effect_cd = 0;
	int show_cd = 100;
	bool stage[3];
	static const int MAX_HURRICANE = 16;
	static const int MAX_BANANA = 16;
	Hurricane* hurricane[MAX_HURRICANE];
	Banana* banana[MAX_BANANA];

	int radius;
	vector2 effectpos;
	bool iseffect;

	static Uint32 changeData(Uint32 interval, void* param);
};

