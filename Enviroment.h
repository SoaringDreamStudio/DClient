#pragma once
#include "stdafx.h"
#include "Sprite.h"
#include "SDL_Setup.h"
#include "objects.h"
#include "Menu.h"
#include <vector>
class CEnviroment
{
public:
	CEnviroment(float* CameraX, float* CameraY, int* MouseX, int* MouseY, CSDL_Setup* passed_csdl_setup, LoadingProcess* loadingProcess);
	~CEnviroment(void);

    void DrawBack();
    void DrawFront();

    void Update();
    void UpdateAnimation();
    void setSpawn(int x, int y);
    void SaveToFile();
    void LoadFromFile();
    void LoadMap();
    coordinates getSpawn() {return spawn;}
    enum ModeType
    {
        GamePlay,
        LevelCreation
    };
    std::vector<gameObject*> getObjects() {return objects;}
    std::vector<gameItem*> getItems() {return items;}
    std::vector<gameAbilityItem*> getAbilityItems() {return abilityItems;}
    std::vector<gameFood*> getFood() {return food;}
    void delFood(int i) {food.erase(food.begin() + i);}

    void pushItems(int ID, int x, int y, int w, int h) {items.push_back(new gameItem(ID, MouseX, MouseY, x, y, w, h, CameraX, CameraY, csdl_setup, &spawn));}
    void pushAbilityItems(int ID, int x, int y, int w, int h) {abilityItems.push_back(new gameAbilityItem(5000, ID, MouseX, MouseY, x, y, w, h, CameraX, CameraY, csdl_setup, &spawn));}

    void addSprite(std::string, SDL_Texture*);
	bool checkSprite(std::string);
	SDL_Texture* readSprite(std::string);

    int getHours() {return hours;}
    int getMinute() {return minutes;}
    int setHours(int i) {hours = i;}
    int setMinute(int i) {minutes = i;}

    bool isNight() {return night;}
    bool setNight(bool i) {night = i;}
    bool isconsoleActive() {return consoleActive;}

    std::string GetConsoleCommand() {return consoleCommand;}
    void SetConsoleCommand(std::string line) {consoleCommand = line;}
private:
    void writingInConsole();
    void interpretatorOfConsole(std::string);
    int Mode;
    GameInterface* gameInterface;
    CSDL_Setup* csdl_setup;

	int* MouseX;
    int* MouseY;
    float* CameraX;
    float* CameraY;
    bool OnePressed;
	std::vector<gameObject*> objects;
	std::vector<gameGround*> grounds;
	std::vector<gameWater*> waters;
	std::vector<gameItem*> items;
	std::vector<gameFood*> food;
	std::vector<gameAbilityItem*> abilityItems;

    coordinates spawn;
	int tempMapBlocksX; //for map
	int tempMapBlocksY;
	int MapBlocksX; //for map
	int MapBlocksY;

	std::vector<CSprite*> backfont;
	CSprite* TimeWindow;
	Text* TimeText;

	int coordinatesTimer;

	int TimeTimer;
	int hours;
	int minutes;
	std::string tmpHours;
	std::string tmpMinutes;

	bool night;
	bool changeNightFont;
	bool changeDayFont;
	bool changeNightGround;
	bool changeDayGround;
	bool changeNightFood;
	bool changeDayFood;

	CSprite* spriteConsole;
	std::string consoleCommand;
	bool consoleActive;
	Text* ConsoleLine[10];
	bool shiftActive;
	int backspaceTimer; //время от нажатия клавиш
	int backspacePressTimer; //время зажатия от начала нажатия клавиши
	int backspaceTimer1; //таймер нажимания (обновляется после каждого применения)

	int debugTimer = SDL_GetTicks();
};

