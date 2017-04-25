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
typedef sf::Sprite EnemyShape;
typedef sf::Sprite ShipShape;
typedef sf::RectangleShape HPBarShape;

const float PI = 3.14159265358979323846F;  /* pi */

/* Game Constants */
const float WIDTH = 500.0F;
const float HEIGHT = 750.0F;
const int FRAMERATE = 60;
const float BACKGROUND_SPEED = 7.0F;

const float PLAYER_X_ACCEL = 0.7F;
const float PLAYER_Y_ACCEL = 0.5F;
const float SHIP_RADIUS = 20.0F;
const float SHIP_DRAG = 0.93F;
const float MAX_SPEED = 6.0F;
const float STARTING_HP = 100.0F;

const float HP_BAR_LEN = 160.0F;
const float HP_BAR_WIDTH = 15.0F;
const float HP_BAR_SCREEN_BUFFER = 10.0F;

const int BULLET_DAMAGE = 1;
const int BULLET_LEN = 15;
const int BULLET_WIDTH = 3;
const int BULLET_SPEED = 23;
const int DEFAULT_BULLET_FIRERATE = 20;   //Smaller number is faster fire rate

const float PHOTON_RADIUS = 30;
const int PHOTON_EDGES = 20;
const int PHOTON_SPEED = 3;
const int DEFAULT_PHOTON_FIRERATE = 75;
const float PHOTON_FREQUENCY = PI / 30;
const int PHOTON_DAMAGE = 1000000;

const int STAR_SPAWN_RATE = 1; //Larger means less stars
const float STAR_HEIGHT = 2.0F;
const float STAR_WIDTH = 2.0F;

const int ENEMY_HEIGHT = 30;
const int ENEMY_WIDTH = 20;
const float ENEMY_BULLET_SPEED = 5.0F;
const float ENEMY_MAX_SPEED = 3.0F;

const float ENEMY_SEPARATE_FORCE = 0.155F;
const float SEEKER_PLAYERSEEKER_FORCE = 0.3F;
const float SEEKER_SPEED = 10.0F;

const float WANDERER_TARGET_FORCE = 0.16F;
const float WANDERER_MAXSPEED = 2.6F;
const float WANDERER_TARGET_SWITCH = 120;
const int DODGE_TIME = 50;

const float FOLLOWER_BULLET_DODGE = 3.0F;
const float FOLLOWER_MAXSPEED = 4.5F;
const float FOLLOWER_TARGET_FORCE = .18F;
const float FOLLOWER_TARGET_SWITCH = 40;

enum ID {PLAYER, ENEMY};
//For bound checking
enum bounds {RIGHT, LEFT, UPPER, LOWER,EMPTY};

#endif // GAME_CONSTANTS_H_INCLUDED
