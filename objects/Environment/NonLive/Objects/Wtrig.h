#pragma once
#include "../Objects.h"
class Wtrig : public Objects
{
public:
    Wtrig(coordinates* spawn,
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
            bool Collision,
            bool BulletCollision,
            int ConnectionID,
            bool Status
            );

    Wtrig(coordinates* spawn,
            float* CameraX,
            float* CameraY,
            CSDL_Setup* csdl_setup,
            int ID,
            int PosX,
            int PosY);

	~Wtrig(void);

	void Draw();

protected:
    int ConnectionID;
    bool Status;

};
