#pragma once
#include "stdafx.h"
#include "Sprite.h"
#include "SDL_Setup.h"
#include "Enviroment.h"
#include "writing.h"
#include "Mybiblio.h"
#include "effects.h"

class Stomach
{
public:
    Stomach(){ timer = SDL_GetTicks();  food = 0;}
    void digest()
    {
        if(food > 0)
        {
            if(timer+650 < SDL_GetTicks())
            {
                food--;
                if(food < 0)
                    food = 0;
                timer = SDL_GetTicks();
            }
        }
    }
    bool Empty()
    {
        if(food > 0)
            return false;
        else
            return true;
    }
    void eating(int i)
    {
        food += i;
    }
private:
    int timer;
    int food;
};


class MainCharacter
{
public:
	MainCharacter(CSDL_Setup* passed_SDL_Setup, int *passed_MouseX, int *passed_MouseY, float *passed_CameraX, float *passed_CameraY, CEnviroment* passed_Enviroment, LoadingProcess* loadingProcess, GameInterface* passed_gameInterface);
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
    CEnviroment* Enviroment;
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
    int timeCheck2; //hitting timer
    std::vector<int*> timeCheck3; //effects timer
    int timeCheck4; //for update
    int timeCheckMoving;
    int healAccumulation;

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

///////////Голод//////////
    int counterEmptyStomach; //счетчик пустого желудка
                             //Если есть статус пустого желудка, то каждую секунду инкрементируется счетчик.
    int timerCheckEmptyStomach;

    int shortageTimer;       //Время начала игровой сессии(отсчет голода)
    int counterShortage;     //счетчик просчета. Как только он достигает 60000 - просчитать недостатки и обнулить
    int shortageEnergy;      //недостаток энергии. просчитывается из недостатков питательных веществ
    int shortageProtein;     //недостаток белка. Просчитывается каждые 12 игровых часов
    int shortageCarbohydrate;//недостаток углеводов
    int shortageFat;         //недостаток жира
    int dayProtein;          //количество потребленного белка
    int dayCarbohydrate;     //количество потребленных углеводов
    int dayFat;              //количество потребленных жиров
    bool sore;               //статус язвы


//////////////////////////

    Stomach stomach;        //желудок
    std::vector<effect*> effects;
    std::vector<Text*> effectTime;

    Text* text1;
    Text* text2;
    Text* text3;
    Text* text4;

    int nightTimer;
    bool escapeMenu;
};

