#pragma once
#include "TextureManager.h"

class Text
{
public:
	Text();
	Text(const char* fn,const char* s, int xx, int yy, int sz, SDL_Color fc);
	Text(const char* fn, const char* s, int xx, int yy, int sz, int w, int h, SDL_Color fc);
	~Text();

	void render();
	void update(char *tmp);
	void close();
	void generateTex();
	void setbase(const char* fn, const char* s, int xx, int yy, int sz, int w, int h, SDL_Color fc);
	void setString(const char* s);
	void setColor(SDL_Color fc);

	char* getString();
	int getxpos() { return xpos; }
	int getypos() { return ypos; }
	int getwidth() { return dRect.w; }
	int getheight() { return dRect.h; }

private:
	const char* filename;
	char* str;
	int xpos;
	int ypos;
	int size;
	SDL_Color fgColor;
	int alpha;
	SDL_Rect dRect;
	SDL_Texture* tTex;
	TextureManager* TM;
};

