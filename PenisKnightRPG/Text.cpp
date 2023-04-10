#include "Text.h"

Text::Text()
{}
Text::Text(const char* fn,const char* s, int xx, int yy, int sz, SDL_Color fc)
{
	filename = fn;
	str = new char[strlen(s)];
	strcpy_s(str, strlen(s) + 1, s);

	xpos = xx;
	ypos = yy;
	size = sz;
	fgColor = fc;

	dRect.x = xpos;
	dRect.y = ypos;
	dRect.w = 64;
	dRect.h = 30;

	generateTex();
}
Text::Text(const char* fn, const char* s, int xx, int yy, int sz, int w, int h, SDL_Color fc)
{
	filename = fn;
	str = new char[strlen(s)];
	strcpy_s(str, strlen(s) + 1, s);

	xpos = xx;
	ypos = yy;
	size = sz;
	fgColor = fc;

	dRect.x = xpos;
	dRect.y = ypos;
	dRect.w = w;
	dRect.h = h;

	generateTex();
}
Text::~Text()
{
	close();
}

void Text::render()
{
	TM->Draw(tTex, dRect);
}
void Text::update(char* tmp)
{
	setString(tmp);
	close();
	generateTex();
}

void Text::close()
{
	// Free loaded image	
	SDL_DestroyTexture(tTex);
}

void Text::generateTex()
{
	SDL_DestroyTexture(tTex);
	tTex = TM->LoadFontTexture(filename, str, size, fgColor);
}
void Text::setbase(const char* fn, const char* s, int xx, int yy, int sz, int w, int h, SDL_Color fc)
{
	filename = fn;
	str = new char[strlen(s)];
	strcpy_s(str, strlen(s) + 1, s);

	xpos = xx;
	ypos = yy;
	size = sz;
	fgColor = fc;

	dRect.x = xpos;
	dRect.y = ypos;
	dRect.w = w;
	dRect.h = h;

	generateTex();
}
void Text::setString(const char* s)
{
	str = new char[strlen(s) + 1];
	strcpy_s(str, strlen(s) + 1, s);
}
void Text::setColor(SDL_Color fc)
{
	fgColor = fc;
}

char* Text::getString()
{
	return str;
}
