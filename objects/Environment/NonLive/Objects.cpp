#include "Objects.h"

Objects::Objects(std::string passed_className,
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
                bool passed_Collision,
                bool passed_BulletCollision
                )
        : NonLive(  passed_className,
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
    Collision = passed_Collision;
    BulletCollision = passed_BulletCollision;
}

Objects::~Objects(void)
{

}

void Objects::LoadConfigs(void)
{
    if(className != "Characters" ||
       className != "Ground" ||
       className != "Mobs" ||
       className != "Normal" ||
       className != "Trigger" ||
       className != "Wtrig" )
        std::cout << "Class not detected";

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

                                //���� ���������� ����� Collision:, �� ������� �������������� �������� ��� �������
                                if (PreviousWord == "Collision:")
                                    Collision = bool(word.c_str());

                                else if (PreviousWord == "BulletCollision:")
                                    BulletCollision = bool(word.c_str());



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
        std::cout << "File could not be open "<< std::endl;
    }
}
