#include "GamePlayer.h"
#include "GameMonster.h"
#include "HealthPoint.h"
#include "Map.h"

GamePlayer::GamePlayer(const char* filename, float x, float y) : GameObject(filename,x,y)
{
	playerTex = TM->LoadTexture(filename);
	hpbar = new HealthPoint("assets/hpbar.png", pos.x - 9, pos.y + 32);
	mpbar = new HealthPoint("assets/mpbar.png", pos.x - 9, pos.y + 32 + 8);
	effect_hurt = new Mixer("audio/hurt.mp3", EFFECT);

	HP = 500;
	HP_MAX = HP;
	MP = 300;
	MP_MAX = MP;

	ATK = 1;
	speed = 2;
	bonus = 0;
	getin = false;
}
//initialize the player and load .png

GamePlayer::GamePlayer(const char* filename, float x, float y, int n, int wwn, int hhn): GameObject(filename,x,y,n,wwn,hhn)
{
	playerTex = TM->LoadTexture(filename);
	hpbar = new HealthPoint("assets/hpbar.png", pos.x - 9, pos.y + 32);
	mpbar = new HealthPoint("assets/mpbar.png", pos.x - 9, pos.y + 32 + 8);
	effect_hurt = new Mixer("audio/hurt.mp3", EFFECT);

	HP = 200;
	HP_MAX = HP;
	MP = 100;
	MP_MAX = MP;
	ATK = 1;
	speed = 2;
	getin = false;
}

GamePlayer::~GamePlayer() {
	close();
}

void GamePlayer::update() 
{
	if (alive)
	{
		//printf("%d\n", coin);
		recover();
		if (!checkCollision())
		{
			bool pre = getroomornot();
			realpos+= move;
			/*printf("%d %d\n", (int)realpos.x, (int)realpos.y);*/
			checkroomornot();

			bool now = getroomornot();
			if (pre == false && now == true)
			{
				int indexX = (int)realpos.x / 640, indexY = (int)realpos.y / 480;
				vector2 tmp;
				tmp.setXY(move.x,move.y);
				if (tmp.x > 0)
					tmp.x = 32;
				else if (tmp.x < 0)
					tmp.x = -32;
				else
					tmp.x = 0;

				if (tmp.y > 0)
					tmp.y = 32;
				else if (tmp.y < 0)
					tmp.y = -32;
				else
					tmp.y = 0;

				pos.x = (int)realpos.x % 640;
				pos.y = (int)realpos.y % 480;
				realpos += tmp;
				pos += tmp;
				//printf("%lf %lf\n", pos.x, pos.y);
				map->locktheroom(indexX, indexY);

			}
			if (getroomornot())
			{
				checkEffect();
				pos += move;
			}
			else
			{
				pos.x = 640 / 2;
				pos.y = 480 / 2 - 16;
				//ypos += ymove ;
			}
		}
		if (!isAlive())
			alive = false;
	}
	hpbar->update(this);
	mpbar->update_mp(this);
}
//update the Rect

void GamePlayer::render()
{
	wPic = frame % wn;
	hPic = frame / wn;

	srcRect.x = 32 * wPic;
	srcRect.y = 32 * hPic;
	srcRect.w = 32;
	srcRect.h = 32;
	dRect.x = (int)pos.x;
	dRect.y = (int)pos.y;
	dRect.w = srcRect.w ;
	dRect.h = srcRect.h ;
	//dRect.w = srcRect.w*3;
	//dRect.h = srcRect.h*3;

	TM->Draw(playerTex, srcRect, dRect);
	hpbar->render();
	mpbar->render();
}
//render
void GamePlayer::reset()
{
	alive = true;
	HP = HP_MAX;
	MP = MP_MAX;
	pos.x = realpos.x = 320;
	pos.y = realpos.y = 240;
	getin = false;
	
}

void GamePlayer::close()
{
	delete hpbar;
	hpbar = nullptr;
	delete mpbar;
	mpbar = nullptr;
	effect_hurt->close();
	delete effect_hurt;
	effect_hurt = nullptr;
	SDL_DestroyTexture(playerTex);
	playerTex = nullptr;
	SDL_RemoveTimer(timerID);
}

void GamePlayer::Move(float xx, float yy)
{
	if (alive)
	{
		int x, y;

		x = (int)xx, y = (int)yy;
		SDL_RemoveTimer(timerID);

		double bonusEx = 0;
		bool sliding = false;
		if (bonus == 0 && sliding == false)
			;
		else {
			if (friction == false) {
				waterFriction = -0.1;
			}
			if (bonus >= -3 * waterFriction-2)
			{
				if (bonus != 0) {
					bonusEx = bonus;
					if (bonus <= -1.5)
						bonusEx = bonus / 2;
				}
				bonus += bonusEx;
				//printf("Speed: %lf\n", speed);
				sliding = true;
				if (bonus >= 2 || bonus <= -1.5)
					sliding = false;
			}
			else
				waterFriction /= 2;
		}


		move.x = xx * (speed+bonus);
		move.y = yy * (speed+bonus);

		startTimer(20);

		if (x == 0 && y == 0)
			SDL_RemoveTimer(timerID);
		else if (x > 0 && y == 0)
			frametime = 0;
		else if (x < 0 && y == 0)
			frametime = 4;
		else if (x == 0 && y < 0)
			frametime = 8;
		else if (x == 0 && y > 0)
			frametime = 12;
		else
			;

	}
}
void GamePlayer::setFriction(bool a)
{
	friction = a;
}

Uint32 GamePlayer::changeData(Uint32 interval, void* param)
{
	GamePlayer* p = (GamePlayer*)param;

	if (p->t != 0)
	{
		p->frame = (p->frame + 1) % p->wn + p->frametime;  // image frame	
		return interval;
	}
	else
	{
		return 0;
	}
}


bool GamePlayer::isAlive()
{
	if (HP <= 0)
	{
		alive = false;
		SDL_RemoveTimer(timerID);
		move.reset();
		frame = 0;

		//playerTex = TM->LoadTexture("assets/player_died.png");
		return false;
	}

	return true;
}

void GamePlayer::recover()
{
	recoverCoolDown = recoverCoolDown % 100;
	
	if (recoverCoolDown == 0)
	{
		HP++;
		MP+=3;
	}
	if (HP > HP_MAX)
		HP = HP_MAX;
	if (MP > MP_MAX)
		MP = MP_MAX;
	recoverCoolDown++;
}
//automatically recover HP
void GamePlayer::bleeding(int a)
{
	effect_hurt->playEffect(ONE, -1);
	if (HP > 0)
		HP -= a;
}
void GamePlayer::lossMP(int e)
{
	MP -= e;
	if (MP < 0)
		MP = 0;
}
