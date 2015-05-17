#pragma once
#include "../NonLive.h"
class Objects : public NonLive
{
public:
    Objects(std::string className,
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
            bool Collision,
            bool BulletCollision);

    Objects(std::string className,
            float* CameraX,
            float* CameraY,
            coordinates* spawn,
            CSDL_Setup* csdl_setup,
            int ID,
            int PosX,
            int PosY);

	~Objects(void);

	void LoadConfigs();
protected:
    bool Collision;
    bool BulletCollision;
};
