#include "Menu.h"
//������� ���������
extern std::string login;
GameInterface::GameInterface(CSDL_Setup* passed_SDL_Setup, int *passed_MouseX, int *passed_MouseY, float *passed_CameraX, float *passed_CameraY)
{

    CameraX = passed_CameraX;
    CameraY = passed_CameraY;

    HP = 0;
    linkTmpHP = &tmpHP;
    maxHP = 0;
    linkTmpMaxHP = &tmpMaxHP;

    csdl_setup = passed_SDL_Setup;
    MouseX = passed_MouseX;
    MouseY = passed_MouseY;
    HPstatus = 1;
    //interface1 = new CSprite(csdl_setup->GetRenderer(), "data/img/GUI.png", 0, csdl_setup->GetScreenHeight()-(csdl_setup->GetScreenWidth()*0.35)*0.35, csdl_setup->GetScreenWidth()*0.35, (csdl_setup->GetScreenWidth()*0.35)*0.35, CameraX, CameraY,
    //                          CCollisionRectangle(), csdl_setup);
    //interface2 = new CSprite(csdl_setup->GetRenderer(), "data/img/interfaces/02.png", csdl_setup->GetScreenWidth()*0.5 - (csdl_setup->GetScreenWidth()*0.35)/3, csdl_setup->GetScreenHeight()-(csdl_setup->GetScreenWidth()*0.35)*0.25,
    //                          csdl_setup->GetScreenWidth()*0.35, (csdl_setup->GetScreenWidth()*0.35)*0.25, CameraX, CameraY, CCollisionRectangle(), csdl_setup);
/*
    interface1 = new CSprite(csdl_setup->GetRenderer(), "data/img/interfaces/bottom.png", 20, 500,
                              750, 100, CameraX, CameraY, CCollisionRectangle(), csdl_setup);

    mapForm = new CSprite(csdl_setup->GetRenderer(), "data/img/interfaces/map.png", 615, 20,
                              150, 150, CameraX, CameraY, CCollisionRectangle(), csdl_setup);
    statusForm1 = new CSprite(csdl_setup->GetRenderer(), "data/img/interfaces/status.png", 625, 190,
                              60, 60, CameraX, CameraY, CCollisionRectangle(), csdl_setup);
    status1 = new CSprite(csdl_setup->GetRenderer(), "data/img/interfaces/hunger1.png", 625, 195,
                              50, 50, CameraX, CameraY, CCollisionRectangle(0,0,50,50), csdl_setup);

    statusForm2 = new CSprite(csdl_setup->GetRenderer(), "data/img/interfaces/status.png", 700, 190,
                              60, 60, CameraX, CameraY, CCollisionRectangle(), csdl_setup);
    status2 = new CSprite(csdl_setup->GetRenderer(), "data/img/interfaces/health1.png", 700, 200,
                              60, 45, CameraX, CameraY, CCollisionRectangle(0,0,60,45), csdl_setup);
    timeCheck1 = 0;
    timeCheck2 = 0;
    timeCheck1_1 = SDL_GetTicks();
    flagTimeCheck1_1= false;
    timeCheck2_1 = SDL_GetTicks();
    flagTimeCheck2_1= false;


    statusWindow1 = new CSprite(csdl_setup->GetRenderer(), "data/img/interfaces/window.png", 550, 250,
                              260, 100, CameraX, CameraY, CCollisionRectangle(), csdl_setup);
    statusWindow2 = new CSprite(csdl_setup->GetRenderer(), "data/img/interfaces/window.png", 700, 250,
                              100, 100, CameraX, CameraY, CCollisionRectangle(), csdl_setup);

    HPofStatusWindow2 = new Text(tmpHP, 720, 280, 10, 10, csdl_setup, CameraX, CameraY);
    textHPofStatusWindow2 = new Text("HP", 765, 280, 10, 10, csdl_setup, CameraX, CameraY);

    maxHPofStatusWindow2 = new Text(tmpMaxHP, 720, 310, 10, 10, csdl_setup, CameraX, CameraY);
    textmaxHPofStatusWindow2 = new Text("max", 755, 310, 10, 10, csdl_setup, CameraX, CameraY);

    VisibleHPStatus = false;
    VisibleHungerStatus = false;

    escapeWindow1 = new CSprite(csdl_setup->GetRenderer(), "data/img/interfaces/window.png", 200, 100,
                              400, 400, CameraX, CameraY, CCollisionRectangle(), csdl_setup);*/
    VisibleEscapeWindow = false;

/*
    escapeButton1text = new Text("exit to main menu", 310, 245, 12, 12, csdl_setup, CameraX, CameraY);
    escapeButton2text = new Text("exit to windows", 320, 345, 12, 12, csdl_setup, CameraX, CameraY);
    escapeButton1 = new CSprite(csdl_setup->GetRenderer(), "data/img/MenuButton1.png", 300, 225, 225, 50, CameraX, CameraY,
                              CCollisionRectangle(0,0, 225, 50),csdl_setup);
    escapeButton1->SetUpAnimation(3,1);
    escapeButton2 = new CSprite(csdl_setup->GetRenderer(), "data/img/MenuButton1.png", 300, 325, 225, 50, CameraX, CameraY,
                              CCollisionRectangle(0,0, 225, 50),csdl_setup);
    escapeButton2->SetUpAnimation(3,1);
*/


    downInterface = new CSprite(csdl_setup->GetRenderer(), "data/img/inventory/bg.png", 150, 668,
                              700, 100, CameraX, CameraY, CCollisionRectangle(), csdl_setup);
    weaponIcon = new CSprite(csdl_setup->GetRenderer(), "data/img/inventory/wep.png", 795, 727,
                              32, 32, CameraX, CameraY, CCollisionRectangle(), csdl_setup);
    armorIcon = new CSprite(csdl_setup->GetRenderer(), "data/img/inventory/arm.png", 748, 727,
                              32, 32, CameraX, CameraY, CCollisionRectangle(), csdl_setup);
    HPStatus = new CSprite(csdl_setup->GetRenderer(), "data/img/Status/hp.png", 870, 20,
                              72, 72, CameraX, CameraY, CCollisionRectangle(), csdl_setup);
    HPStatus->SetUpAnimation(3,1);
    hungerStatus = new CSprite(csdl_setup->GetRenderer(), "data/img/Status/hunger.png", 950, 20,
                              72, 72, CameraX, CameraY, CCollisionRectangle(), csdl_setup);
    hungerStatus->SetUpAnimation(3,1);
/*

    Text* tHPStatus;
    Text* thungerStatus;*/
}


GameInterface::~GameInterface(void)
{

}

void GameInterface::UpdateInformation(int passed_HP, int passed_maxHP)
{

    HP = passed_HP;

    //�������� �������� ������ HP
    tmpHP = IntToStr(HP);

    maxHP = passed_maxHP;

    //�������� �������� ������ maxHP
    tmpMaxHP = IntToStr(maxHP);


}

void GameInterface::UpdateAnimation()
{



    if((HP >= (maxHP / 3) * 2))
    {
        HPStatus->PlayAnimation(0, 0, 0, 1000);
    }
    else if((HP >= maxHP / 3) && (HP <= (maxHP / 3) * 2))
    {
        HPStatus->PlayAnimation(1, 1, 0, 1000);
    }
    else if((HP <= maxHP / 3))
    {
        HPStatus->PlayAnimation(2, 2, 0, 1000);
    }
    hungerStatus->PlayAnimation(0, 0, 0, 1000);
    /*
    //������� �������� ���������� ��� ������ ������� ���������
    //interface1->SetCrop(0,0,364,128);
    escapeButton1text->Update();
    escapeButton2text->Update();
    stomachStatus->Update();
    soreStatus->Update();
    depletionStatus->Update();


    //���� ����� �������� �� ������1, �� �� ������ ��� - ��������� ��������
    if(escapeButton1->isColliding(*MouseX, *MouseY) && !(csdl_setup->GetMainEvent()->button.button == SDL_BUTTON(SDL_BUTTON_LEFT) || csdl_setup->GetMainEvent()->button.button == SDL_BUTTON_LEFT))
    {
        escapeButton1->PlayAnimation(1, 1, 0, 10);
        escapeButton2->PlayAnimation(0, 0, 0, 10);
    }

    //���� ����� �������� �� ������2, �� �� ������ ��� - ��������� ��������
    else if(escapeButton2->isColliding(*MouseX, *MouseY) && !(csdl_setup->GetMainEvent()->button.button == SDL_BUTTON(SDL_BUTTON_LEFT) || csdl_setup->GetMainEvent()->button.button == SDL_BUTTON_LEFT))
    {
        escapeButton1->PlayAnimation(0, 0, 0, 10);
        escapeButton2->PlayAnimation(1, 1, 0, 10);
    }

    //���� ����� �������� �� ������1 � ������ ��� - ��������� ��������
    else if(escapeButton1->isColliding(*MouseX, *MouseY) && (csdl_setup->GetMainEvent()->button.button == SDL_BUTTON(SDL_BUTTON_LEFT) || csdl_setup->GetMainEvent()->button.button == SDL_BUTTON_LEFT)
                                    && (csdl_setup->GetMainEvent()->type == SDL_MOUSEBUTTONDOWN || csdl_setup->GetMainEvent()->type == SDL_MOUSEMOTION))
    {
        escapeButton1->PlayAnimation(2, 2, 0, 10);
        escapeButton2->PlayAnimation(0, 0, 0, 10);
    }

    //���� ����� �������� �� ������2 � ������ ��� - ��������� ��������
    else if(escapeButton2->isColliding(*MouseX, *MouseY) && (csdl_setup->GetMainEvent()->button.button == SDL_BUTTON(SDL_BUTTON_LEFT) || csdl_setup->GetMainEvent()->button.button == SDL_BUTTON_LEFT)
                                    && (csdl_setup->GetMainEvent()->type == SDL_MOUSEBUTTONDOWN || csdl_setup->GetMainEvent()->type == SDL_MOUSEMOTION))
    {
        escapeButton1->PlayAnimation(0, 0, 0, 10);
        escapeButton2->PlayAnimation(2, 2, 0, 10);
    }

    //����� ��������� ����������� ��������
    else
    {
        escapeButton1->PlayAnimation(0, 0, 0, 250);
        escapeButton2->PlayAnimation(0, 0, 0, 250);
    }
    */
}

void GameInterface::Update()
{
    /*
    if(emptyStomach)
    {
        stomachStatus->SetText("empty stomach");
    }
    else
    {
        stomachStatus->SetText("");
    }
    if(shortageEnergy > 2000)
    {
        depletionStatus->SetText("severe depletion");
    }
    else if(shortageEnergy > 1000)
    {
        depletionStatus->SetText("depletion");
    }
    else if(shortageEnergy > 500)
    {
        depletionStatus->SetText("weak depletion");
    }
    else
    {
        depletionStatus->SetText("");
    }
    if(sore)
    {
        soreStatus->SetText("sore stomach");
    }
    else
    {
        soreStatus->SetText("");
    }


    HPofStatusWindow2->SetText(tmpHP);
    maxHPofStatusWindow2->SetText(tmpMaxHP);

    textHPofStatusWindow2->Update();
    textmaxHPofStatusWindow2->Update();
    HPofStatusWindow2->Update();
    maxHPofStatusWindow2->Update();

    //���� ������������ ����� ������ �� ������ hunger
    if(status1->isColliding(*MouseX, *MouseY))
    {
        //������� ����������� 3 �������
        if(!flagTimeCheck1_1)
        {
            timeCheck1_1 = SDL_GetTicks();
            flagTimeCheck1_1 = true;
        }
        timeCheck1 = SDL_GetTicks() - timeCheck1_1;
    }
    //�����
    //������� ����������
    else
    {
        flagTimeCheck1_1 = false;
        timeCheck1 = 0;
        timeCheck1_1 = SDL_GetTicks();
        VisibleStatusWindow1 = false;
    }
    //���� ������� ����� 0.5 ������e ��� ������
    //������� �������� � �������
    if(timeCheck1 >= 500)
    {
        VisibleStatusWindow1 = true;
    }

    //���� ������������ ����� ������ �� ������ HP
    if(status2->isColliding(*MouseX, *MouseY))
    {
        //������� ����������� 3 �������
        if(!flagTimeCheck2_1)
        {
            timeCheck2_1 = SDL_GetTicks();
            flagTimeCheck2_1 = true;
        }
        timeCheck2 = SDL_GetTicks() - timeCheck2_1;
    }
    //�����
    //������� ����������
    else
    {
        flagTimeCheck2_1 = false;
        timeCheck2 = 0;
        timeCheck2_1 = SDL_GetTicks();
        VisibleStatusWindow2 = false;
    }
    //���� ������� ����� 0,5 ������e ��� ������
    //������� �������� � �������
    if(timeCheck2 >= 500)
    {
        VisibleStatusWindow2 = true;
    }
    if (csdl_setup->GetMainEvent()->type == SDL_KEYDOWN)
    {

        if (!OnePressed && csdl_setup->GetMainEvent()->key.keysym.sym == SDLK_ESCAPE)
        {
            if(!VisibleEscapeWindow1)
                VisibleEscapeWindow1 = true;
            else
                VisibleEscapeWindow1 = false;
            OnePressed = true;
        }
    }
    if (csdl_setup->GetMainEvent()->type == SDL_KEYUP)
    {

        if (OnePressed && csdl_setup->GetMainEvent()->key.keysym.sym == SDLK_ESCAPE)
        {
            OnePressed = false;
        }

    }

    if((csdl_setup->GetMainEvent()->type == SDL_MOUSEBUTTONUP) &&
       (csdl_setup->GetMainEvent()->button.state == SDL_RELEASED) &&
       (csdl_setup->GetMainEvent()->button.button == SDL_BUTTON(SDL_BUTTON_LEFT)))
    {
        //���� ���� ������ ������1
        if(escapeButton1->isColliding(*MouseX, *MouseY) && VisibleEscapeWindow1)
        {
            //������� ������ �� ���� - ON
            Mquit = true;
        }

        //���� ���� ������ ������2
        if(escapeButton2->isColliding(*MouseX, *MouseY) && VisibleEscapeWindow1)
        {
            //����� �� ���������
            exit(1);
        }
    }

*/
    //�������� ��������
    UpdateAnimation();


}

void GameInterface::Draw()
{
    //���������� ���������

    downInterface->DrawStatic();
    weaponIcon->DrawStatic();
    armorIcon->DrawStatic();

    HPStatus->DrawStatic();
    hungerStatus->DrawStatic();

    //CSprite* HPStatus;
    //CSprite* hungerStatus;

/*
    if(VisibleEscapeWindow)
    {

        escapeWindow1->DrawStatic();
        escapeButton1->DrawStatic();
        escapeButton2->DrawStatic();
        escapeButton1text->Draw();
        escapeButton2text->Draw();
    }*/
}

//������� ����
MainMenu::MainMenu(CSDL_Setup* passed_SDL_Setup, int *passed_MouseX, int *passed_MouseY, float *passed_CameraX, float *passed_CameraY, net::Socket* passed_gsocket)
{

    gsocket = passed_gsocket;
    CameraX = passed_CameraX;
    CameraY = passed_CameraY;

    csdl_setup = passed_SDL_Setup;
    MouseX = passed_MouseX;
    MouseY = passed_MouseY;
    Mquit  = false;

    activeMenu = mainMenu;

    startButton = new CSprite(csdl_setup->GetRenderer(), "data/img/Menu/Start1.png", 450, 480, 130, 60, CameraX, CameraY,
                              CCollisionRectangle(0,0, 285, 75),csdl_setup);
    startButton->SetUpAnimation(3,1);
    optionsButton = new CSprite(csdl_setup->GetRenderer(), "data/img/Menu/Options1.png", 426, 560, 175, 75, CameraX, CameraY,
                              CCollisionRectangle(0,0, 285, 75),csdl_setup);
    optionsButton->SetUpAnimation(3,1);
    exitButton = new CSprite(csdl_setup->GetRenderer(), "data/img/Menu/Exit1.png", 470, 660, 85, 50, CameraX, CameraY,
                              CCollisionRectangle(0,0, 85, 50),csdl_setup);
    exitButton->SetUpAnimation(3,1);

    BG = new CSprite(csdl_setup->GetRenderer(), "data/img/Menu/BG.png", 0, 0, csdl_setup->GetScreenWidth(), csdl_setup->GetScreenHeight(),
                     CameraX, CameraY, CCollisionRectangle() , csdl_setup);


}


MainMenu::~MainMenu(void)
{

}

void MainMenu::UpdateAnimation()
{
    if(activeMenu == mainMenu)
    {
        //���� ����� �������� �� ������1, �� �� ������ ��� - ��������� ��������
        if(startButton->isColliding(*MouseX, *MouseY) && !(csdl_setup->GetMainEvent()->button.button == SDL_BUTTON(SDL_BUTTON_LEFT) || csdl_setup->GetMainEvent()->button.button == SDL_BUTTON_LEFT))
        {
            startButton->PlayAnimation(1, 1, 0, 10);
            optionsButton->PlayAnimation(0, 0, 0, 10);
            exitButton->PlayAnimation(0, 0, 0, 10);
        }

        //���� ����� �������� �� ������2, �� �� ������ ��� - ��������� ��������
        else if(optionsButton->isColliding(*MouseX, *MouseY) && !(csdl_setup->GetMainEvent()->button.button == SDL_BUTTON(SDL_BUTTON_LEFT) || csdl_setup->GetMainEvent()->button.button == SDL_BUTTON_LEFT))
        {
            startButton->PlayAnimation(0, 0, 0, 10);
            optionsButton->PlayAnimation(1, 1, 0, 10);
            exitButton->PlayAnimation(0, 0, 0, 10);
        }

        //���� ����� �������� �� ������3, �� �� ������ ��� - ��������� ��������
        else if(exitButton->isColliding(*MouseX, *MouseY) && !(csdl_setup->GetMainEvent()->button.button == SDL_BUTTON(SDL_BUTTON_LEFT) || csdl_setup->GetMainEvent()->button.button == SDL_BUTTON_LEFT))
        {
            startButton->PlayAnimation(0, 0, 0, 10);
            optionsButton->PlayAnimation(0, 0, 0, 10);
            exitButton->PlayAnimation(1, 1, 0, 10);
        }

        //���� ����� �������� �� ������1 � ������ ��� - ��������� ��������
        else if(startButton->isColliding(*MouseX, *MouseY) && (csdl_setup->GetMainEvent()->button.button == SDL_BUTTON(SDL_BUTTON_LEFT) || csdl_setup->GetMainEvent()->button.button == SDL_BUTTON_LEFT)
                                        && (csdl_setup->GetMainEvent()->type == SDL_MOUSEBUTTONDOWN || csdl_setup->GetMainEvent()->type == SDL_MOUSEMOTION))
        {
            startButton->PlayAnimation(2, 2, 0, 10);
            optionsButton->PlayAnimation(0, 0, 0, 10);
            exitButton->PlayAnimation(0, 0, 0, 10);
        }

        //���� ����� �������� �� ������2 � ������ ��� - ��������� ��������
        else if(optionsButton->isColliding(*MouseX, *MouseY) && (csdl_setup->GetMainEvent()->button.button == SDL_BUTTON(SDL_BUTTON_LEFT) || csdl_setup->GetMainEvent()->button.button == SDL_BUTTON_LEFT)
                                        && (csdl_setup->GetMainEvent()->type == SDL_MOUSEBUTTONDOWN || csdl_setup->GetMainEvent()->type == SDL_MOUSEMOTION))
        {
            startButton->PlayAnimation(0, 0, 0, 10);
            optionsButton->PlayAnimation(2, 2, 0, 10);
            exitButton->PlayAnimation(0, 0, 0, 10);
        }
        //���� ����� �������� �� ������3 � ������ ��� - ��������� ��������
        else if(exitButton->isColliding(*MouseX, *MouseY) && (csdl_setup->GetMainEvent()->button.button == SDL_BUTTON(SDL_BUTTON_LEFT) || csdl_setup->GetMainEvent()->button.button == SDL_BUTTON_LEFT)
                                        && (csdl_setup->GetMainEvent()->type == SDL_MOUSEBUTTONDOWN || csdl_setup->GetMainEvent()->type == SDL_MOUSEMOTION))
        {
            startButton->PlayAnimation(0, 0, 0, 10);
            optionsButton->PlayAnimation(0, 0, 0, 10);
            exitButton->PlayAnimation(2, 2, 0, 10);
        }

        //����� ��������� ����������� ��������
        else
        {
            startButton->PlayAnimation(0, 0, 0, 10);
            optionsButton->PlayAnimation(0, 0, 0, 10);
            exitButton->PlayAnimation(0, 0, 0, 10);
        }
    }
}

void MainMenu::Update()
{
    UpdateAnimation();
    UpdateControls();
}

void MainMenu::UpdateControls()
{
    if(activeMenu == mainMenu)
    {
        //���� ������ ���� �������� � ��� ���
        if((csdl_setup->GetMainEvent()->type == SDL_MOUSEBUTTONUP) &&
           (csdl_setup->GetMainEvent()->button.state == SDL_RELEASED) &&
           (csdl_setup->GetMainEvent()->button.button == SDL_BUTTON(SDL_BUTTON_LEFT)))
        {
            //���� ���� ������ ������1
            if(startButton->isColliding(*MouseX, *MouseY))
            {
                //������� ������ �� ���� - ON

                char data[18];
                data[0] = 10;
                int l;
                for(int n = 1, l = 0; n <=9; n++, l++)
                {
                    data[n] = login[l];
                }
                std::string pass = "89658965";
                for(int n = 10, l = 0; n <=18; n++, l++)
                {
                    data[n] = pass[l];
                }

                unsigned char packet[sizeof(data)+4];
                packet[0] = (unsigned char) ( ProtocolId >> 24 );
                packet[1] = (unsigned char) ( ( ProtocolId >> 16 ) & 0xFF );
                packet[2] = (unsigned char) ( ( ProtocolId >> 8 ) & 0xFF );
                packet[3] = (unsigned char) ( ( ProtocolId ) & 0xFF );
                memcpy( &packet[4], data, sizeof(data) );

                gsocket->Send( net::Address(79,164,35,62,21995), packet, sizeof(packet) );

                std::cout<< "Sent" << std::endl;

                activeMenu = connectMenu;

                csdl_setup->GetMainEvent()->type = NULL;
                csdl_setup->GetMainEvent()->button.state = NULL;
                csdl_setup->GetMainEvent()->button.button = NULL;
                //Mquit = true;
            }

            //���� ���� ������ ������2
            if(exitButton->isColliding(*MouseX, *MouseY))
            {
                //����� �� ���������
                exit(1);
            }
        }
    }
    else if(activeMenu == connectMenu)
    {

        Mquit = true;
    }

}

void MainMenu::Draw()
{
    //���������� �������
    BG->DrawStatic();

    if(activeMenu == mainMenu)
    {
        startButton->DrawStatic();
        optionsButton->DrawStatic();
        exitButton->DrawStatic();
    }
    else if(activeMenu == connectMenu)
    {

    }
}
/*
GameOverMenu::GameOverMenu(CSDL_Setup* passed_SDL_Setup, int *passed_MouseX, int *passed_MouseY, float *passed_CameraX, float *passed_CameraY)
{

    CameraX = passed_CameraX;
    CameraY = passed_CameraY;

    csdl_setup = passed_SDL_Setup;
    MouseX = passed_MouseX;
    MouseY = passed_MouseY;
    Mquit  = false;

    text1 = new Text("Game Over", "BLACK", csdl_setup->GetScreenWidth()*0.2, csdl_setup->GetScreenHeight()*0.37, csdl_setup->GetScreenWidth()*0.066, csdl_setup->GetScreenHeight()*0.066, csdl_setup, CameraX, CameraY);
    text2 = new Text("Main menu", csdl_setup->GetScreenWidth()*0.283, csdl_setup->GetScreenHeight()*0.67, csdl_setup->GetScreenWidth()*0.05, csdl_setup->GetScreenHeight()*0.066, csdl_setup, CameraX, CameraY);

    MenuButton1 = new CSprite(csdl_setup->GetRenderer(), "data/img/MenuButton1.png", csdl_setup->GetScreenWidth()*0.25, csdl_setup->GetScreenHeight()*0.6, csdl_setup->GetScreenWidth()*0.5, csdl_setup->GetScreenHeight()*0.2, CameraX, CameraY,
                              CCollisionRectangle(0,0,csdl_setup->GetScreenWidth()*0.5,csdl_setup->GetScreenHeight()*0.2), csdl_setup);
    MenuButton1->SetUpAnimation(3,1);
}


GameOverMenu::~GameOverMenu(void)
{

}

void GameOverMenu::UpdateAnimation()
{
    //��������� ����� gameover
    text1->Update();

    //��������� ����� �� ������
    text2->Update();

    //���� ����� �������� �� ������ - ��������� ��������
    if(MenuButton1->isColliding(*MouseX, *MouseY) && !(csdl_setup->GetMainEvent()->button.button == SDL_BUTTON(SDL_BUTTON_LEFT) || csdl_setup->GetMainEvent()->button.button == SDL_BUTTON_LEFT))
    {
        MenuButton1->PlayAnimation(1, 1, 0, 10);
    }

    //���� ������ ������ ��� - ��������� ��������
    else if(MenuButton1->isColliding(*MouseX, *MouseY) && (csdl_setup->GetMainEvent()->button.button == SDL_BUTTON(SDL_BUTTON_LEFT) || csdl_setup->GetMainEvent()->button.button == SDL_BUTTON_LEFT)
                                    && (csdl_setup->GetMainEvent()->type == SDL_MOUSEBUTTONDOWN || csdl_setup->GetMainEvent()->type == SDL_MOUSEMOTION))
    {
        MenuButton1->PlayAnimation(2, 2, 0, 10);
    }

    //����� ��������� ����������� ��������
    else
    {
        MenuButton1->PlayAnimation(0, 0, 0, 250);
    }
}

void GameOverMenu::Update()
{
    UpdateAnimation();
    UpdateControls();
}

void GameOverMenu::UpdateControls()
{
    //���� ������ ���� �������� � ��� ���
    if((csdl_setup->GetMainEvent()->type == SDL_MOUSEBUTTONUP) &&
       (csdl_setup->GetMainEvent()->button.state == SDL_RELEASED) &&
       (csdl_setup->GetMainEvent()->button.button == SDL_BUTTON(SDL_BUTTON_LEFT)))
    {
        //���� ���� ������ ������1
        if(MenuButton1->isColliding(*MouseX, *MouseY))
        {
            //������� ������ �� ���� - ON
            Mquit = true;
        }
    }
}
void GameOverMenu::Draw()
{
    //���������� ������1
    MenuButton1->DrawStatic();

    //����������� gameover
    text1->Draw();

    //���������� ����� �� ������
    text2->Draw();

}
*/
LoadingProcess::LoadingProcess(CSDL_Setup* passed_SDL_Setup, int *passed_MouseX, int *passed_MouseY, float *passed_CameraX, float *passed_CameraY)
{

    CameraX = passed_CameraX;
    CameraY = passed_CameraY;

    csdl_setup = passed_SDL_Setup;
    MouseX = passed_MouseX;
    MouseY = passed_MouseY;
    ProgressPositionX = int(csdl_setup->GetScreenWidth()*0.45);
    Progress = 0;


    MCHPbar1 = new CSprite(csdl_setup->GetRenderer(), "data/img/GUI.png", csdl_setup->GetScreenWidth()*0.125, csdl_setup->GetScreenHeight()*0.6,
                           csdl_setup->GetScreenWidth()*0.68, csdl_setup->GetScreenHeight()*0.065, CameraX, CameraY, CCollisionRectangle(), csdl_setup);
    MCHPbar2 = new CSprite(csdl_setup->GetRenderer(), "data/img/GUI.png", csdl_setup->GetScreenWidth()*0.125, csdl_setup->GetScreenHeight()*0.6,
                           csdl_setup->GetScreenWidth()*0.68, csdl_setup->GetScreenHeight()*0.065, CameraX, CameraY, CCollisionRectangle(), csdl_setup);

    text1 = new Text(csdl_setup->GetRenderer(),
                      "Loading",
                      400,
                      300,
                      50);
    text2 = new Text(csdl_setup->GetRenderer(),
                      "0",
                      ProgressPositionX,
                      462,
                      50);
}


LoadingProcess::~LoadingProcess(void)
{

}

void LoadingProcess::UpdateAnimation()
{
    //��������� �������� �������� �� Float � int
    int intProgress = int(Progress);

    //��������� ����� � ���������� ��� ������ ��������� ��������
    text2->SetText(IntToStr(intProgress));

    //�������� �� �������� GUI �����������
    MCHPbar1->SetCrop(0,128,112,11);

    //�������� ������� HP��� � ����������� �� ��������� ��������
    MCHPbar2->SetCrop(112,128,112*(Progress/100),11);

    //�������� ������ ������� ������������
    MCHPbar2->SetCameraW((csdl_setup->GetScreenWidth()*0.68)*(Progress/100));
}

void LoadingProcess::Update()
{
    UpdateAnimation();
}

void LoadingProcess::Draw()
{
    //���������� �����������
    MCHPbar1->DrawStatic();
    MCHPbar2->DrawStatic();

    //���������� gameover
    text1->Draw();

    //���������� ����� �� ������
    text2->Draw();

}
void LoadingProcess::addProcent(float z)
{
    //��������� �������� �� ��������� ��������
    Progress += z;

    //���� ����� ��������� ����������, �� ������ ������������ � ������� �
    if(Progress > 9)
    {
        ProgressPositionX = int(csdl_setup->GetScreenWidth()*0.45 + csdl_setup->GetScreenWidth()*0.025);
        text2->SetX(ProgressPositionX);
    }

    //���� ����� ��������� �����������, �� ������ ������������ � ������� �
    if(Progress > 99)
    {
        ProgressPositionX = int(csdl_setup->GetScreenWidth()*0.45 + csdl_setup->GetScreenWidth()*0.05);
        text2->SetX(ProgressPositionX);
    }

    //���� �������� ������ ��� ���������, �� �������� ��� ������ 100
    if(Progress >= 100)
        Progress = 100;

}

