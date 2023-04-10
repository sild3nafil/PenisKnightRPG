#pragma once
#include "Text.h"
#include "GameObject.h"
#include "GamePlayer.h"
#include "Map.h"
#include "Weapon.h"
#include "TextureManager.h"
#include "Mixer.h"
#include "constants.h"
class Game;

class GameMenu
{
public:
	GameMenu();
	~GameMenu();

	void HandleEvent_opening(SDL_Event& e, Game* g);
	void HandleEvent_weapon_select(SDL_Event& e, Game* g, Weapon* w);
	void HandleEvent_shop(SDL_Event& e, Game* g, GamePlayer* p, Weapon* w);
	void HandleEvent_intro(SDL_Event& e, Game* g);
	void HandleEvent_pause(SDL_Event& e,Game* g);
	void HandleEvent_die(SDL_Event& e, Game* g);
	void HandleEvent_win(SDL_Event& e, Game* g);

	void render_opening();
	void render_weapon_select();
	void render_shop();
	void render_intro();
	void render_pause();
	void render_die();
	void render_win();
	void setMusic(Mixer* m) { music = m; }

	bool foolproof();

	static const int weapon_num = 10;
	bool purchase[weapon_num];
	int price[weapon_num] = { 0,100,150,250,999,690,777,3000,5555,50 };
	bool selected_shop[weapon_num] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	bool selected_play[weapon_num];
private:
	bool shop_page[3] = { 0, 0, 0 };
	bool intro_page[3] = { 0, 0, 0 };
	
	static const int pause_num = 3;
	static const int opening_num = 4;

	const char* labels[pause_num] = { "Continue", "Home", "Exit" };
	bool selected_pause[pause_num] = { 0, 0, 0 };
	Text pause[pause_num];
	Text wasted;
	Text winner;
	Text warning;

	int warning_cd;

	TextureManager* TM;
	SDL_Color color[pause_num] = { {255, 255, 255}, {255, 0, 0} };

	SDL_Texture* background;
	SDL_Texture* poopnum;

	SDL_Texture* Title;
	SDL_Texture* Intro[3];
	SDL_Texture* Shop;
	SDL_Texture* button_buy;
	SDL_Texture* button_pick;
	SDL_Texture* button_null;
	SDL_Texture* button_next;
	SDL_Texture* button_last;

	SDL_Texture* button_play;
	SDL_Texture* button_shop;
	SDL_Texture* button_intro;
	SDL_Texture* button_exit;
	SDL_Texture* button_lastpage;
	bool selected_opening[opening_num] = { 0,0,0,0 };
	SDL_Rect srcRect_opening[opening_num] = { {0,0,128,44},{0,0,128,44},{0,0,128,44},{0,0,128,44} };
	SDL_Rect dRect_opening[opening_num] = { {256,132,128,44},{256,220,128,44},{256,308,128,44},{256,396,128,44} };
	Mixer* effect_select;
	Mixer* effect_buy;
	Mixer* effect_fail;
	Mixer* music;
};

