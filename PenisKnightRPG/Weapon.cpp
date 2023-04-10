#include "Weapon.h"
#include <math.h>

Weapon::Weapon()
{
	dir.setXY(1, 1);
	
	frame = 0;
	num = 4;
	hn = 1;
	wn = 4;

	mode = 0;
	atk = 99;
	range = 32;

	bullet_icon = TM->LoadTexture("assets/bullet_icon.png");
	Sword = TM->LoadTexture("assets/goldensword.png");
	Gun = TM->LoadTexture("assets/gun.png");
	Magic = TM->LoadTexture("assets/magic.png");
	Lazer = TM->LoadTexture("assets/lazer.png");
	Portalgun = TM->LoadTexture("assets/portalgun.png");
	Sniper = TM->LoadTexture("assets/dickrifle.png");
	BananaBoomerang = TM->LoadTexture("assets/banana.png");
	Sharkgun = TM->LoadTexture("assets/sharkgun.png");
	CDplayer = TM->LoadTexture("assets/cdplayer.png");
	Poop_food = TM->LoadTexture("assets/poop.png");

	effect_Sword = new Mixer("audio/sword.mp3", EFFECT);
	effect_Gun = new Mixer("audio/gun.mp3", EFFECT);
	effect_Magic = new Mixer("audio/magic.mp3", EFFECT);
	effect_Lazer = new Mixer("audio/lazer.mp3", EFFECT);
	effect_Portalgun = new Mixer("audio/portalgun.mp3", EFFECT);
	effect_reset = new Mixer("audio/button.mp3", EFFECT);
	effect_Sniper = new Mixer("audio/sniper.mp3", EFFECT);
	effect_reload = new Mixer("audio/reload.mp3", EFFECT);
	effect_Banana = new Mixer("audio/banana.mp3", EFFECT);
	effect_shark = new Mixer("audio/water.mp3", EFFECT);
	effect_rickroll = new Mixer("audio/rickroll.mp3", EFFECT);
	effect_poop = new Mixer("audio/fart.mp3", EFFECT);

	bullet_num = new Text("fonts/FFFFORWA.TTF", "INF", 32, 2, 15, { 255,255,255 });

	for (int i = 0; i < MAX_BULLET; i++)
		bullet[i] = new Bullet("assets/bullet.png",50);
	for (int i = 0; i < MAX_HURRICANE; i++)
		hurricane[i] = new Hurricane();
	for (int i = 0; i < MAX_BANANA; i++)
		banana[i] = new Banana();
	for (int i = 0; i < MAX_MUSICRING; i++)
		musicring[i] = new Musicring();
	lazerbeam = new Lazerbeam();
	portalring = new Portalring();
	snipershot = new Snipershot();
	sharkbite = new SharkBite();
	poop = new Poop();
}
Weapon::~Weapon()
{
}

void Weapon::render()
{
	wPic = frame % wn;
	hPic = frame / wn;

	srcRect.x = 32 * wPic;
	srcRect.y = 32 * hPic;
	srcRect.w = 32;
	srcRect.h = 32;
	dRect.x = (int)pos.x;
	dRect.y = (int)pos.y;
	dRect.w = srcRect.w;
	dRect.h = srcRect.h;

	SDL_Texture* tmp;
	SDL_Rect bRect;
	bRect.x = bRect.y = 0;
	bRect.w = bRect.h = 32;

	switch (mode)
	{
	case 0:
		tmp = NULL;
		TM->DrawEx(tmp, srcRect, dRect, { 15,15 }, angle, SDL_FLIP_NONE);
		break;
	case 1:
		tmp = Sword;
		TM->DrawEx(tmp, srcRect, dRect, { 15,15 }, angle, SDL_FLIP_NONE);
		break;
	case 2:
		tmp = Gun;
		TM->Draw(bullet_icon, bRect, bRect);
		bullet_num->render();
		TM->DrawEx(tmp, srcRect, dRect, { 15,15 }, angle, SDL_FLIP_NONE);
		break;
	case 3:
		tmp = Magic;
		TM->DrawEx(tmp, srcRect, dRect, { 15,15 }, angle, SDL_FLIP_NONE);
		break;
	case 4:
		tmp = Lazer;
		TM->Draw(bullet_icon, bRect, bRect);
		bullet_num->render();
		TM->DrawEx(tmp, srcRect, dRect, { 15,15 }, angle, SDL_FLIP_NONE);
		break;
	case 5:
		tmp = Portalgun;
		TM->DrawEx(tmp, srcRect, dRect, { 15,15 }, angle, SDL_FLIP_NONE);
		break;
	case 6:
		tmp = Sniper;
		TM->Draw(bullet_icon, bRect, bRect);
		TM->DrawEx(tmp, srcRect, dRect, { 15,15 }, angle, SDL_FLIP_NONE);
		break;
	case 7:
		tmp = BananaBoomerang;
		TM->DrawEx(tmp, srcRect, dRect, { 15,15 }, angle, SDL_FLIP_NONE);
		break;
	case 8:
		tmp = Sharkgun;
		TM->DrawEx(tmp, srcRect, dRect, { 15,15 }, angle, SDL_FLIP_NONE);
		break;
	case 9:
		tmp = CDplayer;
		TM->DrawEx(tmp, srcRect, dRect, { 15,15 }, angle, SDL_FLIP_NONE);
		break;
	case 10:
		tmp = Poop_food;
		TM->Draw(tmp, bRect, bRect);
		TM->DrawEx(tmp, srcRect, dRect, { 15,15 }, angle, SDL_FLIP_NONE);
		break;
	}

	for (int i = 0; i < MAX_BULLET; i++)
		bullet[i]->render();
	for (int i = 0; i < MAX_HURRICANE; i++)
		hurricane[i]->render();
	
	if(mode==4)
		lazerbeam->render();
	if(mode==6)
		snipershot->render();
	if (mode == 7)
	{
		for (int i = 0; i < MAX_BANANA; i++)
			banana[i]->render();
	}
	if (mode == 8)
		sharkbite->render();
	if (mode == 9)
	{
		for (int i = 0; i < MAX_MUSICRING; i++)
			musicring[i]->render();
	}
	portalring->render();
	if (mode == 10)
		poop->render();
}
void Weapon::update(vector<GameMonster*> mst,GamePlayer* p,float msx,float msy)
{
	realpos.x = p->getrealxpos();
	realpos.y = p->getrealypos();
	pos.x = p->getxpos();
	pos.y = p->getypos();

	angle = dir.getAngle();
	rad = dir.getRad();

	for (int i = 0; i < MAX_BULLET; i++)
		bullet[i]->update(mst);
	for (int i = 0; i < MAX_HURRICANE; i++)
		hurricane[i]->update(mst);
	for (int i = 0; i < MAX_BANANA; i++)
		banana[i]->update(mst,p);
	for (int i = 0; i < MAX_MUSICRING; i++)
		musicring[i]->update(pos.x + 15, pos.y + 15);
	lazerbeam->update(realpos.x, realpos.y, rad, mst);
	snipershot->update(realpos.x, realpos.y, rad, mst);
	portalring->update(p);
	sharkbite->update(mst, p, msx, msy, width, height);
	poop->update();
}
void Weapon::clear()
{
	stopTimer();
	for (int i = 0; i < MAX_BULLET; i++)
		bullet[i]->reload();
	for (int i = 0; i < MAX_HURRICANE; i++)
		hurricane[i]->reload();
	for (int i = 0; i < MAX_BANANA; i++)
		banana[i]->reload();
	for (int i = 0; i < MAX_MUSICRING; i++)
		musicring[i]->reset();
	lazerbeam->turnoff();
	snipershot->turnoff();
	portalring->reset();
	sharkbite->reload();
}
void Weapon::attack(vector<GameMonster*> mst) //lasting
{	
	if (mode == 1)
	{
		effect_Sword->playEffect(ONE, -1);
		sword_cooldown %= 10;
		if (sword_cooldown == 0)
			slash(mst);
		sword_cooldown++;
	}
	if (mode == 2)
	{
		effect_Gun->playEffect(ONE, -1);
		bullet_cooldown %= 4;
		if (bullet_cooldown == 0)
			fire();
		bullet_cooldown++;
	}

	if (mode == 4)
	{
		effect_Lazer->playEffect(ONE, -1);
		lazerbeam->turnon();
	}

	if (mode == 6)
		snipershot->aim(realpos.x + 15, realpos.y + 15, rad, mst);
	if (mode == 7)
	{
		effect_Banana->playEffect(ONE, -1);
		banana_cooldown %= 7+7;
		if (banana_cooldown == 0)
			throw_Banana();
		banana_cooldown++;
	}
	if (mode == 9)
	{
		if (!music_on)
		{
			effect_rickroll->playEffect(FOREVER, 1);
			music_on = true;
		}
		musicring_cooldown %= 30;
		if (musicring_cooldown == 0)
			musicring_play();
		musicring_cooldown++;
	}
}

void Weapon::slash(vector<GameMonster*> mst)
{	
	if (mode == 1)
	{
		for (int i = 0; i < mst.size(); i++)
		{
			int x = mst[i]->getxpos(), y = mst[i]->getypos();
			if (angle >= -90 && angle <= 90)
			{
				if (x <= pos.x + 31 + range && x >= pos.x + 15 && y <= pos.y + 31 + range && y >= pos.y - range)
				{
					mst[i]->bleeding(atk);
					break;
				}
				else if (x <= pos.x + 31 + range && x >= pos.x + 15 && y + 31 <= pos.y + 31 + range && y + 31 >= pos.y - range)
				{
					mst[i]->bleeding(atk);
					break;
				}
				else if (x + 31 <= pos.x + 31 + range && x + 31 >= pos.x + 15 && y <= pos.y + 31 + range && y >= pos.y - range)
				{
					mst[i]->bleeding(atk);
					break;
				}
				else if (x + 31 <= pos.x + 31 + range && x + 31 >= pos.x + 15 && y + 31 <= pos.y + 31 + range && y + 31 >= pos.y - range)
				{
					mst[i]->bleeding(atk);
					break;
				}
			}
			else if (angle >= 0 && angle <= 180)
			{
				if (x <= pos.x + 31 + range && x >= pos.x - range && y <= pos.y + 31 + range && y >= pos.y + 15)
				{
					mst[i]->bleeding(atk);
					break;
				}
				else if (x <= pos.x + 31 + range && x >= pos.x - range && y+31 <= pos.y + 31 + range && y+31 >= pos.y + 15)
				{
					mst[i]->bleeding(atk);
					break;
				}
				else if (x+31 <= pos.x + 31 + range && x+31 >= pos.x - range && y <= pos.y + 31 + range && y >= pos.y + 15)
				{
					mst[i]->bleeding(atk);
					break;
				}
				else if (x+31 <= pos.x + 31 + range && x+31 >= pos.x - range && y+31 <= pos.y + 31 + range && y+31 >= pos.y + 15)
				{
					mst[i]->bleeding(atk);
					break;
				}
			}

			else if (angle >= 90 || angle <= -90)
			{
				if (x >= pos.x - range && x <= pos.x + 15 && y <= pos.y + 31 + range && y >= pos.y - range)
				{
					mst[i]->bleeding(atk);
					break;
				}
				else if (x >= pos.x - range && x <= pos.x + 15 && y+31 <= pos.y + 31 + range && y+31 >= pos.y - range)
				{
					mst[i]->bleeding(atk);
					break;
				}
				else if (x+31 >= pos.x - range && x+31 <= pos.x + 15 && y <= pos.y + 31 + range && y >= pos.y - range)
				{
					mst[i]->bleeding(atk);
					break;
				}
				else if (x+31 >= pos.x - range && x+31 <= pos.x + 15 && y+31 <= pos.y + 31 + range && y+31 >= pos.y - range)
				{
					mst[i]->bleeding(atk);
					break;
				}
			}
			else if (angle >= -180 && angle <= 0)
			{
				if (x <= pos.x + 31 + range && x >= pos.x - range && y <= pos.y + 15 && y >= pos.y - range)
				{
					mst[i]->bleeding(atk);
					break;
				}
				else if (x <= pos.x + 31 + range && x >= pos.x - range && y+31 <= pos.y + 15 && y+31 >= pos.y - range)
				{
					mst[i]->bleeding(atk);
					break;
				}
				else if (x+31 <= pos.x + 31 + range && x+31 >= pos.x - range && y <= pos.y + 15 && y >= pos.y - range)
				{
					mst[i]->bleeding(atk);
					break;
				}
				else if (x+31 <= pos.x + 31 + range && x+31 >= pos.x - range && y+31 <= pos.y + 15 && y+31 >= pos.y - range)
				{
					mst[i]->bleeding(atk);
					break;
				}
			}
		}
	}
}

void Weapon::fire()
{
	for (int i = 0; i < MAX_BULLET; i++)
	{
		if (!bullet[i]->Active())
		{
			bullet[i]->loadMap(mapItem, mapProperty);
			bullet[i]->fire(realpos.x+15,realpos.y+15,rad);
			break;
		}
	}
}
void Weapon::summon(GamePlayer* p)
{
	if (mode == 3&&p->ShowMP()>9)
		for (int i = 0; i < MAX_HURRICANE; i++)
			if (!hurricane[i]->Active())
			{
				effect_Magic->playEffect(ONE, -1);
				hurricane[i]->summon(realpos.x + 15, realpos.y + 15, rad);
				p->lossMP(10);
				break;
			}	
}
void Weapon::summon_shark()
{
	if (mode == 8)
	{
		effect_shark->playEffect(ONE, -1);
		sharkbite->summon();
	}
}
void Weapon::throw_Banana()
{
	for (int i = 0; i < MAX_BULLET; i++)
	{
		if (!banana[i]->Active())
		{
			banana[i]->loadMap(mapItem, mapProperty);
			banana[i]->throw_Banana(realpos.x, realpos.y, rad);
			break;
		}
	}
}
void Weapon::send(int n)
{
	if (mode == 5)
	{
		switch (n)
		{
		case 0:
			effect_reset->playEffect(ONE, -1);
			portalring->reset();
			break;
		case 1:
			effect_Portalgun->playEffect(ONE, -1);
			portalring->sendblue(realpos.x, realpos.y, rad);
			break;
		case 2:
			effect_Portalgun->playEffect(ONE, -1);
			portalring->sendoran(realpos.x, realpos.y, rad);
			break;
		}
	}
}

void Weapon::sniperShot(vector<GameMonster*> mst)
{
	if (mode == 6 && snipershot->getBullet() > 0)
	{
		effect_Sniper->playEffect(ONE, -1);
		snipershot->shot(mst);
		snipershot->turnoff();
	}
	else if (mode == 6)
		snipershot->turnoff();
}
void Weapon::musicring_play()
{
	for (int i = 0; i < MAX_MUSICRING; i++)
	{
		if (!musicring[i]->Active())
		{
			musicring[i]->play(pos.x + 15, pos.y + 15);
			break;
		}
	}
}
void Weapon::musicring_stop()
{
	effect_rickroll->stopEffect(1);
	music_on = false;
	for (int i = 0; i < MAX_MUSICRING; i++)
	{
		if (musicring[i]->Active())
		{
			musicring[i]->reset();
		}
	}
}
void Weapon::eat_poop(GamePlayer* p)
{
	if (mode == 10)
	{
		effect_poop->playEffect(ONE, -1);
		poop->eat(p);
	}
}

void Weapon::sniperReload()
{
	if (mode == 6)
	{
		effect_reload->playEffect(ONE, -1);
		snipershot->reload();
	}
}

void Weapon::Active(bool a)
{
	active = a;
	if (!a)
		lazerbeam->turnoff();
}

void Weapon::changeMode(int type)
{
	if (type == 8)
		sharkbite->setActive(true);
	else
		sharkbite->setActive(false);
	
	switch (type)
	{
	case 0:
		mode = 0;
		break;
	case 1:
		mode = 1;
		break;
	case 2:
		mode = 2;
		break;
	case 3:
		mode = 3;
		break;
	case 4:
		mode = 4;
		break;
	case 5:
		mode = 5;
		break;
	case 6:
		mode = 6;
		break;
	case 7:
		mode = 7;
		break;
	case 8:
		mode = 8;
		break;
	case 9:
		mode = 9;
		break;
	case 10:
		mode = 10;
		break;
	}
}

void Weapon::setDir(int xx, int yy)
{
	dir.setXY(xx, yy);
}

void Weapon::loadMap(const char map[MAPY][MAPX], const bool tmp[MAPY][MAPX])
{
	for (int i = 0; i < MAPY; i++)
		for (int j = 0; j < MAPX; j++)
			mapItem[i][j] = map[i][j];

	for (int i = 0; i < MAPY; i++)
		for (int j = 0; j < MAPX; j++)
			mapProperty[i][j] = tmp[i][j];

	lazerbeam->loadMap(map, tmp);
	snipershot->loadMap(map, tmp);
	portalring->loadMap(map, tmp);
	sharkbite->loadMap(map, tmp);
}

void Weapon::startTimer(Uint32 t)
{
	time = t;
	frame = 0;
	timerID = SDL_AddTimer(time, changeData, this); // Set Timer callback
}
void Weapon::stopTimer()
{
	time = 0;
}
Uint32 Weapon::changeData(Uint32 interval, void* param)
{
	Weapon* p = (Weapon*)param;

	if (p->time != 0)
	{
		p->frame = (p->frame + 1) % p->wn;  // image frame	
		return interval;
	}
	else
	{
		return 0;
	}
}
