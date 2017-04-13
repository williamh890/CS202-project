// enemy.h
// CS 202 Project: Scrolling Space Shooter
// Team Members: William Horn, Corey Gray, Michael Bilan, Cameron Titus, Kyle Tam, Andrew Cummins
// Created: 20170410
// Updated: 20170412
// 
// Definitions for Enemy class

#include "enemy.h"

#include <SFML/Graphics.hpp>
using sf::Vector2;
using sf::Color;

// Constructor
Enemy::Enemy(Vector2<float> starting_pos,
             Vector2<float> starting_dir,
             int health, int d) : EnemyShape(Vector2<float>((float)ENEMY_HEIGHT,(float)ENEMY_WIDTH)),
                                  direction(starting_dir),
                                  hp(health),
                                  damage(d)
{
    this->setPosition(starting_pos);
    this->setFillColor(Color(255, 76, 240));
}

