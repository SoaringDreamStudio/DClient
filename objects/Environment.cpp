#include "Environment.h"
Environment::Environment(std::string passed_className,
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
                        std::map<std::string, AnimationInfo> passed_Animations)
{
    className = passed_className;
    spawn = passed_spawn;
    CameraX = passed_CameraX;
    CameraY = passed_CameraY;
    csdl_setup = passed_csdl_setup;
    hitbox = passed_Hitbox;
    ExistOnMap = passed_ExistOnMap;
    ID = passed_ID;
    PosX = passed_PosX;
    PosY = passed_PosY;
    ActiveAnimation = passed_ActiveAnimation;
    Animations = passed_Animations;
    LoadConfigs();
    image = new CSprite(csdl_setup->GetRenderer(),
                        FilePathSprite,
                        Rect.x,
                        Rect.y,
                        Rect.w,
                        Rect.h,
                        CameraX,
                        CameraY,
                        CCollisionRectangle(hitbox.x,hitbox.y,hitbox.w,hitbox.h),
                        csdl_setup );
}

Environment::Environment(std::string passed_className,
                        float* passed_CameraX,
                        float* passed_CameraY,
                        coordinates* passed_spawn,
                        CSDL_Setup* passed_csdl_setup,
                        int passed_ID,
                        int passed_PosX,
                        int passed_PosY)
{
    className = passed_className;
    CameraX = passed_CameraX;
    CameraY = passed_CameraY;
    spawn = passed_spawn;
    csdl_setup = passed_csdl_setup;
    ID = passed_ID;
    PosX = passed_PosX;
    PosY = passed_PosY;
    LoadConfigs();
    Rect.x = PosX;
    Rect.y = PosY;
    image = new CSprite(csdl_setup->GetRenderer(),
                        FilePathSprite,
                        Rect.x,
                        Rect.y,
                        Rect.w,
                        Rect.h,
                        CameraX,
                        CameraY,
                        CCollisionRectangle(hitbox.x,hitbox.y,hitbox.w,hitbox.h),
                        csdl_setup );
}

Environment::~Environment(void)
{

}

void Environment::LoadConfigs(void)
{
    if(!(className != "Characters" ||
       className != "Ground" ||
       className != "Mobs" ||
       className != "Normal" ||
       className != "Trigger" ||
       className != "Wtrig" ))
        std::cout << "Class not detected" << std::endl << "Ur: " << className << std::endl;

    //��������� ����� �������� ��� ������
    std::ifstream LoadedFile(("data/configs/" + className + ".dat").c_str());

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
                                        Animations[TempNameAnimation] = tmpAI;
                                    }
                                }

                                //���� ������ ����� � ������ hitbox:
                                else if (FirstWord == "hitbox:")
                                {
                                    //���� ���������� ����� x:, �� �������� �������� �
                                    if (PreviousWord == "x:")
                                        hitbox.x = Rect.x*(static_cast<float>(atoi(word.c_str()))/100);

                                    //���� ���������� ����� y:, �� �������� �������� y
                                    if (PreviousWord == "y:")
                                        hitbox.y = Rect.y*(static_cast<float>(atoi(word.c_str()))/100);

                                    //���� ���������� ����� w:, �� �������� �������� w
                                    if (PreviousWord == "w:")
                                        hitbox.w = Rect.w*(static_cast<float>(atoi(word.c_str()))/100);

                                    //���� ���������� ����� h:, �� �������� �������� h
                                    if (PreviousWord == "h:")
                                        hitbox.h = Rect.h*(static_cast<float>(atoi(word.c_str()))/100);
                                }

                                //���� ���������� ����� FilePathSprite:, �� ������� �������������� �������� ��� �������
                                else if (PreviousWord == "FilePathSprite:")
                                    FilePathSprite = word;

                                //���� ���������� ����� SetCrops:, �� ������� ������ �� ������� �� ����� �������� ��� �������
                                else if (PreviousWord == "SetCrops:")
                                {
                                    SpriteCropX = atoi(word.c_str());
                                    iss >> word;
                                    SpriteCropY = atoi(word.c_str());
                                }
                                //���� ���������� ����� SetCrops:, �� ������� ������ �� ������� �� ����� �������� ��� �������
                                else if (PreviousWord == "Size:")
                                {
                                    Rect.w = atoi(word.c_str());
                                    iss >> word;
                                    Rect.h = atoi(word.c_str());
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
