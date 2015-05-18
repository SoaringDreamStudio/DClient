#pragma once
#include "../Live.h"
#include "../../Items.h"
class Characters : public Live
{
public:
    Characters(coordinates* spawn,
                float* CameraX,
                float* CameraY,
                CSDL_Setup* csdl_setup,
                SDL_Rect Hitbox,
                bool ExistOnMap,
                int ID,
                int PosX,
                int PosY,
                std::string ActiveAnimation,
                std::map<std::string, AnimationInfo> Animations,
                int fpX,
                int fpY,
                int HP,
                int MS,
                int Range,
                int AttackDmg,
                int Defense,
                int AttackCDTime,
                int AttackAnimationTime,
                std::string NickName,
                std::vector<Items> Inventory,
                int WSLOT,
                int ASLOT,
                int Hunger
                );
    Characters(coordinates* spawn,
                float* CameraX,
                float* CameraY,
                CSDL_Setup* csdl_setup,
                int ID,
                int PosX,
                int PosY,
                std::string NickName
                );

	~Characters(void);

	std::string getNickName() {return NickName;}

	void Draw();
protected:
    std::string NickName;
    std::vector<Items> Inventory;
    int WSLOT;
    int ASLOT;
    int Hunger;

};
