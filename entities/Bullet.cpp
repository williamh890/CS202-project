
#include "../globals.h"
#include "Bullet.h"

#include <SFML/Graphics.hpp>
using sf::Vector2;

Bullet::Bullet(float bulletX, float bulletY) : BulletShape(Vector2<float>(BULLET_WIDTH,BULLET_LEN)){
    Color BULLET_COLOR{255, 0, 0};

    this->setPosition(bulletX, bulletY);
    this->setFillColor(BULLET_COLOR);
}
