#include "GameMenu.h"
#include "Game.h"

GameObject* penis;

GameMenu::GameMenu()
{
	FILE* purchased;
	fopen_s(&purchased,"file/purchase.dat", "rb");
	fread(purchase, sizeof(purchase), 1, purchased);
	fclose(purchased);

	penis=new GameObject("assets/penis.png", -64, 480-57);

	pause[0].setbase("fonts/FFFFORWA.TTF", labels[0], 320-75, 70, 24, 150, 50, color[0]);
	pause[1].setbase("fonts/FFFFORWA.TTF", labels[1], 320-75, 70+50+70, 24, 150, 50, color[0]);
	pause[2].setbase("fonts/FFFFORWA.TTF", labels[2], 320-75, 190+50+70, 24, 150, 50, color[0]);
	wasted.setbase("fonts/FFFFORWA.TTF", "WASTED", 320 - 100, 70, 24, 200, 50, { 225,0,0 });
	winner.setbase("fonts/FFFFORWA.TTF", "WINNER WINNER PENIS DINNER", 320-250, 100, 18, 500, 50, { 139, 128, 0 });
	warning.setbase("fonts/FFFFORWA.TTF", "Please at Least Pick 1 Item", 320 - 250, 70, 24, 500, 50, { 225,0,0 });
	background = TM->LoadTexture("assets/opening_background.png");
	poopnum = TM->LoadTexture("assets/poop.png");
	Title = TM->LoadTexture("assets/title.png");
	Shop = TM->LoadTexture("assets/shop_item.png");
	Intro[0] = TM->LoadTexture("assets/intro_1.png");
	Intro[1] = TM->LoadTexture("assets/intro_2.png");
	Intro[2] = TM->LoadTexture("assets/intro_3.png");

	button_buy = TM->LoadTexture("assets/button_buy.png");
	button_pick = TM->LoadTexture("assets/button_pick.png");
	button_null = TM->LoadTexture("assets/null.png");
	button_next = TM->LoadTexture("assets/next.png");
	button_last = TM->LoadTexture("assets/last.png");

	button_play = TM->LoadTexture("assets/button_play.png");
	button_shop = TM->LoadTexture("assets/button_shop.png");
	button_intro = TM->LoadTexture("assets/button_intro.png");
	button_exit = TM->LoadTexture("assets/button_exit.png");
	button_lastpage = TM->LoadTexture("assets/button_lastpage.png");
	
	effect_select = new Mixer("audio/click.mp3", EFFECT);
	effect_buy = new Mixer("audio/Kaching.mp3", EFFECT);
	effect_fail = new Mixer("audio/fail.mp3", EFFECT);
}
GameMenu::~GameMenu()
{}
void GameMenu::HandleEvent_opening(SDL_Event& e, Game* g)
{
	int x, y;

	switch (e.type)
	{
	case SDL_QUIT:
		g->isRunning = 0;
		break;
	case SDL_MOUSEMOTION:
		x = e.motion.x;
		y = e.motion.y;
		for (int i = 0; i < opening_num; i++)
		{
			if (x >= dRect_opening[i].x && x <= dRect_opening[i].x + dRect_opening[i].w && y >= dRect_opening[i].y && y <= dRect_opening[i].y + dRect_opening[i].h)
			{
				if (!selected_opening[i])
				{
					effect_select->playEffect(ONE, -1);
					selected_opening[i] = 1;
					srcRect_opening[i].x=128;
				}
			}
			else {
				if (selected_opening[i])
				{
					selected_opening[i] = 0;
					srcRect_opening[i].x = 0;
				}
			}
		}
		break;
	case SDL_MOUSEBUTTONDOWN:
		if (e.button.button == SDL_BUTTON_LEFT)
		{
			x = e.motion.x;
			y = e.motion.y;
			for (int i = 0; i < opening_num; i++)
			{
				if (x >= dRect_opening[i].x && x <= dRect_opening[i].x + dRect_opening[i].w && y >= dRect_opening[i].y && y <= dRect_opening[i].y + dRect_opening[i].h)
				{
					g->opening = 0;
					if (i == 3)
						g->isRunning = false;
					else if (i == 2)
					{
						g->opening = 0;
						g->intro = 1;
						intro_page[0] = 1;
						intro_page[1] = 0;
						intro_page[2] = 0;
					}
					else if (i == 1)
					{
						g->opening = 0;
						g->shop = 1;
						shop_page[0] = 1;
					}
					else if (i == 0)
					{
						g->reset();
						g->weapon_select = 1;
						shop_page[0] = 1;
					}
				}
			}
		}
		break;
	}
}
void GameMenu::HandleEvent_weapon_select(SDL_Event& e, Game* g, Weapon* w)
{
	int x, y;

	if (shop_page[0])
	{
		switch (e.type)
		{
		case SDL_QUIT:
			g->isRunning = 0;
			break;
		case SDL_MOUSEMOTION:
			x = e.motion.x;
			y = e.motion.y;
			for (int i = 0; i < 4; i++) //96 + i * 128,150,32 * 3,40 * 3
			{
				if (x >= 80 + i * 128 && x <= 80 + i * 128 + 96 && y >= 320 - 20 && y <= 320 - 20 + 48)
				{
					if (!selected_shop[i])
					{
						selected_shop[i] = 1;
						effect_select->playEffect(ONE, -1);
					}
				}
				else
				{
					selected_shop[i] = 0;
				}

			}
			//256,400,128,44
			if (x >= 256 && x <= 256 + 128 && y >= 400 && y <= 400 + 44 )
				{
					if (!selected_opening[0])
					{
						effect_select->playEffect(ONE, -1);
						selected_opening[0] = 1;
						srcRect_opening[0].x = 128;
					}
				}
			else {
				if (selected_opening[0])
				{
					selected_opening[0] = 0;
					srcRect_opening[0].x = 0;
				}
			}
			
			break;
		case SDL_MOUSEBUTTONDOWN:
			if (e.button.button == SDL_BUTTON_LEFT)
			{
				x = e.motion.x;
				y = e.motion.y;
				if (x >= 256 && x <= 256 + 128 && y >= 400 && y <= 400 + 44)
				{
					if (foolproof())
					{
						g->weapon_select = 0;
						shop_page[0] = shop_page[1] = shop_page[2] = 0;
						g->play = 1;
						music->play(FOREVER);
						break;
					}
					else
					{
						warning_cd = 50;
						effect_fail->playEffect(ONE, -1);
						break;
					}
				}
				if (x >= 640 - 64 && x <= 640 && y >= 480 - 64 && y <= 480)
				{
					g->weapon_select = 0;
					shop_page[0] = shop_page[1] = shop_page[2] = 0;
					g->opening = 1;
					break;
				}
				if (x >= 640 - 70 && x <= 640 - 6 && y >= 240 - 32 && y <= 240 + 32)
				{
					shop_page[0] = 0;
					shop_page[1] = 1;
					break;
				}

				for (int i = 0; i < 4; i++) // 96 + i * 128,150,32 * 3,40 * 3 
				{
					if (x >= 80 + i * 128 && x <= 80 + i * 128 + 96 && y >= 320 - 20 && y <= 320 - 20 + 48)
					{
						if (purchase[i])
						{
							effect_select->playEffect(ONE, -1);
							if (selected_play[i] == 0)
								selected_play[i] = 1;
							else if (selected_play[i] == 1)
								selected_play[i] = 0;
							break;
						}
					}

				}
			}
			break;
		}
	}
	else if (shop_page[1])
	{
		switch (e.type)
		{
		case SDL_QUIT:
			g->isRunning = 0;
			break;
		case SDL_MOUSEMOTION:
			x = e.motion.x;
			y = e.motion.y;
			for (int i = 4; i < 8; i++) //96 + i * 128,150,32 * 3,40 * 3
			{
				if (x >= 80 + (i - 4) * 128 && x <= 80 + (i - 4) * 128 + 96 && y >= 320 - 20 && y <= 320 - 20 + 48)
				{
					if (!selected_shop[i])
					{
						selected_shop[i] = 1;
						effect_select->playEffect(ONE, -1);
					}
				}
				else
				{
					selected_shop[i] = 0;
				}
			}
			if (x >= 256 && x <= 256 + 128 && y >= 400 && y <= 400 + 44)
			{
				if (!selected_opening[0])
				{
					effect_select->playEffect(ONE, -1);
					selected_opening[0] = 1;
					srcRect_opening[0].x = 128;
				}
			}
			else {
				if (selected_opening[0])
				{
					selected_opening[0] = 0;
					srcRect_opening[0].x = 0;
				}
			}
			break;
		case SDL_MOUSEBUTTONDOWN:
			if (e.button.button == SDL_BUTTON_LEFT)
			{
				x = e.motion.x;
				y = e.motion.y;
				if (x >= 256 && x <= 256 + 128 && y >= 400 && y <= 400 + 44)
				{
					if (foolproof())
					{
						g->weapon_select = 0;
						shop_page[0] = shop_page[1] = shop_page[2] = 0;
						g->play = 1;
						music->play(FOREVER);
						break;
					}
					else
					{
						warning_cd = 50;
						effect_fail->playEffect(ONE, -1);
						break;
					}
				}
				if (x >= 640 - 64 && x <= 640 && y >= 480 - 64 && y <= 480)
				{
					g->weapon_select = 0;
					shop_page[0] = shop_page[1] = shop_page[2] = 0;
					g->opening = 1;
					break;
				}
				if (x >= 6 && x <= 70 && y >= 240 - 32 && y <= 240 + 32)
				{
					shop_page[0] = 1;
					shop_page[1] = 0;
					break;
				}
				if (x >= 640 - 70 && x <= 640 - 6 && y >= 240 - 32 && y <= 240 + 32)
				{
					shop_page[2] = 1;
					shop_page[1] = 0;
					break;
				}

				for (int i = 4; i < 8; i++) // 96 + i * 128,150,32 * 3,40 * 3 
				{
					if (x >= 80 + (i - 4) * 128 && x <= 80 + (i - 4) * 128 + 96 && y >= 320 - 20 && y <= 320 - 20 + 48)
					{
						if (purchase[i])
						{
							effect_select->playEffect(ONE, -1);
							if (selected_play[i] == 0)
								selected_play[i] = 1;
							else if (selected_play[i] == 1)
								selected_play[i] = 0;
							break;
						}
					}
				}
			}
			break;
		}
	}
	else if (shop_page[2])
	{
		switch (e.type)
		{
		case SDL_QUIT:
			g->isRunning = 0;
			break;
		case SDL_MOUSEMOTION:
			x = e.motion.x;
			y = e.motion.y;
			for (int i = 8; i < 10; i++) //96 + i * 128,150,32 * 3,40 * 3
			{
				if (x >= 80 + (i - 8) * 128 && x <= 80 + (i - 8) * 128 + 96 && y >= 320 - 20 && y <= 320 - 20 + 48)
				{
					if (!selected_shop[i])
					{
						selected_shop[i] = 1;
						effect_select->playEffect(ONE, -1);
					}
				}
				else
				{
					selected_shop[i] = 0;
				}

			}
			if (x >= 256 && x <= 256 + 128 && y >= 400 && y <= 400 + 44)
			{
				if (!selected_opening[0])
				{
					effect_select->playEffect(ONE, -1);
					selected_opening[0] = 1;
					srcRect_opening[0].x = 128;
				}
			}
			else {
				if (selected_opening[0])
				{
					selected_opening[0] = 0;
					srcRect_opening[0].x = 0;
				}
			}
			break;
		case SDL_MOUSEBUTTONDOWN:
			if (e.button.button == SDL_BUTTON_LEFT)
			{
				x = e.motion.x;
				y = e.motion.y;
				if (x >= 256 && x <= 256 + 128 && y >= 400 && y <= 400 + 44)
				{
					if (foolproof())
					{
						g->weapon_select = 0;
						shop_page[0] = shop_page[1] = shop_page[2] = 0;
						g->play = 1;
						music->play(FOREVER);
						break;
					}
					else
					{
						warning_cd = 50;
						effect_fail->playEffect(ONE, -1);
						break;
					}
				}
				if (x >= 640 - 64 && x <= 640 && y >= 480 - 64 && y <= 480)
				{
					g->weapon_select = 0;
					shop_page[0] = shop_page[1] = shop_page[2] = 0;
					g->opening = 1;
					break;
				}
				if (x >= 6 && x <= 70 && y >= 240 - 32 && y <= 240 + 32)
				{
					shop_page[1] = 1;
					shop_page[2] = 0;
					break;
				}

				for (int i = 8; i < 10; i++) // 96 + i * 128,150,32 * 3,40 * 3 
				{
					if (x >= 80 + (i - 8) * 128 && x <= 80 + (i - 8) * 128 + 96 && y >= 320 - 20 && y <= 320 - 20 + 48)
					{

						if (purchase[i])
						{
							effect_select->playEffect(ONE, -1);
							if (selected_play[i] == 0)
								selected_play[i] = 1;
							else if (selected_play[i] == 1)
								selected_play[i] = 0;
							break;
						}
						if (i == 9)
						{
							if (w->poop->Getpoopnum() > 0)
							{
								if (selected_play[i] == 0)
									selected_play[i] = 1;
								else if (selected_play[i] == 1)
									selected_play[i] = 0;
								break;
							}
						}

					}
				}
			}
			break;
		}
	}
}
void GameMenu::HandleEvent_shop(SDL_Event& e, Game* g, GamePlayer* p, Weapon* w)
{
	int x, y;

	if (shop_page[0])
	{
		switch (e.type)
		{
		case SDL_QUIT:
			g->isRunning = 0;
			break;
		case SDL_MOUSEMOTION:
			x = e.motion.x;
			y = e.motion.y;
			for (int i = 0; i < 4; i++) //96 + i * 128,150,32 * 3,40 * 3
			{
				if (x >= 80 + i * 128 && x <= 80+ i * 128 + 96 && y >= 320 - 20 && y <= 320 - 20 + 48)
				{
					if (!selected_shop[i])
					{
						selected_shop[i] = 1;
						effect_select->playEffect(ONE, -1);
					}
				}
				else
				{
					selected_shop[i] = 0;
				}

			}
			break;
		case SDL_MOUSEBUTTONDOWN:
			if (e.button.button == SDL_BUTTON_LEFT)
			{
				x = e.motion.x;
				y = e.motion.y;
				if (x >= 640 - 64 && x <= 640 && y >= 480 - 64 && y <= 480)
				{
					g->shop = 0;
					shop_page[0] = shop_page[1] = shop_page[2] = 0;
					g->opening = 1;
					break;
				}
				if (x >= 640 - 70 && x <= 640 - 6 && y >= 240 - 32 && y <= 240 + 32)
				{
					shop_page[0] = 0;
					shop_page[1] = 1;
					break;
				}

				for (int i = 0; i < 4; i++) // 96 + i * 128,150,32 * 3,40 * 3 
				{
					if (x >= 80 + i * 128 && x <= 80 + i * 128 + 96 && y >= 320 - 20 && y <= 320 - 20 + 48)
					{
						if (p->GetCoin() >= price[i] && purchase[i] == 0)
						{
							effect_buy->playEffect(ONE, -1);
							purchase[i] = 1;
							p->AddCoin(-price[i]);
							break;
						}
					}
				}
			}
			break;
		}
	}
	else if (shop_page[1])
	{
		switch (e.type)
		{
		case SDL_QUIT:
			g->isRunning = 0;
			break;
		case SDL_MOUSEMOTION:
			x = e.motion.x;
			y = e.motion.y;
			for (int i = 4; i < 8; i++) //96 + i * 128,150,32 * 3,40 * 3
			{
				if (x >= 80 + (i-4) * 128 && x <= 80 + (i-4) * 128 + 96 && y >= 320 - 20 && y <= 320 - 20 + 48)
				{
					if (!selected_shop[i])
					{
						selected_shop[i] = 1;
						effect_select->playEffect(ONE, -1);
					}
				}
				else
				{
					selected_shop[i] = 0;
				}

			}
			break;
		case SDL_MOUSEBUTTONDOWN:
			if (e.button.button == SDL_BUTTON_LEFT)
			{
				x = e.motion.x;
				y = e.motion.y;
				if (x >= 640 - 64 && x <= 640 && y >= 480 - 64 && y <= 480)
				{
					g->shop = 0;
					shop_page[0] = shop_page[1] = shop_page[2] = 0;
					g->opening = 1;
					break;
				}
				if (x >= 6 && x <= 70 && y >= 240 - 32 && y <= 240 + 32)
				{
					shop_page[0] = 1;
					shop_page[1] = 0;
					break;
				}
				if (x >= 640 - 70 && x <= 640 - 6 && y >= 240 - 32 && y <= 240 + 32)
				{
					shop_page[2] = 1;
					shop_page[1] = 0;
					break;
				}

				for (int i = 4; i < 8; i++) // 96 + i * 128,150,32 * 3,40 * 3 
				{
					if (x >= 80 + (i-4) * 128 && x <= 80 + (i-4) * 128 + 96 && y >= 320 - 20 && y <= 320 - 20 + 48)
					{
						if (p->GetCoin() >= price[i] && purchase[i] == 0)
						{
							effect_buy->playEffect(ONE, -1);
							purchase[i] = 1;
							p->AddCoin(-price[i]);
							break;
						}
					}
				}
			}
			break;
		}
	}
	else if (shop_page[2])
	{
		switch (e.type)
		{
		case SDL_QUIT:
			g->isRunning = 0;
			break;
		case SDL_MOUSEMOTION:
			x = e.motion.x;
			y = e.motion.y;
			for (int i = 8; i < 10; i++) //96 + i * 128,150,32 * 3,40 * 3
			{
				if (x >= 80 + (i - 8) * 128 && x <= 80 + (i - 8) * 128 + 96 && y >= 320 - 20 && y <= 320 - 20 + 48)
				{
					if (!selected_shop[i])
					{
						selected_shop[i] = 1;
						effect_select->playEffect(ONE, -1);
					}
				}
				else
				{
					selected_shop[i] = 0;
				}

			}
			break;
		case SDL_MOUSEBUTTONDOWN:
			if (e.button.button == SDL_BUTTON_LEFT)
			{
				x = e.motion.x;
				y = e.motion.y;
				if (x >= 640 - 64 && x <= 640 && y >= 480 - 64 && y <= 480)
				{
					g->shop = 0;
					shop_page[0] = shop_page[1] = shop_page[2] = 0;
					g->opening = 1;
					break;
				}
				if (x >= 6 && x <= 70 && y >= 240 - 32 && y <= 240 + 32)
				{
					shop_page[1] = 1;
					shop_page[2] = 0;
					break;
				}

				for (int i = 8; i < 10; i++) // 96 + i * 128,150,32 * 3,40 * 3 
				{
					if (x >= 80 + (i - 8) * 128 && x <= 80 + (i - 8) * 128 + 96 && y >= 320 - 20 && y <= 320 - 20 + 48)
					{
						if (p->GetCoin() >= price[i] && purchase[i] == 0)
						{
							effect_buy->playEffect(ONE, -1);
							if (i == 9)
							{
								if (w->poop->Getpoopnum() < 99999)
								{
									purchase[i] = 0;
									w->poop->increase();
								}
							}
							else
								purchase[i] = 1;

							p->AddCoin(-price[i]);
							break;
						}
					}
				}
			}
			break;
		}
	}
}

void GameMenu::HandleEvent_intro(SDL_Event& e, Game* g)
{
	int x, y;

	if (intro_page[0])
	{
		switch (e.type)
		{
		case SDL_QUIT:
			g->isRunning = 0;
			break;
		case SDL_MOUSEBUTTONDOWN:
			if (e.button.button == SDL_BUTTON_LEFT)
			{
				x = e.motion.x;
				y = e.motion.y;
				if (x >= 640 - 64 && x <= 640 && y >= 0 && y <= 64)
				{
					g->intro = 0;
					g->opening = 1;
				}
				if (x >= 0 && x <= 64 && y >= 480 - 64 && y <= 480)
				{
					/*intro_page[0] = 0;
					intro_page[1] = 1;*/
					;
				}
				if (x >= 640 - 64 && x <= 640 && y >= 480 - 64 && y <= 480)
				{
					intro_page[0] = 0;
					intro_page[1] = 1;
					intro_page[2] = 0;
				}
			}
			break;
		}
	}
	else if (intro_page[1])
	{
		switch (e.type)
		{
		case SDL_QUIT:
			g->isRunning = 0;
			break;
		case SDL_MOUSEBUTTONDOWN:
			if (e.button.button == SDL_BUTTON_LEFT)
			{
				x = e.motion.x;
				y = e.motion.y;
				if (x >= 640 - 64 && x <= 640 && y >= 0 && y <= 64)
				{
					g->intro = 0;
					g->opening = 1;
				}
				if (x >= 0 && x <= 64 && y >= 480 - 64 && y <= 480)
				{
					intro_page[0] = 1;
					intro_page[1] = 0;
					intro_page[2] = 0;
				}
				if (x >= 640 - 64 && x <= 640 && y >= 480 - 64 && y <= 480)
				{
					intro_page[0] = 0;
					intro_page[1] = 0;
					intro_page[2] = 1;
				}
			}
			break;
		}
	}
	else if (intro_page[2])
	{
		switch (e.type)
		{
		case SDL_QUIT:
			g->isRunning = 0;
			break;
		case SDL_MOUSEBUTTONDOWN:
			if (e.button.button == SDL_BUTTON_LEFT)
			{
				x = e.motion.x;
				y = e.motion.y;
				if (x >= 640 - 64 && x <= 640 && y >= 0 && y <= 64)
				{
					g->intro = 0;
					g->opening = 1;
				}
				if (x >= 0 && x <= 64 && y >= 480 - 64 && y <= 480)
				{
					intro_page[0] = 0;
					intro_page[1] = 1;
					intro_page[2] = 0;
				}
				if (x >= 640 - 64 && x <= 640 && y >= 480 - 64 && y <= 480)
				{
					/*intro_page[0] = 0;
					intro_page[1] = 0;
					intro_page[2] = 1;*/
					;
				}
			}
			break;
		}
	}
}
void GameMenu::HandleEvent_pause(SDL_Event& e,Game* g)
{
	int x, y;

	music->pause();
	switch (e.type)
	{
	case SDL_QUIT:
		g->isRunning = 0;
		break;
	case SDL_KEYDOWN:
		switch (e.key.keysym.sym)
		{
		case SDLK_ESCAPE:
			music->resume();
			g->pause = 0;
			break;
		}
		break;
	case SDL_MOUSEMOTION:
		x = e.motion.x;
		y = e.motion.y;
		for (int i = 0; i < pause_num; i++)
		{
			if (x >= pause[i].getxpos() && x <= pause[i].getxpos() + pause[i].getwidth() && y >= pause[i].getypos() && y <= pause[i].getypos() + pause[i].getheight())
			{
				if (!selected_pause[i])
				{
					effect_select->playEffect(ONE, -1);
					selected_pause[i] = 1;
					pause[i].setColor(color[1]);
					pause[i].generateTex();
				}
			}
			else {
				if (selected_pause[i])
				{
					selected_pause[i] = 0;
					pause[i].setColor(color[0]);
					pause[i].generateTex();
				}
			}
		}
		break;
	case SDL_MOUSEBUTTONDOWN:
		if (e.button.button == SDL_BUTTON_LEFT)
		{
			x = e.motion.x;
			y = e.motion.y;
			for (int i = 0; i < pause_num; i++)
			{
				if (x >= pause[i].getxpos() && x <= pause[i].getxpos() + pause[i].getwidth() && y >= pause[i].getypos() && y <= pause[i].getypos() + pause[i].getheight())
				{
					if (i == 2)
						g->isRunning = false;
					else if (i == 1)
					{
						g->reset();
						g->pause = 0;
						g->opening = 1;
					}
					else if (i == 0)
					{
						music->resume();
						g->pause = 0;
					}
				}
			}
		}
		break;
	}
}
void GameMenu::HandleEvent_die(SDL_Event& e, Game* g)
{
	int x, y;

	music->pause();
	switch (e.type)
	{
	case SDL_QUIT:
		g->isRunning = 0;
		break;
	case SDL_MOUSEMOTION:
		x = e.motion.x;
		y = e.motion.y;
		for (int i = 1; i < pause_num; i++)
		{
			if (x >= pause[i].getxpos() && x <= pause[i].getxpos() + pause[i].getwidth() && y >= pause[i].getypos() && y <= pause[i].getypos() + pause[i].getheight())
			{
				if (!selected_pause[i])
				{
					effect_select->playEffect(ONE, -1);
					selected_pause[i] = 1;
					pause[i].setColor(color[1]);
					pause[i].generateTex();
				}
			}
			else {
				if (selected_pause[i])
				{
					selected_pause[i] = 0;
					pause[i].setColor(color[0]);
					pause[i].generateTex();
				}
			}
		}
		break;
	case SDL_MOUSEBUTTONDOWN:
		if (e.button.button == SDL_BUTTON_LEFT)
		{
			x = e.motion.x;
			y = e.motion.y;
			for (int i = 1; i < pause_num; i++)
			{
				if (x >= pause[i].getxpos() && x <= pause[i].getxpos() + pause[i].getwidth() && y >= pause[i].getypos() && y <= pause[i].getypos() + pause[i].getheight())
				{
					if (i == 2)
						g->isRunning = false;
					else if (i == 1)
					{
						g->reset();
						g->die = 0;
						g->opening = 1;
					}
				}
			}
		}
		break;
	}
}
void GameMenu::HandleEvent_win(SDL_Event& e, Game* g)
{
	int x, y;

	music->pause();
	switch (e.type)
	{
	case SDL_QUIT:
		g->isRunning = 0;
		break;
	case SDL_MOUSEMOTION:
		x = e.motion.x;
		y = e.motion.y;
		for (int i = 1; i < pause_num; i++)
		{
			if (x >= pause[i].getxpos() && x <= pause[i].getxpos() + pause[i].getwidth() && y >= pause[i].getypos() && y <= pause[i].getypos() + pause[i].getheight())
			{
				if (!selected_pause[i])
				{
					effect_select->playEffect(ONE, -1);
					selected_pause[i] = 1;
					pause[i].setColor(color[1]);
					pause[i].generateTex();
				}
			}
			else {
				if (selected_pause[i])
				{
					selected_pause[i] = 0;
					pause[i].setColor(color[0]);
					pause[i].generateTex();
				}
			}
		}
		break;
	case SDL_MOUSEBUTTONDOWN:
		if (e.button.button == SDL_BUTTON_LEFT)
		{
			x = e.motion.x;
			y = e.motion.y;
			for (int i = 1; i < pause_num; i++)
			{
				if (x >= pause[i].getxpos() && x <= pause[i].getxpos() + pause[i].getwidth() && y >= pause[i].getypos() && y <= pause[i].getypos() + pause[i].getheight())
				{
					if (i == 2)
						g->isRunning = false;
					else if (i == 1)
					{
						g->win = 0;
						g->opening = 1;
					}
				}
			}
		}
		break;
	}
}

void GameMenu::render_opening()
{
	penis->setxpos(penis->getxpos() + 1);
	if (penis->getxpos()+18 < 256 && penis->getxpos()+18 >= 256-4)
		penis->setypos(penis->getypos() - 14);
	else if (penis->getxpos() < 256 + 128 + 4 && penis->getxpos() >= 256 + 128)
		penis->setypos(penis->getypos() + 14);
	
	if (penis->getxpos() > 640 + 20)
		penis->setxpos(-64);

	TM->Draw(background, { 0,0,WIDTH,HEIGHT }, { 0,0,WIDTH,HEIGHT });
	penis->render();
	TM->Draw(Title, {0,0,480,44}, {80,44,480,44});
	TM->Draw(button_play, srcRect_opening[0], dRect_opening[0]);
	TM->Draw(button_shop, srcRect_opening[1], dRect_opening[1]);
	TM->Draw(button_intro, srcRect_opening[2], dRect_opening[2]);
	TM->Draw(button_exit, srcRect_opening[3], dRect_opening[3]);
}
void GameMenu::render_shop()
{
	TM->Draw(background, { 0,0,WIDTH,HEIGHT }, { 0,0,WIDTH,HEIGHT });

	if (shop_page[0])
	{
		for (int i = 0; i < 4; i++)
		{
			TM->Draw(Shop, { 32 * i,0,32,40 }, { 80 + i * 128,150,32 * 3,40 * 3 });
			TM->Draw(button_buy, { 32 * purchase[i],0,32,16 }, { 80 + i * 128,320 - 20,32 * 3,16 * 3 });
		}
		TM->Draw(button_next, { 0,0,64,64 }, { 640 - 70,240 - 32,64,64 });
	}
	if (shop_page[1])
	{
		for (int i = 4; i < 8; i++)
		{
			TM->Draw(Shop, { 32 * i,0,32,40 }, { 80 + (i-4) * 128,150,32 * 3,40 * 3 });
			TM->Draw(button_buy, { 32 * purchase[i],0,32,16 }, { 80 + (i-4) * 128,320 - 20,32 * 3,16 * 3 });
		}
		TM->Draw(button_last, { 0,0,64,64 }, { 6,240 - 32,64,64 });
		TM->Draw(button_next, { 0,0,64,64 }, { 640 - 70,240 - 32,64,64 });
	}
	if (shop_page[2])
	{
		for (int i = 8; i < 10; i++)
		{
			TM->Draw(Shop, { 32 * i,0,32,40 }, { 80 + (i - 8) * 128,150,32 * 3,40 * 3 });
			TM->Draw(button_buy, { 32 * purchase[i],0,32,16 }, { 80 + (i - 8) * 128,320 - 20,32 * 3,16 * 3 });
		}
		TM->Draw(button_last, { 0,0,64,64 }, { 6,240 - 32,64,64 });
	}
	TM->Draw(button_lastpage, { 0,0,64,64 }, { 640 - 64,480 - 64,64,64 });
	TM->Draw(poopnum, {0,0,32,32}, {0,0,32,32});
}
void GameMenu::render_weapon_select()
{
	TM->Draw(background, { 0,0,WIDTH,HEIGHT }, { 0,0,WIDTH,HEIGHT });

	if (shop_page[0])
	{
		for (int i = 0; i < 4; i++)
		{
			TM->Draw(Shop, { 32 * i,0,32,40 }, { 80 + i * 128,150,32 * 3,40 * 3 });
			if (purchase[i])
				TM->Draw(button_pick, { 32 * selected_play[i],0,32,16 }, { 80 + i * 128,320 - 20,32 * 3,16 * 3 });
			else
				TM->Draw(button_null, { 32 * selected_play[i],0,32,16 }, { 80 + i * 128,320 - 20,32 * 3,16 * 3 });
		}
		TM->Draw(button_next, { 0,0,64,64 }, { 640 - 70,240 - 32,64,64 });
	}
	if (shop_page[1])
	{
		for (int i = 4; i < 8; i++)
		{
			TM->Draw(Shop, { 32 * i,0,32,40 }, { 80 + (i - 4) * 128,150,32 * 3,40 * 3 });
			if (purchase[i])
				TM->Draw(button_pick, { 32 * selected_play[i],0,32,16 }, { 80 + (i - 4) * 128,320 - 20,32 * 3,16 * 3 });
			else
				TM->Draw(button_null, { 32 * selected_play[i],0,32,16 }, { 80 + (i - 4) * 128,320 - 20,32 * 3,16 * 3 });
		}
		TM->Draw(button_last, { 0,0,64,64 }, { 6,240 - 32,64,64 });
		TM->Draw(button_next, { 0,0,64,64 }, { 640 - 70,240 - 32,64,64 });
	}
	if (shop_page[2])
	{
		for (int i = 8; i < 10; i++)
		{
			TM->Draw(Shop, { 32 * i,0,32,40 }, { 80 + (i - 8) * 128,150,32 * 3,40 * 3 });
			if (purchase[i] || i==9)
				TM->Draw(button_pick, { 32 * selected_play[i],0,32,16 }, { 80 + (i - 8) * 128,320 - 20,32 * 3,16 * 3 });
			else
				TM->Draw(button_null, { 32 * selected_play[i],0,32,16 }, { 80 + (i - 8) * 128,320 - 20,32 * 3,16 * 3 });
		}
		TM->Draw(button_last, { 0,0,64,64 }, { 6,240 - 32,64,64 });
	}
	if (warning_cd)
	{
		warning_cd--;
		warning.render();
	}
	TM->Draw(button_lastpage, { 0,0,64,64 }, { 640 - 64,480 - 64,64,64 });
	TM->Draw(poopnum, { 0,0,32,32 }, { 0,0,32,32 });
	TM->Draw(button_play, srcRect_opening[0], { 256,400,128,44 });
}
void GameMenu::render_intro()
{
	if (intro_page[0])
	{
		TM->Draw(Intro[0], {0,0,640,480}, {0, 0, 640, 480});
		TM->Draw(button_next, { 0,0,64,64 }, {640-64,480 - 64,64,64 });
	}
	if (intro_page[1])
	{
		TM->Draw(Intro[1], { 0,0,640,480 }, { 0, 0, 640, 480 });
		TM->Draw(button_last, { 0,0,64,64 }, { 0,480 - 64,64,64 });
		TM->Draw(button_next, { 0,0,64,64 }, { 640 - 64,480 - 64,64,64 });
	}
	if (intro_page[2])
	{
		TM->Draw(Intro[2], { 0,0,640,480 }, { 0, 0, 640, 480 });
		TM->Draw(button_last, { 0,0,64,64 }, { 0,480 - 64,64,64 });
	}
	TM->Draw(button_lastpage, { 0,0,64,64 }, { 640 - 64,0,64,64 });
}
void GameMenu::render_pause()
{
	for (int i = 0; i < pause_num; i++)
		pause[i].render();
}
void GameMenu::render_die()
{
	wasted.render();
	for (int i = 1; i < pause_num; i++)
		pause[i].render();
}
void GameMenu::render_win()
{
	winner.render();
	for (int i = 1; i < pause_num; i++)
		pause[i].render();
}
bool GameMenu::foolproof()
{
	for (int i = 0; i < 10; i++)
		if (selected_play[i] == true)
			return true;
	return false;
}