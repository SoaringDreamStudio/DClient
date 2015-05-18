#pragma once
#include "libraries.h"
#include "graphics/CollisionRectangle.h"

struct coordinates
{
    int x;
    int y;
};

struct AnimationInfo
{
    int BeginFrame;
    int EndFrame;
    int Row;
    int Speed;
};

enum ObjectType
{
    TypeNone,
    TypeCharacters,
    TypeGround,
    TypeMobs,
    TypeNormal,
    TypeTrigger,
    TypeWtrig
};

enum EffectType
{
    EffectTypeNone,
    EffectTypeChamp
};

std::string IntToStr(int x);
bool allTrue(bool x[], int Size);
