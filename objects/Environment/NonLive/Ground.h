#pragma once
#include "../NonLive.h"
class Ground : public NonLive
{
public:
    Ground(coordinates* spawn,
            float* CameraX,
            float* CameraY,
            CSDL_Setup* csdl_setup,
            SDL_Rect Hitbox,
            bool ExistOnMap,
            int ID,
            int PosX,
            int PosY,
            std::string ActiveAnimation,
            std::map<std::string, AnimationInfo> Animations);

	~Ground(void);
    void Draw();

};
