#pragma once
#include "TextureManager.h"
#include "GameMonster.h"
#include "Mixer.h"
#include "Text.h"
#include "constants.h"

#include "Bullet.h"
#include "Hurricane.h"
#include "Lazerbeam.h"
#include "Portalring.h"
#include "Snipershot.h"
#include "Banana.h"
#include "SharkBite.h"
#include "Musicring.h"
#include "Poop.h"

#define MAPX 101
#define MAPY 75

class Weapon
{
public:
	Weapon();
	~Weapon();

	void render();
	void update(vector<GameMonster*> mst,GamePlayer* p,float msx,float msy);
	void clear();

	void attack(vector<GameMonster*> mst);

	void slash(vector<GameMonster*> mst);
	void fire();
	void summon(GamePlayer* p);
	void summon_shark();
	void throw_Banana();
	void send(int n);
	void sniperShot(vector<GameMonster*> mst);
	void sniperReload();
	void portalBlue();
	void portalOran();
	void musicring_play();
	void musicring_stop();
	void eat_poop(GamePlayer* p);

	void Active(bool);
	bool isActive() { return active; }

	void changeMode(int);
	int getMode() { return mode; }
	void setDir(int, int);
	void setwh(int w, int h) { width = w, height = h; }

	void loadMap(const char[MAPY][MAPX], const bool[MAPY][MAPX]);
	void startTimer(Uint32 t);
	void stopTimer();
	static Uint32 changeData(Uint32 interval, void* param);

	static const int MAX_BULLET = 100;
	static const int MAX_HURRICANE = 69;
	static const int MAX_BANANA = 20;
	static const int MAX_MUSICRING = 14;

	Bullet* bullet[MAX_BULLET];
	Hurricane* hurricane[MAX_HURRICANE];
	Lazerbeam* lazerbeam;
	Portalring* portalring;
	Snipershot* snipershot;
	Banana* banana[MAX_BANANA];
	SharkBite* sharkbite;
	Musicring* musicring[MAX_MUSICRING];
	Poop* poop;

protected:
	SDL_Texture* bullet_icon;
	SDL_Texture* Sword;
	SDL_Texture* Gun;
	SDL_Texture* Magic;
	SDL_Texture* Lazer;
	SDL_Texture* Portalgun;
	SDL_Texture* Sniper;
	SDL_Texture* BananaBoomerang;
	SDL_Texture* Sharkgun;
	SDL_Texture* CDplayer;
	SDL_Texture* Poop_food;

	Mixer* effect_Sword;
	Mixer* effect_Gun;
	Mixer* effect_Magic;
	Mixer* effect_Lazer;
	Mixer* effect_Portalgun;
	Mixer* effect_reset;
	Mixer* effect_Sniper;
	Mixer* effect_reload;
	Mixer* effect_Banana;
	Mixer* effect_shark;
	Mixer* effect_rickroll;
	Mixer* effect_poop;

	Text* bullet_num;

	int sword_cooldown = 0;
	int bullet_cooldown = 0;
	int banana_cooldown = 0;
	int musicring_cooldown = 0;

private:
	int mode;
	int atk;
	int range;
	vector2 pos;
	vector2 realpos;
	vector2 dir;

	double angle;
	double rad;
	bool active = false;
	bool music_on = false;

	int wPic;
	int hPic;

	TextureManager* TM;
	SDL_Rect srcRect, dRect;
	SDL_TimerID timerID;
	Uint32 time;

	int frame;
	int num;
	int wn;
	int hn;

	int width;
	int height;

	bool mapProperty[MAPY][MAPX];
	char mapItem[MAPY][MAPX];
};

