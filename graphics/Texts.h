#pragma once
#include "SDL_Setup.h"

class Text
{
public:
	Text(SDL_Renderer* passed_renderer,
              std::string passed_message,
              int X,
              int Y,
              int passed_fontSize);

	~Text(void);

	void Draw();

	void SetX(float X);
	void SetY(float Y);
	void SetPosition(float X, float Y);

	float GetX();
	float GetY();

	void SetFontSize(int fontSize);
	int GetFontSize( );

	void SetText(std::string message);
	std::string GetText() {return message;}

private:

	float x;
	float y;
	SDL_Texture* image;
	int fontSize;
	SDL_Color color;
	std::string message;
	SDL_Surface* surf;

	SDL_Rect rect;
    TTF_Font* font;
	SDL_Renderer* renderer;
};

