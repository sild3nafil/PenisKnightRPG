#pragma once
#include "GameObject.h"
#include "TextureManager.h"
class GamePlayer;
class HealthPoint;

class GameMonster : public GameObject
{
public:
	GameMonster(const char* filename, float x, float y,int hp, int atk, int vw, int id);
	GameMonster(const char* filename, float x, float y,int hp, int atk, int vw,int n,int wwn,int hhn,int id);
	virtual ~GameMonster();

	virtual void update(GamePlayer *); 
	virtual void attack(GamePlayer*);
	virtual void render(); 
	virtual void close();
	virtual void rez(float, float);
	void reload() { alive = false; }
	void Move(float xx, float yy);
	void checkPlayerDie(GamePlayer *);
	bool getAlive() { return alive; }
	
	
	int code;
	int ATKcooldown;
	int range;
	int view;

	bool super[3];
	void super_state(bool a, bool b, bool c) { super[0] = a, super[1] = b, super[2] = c; }
	virtual int getStage();
	int getID() { return code; }
protected:
	HealthPoint* hpbar;
	SDL_Texture* monsTex;

private:
	static Uint32 changeData(Uint32 interval, void* param);
};

