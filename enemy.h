// enemy.h
// CS 202 Project: Scrolling Space Shooter
// Team Members: William Horn, Corey Gray, Michael Bilan, Cameron Titus, Kyle Tam, Andrew Cummins
// Created: 20170410
// Updated: 20170412
// 
// Header for Enemy class

#ifndef ENEMY_H
#define ENEMY_H

#include <SFML/Graphics.hpp>
using sf::Vector2;

#include "constants.h"

struct Enemy : public EnemyShape{
    Enemy(Vector2<float> starting_pos, Vector2<float> starting_dir, int hp, int damage);
    Vector2<float> direction;
    int hp;
    int damage;
};

#endif // ENEMY_H
