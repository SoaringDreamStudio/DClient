#include "Wtrig.h"

Wtrig::Wtrig(coordinates* passed_spawn,
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
                int passed_ConnectionID,
                bool passed_Status
                )
    : Objects("Wtrig",
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
    ConnectionID = passed_ConnectionID;
    Status = passed_Status;
}

Wtrig::Wtrig(coordinates* passed_spawn,
                float* passed_CameraX,
                float* passed_CameraY,
                CSDL_Setup* passed_csdl_setup,
                int passed_ID,
                int passed_PosX,
                int passed_PosY,
                bool passed_Status,
                int passed_ConnectionID)
    :Objects("Wtrig",
                passed_CameraX,
                passed_CameraY,
                passed_spawn,
                passed_csdl_setup,
                passed_ID,
                passed_PosX,
                passed_PosY)

{

}

Wtrig::~Wtrig(void)
{

}

void Wtrig::Draw()
{
    //отрисовать объект
    image->DrawWithCoord(csdl_setup, *spawn);
}
