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

    //создается поток файловый для чтения
    std::ifstream LoadedFile(("data/configs/" + className).c_str());

    //инициализация переменной-строки для чтения конфигов
    std::string line;

    //если файл был успешно открыт
    if (LoadedFile.is_open())
    {
        //выполнять до тех пор, пока нет ошибок
        while ( LoadedFile.good() )
        {
            //считать строку из файла
            std::getline(LoadedFile, line);

            //добаляет в поток строку из string
            std::istringstream iss(line);

            //создание временных переменных
            std::string TempNameAnimation;
            int TempBeginFrame = 0;
            int TempEndFrame = 0;
            int TempRow = 0;
            int TempSpeed = 0;

            //переменные "предыдущее слово в строке" и "первое слово в строке"
            std::string PreviousWord;
            std::string FirstWord;

            //пока не строка не закончилась
            while (iss)
            {
                //текущее слово
                std::string word;

                //текущее слово вставляется из потока
                iss >> word;

                //если предыдущее слово ID:
                if (PreviousWord == "ID:")
                {
                    //если написанный ID соответствует нужному, то начинается загрузка параметров
                    if (ID == atoi(word.c_str()))
                    {
                        //считываем новую строку
                        std::getline(LoadedFile, line);

                        //добаляет в поток строку из string
                        std::istringstream iss(line);

                        //считываем данные до тех пор, пока не встретим "-"
                        while(line != "-")
                        {
                            //считываем новую строку
                            std::getline(LoadedFile, line);

                            //добаляет в поток строку из string
                            std::istringstream iss(line);

                            //сбрасываем "первое слово в строке"
                            FirstWord = "";

                            //пока не строка не закончилась
                            while(iss)
                            {
                                //текущее слово вставляется из потока
                                iss >> word;

                                //если предыдущее слово Collision:, то считать местоположение картинки для спрайта
                                if (PreviousWord == "Collision:")
                                    Collision = bool(word.c_str());

                                else if (PreviousWord == "BulletCollision:")
                                    BulletCollision = bool(word.c_str());



                                //если первое слово еще не заполнено, то записать его
                                if(FirstWord.begin() == FirstWord.end())
                                    FirstWord = word;

                                //предыдущее слово приравнять к текущему
                                PreviousWord = word;
                            }
                        }
                    }
                }
                //предыдущее слово приравнять к текущему
                PreviousWord = word;
            }


        }
    }
    else // в случае невозможности открыть файл - выдать ошибку
    {
        std::cout << "File could not be open "<< std::endl;
    }
}
