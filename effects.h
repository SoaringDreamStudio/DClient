#pragma once
#include "stdafx.h"
#include "Sprite.h"
#include "SDL_Setup.h"
#include "objects.h"

class effect
{
public:
	effect(int passed_ID, gameObject* Parent, int passed_lifeTimer, int X, int Y, int W, int H, float* CameraX, float* CameraY, CSDL_Setup* passed_csdl_setup, coordinates* passed_spawn);
	~effect(void);

    CSprite* getSprite() { return spriteInfo;}
    int getHP() {return HP;}
    int getSpeed() {return speed;}
    int getLifeTimer() {return lifeTimer;}
    void setLifeTimer(int i) {lifeTimer = i;}
    gameObject* getEffectParent() {return Parent;}
    void setEffectParent(gameObject* passedParent) {Parent = passedParent;}
    std::string getFilePathSpriteInfo() {return FilePathSpriteInfo;}
    int getID() {return ID;}
    void setID(int passed_ID) { ID = passed_ID; }
    void Draw();
    void LoadConfigs();

protected:
    gameObject* Parent;
    std::string EffectName;
    int ID;
    int lifeTimer;
    //bool invisible;
    coordinates* spawn;
    CSDL_Setup* csdl_setup;
    SDL_Rect Rect;
    std::string FilePath;
    std::string FilePathSpriteInfo;
    //int SpriteCropX;
    //int SpriteCropY;
    int HP;
    int speed;
    bool statusStack;

    CSprite* spriteInfo;
    std::map<std::string,AnimationInfo> animations;
};
