
#include "effects.h"

effect::effect(int passed_ID, gameObject* passed_Parent, int passed_lifeTimer, int X, int Y, int W, int H, float *CameraX, float *CameraY, CSDL_Setup* passed_csdl_setup, coordinates* passed_spawn)
{
    csdl_setup = passed_csdl_setup;
    spawn = passed_spawn;
    ID = passed_ID;
    Rect.x = X;
    Rect.y = Y;
    Rect.w = W;
    Rect.h = H;
    EffectName = " ";
    lifeTimer = passed_lifeTimer;
    Parent = passed_Parent;
    //invisible = true;
    FilePath = "data/configs/effects.dat";
    //SpriteCropX = 0;
    //SpriteCropY = 0;
    LoadConfigs();
    spriteInfo = new CSprite(csdl_setup->GetRenderer(), FilePathSpriteInfo, Rect.x, Rect.y, Rect.w, Rect.h, CameraX, CameraY, CCollisionRectangle(), csdl_setup);
}

effect::~effect(void)
{

}

void effect::LoadConfigs()
{
    //��������� ����� �������� ��� ������
    std::ifstream LoadedFile(FilePath.c_str());

    //������������� ����������-������ ��� ������ ��������
    std::string line;

    //������������� ���� ������� (�������� �� ������ �������� ��� �������� ������)
    int CurrentType = TypeNone;

    //���� ���� ��� ������� ������
    if (LoadedFile.is_open())
    {
        //��������� �� ��� ���, ���� ��� ������
        while ( LoadedFile.good() )
        {
            //������� ������ �� �����
            std::getline(LoadedFile, line);

            //���� ����� Effects ������� ��� - �������
            if(line == "Effects:")
            {
                CurrentType = TypeItem;
            }

            //���� ����� end, �� �������� ������� ���
            else if (line == "end")
            {
                CurrentType = TypeNone;
            }

            //� ������ �������
            else
            {
                //���� ������� ��� �� ������
                if(CurrentType != TypeNone)
                {
                    //�������� � ����� ������ �� string
                    std::istringstream iss(line);

                    //�������� ��������� ����������
                    std::string TempNameAnimation;
                    int TempBeginFrame = 0;
                    int TempEndFrame = 0;
                    int TempRow = 0;
                    int TempSpeed = 0;

                    //���������� "���������� ����� � ������" � "������ ����� � ������"
                    std::string PreviousWord;
                    std::string FirstWord;

                    //���� �� ������ �� �����������
                    while (iss)
                    {
                        //������� �����
                        std::string word;

                        //������� ����� ����������� �� ������
                        iss >> word;

                        //���� ���������� ����� ID:
                        if (PreviousWord == "ID:")
                        {
                            //���� ���������� ID ������������� �������, �� ���������� �������� ����������
                            if (ID == atoi(word.c_str()))
                            {
                                //��������� ����� ������
                                std::getline(LoadedFile, line);

                                //�������� � ����� ������ �� string
                                std::istringstream iss(line);

                                //���������������� ���������� ��� ���� ������� (infoSprite - ��� ������, sprite - ��� ��������� �������� ����� ���������)
                                std::string SpriteType;

                                //��������� ������ �� ��� ���, ���� �� �������� "-"
                                while(line != "-")
                                {
                                    //��������� ����� ������
                                    std::getline(LoadedFile, line);

                                    //�������� � ����� ������ �� string
                                    std::istringstream iss(line);

                                    //���� ������ - infoSprite, �� ��������� ��������� ��� ����� ���� �������
                                    if(line == "infoSprite:")
                                        SpriteType = "infoSprite";

                                    //���� ������ - sprite, �� ��������� ��������� ��� ����� ���� �������
                                    else if(line == "sprite:")
                                        SpriteType = "sprite";

                                    //���������� "������ ����� � ������"
                                    FirstWord = "";

                                    //���� �� ������ �� �����������
                                    while(iss)
                                    {
                                        //������� ����� ����������� �� ������
                                        iss >> word;

                                        //���� ������ ����� � ������ Animation
                                        if (FirstWord == "Animation:")
                                        {
                                            //���� ���������� ����� name, �� ���������� ����� �� ��������� ����������
                                            if(PreviousWord == "name:")
                                                TempNameAnimation = word;

                                            //���� ���������� ����� parameters
                                            if(PreviousWord == "parameters:")
                                            {
                                                //��������� ����� ���������� �����
                                                TempBeginFrame = atoi(word.c_str());

                                                //���������� �� �����
                                                iss >> word;

                                                //��������� ����� ���������� �����
                                                TempEndFrame = atoi(word.c_str());

                                                //���������� �� �����
                                                iss >> word;

                                                //��������� ����� ���� ��� ������
                                                TempRow = atoi(word.c_str());

                                                //���������� �� �����
                                                iss >> word;

                                                //��������� �������� ��������
                                                TempSpeed = atoi(word.c_str());

                                                //������� ���������� � ����������� �� ��������
                                                AnimationInfo tmpAI;

                                                //���������� ��������� ������ � ����������
                                                tmpAI.BeginFrame = TempBeginFrame;
                                                tmpAI.EndFrame = TempEndFrame;
                                                tmpAI.Row = TempRow;
                                                tmpAI.Speed = TempSpeed;

                                                //�������� ������ � �������� � map ��������
                                                animations[TempNameAnimation] = tmpAI;
                                            }
                                        }

                                        //���� ���������� � ������ ����� name, �� �������� �������� �������
                                        else if (PreviousWord == "name:" && FirstWord == "name:")
                                        {
                                            EffectName = word;
                                        }

                                        //���� ����������� ����� HP, �� ������� ������ �� HP
                                        else if (PreviousWord == "HP:")
                                        {
                                            HP = atoi(word.c_str());
                                        }

                                        //���� ���������� ����� stack, �������� ��� ��������� ����������� ����� ��������
                                        else if (PreviousWord == "stack: ")
                                        {
                                            if(word == "Off")
                                                statusStack = false;
                                            if(word == "On")
                                                statusStack = true;
                                        }

                                        //���� ���������� ����� speed, �� ������� ��������� ��������
                                        else if (PreviousWord == "speed:")
                                        {
                                            speed = atoi(word.c_str());
                                        }

                                        //���� ���������� ����� FilePathSprite, �� ������� ���� ��� ��������
                                        else if (PreviousWord == "FilePathSprite:")
                                        {
                                            //���� �������� ��� ������� - infoSprite, �� �������� ���� ��� ����
                                            if(SpriteType == "infoSprite")
                                            {
                                                FilePathSpriteInfo = word;
                                            }

                                        }

                                        //���� ������ ����� ��� �� ���������, �� �������� ���
                                        if(FirstWord.begin() == FirstWord.end())
                                            FirstWord = word;

                                        //���������� ����� ���������� � ��������
                                        PreviousWord = word;
                                    }
                                }
                            }
                        }

                        //���������� ����� ���������� � ��������
                        PreviousWord = word;
                    }
                }
            }
        }
    }
    else // � ������ ������������� ������� ���� - ������ ������
    {
        std::cout << "File could not be open: " + FilePath << std::endl;
    }

}

void effect::Draw()
{
    //���������� spriteInfo
    spriteInfo->DrawStatic();
}
