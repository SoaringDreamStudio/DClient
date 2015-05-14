#include "Texts.h"
#include "../libraries.h"


Text::Text(SDL_Renderer* passed_renderer,
              std::string passed_message,
              int X,
              int Y,
              int passed_fontSize)
{
	renderer = passed_renderer;
	image = NULL;

	x = X;
	y = Y;

    color = { 0, 0, 0, 255 };
	fontSize = passed_fontSize;
	message = passed_message;

	rect.x = x;
	rect.y = y;
	rect.w = fontSize * message.size() / 2 + 5 * message.size();
	rect.h = fontSize;

    font = TTF_OpenFont("data/DrawingBlood.ttf", fontSize);
}

Text::~Text(void)
{
	SDL_DestroyTexture(image);
}

void Text::Draw()
{
    rect.w = fontSize * message.size() / 2 + 5 * message.size();
	rect.h = fontSize;

    surf = TTF_RenderText_Blended(font, message.c_str(), color);

	image = SDL_CreateTextureFromSurface(renderer, surf);

	SDL_RenderCopy(renderer, image, NULL, &rect);
}


void Text::SetText(std::string passed_message)
{
    message = passed_message;
}

void Text::SetX(float X)
{
	x = X;
}

void Text::SetY(float Y)
{
	y = Y;
}

void Text::SetPosition(float X, float Y)
{
	x = X;
	y = Y;
}

float Text::GetX()
{
	return x;
}

float Text::GetY()
{
	return y;
}

void Text::SetFontSize(int FontSize)
{
	fontSize = FontSize;
}

int Text::GetFontSize()
{
	return fontSize;
}
