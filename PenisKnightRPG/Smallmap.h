#pragma one
#include<SDL.h>
#include "TextureManager.h"
#include"GamePlayer.h"

class Smallmap
{
public:
	Smallmap();
	~Smallmap();
	void render(GamePlayer*);

private:
	TextureManager* TM;
	SDL_Texture* boss_logo;
};