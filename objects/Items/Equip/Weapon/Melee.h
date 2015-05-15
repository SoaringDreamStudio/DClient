#include "../Weapon.h"
#include "../../../../struct.h"
class Melee : public Weapon
{
public:
    Melee(int ID,
            int AD,
            int Range,
            std::string AttackAnimationName,
            SDL_Rect hitBox);

	~Melee(void);
protected:
    SDL_Rect hitBox;
};
