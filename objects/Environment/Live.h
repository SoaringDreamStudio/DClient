#pragma once
#include "../Environment.h"
class Live : public Environment
{
public:
    Live(std::string className,
            float* CameraX,
            float* CameraY,
            coordinates* spawn,
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
            int AttackAnimationTime);

    Live(std::string className,
            float* CameraX,
            float* CameraY,
            coordinates* spawn,
            CSDL_Setup* csdl_setup,
            int ID,
            int PosX,
            int PosY);

	~Live(void);

	void LoadConfigs();

protected:
    int fpX;
    int fpY;
    int HP;
    int MS;
    int Range;
    int AttackDmg;
    int Defense;
    int AttackCDTime;
    int AttackAnimationTime;
};
