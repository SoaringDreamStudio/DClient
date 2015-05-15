#pragma once
#include "../graphics.h"
class Items
{
public:
	Items(int ID);
	~Items(void);

protected:
    int ID;
    CSprite* image;

    //Sprite(SDL_Sprite)
};
