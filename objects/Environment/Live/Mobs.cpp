#include "Mobs.h"
Mobs::Mobs(coordinates* passed_spawn,
            float* passed_CameraX,
            float* passed_CameraY,
            CSDL_Setup* passed_csdl_setup,
            SDL_Rect passed_Hitbox,
            bool passed_ExistOnMap,
            int passed_ID,
            int passed_PosX,
            int passed_PosY,
            std::string passed_ActiveAnimation,
            std::map<std::string, AnimationInfo> passed_Animations,
            int passed_fpX,
            int passed_fpY,
            int passed_HP,
            int passed_MS,
            int passed_Range,
            int passed_AttackDmg,
            int passed_Defense,
            int passed_AttackCDTime,
            int passed_AttackAnimationTime,
            bool passed_Aggressive,
            SDL_Rect passed_AgroRange
            )

    : Live("Mobs",
                passed_CameraX,
                passed_CameraY,
                passed_spawn,
                passed_csdl_setup,
                passed_Hitbox,
                passed_ExistOnMap,
                passed_ID,
                passed_PosX,
                passed_PosY,
                passed_ActiveAnimation,
                passed_Animations,
                passed_fpX,
                passed_fpY,
                passed_HP,
                passed_MS,
                passed_Range,
                passed_AttackDmg,
                passed_Defense,
                passed_AttackCDTime,
                passed_AttackAnimationTime)
{
    Aggressive = passed_Aggressive;
    AgroRange = passed_AgroRange;

}

Mobs::Mobs(coordinates* passed_spawn,
                        float* passed_CameraX,
                        float* passed_CameraY,
                        CSDL_Setup* passed_csdl_setup,
                        int passed_ID,
                        int passed_PosX,
                        int passed_PosY
                        )
        : Live("Mobs",
                passed_CameraX,
                passed_CameraY,
                passed_spawn,
                passed_csdl_setup,
                passed_ID,
                passed_PosX,
                passed_PosY)
{
    LoadConfigs();
}

Mobs::~Mobs(void)
{

}

void Mobs::Draw()
{
    //���������� ������
    image->DrawWithCoord(csdl_setup, *spawn);
}


void Mobs::LoadConfigs(void)
{
    if(!(className != "Characters" ||
       className != "Ground" ||
       className != "Mobs" ||
       className != "Normal" ||
       className != "Trigger" ||
       className != "Wtrig" ))
        std::cout << "Class not detected" << std::endl << "Ur: " << className << std::endl;


    //��������� ����� �������� ��� ������
    std::ifstream LoadedFile(("data/configs/" + className).c_str());

    //������������� ����������-������ ��� ������ ��������
    std::string line;

    //���� ���� ��� ������� ������
    if (LoadedFile.is_open())
    {
        //��������� �� ��� ���, ���� ��� ������
        while ( LoadedFile.good() )
        {
            //������� ������ �� �����
            std::getline(LoadedFile, line);

            //�������� � ����� ������ �� string
            std::istringstream iss(line);

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

                        //��������� ������ �� ��� ���, ���� �� �������� "-"
                        while(line != "-")
                        {
                            //��������� ����� ������
                            std::getline(LoadedFile, line);

                            //�������� � ����� ������ �� string
                            std::istringstream iss(line);

                            //���������� "������ ����� � ������"
                            FirstWord = "";

                            //���� �� ������ �� �����������
                            while(iss)
                            {
                                //������� ����� ����������� �� ������
                                iss >> word;

                                //���� ���������� ����� fpX:, �� ������� �������������� �������� ��� �������
                                if (PreviousWord == "Aggressive:")
                                    Aggressive = bool(word.c_str());

                                //���� ������ ����� � ������ hitbox:
                                else if (FirstWord == "AgroRange:")
                                {
                                    //���� ���������� ����� x:, �� �������� �������� �
                                    if (PreviousWord == "x:")
                                        AgroRange.x = Rect.x*(static_cast<float>(atoi(word.c_str()))/100);

                                    //���� ���������� ����� y:, �� �������� �������� y
                                    if (PreviousWord == "y:")
                                        AgroRange.y = Rect.y*(static_cast<float>(atoi(word.c_str()))/100);

                                    //���� ���������� ����� w:, �� �������� �������� w
                                    if (PreviousWord == "w:")
                                        AgroRange.w = Rect.w*(static_cast<float>(atoi(word.c_str()))/100);

                                    //���� ���������� ����� h:, �� �������� �������� h
                                    if (PreviousWord == "h:")
                                        AgroRange.h = Rect.h*(static_cast<float>(atoi(word.c_str()))/100);
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
    else // � ������ ������������� ������� ���� - ������ ������
    {
        std::cout << "File could not be open " << std::endl;
    }
}

