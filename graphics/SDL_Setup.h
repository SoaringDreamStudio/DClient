#pragma once
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

	//решение невозможности размещения статического map в классе
	std::map<std::string, SDL_Texture*> createdSprites;
};

