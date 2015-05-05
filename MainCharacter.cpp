#include "MainCharacter.h"

MainCharacter::MainCharacter(CSDL_Setup* passed_SDL_Setup, int *passed_MouseX, int *passed_MouseY, float *passed_CameraX, float *passed_CameraY, CEnviroment* passed_Enviroment, LoadingProcess* loadingProcess, GameInterface* passed_gameInterface)
{
    Enviroment = passed_Enviroment;
    gameInterface = passed_gameInterface;


    CameraX = passed_CameraX;
    CameraY = passed_CameraY;
    maxHP = 100;
    HP = 100;
    healAccumulation = 0;

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
    csdl_setup->End();
    //
    text1 = new Text(" ", "WHITE", (csdl_setup->GetScreenWidth()/2)+20, (csdl_setup->GetScreenHeight()/2)-80, 9, 9, csdl_setup, CameraX, CameraY, true);
    text2 = new Text(" ", "WHITE", (csdl_setup->GetScreenWidth()/2)+20, (csdl_setup->GetScreenHeight()/2)-90, 9, 9, csdl_setup, CameraX, CameraY, true);
    text3 = new Text(" ", "WHITE", (csdl_setup->GetScreenWidth()/2)+20, (csdl_setup->GetScreenHeight()/2)-100, 9, 9, csdl_setup, CameraX, CameraY, true);

    //
    csdl_setup->Begin();
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
	timeCheck2 = SDL_GetTicks();
	timeCheck4 = SDL_GetTicks();
	timeCheckMoving = SDL_GetTicks();
	Follow = false;
	distance = 0;
	stopAnimation = false;

    ///////////Голод//////////
    counterEmptyStomach = 0; //счетчик пустого желудка
                             //Если есть статус пустого желудка, то каждую секунду инкрементируется счетчик.
    timerCheckEmptyStomach = SDL_GetTicks();
    shortageTimer = SDL_GetTicks();       //Время начала игровой сессии(отсчет голода)
    counterShortage = 0;     //счетчик просчета. Как только он достигает 60000 - просчитать недостатки и обнулить
    shortageEnergy = 0;      //недостаток энергии. просчитывается из недостатков питательных веществ
    shortageProtein = 0;     //недостаток белка. Просчитывается каждые 12 игровых часов
    shortageCarbohydrate = 0;//недостаток углеводов
    shortageFat = 0;         //недостаток жира
    dayProtein = 0;          //количество потребленного белка
    dayCarbohydrate = 0;     //количество потребленных углеводов
    dayFat = 0;              //количество потребленных жиров
    sore = false;               //статус язвы


    /////////////////////////


    coordinates spawn = Enviroment->getSpawn();

    for(int i = 0; i < 10; i++)
    {
        timeCheck3.push_back(new int(SDL_GetTicks()));
        effectTime.push_back(new Text(" ", "WHITE", 1000, csdl_setup->GetScreenHeight()-(csdl_setup->GetScreenWidth()*0.35)*0.35 + csdl_setup->GetScreenWidth()*0.035-16, 15, 15, csdl_setup, CameraX, CameraY, true));
        effects.push_back(new effect(0, 0, 0, -1000, csdl_setup->GetScreenHeight()-(csdl_setup->GetScreenWidth()*0.35)*0.35, csdl_setup->GetScreenWidth()*0.035, csdl_setup->GetScreenWidth()*0.035, CameraX, CameraY, csdl_setup, &spawn));

        //
        csdl_setup->Begin();
        loadingProcess->addProcent(1);
        loadingProcess->Update();
        loadingProcess->Draw();
        csdl_setup->End();
        //
    }
}


MainCharacter::~MainCharacter(void)
{
    delete SpriteMainHero;

}

void MainCharacter::SendInfoToInterface()
{
    gameInterface->UpdateInformation(HP, maxHP, shortageEnergy,
                                        stomach.Empty(), sore);
}

void MainCharacter::UpdateAnimation() //Обновление анимации главного героя
{
    //обновить 3 строки изменения HP над персонажем
    text1->Update();
    text2->Update();
    text3->Update();

    //обновить отображение счетчика эффектов
    for (std::vector<Text*>::iterator i = effectTime.begin(); i != effectTime.end(); ++i)
    {
        (*i)->Update();
    }

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

    if (!(Enviroment->isconsoleActive()) && !escapeMenu)
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
        switch (csdl_setup->GetMainEvent()->type)
        {
            //Если нажата клавиша (отдельный блок для считывания функциональных клавиш)
            case SDL_KEYDOWN:
                //если клавиша еще не нажималась и она - Q
                if (!OnePressed && csdl_setup->GetMainEvent()->key.keysym.sym == SDLK_q)
                {
                    //создать объект умения
                    Enviroment->pushAbilityItems(1, -*CameraX + Enviroment->getSpawn().x - 97.0/4.0, -*CameraY + Enviroment->getSpawn().y - 65/2, 30, 30);

                    //триггер нажатия - активен
                    OnePressed = true;
                }
                break;

            //Если не нажата клавиша (отдельный блок для считывания функциональных клавиш)
            case SDL_KEYUP:
                //если клавиша нажималась и она - Q
                if (OnePressed && csdl_setup->GetMainEvent()->key.keysym.sym == SDLK_q)
                {
                    //триггер нажатия - не активен
                    OnePressed = false;
                }
                break;
        }

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

    }
    //создание тригерра столкновения с объектами
    bool colldingWithObject = false;

    //Выполняется каждые 0,5 сек
    if (timeCheck2+500 < SDL_GetTicks())
    {
        //сдвиг строки изменения HP
        text3->SetText(text2->GetText());
        text2->SetText(text1->GetText());

        //если нет изменения
        if(healAccumulation == 0)

            //первая строка изменения - пустая
            text1->SetText(" ");

        //если изменение положительно
        else if (healAccumulation > 0)
        {
            //создать строку с прогрессом
            std::string tmp = "+" + IntToStr(healAccumulation) + "HP";

            //записать созданную строку изменения HP
            text1->SetText(tmp);
        }

        //если изменение отрицательное
        else if (healAccumulation < 0)
        {
            //создать строку с прогрессом(минус не указывается, потому что в самом числе есть минус)
            std::string tmp = IntToStr(healAccumulation) + "HP";

            //записать созданную строку изменения HP
            text1->SetText(tmp);
        }

        //обнулить счетчик изменения HP
        healAccumulation = 0;

        //тик таймера
        timeCheck2 = SDL_GetTicks();
    }

    //Выполняется каждые 0,1 сек
    if (timeCheck4+100 < SDL_GetTicks())
    {
        //просчет координат отображения статуса на экране
        for(int f = 0; f < effects.size(); f++)
        {
            effects[f]->getSprite()->SetX((csdl_setup->GetScreenWidth()*0.40)+f*((csdl_setup->GetScreenWidth()*0.035)+((csdl_setup->GetScreenWidth()*0.01))));
            effectTime[f]->SetX(((csdl_setup->GetScreenWidth()*0.40)+f*((csdl_setup->GetScreenWidth()*0.035)+((csdl_setup->GetScreenWidth()*0.01))))+ csdl_setup->GetScreenWidth()*0.035-16);
        }

        //
        std::vector<int*>::iterator j = timeCheck3.begin();
        std::vector<Text*>::iterator k = effectTime.begin();
        for (std::vector<effect*>::iterator i = effects.begin(); i != effects.end(); ++i,++j,++k)
        {
            if((*i)->getID() > 0)
            {
                //обновление таймера встроенного в effect
                (*i)->setLifeTimer( (*i)->getLifeTimer() - (SDL_GetTicks() - *(*j) ) );

                //выставить текст таймера в секундах
                (*k)->SetText(IntToStr((*i)->getLifeTimer()/1000+1));

                //обновление таймера
                *(*j) = SDL_GetTicks();

                //если время жизни эффекта прошло
                if( ( (*i)->getLifeTimer() ) <= 0 )
                {
                    //количество статусов, действующих одновременно на персонажа ограничено 10
                    //поэтому при удалении статуса создается еще один с ID = 0

                    //ffresult - количество статусов с ненулевыми ID
                    int ffresult = -2;

                    for(int ff = effects.size(); ff > 0; ff--)
                    {
                        if(effects[ff-1]->getID() == 0)
                            ffresult = ff-1;
                    }

                    if(ffresult > effectTime.size()) //решение бага с некорректным отображением таймеров при удалении статусов
                    {
                        effectTime[ffresult]->SetText(" ");
                        effectTime[ffresult-1]->SetText(" ");
                    }
                    else
                        effectTime[ffresult]->SetText(" ");

                    //удаление эффекта и "сдвиг" всех параметров
                    effects.erase(i);
                    i--;
                    j--;
                    (*k)->SetText(" ");
                    k--;

                    //восстановление параметра скорости после окончания эффекта статуса
                    speed = staticSpeed;

                    //восполнение удаленного эффекта пустым
                    coordinates spawn = Enviroment->getSpawn();
                    effects.push_back(new effect(0, 0, 0, -1000, csdl_setup->GetScreenHeight()-(csdl_setup->GetScreenWidth()*0.35)*0.35, csdl_setup->GetScreenWidth()*0.035, csdl_setup->GetScreenWidth()*0.035, CameraX, CameraY, csdl_setup, &spawn));
                }
                else //просчет действия эффекта на персонажа
                {
                    //просчет скорости
                    speed = staticSpeed*(static_cast<float>((*i)->getSpeed())/100);

                    //просчет изменения HP
                    HP += (*i)->getHP();

                    //запись изменения HP для визуального отображения
                    healAccumulation += (*i)->getHP();

                    //запрет лечения, если достигнут максимальный порог HP
                    if(HP > maxHP)
                    {
                        healAccumulation = healAccumulation - (HP - maxHP);
                        HP = maxHP;
                    }
                }
            }
        }

        //просчет столкновений с объектами
        for (int i = 0; i < Enviroment->getItems().size(); i++)
        {
            if (SpriteMainHero->isColliding(Enviroment->getItems()[i]->getSprite()->GetCollisionRect()))
            {
                //при столкновении с объектом добавляется эффект
                //создание временного вектора эффектов для создания эффекта
                std::vector<EffectInfo*> tempEffects = Enviroment->getItems()[i]->getEffects();

                coordinates spawn = Enviroment->getSpawn();

                for (std::vector<EffectInfo*>::iterator z = tempEffects.begin(); z != tempEffects.end(); ++z)
                {
                    bool being = false;
                    for (std::vector<effect*>::iterator j = effects.begin(); j != effects.end(); ++j)
                    {
                        //если эффект от объекта уже существует, то обновить таймер
                        if ( (*j)->getEffectParent() == (*z)->getEffectParent() )
                        {
                            if(((*j)->getID() == (*z)->getID()))
                            {
                                (*j)->setLifeTimer( (*z)->getTime() );
                                being = true;
                            }
                        }
                    }
                    if(!being)
                    {
                        //количество статусов, действующих одновременно на персонажа ограничено 10
                        //поэтому при удалении статуса создается еще один с ID = 0

                        //ffresult - количество статусов с ненулевыми ID
                        int ffresult = -2;
                        for(int ff = effects.size(); ff > 0; ff--)
                        {
                            if(effects[ff-1]->getID() == 0)
                                ffresult = ff-1;
                        }
                        if(ffresult == -2)
                            std::cout << "Too many effects!" << std::endl;
                        else
                        {
                            //запись из временного вектора эффектов в свободную ячейку статусов
                            effects[ffresult]->setID((*z)->getID());
                            effects[ffresult]->setEffectParent((*z)->getEffectParent());
                            effects[ffresult]->setLifeTimer((*z)->getTime());
                            effects[ffresult]->LoadConfigs();
                            effects[ffresult]->getSprite()->SetImagePath(effects[ffresult]->getFilePathSpriteInfo());
                            effects[ffresult]->setLifeTimer( (*z)->getTime() );
                            *(timeCheck3[ffresult]) = SDL_GetTicks();
                        }
                    }
                }
            }

            //тригер столкновения с объектами - ON
            colldingWithObject = true;

            //обновление таймера
            timeCheck = SDL_GetTicks();
        }

        //просчет столкновений с объектами умений
        for (int i = 0; i < Enviroment->getAbilityItems().size(); i++)
        {
            if (SpriteMainHero->isColliding(Enviroment->getAbilityItems()[i]->getSprite()->GetCollisionRect()))
            {
                //при столкновении с объектом добавляется эффект
                //создание временного вектора эффектов для создания эффекта
                std::vector<EffectInfo*> tempEffects = Enviroment->getAbilityItems()[i]->getAnimationEffects()[Enviroment->getAbilityItems()[i]->getActiveAnimation()];

                coordinates spawn = Enviroment->getSpawn();

                for (std::vector<EffectInfo*>::iterator z = tempEffects.begin(); z != tempEffects.end(); ++z)
                {
                    bool being = false;
                    for (std::vector<effect*>::iterator j = effects.begin(); j != effects.end(); ++j)
                    {
                        //если эффект от объекта уже существует, то обновить таймер
                        if ( (*j)->getEffectParent() == (*z)->getEffectParent() )
                        {
                            (*j)->setLifeTimer( (*z)->getTime() );
                            if(((*j)->getID() == (*z)->getID()))
                            {
                                being = true;
                            }
                        }
                    }
                    if(!being)
                    {
                        //количество статусов, действующих одновременно на персонажа ограничено 10
                        //поэтому при удалении статуса создается еще один с ID = 0

                        //ffresult - количество статусов с ненулевыми ID
                        int ffresult = -2;
                        for(int ff = effects.size(); ff > 0; ff--)
                        {
                            if(effects[ff-1]->getID() == 0)
                                ffresult = ff-1;
                        }
                        if(ffresult == -2)
                            std::cout << "Too many effects!" << std::endl;
                        else
                        {
                            //запись из временного вектора эффектов в свободную ячейку статусов
                            effects[ffresult]->setID((*z)->getID());
                            effects[ffresult]->setEffectParent((*z)->getEffectParent());
                            effects[ffresult]->setLifeTimer((*z)->getTime());
                            effects[ffresult]->LoadConfigs();
                            effects[ffresult]->getSprite()->SetImagePath(effects[ffresult]->getFilePathSpriteInfo());
                            effects[ffresult]->setLifeTimer( (*z)->getTime() );
                            *(timeCheck3[ffresult]) = SDL_GetTicks();
                        }
                    }
                }
            }

            //тригер столкновения с объектами - ON
            colldingWithObject = true;

            //обновление таймера
            timeCheck = SDL_GetTicks();
        }

        //просчет столкновений с едой
        for (int i = 0; i < Enviroment->getFood().size(); i++)
        {
            if (SpriteMainHero->isColliding(Enviroment->getFood()[i]->getSprite()->GetCollisionRect()))
            {

                dayProtein += Enviroment->getFood()[i]->GetProtein();
                dayCarbohydrate += Enviroment->getFood()[i]->GetCarbohydrate();
                dayFat += Enviroment->getFood()[i]->GetFat();
                stomach.eating(Enviroment->getFood()[i]->GetEnergy());
                Enviroment->delFood(i);
                break;

            }
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
    if(nightTimer+850 < SDL_GetTicks())
    {
        if(Enviroment->isNight())
        {
            SpriteMainHero->SetImagePath("data/img/hero_n.png");
        }
        else
        {
            SpriteMainHero->SetImagePath("data/img/hero.png");
        }
        nightTimer = SDL_GetTicks();
    }

    //обновить состояние анимации
    UpdateAnimation();

    //обновить управление
    UpdateControls();

    //просчет голода
    counterShortage = SDL_GetTicks() - shortageTimer;     //счетчик просчета. Как только он достигает 600000 - просчитать недостатки и обнулить
    stomach.digest();

    if(counterShortage > 600000)
    {
        shortageTimer = SDL_GetTicks();
        //просчет недостатков

        if(dayProtein < 32)
        {
            shortageProtein += 32 - dayProtein;
            dayProtein = 0;
        }
        else
        {
            shortageProtein -= dayProtein - 32;
            if(shortageProtein < 0)
                shortageProtein = 0;
            dayProtein = 0;
        }
        if(dayCarbohydrate < 128)
        {
            shortageCarbohydrate += 128 - dayCarbohydrate;
            dayCarbohydrate = 0;
        }
        else
        {
            shortageCarbohydrate -= dayCarbohydrate - 128;
            if(shortageCarbohydrate < 0)
                shortageCarbohydrate = 0;
            dayCarbohydrate = 0;
        }
        if(dayFat < 35)
        {
            shortageFat += 35 - dayFat;
            dayFat = 0;
        }
        else
        {
            shortageFat -= dayFat - 35;
            if(shortageFat < 0)
                shortageFat = 0;
            dayFat = 0;
        }
        shortageEnergy = static_cast<int>(shortageProtein*4 + shortageCarbohydrate*3.75 + shortageFat*9);
    }

    if(timerCheckEmptyStomach+2000 < SDL_GetTicks() )
    {
        if(stomach.Empty())
            counterEmptyStomach += 2;
        else
        {
            counterEmptyStomach--;
            if(counterEmptyStomach < 0) counterEmptyStomach = 0;
        }
        timerCheckEmptyStomach = SDL_GetTicks();
    }
    if(counterEmptyStomach > 360000)
        sore = true;               //статус язвы

    //отправить данные интерфейсу
    SendInfoToInterface();
}

void MainCharacter::Draw()
{
    //отрисовать спрайт ГГ
    SpriteMainHero->DrawSteady();

    //отрисовать иконки статусов
    for (std::vector<effect*>::iterator i = effects.begin(); i != effects.end(); ++i)
    {
        (*i)->Draw();
    }

    //отрисовать таймеры статусов
    for (std::vector<Text*>::iterator i = effectTime.begin(); i != effectTime.end(); ++i)
    {
        if(atoi((*i)->GetText().c_str()) >= 0)
            (*i)->Draw();
    }

    //отрисовать строки изменения HP
    text1->Draw();
    text2->Draw();
    text3->Draw();
}

double MainCharacter::GetDistance(int X1, int Y1, int X2, int Y2)
{
	double DifferenceX = X1 - X2;
	double DifferenceY = Y1 - Y2;
	double distance = sqrt((DifferenceX * DifferenceX) + (DifferenceY * DifferenceY));
	return distance;
}
