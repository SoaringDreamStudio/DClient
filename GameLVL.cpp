
#include "GameLVL.h"


GameLVL::GameLVL(float *passed_CameraX, float *passed_CameraY, int* passed_MouseX, int* passed_MouseY, CSDL_Setup* passed_csdl_setup, LoadingProcess* loadingProcess)
{

    csdl_setup = passed_csdl_setup;
    CameraX = passed_CameraX;
    CameraY = passed_CameraY;

	MouseX = passed_MouseX;
    MouseY = passed_MouseY;

    OnePressed = false;

    hours = 22;
    minutes = 0;

    TimeTimer = SDL_GetTicks();

    tmpHours = IntToStr(hours);
    tmpMinutes = IntToStr(minutes);
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////���������������/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    night = true;
	changeNightFont = false;
	changeDayFont = false;
	changeNightGround = false;
	changeDayGround = false;
	changeNightFood = false;
	changeDayFood = false;
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 // consoleActive = false;

    loadingProcess->addProcent(9);
    spawn.x = 300;
    spawn.y = 150;

    loadingProcess->addProcent(9);


    loadingProcess->addProcent(9);
    characters.push_back(new Characters(&spawn,
                                        CameraX,
                                        CameraY,
                                        csdl_setup,
                                        1,
                                        100,
                                        100,
                                        "LOL"
                                        ));


    loadingProcess->addProcent(9);
}


GameLVL::~GameLVL(void)
{

}

void GameLVL::DrawBack()
{
	for (std::vector<Ground*>::iterator i = ground.begin(); i != ground.end(); ++i)
    {
        (*i)->Draw();
    }

}
void GameLVL::DrawFront()
{
	for (std::vector<Normal*>::iterator i = normal.begin(); i != normal.end(); ++i)
    {
        (*i)->Draw();
    }

	for (std::vector<Wtrig*>::iterator i = wtrig.begin(); i != wtrig.end(); ++i)
    {
        (*i)->Draw();
    }

	for (std::vector<Trigger*>::iterator i = trigger.begin(); i != trigger.end(); ++i)
    {
        (*i)->Draw();
    }

	for (std::vector<Mobs*>::iterator i = mobs.begin(); i != mobs.end(); ++i)
    {
        (*i)->Draw();
    }

	for (std::vector<Characters*>::iterator i = characters.begin(); i != characters.end(); ++i)
    {
        (*i)->Draw();
    }
}

void GameLVL::Update() //������� �������� ������������ ������� ����
{
    //TimeText->Update();

    if(TimeTimer+830 < SDL_GetTicks())
    {
        //������ 0,83 �������
        //+1 ������
        //1200 c����� � 20 �������
        //1440 ����� � 24 �����

        if(minutes == 59)
        {
            if(hours == 23)
            {
                hours = 0;
            }
            else
            {
                hours++;
            }
            minutes = 0;
        }
        minutes++;
        if(hours == 21)
        {
            night = true;
        }
        if(hours == 7)
        {
            night = false;
        }



        if(hours < 10)
        {
           tmpHours = "0" + IntToStr(hours);
        }
        if(minutes < 10)
        {
            tmpMinutes = "0" + IntToStr(minutes);
        }
        else
        {
            tmpHours = IntToStr(hours);
            tmpMinutes = IntToStr(minutes);
        }
        //TimeText->SetText(tmpHours+":"+tmpMinutes);

        TimeTimer = SDL_GetTicks();
    }
    //����������� �� ������� �� �����
}
