#pragma once
#include "../Objects.h"
class Normal : public Objects
{
public:
    Normal(coordinates* spawn,
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
            bool PickUpAble);

    Normal(coordinates* spawn,
            float* CameraX,
            float* CameraY,
            CSDL_Setup* csdl_setup,
            int ID,
            int PosX,
            int PosY);


	~Normal(void);

	void Draw();
protected:
    bool PickUpAble;

};
