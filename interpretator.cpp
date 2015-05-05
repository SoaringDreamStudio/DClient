#include "interpretator.h"

CInterpretator::CInterpretator(CEnviroment* passed_enviroment, MainCharacter* passed_MainCharacter)
{
    enviroment = passed_enviroment;
    mainCharacter = passed_MainCharacter;
}
CInterpretator::~CInterpretator()
{

}

void CInterpretator::command(std::string commandLine)
{
    std::istringstream iss(commandLine);
    std::string PreviousWord = "";
    while (iss)
    {

        std::string word;

        iss >> word;

        if (PreviousWord == "settime")
        {
            enviroment->setHours(atoi(word.c_str()));
            iss >> word;
            enviroment->setMinute(atoi(word.c_str()));
            if(enviroment->getHours() > 23)
                enviroment->setHours(23);
            if(enviroment->getHours() < 0)
                enviroment->setHours(0);
            if(enviroment->getMinute() > 59)
                enviroment->setMinute(59);
            if(enviroment->getMinute() < 0)
                enviroment->setMinute(0);
            if(enviroment->getHours() >= 21 || enviroment->getHours() < 7)
            {
                enviroment->setNight(true);
            }
            else if(enviroment->getHours() >= 7 || enviroment->getHours() < 21)
            {
                enviroment->setNight(false);
            }

        }

        if (PreviousWord == "sethp")
        {
            mainCharacter->SetHP(atoi(word.c_str()));
        }

        if (PreviousWord == "die")
        {
            mainCharacter->SetHP(0);
        }

        PreviousWord = word;
    }
}
