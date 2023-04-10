#pragma once
#include "GameObject.h"
#include "TextureManager.h"
#include "Mixer.h"

class GameMonster;
class HealthPoint;

class GamePlayer : public GameObject
{
public:
	GamePlayer(const char* filename, float x, float y);
	GamePlayer(const char* filename, float x, float y, int n, int wwn, int hhn);
	virtual ~GamePlayer();
	void update();
	void render();
	void reset();
	void close();
	void Move(float xx, float yy);
	void setFriction(bool);
	
	bool isAlive();
	void recover();
	void bleeding(int);
	void lossMP(int);
	void Attack(); //preparing

	bool getin;
private:
	int recoverCoolDown=100;
	bool friction;
	SDL_Texture* playerTex;
	HealthPoint* hpbar;
	HealthPoint* mpbar;
	Mixer* effect_hurt;

	static Uint32 changeData(Uint32 interval, void* param);
};

