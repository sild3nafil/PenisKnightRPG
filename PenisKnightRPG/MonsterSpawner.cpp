#include "MonsterSpawner.h"
#include "Map.h"
#include "constants.h"

MonsterSpawner::MonsterSpawner()
{
	srand(time(NULL));

	for (int i = 0; i < 5; i++)
	{
		woman[i]=new Woman("assets/woman_animation.png", 0, 0, 500, 3, 96, 16, 4, 4, WOMAN);
		rat[i] = new Rat("assets/rat.png", 0, 0, 100, 87, 64, 16, 4, 4, RAT);
		slime[i] = new Slime("assets/slime.png", 0, 0, 250, 0, 128, 16, 4, 4, SLIME);
	}
	for(int i=0;i<3;i++)
		tower[i] = new Tower("assets/tower.png", 0, 0, 1000, 0, 640, TOWER);
	healer = new Healer("assets/healer.png", 640 * 2 + 300, 480 * 2 + 200, 1500, 0, 640, 16, 4, 4, HEALER);
	skull = new GameBoss("assets/boss_animation.png", 640 * 2 + 320 - 26, 480 * 2 + 240 - 26, 10000, 50, 640, 16, 4, 4, BOSS);
}
MonsterSpawner::~MonsterSpawner()
{}

vector2 MonsterSpawner::setrandomXY()
{
	vector2 xy;
	static int i = 32;
	xy.x = (rand() % (640 - 100) + 100 + i) % 640;
	xy.y = (rand() % (480 - 100) + 100 + i) % 480;
	i += 32;
	return xy;
}

void MonsterSpawner::push_back(vector2 tmp)
{
	static int i = 1;
	if (mst.size() < MAX)
	{
		//GameMonster* m;
		//m = new GameMonster("assets/woman_animation.png", tmp.x, tmp.y, 500, 3, 96, 16, 4, 4);
		/*Woman* woman;
		Rat* rat;
		Slime* slime;*/
		
		switch (i)
		{
		case 1:
			for(int i=0;i<WOMAN_MAX;i++)
				if (!woman[i]->getAlive())
				{
					woman[i]->rez(tmp.x, tmp.y);
					woman[i]->loadMap(mapItem, mapProperty);
					mst.push_back(woman[i]);
					break;
				}
			break;
			//woman = new Woman("assets/woman_animation.png", tmp.x, tmp.y, 500, 3, 96, 16, 4, 4, WOMAN);
		case 2:
			for (int i = 0; i < RAT_MAX; i++)
				if (!rat[i]->getAlive())
				{
					rat[i]->rez(tmp.x, tmp.y);
					rat[i]->loadMap(mapItem, mapProperty);
					mst.push_back(rat[i]);
					break;
				}
			break;
			//rat = new Rat("assets/rat.png", tmp.x, tmp.y, 100, 87, 64, 16, 4, 4, RAT);
		case 3:
			for (int i = 0; i < SLIME_MAX; i++)
				if (!slime[i]->getAlive())
				{
					slime[i]->rez(tmp.x, tmp.y);
					slime[i]->loadMap(mapItem, mapProperty);
					mst.push_back(slime[i]);
					break;
				}
			break;
			//slime = new Slime("assets/slime.png", tmp.x, tmp.y, 250, 0, 128, 16, 4, 4, SLIME);
		}
	}
	i = i % 3 + 1;
}

void MonsterSpawner::clear()
{
	while (mst.size())
	{
		mst[0]->reload();
		mst.erase(mst.begin());
	}
}

void MonsterSpawner::generateMos(int n, int xx, int yy)
{
	vector2 tmp;
	
	for (int i = 0; i < n; i++)
	{
		tmp = setrandomXY();
		tmp = (xx * 640) < tmp;
		tmp = (yy * 480) > tmp;
			
		push_back(tmp);
	}
}
void MonsterSpawner::generateBoss()
{
	//skull = new GameBoss("assets/boss_animation.png", 640 * 2 + 320 - 26, 480 * 2 + 240 - 26, 10000, 50, 640, 16, 4, 4, BOSS);
	if (!skull->getAlive())
	{
		skull->rez(640 * 2 + 320 - 26, 480 * 2 + 240 - 26);
		skull->loadMap(mapItem, mapProperty);
		mst.push_back(skull);
		generateTower(640 * 2 + 100, 480 * 2 + 100);
		generateTower(640 * 2 + 320 - 16, 480 * 3 - 100);
		generateTower(640 * 3 - 100, 480 * 2 + 100);
	}
}
void MonsterSpawner::generateTower(float x, float y)
{
	//Tower* tower;
	//tower = new Tower("assets/tower.png", x, y, 1000, 0, 640, TOWER);
	for (int i = 0; i < TOWER_MAX; i++)
	{
		if (!tower[i]->getAlive())
		{
			printf("true\n");
			tower[i]->rez(x, y);
			tower[i]->loadMap(mapItem, mapProperty);
			mst.push_back(tower[i]);
			break;
		}
	}
}
void MonsterSpawner::generateHealer()
{
	//Healer* healer;
	//healer = new Healer("assets/healer.png", 640 * 2 + 300, 480 * 2 + 200, 1500, 0, 640, 16, 4, 4, HEALER);
	//printf("true\n");
	if (!healer->getAlive())
	{
		healer->rez(640 * 2 + 300, 480 * 2 + 200);
		healer->loadMap(mapItem, mapProperty);
		mst.push_back(healer);
	}
}
void MonsterSpawner::update(GamePlayer* player)
{
	int pre = mst.size();
	int boss_stage_pre=-1;

	if (ratdie > 0)
		ratdie--;
	if (mst.size() >= 1)
	{
		if (mst[0]->getID() == BOSS)
		{
			boss_stage_pre = mst[0]->getStage();
			switch (pre)
			{
			case 1:
				mst[0]->super_state(0, 0, 0);
				break;
			case 2:
				mst[0]->super_state(0, 0, 1);
				break;
			case 3:
				mst[0]->super_state(0, 1, 0);
				break;
			case 4:
				mst[0]->super_state(1, 0, 0);
				break;
			}
		}
	}
	for (int i = 0; i < mst.size(); i++)
	{
		mst[i]->update(player);
		if (!mst[i]->getAlive())
		{			
			//mst[i]->reload();
			player->AddCoin(mst[i]->GetCoin());
			if (mst[i]->code == 2)
				ratdie = 15,ratdiepos.setXY(mst[i]->getxpos(),mst[i]->getypos());
			mst.erase(mst.begin() + i);
			break;
		}
	}
	int now = mst.size();
	int boss_stage_now=-1;

	if (mst.size() >= 1)
		if (mst[0]->getID() == BOSS)
			boss_stage_now = mst[0]->getStage();
	
	//printf("%d\n", mst.size());
	if (boss_stage_pre == 2 && boss_stage_now == 3)
		generateHealer();

	if (mst.size() >= 2)
	{
		if (mst[1]->getID() == HEALER)
		{
			static int summon_cd = 0;
			static int recover_cd = 0;
			if (summon_cd == 0 && pre==2)
			{
				generateTower(640 * 2 + 320 - 16, 480 * 2 + 240 - 16);
			}
			summon_cd = (summon_cd + 1) % 650;
			if (recover_cd == 0)
			{
				mst[0]->onethreeHP();
			}
			recover_cd = (recover_cd + 1) % 1200;
		}
	}


	if (pre && !now)
	{
		map->unlocktheroom((int)player->getrealxpos()/ 640, (int)player->getrealypos() / 480);
	}

}

void MonsterSpawner::render()
{
	if(ratdie)
		TM->DrawFilledCircle(ratdiepos.x + 15, ratdiepos.y + 15, 64, 220, 0, 0, 180);
	for (int i = 0; i < mst.size(); i++)
		mst[i]->render();
}

void MonsterSpawner::loadMap(const char map[MAPY][MAPX], const bool tmp[MAPY][MAPX]) {
	for (int i = 0; i < MAPY; i++)
		for (int j = 0; j < MAPX; j++)
			mapItem[i][j] = map[i][j];

	for (int i = 0; i < MAPY; i++)
		for (int j = 0; j < MAPX; j++)
			mapProperty[i][j] = tmp[i][j];
}
void MonsterSpawner::setMap(Map* mmap)
{
	map = mmap;
}