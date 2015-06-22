#pragma once
#include "../libraries.h"

class Sound
{
public:
	Sound(std::string passed_sound);

	~Sound(void);

	void Play();

private:
	Mix_Chunk* sound;
};

