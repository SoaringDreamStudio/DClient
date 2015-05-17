#pragma once
#include "libraries.h"
#include "graphics.h"


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
	void UpdateInformation(int, int);
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

    int HPstatus;

    int *MouseX;
    int *MouseY;

    CSDL_Setup* csdl_setup;

    CSprite* downInterface;
    CSprite* weaponIcon;
    CSprite* armorIcon;

    CSprite* HPStatus;
    CSprite* hungerStatus;

    Text* tHPStatus;
    Text* thungerStatus;
    bool VisibleHPStatus;
    bool VisibleHungerStatus;

    CSprite* escapeWindow1;
    Text* escapeButton1text;
    Text* escapeButton2text;
    CSprite* escapeButton1;
    CSprite* escapeButton2;
    bool VisibleEscapeWindow;

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

    CSprite* startButton;
    CSprite* optionsButton;
    CSprite* exitButton;
    //CSprite* connectMenuButton1;
    //CSprite* connectMenuButton2;

    CSprite* BG;

    enum ActiveMenu
    {
        mainMenu,
        connectMenu
    };

    ActiveMenu activeMenu;

    bool Mquit;
};
/*
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
*/
