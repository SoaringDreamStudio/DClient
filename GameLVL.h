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
    int setHours(int i) {hours = i;}
    int setMinute(int i) {minutes = i;}

    bool isNight() {return night;}
    bool setNight(bool i) {night = i;}
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

