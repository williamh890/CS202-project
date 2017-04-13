//Bullet.h
//Auth: William Horn
//4.12.2017
//Header for Bullet class

#ifndef BULLET_H
#define BULLET_H

#include "../globals.h"

struct Bullet : public BulletShape{
    Bullet(float x, float y);

    int damage;
};
#endif // BULLET_H
