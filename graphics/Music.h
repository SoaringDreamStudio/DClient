#pragma once
#include "../libraries.h"

class Music
{
public:
	Music(std::string passed_sound);

	~Music(void);

	void Play();

	void Stop();

private:
	Mix_Music* music;
};

