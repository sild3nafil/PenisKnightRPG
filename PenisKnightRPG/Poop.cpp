#include "Poop.h"

Poop::Poop()
{
	FILE* poopnum;
	fopen_s(&poopnum, "file/poopnum.txt", "r");
	fscanf_s(poopnum, "%d", &poop_num);
	fclose(poopnum);
	_itoa_s(poop_num, p_num_s, 10);
	p_num_t = new Text("fonts/FFFFORWA.TTF", p_num_s, 32, 0, 15, 64, 32, { 255,255,255 });
	fclose(poopnum);
}
Poop::~Poop()
{}

void Poop::update()
{
	_itoa_s(poop_num, p_num_s, 10);
	p_num_t->update(p_num_s);
}
void Poop::render()
{
	p_num_t->render();
}
void Poop::eat(GamePlayer* p)
{
	if (poop_num > 0)
	{
		decrease();
		p->AddHP(25);
		p->AddMP(15);
	}
}
void Poop::increase()
{
	if (poop_num < MAX_POOP_NUM)
		poop_num++;
}
void Poop::decrease()
{
	if (poop_num > 0)
		poop_num--;
}
