//Ship.h
//Auth : William Horn
//4.12.2017
//Header for ship class

#ifndef SHIP_H
#define SHIP_H

#include "../globals.h"

struct Ship : public ShipShape{
    Ship();

    int weaponDamage;
};

#endif // SHIP_H
