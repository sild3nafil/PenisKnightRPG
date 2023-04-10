#include "WeaponItem.h"

WeaponItem::WeaponItem()
{
	cooldown = 0;
}
WeaponItem::~WeaponItem()
{}

bool WeaponItem::Outta()
{
	if (pos.x > 1280 / 2 || pos.x < 0 || pos.y>960 / 2 || pos.y < 0)
		return true;
	return false;
}

void WeaponItem::loadMap(const char map[MAPY][MAPX], const bool tmp[MAPY][MAPX]) {
	for (int i = 0; i < MAPY; i++)
		for (int j = 0; j < MAPX; j++)
			mapItem[i][j] = map[i][j];

	for (int i = 0; i < MAPY; i++)
		for (int j = 0; j < MAPX; j++)
			mapProperty[i][j] = tmp[i][j];
}