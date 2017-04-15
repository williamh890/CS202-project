//Ship.h
//Auth : William Horn
//4.12.2017
//Header for ship class

#ifndef SHIP_H
#define SHIP_H

#include "../constants.h"
#include "Photon.h"

#include <vector>

struct Ship : public ShipShape{
    Ship();

    void photonCannon(std::vector<Photon> & photons);
    int weaponDamage;

    int amountOfLives;
    bool playerIsDead;
    bool isTouchingEnemy;
    bool checkIntersect(const EnemyShape &e);

    int sourceID;

};

#endif // SHIP_H
