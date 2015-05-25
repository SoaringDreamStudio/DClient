#pragma once
#include "libraries.h"
#include "graphics.h"
#include "objects.h"
#include "Menu.h"
#include <vector>
class GameLVL
{
public:
	GameLVL(float* CameraX, float* CameraY, int* MouseX, int* MouseY, CSDL_Setup* passed_csdl_setup, LoadingProcess* loadingProcess);
	~GameLVL(void);

    void DrawBack();
    void DrawFront();

    void Update();
    void UpdateAnimation();

    int getHours() {return hours;}
    int getMinute() {return minutes;}
    void setHours(int i) {hours = i;}
    void setMinute(int i) {minutes = i;}

    void setSpawnX(int X) {spawn.x = X;}
    void setSpawnY(int Y) {spawn.y = Y;}

    bool isNight() {return night;}
    bool setNight(bool i) {night = i;}
    coordinates getSpawn() {return spawn;}
    std::vector<Characters*> GetCharacters() {return characters;}
	std::vector<Mobs*> GetMobs() {return mobs;}
	std::vector<Normal*> GetNormal() {return normal;}
	std::vector<Wtrig*> GetWtrig() {return wtrig;}
	std::vector<Trigger*> GetTrigger() {return trigger;}
	std::vector<Ground*> GetGround() {return ground;}


	void CreateGround(int ID,int PosX,int PosY) {ground.push_back(new Ground(&spawn,
                                                                            CameraX,
                                                                            CameraY,
                                                                            csdl_setup,
                                                                            ID,
                                                                            PosX,
                                                                            PosY));}
    void CreateNormal(int ID,int PosX,int PosY) {normal.push_back(new Normal(&spawn,
                                                                            CameraX,
                                                                            CameraY,
                                                                            csdl_setup,
                                                                            ID,
                                                                            PosX,
                                                                            PosY));}
    void CreateCharacter(int ID,int PosX,int PosY,std::string NickName) {characters.push_back(new Characters(&spawn,
                                                                                CameraX,
                                                                                CameraY,
                                                                                csdl_setup,
                                                                                ID,
                                                                                PosX,
                                                                                PosY,
                                                                                NickName));}
private:
    GameInterface* gameInterface;
    CSDL_Setup* csdl_setup;

	int* MouseX;
    int* MouseY;
    float* CameraX;
    float* CameraY;
    bool OnePressed;

	std::vector<Characters*> characters;
	std::vector<Mobs*> mobs;
	std::vector<Normal*> normal;
	std::vector<Wtrig*> wtrig;
	std::vector<Trigger*> trigger;
	std::vector<Ground*> ground;

	int coordinatesTimer;

	int TimeTimer;
	int hours;
	int minutes;
	std::string tmpHours;
	std::string tmpMinutes;

    coordinates spawn;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////Отредактировать/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	bool night;
	bool changeNightFont;
	bool changeDayFont;
	bool changeNightGround;
	bool changeDayGround;
	bool changeNightFood;
	bool changeDayFood;
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	int debugTimer = SDL_GetTicks();
};

