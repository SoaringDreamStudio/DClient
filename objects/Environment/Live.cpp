#include "Live.h"

Live::Live(std::string passed_className,
            float* passed_CameraX,
            float* passed_CameraY,
            coordinates* passed_spawn,
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
            int passed_AttackAnimationTime)

        : Environment(passed_className,
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
                    passed_Animations)
{
    fpX = passed_fpX;
    fpY = passed_fpY;
    HP = passed_HP;
    MS = passed_MS;
    Range = passed_Range;
    AttackDmg = passed_AttackDmg;
    Defense = passed_Defense;
    AttackCDTime = passed_AttackCDTime;
    AttackAnimationTime = passed_AttackAnimationTime;
}

Live::Live(std::string passed_className,
            float* passed_CameraX,
            float* passed_CameraY,
            coordinates* passed_spawn,
            CSDL_Setup* passed_csdl_setup,
            int passed_ID,
            int passed_PosX,
            int passed_PosY)
    :Environment(passed_className,
                passed_CameraX,
                passed_CameraY,
                passed_spawn,
                passed_csdl_setup,
                passed_ID,
                passed_PosX,
                passed_PosY)

{

}

Live::~Live(void)
{

}

void Live::LoadConfigs(void)
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
                                if (PreviousWord == "fpX:")
                                    fpX = int(word.c_str());

                                else if (PreviousWord == "fpY:")
                                    fpY = int(word.c_str());
                                else if (PreviousWord == "HP:")
                                    HP = int(word.c_str());
                                else if (PreviousWord == "MS:")
                                    MS = int(word.c_str());
                                else if (PreviousWord == "Range:")
                                    Range = int(word.c_str());
                                else if (PreviousWord == "AttackDmg:")
                                    AttackDmg = int(word.c_str());
                                else if (PreviousWord == "Defense:")
                                    Defense = int(word.c_str());
                                else if (PreviousWord == "AttackCDTime:")
                                    AttackCDTime = int(word.c_str());
                                else if (PreviousWord == "AttackAnimationTime:")
                                    AttackAnimationTime = int(word.c_str());


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
