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
    //отрисовать объект
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

                                //если предыдущее слово fpX:, то считать местоположение картинки для спрайта
                                if (PreviousWord == "Aggressive:")
                                    Aggressive = bool(word.c_str());

                                //если первое слово в строке hitbox:
                                else if (FirstWord == "AgroRange:")
                                {
                                    //если предыдущее слово x:, то записать параметр х
                                    if (PreviousWord == "x:")
                                        AgroRange.x = Rect.x*(static_cast<float>(atoi(word.c_str()))/100);

                                    //если предыдущее слово y:, то записать параметр y
                                    if (PreviousWord == "y:")
                                        AgroRange.y = Rect.y*(static_cast<float>(atoi(word.c_str()))/100);

                                    //если предыдущее слово w:, то записать параметр w
                                    if (PreviousWord == "w:")
                                        AgroRange.w = Rect.w*(static_cast<float>(atoi(word.c_str()))/100);

                                    //если предыдущее слово h:, то записать параметр h
                                    if (PreviousWord == "h:")
                                        AgroRange.h = Rect.h*(static_cast<float>(atoi(word.c_str()))/100);
                                }



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
        std::cout << "File could not be open " << std::endl;
    }
}

