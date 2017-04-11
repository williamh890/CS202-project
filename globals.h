//game_constants.h
//CS 202 Proj
//Auth: William Horn
//4.7.2017

/*
    Constants related to all parts of the game
*/

#include <SFML/Graphics.hpp>

#ifndef GAME_CONSTANTS_H_INCLUDED
#define GAME_CONSTANTS_H_INCLUDED

/* Easily change shapes later if needed */
typedef sf::RectangleShape StarShape;
typedef sf::RectangleShape BulletShape;
typedef sf::RectangleShape EnemyShape;
typedef sf::CircleShape ShipShape;

/* Game Constants */
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
const int FIRE_RATE = 10;   //Smaller number is faster fire rate

const int STAR_SPAWN_RATE = 1; //Larger means less stars
const int STAR_HEIGHT = 2;
const int STAR_WIDTH = 2;

const int ENEMY_HEIGHT = 20;
const int ENEMY_WIDTH = 15;

//For bound checking
enum bounds {RIGHT, LEFT, UPPER, LOWER,EMPTY};

#endif // GAME_CONSTANTS_H_INCLUDED
