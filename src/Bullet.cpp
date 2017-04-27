/*
Bullet.cpp
CS 202 Final Project: Scroling Space Shooter
Team Members: Michael Bilan, Andrew Cummins, Corey Gray, William Horn, Kyle Tam, Cameron Titus
Created: 12/4/2017
Last Updated: 27/04/2017
Definitions for Bullet class
*/

#include "Bullet.h"

#include <SFML/Graphics.hpp>
using sf::Vector2f;
using sf::Color;

Color Bullet::defaultBulletColor{255, 0, 0};

Bullet::Bullet(int source,
               float bulletX,
               float bulletY,
               Vector2f & dir,
               Color & col) : BulletShape(Vector2f(BULLET_WIDTH,BULLET_SPEED)),
                            _source(source),
                            _damage(BULLET_DAMAGE),
                            _direction(dir)
{
    setPosition(bulletX, bulletY);
    setFillColor(col);
}
