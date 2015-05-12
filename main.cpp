#include "libraries.h"
#include "Main.h"

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

}


CMain::~CMain(void)
{
	delete csdl_setup;
	//delete MainHero;
}

void CMain::GameLoop(void)
{
    /*
    //�������������� ������� ��������
    LoadingProcess* loadingProcess = new LoadingProcess(csdl_setup, &MouseX, &MouseY, &CameraX, &CameraY);
    DrawLoadingProcess(3.3, loadingProcess);

    //�������������� ��������� ������
    CameraX = 0;
    CameraY = 0;
    DrawLoadingProcess(3.3, loadingProcess);

    //�������������� ��������� ���� � ������� �������
    SDL_GetMouseState(&MouseX, &MouseY);
    Stage1 = new CEnviroment(&CameraX, &CameraY, &MouseX, &MouseY,  csdl_setup, loadingProcess);
    DrawLoadingProcess(3.4, loadingProcess);

    //�������������� ������� ���������
    GameInterface* gameInterface = new GameInterface(csdl_setup, &MouseX, &MouseY, &CameraX, &CameraY);
    DrawLoadingProcess(9, loadingProcess);

    //�������������� �������� �����
    MainHero = new MainCharacter(csdl_setup, &MouseX, &MouseY, &CameraX, &CameraY, Stage1, loadingProcess, gameInterface);
    DrawLoadingProcess(4, loadingProcess);

    interpretator = new CInterpretator(Stage1, MainHero);
    DrawLoadingProcess(4, loadingProcess);

    //������� ������� ��������
    delete loadingProcess;

    //�������� ������� ����
    //����������� �� ��� ��� ���� ���������� quit ����� � �� ��� ����� �������
	while(!quit && csdl_setup->GetMainEvent()->type != SDL_QUIT)
	{
	    //������� ���� � ��������� �� �������
		csdl_setup->Begin();

        //std::cout << "updateTimer: " << updateTimer <<  "SDL_GetTicks: " << SDL_GetTicks() << std::endl;
        if(updateTimer+250 < SDL_GetTicks())
        {
            gsocket->Update();
            net::Address sender;
            unsigned char buffer[256];
            int bytes_read = gsocket->Receive( sender, buffer, sizeof( buffer ) );
            if ( bytes_read )
            {
                printf( "received packet from %d.%d.%d.%d:%d (%d bytes)\n",
                sender.GetA(), sender.GetB(), sender.GetC(), sender.GetD(),
                sender.GetPort(), bytes_read );
                const char data[] = "hello world!";

                unsigned char packet[sizeof(data)+4];
                packet[0] = (unsigned char) ( ProtocolId >> 24 );
                packet[1] = (unsigned char) ( ( ProtocolId >> 16 ) & 0xFF );
                packet[2] = (unsigned char) ( ( ProtocolId >> 8 ) & 0xFF );
                packet[3] = (unsigned char) ( ( ProtocolId ) & 0xFF );
                memcpy( &packet[4], data, sizeof(data) );

                gsocket->Send( net::Address(79,164,35,62,21995), packet, sizeof(packet) );

                std::cout<< "Sent" << std::endl;
            }
            updateTimer = SDL_GetTicks();

        }




        //��������� ��������� �����
		SDL_GetMouseState(&MouseX, &MouseY);

        //�������� �� ����� ���� � ���������� ������ ��� ������������ �������
        Stage1->Update();

        interpretator->command(Stage1->GetConsoleCommand());
        Stage1->SetConsoleCommand("");

        //��������� ������� �����
        Stage1->DrawBack();

        //��������� �������� �����
        MainHero->Draw();

        //���������� �������� � ���������� ��
        MainHero->Update();

        //������� � ���������� ��� �������� ����������
        gameInterface->Update();
        gameInterface->Draw();

        //��������� ��������� �����
        Stage1->DrawFront();

        //��������� �������
		csdl_setup->End();

		//� ������, ���� �������� �� ������ �� 0 - ������� ��� � ����� �� �����
		if(*(MainHero->GetHP()) <= 0)
        {
            delete MainHero;
            break;
        }
        if(gameInterface->getMquit())
        {
            ignoreGameOver = true;
            break;
        }
	}*/
}
void CMain::GameMenu(void)
{
    //������������� �������� ����
    MainMenu* mainMenu = new MainMenu(csdl_setup, &MouseX, &MouseY, &CameraX, &CameraY, gsocket);
    //CSprite* menu1 = new CSprite(csdl_setup->GetRenderer(), "data/img/menu1.png", 100, 0, 800, 600, &CameraX, &CameraY, CCollisionRectangle());
    //CSprite* menuButton1 = new CSprite(csdl_setup->GetRenderer(), "data/img/menuButton.png", 50, 150, 300, 100, &CameraX, &CameraY, CCollisionRectangle());
    //CSprite* menuButton2 = new CSprite(csdl_setup->GetRenderer(), "data/img/menuButton.png", 50, 300, 300, 100, &CameraX, &CameraY, CCollisionRectangle());

    //����������� �� ��� ���, ���� �� ����� �������� ������� ������ �� �������� ����

    ////� ����� �� ������ ���� ����?
    for(;;)
    {

        ignoreGameOver = false;

        //????������������� Mquit � mainmenu (������������ ��� ����������� ������ �� ���������)
        mainMenu->setMquit(false);

        //������������� Mquit ��� �����
        Mquit = false;

        //���� ��� ����������� �������� ����
        //����������� �� ��� ��� ���� ���������� quit ����� � �� ��� ����� �������
        while(!Mquit && csdl_setup->GetMainEvent()->type != SDL_QUIT)
        {
            //������� ���� � ��������� �� �������
            csdl_setup->Begin();

            //��������� ��������� �����
            SDL_GetMouseState(&MouseX, &MouseY);

            //��������� � "��������"
            mainMenu->Draw();
            mainMenu->Update();

            //������������� Mquit Mquit'y  �� ����
            Mquit = mainMenu->getMquit();

            //menu1->Draw();
            //menuButton1->Draw();
            //menuButton2->Draw();

            //��������� �������
            csdl_setup->End();
        }
        if(Mquit)
        {
            //������ �������� ��������
            GameLoop();

            //������ GameOver
            GOMenu();
            //����!! ������ �� ������ ��������
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
    //������������� Mquit
    Mquit = ignoreGameOver;

    //������������� GameOver ����
    GameOverMenu* gameOverMenu = new GameOverMenu(csdl_setup, &MouseX, &MouseY, &CameraX, &CameraY);

    //�������� ���� GameOver ����
    //����������� �� ��� ��� ���� ���������� quit ����� � �� ��� ����� �������
    while(!Mquit && csdl_setup->GetMainEvent()->type != SDL_QUIT)
    {
        //������� ���� � ��������� �� �������
        csdl_setup->Begin();

        //��������� ��������� �����
		SDL_GetMouseState(&MouseX, &MouseY);

		//��������� � "��������"
		gameOverMenu->Draw();
        gameOverMenu->Update();

        //������������� Mquit Mquit'y �� ����
        Mquit = gameOverMenu->getMquit();

        //��������� �������
		csdl_setup->End();
    }
    return true;*/
}
/*
void CMain::Loading(void)
{
    //������������� ���� ��������
    LoadingProcess* loadingProcess = new LoadingProcess(csdl_setup, &MouseX, &MouseY, &CameraX, &CameraY);

    //�������� ���� ��������
    //����������� �� ��� ��� ���� ���������� quit ����� � �� ��� ����� �������
    while(csdl_setup->GetMainEvent()->type != SDL_QUIT)
    {
        //������� ���� � ��������� �� �������
        csdl_setup->Begin();

        //��������� ��������� �����
		SDL_GetMouseState(&MouseX, &MouseY);

		//��������� 0.1 �������
        loadingProcess->addProcent(0.1);

        //�������� � "���������"
        loadingProcess->Update();
		loadingProcess->Draw();

        //��������� �������
		csdl_setup->End();
    }
}

void CMain::DrawLoadingProcess(float percent, LoadingProcess* loadingProcess) //��������� �������� (������ ��� ������� �������������, ��-��)
{
    csdl_setup->Begin();
    loadingProcess->addProcent(percent);
    loadingProcess->Update();
    loadingProcess->Draw();
    csdl_setup->End();
}
*/
