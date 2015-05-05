#pragma once
#include "stdafx.h"
#include "Sprite.h"
#include "SDL_Setup.h"
#include "writing.h"
#include "Mybiblio.h"
#include <cstdlib>
#include <sstream>


extern const int ServerPort;
extern const int ClientPort;
extern const int ProtocolId;
extern const float DeltaTime;
extern const float SendRate;
extern const float TimeOut;

class LoadingProcess
{
public:
	LoadingProcess(CSDL_Setup* passed_SDL_Setup, int *passed_MouseX, int *passed_MouseY, float *passed_CameraX, float *passed_CameraY);
	~LoadingProcess(void);

    void addProcent(float);
    float getProgress() {return Progress;}
	void Update();
	void Draw();
private:
    void UpdateAnimation();
    float *CameraX;
    float *CameraY;

    float Progress;
    int ProgressPositionX;

    int *MouseX;
    int *MouseY;

    CSDL_Setup* csdl_setup;

    CSprite* MCHPbar1;
    CSprite* MCHPbar2;
    Text* text1;
    Text* text2;
};

class GameInterface
{
public:
	GameInterface(CSDL_Setup* passed_SDL_Setup, int *passed_MouseX, int *passed_MouseY, float *passed_CameraX, float *passed_CameraY);
	~GameInterface(void);

    bool getMquit() {return Mquit;}
	void Update();
	void Draw();
	void UpdateInformation(int, int, int, bool, bool);
private:
    void UpdateAnimation();
    float *CameraX;
    float *CameraY;

    int HP;
    std::string tmpHP;
    std::string* linkTmpHP;
    int maxHP;
    std::string tmpMaxHP;
    std::string* linkTmpMaxHP;
    bool emptyStomach;       //статус пустого желудка
    int shortageEnergy;      //недостаток энергии. просчитывается из недостатков питательных веществ
    bool sore;               //статус язвы

    int HPstatus;

    int *MouseX;
    int *MouseY;

    CSDL_Setup* csdl_setup;

    CSprite* interface1;
    //CSprite* interface2;

    CSprite* mapForm;
    CSprite* statusForm1;
    CSprite* statusWindow1;
    Text* hungerOfStatusWindow1;
    bool VisibleStatusWindow1;

    CSprite* statusForm2;
    CSprite* statusWindow2;
    Text* HPofStatusWindow2;
    Text* maxHPofStatusWindow2;
    Text* textHPofStatusWindow2;
    Text* textmaxHPofStatusWindow2;
    bool VisibleStatusWindow2;

    CSprite* escapeWindow1;
    Text* escapeButton1text;
    Text* escapeButton2text;
    CSprite* escapeButton1;
    CSprite* escapeButton2;
    bool VisibleEscapeWindow1;

    CSprite* status1;
    int timeCheck1; //таймер наведения на статус (для показа дополнительной информации) (hunger)
    int timeCheck1_1; //время наведения на статус (hunger)
    bool flagTimeCheck1_1; //триггер наведения на статус (hunger)
    CSprite* status2;
    int timeCheck2; //таймер наведения на статус (для показа дополнительной информации) (HP)
    int timeCheck2_1; //время наведения на статус (HP)
    bool flagTimeCheck2_1; //триггер наведения на статус (HP)

    Text* stomachStatus; //статус пустого желудка
    Text* soreStatus; //Язва
    Text* depletionStatus; //истощение

    bool OnePressed = false;
    bool Mquit = false;
};

class MainMenu
{
public:
	MainMenu(CSDL_Setup* passed_SDL_Setup, int *passed_MouseX, int *passed_MouseY, float *passed_CameraX, float *passed_CameraY, net::Socket* passed_gsocket);
	~MainMenu(void);

	void Update();
	void Draw();
    bool getMquit() {return Mquit;}
    void setMquit(bool per) {Mquit = per;}
private:
    void UpdateAnimation();
    net::Socket* gsocket;
    void UpdateControls();
    float *CameraX;
    float *CameraY;

    int *MouseX;
    int *MouseY;

    CSDL_Setup* csdl_setup;

    Text* text1;
    Text* text2;
    Text* connectText1;
    Text* connectText2;
    Text* connectText3;
    Text* connectText4;

    CSprite* MenuButton1;
    CSprite* MenuButton2;
    CSprite* connectMenuButton1;
    CSprite* connectMenuButton2;

    CSprite* MenuBack1;
    CSprite* MenuBack2;

    enum ActiveMenu
    {
        mainMenu,
        connectMenu
    };

    ActiveMenu activeMenu;

    bool Mquit;
};

class GameOverMenu
{
public:
	GameOverMenu(CSDL_Setup* passed_SDL_Setup, int *passed_MouseX, int *passed_MouseY, float *passed_CameraX, float *passed_CameraY);
	~GameOverMenu(void);

	void Update();
	void Draw();
    bool getMquit() {return Mquit;}
private:
    void UpdateAnimation();
    void UpdateControls();
    float *CameraX;
    float *CameraY;

    int *MouseX;
    int *MouseY;

    CSDL_Setup* csdl_setup;

    Text* text1;
    Text* text2;

    CSprite* MenuButton1;
    CSprite* MenuButton2;
    bool Mquit;
};

