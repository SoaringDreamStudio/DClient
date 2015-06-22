
#include "GameLVL.h"


GameLVL::GameLVL(float *passed_CameraX, float *passed_CameraY, int* passed_MouseX, int* passed_MouseY, CSDL_Setup* passed_csdl_setup, LoadingProcess* loadingProcess, MainCharacter* passed_MainHero)
{
    MainHero = passed_MainHero;
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
    spawn.x = 0;
    spawn.y = 0;

    loadingProcess->addProcent(9);


    loadingProcess->addProcent(9);
    /*
    characters.push_back(new Characters(&spawn,
                                        CameraX,
                                        CameraY,
                                        csdl_setup,
                                        1,
                                        100,
                                        100,
                                        "LOL"));

    mobs.push_back(new Mobs(&spawn,
                            CameraX,
                            CameraY,
                            csdl_setup,
                            1,
                            100,
                            100));
    ground.push_back(new Ground(&spawn,
                            CameraX,
                            CameraY,
                            csdl_setup,
                            1,
                            100,
                            100));
    normal.push_back(new Normal(&spawn,
                            CameraX,
                            CameraY,
                            csdl_setup,
                            1,
                            100,
                            100));
    trigger.push_back(new Trigger(&spawn,
                            CameraX,
                            CameraY,
                            csdl_setup,
                            1,
                            100,
                            100,
                            false,
                            1));
    wtrig.push_back(new Wtrig(&spawn,
                            CameraX,
                            CameraY,
                            csdl_setup,
                            1,
                            100,
                            100,
                            false,
                            1));*/




    loadingProcess->addProcent(9);
    LoadStage();
}


GameLVL::~GameLVL(void)
{

}

void GameLVL::LoadStage()
{
    //��������� ����� �������� ��� ������
    std::ifstream LoadedFile("data/stages/stage.dat");

    //������������� ����������-������ ��� ������ ��������
    std::string line;

    //���� ���� ��� ������� ������
    if (LoadedFile.is_open())
    {
        //��������� �� ��� ���, ���� ��� ������
        while ( LoadedFile.good() )
        {
            //������� ������ �� �����
            std::getline(LoadedFile, line);

            //�������� � ����� ������ �� string
            std::istringstream iss(line);

            int ID;
            int X;
            int Y;

            //���������� "���������� ����� � ������" � "������ ����� � ������"
            std::string PreviousWord;

            //���� �� ������ �� �����������
            while (iss)
            {

                //������� �����
                std::string word;


                //������� ����� ����������� �� ������
                iss >> word;

                //���� ���������� ����� name, �� ���������� ����� �� ��������� ����������
                if(PreviousWord == "ID:")
                    ID = atoi(word.c_str());

                if(PreviousWord == "x:")
                    X = atoi(word.c_str());

                if(PreviousWord == "y:")
                    Y = atoi(word.c_str());



                //���������� ����� ���������� � ��������
                PreviousWord = word;
            }
            CreateGround(ID,
                            X,
                            Y);/*
            ground.push_back(new Ground(&spawn,
                                        ID,
                                        X,
                                        Y));*/


        }
    }
    else // � ������ ������������� ������� ���� - ������ ������
    {
        std::cout << "File could not be open " << std::endl;
    }

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



/*
        //������� ������������ � ���������
        for (int i = 0; i < characters.size(); i++)
        {

            if (SpriteMainHero->isColliding(characters[i]->getSprite()->GetCollisionRect()))
            {
                ////////////////////////////////////////////////////////////////////////////////////////
                ////////////////////////////////////////////////////////////////////////////////////////
                ////////////////////////////////////////////////////////////////////////////////////////
                ////////////////////////////////////////////////////////////////////////////////////////
                ////////////////////////////////////////////////////////////////////////////////////////
                //std::cout << "I'm colliding!" << std::endl;
                ////////////////////////////////////////////////////////////////////////////////////////
                ////////////////////////////////////////////////////////////////////////////////////////
                ////////////////////////////////////////////////////////////////////////////////////////
                ////////////////////////////////////////////////////////////////////////////////////////
            }

            //������ ������������ � ��������� - ON
            colldingWithObject = true;

            //���������� �������
            timeCheck = SDL_GetTicks();
        }

        //������� ������������ � ���������
        for (int i = 0; i < gameLVL->GetMobs().size(); i++)
        {

            if (SpriteMainHero->isColliding(gameLVL->GetMobs()[i]->getSprite()->GetCollisionRect()))
            {
                ////////////////////////////////////////////////////////////////////////////////////////
                ////////////////////////////////////////////////////////////////////////////////////////
                ////////////////////////////////////////////////////////////////////////////////////////
                ////////////////////////////////////////////////////////////////////////////////////////
                ////////////////////////////////////////////////////////////////////////////////////////
                ////////////////////////////////////////////////////////////////////////////////////////
                ////////////////////////////////////////////////////////////////////////////////////////
                //std::cout << "I'm colliding!" << std::endl;
                ////////////////////////////////////////////////////////////////////////////////////////
                ////////////////////////////////////////////////////////////////////////////////////////
                ////////////////////////////////////////////////////////////////////////////////////////
                ////////////////////////////////////////////////////////////////////////////////////////
                ////////////////////////////////////////////////////////////////////////////////////////
                ////////////////////////////////////////////////////////////////////////////////////////
            }

            //������ ������������ � ��������� - ON
            colldingWithObject = true;

            //���������� �������
            timeCheck = SDL_GetTicks();
        }
*/
        //������� ������������ � ���������
        for (std::vector<Normal*>::iterator it = normal.begin(); it != normal.end(); it++)
        {
            if((*it)->getSprite()->isColliding(MainHero->getSprite()->GetCollisionRect()))
            {
                if(MainHero->getDirection() == 0)
                {
                    *CameraY = *CameraY - MainHero->getSpeed();
                    MainHero->sendPosition("stopu");
                }
                if(MainHero->getDirection() == 1)
                {
                    *CameraX = *CameraX + MainHero->getSpeed();
                    *CameraY = *CameraY - MainHero->getSpeed();
                    MainHero->sendPosition("stopu");
                }
                if(MainHero->getDirection() == 2)
                {
                    *CameraX = *CameraX + MainHero->getSpeed();
                    MainHero->sendPosition("stopl");
                }
                if(MainHero->getDirection() == 3)
                {
                    *CameraX = *CameraX + MainHero->getSpeed();
                    *CameraY = *CameraY + MainHero->getSpeed();
                    MainHero->sendPosition("stopd");
                }
                if(MainHero->getDirection() == 4)
                {
                    *CameraY = *CameraY + MainHero->getSpeed();
                    MainHero->sendPosition("stopd");
                }
                if(MainHero->getDirection() == 5)
                {
                    *CameraX = *CameraX - MainHero->getSpeed();
                    *CameraY = *CameraY + MainHero->getSpeed();
                    MainHero->sendPosition("stopd");
                }
                if(MainHero->getDirection() == 6)
                {
                    *CameraX = *CameraX - MainHero->getSpeed();
                    MainHero->sendPosition("stopr");
                }
                if(MainHero->getDirection() == 7)
                {
                    *CameraX = *CameraX - MainHero->getSpeed();
                    *CameraY = *CameraY - MainHero->getSpeed();
                    MainHero->sendPosition("stopu");
                }
            }

        }

        //������� ������������ � ���������
        for (std::vector<Wtrig*>::iterator it = wtrig.begin(); it != wtrig.end(); it++)
        {
/*
            if (SpriteMainHero->isColliding(gameLVL->GetWtrig()[i]->getSprite()->GetCollisionRect()))
            {
                ////////////////////////////////////////////////////////////////////////////////////////
                ////////////////////////////////////////////////////////////////////////////////////////
                ////////////////////////////////////////////////////////////////////////////////////////
                ////////////////////////////////////////////////////////////////////////////////////////
                ////////////////////////////////////////////////////////////////////////////////////////
                //std::cout << "I'm colliding!" << std::endl;

                ////////////////////////////////////////////////////////////////////////////////////////
                ////////////////////////////////////////////////////////////////////////////////////////
                ////////////////////////////////////////////////////////////////////////////////////////
                ////////////////////////////////////////////////////////////////////////////////////////
                ////////////////////////////////////////////////////////////////////////////////////////
            }

            //������ ������������ � ��������� - ON
            colldingWithObject = true;

            //���������� �������
            timeCheck = SDL_GetTicks();*/
        }

        //������� ������������ � ���������
        for (std::vector<Trigger*>::iterator it = trigger.begin(); it != trigger.end(); it++)
        {
/*
            if (SpriteMainHero->isColliding(gameLVL->GetTrigger()[i]->getSprite()->GetCollisionRect()))
            {

            }

            //������ ������������ � ��������� - ON
            colldingWithObject = true;

            //���������� �������
            timeCheck = SDL_GetTicks();*/
        }

}

void GameLVL::DelCharacter(std::string NickName)
{
    for(std::vector<Characters*>::iterator it = characters.begin();it != characters.end(); it++)
    {
        if((*it)->getNickName() == NickName)
        {
            characters.erase(it);
            it = characters.begin();
            if(characters.begin() == characters.end())
                break;
        }
    }
}
