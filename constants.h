// constants.h
// CS 202 Project: Scrolling Space Shooter
// Team Members: William Horn, Corey Gray, Michael Bilan, Cameron Titus, Kyle Tam, Andrew Cummins
// Created: 20170407
// Updated: 20170412
// 
// Constant integers used throughout the game

#include <SFML/Graphics.hpp>

#ifndef CONSTANTS_H_INCLUDED
#define CONSTANTS_H_INCLUDED

// Easily change shapes later if needed
typedef sf::RectangleShape StarShape;
typedef sf::RectangleShape BulletShape;
typedef sf::RectangleShape EnemyShape;
typedef sf::CircleShape ShipShape;

// Game constants
const int WIDTH = 500;
const int HEIGHT = 750;
const int FRAMERATE = 60;
const int BACKGROUND_SPEED = 7;

const int PLAYER_X_SPEED = 5;
const int PLAYER_Y_SPEED = 5;
const int SHIP_RADIUS = 20;

const int BULLET_LEN = 10;
const int BULLET_WIDTH = 2;
const int BULLET_SPEED = 25;
const int FIRE_RATE = 10; // Smaller number for faster fire rate

const int STAR_SPAWN_RATE = 1; // Larger number for fewer stars
const int STAR_HEIGHT = 2;
const int STAR_WIDTH = 2;

const int ENEMY_HEIGHT = 20;
const int ENEMY_WIDTH = 15;

// For bound checking
enum bounds {RIGHT, LEFT, UPPER, LOWER, EMPTY};

#endif // CONSTANTS_H_INCLUDED
