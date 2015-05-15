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

    //создается поток файловый для чтения
    std::ifstream LoadedFile(("data/configs/" + className + ".dat").c_str());

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
                                        Animations[TempNameAnimation] = tmpAI;
                                    }
                                }

                                //если первое слово в строке hitbox:
                                else if (FirstWord == "hitbox:")
                                {
                                    //если предыдущее слово x:, то записать параметр х
                                    if (PreviousWord == "x:")
                                        hitbox.x = Rect.x*(static_cast<float>(atoi(word.c_str()))/100);

                                    //если предыдущее слово y:, то записать параметр y
                                    if (PreviousWord == "y:")
                                        hitbox.y = Rect.y*(static_cast<float>(atoi(word.c_str()))/100);

                                    //если предыдущее слово w:, то записать параметр w
                                    if (PreviousWord == "w:")
                                        hitbox.w = Rect.w*(static_cast<float>(atoi(word.c_str()))/100);

                                    //если предыдущее слово h:, то записать параметр h
                                    if (PreviousWord == "h:")
                                        hitbox.h = Rect.h*(static_cast<float>(atoi(word.c_str()))/100);
                                }

                                //если предыдущее слово FilePathSprite:, то считать местоположение картинки для спрайта
                                else if (PreviousWord == "FilePathSprite:")
                                    FilePathSprite = word;

                                //если предыдущее слово SetCrops:, то считать данные об обрезке на кадры картинки для спрайта
                                else if (PreviousWord == "SetCrops:")
                                {
                                    SpriteCropX = atoi(word.c_str());
                                    iss >> word;
                                    SpriteCropY = atoi(word.c_str());
                                }
                                //если предыдущее слово SetCrops:, то считать данные об обрезке на кадры картинки для спрайта
                                else if (PreviousWord == "Size:")
                                {
                                    Rect.w = atoi(word.c_str());
                                    iss >> word;
                                    Rect.h = atoi(word.c_str());
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
