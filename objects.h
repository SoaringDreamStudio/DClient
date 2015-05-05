#pragma once
#include "stdafx.h"
#include "Sprite.h"
#include "SDL_Setup.h"
class gameObject;
class EffectInfo
{
public:
    EffectInfo() {ID=0;Time=0;parent=0;}
    EffectInfo(int passed_ID,int passed_Time,gameObject* passed_parent) {ID=passed_ID;Time=passed_Time;parent=passed_parent;}
    ~EffectInfo() {}
    int getID() {return ID;}
    void setID(int passed_ID) {ID = passed_ID;}
    int getTime() {return Time;}
    void setTime(int passed_Time) {Time = passed_Time;}
    gameObject* getEffectParent() {return parent;}
    void setEffectParent(gameObject* passed_EffectParent) {parent = passed_EffectParent;}
private:
    int ID;
    int Time;
    gameObject* parent;
};

class gameObject
{
public:
	gameObject(std::string Passed_ClassName, int passed_ID, int *passed_MouseX, int *passed_MouseY, int X, int Y, int W, int H, float* CameraX, float* CameraY, CSDL_Setup* passed_csdl_setup, coordinates* passed_spawn);
	~gameObject(void);

    CSprite* getSprite() { return sprite;}

    std::vector<EffectInfo*> getEffects() {return effects;}
    double GetDistance(int X1, int Y1, int X2, int Y2);
    void setFollowPoint(int X, int Y) {Follow_Point_X = X; Follow_Point_Y = Y;}

    void Draw();
    void LoadConfigs();

    //debug
    void writeSprite() {std::cout << "sprite " << sprite->getImage() << std::endl;}
    void writeSpritePath() {std::cout << "FilePathSprite " << FilePathSprite << std::endl;}

protected:
    std::string ClassName;
    std::string ObjectName;
    int ID;
    bool invisible;
    coordinates* spawn;
    CSDL_Setup* csdl_setup;
    SDL_Rect Rect;
    SDL_Rect hitbox;
    SDL_Rect crop;
    std::string FilePath;
    std::string FilePathSprite;
    int SpriteCropX;
    int SpriteCropY;


    bool Follow;
	int Follow_Point_X;
	int Follow_Point_Y;
	float* CameraX;
    float* CameraY;

    int timeCheckMoving;

	int *MouseX;
    int *MouseY;

	float distance;
    float speed;

    CSprite* sprite;
    std::vector<EffectInfo*> effects;
    std::map<std::string,AnimationInfo> animations;
};

class gameSpace : public gameObject
{
public:
    gameSpace(std::string Passed_ClassName, int passed_ID, int *passed_MouseX, int *passed_MouseY, int X, int Y, int W, int H, float* CameraX, float* CameraY, CSDL_Setup* passed_csdl_setup, coordinates* passed_spawn) :  gameObject(Passed_ClassName, passed_ID, passed_MouseX, passed_MouseY, X, Y, W, H, CameraX, CameraY, passed_csdl_setup, passed_spawn)
    { }

	~gameSpace(void) {};
};

class gameItem : public gameSpace
{
public:
    gameItem(int passed_ID, int *passed_MouseX, int *passed_MouseY, int X, int Y, int W, int H, float* CameraX, float* CameraY, CSDL_Setup* passed_csdl_setup, coordinates* passed_spawn) :  gameSpace("gameItem", passed_ID, passed_MouseX, passed_MouseY, X, Y, W, H, CameraX, CameraY, passed_csdl_setup, passed_spawn)
    {ClassName = "gameItem";}
    gameItem(std::string Passed_ClassName, int passed_ID, int *passed_MouseX, int *passed_MouseY, int X, int Y, int W, int H, float* CameraX, float* CameraY, CSDL_Setup* passed_csdl_setup, coordinates* passed_spawn) :  gameSpace(Passed_ClassName, passed_ID, passed_MouseX, passed_MouseY, X, Y, W, H, CameraX, CameraY, passed_csdl_setup, passed_spawn)
    {ClassName = Passed_ClassName;}

	~gameItem(void) {};
};

class gameFood : public gameItem
{
public:
    gameFood(int passed_ID, int *passed_MouseX, int *passed_MouseY, int X, int Y, int W, int H, float* CameraX, float* CameraY, CSDL_Setup* passed_csdl_setup, coordinates* passed_spawn) :  gameItem("gameFood", passed_ID, passed_MouseX, passed_MouseY, X, Y, W, H, CameraX, CameraY, passed_csdl_setup, passed_spawn)
    {ClassName = "gameFood"; LoadConfigs();}

	~gameFood(void) {};
	int GetEnergy()
	{
	    return static_cast<int>(Protein*4 + Carbohydrate*3,75 + Fat*9);
	}
	int GetProtein() {return Protein;}
	int GetCarbohydrate() {return Carbohydrate;}
	int GetFat() {return Fat;}
	void LoadConfigs();
private:
    int Energy;
    int Protein;
    int Carbohydrate;
    int Fat;
};

class gameAbilityItem : public gameSpace
{
public:
    gameAbilityItem(int passedLifeTime, int passed_ID, int *passed_MouseX, int *passed_MouseY, int X, int Y, int W, int H, float* CameraX, float* CameraY, CSDL_Setup* passed_csdl_setup, coordinates* passed_spawn) :  gameSpace("gameAbilityItem", passed_ID, passed_MouseX, passed_MouseY, X, Y, W, H, CameraX, CameraY, passed_csdl_setup, passed_spawn)
    {ClassName = "gameAbilityItem"; lifeTime = passedLifeTime; lifeTimer = SDL_GetTicks(); plsDestroyMe = false; LoadAnimations(); timeCreate=SDL_GetTicks();
        AnimationInfo tmpAI;tmpAI.BeginFrame = 998;tmpAI.EndFrame = 999;tmpAI.Row = 0;
        tmpAI.Speed = 1;animations["creating"] = tmpAI;
    }
	~gameAbilityItem(void) {};
    bool Destroy() {return plsDestroyMe;}
    void LoadAnimations();
	void Draw();
	std::map<std::string,std::vector<EffectInfo*> > getAnimationEffects() {return animationEffects;}
	std::string getActiveAnimation() {return activeAnimation;}
private:
    void update();
    void updateAnimation();
    int lifeTime;
    int lifeTimer;
    int timeCreate;
    std::string activeAnimation;
    std::map<std::string,std::vector<EffectInfo*> > animationEffects;
    bool plsDestroyMe;
};

class gameFloor : public gameSpace
{
public:
    gameFloor(std::string Passed_ClassName, int passed_ID, int *passed_MouseX, int *passed_MouseY, int X, int Y, int W, int H, float* CameraX, float* CameraY, CSDL_Setup* passed_csdl_setup, coordinates* passed_spawn) :  gameSpace(Passed_ClassName, passed_ID, passed_MouseX, passed_MouseY, X, Y, W, H, CameraX, CameraY, passed_csdl_setup, passed_spawn)
    { }


	~gameFloor(void) {};
};

class gameGround : public gameFloor
{
public:
    gameGround(int passed_ID, int *passed_MouseX, int *passed_MouseY, int X, int Y, int W, int H, float* CameraX, float* CameraY, CSDL_Setup* passed_csdl_setup, coordinates* passed_spawn) :  gameFloor("gameGround", passed_ID, passed_MouseX, passed_MouseY, X, Y, W, H, CameraX, CameraY, passed_csdl_setup, passed_spawn)
    {ClassName = "gameGround"; }

	~gameGround(void) {};
    void Draw();
};

class gameWater : public gameFloor
{
public:
    gameWater(int passed_ID, int *passed_MouseX, int *passed_MouseY, int X, int Y, int W, int H, float* CameraX, float* CameraY, CSDL_Setup* passed_csdl_setup, coordinates* passed_spawn) :  gameFloor("gameWater", passed_ID, passed_MouseX, passed_MouseY, X, Y, W, H, CameraX, CameraY, passed_csdl_setup, passed_spawn)
    {ClassName = "gameWater"; }

	~gameWater(void) {};
};

class gameActor : public gameObject
{
public:
    gameActor(std::string Passed_ClassName, int passed_ID, int *passed_MouseX, int *passed_MouseY, int X, int Y, int W, int H, float *CameraX, float *CameraY, CSDL_Setup* passed_csdl_setup, coordinates* passed_spawn) :  gameObject(Passed_ClassName, passed_ID, passed_MouseX, passed_MouseY, X, Y, W, H, CameraX, CameraY, passed_csdl_setup, passed_spawn)
    { }

	~gameActor(void) {};
};
