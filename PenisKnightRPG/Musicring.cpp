#include "Musicring.h"

Musicring::Musicring()
{
	reset();
}
Musicring::~Musicring()
{

}
void Musicring::update(float x, float y)
{
	if (active)
	{
		pos.x = x;
		pos.y = y;
		radius ++;
		if (radius > 128)
			reset();

		cooldown++;
		cooldown %= 20;
		if (cooldown == 0)
			color_index = (color_index + 1) % 7;
	}
}
void Musicring::render()
{
	if (active)
	{
		TM->DrawCircle(pos.x, pos.y, radius, rainbow[color_index].r, rainbow[color_index].g, rainbow[color_index].b, 200);
	}
}
void Musicring::reset()
{
	active = false;
	radius = 0;
	cooldown = 0;
	color_index = 0;
}
void Musicring::play(float x, float y)
{
	active = true;
	pos.x = x;
	pos.y = y;
}
