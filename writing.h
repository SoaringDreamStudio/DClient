#pragma once
#include "stdafx.h"
#include "Sprite.h"
#include "SDL_Setup.h"
#include <vector>
#include <windows.h>

class Text
{
public:
	Text(std::string passed_text, int x, int y, int w, int h, CSDL_Setup* passed_SDL_Setup, float *passed_CameraX, float *passed_CameraY);
	Text(std::string passed_text, std::string passed_color, int x, int y, int w, int h, CSDL_Setup* passed_SDL_Setup, float *passed_CameraX, float *passed_CameraY);
	Text(std::string* passed_text, int x, int y, int w, int h, CSDL_Setup* passed_SDL_Setup, float *passed_CameraX, float *passed_CameraY);
	Text(std::string* passed_text, std::string passed_color, int x, int y, int w, int h, CSDL_Setup* passed_SDL_Setup, float *passed_CameraX, float *passed_CameraY);
	Text(std::string passed_text, int x, int y, int w, int h, CSDL_Setup* passed_SDL_Setup, float *passed_CameraX, float *passed_CameraY, bool inverted);
	Text(std::string passed_text, std::string passed_color, int x, int y, int w, int h, CSDL_Setup* passed_SDL_Setup, float *passed_CameraX, float *passed_CameraY, bool inverted);
	Text(std::string* passed_text, int x, int y, int w, int h, CSDL_Setup* passed_SDL_Setup, float *passed_CameraX, float *passed_CameraY, bool inverted);
	Text(std::string* passed_text, std::string passed_color, int x, int y, int w, int h, CSDL_Setup* passed_SDL_Setup, float *passed_CameraX, float *passed_CameraY, bool inverted);
	~Text(void);

	void Update();
	void Draw();
	void SetText(std::string passed_text);
	std::string GetText() {return text;}
	void deleteLastSymbol() {if(text.size()) {letters.erase(letters.end()-1); text.erase(text.end()-1); }}

	void SetX(int num);


private:

    void UpdateAnimation();
    float *CameraX;
    float *CameraY;

    bool inv;

    int X,Y,W,H;

    CSDL_Setup* csdl_setup;
    std::string* linkText;
    std::string text;

    std::string color;

    std::vector<CSprite*> letters;
};

