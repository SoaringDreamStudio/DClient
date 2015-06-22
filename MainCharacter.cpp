#include "MainCharacter.h"

MainCharacter::MainCharacter(std::string passed_NickName, CSDL_Setup* passed_SDL_Setup, int *passed_MouseX, int *passed_MouseY, float *passed_CameraX, float *passed_CameraY, LoadingProcess* loadingProcess, GameInterface* passed_gameInterface, net::Socket* passed_gsocket)
{
    gsocket = passed_gsocket;
    NickName = passed_NickName;
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

    staticSpeed = 1;
	speed = 1;

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
    tmpW = 79; //размер спрайта игрока
    tmpH = 98;
	SpriteMainHero = new CSprite(csdl_setup->GetRenderer(),"data/img/Characters/hero.png", (csdl_setup->GetScreenWidth()/2), (csdl_setup->GetScreenHeight()/2), tmpW, tmpH, CameraX, CameraY,
                   CCollisionRectangle(41,98,79,98), csdl_setup);
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




    onceSendDirection = true;
    lastDirection = down;
}


MainCharacter::~MainCharacter(void)
{
    delete SpriteMainHero;

}

void MainCharacter::SendInfoToInterface()
{
    gameInterface->UpdateInformation(HP, maxHP);
}

void MainCharacter::UpdateAnimation() //Обновление анимации главного героя
{

    //какие-то вычисления для определения угла-направления пункта назначения
    //angle = atan2(Follow_Point_Y - *CameraY, Follow_Point_X - *CameraX);
    //angle = (angle * (180/3.14)) + 180;

    //Если герой двигается в определенном направлении, то выдать соответствующую анимацию
    //Движение по клавишам

    if (MoveRight && MoveLeft && MoveUp)
    {
        SpriteMainHero->PlayAnimation(0, 3, 0, 250);
        lastDirection = up;
    }
    else if (MoveRight && MoveLeft && MoveDown)
    {
        SpriteMainHero->PlayAnimation(0, 3, 3, 250);
        lastDirection = down;
    }
    else if (MoveUp && MoveDown && MoveRight)
    {
        SpriteMainHero->PlayAnimation(0, 5, 2, 250);
        lastDirection = right;
    }
    else if (MoveUp && MoveDown && MoveLeft)
    {
        SpriteMainHero->PlayAnimation(0, 5, 1, 250);
        lastDirection = left;
    }
    else if (MoveRight && MoveLeft)
    {
        lastDirection = down;
    }
    else if (MoveUp && MoveDown)
    {
        lastDirection = down;
    }
    else if (MoveRight)
    {
        SpriteMainHero->PlayAnimation(0, 5, 2, 250);
        lastDirection = right;
    }
    else if (MoveUp)
    {
        SpriteMainHero->PlayAnimation(0, 3, 0, 250);
        lastDirection = up;
    }
    else if (MoveLeft)
    {
        SpriteMainHero->PlayAnimation(0, 5, 1, 250);
        lastDirection = left;
    }
    else if (MoveDown)
    {
        SpriteMainHero->PlayAnimation(0, 3, 3, 250);
        lastDirection = down;
    }

    //Если анимация не остановлена
    if (!stopAnimation)
    {
        //движение по мышке
        if ((angle <=360 && angle >315) || (angle >=0 && angle <= 45))//left
        {
            if (distance < 20)
                SpriteMainHero->PlayAnimation(1, 1, 1, 250);
            else
                SpriteMainHero->PlayAnimation(0, 2, 1, 250);
        }
        else if (angle > 45 && angle <=135)//up
        {
            if (distance < 20)
                SpriteMainHero->PlayAnimation(1, 1, 0, 250);
            else
                SpriteMainHero->PlayAnimation(0, 2, 0, 250);
        }
        else if (angle > 135 && angle <=225)//right
        {

            if (distance < 20)
                SpriteMainHero->PlayAnimation(1, 1, 2, 250);
            else
                SpriteMainHero->PlayAnimation(0, 2, 2, 250);

        }
        else if (angle > 225 && angle <= 315)//down
        {

            if (distance < 20)
                SpriteMainHero->PlayAnimation(1, 1, 3, 250);
            else
                SpriteMainHero->PlayAnimation(0, 2, 3, 250);

        }
    }
}

void MainCharacter::UpdateControls()
{
    //всегда работает не зависимо от консоли
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

        //если происходит какое-то событие
        switch (csdl_setup->GetMainEvent()->type)
        {
            //если нажата клавиша
            case SDL_KEYDOWN:
                switch (csdl_setup->GetMainEvent()->key.keysym.sym)
                {
                    //если нажата клавиша A
                    case SDLK_a:
                        //включить триггер передвижения налево
                        MoveLeft = true;
                        break;
                    //если нажата клавиша S
                    case SDLK_s:
                        //включить триггер передвижения вниз
                        MoveDown = true;
                        break;
                    //если нажата клавиша D
                    case SDLK_d:
                        //включить триггер передвижения направо
                        MoveRight = true;
                        break;
                    //если нажата клавиша W
                    case SDLK_w:
                        //включить триггер передвижения вверх
                        MoveUp = true;
                        break;
                    default:
                        break;
                }

                break;

            //если отпущена клавиша (отдельный блок для считывания движения)
            case SDL_KEYUP:
                switch (csdl_setup->GetMainEvent()->key.keysym.sym)
                {
                    //если нажата клавиша A
                    case SDLK_a:
                        //выключить триггер передвижения влево
                        MoveLeft = false;

                        //выключить следование к пункту назначения, указанным мышкой
                        Follow = false;

                        //установить угол-направления
                        angle = 0;
                        break;

                    //если нажата клавиша S
                    case SDLK_s:
                        //выключить триггер передвижения вниз
                        MoveDown = false;

                        //выключить следование к пункту назначения, указанным мышкой
                        Follow = false;

                        //установить угол-направления
                        angle = 260;
                        break;

                    //если нажата клавиша D
                    case SDLK_d:
                        //выключить триггер передвижения вправо
                        MoveRight = false;

                        //выключить следование к пункту назначения, указанным мышкой
                        Follow = false;

                        //установить угол-направления
                        angle = 180;
                        break;

                    //если нажата клавиша W
                    case SDLK_w:
                        //выключить триггер передвижения вверх
                        MoveUp = false;

                        //выключить следование к пункту назначения, указанным мышкой
                        Follow = false;

                        //установить угол-направления
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
        //Если нажата клавиша мыши или мышь находится в движении
        if(csdl_setup->GetMainEvent()->type == SDL_MOUSEBUTTONDOWN || csdl_setup->GetMainEvent()->type == SDL_MOUSEMOTION)
        {
            //если нажата ЛКМ в движении или не в движении
            if(csdl_setup->GetMainEvent()->button.button == SDL_BUTTON(SDL_BUTTON_LEFT) || csdl_setup->GetMainEvent()->button.button == SDL_BUTTON_LEFT)
            {
                //обновление пункта назначения
                Follow_Point_X = *CameraX - *MouseX + (csdl_setup->GetScreenWidth()/2);
                Follow_Point_Y = *CameraY - *MouseY + (csdl_setup->GetScreenHeight()/2);

                //тригер "преследования" - активен
                Follow = true;
            }
        }
*/
    }
    //создание тригерра столкновения с объектами
    bool colldingWithObject = false;

    //Выполняется каждые 0,1 сек
    if (timeCheck4+10 < SDL_GetTicks())
    {


        //обновление таймера
        timeCheck4 = SDL_GetTicks();
    }

    if (timeCheckMoving+50 < SDL_GetTicks() && (!Follow && !MoveDown && !MoveLeft && !MoveRight && !MoveUp))
    {
        if(lastDirection == left && !MoveLeft)
        {
            if(!onceSendDirection)
            {
                sendPosition("stopl");
                onceSendDirection = true;
            }
        }

        if(lastDirection == down && !MoveDown)
        {
            if(!onceSendDirection)
            {
                sendPosition("stopd");
                onceSendDirection = true;
            }
        }
        if(lastDirection == right && !MoveRight)
        {
            if(!onceSendDirection)
            {
                sendPosition("stopr");
                onceSendDirection = true;
            }
        }
        if(lastDirection == up && !MoveUp)
        {
            if(!onceSendDirection)
            {
                sendPosition("stopu");
                onceSendDirection = true;
            }
        }

        timeCheckMoving = SDL_GetTicks();
    }
    //просчет движения каждые 0,05 сек
    if (timeCheckMoving+16 < SDL_GetTicks() && (Follow || MoveDown || MoveLeft || MoveRight || MoveUp))
    {
        //просчет движения при нажатии клавиш
        if (MoveLeft)
        {
            *CameraX = *CameraX + speed;
            sendPosition("movel");
            onceSendDirection = false;
        }
        if (MoveDown)
        {
            *CameraY = *CameraY - speed;
            sendPosition("moved");
            onceSendDirection = false;
        }
        if (MoveRight)
        {
            *CameraX = *CameraX - speed;
            sendPosition("mover");
            onceSendDirection = false;
        }
        if (MoveUp)
        {
            *CameraY = *CameraY + speed;
            sendPosition("moveu");
            onceSendDirection = false;
        }


        //обновление таймера движения
        timeCheckMoving = SDL_GetTicks();
    }


}

void MainCharacter::Update()
{

    //обновить состояние анимации
    UpdateAnimation();

    //обновить управление
    UpdateControls();

    //отправить данные интерфейсу
    SendInfoToInterface();
}

void MainCharacter::Draw()
{
    //отрисовать спрайт ГГ
    SpriteMainHero->DrawSteady();
}

double MainCharacter::GetDistance(int X1, int Y1, int X2, int Y2)
{
	double DifferenceX = X1 - X2;
	double DifferenceY = Y1 - Y2;
	double distance = sqrt((DifferenceX * DifferenceX) + (DifferenceY * DifferenceY));
	return distance;
}

void MainCharacter::sendPosition(std::string ActiveAnimation)
{
    //std::cout << "Active " << ActiveAnimation << std:: endl;
    unsigned char data[33];
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
    data[9] = (unsigned char) ( int(*CameraX * -1) >> 24 );
    data[10] = (unsigned char) ( int(*CameraX * -1) >> 16 );
    data[11] = (unsigned char) ( int(*CameraX * -1) >> 8 );
    data[12] = (unsigned char) ( int(*CameraX * -1) );

    //Y
    data[13] = (unsigned char) ( int(*CameraY * -1) >> 24 );
    data[14] = (unsigned char) ( int(*CameraY * -1) >> 16 );
    data[15] = (unsigned char) ( int(*CameraY * -1) >> 8 );
    data[16] = (unsigned char) ( int(*CameraY * -1) );

    //NickName
    data[17] = (unsigned char) ( NickName[0]);
    data[18] = (unsigned char) ( NickName[1]);
    data[19] = (unsigned char) ( NickName[2]);
    data[20] = (unsigned char) ( NickName[3]);
    data[21] = (unsigned char) ( NickName[4]);
    data[22] = (unsigned char) ( NickName[5]);
    data[23] = (unsigned char) ( NickName[6]);
    data[24] = (unsigned char) ( NickName[7]);

    //ActiveAnimation
    if(0 < ActiveAnimation.size())
        data[25] = (unsigned char) ( ActiveAnimation[0]);
    else
        data[25] = (unsigned char) ( 0 );
    if(1 < ActiveAnimation.size())
        data[26] = (unsigned char) ( ActiveAnimation[1]);
    else
        data[26] = (unsigned char) ( 0 );
    if(2 < ActiveAnimation.size())
        data[27] = (unsigned char) ( ActiveAnimation[2]);
    else
        data[27] = (unsigned char) ( 0 );
    if(3 < ActiveAnimation.size())
        data[28] = (unsigned char) ( ActiveAnimation[3]);
    else
        data[28] = (unsigned char) ( 0 );
    if(4 < ActiveAnimation.size())
        data[29] = (unsigned char) ( ActiveAnimation[4]);
    else
        data[29] = (unsigned char) ( 0 );
    if(5 < ActiveAnimation.size())
        data[30] = (unsigned char) ( ActiveAnimation[5]);
    else
        data[30] = (unsigned char) ( 0 );
    if(6 < ActiveAnimation.size())
        data[31] = (unsigned char) ( ActiveAnimation[6]);
    else
        data[31] = (unsigned char) ( 0 );
    if(7 < ActiveAnimation.size())
        data[32] = (unsigned char) ( ActiveAnimation[7]);
    else
        data[32] = (unsigned char) ( 0 );



    for(std::map<unsigned int, net::Connection*>::iterator it = gsocket->getConnections().begin(); it != gsocket->getConnections().end(); ++it)
    {
        //std::cout << "server: " << it->first << std::endl;
        if(it->first != 1)
            it->second->Send(data, 33 );
    }
}


int MainCharacter::getDirection()
{
    if ((!MoveLeft &&  !MoveDown && !MoveRight && MoveUp) ||
        (MoveLeft &&  !MoveDown && MoveRight && MoveUp))
    {
        return 0;
    }
    else if (!MoveLeft &&  !MoveDown && MoveRight && MoveUp)
    {
        return 1;
    }
    else if ((!MoveLeft &&  !MoveDown && MoveRight && !MoveUp) ||
            (!MoveLeft &&  MoveDown && MoveRight && MoveUp))
    {
        return 2;
    }
    else if (!MoveLeft &&  MoveDown && MoveRight && !MoveUp)
    {
        return 3;
    }
    else if ((!MoveLeft &&  MoveDown && !MoveRight && !MoveUp) ||
            (MoveLeft &&  MoveDown && MoveRight && !MoveUp))
    {
        return 4;
    }
    else if (MoveLeft &&  MoveDown && !MoveRight && !MoveUp)
    {
        return 5;
    }
    else if ((MoveLeft &&  !MoveDown && !MoveRight && !MoveUp) ||
            (MoveLeft &&  MoveDown && !MoveRight && MoveUp))
    {
        return 6;
    }
    else if (MoveLeft &&  !MoveDown && !MoveRight && MoveUp)
    {
        return 7;
    }
}
