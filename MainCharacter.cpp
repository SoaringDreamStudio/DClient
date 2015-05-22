#include "MainCharacter.h"

MainCharacter::MainCharacter(std::string passed_NickName, CSDL_Setup* passed_SDL_Setup, int *passed_MouseX, int *passed_MouseY, float *passed_CameraX, float *passed_CameraY, GameLVL* passed_gameLVL, LoadingProcess* loadingProcess, GameInterface* passed_gameInterface)
{
    NickName = passed_NickName;
    gameLVL = passed_gameLVL;
    gameInterface = passed_gameInterface;

    CameraX = passed_CameraX;
    CameraY = passed_CameraY;
    maxHP = 100;
    HP = 100;

    OnePressed = false;
    escapeMenu = false;
    MoveLeft = false;
    MoveDown = false;
    MoveRight = false;
    MoveUp = false;

    staticSpeed = 3;
	speed = 3;

    csdl_setup = passed_SDL_Setup;
    //
    csdl_setup->Begin();
    loadingProcess->addProcent(9);
    loadingProcess->Update();
    loadingProcess->Draw();

    loadingProcess->addProcent(9);
    loadingProcess->Update();
    loadingProcess->Draw();
    csdl_setup->End();
    //

    MouseX = passed_MouseX;
    MouseY = passed_MouseY;
    tmpW = 97; //������ ������� ������
    tmpH = 65;
	SpriteMainHero = new CSprite(csdl_setup->GetRenderer(),"data/img/hero.png", (csdl_setup->GetScreenWidth()/2)-(tmpW/2), (csdl_setup->GetScreenHeight()/2)-tmpH, tmpW, tmpH, CameraX, CameraY,
                   CCollisionRectangle((csdl_setup->GetScreenWidth()/2)-(tmpW/2)+35,(csdl_setup->GetScreenHeight()/2)-tmpH+50,tmpW-70,tmpH-50), csdl_setup);
    SpriteMainHero->SetUpAnimation(6,4);
	SpriteMainHero->SetOrgin(SpriteMainHero->GetWidht()/2.0f,SpriteMainHero->GetHeight());

    nightTimer = SDL_GetTicks();

    //
    csdl_setup->Begin();
    loadingProcess->addProcent(9);
    loadingProcess->Update();
    loadingProcess->Draw();
    csdl_setup->End();
    //

	timeCheck = SDL_GetTicks();
	timeCheck4 = SDL_GetTicks();
	timeCheckMoving = SDL_GetTicks();
	Follow = false;
	distance = 0;
	stopAnimation = false;


    coordinates spawn = gameLVL->getSpawn();
}


MainCharacter::~MainCharacter(void)
{
    delete SpriteMainHero;

}

void MainCharacter::SendInfoToInterface()
{
    gameInterface->UpdateInformation(HP, maxHP);
}

void MainCharacter::UpdateAnimation() //���������� �������� �������� �����
{

    //�����-�� ���������� ��� ����������� ����-����������� ������ ����������
    angle = atan2(Follow_Point_Y - *CameraY, Follow_Point_X - *CameraX);
    angle = (angle * (180/3.14)) + 180;

    //���� ����� ��������� � ������������ �����������, �� ������ ��������������� ��������
    //�������� �� ��������

    if (MoveRight && MoveLeft && MoveUp)
    {
        SpriteMainHero->PlayAnimation(0, 2, 0, 250);
    }
    else if (MoveRight && MoveLeft && MoveDown)
    {
        SpriteMainHero->PlayAnimation(0, 2, 3, 250);
    }
    else if (MoveUp && MoveDown && MoveRight)
    {
        SpriteMainHero->PlayAnimation(0, 2, 2, 250);
    }
    else if (MoveUp && MoveDown && MoveLeft)
    {
        SpriteMainHero->PlayAnimation(0, 2, 1, 250);
    }
    else if (MoveRight && MoveLeft)
    {

    }
    else if (MoveUp && MoveDown)
    {

    }
    else if (MoveRight)
    {
        SpriteMainHero->PlayAnimation(0, 2, 2, 250);
    }
    else if (MoveUp)
    {
        SpriteMainHero->PlayAnimation(0, 2, 0, 250);
    }
    else if (MoveLeft)
    {
        SpriteMainHero->PlayAnimation(0, 2, 1, 250);
    }
    else if (MoveDown)
    {
        SpriteMainHero->PlayAnimation(0, 2, 3, 250);
    }

    //���� �������� �� �����������
    if (!stopAnimation)
    {
        //�������� �� �����
        if ((angle <=360 && angle >315) || (angle >=0 && angle <= 45))//left
        {
            if (distance < 20)
                SpriteMainHero->PlayAnimation(1, 1, 2, 250);
            else
                SpriteMainHero->PlayAnimation(0, 2, 2, 250);
        }
        else if (angle > 45 && angle <=135)//up
        {
            if (distance < 20)
                SpriteMainHero->PlayAnimation(1, 1, 3, 250);
            else
                SpriteMainHero->PlayAnimation(0, 2, 3, 250);
        }
        else if (angle > 135 && angle <=225)//right
        {
            if (distance < 20)
                SpriteMainHero->PlayAnimation(1, 1, 1, 250);
            else
                SpriteMainHero->PlayAnimation(0, 2, 1, 250);
        }
        else if (angle > 225 && angle <= 315)//down
        {
            if (distance < 20)
                SpriteMainHero->PlayAnimation(1, 1, 0, 250);
            else
                SpriteMainHero->PlayAnimation(0, 2, 0, 250);
        }
    }
}

void MainCharacter::UpdateControls()
{
    //������ �������� �� �������� �� �������
    if (csdl_setup->GetMainEvent()->type == SDL_KEYDOWN)
    {

        if (!OnePressed && csdl_setup->GetMainEvent()->key.keysym.sym == SDLK_ESCAPE)
        {
            if(!escapeMenu)
                escapeMenu = true;
            else
                escapeMenu = false;
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

    if (!escapeMenu)
    {

        //���� ���������� �����-�� �������
        switch (csdl_setup->GetMainEvent()->type)
        {
            //���� ������ �������
            case SDL_KEYDOWN:
                switch (csdl_setup->GetMainEvent()->key.keysym.sym)
                {
                    //���� ������ ������� A
                    case SDLK_a:
                        //�������� ������� ������������ ������
                        MoveLeft = true;
                        break;
                    //���� ������ ������� S
                    case SDLK_s:
                        //�������� ������� ������������ ����
                        MoveDown = true;
                        break;
                    //���� ������ ������� D
                    case SDLK_d:
                        //�������� ������� ������������ �������
                        MoveRight = true;
                        break;
                    //���� ������ ������� W
                    case SDLK_w:
                        //�������� ������� ������������ �����
                        MoveUp = true;
                        break;
                    default:
                        break;
                }

                break;

            //���� �������� ������� (��������� ���� ��� ���������� ��������)
            case SDL_KEYUP:
                switch (csdl_setup->GetMainEvent()->key.keysym.sym)
                {
                    //���� ������ ������� A
                    case SDLK_a:
                        //��������� ������� ������������ �����
                        MoveLeft = false;

                        //��������� ���������� � ������ ����������, ��������� ������
                        Follow = false;

                        //���������� ����-�����������
                        angle = 0;
                        break;

                    //���� ������ ������� S
                    case SDLK_s:
                        //��������� ������� ������������ ����
                        MoveDown = false;

                        //��������� ���������� � ������ ����������, ��������� ������
                        Follow = false;

                        //���������� ����-�����������
                        angle = 260;
                        break;

                    //���� ������ ������� D
                    case SDLK_d:
                        //��������� ������� ������������ ������
                        MoveRight = false;

                        //��������� ���������� � ������ ����������, ��������� ������
                        Follow = false;

                        //���������� ����-�����������
                        angle = 180;
                        break;

                    //���� ������ ������� W
                    case SDLK_w:
                        //��������� ������� ������������ �����
                        MoveUp = false;

                        //��������� ���������� � ������ ����������, ��������� ������
                        Follow = false;

                        //���������� ����-�����������
                        angle = 90;
                        break;

                    default:
                        break;
                }

                break;

            default:
                break;


            break;
        }
/*
        //���� ������ ������� ���� ��� ���� ��������� � ��������
        if(csdl_setup->GetMainEvent()->type == SDL_MOUSEBUTTONDOWN || csdl_setup->GetMainEvent()->type == SDL_MOUSEMOTION)
        {
            //���� ������ ��� � �������� ��� �� � ��������
            if(csdl_setup->GetMainEvent()->button.button == SDL_BUTTON(SDL_BUTTON_LEFT) || csdl_setup->GetMainEvent()->button.button == SDL_BUTTON_LEFT)
            {
                //���������� ������ ����������
                Follow_Point_X = *CameraX - *MouseX + (csdl_setup->GetScreenWidth()/2);
                Follow_Point_Y = *CameraY - *MouseY + (csdl_setup->GetScreenHeight()/2);

                //������ "�������������" - �������
                Follow = true;
            }
        }
*/
    }
    //�������� �������� ������������ � ���������
    bool colldingWithObject = false;

    //����������� ������ 0,1 ���
    if (timeCheck4+100 < SDL_GetTicks())
    {
        //������� ������������ � ���������
        for (int i = 0; i < gameLVL->GetCharacters().size(); i++)
        {

            if (SpriteMainHero->isColliding(gameLVL->GetCharacters()[i]->getSprite()->GetCollisionRect()))
            {
                std::cout << "I'm colliding!" << std::endl;
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
                std::cout << "I'm colliding!" << std::endl;
            }

            //������ ������������ � ��������� - ON
            colldingWithObject = true;

            //���������� �������
            timeCheck = SDL_GetTicks();
        }

        //������� ������������ � ���������
        for (int i = 0; i < gameLVL->GetNormal().size(); i++)
        {

            if (SpriteMainHero->isColliding(gameLVL->GetNormal()[i]->getSprite()->GetCollisionRect()))
            {
                std::cout << "I'm colliding!" << std::endl;
            }

            //������ ������������ � ��������� - ON
            colldingWithObject = true;

            //���������� �������
            timeCheck = SDL_GetTicks();
        }

        //������� ������������ � ���������
        for (int i = 0; i < gameLVL->GetWtrig().size(); i++)
        {

            if (SpriteMainHero->isColliding(gameLVL->GetWtrig()[i]->getSprite()->GetCollisionRect()))
            {
                std::cout << "I'm colliding!" << std::endl;
            }

            //������ ������������ � ��������� - ON
            colldingWithObject = true;

            //���������� �������
            timeCheck = SDL_GetTicks();
        }

        //������� ������������ � ���������
        for (int i = 0; i < gameLVL->GetTrigger().size(); i++)
        {

            if (SpriteMainHero->isColliding(gameLVL->GetTrigger()[i]->getSprite()->GetCollisionRect()))
            {
                std::cout << "I'm colliding!" << std::endl;
            }

            //������ ������������ � ��������� - ON
            colldingWithObject = true;

            //���������� �������
            timeCheck = SDL_GetTicks();
        }

        //���������� �������
        timeCheck4 = SDL_GetTicks();
    }

    //������� �������� ������ 0,05 ���
    if (timeCheckMoving+50 < SDL_GetTicks() && (Follow || MoveDown || MoveLeft || MoveRight || MoveUp))
    {
        //������� �������� ��� ������� ������
        if (MoveLeft)
        {
            *CameraX = *CameraX + speed;
            Follow_Point_X = *CameraX;
            Follow_Point_Y = *CameraY;
        }
        if (MoveDown)
        {
            *CameraY = *CameraY - speed;
            Follow_Point_X = *CameraX;
            Follow_Point_Y = *CameraY;
        }
        if (MoveRight)
        {
            *CameraX = *CameraX - speed;
            Follow_Point_X = *CameraX;
            Follow_Point_Y = *CameraY;
        }
        if (MoveUp)
        {
            *CameraY = *CameraY + speed;;
            Follow_Point_X = *CameraX;
            Follow_Point_Y = *CameraY;
        }

        //������� ��������� �� ������ ����������
        distance = GetDistance(*CameraX, *CameraY, Follow_Point_X, Follow_Point_Y);

        //���� ��������� ������ 15 ��������, �� ���������� ��������
        if (distance < 15)
            stopAnimation = true;
        else
            stopAnimation = false;

        //���� ���������� ������ 15 ��������
        if (distance > 15)
        {
            //������� �������� ��� �������� ������
            if (*CameraX != Follow_Point_X)
            {
                *CameraX = *CameraX - ((*CameraX - Follow_Point_X) / distance)*speed;
            }
            if (*CameraY != Follow_Point_Y)
            {
                *CameraY = *CameraY - ((*CameraY - Follow_Point_Y) / distance )*speed;
            }
        }
        else
            Follow = false;

        //���������� ������� ��������
        timeCheckMoving = SDL_GetTicks();
    }


}

void MainCharacter::Update()
{

    //�������� ��������� ��������
    UpdateAnimation();

    //�������� ����������
    UpdateControls();

    //��������� ������ ����������
    SendInfoToInterface();
}

void MainCharacter::Draw()
{
    //���������� ������ ��
    SpriteMainHero->DrawSteady();
}

double MainCharacter::GetDistance(int X1, int Y1, int X2, int Y2)
{
	double DifferenceX = X1 - X2;
	double DifferenceY = Y1 - Y2;
	double distance = sqrt((DifferenceX * DifferenceX) + (DifferenceY * DifferenceY));
	return distance;
}
