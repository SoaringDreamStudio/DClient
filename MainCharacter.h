#pragma once
#include "graphics.h"
#include "libraries.h"
#include "GameLVL.h"
#include "struct.h"

class MainCharacter
{
public:
	MainCharacter(CSDL_Setup* passed_SDL_Setup, int *passed_MouseX, int *passed_MouseY, float *passed_CameraX, float *passed_CameraY, GameLVL* passed_gameLVL, LoadingProcess* loadingProcess, GameInterface* passed_gameInterface);
	~MainCharacter(void);

	double GetDistance(int X1, int Y1, int X2, int Y2);

	void Update();
	void Draw();
	int* GetHP() {return &HP;}
	void SetHP(int passed_HP) {HP=passed_HP;}
	int* GetMaxHP() {return &maxHP;}
	void SetMaxHP(int passed_maxHP) {maxHP=passed_maxHP;}

	void SendInfoToInterface();

private:
    GameLVL* gameLVL;
    GameInterface* gameInterface;
    void UpdateAnimation();
    void UpdateControls();
    float *CameraX;
    float *CameraY;

    int *MouseX;
    int *MouseY;

    CSDL_Setup* csdl_setup;

    bool OnePressed;
    bool MoveLeft;
    bool MoveDown;
    bool MoveRight;
    bool MoveUp;
    float angle;

    CSprite* SpriteMainHero;
    int timeCheck; //hitting timer from colliding with object
    //std::vector<int*> timeCheck3; //effects timer
    int timeCheck4; //for update
    int timeCheckMoving;

	bool Follow;
	int Follow_Point_X;
	int Follow_Point_Y;

	float distance;
	bool stopAnimation;

    float speed;
    float staticSpeed;

	int tmpW;
    int tmpH;

    int maxHP;
    int HP;

    //Text* text4;

    int nightTimer;
    bool escapeMenu;
};

