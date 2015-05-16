#pragma once
#include "../Objects.h"
class Trigger : public Objects
{
public:
    Trigger(coordinates* spawn,
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
            bool Status,
            int ConnectionID);
    Trigger(coordinates* spawn,
            float* CameraX,
            float* CameraY,
            CSDL_Setup* csdl_setup,
            int ID,
            int PosX,
            int PosY);

	~Trigger(void);

	void Draw();
protected:
    bool Status;
    int ConnectionID;

};
