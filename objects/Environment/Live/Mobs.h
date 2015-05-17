#pragma once
#include "../Live.h"
#include "../../../struct.h"
class Mobs : public Live
{
public:
    Mobs(coordinates* spawn,
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
            bool Aggressive,
            SDL_Rect AgroRange
            );
    Mobs(coordinates* spawn,
                        float* CameraX,
                        float* CameraY,
                        CSDL_Setup* csdl_setup,
                        int ID,
                        int PosX,
                        int PosY);

	~Mobs(void);

	void LoadConfigs();
	void Draw();
protected:
    bool Aggressive;
    SDL_Rect AgroRange;

};
