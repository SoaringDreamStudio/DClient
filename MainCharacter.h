#pragma once
#include "graphics.h"
#include "libraries.h"
#include "Menu.h"
#include "struct.h"

class MainCharacter
{
public:
	MainCharacter(std::string passed_NickName,
               CSDL_Setup* passed_SDL_Setup,
               int *passed_MouseX,
               int *passed_MouseY,
               float *passed_CameraX,
               float *passed_CameraY,
               LoadingProcess* loadingProcess,
               GameInterface* passed_gameInterface,
               net::Socket* passed_gsocket);
	~MainCharacter(void);

	double GetDistance(int X1, int Y1, int X2, int Y2);

	void Update();
	void Draw();
	int* GetHP() {return &HP;}
	void SetHP(int passed_HP) {HP=passed_HP;}
	int* GetMaxHP() {return &maxHP;}
	void SetMaxHP(int passed_maxHP) {maxHP=passed_maxHP;}
    int getDirection();
    void sendPosition(std::string);

	void SendInfoToInterface();

	std::string getNickName() {return NickName;}
    CSprite* getSprite() {return SpriteMainHero;}
    int getSpeed() {return speed;}

private:
    GameInterface* gameInterface;
    void UpdateAnimation();
    void UpdateControls();
    float *CameraX;
    float *CameraY;

    std::string NickName;

    int *MouseX;
    int *MouseY;

    CSDL_Setup* csdl_setup;
    net::Socket* gsocket;

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
    int sendTimer;
    enum Direction
    {
        up,
        left,
        right,
        down
    };
    bool onceSendDirection;
    Direction lastDirection;

    int nightTimer;
    bool escapeMenu;
};

