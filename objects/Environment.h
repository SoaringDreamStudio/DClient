#pragma once
#include <string>
#include "../graphics.h"
#include "../struct.h"
class Environment
{
public:
	Environment(std::string className,
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
                std::map<std::string, AnimationInfo> Animations);
	Environment(std::string className,
                float* CameraX,
                float* CameraY,
                coordinates* spawn,
                CSDL_Setup* csdl_setup,
                int ID,
                int PosX,
                int PosY);

	~Environment(void);

	void LoadConfigs();
	CSprite* getSprite() {return image;}
	void changeXY(int X, int Y);
	int getID() {return ID;}
	int getX() {return PosX;}
	int getY() {return PosY;}
	std::string getActiveAnimation(){return ActiveAnimation;}
    void setActiveAnimation(std::string passed_ActiveAnimation) {ActiveAnimation = passed_ActiveAnimation;}


protected:
    CSprite* image;
    bool ExistOnMap;
    int ID;
    int PosX;
    int PosY;
    std::string ActiveAnimation;
    std::map<std::string, AnimationInfo> Animations;

    coordinates* spawn;
    CSDL_Setup* csdl_setup;

    std::string className;

    float* CameraX;
    float* CameraY;

    SDL_Rect Rect;
    SDL_Rect hitbox;
    SDL_Rect crop;
    int SpriteCropX;
    int SpriteCropY;
    std::string FilePathSprite;

};
