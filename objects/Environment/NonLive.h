#pragma once
#include "../Environment.h"
class NonLive : public Environment
{
public:
    NonLive(std::string className,
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
            std::map<std::string, AnimationInfo> Animations);

	~NonLive(void);

	void LoadConfigs();

};
