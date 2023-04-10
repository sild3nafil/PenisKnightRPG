#pragma once
#include "Game.h"

class TextureManager
{
public:
	SDL_Texture* LoadTexture(const char* filename);
	SDL_Texture* LoadFontTexture(const char* filename, const char*str, int size, SDL_Color fgColor);
	void Draw(SDL_Texture* tex, SDL_Rect dRect);
	void Draw(SDL_Texture* tex, SDL_Rect srcRect, SDL_Rect dRect);
	void DrawEx(SDL_Texture* tex, SDL_Rect srcRect, SDL_Rect dRect, SDL_Point center, double angle, SDL_RendererFlip flip);
	void DrawRect(SDL_Rect dRect);
	void DrawLine(int x1, int y1, int x2, int y2, int r, int g, int b, int a);
	void DrawCircle(int x, int y, int rad, int r, int g, int b, int a);
	void DrawFilledCircle(int x, int y, int rad, int r, int g, int b, int a);
	void DrawFilledRect(int x, int y, int w, int h, int r, int g, int b, int a);
};

