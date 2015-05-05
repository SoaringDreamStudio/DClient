#pragma once
#include "../libraries.h"
#include "CollisionRectangle.h"
#include "SDL_Setup.h"

class CSprite
{
public:
	CSprite(SDL_Renderer* passed_renderer,
          std::string FilePath,
          int x,
          int y,
          int w,
          int h,
          float *passed_CameraX,
          float *passed_CameraY,
          CCollisionRectangle passed_CollisionRect,
          CSDL_Setup* csdl_setup);

	CSprite(SDL_Renderer* passed_renderer,
          std::string FilePath,
          int x,
          int y,
          int w,
          int h,
          float *passed_CameraX,
          float *passed_CameraY,
          float *passed_MovingCameraX,
          float *passed_MovingCameraY,
          CCollisionRectangle passed_CollisionRect,
          CSDL_Setup* csdl_setup);
	//CSprite(SDL_Renderer* passed_renderer, std::string FilePath, int* x, int* y, int w, int h, float *passed_CameraX, float *passed_CameraY, CCollisionRectangle passed_CollisionRect);
	//CSprite(spriteInfo info);
	~CSprite(void);

    bool checkLoadedSprites(CSDL_Setup* csdl_setup, std::string FilePath);
    void DrawWithCoord(CSDL_Setup *csdl_setup, coordinates spawn);
	void Draw();
	void DrawSteady();
	void DrawStatic();

	void DrawWithRotate(double angle);

	void SetX(float X);
	void SetY(float Y);
	void SetPosition(float X, float Y);

	float GetX();
	float GetY();

	void SetWidht(int W);
	void SetHeight(int H);

	int GetWidht();
	int GetHeight();

	void SetOrgin(float X, float Y);

	void PlayAnimation(int BeginFrame, int EndFrame, int Row, float Speed);

	void SetUpAnimation(int passed_Amount_X, int passed_Amount_Y);

	bool isColliding(CCollisionRectangle theCollider);
	bool isColliding(int x, int y);

	CCollisionRectangle GetCollisionRect() {return CollisionRect;}

	void SetCrop(int x, int y, int w, int h) {crop.x = x; crop.y = y; crop.w = w; crop.h = h;}
	void SetCameraW(int w) {Camera.w = w; }
	void SetImagePath(std::string FilePath) {image = IMG_LoadTexture(renderer, FilePath.c_str());}

    SDL_Texture* getImage(){return image;}

private:
    CCollisionRectangle CollisionRect;
    SDL_Rect Camera;

    float *CameraX;
    float *CameraY;
    float *MovingCameraX;
    float *MovingCameraY;

	float Orgin_X;
	float Orgin_Y;

	float X_pos;
	float Y_pos;
	SDL_Texture* image;
	SDL_Texture* hitbox;
	SDL_Rect rect;
	SDL_Rect crop;
	int img_width;
	int img_height;

	int CurrentFrame;
	int timeCheck;
	int animationDelay;

	int Amount_Frame_X;
	int Amount_Frame_Y;

	SDL_Renderer* renderer;
};

