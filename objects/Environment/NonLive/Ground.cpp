#include "Ground.h"

Ground::Ground(coordinates* passed_spawn,
                float* passed_CameraX,
                float* passed_CameraY,
                CSDL_Setup* passed_csdl_setup,
                SDL_Rect passed_Hitbox,
                bool passed_ExistOnMap,
                int passed_ID,
                int passed_PosX,
                int passed_PosY,
                std::string passed_ActiveAnimation,
                std::map<std::string, AnimationInfo> passed_Animations)
    : NonLive( "Ground",
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
                passed_Animations)
{

}

Ground::Ground(coordinates* passed_spawn,
                        float* passed_CameraX,
                        float* passed_CameraY,
                        CSDL_Setup* passed_csdl_setup,
                        int passed_ID,
                        int passed_PosX,
                        int passed_PosY
                        )
        : NonLive("Ground",
                passed_CameraX,
                passed_CameraY,
                passed_spawn,
                passed_csdl_setup,
                passed_ID,
                passed_PosX,
                passed_PosY)
{

}

Ground::~Ground(void)
{

}
void Ground::Draw()
{
    //отрисовать объект
    image->DrawWithCoord(csdl_setup, *spawn);
}
