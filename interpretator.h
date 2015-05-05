#include "stdafx.h"
#include "Enviroment.h"
#include "objects.h"
#include "MainCharacter.h"

class CInterpretator
{
public:
    CInterpretator(CEnviroment* passed_enviroment, MainCharacter* passed_MainCharacter);
    ~CInterpretator();

    void command(std::string);

private:
    CEnviroment* enviroment;
    MainCharacter* mainCharacter;
};
