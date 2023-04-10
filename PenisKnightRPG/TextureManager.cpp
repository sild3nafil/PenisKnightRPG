#include "TextureManager.h"

SDL_Texture* TextureManager::LoadTexture(const char* filename) {
	SDL_Surface* TexSurface = IMG_Load(filename);
	SDL_Texture* Tex = SDL_CreateTextureFromSurface(Game::renderer, TexSurface);
	SDL_FreeSurface(TexSurface);

	return Tex;
}
//Use Surface and Texture to load .png to renderer

SDL_Texture* TextureManager::LoadFontTexture(const char* filename,const char* str,int size,SDL_Color fgColor) 
{
	TTF_Font* Font = TTF_OpenFont(filename, size);
	if (Font == NULL)
	{
		printf("failed\n");
		exit(0);
	}
	TTF_SetFontStyle(Font, TTF_STYLE_BOLD);
	SDL_Surface* TexSurface = TTF_RenderText_Solid(Font, str, fgColor);
	SDL_Texture* Tex = SDL_CreateTextureFromSurface(Game::renderer, TexSurface);
	TTF_CloseFont(Font);
	SDL_FreeSurface(TexSurface);

	return Tex;
}

void TextureManager::Draw(SDL_Texture* tex, SDL_Rect dRect)
{
	SDL_RenderCopy(Game::renderer, tex, NULL, &dRect);
}

void TextureManager::Draw(SDL_Texture* tex, SDL_Rect srcRect, SDL_Rect dRect)
{
	SDL_RenderCopy(Game::renderer, tex, &srcRect, &dRect);
}
//draw the onject one the map

void TextureManager::DrawEx(SDL_Texture* tex, SDL_Rect srcRect, SDL_Rect dRect, SDL_Point center, double angle, SDL_RendererFlip flip)
{
	SDL_RenderCopyEx(Game::renderer, tex, &srcRect, &dRect, angle, &center, flip);
}

void TextureManager::DrawRect(SDL_Rect dRect)
{
	SDL_RenderDrawRect(Game::renderer, &dRect);
}

void TextureManager::DrawLine(int x1,int y1,int x2,int y2,int r,int g,int b,int a)
{
	thickLineRGBA(Game::renderer, x1, y1, x2, y2, 4, r, g, b, a); //252,76,2,100
}

void TextureManager::DrawCircle(int x, int y, int rad, int r, int g, int b, int a)
{
	circleRGBA(Game::renderer, x, y, rad, r, g, b, a);
}

void TextureManager::DrawFilledCircle(int x,int y,int rad,int r,int g,int b,int a)
{
	filledCircleRGBA(Game::renderer, x, y, rad, r, g, b, a);
}

void TextureManager::DrawFilledRect(int x, int y, int w, int h, int r, int g, int b, int a)
{
	boxRGBA(Game::renderer, x, y, x + w, y + h, r, g, b, a);
}
