#pragma once
#include "../Items.h"
class Equip : public Items
{
public:
    Equip(int ID);

	~Equip(void);

protected:
    CSprite* EQ_Sprite;

};
