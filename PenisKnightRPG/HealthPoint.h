#pragma once
#include "GameObject.h"
#include "TextureManager.h"
class GamePlayer;
class GameMonster;
class GameBoss;
class Snipershot;

class HealthPoint : public GameObject
{
public:
	HealthPoint(const char* filename, float x, float y);
	HealthPoint(const char* filename, float x, float y, int w, int h);
	virtual ~HealthPoint();
	void update(GamePlayer*) ;
	void update_mp(GamePlayer*);
	void update(GameMonster*);
	void update(GameBoss*);
	void update(Snipershot*);
	void render();
	void render_boss();
	void close();

private:
	int hpline;
	SDL_Texture* hpTex;
};

