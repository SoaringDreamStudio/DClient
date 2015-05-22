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
    tmpW = 97; //размер спрайта игрока
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

void MainCharacter::UpdateAnimation() //Обновление анимации главного героя
{

    //какие-то вычисления для определения угла-направления пункта назначения
    angle = atan2(Follow_Point_Y - *CameraY, Follow_Point_X - *CameraX);
    angle = (angle * (180/3.14)) + 180;

    //Если герой двигается в определенном направлении, то выдать соответствующую анимацию
    //Движение по клавишам

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

    //Если анимация не остановлена
    if (!stopAnimation)
    {
        //движение по мышке
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
    if (timeCheck4+100 < SDL_GetTicks())
    {
        //просчет столкновений с объектами
        for (int i = 0; i < gameLVL->GetCharacters().size(); i++)
        {

            if (SpriteMainHero->isColliding(gameLVL->GetCharacters()[i]->getSprite()->GetCollisionRect()))
            {
                std::cout << "I'm colliding!" << std::endl;
            }

            //тригер столкновения с объектами - ON
            colldingWithObject = true;

            //обновление таймера
            timeCheck = SDL_GetTicks();
        }

        //просчет столкновений с объектами
        for (int i = 0; i < gameLVL->GetMobs().size(); i++)
        {

            if (SpriteMainHero->isColliding(gameLVL->GetMobs()[i]->getSprite()->GetCollisionRect()))
            {
                std::cout << "I'm colliding!" << std::endl;
            }

            //тригер столкновения с объектами - ON
            colldingWithObject = true;

            //обновление таймера
            timeCheck = SDL_GetTicks();
        }

        //просчет столкновений с объектами
        for (int i = 0; i < gameLVL->GetNormal().size(); i++)
        {

            if (SpriteMainHero->isColliding(gameLVL->GetNormal()[i]->getSprite()->GetCollisionRect()))
            {
                std::cout << "I'm colliding!" << std::endl;
            }

            //тригер столкновения с объектами - ON
            colldingWithObject = true;

            //обновление таймера
            timeCheck = SDL_GetTicks();
        }

        //просчет столкновений с объектами
        for (int i = 0; i < gameLVL->GetWtrig().size(); i++)
        {

            if (SpriteMainHero->isColliding(gameLVL->GetWtrig()[i]->getSprite()->GetCollisionRect()))
            {
                std::cout << "I'm colliding!" << std::endl;
            }

            //тригер столкновения с объектами - ON
            colldingWithObject = true;

            //обновление таймера
            timeCheck = SDL_GetTicks();
        }

        //просчет столкновений с объектами
        for (int i = 0; i < gameLVL->GetTrigger().size(); i++)
        {

            if (SpriteMainHero->isColliding(gameLVL->GetTrigger()[i]->getSprite()->GetCollisionRect()))
            {
                std::cout << "I'm colliding!" << std::endl;
            }

            //тригер столкновения с объектами - ON
            colldingWithObject = true;

            //обновление таймера
            timeCheck = SDL_GetTicks();
        }

        //обновление таймера
        timeCheck4 = SDL_GetTicks();
    }

    //просчет движения каждые 0,05 сек
    if (timeCheckMoving+50 < SDL_GetTicks() && (Follow || MoveDown || MoveLeft || MoveRight || MoveUp))
    {
        //просчет движения при нажатии клавиш
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

        //просчет дистанции до пункта назначения
        distance = GetDistance(*CameraX, *CameraY, Follow_Point_X, Follow_Point_Y);

        //если дистанция меньше 15 пикселей, то остановить анимацию
        if (distance < 15)
            stopAnimation = true;
        else
            stopAnimation = false;

        //если дисктанция больше 15 пикселей
        if (distance > 15)
        {
            //просчет движения при движении мышкой
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
