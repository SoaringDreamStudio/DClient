#include "Mobs.h"
Mobs::Mobs(coordinates* passed_spawn,
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
            int passed_fpX,
            int passed_fpY,
            int passed_HP,
            int passed_MS,
            int passed_Range,
            int passed_AttackDmg,
            int passed_Defense,
            int passed_AttackCDTime,
            int passed_AttackAnimationTime,
            bool passed_Aggressive,
            SDL_Rect passed_AgroRange
            )

    : Live("Mobs",
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
                passed_fpX,
                passed_fpY,
                passed_HP,
                passed_MS,
                passed_Range,
                passed_AttackDmg,
                passed_Defense,
                passed_AttackCDTime,
                passed_AttackAnimationTime)
{
    Aggressive = passed_Aggressive;
    AgroRange = passed_AgroRange;

}

Mobs::~Mobs(void)
{

}

void Mobs::Draw()
{
    //отрисовать объект
    image->DrawWithCoord(csdl_setup, *spawn);
}

