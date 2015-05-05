
#include "writing.h"


Text::Text(std::string passed_text, int x, int y, int w, int h, CSDL_Setup* passed_SDL_Setup, float *passed_CameraX, float *passed_CameraY)
{
    CameraX = passed_CameraX;
    CameraY = passed_CameraY;

    X = X;
    Y = y;
    W = w;
    H = h;

    text = passed_text;
    inv = false;
    linkText = 0;


    csdl_setup = passed_SDL_Setup;
    for(int i = 0; i < 30/*text.size()*/; i++)
    {
        letters.push_back(new CSprite(csdl_setup->GetRenderer(), "data/img/fontBlack1.png", x+i*w, y, w, h, CameraX, CameraY, CCollisionRectangle(), csdl_setup));
        //letters[i]->SetUpAnimation(16,3);
    }


}

Text::Text(std::string passed_text, std::string passed_color, int x, int y, int w, int h, CSDL_Setup* passed_SDL_Setup, float *passed_CameraX, float *passed_CameraY)
{
    CameraX = passed_CameraX;
    CameraY = passed_CameraY;

    X = X;
    Y = y;
    W = w;
    H = h;

    text = passed_text;
    inv = false;
    linkText = 0;

    color = passed_color;

    csdl_setup = passed_SDL_Setup;
    for(int i = 0; i < 30/*text.size()*/; i++)
    {
        if(color == "WHITE")
            letters.push_back(new CSprite(csdl_setup->GetRenderer(), "data/img/fontWhite1.png", x+i*w, y, w, h, CameraX, CameraY, CCollisionRectangle(), csdl_setup));
        else
            letters.push_back(new CSprite(csdl_setup->GetRenderer(), "data/img/fontBlack1.png", x+i*w, y, w, h, CameraX, CameraY, CCollisionRectangle(), csdl_setup));
        //letters[i]->SetUpAnimation(16,3);
    }


}

Text::Text(std::string* passed_text, int x, int y, int w, int h, CSDL_Setup* passed_SDL_Setup, float *passed_CameraX, float *passed_CameraY)
{
    CameraX = passed_CameraX;
    CameraY = passed_CameraY;

    X = X;
    Y = y;
    W = w;
    H = h;

    text = *passed_text;
    inv = false;
    linkText = passed_text;

    csdl_setup = passed_SDL_Setup;
    for(int i = 0; i < 30; i++)
    {
        letters.push_back(new CSprite(csdl_setup->GetRenderer(), "data/img/fontBlack1.png", x+i*w, y, w, h, CameraX, CameraY, CCollisionRectangle(), csdl_setup));
        //letters[i]->SetUpAnimation(16,3);
    }


}

Text::Text(std::string* passed_text, std::string passed_color, int x, int y, int w, int h, CSDL_Setup* passed_SDL_Setup, float *passed_CameraX, float *passed_CameraY)
{
    CameraX = passed_CameraX;
    CameraY = passed_CameraY;

    X = X;
    Y = y;
    W = w;
    H = h;

    text = *passed_text;
    inv = false;
    linkText = passed_text;

    color = passed_color;

    csdl_setup = passed_SDL_Setup;
    for(int i = 0; i < 30/*text.size()*/; i++)
    {
        if(color == "WHITE")
            letters.push_back(new CSprite(csdl_setup->GetRenderer(), "data/img/fontWhite1.png", x+i*w, y, w, h, CameraX, CameraY, CCollisionRectangle(), csdl_setup));
        else
            letters.push_back(new CSprite(csdl_setup->GetRenderer(), "data/img/fontBlack1.png", x+i*w, y, w, h, CameraX, CameraY, CCollisionRectangle(), csdl_setup));
        //letters[i]->SetUpAnimation(16,3);
    }


}

Text::Text(std::string passed_text, int x, int y, int w, int h, CSDL_Setup* passed_SDL_Setup, float *passed_CameraX, float *passed_CameraY, bool inverted)
{
    CameraX = passed_CameraX;
    CameraY = passed_CameraY;

    X = X;
    Y = y;
    W = w;
    H = h;

    text = passed_text;
    inv = inverted;
    linkText = 0;

    //std::cout << text.size();
    //std::cout << "Text: " << text << std::endl;

    csdl_setup = passed_SDL_Setup;
    int i, j;
    for(i = 30/*text.size()*/, j = 0; i > 0; i--, j++)
    {
        letters.push_back(new CSprite(csdl_setup->GetRenderer(), "data/img/fontBlack1.png", x-j*w, y, w, h, CameraX, CameraY, CCollisionRectangle(), csdl_setup));
        //letters[i]->SetUpAnimation(16,3);
    }


}

Text::Text(std::string passed_text, std::string passed_color, int x, int y, int w, int h, CSDL_Setup* passed_SDL_Setup, float *passed_CameraX, float *passed_CameraY, bool inverted)
{

    CameraX = passed_CameraX;
    CameraY = passed_CameraY;

    X = X;
    Y = y;
    W = w;
    H = h;

    text = passed_text;
    inv = inverted;
    linkText = 0;
    color = passed_color;
    //std::cout << " now : " << SDL_GetTicks() << std::endl;

    csdl_setup = passed_SDL_Setup;
    int i,j;
    for(i = 30/*text.size()*/, j = 0; i > 0; i--, j++)
    {

        //std::cout << " Checking type of" << j << " : " << SDL_GetTicks() << std::endl;
        if(color == "WHITE")
        {
            //std::cout << " Creating" << j << " letter : " << SDL_GetTicks() << std::endl;

            CSprite* p = new CSprite(csdl_setup->GetRenderer(), "data/img/fontWhite1.png", x-j*w, y, w, h, CameraX, CameraY, CCollisionRectangle(), csdl_setup);
            //std::cout << " Created texture of " << j << " letter : " << SDL_GetTicks() << std::endl;
            letters.push_back(p);

            //std::cout << " Created" << j << " letter : " << SDL_GetTicks() << std::endl;
        }
        else
            letters.push_back(new CSprite(csdl_setup->GetRenderer(), "data/img/fontBlack1.png", x-j*w, y, w, h, CameraX, CameraY, CCollisionRectangle(),csdl_setup));
        //letters[i]->SetUpAnimation(16,3);
    }

    //std::cout << " after create letters : " << SDL_GetTicks() << std::endl;


}

Text::Text(std::string* passed_text, int x, int y, int w, int h, CSDL_Setup* passed_SDL_Setup, float *passed_CameraX, float *passed_CameraY, bool inverted)
{
    CameraX = passed_CameraX;
    CameraY = passed_CameraY;

    X = X;
    Y = y;
    W = w;
    H = h;

    text = *passed_text;
    inv = inverted;
    linkText = passed_text;

    csdl_setup = passed_SDL_Setup;
    int i,j;
    for(i = 30, j = 0; i > 0; i--, j++)
    {
        letters.push_back(new CSprite(csdl_setup->GetRenderer(), "data/img/fontBlack1.png", x-j*w, y, w, h, CameraX, CameraY, CCollisionRectangle(), csdl_setup));
        //letters[i]->SetUpAnimation(16,3);
    }


}

Text::Text(std::string* passed_text, std::string passed_color, int x, int y, int w, int h, CSDL_Setup* passed_SDL_Setup, float *passed_CameraX, float *passed_CameraY, bool inverted)
{
    CameraX = passed_CameraX;
    CameraY = passed_CameraY;

    X = X;
    Y = y;
    W = w;
    H = h;

    text = *passed_text;
    inv = inverted;
    linkText = passed_text;

    color = passed_color;

    csdl_setup = passed_SDL_Setup;
    int i,j;
    for(i = 30, j = 0; i > 0; i--, j++)
    {
        if(color == "WHITE")
            letters.push_back(new CSprite(csdl_setup->GetRenderer(), "data/img/fontWhite1.png", x-j*w, y, w, h, CameraX, CameraY, CCollisionRectangle(0,0,300,100), csdl_setup));
        else
            letters.push_back(new CSprite(csdl_setup->GetRenderer(), "data/img/fontBlack1.png", x-j*w, y, w, h, CameraX, CameraY, CCollisionRectangle(0,0,300,100), csdl_setup));
        //letters[i]->SetUpAnimation(16,3);
    }


}


Text::~Text(void)
{

}

void Text::UpdateAnimation()
{

    int begin,j;
    if(inv == true)
    {
        begin = text.size()-1;
    }
    else
    {
        begin = 0;
    }
    for(int i = 0, j = begin; i < text.size(); i++ )
    {

        //std::cout << text.size() << std::endl;
        //std::cout << letters.size() << std::endl;
        //std::cout << begin << std::endl;
        //std::cout << i << std::endl;
        //std::cout << text[i] << std::endl;
        //std::cout << "(linkText != NULL) " << (linkText != NULL) << std::endl;
        //if(linkText != NULL)
        //{
        //std::cout << text.size() << std::endl;
        //std::cout << letters.size() << std::endl;
        //std::cout << text[i] << std::endl;
        //}
        if(text[j] == ' ')
            letters[i]->SetCrop(6, 26, -100, 33);
        if(text[j] == 'A' || text[i] == 'a')
            letters[i]->SetCrop(6, 26, 46, 33);
            //letters[i]->PlayAnimation(0, 0, 0, 10);
        if(text[j] == 'B' || text[i] == 'b')
            letters[i]->SetCrop(46, 26, 46, 33);
            //letters[i]->PlayAnimation(1, 1, 0, 10);
        if(text[j] == 'C' || text[i] == 'c')
            letters[i]->SetCrop(87, 26, 46, 33);
            //letters[i]->PlayAnimation(2, 2, 0, 10);
        if(text[j] == 'D' || text[i] == 'd')
            letters[i]->SetCrop(127, 26, 46, 33);
            //letters[i]->PlayAnimation(3, 3, 0, 10);
        if(text[j] == 'E' || text[i] == 'e')
            letters[i]->SetCrop(167, 26, 46, 33);
            //letters[i]->PlayAnimation(4, 4, 0, 10);
        if(text[j] == 'F' || text[i] == 'f')
            letters[i]->SetCrop(206, 26, 46, 33);
            //letters[i]->PlayAnimation(5, 5, 0, 10);
        if(text[j] == 'G' || text[i] == 'g')
            letters[i]->SetCrop(246, 26, 46, 33);
            //letters[i]->PlayAnimation(6, 6, 0, 10);
        if(text[j] == 'H' || text[i] == 'h')
            letters[i]->SetCrop(286, 26, 46, 33);
            //letters[i]->PlayAnimation(7, 7, 0, 10);
        if(text[j] == 'I' || text[i] == 'i')
            letters[i]->SetCrop(327, 26, 46, 33);
            //letters[i]->PlayAnimation(8, 8, 0, 10);
        if(text[j] == 'J' || text[i] == 'j')
            letters[i]->SetCrop(367, 26, 46, 33);
            //letters[i]->PlayAnimation(9, 9, 0, 10);
        if(text[j] == 'K' || text[i] == 'k')
            letters[i]->SetCrop(406, 26, 46, 33);
            //letters[i]->PlayAnimation(10, 10, 0, 10);
        if(text[j] == 'L' || text[i] == 'l')
            letters[i]->SetCrop(446, 26, 46, 33);
            //letters[i]->PlayAnimation(11, 11, 0, 10);
        if(text[j] == 'M' || text[i] == 'm')
            letters[i]->SetCrop(486, 26, 46, 33);
            //letters[i]->PlayAnimation(12, 12, 0, 10);
        if(text[j] == 'N' || text[i] == 'n')
            letters[i]->SetCrop(526, 26, 46, 33);
            //letters[i]->PlayAnimation(13, 13, 0, 10);
        if(text[j] == 'O' || text[i] == 'o')
            letters[i]->SetCrop(566, 26, 46, 33);
            //letters[i]->PlayAnimation(14, 14, 0, 10);
        if(text[j] == 'P' || text[i] == 'p')
            letters[i]->SetCrop(606, 26, 46, 33);
            //letters[i]->PlayAnimation(15, 15, 0, 10);

        if(text[j] == 'Q' || text[i] == 'q')
            letters[i]->SetCrop(6, 88, 46, 33);
            //letters[i]->PlayAnimation(0, 0, 0, 10);
        if(text[j] == 'R' || text[i] == 'r')
            letters[i]->SetCrop(46, 90, 46, 33);
            //letters[i]->PlayAnimation(1, 1, 0, 10);
        if(text[j] == 'S' || text[i] == 's')
            letters[i]->SetCrop(87, 90, 46, 33);
            //letters[i]->PlayAnimation(2, 2, 0, 10);
        if(text[j] == 'T' || text[i] == 't')
            letters[i]->SetCrop(127, 90, 46, 33);
            //letters[i]->PlayAnimation(3, 3, 0, 10);
        if(text[j] == 'U' || text[i] == 'u')
            letters[i]->SetCrop(167, 90, 46, 33);
            //letters[i]->PlayAnimation(4, 4, 0, 10);
        if(text[j] == 'V' || text[i] == 'v')
            letters[i]->SetCrop(206, 90, 46, 33);
            //letters[i]->PlayAnimation(5, 5, 0, 10);
        if(text[j] == 'W' || text[i] == 'w')
            letters[i]->SetCrop(246, 90, 46, 33);
            //letters[i]->PlayAnimation(6, 6, 0, 10);
        if(text[j] == 'X' || text[i] == 'x')
            letters[i]->SetCrop(286, 90, 46, 33);
            //letters[i]->PlayAnimation(7, 7, 0, 10);
        if(text[j] == 'Y' || text[i] == 'y')
            letters[i]->SetCrop(327, 90, 46, 33);
            //letters[i]->PlayAnimation(8, 8, 0, 10);
        if(text[j] == 'Z' || text[i] == 'z')
            letters[i]->SetCrop(367, 90, 46, 33);
            //letters[i]->PlayAnimation(9, 9, 0, 10);

        if(letters[i]->GetWidht() > 10 && text[j] == '1')
            letters[i]->SetCrop(6, 283, 46, 33);
            //letters[i]->PlayAnimation(0, 0, 0, 10);
        if(letters[i]->GetWidht() <= 10 && text[j] == '1')
            letters[i]->SetCrop(6, 640, 46, 33);
        if(letters[i]->GetWidht() > 10 && text[j] == '2')
            letters[i]->SetCrop(46, 283, 46, 33);
            //letters[i]->PlayAnimation(1, 1, 0, 10);
        if(letters[i]->GetWidht() <= 10 && text[j] == '2')
            letters[i]->SetCrop(46, 640, 46, 33);
        if(letters[i]->GetWidht() > 10 && text[j] == '3')
            letters[i]->SetCrop(87, 283, 46, 33);
            //letters[i]->PlayAnimation(2, 2, 0, 10);
        if(letters[i]->GetWidht() <= 10 && text[j] == '3')
            letters[i]->SetCrop(87, 640, 46, 33);
        if(letters[i]->GetWidht() > 10 && text[j] == '4')
            letters[i]->SetCrop(127, 283, 46, 33);
            //letters[i]->PlayAnimation(3, 3, 0, 10);
        if(letters[i]->GetWidht() <= 10 && text[j] == '4')
            letters[i]->SetCrop(127, 643, 46, 30);
        if(letters[i]->GetWidht() > 10 && text[j] == '5')
            letters[i]->SetCrop(167, 283, 46, 33);
            //letters[i]->PlayAnimation(4, 4, 0, 10);
        if(letters[i]->GetWidht() <= 10 && text[j] == '5')
            letters[i]->SetCrop(167, 640, 46, 33);
        if(letters[i]->GetWidht() > 10 && text[j] == '6')
            letters[i]->SetCrop(206, 283, 46, 33);
            //letters[i]->PlayAnimation(5, 5, 0, 10);
        if(letters[i]->GetWidht() <= 10 && text[j] == '6')
            letters[i]->SetCrop(206, 640, 46, 33);
        if(letters[i]->GetWidht() > 10 && text[j] == '7')
            letters[i]->SetCrop(246, 283, 46, 33);
            //letters[i]->PlayAnimation(6, 6, 0, 10);
        if(letters[i]->GetWidht() <= 10 && text[j] == '7')
            letters[i]->SetCrop(246, 640, 46, 33);
        if(letters[i]->GetWidht() > 10 && text[j] == '8')
            letters[i]->SetCrop(286, 283, 46, 33);
            //letters[i]->PlayAnimation(7, 7, 0, 10);
        if(letters[i]->GetWidht() <= 10 && text[j] == '8')
            letters[i]->SetCrop(286, 640, 46, 33);
        if(letters[i]->GetWidht() > 10 && text[j] == '9')
            letters[i]->SetCrop(327, 283, 46, 33);
            //letters[i]->PlayAnimation(8, 8, 0, 10);
        if(letters[i]->GetWidht() <= 10 && text[j] == '9')
            letters[i]->SetCrop(327, 640, 46, 33);
        if(letters[i]->GetWidht() > 10 && text[j] == '0')
            letters[i]->SetCrop(367, 283, 46, 33);
            //letters[i]->PlayAnimation(9, 9, 0, 10);
        if(letters[i]->GetWidht() <= 10 && text[j] == '0')
            letters[i]->SetCrop(367, 640, 46, 33);

        if(text[j] == '[')
            letters[i]->SetCrop(6, 340, 46, 40);
            //letters[i]->PlayAnimation(0, 0, 0, 10);
        if(text[j] == '!')
            letters[i]->SetCrop(46, 346, 46, 33);
            //letters[i]->PlayAnimation(1, 1, 0, 10);
        if(text[j] == '?')
            letters[i]->SetCrop(87, 346, 46, 33);
            //letters[i]->PlayAnimation(2, 2, 0, 10);
        if(text[j] == ']')
            letters[i]->SetCrop(127, 340, 46, 40);
            //letters[i]->PlayAnimation(3, 3, 0, 10);
        if(text[j] == '"')
            letters[i]->SetCrop(167, 346, 46, 33);
            //letters[i]->PlayAnimation(4, 4, 0, 10);
        if(text[j] == '/')
            letters[i]->SetCrop(206, 346, 46, 33);
            //letters[i]->PlayAnimation(5, 5, 0, 10);
        if(text[j] == '|')
            letters[i]->SetCrop(246, 340, 46, 40);
            //letters[i]->PlayAnimation(6, 6, 0, 10);
        if(text[j] == '\\')
            letters[i]->SetCrop(286, 346, 46, 33);
            //letters[i]->PlayAnimation(7, 7, 0, 10);
        if(text[j] == '\'')
            letters[i]->SetCrop(327, 346, 46, 33);
            //letters[i]->PlayAnimation(8, 8, 0, 10);
        if(text[j] == '.')
            letters[i]->SetCrop(367, 334, 46, 33);
            //letters[i]->PlayAnimation(9, 9, 0, 10);
        if(text[j] == ':')
            letters[i]->SetCrop(406, 346, 46, 33);
            //letters[i]->PlayAnimation(10, 10, 0, 10);
        if(text[j] == ',')
            letters[i]->SetCrop(446, 334, 46, 33);
            //letters[i]->PlayAnimation(11, 11, 0, 10);
        if(text[j] == ';')
            letters[i]->SetCrop(486, 346, 46, 33);
            //letters[i]->PlayAnimation(12, 12, 0, 10);
        if(text[j] == '*')
            letters[i]->SetCrop(526, 346, 46, 33);
            //letters[i]->PlayAnimation(13, 13, 0, 10);
        if(text[j] == '+')
            letters[i]->SetCrop(566, 340, 46, 40);
            //letters[i]->PlayAnimation(14, 14, 0, 10);
        if(text[j] == '-')
            letters[i]->SetCrop(610, 340, 46, 40);
            //letters[i]->PlayAnimation(15, 15, 0, 10);
        if(inv == true)
        {
            j--;
        }
        else
        {
            j++;
        }
    }

}

void Text::Update()
{/*
    if(text.size() != letters.size())
    {
        for (std::vector<CSprite*>::iterator i = letters.begin(); i != letters.end(); ++i)
        {
            delete (*i);
        }
        letters.clear();
        if(inv == true)
        {
            int i,j;
            for(i = 10, j = 0; i > 0; i--, j++)
            {
                if(color == "WHITE")
                    letters.push_back(new CSprite(csdl_setup->GetRenderer(), "data/img/fontWhite1.png", X-j*W, Y, W, H, CameraX, CameraY, CCollisionRectangle(0,0,300,100)));
                else
                    letters.push_back(new CSprite(csdl_setup->GetRenderer(), "data/img/fontBlack1.png", X-j*W, Y, W, H, CameraX, CameraY, CCollisionRectangle(0,0,300,100)));
                //letters[i]->SetUpAnimation(16,3);
            }
        }
        else
        {
            for(int i = 0; i < text.size(); i++)
            {
                if(color == "WHITE")
                    letters.push_back(new CSprite(csdl_setup->GetRenderer(), "data/img/fontWhite1.png", X+i*W, Y, W, H, CameraX, CameraY, CCollisionRectangle()));
                else
                    letters.push_back(new CSprite(csdl_setup->GetRenderer(), "data/img/fontBlack1.png", X+i*W, Y, W, H, CameraX, CameraY, CCollisionRectangle()));
                //letters[i]->SetUpAnimation(16,3);
            }
        }
    }*/
    if(linkText != 0)
    {
        //std::cout << *linkText;
        std::string tmp = *linkText;
        //std::cout << tmp;
        text = tmp;
        //std::cout << tmp << " " << text << std::endl;
        //std::cout << text.size() << std::endl;
        //text = *linkText;
    }
    //std::cout << text.size() << std::endl;
    UpdateAnimation();
 //   UpdateControls();


}

void Text::Draw()
{
    //std::cout << "letters.size() " << letters.size() << " text.size() " << text.size() << std::endl;
    for(int i = 0; i < text.size(); i++)
    {
        letters[i]->DrawStatic();
    }

}

void Text::SetText(std::string passed_text)
{
    if(passed_text.size() > letters.size())
    {
        for(int i = 0; i < passed_text.size() - letters.size(); ++i)
        {
            letters.push_back(new CSprite(csdl_setup->GetRenderer(), "data/img/fontBlack1.png", X + (letters.size()+1)*W + (W/3), Y, W, H, CameraX, CameraY, CCollisionRectangle(), csdl_setup));
        }
    }
    text = passed_text;
}

void Text::SetX(int num)
{
    for (int i = 0; i < letters.size(); i++)
    {
        if(inv == true)
            letters[i]->SetX(num-i*(letters[i]->GetWidht()));
        else
            letters[i]->SetX(num+i*(letters[i]->GetWidht()));
    }
}
