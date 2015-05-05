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
	timeCheck2 = SDL_GetTicks();
	timeCheck4 = SDL_GetTicks();
	timeCheckMoving = SDL_GetTicks();
	Follow = false;
	distance = 0;
	stopAnimation = false;

    ///////////�����//////////
    counterEmptyStomach = 0; //������� ������� �������
                             //���� ���� ������ ������� �������, �� ������ ������� ���������������� �������.
    timerCheckEmptyStomach = SDL_GetTicks();
    shortageTimer = SDL_GetTicks();       //����� ������ ������� ������(������ ������)
    counterShortage = 0;     //������� ��������. ��� ������ �� ��������� 60000 - ���������� ���������� � ��������
    shortageEnergy = 0;      //���������� �������. �������������� �� ����������� ����������� �������
    shortageProtein = 0;     //���������� �����. �������������� ������ 12 ������� �����
    shortageCarbohydrate = 0;//���������� ���������
    shortageFat = 0;         //���������� ����
    dayProtein = 0;          //���������� ������������� �����
    dayCarbohydrate = 0;     //���������� ������������ ���������
    dayFat = 0;              //���������� ������������ �����
    sore = false;               //������ ����


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

void MainCharacter::UpdateAnimation() //���������� �������� �������� �����
{
    //�������� 3 ������ ��������� HP ��� ����������
    text1->Update();
    text2->Update();
    text3->Update();

    //�������� ����������� �������� ��������
    for (std::vector<Text*>::iterator i = effectTime.begin(); i != effectTime.end(); ++i)
    {
        (*i)->Update();
    }

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

    if (!(Enviroment->isconsoleActive()) && !escapeMenu)
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
        switch (csdl_setup->GetMainEvent()->type)
        {
            //���� ������ ������� (��������� ���� ��� ���������� �������������� ������)
            case SDL_KEYDOWN:
                //���� ������� ��� �� ���������� � ��� - Q
                if (!OnePressed && csdl_setup->GetMainEvent()->key.keysym.sym == SDLK_q)
                {
                    //������� ������ ������
                    Enviroment->pushAbilityItems(1, -*CameraX + Enviroment->getSpawn().x - 97.0/4.0, -*CameraY + Enviroment->getSpawn().y - 65/2, 30, 30);

                    //������� ������� - �������
                    OnePressed = true;
                }
                break;

            //���� �� ������ ������� (��������� ���� ��� ���������� �������������� ������)
            case SDL_KEYUP:
                //���� ������� ���������� � ��� - Q
                if (OnePressed && csdl_setup->GetMainEvent()->key.keysym.sym == SDLK_q)
                {
                    //������� ������� - �� �������
                    OnePressed = false;
                }
                break;
        }

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

    }
    //�������� �������� ������������ � ���������
    bool colldingWithObject = false;

    //����������� ������ 0,5 ���
    if (timeCheck2+500 < SDL_GetTicks())
    {
        //����� ������ ��������� HP
        text3->SetText(text2->GetText());
        text2->SetText(text1->GetText());

        //���� ��� ���������
        if(healAccumulation == 0)

            //������ ������ ��������� - ������
            text1->SetText(" ");

        //���� ��������� ������������
        else if (healAccumulation > 0)
        {
            //������� ������ � ����������
            std::string tmp = "+" + IntToStr(healAccumulation) + "HP";

            //�������� ��������� ������ ��������� HP
            text1->SetText(tmp);
        }

        //���� ��������� �������������
        else if (healAccumulation < 0)
        {
            //������� ������ � ����������(����� �� �����������, ������ ��� � ����� ����� ���� �����)
            std::string tmp = IntToStr(healAccumulation) + "HP";

            //�������� ��������� ������ ��������� HP
            text1->SetText(tmp);
        }

        //�������� ������� ��������� HP
        healAccumulation = 0;

        //��� �������
        timeCheck2 = SDL_GetTicks();
    }

    //����������� ������ 0,1 ���
    if (timeCheck4+100 < SDL_GetTicks())
    {
        //������� ��������� ����������� ������� �� ������
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
                //���������� ������� ����������� � effect
                (*i)->setLifeTimer( (*i)->getLifeTimer() - (SDL_GetTicks() - *(*j) ) );

                //��������� ����� ������� � ��������
                (*k)->SetText(IntToStr((*i)->getLifeTimer()/1000+1));

                //���������� �������
                *(*j) = SDL_GetTicks();

                //���� ����� ����� ������� ������
                if( ( (*i)->getLifeTimer() ) <= 0 )
                {
                    //���������� ��������, ����������� ������������ �� ��������� ���������� 10
                    //������� ��� �������� ������� ��������� ��� ���� � ID = 0

                    //ffresult - ���������� �������� � ���������� ID
                    int ffresult = -2;

                    for(int ff = effects.size(); ff > 0; ff--)
                    {
                        if(effects[ff-1]->getID() == 0)
                            ffresult = ff-1;
                    }

                    if(ffresult > effectTime.size()) //������� ���� � ������������ ������������ �������� ��� �������� ��������
                    {
                        effectTime[ffresult]->SetText(" ");
                        effectTime[ffresult-1]->SetText(" ");
                    }
                    else
                        effectTime[ffresult]->SetText(" ");

                    //�������� ������� � "�����" ���� ����������
                    effects.erase(i);
                    i--;
                    j--;
                    (*k)->SetText(" ");
                    k--;

                    //�������������� ��������� �������� ����� ��������� ������� �������
                    speed = staticSpeed;

                    //����������� ���������� ������� ������
                    coordinates spawn = Enviroment->getSpawn();
                    effects.push_back(new effect(0, 0, 0, -1000, csdl_setup->GetScreenHeight()-(csdl_setup->GetScreenWidth()*0.35)*0.35, csdl_setup->GetScreenWidth()*0.035, csdl_setup->GetScreenWidth()*0.035, CameraX, CameraY, csdl_setup, &spawn));
                }
                else //������� �������� ������� �� ���������
                {
                    //������� ��������
                    speed = staticSpeed*(static_cast<float>((*i)->getSpeed())/100);

                    //������� ��������� HP
                    HP += (*i)->getHP();

                    //������ ��������� HP ��� ����������� �����������
                    healAccumulation += (*i)->getHP();

                    //������ �������, ���� ��������� ������������ ����� HP
                    if(HP > maxHP)
                    {
                        healAccumulation = healAccumulation - (HP - maxHP);
                        HP = maxHP;
                    }
                }
            }
        }

        //������� ������������ � ���������
        for (int i = 0; i < Enviroment->getItems().size(); i++)
        {
            if (SpriteMainHero->isColliding(Enviroment->getItems()[i]->getSprite()->GetCollisionRect()))
            {
                //��� ������������ � �������� ����������� ������
                //�������� ���������� ������� �������� ��� �������� �������
                std::vector<EffectInfo*> tempEffects = Enviroment->getItems()[i]->getEffects();

                coordinates spawn = Enviroment->getSpawn();

                for (std::vector<EffectInfo*>::iterator z = tempEffects.begin(); z != tempEffects.end(); ++z)
                {
                    bool being = false;
                    for (std::vector<effect*>::iterator j = effects.begin(); j != effects.end(); ++j)
                    {
                        //���� ������ �� ������� ��� ����������, �� �������� ������
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
                        //���������� ��������, ����������� ������������ �� ��������� ���������� 10
                        //������� ��� �������� ������� ��������� ��� ���� � ID = 0

                        //ffresult - ���������� �������� � ���������� ID
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
                            //������ �� ���������� ������� �������� � ��������� ������ ��������
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

            //������ ������������ � ��������� - ON
            colldingWithObject = true;

            //���������� �������
            timeCheck = SDL_GetTicks();
        }

        //������� ������������ � ��������� ������
        for (int i = 0; i < Enviroment->getAbilityItems().size(); i++)
        {
            if (SpriteMainHero->isColliding(Enviroment->getAbilityItems()[i]->getSprite()->GetCollisionRect()))
            {
                //��� ������������ � �������� ����������� ������
                //�������� ���������� ������� �������� ��� �������� �������
                std::vector<EffectInfo*> tempEffects = Enviroment->getAbilityItems()[i]->getAnimationEffects()[Enviroment->getAbilityItems()[i]->getActiveAnimation()];

                coordinates spawn = Enviroment->getSpawn();

                for (std::vector<EffectInfo*>::iterator z = tempEffects.begin(); z != tempEffects.end(); ++z)
                {
                    bool being = false;
                    for (std::vector<effect*>::iterator j = effects.begin(); j != effects.end(); ++j)
                    {
                        //���� ������ �� ������� ��� ����������, �� �������� ������
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
                        //���������� ��������, ����������� ������������ �� ��������� ���������� 10
                        //������� ��� �������� ������� ��������� ��� ���� � ID = 0

                        //ffresult - ���������� �������� � ���������� ID
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
                            //������ �� ���������� ������� �������� � ��������� ������ ��������
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

            //������ ������������ � ��������� - ON
            colldingWithObject = true;

            //���������� �������
            timeCheck = SDL_GetTicks();
        }

        //������� ������������ � ����
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

    //�������� ��������� ��������
    UpdateAnimation();

    //�������� ����������
    UpdateControls();

    //������� ������
    counterShortage = SDL_GetTicks() - shortageTimer;     //������� ��������. ��� ������ �� ��������� 600000 - ���������� ���������� � ��������
    stomach.digest();

    if(counterShortage > 600000)
    {
        shortageTimer = SDL_GetTicks();
        //������� �����������

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
        sore = true;               //������ ����

    //��������� ������ ����������
    SendInfoToInterface();
}

void MainCharacter::Draw()
{
    //���������� ������ ��
    SpriteMainHero->DrawSteady();

    //���������� ������ ��������
    for (std::vector<effect*>::iterator i = effects.begin(); i != effects.end(); ++i)
    {
        (*i)->Draw();
    }

    //���������� ������� ��������
    for (std::vector<Text*>::iterator i = effectTime.begin(); i != effectTime.end(); ++i)
    {
        if(atoi((*i)->GetText().c_str()) >= 0)
            (*i)->Draw();
    }

    //���������� ������ ��������� HP
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
