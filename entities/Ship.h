//Ship.h
//Auth : William Horn
//4.12.2017
//Header for ship class

#include "../globals.h"


struct Ship : public ShipShape{
    Ship();

    int weaponDamage;
};
