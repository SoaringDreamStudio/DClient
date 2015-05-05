
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
    //создается поток файловый для чтения
    std::ifstream LoadedFile(FilePath.c_str());

    //инициализация переменной-строки для чтения конфигов
    std::string line;

    //инициализация типа эффекта (осталось от чтения конфигов для игрового уровня)
    int CurrentType = TypeNone;

    //если файл был успешно открыт
    if (LoadedFile.is_open())
    {
        //выполнять до тех пор, пока нет ошибок
        while ( LoadedFile.good() )
        {
            //считать строку из файла
            std::getline(LoadedFile, line);

            //если линия Effects текущий тип - предмет
            if(line == "Effects:")
            {
                CurrentType = TypeItem;
            }

            //если линия end, то сбросить текущий тип
            else if (line == "end")
            {
                CurrentType = TypeNone;
            }

            //в других случаях
            else
            {
                //если текущий тип не пустой
                if(CurrentType != TypeNone)
                {
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

                                //инициализируется переменная для типа спрайта (infoSprite - для иконки, sprite - для различных эффектов около персонажа)
                                std::string SpriteType;

                                //считываем данные до тех пор, пока не встретим "-"
                                while(line != "-")
                                {
                                    //считываем новую строку
                                    std::getline(LoadedFile, line);

                                    //добаляет в поток строку из string
                                    std::istringstream iss(line);

                                    //если строка - infoSprite, то загружаем параметры для этого типа спрайта
                                    if(line == "infoSprite:")
                                        SpriteType = "infoSprite";

                                    //если строка - sprite, то загружаем параметры для этого типа спрайта
                                    else if(line == "sprite:")
                                        SpriteType = "sprite";

                                    //сбрасываем "первое слово в строке"
                                    FirstWord = "";

                                    //пока не строка не закончилась
                                    while(iss)
                                    {
                                        //текущее слово вставляется из потока
                                        iss >> word;

                                        //если первое слово в строке Animation
                                        if (FirstWord == "Animation:")
                                        {
                                            //если предыдущее слово name, то записываем слово во временную переменную
                                            if(PreviousWord == "name:")
                                                TempNameAnimation = word;

                                            //если предыдущее слово parameters
                                            if(PreviousWord == "parameters:")
                                            {
                                                //считываем номер начального кадра
                                                TempBeginFrame = atoi(word.c_str());

                                                //сдвигаемся на слово
                                                iss >> word;

                                                //считываем номер последнего кадра
                                                TempEndFrame = atoi(word.c_str());

                                                //сдвигаемся на слово
                                                iss >> word;

                                                //считываем номер ряда для кадров
                                                TempRow = atoi(word.c_str());

                                                //сдвигаемся на слово
                                                iss >> word;

                                                //считываем скорость анимации
                                                TempSpeed = atoi(word.c_str());

                                                //создаем переменную с информацией по анимации
                                                AnimationInfo tmpAI;

                                                //записываем считанные данные в переменную
                                                tmpAI.BeginFrame = TempBeginFrame;
                                                tmpAI.EndFrame = TempEndFrame;
                                                tmpAI.Row = TempRow;
                                                tmpAI.Speed = TempSpeed;

                                                //добавить данные о анимации в map анимаций
                                                animations[TempNameAnimation] = tmpAI;
                                            }
                                        }

                                        //если предыдущее и первое слово name, то записать название эффекта
                                        else if (PreviousWord == "name:" && FirstWord == "name:")
                                        {
                                            EffectName = word;
                                        }

                                        //если предыдующее слово HP, то считать эффект на HP
                                        else if (PreviousWord == "HP:")
                                        {
                                            HP = atoi(word.c_str());
                                        }

                                        //если предыдущее слово stack, включить или выключить возможность стака эффектов
                                        else if (PreviousWord == "stack: ")
                                        {
                                            if(word == "Off")
                                                statusStack = false;
                                            if(word == "On")
                                                statusStack = true;
                                        }

                                        //если предыдущее слово speed, то считать изменения скорости
                                        else if (PreviousWord == "speed:")
                                        {
                                            speed = atoi(word.c_str());
                                        }

                                        //если предыдущее слово FilePathSprite, то считать пути для спрайтов
                                        else if (PreviousWord == "FilePathSprite:")
                                        {
                                            //если активный тип спрайта - infoSprite, то записать путь для него
                                            if(SpriteType == "infoSprite")
                                            {
                                                FilePathSpriteInfo = word;
                                            }

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
        }
    }
    else // в случае невозможности открыть файл - выдать ошибку
    {
        std::cout << "File could not be open: " + FilePath << std::endl;
    }

}

void effect::Draw()
{
    //отрисовать spriteInfo
    spriteInfo->DrawStatic();
}
