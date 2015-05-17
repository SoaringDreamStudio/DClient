#include "NonLive.h"

NonLive::NonLive(std::string passed_className,
                float* passed_CameraX,
                float* passed_CameraY,
                coordinates* passed_spawn,
                CSDL_Setup* passed_csdl_setup,
                SDL_Rect passed_Hitbox,
                bool passed_ExistOnMap,
                int passed_ID,
                int passed_PosX,
                int passed_PosY,
                std::string passed_ActiveAnimation,
                std::map<std::string, AnimationInfo> passed_Animations)

    : Environment( passed_className,
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

NonLive::NonLive(std::string passed_className,
            float* passed_CameraX,
            float* passed_CameraY,
            coordinates* passed_spawn,
            CSDL_Setup* passed_csdl_setup,
            int passed_ID,
            int passed_PosX,
            int passed_PosY)
    :Environment(passed_className,
                passed_CameraX,
                passed_CameraY,
                passed_spawn,
                passed_csdl_setup,
                passed_ID,
                passed_PosX,
                passed_PosY)

{

}

NonLive::~NonLive(void)
{

}

void  NonLive::LoadConfigs(void)
{

}
