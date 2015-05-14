#pragma once
#include <map>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
class CSDL_Setup
{
public:
	CSDL_Setup(bool* quit, int ScreenWidth, int ScreenHeight);
	~CSDL_Setup(void);

	SDL_Renderer* GetRenderer();
	SDL_Event* GetMainEvent();
    int GetScreenWidth();
    int GetScreenHeight();

	void Begin();
	void End();

	SDL_Texture* addSprite(std::string);
	bool checkSprite(std::string);
	SDL_Texture* readSprite(std::string);

	//debug
	void showMap();
private:
    int ScreenWidth;
    int ScreenHeight;
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Event* mainEvent;

	//������� ������������� ���������� ������������ map � ������
	std::map<std::string, SDL_Texture*> createdSprites;
};

