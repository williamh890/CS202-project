/*
constants.h
CS 202 Final Project
Team Members: Michael Bilan, Andrew Cummins, Corey Gray, William Horn, Kyle Tam, Cameron Titus
Created: 7/4/2017
Last Updated: 26/4/2017
Constants games constants used by several game files
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

const float PLAYER_X_ACCEL = 1.0F;
const float PLAYER_Y_ACCEL = 1.0F;
const float SHIP_RADIUS = 20.0F;
const float SHIP_DRAG = 0.92F;
const float MAX_SPEED = 8.0F;
const float STARTING_HP = 25.0F;
const float SWITCH_THRESHHOLD = 5.0F;

const float HP_BAR_LEN = 160.0F;
const float HP_BAR_WIDTH = 15.0F;
const float HP_BAR_SCREEN_BUFFER = 10.0F;

const int BULLET_DAMAGE = 1;
const int BULLET_LEN = 15;
const int BULLET_WIDTH = 4;
const int BULLET_SPEED = 23;
const int DEFAULT_BULLET_FIRERATE = 20;   //Smaller number is faster fire rate

const float PHOTON_RADIUS = 30;
const int PHOTON_EDGES = 20;
const int PHOTON_SPEED = 2;
const int DEFAULT_PHOTON_FIRERATE = 200;
const float PHOTON_FREQUENCY = PI / 35;
const int PHOTON_DAMAGE = 10;

const float RELOAD_BAR_WIDTH = 160.0F;
const float RELOAD_BAR_HEIGHT = 8.0F;

const int STAR_SPAWN_RATE = 1; //Larger means less stars
const float STAR_HEIGHT = 2.0F;
const float STAR_WIDTH = 2.0F;

const int ENEMY_HEIGHT = 30;
const int ENEMY_WIDTH = 20;
const float ENEMY_BULLET_SPEED = 5.0F;
const float ENEMY_MAX_SPEED = 3.0F;

const float ENEMY_SEPARATE_FORCE = 0.16F;
const float SEEKER_PLAYERSEEKER_FORCE = 0.3F;
const float SEEKER_SPEED = 10.0F;

const float WANDERER_TARGET_FORCE = 0.17F;
const float WANDERER_MAXSPEED = 3.0F;
const float WANDERER_TARGET_SWITCH = 120;

const int DODGE_TIME = 75;
const int DODGE_ANIMATION_TIME = 20;

const float FOLLOWER_BULLET_DODGE = 8.0F;
const float FOLLOWER_MAXSPEED = 4.5F;
const float FOLLOWER_TARGET_FORCE = .18F;
const float FOLLOWER_TARGET_SWITCH = 40;

enum ID {PLAYER, ENEMY};
//For bound checking
enum bounds {RIGHT, LEFT, UPPER, LOWER,EMPTY};

#endif // GAME_CONSTANTS_H_INCLUDED
