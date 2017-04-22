/*Screen_0.h
Team Members: William Horn, Corey Gray, Michael Bilan, Cameron Titus, Kyle Tam, Andrew Cummins
Created: 17/5/2017
Updated: 17/5/2017
Screen_1 inherits from the Screens.h virtual class; it is an object that controls the game screen.*/

#ifndef SCREEN_1_H_INCLUDED
#define SCREEN_1_H_INCLUDED

#include "Screens.h"
#include "constants.h"
#include "entities/Enemy.h"
#include "entities/Bullet.h"
#include "entities/Photon.h"
#include "entities/Ship.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <random>
//Menu Screen Constants


class Screen_1 : public Screens{
public:
    virtual int Run(sf::RenderWindow &) override;
};

/* Player Ship Object */
Ship playerShip;

/* Main Containers for game entities*/
std::vector<Bullet> bullets;
std::vector<Photon> photons;
std::vector<StarShape> stars;
std::vector<Enemy> enemies;

void updatePhotons();
void addPhoton(Photon p);

/* Utility Functions for bullets */

void updateBullets();
void addBullet(Bullet b);

// Utility functions for stars
void makeStar(float startingHeight);
void populateInitialStars();
void updateStars();

/* Utility Functions for player ship */

void updateShip();
std::vector<bounds> onBound(const Ship & playerShip);

void makeInitEnemies();
void updateEnemies();

void show();
void update();
Ship getPlayerShip();

// Random Real Generators
static std::random_device ranDev;
static std::mt19937 rng;
static std::uniform_real_distribution<float> starDist;
static std::uniform_int_distribution<int> starBrightness;
static std::uniform_int_distribution<int> randomInt;

#endif // SCREEN_1_H_INCLUDED
