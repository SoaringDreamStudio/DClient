
#include "Enviroment.h"


CEnviroment::CEnviroment(float *passed_CameraX, float *passed_CameraY, int* passed_MouseX, int* passed_MouseY, CSDL_Setup* passed_csdl_setup, LoadingProcess* loadingProcess)
{

    csdl_setup = passed_csdl_setup;
    CameraX = passed_CameraX;
    CameraY = passed_CameraY;

	MouseX = passed_MouseX;
    MouseY = passed_MouseY;

    Mode = GamePlay;
    OnePressed = false;
    backspaceTimer = SDL_GetTicks();
    backspacePressTimer = 0;
    backspaceTimer1 = SDL_GetTicks();

    hours = 22;
    minutes = 0;

    TimeTimer = SDL_GetTicks();

    tmpHours = IntToStr(hours);
    tmpMinutes = IntToStr(minutes);

    night = true;
	changeNightFont = false;
	changeDayFont = false;
	changeNightGround = false;
	changeDayGround = false;
	changeNightFood = false;
	changeDayFood = false;

	TimeWindow = new CSprite(csdl_setup->GetRenderer(), "data/img/interfaces/window.png", 500, 20,
                              120, 30, CameraX, CameraY, CCollisionRectangle(), csdl_setup);
	TimeText = new Text(tmpHours+":"+tmpMinutes, 525, 29, 15, 15, csdl_setup, CameraX, CameraY);

    consoleActive = false;
    shiftActive = false;
	spriteConsole = new CSprite(csdl_setup->GetRenderer(), "data/img/console.png", 0, 300,
                              800, 300, CameraX, CameraY, CCollisionRectangle(), csdl_setup);
    for(int i = 0; i < 10; ++i)
        ConsoleLine[i] = new Text("", 20, 320+i*20, 15, 15, csdl_setup, CameraX, CameraY);

    for(int i = 0; i <= (csdl_setup->GetScreenWidth()/64)+64; ++i)
    {
        for(int j = 0; j <= (csdl_setup->GetScreenHeight()/64)+64; ++j)
        {
            backfont.push_back(new CSprite(csdl_setup->GetRenderer(), "data/img/water/1.png", i*64, j*64, 64, 64, CameraX, CameraY, CCollisionRectangle(), csdl_setup));
        }
    }

    loadingProcess->addProcent(9);
    spawn.x = 300;
    spawn.y = 150;

    loadingProcess->addProcent(9);
    LoadMap();

    loadingProcess->addProcent(9);

    LoadFromFile();


    loadingProcess->addProcent(9);
}


CEnviroment::~CEnviroment(void)
{

}

void CEnviroment::DrawBack()
{
    //отрисовка фона
    for (std::vector<CSprite*>::iterator i = backfont.begin(); i != backfont.end(); ++i)
    {
        (*i)->DrawSteady();
        if((night == true) && (changeNightFont == false))
        {
            //std::cout<<"time: " << hours << ":" << minutes << std::endl;
            //std::cout<<"night"<<std::endl;
            (*i)->SetCrop(32,0,32,32);
            if(i == backfont.end())
                changeNightFont = true;
        }
        if((night == false) && (changeDayFont == false))
        {
            //std::cout<<"time: " << hours << ":" << minutes << std::endl;
            //std::cout<<"day"<<std::endl;
            (*i)->SetCrop(0,0,32,32);
            if(i == backfont.end())
                changeDayFont = true;
        }
    }

    //отрисовка земли
    for (std::vector<gameGround*>::iterator i = grounds.begin(); i != grounds.end(); ++i)
    {
        (*i)->Draw();
        if((night == true) && (changeNightGround == false))
        {
            //std::cout<<"time: " << hours << ":" << minutes << std::endl;
            //std::cout<<"night"<<std::endl;
            (*i)->getSprite()->SetCrop(32,0,32,32);
            if(i == grounds.end())
                changeNightGround = true;
        }
        if((night == false) && (changeDayGround == false))
        {
            //std::cout<<"time: " << hours << ":" << minutes << std::endl;
            //std::cout<<"day"<<std::endl;
            (*i)->getSprite()->SetCrop(0,0,32,32);
            if(i == grounds.end())
                changeDayGround = true;
        }
    }
    for (std::vector<gameFood*>::iterator i = food.begin(); i != food.end(); ++i)
    {
        (*i)->Draw();
        if((night == true) && (changeNightFood == false))
        {
            //std::cout<<"time: " << hours << ":" << minutes << std::endl;
            //std::cout<<"night"<<std::endl;
            (*i)->getSprite()->SetCrop(150,0,150,100);
            if(i == food.end())
                changeNightFood = true;
        }
        if((night == false) && (changeDayFood == false))
        {
            //std::cout<<"time: " << hours << ":" << minutes << std::endl;
            //std::cout<<"day"<<std::endl;
            (*i)->getSprite()->SetCrop(0,0,150,100);
            if(i == food.end())
                changeDayFood = true;
        }
    }

    //отрисовка воды
    for (std::vector<gameWater*>::iterator i = waters.begin(); i != waters.end(); ++i)
    {
        (*i)->Draw();
    }

    //отрисовка объектов
    for (std::vector<gameItem*>::iterator i = items.begin(); i != items.end(); ++i)
    {
        (*i)->Draw();
    }
    TimeWindow->DrawStatic();
    TimeText->Draw();
    if(consoleActive)
    {
        spriteConsole->DrawStatic();
        for(int i = 0; i < 10; ++i)
            ConsoleLine[i]->Draw();
    }


    try
    {
        //
        for (std::vector<gameAbilityItem*>::iterator i = abilityItems.begin(); i != abilityItems.end(); ++i)
        {
            //приравниваем временную z к переменной plsDestroyMe из gameAbilityItem
            bool z = (*i)->Destroy();

            //если true - удалить объект
            if(z)
            {
                delete (*i);
                abilityItems.erase(i);

                //массив больше одного, то интератор - уменьшается на один
                if(abilityItems.size() > 1)
                {
                    i--;
                }

                //в другом случае - выход из цикла
                else
                {
                    throw z;
                }
            }

            //если false - то отрисовать объект
            else
            {
                (*i)->Draw();
            }

        }
    }
    catch(...){}

    //debug
    switch (csdl_setup->GetMainEvent()->type)
    {
        //если нажата клавиша
        case SDL_KEYDOWN:
            switch (csdl_setup->GetMainEvent()->key.keysym.sym)
            {
                //если нажата клавиша A
                case SDLK_z:
                    csdl_setup->showMap();
                    break;
                case SDLK_x:
                    for (std::vector<gameGround*>::iterator i = grounds.begin(); i != grounds.end(); ++i)
                    {
                        std::cout << "\tSprite: " << (*i)->getSprite() << std::endl;
                        (*i)->writeSpritePath();
                        std::cout << std::endl;
                    }
                    break;
            }
    }
}
void CEnviroment::DrawFront()
{

}

void CEnviroment::setSpawn(int x, int y)
{
    spawn.x = x;
    spawn.y = y;
}

void CEnviroment::LoadMap()
{
    //создается поток файловый для чтения
    std::ifstream LoadedFile("data/Stages/Stage1.map");

    //инициализация переменной-строки для чтения конфигов
    std::string line;

    //инициализация типа объекта
    int CurrentType = TypeNone;

    //если файл был успешно открыт
    if (LoadedFile.is_open())
    {
        //выполнять до тех пор, пока нет ошибок
        while ( LoadedFile.good() )
        {
            //считать строку из файла
            std::getline(LoadedFile, line);

            //если линия Ground.start текущий тип - земля
            if (line == "Ground.start")
            {
                CurrentType = TypeGround;
            }

            //если линия Ground.end, то сбросить текущий тип
            else if (line == "Ground.end")
            {
                CurrentType = TypeNone;
            }

            //в других случаях
            else
            {
                //если текущий тип TypeGround
                if(CurrentType == TypeGround)
                {
                    //добаляет в поток строку из string
                    std::istringstream iss(line);

                    //создание временных переменных
                    std::string PreviousWord;
                    tempMapBlocksX = 0;
                    tempMapBlocksY = 0;

                    //пока не строка не закончилась
                    while (iss)
                    {
                        //текущее слово
                        std::string word;

                        //текущее слово вставляется из потока
                        iss >> word;

                        //если предыдущее слово mapBlocksX:, то считать ее во временную переменую
                        if (PreviousWord == "mapBlocksX:")
                        {
                            tempMapBlocksX = atoi(word.c_str());
                            MapBlocksX = atoi(word.c_str());
                        }

                        //если предыдущее слово mapBlocksY:, то считать ее во временную переменую
                        if (PreviousWord == "mapBlocksY:")
                        {
                            tempMapBlocksY = atoi(word.c_str());
                            MapBlocksY = atoi(word.c_str());

                        }

                        //если указаны tempMapBlocksY && tempMapBlocksX
                        if(tempMapBlocksY && tempMapBlocksX)
                        {
                            //текущее слово
                            std::string mapBlock;

                            //чтение строк
                            for (int i = 0; i < tempMapBlocksY; i++)
                            {
                                std::getline(LoadedFile, line);
                                std::istringstream iss(line);

                                //чтение столбцов
                                for(int j = 0; j < tempMapBlocksX; j++)
                                {

                                    iss >> mapBlock;
                                    grounds.push_back(new gameGround(atoi(mapBlock.c_str()), MouseX, MouseY, j*64,
                                                                     i*64, 64, 64, CameraX, CameraY, csdl_setup, &spawn));

                                }
                            }
                            break;
                        }

                        PreviousWord = word;
                    }
                }

            }
        }
    }
    else //в случае ошибки
    {
        std::cout << "File could not be open: data/Stages/Stage1.map" << std::endl;
    }

}

void CEnviroment::LoadFromFile()
{
    //создается поток файловый для чтения
    std::ifstream LoadedFile("data/Stages/Stage1.map");

    //инициализация переменной-строки для чтения конфигов
    std::string line;

    //инициализация типа объекта (осталось от чтения конфигов для игрового уровня)
    int CurrentType = TypeNone;

    //если файл был успешно открыт
    if (LoadedFile.is_open())
    {
        //выполнять до тех пор, пока нет ошибок
        while ( LoadedFile.good() )
        {
            //считать строку из файла
            std::getline(LoadedFile, line);

            //если линия Items.start текущий тип - предмет
            if (line == "Items.start")
            {
                CurrentType = TypeItem;
            }

            //если линия Items.end, то сбросить текущий тип
            else if (line == "Items.end")
            {
                CurrentType = TypeNone;
            }

            if (line == "Food.start")
            {
                CurrentType = TypeFood;
            }

            //если линия Food.end, то сбросить текущий тип
            else if (line == "Food.end")
            {
                CurrentType = TypeNone;
            }

            //в других случаях
            else
            {
                //если текущий тип TypeItem
                if(CurrentType == TypeItem)
                {
                    //добаляет в поток строку из string
                    std::istringstream iss(line);

                    //переменная "предыдущее слово"
                    std::string PreviousWord;

                    //создание временных переменных
                    int tempID = 0;
                    int tempX = 0;
                    int tempY = 0;
                    int tempH = 0;

                    //пока не строка не закончилась
                    while (iss)
                    {
                        //текущее слово
                        std::string word;

                        //текущее слово вставляется из потока
                        iss >> word;

                        //если предыдущее слово ID: то считать ID
                        if (PreviousWord == "ID:")
                        {
                            tempID = atoi(word.c_str());
                        }

                        //если предыдущее слово x: то считать x
                        if (PreviousWord == "x:")
                        {
                            tempX = atoi(word.c_str());
                        }

                        //если предыдущее слово y: то считать y
                        if (PreviousWord == "y:")
                        {
                            tempY = atoi(word.c_str());
                        }

                        //если предыдущее слово size: то считать size
                        if (PreviousWord == "size:")
                        {
                            tempH = atoi(word.c_str());
                        }

                        //если считаны все переменные - создать новый объект
                        if(tempID && tempX && tempY && tempH)
                        {
                            items.push_back(new gameItem(tempID, MouseX, MouseY, tempX, tempY, tempH, tempH, CameraX, CameraY, csdl_setup, &spawn));
                            break;
                        }

                        //предыдущее слово приравнять к текущему
                        PreviousWord = word;
                    }
                }

                if(CurrentType == TypeFood)
                {
                    //добаляет в поток строку из string
                    std::istringstream iss(line);

                    //переменная "предыдущее слово"
                    std::string PreviousWord;

                    //создание временных переменных
                    int tempID = 0;
                    int tempX = 0;
                    int tempY = 0;
                    int tempH = 0;

                    //пока не строка не закончилась
                    while (iss)
                    {
                        //текущее слово
                        std::string word;

                        //текущее слово вставляется из потока
                        iss >> word;

                        //если предыдущее слово ID: то считать ID
                        if (PreviousWord == "ID:")
                        {
                            tempID = atoi(word.c_str());
                        }

                        //если предыдущее слово x: то считать x
                        if (PreviousWord == "x:")
                        {
                            tempX = atoi(word.c_str());
                        }

                        //если предыдущее слово y: то считать y
                        if (PreviousWord == "y:")
                        {
                            tempY = atoi(word.c_str());
                        }

                        //если предыдущее слово size: то считать size
                        if (PreviousWord == "size:")
                        {
                            tempH = atoi(word.c_str());
                        }

                        //если считаны все переменные - создать новый объект
                        if(tempID && tempX && tempY && tempH)
                        {
                            food.push_back(new gameFood(tempID, MouseX, MouseY, tempX, tempY, tempH, tempH, CameraX, CameraY, csdl_setup, &spawn));
                            break;
                        }

                        //предыдущее слово приравнять к текущему
                        PreviousWord = word;
                    }
                }

            }
        }
    }
    else //в случае ошибки
    {
        std::cout << "File could not be open: data/Stages/Stage1.map" << std::endl;
    }

}
void CEnviroment::SaveToFile() //функция сохранения игрового уровня при изменении из игры
{
    /*
    std::ofstream LoadedFile;

    LoadedFile.open("data/Stages/Stage1.map");
    LoadedFile << "Trees.start" << std::endl;
    for (std::vector<Tree*>::iterator i = trees.begin(); i != trees.end(); ++i)
    {
        LoadedFile << "x: " << (*i)->GetX() <<" y: " << (*i)->GetY() << std::endl;
    }
    LoadedFile << "Trees.end" << std::endl;

    LoadedFile.close();
    */
    std::cout << "Stage saved!" << std::endl;
}
void CEnviroment::Update() //функция контроля переключения режимов игры
{
    TimeText->Update();
    for(int i = 0; i < 10; ++i)
        ConsoleLine[i]->Update();

    if(TimeTimer+830 < SDL_GetTicks())
    {
        //каждые 0,83 секунды
        //+1 минута
        //1200 cекунд в 20 минутах
        //1440 минут в 24 часах

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
        TimeText->SetText(tmpHours+":"+tmpMinutes);

        TimeTimer = SDL_GetTicks();
    }
    //возвращение ГГ обратно на землю


    /*
    if(coordinatesTimer+50 < SDL_GetTicks())
    {
        if((*(CameraX) - spawn.x) > 0)
        {
            *(CameraX) = spawn.x;
        }
        if((*(CameraY) - spawn.y + 10) > 0)
        {
            *(CameraY) = spawn.y - 10;
        }
        if((*(CameraX) - spawn.x ) < -(MapBlocksX*64))
        {
            *(CameraX) = -(MapBlocksX*64) + spawn.x;
        }
        if((*(CameraY) - spawn.y) < -(MapBlocksY*64))
        {
            *(CameraY) = -(MapBlocksY*64) + spawn.y;
        }
        coordinatesTimer = SDL_GetTicks();
    }


    */
    if(!consoleActive)
    {
        if (csdl_setup->GetMainEvent()->type == SDL_KEYDOWN)
        {

            if (!OnePressed && csdl_setup->GetMainEvent()->key.keysym.sym == SDLK_BACKQUOTE)
            {
                consoleActive = true;
                OnePressed = true;
            }

        }
        if (csdl_setup->GetMainEvent()->type == SDL_KEYUP)
        {

            if (OnePressed && csdl_setup->GetMainEvent()->key.keysym.sym == SDLK_BACKQUOTE)
            {

                OnePressed = false;
            }

        }
        //если текущий режим LevelCreation
        if (Mode == LevelCreation)
        {
            //если нажата клавиша
            if (csdl_setup->GetMainEvent()->type == SDL_KEYDOWN)
            {
                /*
                //если клавиша не была нажата и она - Q
                if (!OnePressed && csdl_setup->GetMainEvent()->key.keysym.sym == SDLK_q)
                {
                    //создать объект новый объект с ID = 2
                    items.push_back(new gameItem(2, MouseX, MouseY, *CameraX, *CameraY, 30, 30, CameraX, CameraY, csdl_setup, &spawn));
                    OnePressed = true;
                }
                */
            }

            //если отпущена клавиша
            if (csdl_setup->GetMainEvent()->type == SDL_KEYUP)
            {
                /*
                if (OnePressed && csdl_setup->GetMainEvent()->key.keysym.sym == SDLK_1)
                {

                    OnePressed = false;
                }
                */
            }

            //отдельный блок для переключения режимов игры и важных функций
            //если нажата клавиша
            if (csdl_setup->GetMainEvent()->type == SDL_KEYDOWN)
            {
                //если клавиша не была нажата и она - F12
                if (!OnePressed && csdl_setup->GetMainEvent()->key.keysym.sym == SDLK_F12)
                {
                    std::cout << "LevelCreation: OFF" << std::endl;

                    //переключить режим игры
                    Mode = GamePlay;
                    OnePressed = true;
                }

                //если клавиша не была нажата и она - F11
                if (!OnePressed && csdl_setup->GetMainEvent()->key.keysym.sym == SDLK_F11)
                {
                    std::cout << "Saving location..." << std::endl;

                    //сохранить игровой уровень
                    SaveToFile();
                    OnePressed = true;
                }
            }

            //если была отпущена клавиша
            if (csdl_setup->GetMainEvent()->type == SDL_KEYUP)
            {
                //F12
                if (OnePressed && csdl_setup->GetMainEvent()->key.keysym.sym == SDLK_F12)
                {
                    OnePressed = false;
                }

                //F11
                if (OnePressed && csdl_setup->GetMainEvent()->key.keysym.sym == SDLK_F11)
                {
                    OnePressed = false;
                }
            }
        }

        //если текущий режим GamePlay
        if (Mode == GamePlay)
        {
            //если нажата клавиша
            if (csdl_setup->GetMainEvent()->type == SDL_KEYDOWN)
            {
                //если клавиша не была нажата и она - F12
                if (!OnePressed && csdl_setup->GetMainEvent()->key.keysym.sym == SDLK_F12)
                {
                    std::cout << "LevelCreation: ON" << std::endl;
                    Mode = LevelCreation;
                    OnePressed = true;
                }
            }

            //если отпущена клавиша
            if (csdl_setup->GetMainEvent()->type == SDL_KEYUP)
            {
                //если клавиша была нажата и она - F12
                if (OnePressed && csdl_setup->GetMainEvent()->key.keysym.sym == SDLK_F12)
                {
                    OnePressed = false;
                }
            }
        }
    }
    else if (consoleActive)
    {
        writingInConsole();
    }

    UpdateAnimation();
}
void CEnviroment::UpdateAnimation()
{
    for (std::vector<CSprite*>::iterator i = backfont.begin(); i != backfont.end(); ++i)
    {
//        (*i)->Update();
    }
}

void CEnviroment::writingInConsole()
{
    if (csdl_setup->GetMainEvent()->type == SDL_KEYDOWN)
    {
        /*if (!OnePressed && csdl_setup->GetMainEvent()->key.keysym.sym == SDLK_DOWN)
        {
            for(int i = 9; i > 0; --i)
            {
                ConsoleLine[i]->SetText(ConsoleLine[i-1]->GetText());
            }
            ConsoleLine[0]->SetText("");
            interpretatorOfConsole(ConsoleLine[1]->GetText());
            OnePressed = true;
        }*/
        if (!OnePressed && csdl_setup->GetMainEvent()->key.keysym.sym == SDLK_RETURN)
        {
            for(int i = 9; i > 0; --i)
            {
                ConsoleLine[i]->SetText(ConsoleLine[i-1]->GetText());
            }
            ConsoleLine[0]->SetText("");
            consoleCommand = ConsoleLine[1]->GetText();
            OnePressed = true;
        }
        //если клавиша не была нажата и она - `
        if (!OnePressed && csdl_setup->GetMainEvent()->key.keysym.sym == SDLK_BACKQUOTE)
        {
            consoleActive = false;
            OnePressed = true;
        }
        if (backspaceTimer1+30<SDL_GetTicks() && csdl_setup->GetMainEvent()->key.keysym.sym == SDLK_BACKSPACE)
        {
            if(backspacePressTimer <= 0)
            {
                backspaceTimer = SDL_GetTicks();
                backspacePressTimer++;
            }
            else
            {
                backspacePressTimer = SDL_GetTicks() - backspaceTimer;
            }
            if(backspacePressTimer >= 1000)
            {
                ConsoleLine[0]->deleteLastSymbol();
            }
            backspaceTimer1 = SDL_GetTicks();
        }
        if (csdl_setup->GetMainEvent()->key.keysym.sym == SDLK_LSHIFT)
        {
            shiftActive = true;
        }
        if (!OnePressed && csdl_setup->GetMainEvent()->key.keysym.sym == SDLK_SPACE)
        {
            ConsoleLine[0]->SetText(ConsoleLine[0]->GetText()+" ");
            OnePressed = true;
        }



        if (!OnePressed && csdl_setup->GetMainEvent()->key.keysym.sym == SDLK_q)
        {
            if(!shiftActive)
                ConsoleLine[0]->SetText(ConsoleLine[0]->GetText()+"q");
            else
                ConsoleLine[0]->SetText(ConsoleLine[0]->GetText()+"Q");
            OnePressed = true;
        }
        if (!OnePressed && csdl_setup->GetMainEvent()->key.keysym.sym == SDLK_w)
        {
            if(!shiftActive)
                ConsoleLine[0]->SetText(ConsoleLine[0]->GetText()+"w");
            else
                ConsoleLine[0]->SetText(ConsoleLine[0]->GetText()+"W");
            OnePressed = true;
        }
        if (!OnePressed && csdl_setup->GetMainEvent()->key.keysym.sym == SDLK_e)
        {
            if(!shiftActive)
                ConsoleLine[0]->SetText(ConsoleLine[0]->GetText()+"e");
            else
                ConsoleLine[0]->SetText(ConsoleLine[0]->GetText()+"E");
            OnePressed = true;
        }
        if (!OnePressed && csdl_setup->GetMainEvent()->key.keysym.sym == SDLK_r)
        {
            if(!shiftActive)
                ConsoleLine[0]->SetText(ConsoleLine[0]->GetText()+"r");
            else
                ConsoleLine[0]->SetText(ConsoleLine[0]->GetText()+"R");
            OnePressed = true;
        }
        if (!OnePressed && csdl_setup->GetMainEvent()->key.keysym.sym == SDLK_t)
        {
            if(!shiftActive)
                ConsoleLine[0]->SetText(ConsoleLine[0]->GetText()+"t");
            else
                ConsoleLine[0]->SetText(ConsoleLine[0]->GetText()+"T");
            OnePressed = true;
        }
        if (!OnePressed && csdl_setup->GetMainEvent()->key.keysym.sym == SDLK_y)
        {
            if(!shiftActive)
                ConsoleLine[0]->SetText(ConsoleLine[0]->GetText()+"y");
            else
                ConsoleLine[0]->SetText(ConsoleLine[0]->GetText()+"Y");
            OnePressed = true;
        }
        if (!OnePressed && csdl_setup->GetMainEvent()->key.keysym.sym == SDLK_u)
        {
            if(!shiftActive)
                ConsoleLine[0]->SetText(ConsoleLine[0]->GetText()+"u");
            else
                ConsoleLine[0]->SetText(ConsoleLine[0]->GetText()+"U");
            OnePressed = true;
        }

        if (!OnePressed && csdl_setup->GetMainEvent()->key.keysym.sym == SDLK_i)
        {
            if(!shiftActive)
                ConsoleLine[0]->SetText(ConsoleLine[0]->GetText()+"i");
            else
                ConsoleLine[0]->SetText(ConsoleLine[0]->GetText()+"I");
            OnePressed = true;
        }
        if (!OnePressed && csdl_setup->GetMainEvent()->key.keysym.sym == SDLK_o)
        {
            if(!shiftActive)
                ConsoleLine[0]->SetText(ConsoleLine[0]->GetText()+"o");
            else
                ConsoleLine[0]->SetText(ConsoleLine[0]->GetText()+"O");
            OnePressed = true;
        }
        if (!OnePressed && csdl_setup->GetMainEvent()->key.keysym.sym == SDLK_p)
        {
            if(!shiftActive)
                ConsoleLine[0]->SetText(ConsoleLine[0]->GetText()+"p");
            else
                ConsoleLine[0]->SetText(ConsoleLine[0]->GetText()+"P");
            OnePressed = true;
        }
        if (!OnePressed && csdl_setup->GetMainEvent()->key.keysym.sym == SDLK_LEFTBRACKET)
        {
            if(!shiftActive)
                ConsoleLine[0]->SetText(ConsoleLine[0]->GetText()+"[");
            else
                ConsoleLine[0]->SetText(ConsoleLine[0]->GetText()+"{");
            OnePressed = true;
        }
        if (!OnePressed && csdl_setup->GetMainEvent()->key.keysym.sym == SDLK_RIGHTBRACKET)
        {
            if(!shiftActive)
                ConsoleLine[0]->SetText(ConsoleLine[0]->GetText()+"]");
            else
                ConsoleLine[0]->SetText(ConsoleLine[0]->GetText()+"}");
            OnePressed = true;
        }
        if (!OnePressed && csdl_setup->GetMainEvent()->key.keysym.sym == SDLK_BACKSLASH)
        {
            if(!shiftActive)
                ConsoleLine[0]->SetText(ConsoleLine[0]->GetText()+"\\");
            else
                ConsoleLine[0]->SetText(ConsoleLine[0]->GetText()+"|");
            OnePressed = true;
        }
        if (!OnePressed && csdl_setup->GetMainEvent()->key.keysym.sym == SDLK_a)
        {
            if(!shiftActive)
                ConsoleLine[0]->SetText(ConsoleLine[0]->GetText()+"a");
            else
                ConsoleLine[0]->SetText(ConsoleLine[0]->GetText()+"A");
            OnePressed = true;
        }
        if (!OnePressed && csdl_setup->GetMainEvent()->key.keysym.sym == SDLK_s)
        {
            if(!shiftActive)
                ConsoleLine[0]->SetText(ConsoleLine[0]->GetText()+"s");
            else
                ConsoleLine[0]->SetText(ConsoleLine[0]->GetText()+"S");
            OnePressed = true;
        }
        if (!OnePressed && csdl_setup->GetMainEvent()->key.keysym.sym == SDLK_d)
        {
            if(!shiftActive)
                ConsoleLine[0]->SetText(ConsoleLine[0]->GetText()+"d");
            else
                ConsoleLine[0]->SetText(ConsoleLine[0]->GetText()+"D");
            OnePressed = true;
        }
        if (!OnePressed && csdl_setup->GetMainEvent()->key.keysym.sym == SDLK_f)
        {
            if(!shiftActive)
                ConsoleLine[0]->SetText(ConsoleLine[0]->GetText()+"f");
            else
                ConsoleLine[0]->SetText(ConsoleLine[0]->GetText()+"F");
            OnePressed = true;
        }
        if (!OnePressed && csdl_setup->GetMainEvent()->key.keysym.sym == SDLK_g)
        {
            if(!shiftActive)
                ConsoleLine[0]->SetText(ConsoleLine[0]->GetText()+"g");
            else
                ConsoleLine[0]->SetText(ConsoleLine[0]->GetText()+"G");
            OnePressed = true;
        }
        if (!OnePressed && csdl_setup->GetMainEvent()->key.keysym.sym == SDLK_h)
        {
            if(!shiftActive)
                ConsoleLine[0]->SetText(ConsoleLine[0]->GetText()+"h");
            else
                ConsoleLine[0]->SetText(ConsoleLine[0]->GetText()+"H");
            OnePressed = true;
        }
        if (!OnePressed && csdl_setup->GetMainEvent()->key.keysym.sym == SDLK_j)
        {
            if(!shiftActive)
                ConsoleLine[0]->SetText(ConsoleLine[0]->GetText()+"j");
            else
                ConsoleLine[0]->SetText(ConsoleLine[0]->GetText()+"J");
            OnePressed = true;
        }
        if (!OnePressed && csdl_setup->GetMainEvent()->key.keysym.sym == SDLK_k)
        {
            if(!shiftActive)
                ConsoleLine[0]->SetText(ConsoleLine[0]->GetText()+"k");
            else
                ConsoleLine[0]->SetText(ConsoleLine[0]->GetText()+"K");
            OnePressed = true;
        }
        if (!OnePressed && csdl_setup->GetMainEvent()->key.keysym.sym == SDLK_l)
        {
           if(!shiftActive)
                ConsoleLine[0]->SetText(ConsoleLine[0]->GetText()+"l");
            else
                ConsoleLine[0]->SetText(ConsoleLine[0]->GetText()+"L");
            OnePressed = true;
        }
        if (!OnePressed && csdl_setup->GetMainEvent()->key.keysym.sym == SDLK_KP_COLON)
        {
            if(!shiftActive)
                ConsoleLine[0]->SetText(ConsoleLine[0]->GetText()+";");
            else
                ConsoleLine[0]->SetText(ConsoleLine[0]->GetText()+":");
            OnePressed = true;
        }
        if (!OnePressed && csdl_setup->GetMainEvent()->key.keysym.sym == SDLK_QUOTE)
        {
            if(!shiftActive)
                ConsoleLine[0]->SetText(ConsoleLine[0]->GetText()+"\'");
            else
                ConsoleLine[0]->SetText(ConsoleLine[0]->GetText()+"\"");
            OnePressed = true;
        }
        if (!OnePressed && csdl_setup->GetMainEvent()->key.keysym.sym == SDLK_z)
        {
            if(!shiftActive)
                ConsoleLine[0]->SetText(ConsoleLine[0]->GetText()+"z");
            else
                ConsoleLine[0]->SetText(ConsoleLine[0]->GetText()+"Z");
            OnePressed = true;
        }
        if (!OnePressed && csdl_setup->GetMainEvent()->key.keysym.sym == SDLK_x)
        {
            if(!shiftActive)
                ConsoleLine[0]->SetText(ConsoleLine[0]->GetText()+"x");
            else
                ConsoleLine[0]->SetText(ConsoleLine[0]->GetText()+"X");
            OnePressed = true;
        }
        if (!OnePressed && csdl_setup->GetMainEvent()->key.keysym.sym == SDLK_c)
        {
            if(!shiftActive)
                ConsoleLine[0]->SetText(ConsoleLine[0]->GetText()+"c");
            else
                ConsoleLine[0]->SetText(ConsoleLine[0]->GetText()+"C");
            OnePressed = true;
        }
        if (!OnePressed && csdl_setup->GetMainEvent()->key.keysym.sym == SDLK_v)
        {
            if(!shiftActive)
                ConsoleLine[0]->SetText(ConsoleLine[0]->GetText()+"v");
            else
                ConsoleLine[0]->SetText(ConsoleLine[0]->GetText()+"V");
            OnePressed = true;
        }
        if (!OnePressed && csdl_setup->GetMainEvent()->key.keysym.sym == SDLK_b)
        {
            if(!shiftActive)
                ConsoleLine[0]->SetText(ConsoleLine[0]->GetText()+"b");
            else
                ConsoleLine[0]->SetText(ConsoleLine[0]->GetText()+"B");
            OnePressed = true;
        }
        if (!OnePressed && csdl_setup->GetMainEvent()->key.keysym.sym == SDLK_n)
        {
            if(!shiftActive)
                ConsoleLine[0]->SetText(ConsoleLine[0]->GetText()+"n");
            else
                ConsoleLine[0]->SetText(ConsoleLine[0]->GetText()+"N");
            OnePressed = true;
        }
        if (!OnePressed && csdl_setup->GetMainEvent()->key.keysym.sym == SDLK_m)
        {
            if(!shiftActive)
                ConsoleLine[0]->SetText(ConsoleLine[0]->GetText()+"m");
            else
                ConsoleLine[0]->SetText(ConsoleLine[0]->GetText()+"M");
            OnePressed = true;
        }
        if (!OnePressed && csdl_setup->GetMainEvent()->key.keysym.sym == SDLK_BACKSLASH)
        {
            if(!shiftActive)
                ConsoleLine[0]->SetText(ConsoleLine[0]->GetText()+",");
            else
                ConsoleLine[0]->SetText(ConsoleLine[0]->GetText()+"<");
            OnePressed = true;
        }
        if (!OnePressed && csdl_setup->GetMainEvent()->key.keysym.sym == SDLK_KP_PERIOD)
        {
            if(!shiftActive)
                ConsoleLine[0]->SetText(ConsoleLine[0]->GetText()+".");
            else
                ConsoleLine[0]->SetText(ConsoleLine[0]->GetText()+">");
            OnePressed = true;
        }
        if (!OnePressed && csdl_setup->GetMainEvent()->key.keysym.sym == SDLK_SLASH)
        {
            if(!shiftActive)
                ConsoleLine[0]->SetText(ConsoleLine[0]->GetText()+"/");
            else
                ConsoleLine[0]->SetText(ConsoleLine[0]->GetText()+"?");
            OnePressed = true;
        }
        if (!OnePressed && csdl_setup->GetMainEvent()->key.keysym.sym == SDLK_1)
        {
            if(!shiftActive)
                ConsoleLine[0]->SetText(ConsoleLine[0]->GetText()+"1");
            else
                ConsoleLine[0]->SetText(ConsoleLine[0]->GetText()+"!");
            OnePressed = true;
        }
        if (!OnePressed && csdl_setup->GetMainEvent()->key.keysym.sym == SDLK_2)
        {
            if(!shiftActive)
                ConsoleLine[0]->SetText(ConsoleLine[0]->GetText()+"2");
            else
                ConsoleLine[0]->SetText(ConsoleLine[0]->GetText()+"@");
            OnePressed = true;
        }
        if (!OnePressed && csdl_setup->GetMainEvent()->key.keysym.sym == SDLK_3)
        {
            if(!shiftActive)
                ConsoleLine[0]->SetText(ConsoleLine[0]->GetText()+"3");
            else
                ConsoleLine[0]->SetText(ConsoleLine[0]->GetText()+"#");
            OnePressed = true;
        }
        if (!OnePressed && csdl_setup->GetMainEvent()->key.keysym.sym == SDLK_4)
        {
            if(!shiftActive)
                ConsoleLine[0]->SetText(ConsoleLine[0]->GetText()+"4");
            else
                ConsoleLine[0]->SetText(ConsoleLine[0]->GetText()+"$");
            OnePressed = true;
        }
        if (!OnePressed && csdl_setup->GetMainEvent()->key.keysym.sym == SDLK_5)
        {
            if(!shiftActive)
                ConsoleLine[0]->SetText(ConsoleLine[0]->GetText()+"5");
            else
                ConsoleLine[0]->SetText(ConsoleLine[0]->GetText()+"%");
            OnePressed = true;
        }
        if (!OnePressed && csdl_setup->GetMainEvent()->key.keysym.sym == SDLK_6)
        {
            if(!shiftActive)
                ConsoleLine[0]->SetText(ConsoleLine[0]->GetText()+"6");
            else
                ConsoleLine[0]->SetText(ConsoleLine[0]->GetText()+"^");
            OnePressed = true;
        }
        if (!OnePressed && csdl_setup->GetMainEvent()->key.keysym.sym == SDLK_7)
        {
            if(!shiftActive)
                ConsoleLine[0]->SetText(ConsoleLine[0]->GetText()+"7");
            else
                ConsoleLine[0]->SetText(ConsoleLine[0]->GetText()+"&");
            OnePressed = true;
        }
        if (!OnePressed && csdl_setup->GetMainEvent()->key.keysym.sym == SDLK_8)
        {
            if(!shiftActive)
                ConsoleLine[0]->SetText(ConsoleLine[0]->GetText()+"8");
            else
                ConsoleLine[0]->SetText(ConsoleLine[0]->GetText()+"*");
            OnePressed = true;
        }
        if (!OnePressed && csdl_setup->GetMainEvent()->key.keysym.sym == SDLK_9)
        {
            if(!shiftActive)
                ConsoleLine[0]->SetText(ConsoleLine[0]->GetText()+"9");
            else
                ConsoleLine[0]->SetText(ConsoleLine[0]->GetText()+"(");
            OnePressed = true;
        }
        if (!OnePressed && csdl_setup->GetMainEvent()->key.keysym.sym == SDLK_0)
        {
            if(!shiftActive)
                ConsoleLine[0]->SetText(ConsoleLine[0]->GetText()+"0");
            else
                ConsoleLine[0]->SetText(ConsoleLine[0]->GetText()+")");
            OnePressed = true;
        }
        if (!OnePressed && csdl_setup->GetMainEvent()->key.keysym.sym == SDLK_MINUS)
        {
            if(!shiftActive)
                ConsoleLine[0]->SetText(ConsoleLine[0]->GetText()+"-");
            else
                ConsoleLine[0]->SetText(ConsoleLine[0]->GetText()+"_");
            OnePressed = true;
        }
        if (!OnePressed && csdl_setup->GetMainEvent()->key.keysym.sym == SDLK_EQUALS)
        {
            if(!shiftActive)
                ConsoleLine[0]->SetText(ConsoleLine[0]->GetText()+"=");
            else
                ConsoleLine[0]->SetText(ConsoleLine[0]->GetText()+"+");
            OnePressed = true;
        }
    }
    if (csdl_setup->GetMainEvent()->type == SDL_KEYUP)
    {

        if (OnePressed && csdl_setup->GetMainEvent()->key.keysym.sym == SDLK_RETURN)
        {
            OnePressed = false;
        }
        if (OnePressed && csdl_setup->GetMainEvent()->key.keysym.sym == SDLK_BACKQUOTE)
        {
            OnePressed = false;
        }
        if (csdl_setup->GetMainEvent()->key.keysym.sym == SDLK_BACKSPACE)
        {
            if(backspacePressTimer > 5 && backspacePressTimer < 900)
            {
                ConsoleLine[0]->deleteLastSymbol();
            }
            backspacePressTimer = 0;
        }
        if (csdl_setup->GetMainEvent()->key.keysym.sym == SDLK_LSHIFT)
        {
            shiftActive = false;
        }
        if (OnePressed && csdl_setup->GetMainEvent()->key.keysym.sym == SDLK_SPACE)
        {
            OnePressed = false;
        }
        if (OnePressed && csdl_setup->GetMainEvent()->key.keysym.sym == SDLK_q)
        {
            OnePressed = false;
        }
        if (OnePressed && csdl_setup->GetMainEvent()->key.keysym.sym == SDLK_w)
        {
            OnePressed = false;
        }
        if (OnePressed && csdl_setup->GetMainEvent()->key.keysym.sym == SDLK_e)
        {
            OnePressed = false;
        }
        if (OnePressed && csdl_setup->GetMainEvent()->key.keysym.sym == SDLK_r)
        {
            OnePressed = false;
        }
        if (OnePressed && csdl_setup->GetMainEvent()->key.keysym.sym == SDLK_t)
        {
            OnePressed = false;
        }
        if (OnePressed && csdl_setup->GetMainEvent()->key.keysym.sym == SDLK_y)
        {
            OnePressed = false;
        }
        if (OnePressed && csdl_setup->GetMainEvent()->key.keysym.sym == SDLK_u)
        {
            OnePressed = false;
        }

        if (OnePressed && csdl_setup->GetMainEvent()->key.keysym.sym == SDLK_i)
        {
            OnePressed = false;
        }
        if (OnePressed && csdl_setup->GetMainEvent()->key.keysym.sym == SDLK_o)
        {
            OnePressed = false;
        }
        if (OnePressed && csdl_setup->GetMainEvent()->key.keysym.sym == SDLK_p)
        {
            OnePressed = false;
        }
        if (OnePressed && csdl_setup->GetMainEvent()->key.keysym.sym == SDLK_LEFTBRACKET)
        {
            OnePressed = false;
        }
        if (OnePressed && csdl_setup->GetMainEvent()->key.keysym.sym == SDLK_RIGHTBRACKET)
        {
            OnePressed = false;
        }
        if (OnePressed && csdl_setup->GetMainEvent()->key.keysym.sym == SDLK_BACKSLASH)
        {
            OnePressed = false;
        }
        if (OnePressed && csdl_setup->GetMainEvent()->key.keysym.sym == SDLK_a)
        {
            OnePressed = false;
        }
        if (OnePressed && csdl_setup->GetMainEvent()->key.keysym.sym == SDLK_s)
        {
            OnePressed = false;
        }
        if (OnePressed && csdl_setup->GetMainEvent()->key.keysym.sym == SDLK_d)
        {
            OnePressed = false;
        }
        if (OnePressed && csdl_setup->GetMainEvent()->key.keysym.sym == SDLK_f)
        {
            OnePressed = false;
        }
        if (OnePressed && csdl_setup->GetMainEvent()->key.keysym.sym == SDLK_g)
        {
            OnePressed = false;
        }
        if (OnePressed && csdl_setup->GetMainEvent()->key.keysym.sym == SDLK_h)
        {
            OnePressed = false;
        }
        if (OnePressed && csdl_setup->GetMainEvent()->key.keysym.sym == SDLK_j)
        {
            OnePressed = false;
        }
        if (OnePressed && csdl_setup->GetMainEvent()->key.keysym.sym == SDLK_k)
        {
            OnePressed = false;
        }
        if (OnePressed && csdl_setup->GetMainEvent()->key.keysym.sym == SDLK_l)
        {
            OnePressed = false;
        }
        if (OnePressed && csdl_setup->GetMainEvent()->key.keysym.sym == SDLK_KP_COLON)
        {
            OnePressed = false;
        }
        if (OnePressed && csdl_setup->GetMainEvent()->key.keysym.sym == SDLK_QUOTE)
        {
            OnePressed = false;
        }
        if (OnePressed && csdl_setup->GetMainEvent()->key.keysym.sym == SDLK_z)
        {
            OnePressed = false;
        }
        if (OnePressed && csdl_setup->GetMainEvent()->key.keysym.sym == SDLK_x)
        {
            OnePressed = false;
        }
        if (OnePressed && csdl_setup->GetMainEvent()->key.keysym.sym == SDLK_c)
        {
            OnePressed = false;
        }
        if (OnePressed && csdl_setup->GetMainEvent()->key.keysym.sym == SDLK_v)
        {
            OnePressed = false;
        }
        if (OnePressed && csdl_setup->GetMainEvent()->key.keysym.sym == SDLK_b)
        {
            OnePressed = false;
        }
        if (OnePressed && csdl_setup->GetMainEvent()->key.keysym.sym == SDLK_n)
        {
            OnePressed = false;
        }
        if (OnePressed && csdl_setup->GetMainEvent()->key.keysym.sym == SDLK_m)
        {
            OnePressed = false;
        }
        if (OnePressed && csdl_setup->GetMainEvent()->key.keysym.sym == SDLK_BACKSLASH)
        {
            OnePressed = false;
        }
        if (OnePressed && csdl_setup->GetMainEvent()->key.keysym.sym == SDLK_KP_PERIOD)
        {
            OnePressed = false;
        }
        if (OnePressed && csdl_setup->GetMainEvent()->key.keysym.sym == SDLK_SLASH)
        {
            OnePressed = false;
        }
        if (OnePressed && csdl_setup->GetMainEvent()->key.keysym.sym == SDLK_1)
        {
            OnePressed = false;
        }
        if (OnePressed && csdl_setup->GetMainEvent()->key.keysym.sym == SDLK_2)
        {
            OnePressed = false;
        }
        if (OnePressed && csdl_setup->GetMainEvent()->key.keysym.sym == SDLK_3)
        {
            OnePressed = false;
        }
        if (OnePressed && csdl_setup->GetMainEvent()->key.keysym.sym == SDLK_4)
        {
            OnePressed = false;
        }
        if (OnePressed && csdl_setup->GetMainEvent()->key.keysym.sym == SDLK_5)
        {
            OnePressed = false;
        }
        if (OnePressed && csdl_setup->GetMainEvent()->key.keysym.sym == SDLK_6)
        {
            OnePressed = false;
        }
        if (OnePressed && csdl_setup->GetMainEvent()->key.keysym.sym == SDLK_7)
        {
            OnePressed = false;
        }
        if (OnePressed && csdl_setup->GetMainEvent()->key.keysym.sym == SDLK_8)
        {
            OnePressed = false;
        }
        if (OnePressed && csdl_setup->GetMainEvent()->key.keysym.sym == SDLK_9)
        {
            OnePressed = false;
        }
        if (OnePressed && csdl_setup->GetMainEvent()->key.keysym.sym == SDLK_0)
        {
            OnePressed = false;
        }
        if (OnePressed && csdl_setup->GetMainEvent()->key.keysym.sym == SDLK_MINUS)
        {
            OnePressed = false;
        }
        if (OnePressed && csdl_setup->GetMainEvent()->key.keysym.sym == SDLK_EQUALS)
        {
            OnePressed = false;
        }
    }
}
