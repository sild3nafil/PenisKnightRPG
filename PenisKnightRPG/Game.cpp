#include "Game.h"
#include "TextureManager.h"
#include "GameMenu.h"
#include "GameObject.h"
#include "GamePlayer.h"
#include "GameMonster.h"
#include "MonsterSpawner.h"
#include "Weapon.h"
#include "HealthPoint.h"
#include "Map.h"
#include "Smallmap.h"
#include "Mixer.h"
#include "Text.h"
#include "constants.h"

GameMenu* menu;
GamePlayer* player; //create player object
MonsterSpawner* spawner; //create monster object
Weapon* weapon;
Map* map; //create map object
Smallmap* smap;
TextureManager* TM;
Mixer* music;
Mixer* effect_win;
Text* coin;
Mouse ms;

SDL_Renderer* Game::renderer = nullptr; //create rendere
vector2 pos;

void moveHandleEvent(SDL_Event& e);
void keyboardHandleEvent(SDL_Event& e, Game* g);
void mouseHandleEvent(SDL_Event* e, Mouse* m, Game*);

Game::Game() {

}

Game::~Game() {

}

void Game::init(const char* title, int xpos, int ypos, int width, int height, bool resize_screen) {
	int flags = 0;
	FILE* load_coin;

	fopen_s(&load_coin, "file/coin.txt", "r");
	fscanf_s(load_coin, "%d", &game_coin);
	fclose(load_coin);
	_itoa_s(game_coin, game_coin_s, 10);
	isAttack = false;
	//printf("%s\n", game_coin_s);

	if (resize_screen)
	{
		flags = SDL_WINDOW_RESIZABLE;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		cout << "System Initialized" << endl;

		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		if (window)
		{
			cout << "window created successfully" << endl;
		}

		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer)
		{
			SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
			SDL_RenderSetLogicalSize(renderer, 640, 480);
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			cout << "renderer created succesfully" << endl;
		}

		if (TTF_Init() == -1)
			printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
		
		if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
			// https://www.libsdl.org/projects/SDL_mixer/docs/SDL_mixer_frame.html
			printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());

		isRunning = true;
	}
	ms.count = 0;
	cointex = TM->LoadTexture("assets/coin.png");
	coin = new Text("fonts/FFFFORWA.TTF", game_coin_s, 640 - 64, 2, 15, { 255,255,255 });

	menu = new GameMenu();
	cout << "Menu loaded successfully" << endl;
	player = new GamePlayer("assets/player_animation.png", 640/2, 480/2, 16, 4, 4);
	cout << "player loaded successfully" << endl;
	spawner = new MonsterSpawner();
	cout << "enemy loaded successfully" << endl;
	map = new Map();
	cout << "map loaded successfully" << endl;
	smap = new Smallmap();
	cout << "smallmap loaded successfully" << endl;
	weapon = new Weapon();
	cout << "weapon loaded successfully" << endl;

	player->SetCoin(game_coin);
	player->setMap(map);
	spawner->setMap(map);
	map->setSpawner(spawner);

	map->monsloadmap(spawner);
	map->playerloadmap(player);
	map->weaponloadmap(weapon);

	music = new Mixer("audio/background.mp3", MUSIC);
	effect_win = new Mixer("audio/win.mp3", EFFECT);
	menu->setMusic(music);
	//music->play(FOREVER);
}
//initialize and load png to object which needed

void Game::handleEvent() {
	SDL_Event event;
	SDL_PollEvent(&event);

	if (opening)
		menu->HandleEvent_opening(event, this);
	else if (weapon_select)
		menu->HandleEvent_weapon_select(event, this, weapon);
	else if (intro)
		menu->HandleEvent_intro(event, this);
	else if (shop)
		menu->HandleEvent_shop(event, this, player, weapon);
	else if (pause)
		menu->HandleEvent_pause(event, this);
	else if (win)
		menu->HandleEvent_win(event, this);
	else if (die)
		menu->HandleEvent_die(event, this);
	else
	{
		moveHandleEvent(event);
		keyboardHandleEvent(event, this);
		mouseHandleEvent(&event, &ms, this);
		if (getisAttack())
			if (weapon->isActive())
				weapon->attack(spawner->getmstData());

		if (player->ShowHP() <= 0)
			die = 1;
		if (map->bosswin())
		{
			effect_win->playEffect(ONE, -1);
			win = 1;
		}
	}
}
//handle event and control by keyboard
//esc to quit

void Game::update() {
	if (!pause||!win)
	{
		if (!spawner->getmstnum() && map->getroomlock())
			map->unlocktheroom((int)player->getrealxpos()/640,(int)player->getrealypos()/480);
		if (map->getmapupdate())
		{
			map->monsloadmap(spawner);
			map->playerloadmap(player);
			map->weaponloadmap(weapon);
			map->setmapupdate(false);
		}
		player->update();
		if (!player->getroomornot())
			clear();
		spawner->update(player);
		weapon->update(spawner->getmstData(), player, ms.x, ms.y);

		game_coin = player->GetCoin();
		_itoa_s(game_coin, game_coin_s, 10);
		coin->update(game_coin_s);
	}
}
//update the pos.

void Game::render() {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0,255);
	SDL_RenderClear(renderer);

	if (pause)
	{
		map->drawMap(player);
		player->render();
		spawner->render();
		weapon->render();
		
		TM->DrawFilledRect(0, 0, 640, 480, 182, 182, 182, 150);
		TM->Draw(cointex, { 0,0,32,32 }, { 640 - 96,0,32,32 });
		coin->render();
		menu->render_pause();
	}
	else if (die)
	{
		map->drawMap(player);
		player->render();
		spawner->render();
		weapon->render();
		
		TM->DrawFilledRect(0, 0, 640, 480, 210, 210, 210, 150);
		TM->Draw(cointex, { 0,0,32,32 }, { 640 - 96,0,32,32 });
		coin->render();
		menu->render_die();
	}
	else if (win)
	{
		map->drawMap(player);
		player->render();
		spawner->render();
		weapon->render();

		TM->DrawFilledRect(0, 0, 640, 480, 182, 182, 182, 150);
		TM->Draw(cointex, { 0,0,32,32 }, { 640 - 96,0,32,32 });
		coin->render();
		menu->render_win();
	}
	else if (opening)
	{
		menu->render_opening();
	}
	else if (weapon_select)
	{
		menu->render_weapon_select();
		weapon->poop->render();
	}
	else if (shop)
	{
		menu->render_shop();
		weapon->poop->render();
		TM->Draw(cointex, { 0,0,32,32 }, { 640 - 96,0,32,32 });
		coin->render();
	}	
	else if (intro)
	{
		menu->render_intro();
	}
	else
	{
		map->drawMap(player);
		player->render();
		spawner->render();
		weapon->render();

		TM->Draw(cointex, { 0,0,32,32 }, { 640 - 96,0,32,32 });
		coin->render();
		if(smap_on)
			smap->render(player);
	}

	SDL_RenderPresent(renderer);
}
//show it on the window
void Game::reset()
{
	clear();
	weapon->changeMode(0);
	for(int i=0;i<10;i++)
		menu->selected_play[i] = 0;
	player->reset();
	map->reset();
	
}

void Game::clear()
{
	spawner->clear();
	weapon->clear();
}

void Game::clean() {
	game_coin = player->GetCoin();
	FILE* store_coin;
	FILE* purchased;
	FILE* poopnum;

	fopen_s(&store_coin, "file/coin.txt", "w");
	fprintf(store_coin, "%d", game_coin);
	fclose(store_coin);
	fopen_s(&purchased, "file/purchase.dat", "wb");
	fwrite(menu->purchase, sizeof(menu->purchase), 1, purchased);
	fclose(purchased);
	fopen_s(&poopnum, "file/poopnum.txt", "w");
	fprintf(poopnum, "%d", weapon->poop->Getpoopnum());
	fclose(poopnum);

	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	Mix_Quit();
	TTF_Quit();
	cout << "Game Ended" << endl << "Get " << game_coin << " Coins" << endl;
	cout << "purshased: ";
	for(int i=0;i<10;i++)
		cout<< menu->purchase[i] << " ";
}
//clean the window and close it

void moveHandleEvent(SDL_Event& e)
{
	switch (e.type)
	{
	case SDL_KEYDOWN:
		switch (e.key.keysym.sym)
		{
		case SDLK_a:
			//printf("你按下了←\n");
			player->Move(-1, 0);
			break;
		case SDLK_d:
			//printf("你按下了→\n");
			player->Move(1, 0);
			break;
		case SDLK_w:
			//printf("你按下了↑\n");
			player->Move(0, -1);
			break;
		case SDLK_s:
			//printf("你按下了↓\n");
			player->Move(0, 1);
			break;
		/*case SDLK_SPACE:
			pos=spawner->setrandomXY();
			spawner->push_back(pos);
			break;*/
		}
		break;
	case SDL_KEYUP:
		switch (e.key.keysym.sym)
		{
		case SDLK_a:
			//printf("你松開了←\n");
			player->Move(0, 0);
			break;
		case SDLK_d:
			//printf("你松開了→\n");
			player->Move(0, 0);
			break;
		case SDLK_w:
			//printf("你松開了↑\n");
			player->Move(0, 0);
			break;
		case SDLK_s:
			//printf("你松開了↓\n");
			player->Move(0, 0);
			break;
		}
		break;
	}
}
void keyboardHandleEvent(SDL_Event &e,Game* g)
{
	switch (e.type)
	{
	case SDL_QUIT:
		g->isRunning = false;
		break;
	case SDL_KEYDOWN:
		switch (e.key.keysym.sym)
		{
		case SDLK_LSHIFT:
			//printf("speeding up\n");
			player->Speed(4);
			break;
		case SDLK_r:
			weapon->sniperReload();
			break;
		case SDLK_x:
			g->clear();
			break;
		case SDLK_ESCAPE:
			//printf("tsaimotheriloveyou\n");
			g->pause = true;
			break;
		case SDLK_TAB:
			g->smap_on = true;
			break;
		}
		break;
	case SDL_KEYUP:
		switch (e.key.keysym.sym)
		{
		case SDLK_LSHIFT:
			//printf("normal speed\n");
			player->Speed(2);
			break;
		case SDLK_TAB:
			g->smap_on = false;
			break;
		}
		break;
	default:
		break;
	}
}
void mouseHandleEvent(SDL_Event* e, Mouse* m,Game* g)
{
	// If mouse event happened
	// https://wiki.libsdl.org/SDL_Event
	// https://wiki.libsdl.org/SDL_MouseMotionEvent
	// https://wiki.libsdl.org/SDL_MouseButtonEvent
	// https://wiki.libsdl.org/SDL_MouseWheelEvent
	int width, height;
	SDL_GetWindowSize(g->getWin(), &width, &height);
	weapon->setwh(width,height);

	if (e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP || e->type == SDL_MOUSEWHEEL)
	{
		// Get mouse position
		// https://wiki.libsdl.org/SDL_GetMouseState		
		SDL_GetMouseState(&(m->x), &(m->y));
		/*printf("%d %d\n", m->x, m->y);
		m->x = (int)(((float)width / 680) * m->x);
		m->y = (int)(((float)height / 480) * m->y);*/

		// Mouse is at left/right/above/below of the button. Mouse is outside the button
		if (m->x < 0 || m->x > width || m->y < 0 || m->y > height)
		{
			m->state = OUT;
		}
		else // Mouse is inside button
		{
			static int lasttime = SDL_GetTicks64();
			static int curtime = SDL_GetTicks64();
			static int tmp = 0;
			int timediv;

			lasttime = curtime;
			curtime = SDL_GetTicks64();
			timediv = curtime - lasttime;

			switch (e->type)
			{
			case SDL_MOUSEBUTTONDOWN:
				if (e->button.button == SDL_BUTTON_MIDDLE)
				{
					weapon->send(0);
				}
				if (e->button.button == SDL_BUTTON_LEFT)
				{
					if (player->isAlive())
					{
						g->weapon_turn_on();
						weapon->startTimer(60);
						weapon->Active(true);
						weapon->send(1);
						weapon->summon(player);
						weapon->summon_shark();
						weapon->eat_poop(player);
					}
					/*if (weapon->isActive())
						weapon->attack(spawner->getmstData());*/
				}
				if (e->button.button == SDL_BUTTON_RIGHT)
				{
					if (player->isAlive())
					{
						weapon->startTimer(60);
						weapon->send(2);
					}
				}
				break;

			case SDL_MOUSEBUTTONUP:
				if (e->button.button == SDL_BUTTON_LEFT)
				{
					if (player->isAlive())
					{
						g->weapon_turn_off();
						weapon->sniperShot(spawner->getmstData());
						weapon->musicring_stop();
						weapon->stopTimer();
						weapon->Active(false);
					}
				}
				if (e->button.button == SDL_BUTTON_RIGHT)
				{
					if (player->isAlive())
					{
						weapon->stopTimer();
						weapon->Active(false);
					}
				}
				break;

			case SDL_MOUSEWHEEL:
				if (e->wheel.y > 0) // scroll up
				{
					// Put code for handling "scroll up" here!
					ms.count++;
					ms.count = ms.count % 1 ;
					tmp = (tmp + 1) % 11;
					if (ms.count == 0)
						if (tmp != 0)
						{
							if (menu->selected_play[tmp-1] == true)
							{
								weapon->changeMode(tmp);
							}
							else
							{
								while (1)
								{
									tmp = (tmp + 1) % 11;
									if (tmp == 0 )
									{
										weapon->changeMode(tmp);
										break;
									}
									else if (menu->selected_play[tmp - 1] == true)
									{
										weapon->changeMode(tmp);
										break;
									}
								}
							}
						}
						else
						{
							weapon->changeMode(tmp);
						}
					
					//printf("%d\n", tmp);
				}
				else if (e->wheel.y < 0) // scroll down
				{
					// Put code for handling "scroll down" here!
					ms.count--;
					ms.count = ms.count % 1;
					tmp = fabs((-10 - tmp) % 11);
					if (ms.count == 0)
						if (tmp != 0)
						{
							if (menu->selected_play[tmp - 1] == true)
							{
								weapon->changeMode(tmp);
							}
							else
							{
								while (1)
								{
									tmp = fabs((-10 - tmp) % 11);
									if (tmp == 0)
									{
										weapon->changeMode(tmp);
										break;
									}
									else if (menu->selected_play[tmp - 1] == true)
									{
										weapon->changeMode(tmp);
										break;
									}
								}
							}
						}
						else
						{
							weapon->changeMode(tmp);
						}
				}
				break;

			case SDL_MOUSEMOTION:
				if (player->isAlive())
				{
					m->state = HOVER;
					weapon->setDir(m->x - (player->getxpos() + 15) * width / 640.0, m->y - (player->getypos() + 15) * height / 480.0);
				}
				break;
			}
		}
	}
}