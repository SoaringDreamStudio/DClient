#include "Normal.h"

Normal::Normal(coordinates* passed_spawn,
                float* passed_CameraX,
                float* passed_CameraY,
                CSDL_Setup* passed_csdl_setup,
                SDL_Rect passed_Hitbox,
                bool passed_ExistOnMap,
                int passed_ID,
                int passed_PosX,
                int passed_PosY,
                std::string passed_ActiveAnimation,
                std::map<std::string, AnimationInfo> passed_Animations,
                bool passed_Collision,
                bool passed_BulletCollision,
                bool passed_PickUpAble)
        : Objects("Normal",
                passed_CameraX,
                passed_CameraY,
                passed_spawn,
                passed_csdl_setup,
                passed_Hitbox,
                passed_ExistOnMap,
                passed_ID,
                passed_PosX,
                passed_PosY,
                passed_ActiveAnimation,
                passed_Animations,
                passed_Collision,
                passed_BulletCollision
                )
{
    PickUpAble = passed_PickUpAble;
}

Normal::~Normal(void)
{

}

void Normal::Draw()
{
    //отрисовать объект
    image->DrawWithCoord(csdl_setup, *spawn);
}

