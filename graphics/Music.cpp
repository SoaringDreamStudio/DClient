#include "Music.h"


Music::Music(std::string passed_sound)
{
    music = Mix_LoadMUS( passed_sound.c_str() );
    if(music == NULL)
    {
        std::cout << "can't load " << passed_sound << std::endl;
        //std::cout << Mix_GetError() << std::endl;
    }
}

Music::~Music(void)
{

}

void Music::Play()
{
    Mix_PlayMusic( music, -1 );
}


void Music::Stop()
{
    Mix_PauseMusic();
}
