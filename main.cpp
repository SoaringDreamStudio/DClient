#include "libraries.h"
#include "Main.h"

extern std::string login;
CMain::CMain(int passed_ScreenWidth, int passed_ScreenHeight, net::Socket* passed_gsocket)
{
    gsocket = passed_gsocket;
	ScreenWidth = passed_ScreenWidth;
	ScreenHeight = passed_ScreenHeight;
	quit = false;
	Mquit = false;

	csdl_setup = new CSDL_Setup(&quit, ScreenWidth, ScreenHeight);

    CameraX = 0;
	CameraY = 0;

    //CameraX = (csdl_setup->GetScreenWidth()/2)-(tmpW/2);
	//CameraY = (csdl_setup->GetScreenHeight()/2)-tmpH;

	MouseX = 0;
	MouseY = 0;
	ignoreGameOver = false;

    updateTimer = SDL_GetTicks();

    timerSend = SDL_GetTicks();

}


CMain::~CMain(void)
{
	delete csdl_setup;
	//delete MainHero;
}

int CMain::GameLoop(void)
{


    //инициализируем процесс загрузки
    LoadingProcess* loadingProcess = new LoadingProcess(csdl_setup, &MouseX, &MouseY, &CameraX, &CameraY);
    DrawLoadingProcess(3.3, loadingProcess);

    //инициализируем положение камеры
    CameraX = 0;
    CameraY = 0;
    DrawLoadingProcess(3.3, loadingProcess);

    //инициализируем положение мыши и игровой уровень
    SDL_GetMouseState(&MouseX, &MouseY);
    gameLVL = new GameLVL(&CameraX, &CameraY, &MouseX, &MouseY,  csdl_setup, loadingProcess);
    DrawLoadingProcess(3.4, loadingProcess);

    //инициализируем игровой интерфейс
    GameInterface* gameInterface = new GameInterface(csdl_setup, &MouseX, &MouseY, &CameraX, &CameraY);
    DrawLoadingProcess(9, loadingProcess);

    for(;;)
    {
        gsocket->Update();
        net::Address sender;
        unsigned char buffer[256];
        int bytes_read = gsocket->Receive( sender, buffer, sizeof( buffer ) );
        if ( bytes_read )
        {
            if(buffer[0] >= 200)
            {
                std::cout << "Error #" << int(buffer[0]) << std::endl;
                break;
            }

            else if(buffer[0] == 21)
            {
                unsigned int Size = (unsigned int)(buffer[5] << 24) + (unsigned int)(buffer[6]<< 16) + (unsigned int)(buffer[7] << 8) + buffer[8];
                //std::cout << Size << std::endl;
                bool fragments[Size];
                for(int i = 0; i < Size;i++)
                {

                    fragments[i] = false;
                }
                while( !allTrue(fragments, Size))
                {
                    gsocket->Update();
                    unsigned char buffer[256];
                    int bytes_read = gsocket->Receive( sender, buffer, sizeof( buffer ) );

                    if(buffer[4] == 22)
                    {
                        unsigned int Number = (unsigned int)(buffer[5] << 24) + (unsigned int)(buffer[6]<< 16) + (unsigned int)(buffer[7] << 8) + buffer[8];
                        //std::cout << Number << std::endl;
                        fragments[Number] = true;
                        unsigned int ID = (unsigned int)(buffer[9] << 24) + (unsigned int)(buffer[10]<< 16) + (unsigned int)(buffer[11] << 8) + buffer[12];
                        //std::cout << ID << std::endl;
                        unsigned int X = (unsigned int)(buffer[13] << 24) + (unsigned int)(buffer[14]<< 16) + (unsigned int)(buffer[15] << 8) + buffer[16];
                        //std::cout << X << std::endl;
                        unsigned int Y = (unsigned int)(buffer[17] << 24) + (unsigned int)(buffer[18]<< 16) + (unsigned int)(buffer[19] << 8) + buffer[20];
                        //std::cout << Y << std::endl;

                        gameLVL->CreateGround(ID,X,Y);
                        std::cout << "created Ground" << std::endl;
                    }

                }
                //создать массив булевых переменных для проверки дохождения пакетов
                //break;

            }
            else if(buffer[0] == 23)
            {
                unsigned int Size = (unsigned int)(buffer[5] << 24) + (unsigned int)(buffer[6]<< 16) + (unsigned int)(buffer[7] << 8) + buffer[8];
                std::cout << Size << std::endl;
                bool fragments[Size];
                for(int i = 0; i < Size;i++)
                {

                    fragments[i] = false;
                }
                while( !allTrue(fragments, Size))
                {
                    gsocket->Update();
                    unsigned char buffer[256];
                    int bytes_read = gsocket->Receive( sender, buffer, sizeof( buffer ) );

                    if(buffer[4] == 24)
                    {
                        unsigned int Number = (unsigned int)(buffer[5] << 24) + (unsigned int)(buffer[6]<< 16) + (unsigned int)(buffer[7] << 8) + buffer[8];
                        std::cout << Number << std::endl;
                        fragments[Number] = true;
                        unsigned int ID = (unsigned int)(buffer[9] << 24) + (unsigned int)(buffer[10]<< 16) + (unsigned int)(buffer[11] << 8) + buffer[12];
                        //std::cout << ID << std::endl;
                        unsigned int X = (unsigned int)(buffer[13] << 24) + (unsigned int)(buffer[14]<< 16) + (unsigned int)(buffer[15] << 8) + buffer[16];
                        //std::cout << X << std::endl;
                        unsigned int Y = (unsigned int)(buffer[17] << 24) + (unsigned int)(buffer[18]<< 16) + (unsigned int)(buffer[19] << 8) + buffer[20];
                        //std::cout << Y << std::endl;

                        std::string Nickname;
                        for(int i = 21; i <=28; i++)
                        {
                            if(buffer[i] == 0)
                                break;
                            Nickname += buffer[i];
                        }
                        std::cout << Nickname << std::endl;
                        std::cout << login << std::endl;
                        std::cout << (Nickname == login) << std::endl;
                        if(Nickname == login)
                        {
                            //std::cout << "CameraX: " << CameraX << std::endl;
                            gameLVL->setSpawnX(X);
                            //std::cout << "CameraX: " << CameraX << std::endl;
                            //std::cout << "CameraY: " << CameraY << std::endl;
                            gameLVL->setSpawnY(Y);
                            //std::cout << "CameraY: " << CameraY << std::endl;
                            break;
                        }
                        //std::cout << Nickname << std::endl;

                        bool existNickname;
                        std::vector<Characters*> tmpCharacters = gameLVL->GetCharacters();
                        int l=0;
                        for(std::vector<Characters*>::iterator it = tmpCharacters.begin(); it != tmpCharacters.end(); ++it,++l)
                        {
                            if((*it)->getNickName() == Nickname)
                            {
                                existNickname = true;
                                gameLVL->GetCharacters()[l]->changeXY(X,Y);
                            }
                        }

                        if(!existNickname)
                        {
                            std::cout << "Creating: " << Nickname << std::endl;
                            gameLVL->CreateCharacter(ID,X,Y,Nickname);
                        }

                    }
                }
                //создать массив булевых переменных для проверки дохождения пакетов
                break;

            }
            else
            {

                break;
            }
        }
    }
    //инициализируем главного героя
    MainHero = new MainCharacter(login, csdl_setup, &MouseX, &MouseY, &CameraX, &CameraY, gameLVL, loadingProcess, gameInterface);
    DrawLoadingProcess(4, loadingProcess);

    //interpretator = new CInterpretator(gameLVL, MainHero);
    DrawLoadingProcess(4, loadingProcess);

    //удаляем процесс загрузки
    delete loadingProcess;

    //основной процесс игры
    //Выполняется до тех пор пока переменная quit ложна и не был нажат крестик
	while(!quit && csdl_setup->GetMainEvent()->type != SDL_QUIT)
	{
	    //очищаем окно и проверяем на события
		csdl_setup->Begin();



        net::Address sender;
		for(;;)
        {
            gsocket->Update();
            unsigned char buffer[256];
            int bytes_read = gsocket->Receive( sender, buffer, sizeof( buffer ) );
            if ( bytes_read )
            {
                if(buffer[0] >= 200 && buffer[0] <=220)
                {
                    std::cout << "Error #" << int(buffer[0]) << std::endl;
                    //quit = true;
                    break;
                }

                else if(buffer[0] == 23)
                {
                    unsigned int Size = (unsigned int)(buffer[1] << 24) + (unsigned int)(buffer[2]<< 16) + (unsigned int)(buffer[3] << 8) + buffer[4];
                    //std::cout << Size << std::endl;
                    bool fragments[Size];
                    for(int i = 0; i < Size;i++)
                    {

                        fragments[i] = false;
                    }
                    while( !allTrue(fragments, Size))
                    {
                        gsocket->Update();
                        unsigned char buffer[256];
                        int bytes_read = gsocket->Receive( sender, buffer, sizeof( buffer ) );

                        if(buffer[0] == 24)
                        {
                            unsigned int Number = (unsigned int)(buffer[1] << 24) + (unsigned int)(buffer[2]<< 16) + (unsigned int)(buffer[3] << 8) + buffer[4];
                            //std::cout << Number << std::endl;
                            fragments[Number] = true;
                            unsigned int ID = (unsigned int)(buffer[5] << 24) + (unsigned int)(buffer[6]<< 16) + (unsigned int)(buffer[7] << 8) + buffer[8];
                            //std::cout << ID << std::endl;
                            unsigned int X = (unsigned int)(buffer[9] << 24) + (unsigned int)(buffer[10]<< 16) + (unsigned int)(buffer[11] << 8) + buffer[12];
                            //std::cout << X << std::endl;
                            unsigned int Y = (unsigned int)(buffer[13] << 24) + (unsigned int)(buffer[14]<< 16) + (unsigned int)(buffer[15] << 8) + buffer[16];
                            //std::cout << Y << std::endl;
                            std::string Nickname;

                            for(int i = 17; i <=24; i++)
                            {
                                if(buffer[i] == 0)
                                    break;
                                Nickname += buffer[i];
                            }

                            if(Nickname == login)
                                break;
                            //std::cout << Nickname << std::endl;

                            bool existNickname;
                            std::vector<Characters*> tmpCharacters = gameLVL->GetCharacters();
                            int l=0;
                            for(std::vector<Characters*>::iterator it = tmpCharacters.begin(); it != tmpCharacters.end(); ++it,++l)
                            {
                                if((*it)->getNickName() == Nickname)
                                {
                                    existNickname = true;
                                    gameLVL->GetCharacters()[l]->changeXY(X,Y);
                                }
                            }
                            if(!existNickname)
                            {
                                std::cout << "Creating1: " << Nickname << std::endl;
                                gameLVL->CreateCharacter(ID,X,Y,Nickname);
                            }

                        }
                    }
                    //создать массив булевых переменных для проверки дохождения пакетов
                    break;

                }
                else
                    break;
            }
        }



        //считываем положение мышки
		SDL_GetMouseState(&MouseX, &MouseY);

        //проверка на режим игры и считывание клавиш для переключения режимов
        gameLVL->Update();

        //interpretator->command(gameLVL->GetConsoleCommand());
        //gameLVL->SetConsoleCommand("");

        //отрисовка заднего плана
        gameLVL->DrawBack();

        //отрисовка главного героя
        MainHero->Draw();

        //обновление анимации и управление ГГ
        MainHero->Update();

        //отрисовка переднего плана
        gameLVL->DrawFront();

        //просчет и прорисовка для игрового интерфейса
        gameInterface->Update();

        gameInterface->Draw();

        //отрисовка рендера
		csdl_setup->End();


/*
		unsigned char data2[5];
        data2[0] = 23;
        data2[1] = (unsigned char) ( (gameLVL->GetCharacters().size()+1) >> 24 );
        data2[2] = (unsigned char) ( (gameLVL->GetCharacters().size()+1) >> 16 );
        data2[3] = (unsigned char) ( (gameLVL->GetCharacters().size()+1) >> 8 );
        data2[4] = (unsigned char) ( (gameLVL->GetCharacters().size()+1) );

        unsigned char packet[sizeof(data2)+4];
        packet[0] = (unsigned char) ( ProtocolId >> 24 );
        packet[1] = (unsigned char) ( ( ProtocolId >> 16 ) & 0xFF );
        packet[2] = (unsigned char) ( ( ProtocolId >> 8 ) & 0xFF );
        packet[3] = (unsigned char) ( ( ProtocolId ) & 0xFF );
        memcpy( &packet[4], data2, sizeof(data2) );

        gsocket->Send(sender,
                        packet,
                        sizeof(packet) );


        for(int i = 0; i < gameLVL->GetCharacters().size(); i++)
        {
            unsigned char data[25];
            data[0] = 24;

            //NumberOfPacket
            data[1] = (unsigned char) ( i+1 >> 24 );
            data[2] = (unsigned char) ( i+1 >> 16 );
            data[3] = (unsigned char) ( i+1 >> 8 );
            data[4] = (unsigned char) ( i+1 );

            //ID
            data[5] = (unsigned char) ( gameLVL->GetCharacters()[i]->getID() >> 24 );
            data[6] = (unsigned char) ( gameLVL->GetCharacters()[i]->getID() >> 16 );
            data[7] = (unsigned char) ( gameLVL->GetCharacters()[i]->getID() >> 8 );
            data[8] = (unsigned char) ( gameLVL->GetCharacters()[i]->getID() );

            //X
            data[9] = (unsigned char) ( gameLVL->GetCharacters()[i]->getX() >> 24 );
            data[10] = (unsigned char) ( gameLVL->GetCharacters()[i]->getX() >> 16 );
            data[11] = (unsigned char) ( gameLVL->GetCharacters()[i]->getX() >> 8 );
            data[12] = (unsigned char) ( gameLVL->GetCharacters()[i]->getX() );

            //Y
            data[13] = (unsigned char) ( gameLVL->GetCharacters()[i]->getY() >> 24 );
            data[14] = (unsigned char) ( gameLVL->GetCharacters()[i]->getY() >> 16 );
            data[15] = (unsigned char) ( gameLVL->GetCharacters()[i]->getY() >> 8 );
            data[16] = (unsigned char) ( gameLVL->GetCharacters()[i]->getY() );

            //NickName
            data[17] = (unsigned char) ( gameLVL->GetCharacters()[i]->getNickName()[0]);
            data[18] = (unsigned char) ( gameLVL->GetCharacters()[i]->getNickName()[1]);
            data[19] = (unsigned char) ( gameLVL->GetCharacters()[i]->getNickName()[2]);
            data[20] = (unsigned char) ( gameLVL->GetCharacters()[i]->getNickName()[3]);
            data[21] = (unsigned char) ( gameLVL->GetCharacters()[i]->getNickName()[4]);
            data[22] = (unsigned char) ( gameLVL->GetCharacters()[i]->getNickName()[5]);
            data[23] = (unsigned char) ( gameLVL->GetCharacters()[i]->getNickName()[6]);
            data[24] = (unsigned char) ( gameLVL->GetCharacters()[i]->getNickName()[7]);

            unsigned char packet[sizeof(data)+4];
            packet[0] = (unsigned char) ( ProtocolId >> 24 );
            packet[1] = (unsigned char) ( ( ProtocolId >> 16 ) & 0xFF );
            packet[2] = (unsigned char) ( ( ProtocolId >> 8 ) & 0xFF );
            packet[3] = (unsigned char) ( ( ProtocolId ) & 0xFF );
            memcpy( &packet[4], data, sizeof(data) );

            gsocket->Send(sender,
                            packet,
                            sizeof(packet) );
        }
        //mainCharacter*/
        if(timerSend+33 < SDL_GetTicks())
        {
            unsigned char data[25];
            data[0] = 24;
            //NumberOfPacket
            data[1] = (unsigned char) ( 0 );
            data[2] = (unsigned char) ( 0 );
            data[3] = (unsigned char) ( 0 );
            data[4] = (unsigned char) ( 0 );
            //ID
            data[5] = (unsigned char) ( 0 );//gameLVL->GetCharacters()[i]->getID() >> 24 );
            data[6] = (unsigned char) ( 0 );//gameLVL->GetCharacters()[i]->getID() >> 16 );
            data[7] = (unsigned char) ( 0 );//gameLVL->GetCharacters()[i]->getID() >> 8 );
            data[8] = (unsigned char) ( 1 );//gameLVL->GetCharacters()[i]->getID() );

            //X
            data[9] = (unsigned char) ( int(gameLVL->getSpawn().x-CameraX) >> 24 );
            data[10] = (unsigned char) ( int(gameLVL->getSpawn().x-CameraX) >> 16 );
            data[11] = (unsigned char) ( int(gameLVL->getSpawn().x-CameraX) >> 8 );
            data[12] = (unsigned char) ( int(gameLVL->getSpawn().x-CameraX) );

            //Y
            data[13] = (unsigned char) ( int(gameLVL->getSpawn().y-CameraY) >> 24 );
            data[14] = (unsigned char) ( int(gameLVL->getSpawn().y-CameraY) >> 16 );
            data[15] = (unsigned char) ( int(gameLVL->getSpawn().y-CameraY) >> 8 );
            data[16] = (unsigned char) ( int(gameLVL->getSpawn().y-CameraY) );

            //NickName
            data[17] = (unsigned char) ( MainHero->getNickName()[0]);
            data[18] = (unsigned char) ( MainHero->getNickName()[1]);
            data[19] = (unsigned char) ( MainHero->getNickName()[2]);
            data[20] = (unsigned char) ( MainHero->getNickName()[3]);
            data[21] = (unsigned char) ( MainHero->getNickName()[4]);
            data[22] = (unsigned char) ( MainHero->getNickName()[5]);
            data[23] = (unsigned char) ( MainHero->getNickName()[6]);
            data[24] = (unsigned char) ( MainHero->getNickName()[7]);


            for(std::map<unsigned int, net::Connection*>::iterator it = gsocket->getConnections().begin(); it != gsocket->getConnections().end(); ++it)
            {
                it->second->Send(data, 25 );
            }
            timerSend = SDL_GetTicks();
        }

		//в случае, если здоровье ГГ упадет до 0 - удалить его и выйти из цикла
		/*
		if(*(MainHero->GetHP()) <= 0)
        {
            delete MainHero;
            break;
        }*/
        if(gameInterface->getMquit())
        {
            ignoreGameOver = true;
            break;
        }
	}
	return 0;
}
void CMain::GameMenu(void)
{
    //инициализация главного меню
    MainMenu* mainMenu = new MainMenu(csdl_setup, &MouseX, &MouseY, &CameraX, &CameraY, gsocket);
    //CSprite* menu1 = new CSprite(csdl_setup->GetRenderer(), "data/img/menu1.png", 100, 0, 800, 600, &CameraX, &CameraY, CCollisionRectangle());
    //CSprite* menuButton1 = new CSprite(csdl_setup->GetRenderer(), "data/img/menuButton.png", 50, 150, 300, 100, &CameraX, &CameraY, CCollisionRectangle());
    //CSprite* menuButton2 = new CSprite(csdl_setup->GetRenderer(), "data/img/menuButton.png", 50, 300, 300, 100, &CameraX, &CameraY, CCollisionRectangle());

    //исполняется до тех пор, пока не будет передана команда выхода из главного меню

    ////А нужен ли вообще этот цикл?
    while(!Mquit && csdl_setup->GetMainEvent()->type != SDL_QUIT)
    {

        ignoreGameOver = false;

        //????инициализация Mquit в mainmenu (используется для мгновенного выхода из программы)
        mainMenu->setMquit(false);

        //инициализация Mquit для цикла
        Mquit = false;

        //цикл для отображения главного меню
        //Выполняется до тех пор пока переменная quit ложна и не был нажат крестик
        while(!Mquit && csdl_setup->GetMainEvent()->type != SDL_QUIT)
        {
            //очищаем окно и проверяем на события
            csdl_setup->Begin();

            //считываем положение мышки
            SDL_GetMouseState(&MouseX, &MouseY);

            //отрисовка и "просчеты"
            mainMenu->Draw();
            mainMenu->Update();

            //приравнивание Mquit Mquit'y  из меню
            Mquit = mainMenu->getMquit();

            //menu1->Draw();
            //menuButton1->Draw();
            //menuButton2->Draw();

            //отрисовка рендера
            csdl_setup->End();
        }
        if(Mquit)
        {
            //запуск игрового процесса
            GameLoop();

            //запуск GameOver
            GOMenu();
            //СУКА!! БОЛЬШЕ НЕ БУДЕШЬ БАГОВАТЬ
            csdl_setup->GetMainEvent()->type = NULL;
            csdl_setup->GetMainEvent()->button.state = NULL;
            csdl_setup->GetMainEvent()->button.button = NULL;
            std::cout<<"(csdl_setup->GetMainEvent()->type == SDL_MOUSEBUTTONUP) " << (csdl_setup->GetMainEvent()->type == SDL_MOUSEBUTTONUP) <<
       "(csdl_setup->GetMainEvent()->button.state == SDL_RELEASED) " << (csdl_setup->GetMainEvent()->button.state == SDL_RELEASED) <<
       "(csdl_setup->GetMainEvent()->button.button == SDL_BUTTON(SDL_BUTTON_LEFT)) " << (csdl_setup->GetMainEvent()->button.button == SDL_BUTTON(SDL_BUTTON_LEFT)) << std::endl;
        }
    }
}

bool CMain::GOMenu(void)
{
    /*
    //инициализация Mquit
    Mquit = ignoreGameOver;

    //инициализация GameOver окна
    GameOverMenu* gameOverMenu = new GameOverMenu(csdl_setup, &MouseX, &MouseY, &CameraX, &CameraY);

    //основной цикл GameOver окна
    //Выполняется до тех пор пока переменная quit ложна и не был нажат крестик
    while(!Mquit && csdl_setup->GetMainEvent()->type != SDL_QUIT)
    {
        //очищаем окно и проверяем на события
        csdl_setup->Begin();

        //считываем положение мышки
		SDL_GetMouseState(&MouseX, &MouseY);

		//отрисовка и "просчеты"
		gameOverMenu->Draw();
        gameOverMenu->Update();

        //приравнивание Mquit Mquit'y из окна
        Mquit = gameOverMenu->getMquit();

        //отрисовка рендера
		csdl_setup->End();
    }
    return true;*/
}

void CMain::Loading(void)
{
    //инициализация окна загрузки
    LoadingProcess* loadingProcess = new LoadingProcess(csdl_setup, &MouseX, &MouseY, &CameraX, &CameraY);

    //основной цикл загрузки
    //Выполняется до тех пор пока переменная quit ложна и не был нажат крестик
    while(csdl_setup->GetMainEvent()->type != SDL_QUIT)
    {

        //очищаем окно и проверяем на события
        csdl_setup->Begin();

        //считываем положение мышки
		SDL_GetMouseState(&MouseX, &MouseY);

		//добавляем 0.1 процент
        loadingProcess->addProcent(0.1);

        //просчеты и "отрисовка"
        loadingProcess->Update();
		loadingProcess->Draw();

        //отрисовка рендера
		csdl_setup->End();

    }
}

void CMain::DrawLoadingProcess(float percent, LoadingProcess* loadingProcess) //отрисовка процесса (только для опытных пользователей, хе-хе)
{
    csdl_setup->Begin();
    loadingProcess->addProcent(percent);
    loadingProcess->Update();
    loadingProcess->Draw();
    csdl_setup->End();
}

