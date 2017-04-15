// world.h
// CS 202 Project: Scrolling Space Shooter
// Team Members: William Horn, Corey Gray, Michael Bilan, Cameron Titus, Kyle Tam, Andrew Cummins
// Created: 20170409
// Updated: 20170412
//
// Header for World class

#ifndef WORLD_H
#define WORLD_H

#include "globals.h"
#include "entities/Enemy.h"
#include "entities/Bullet.h"
#include "entities/Ship.h"
#include "entities/Photon.h"

>>>>>>> customShapes
#include <SFML/Graphics.hpp>
#include <vector>
#include <random>


class World : public sf::RenderWindow{
    private:

        /* Player Ship Object */
        Ship playerShip;

        /* Main Containers for game entities*/
        std::vector<Bullet> bullets;
        std::vector<Photon> photons;
        std::vector<StarShape> stars;
        std::vector<Enemy> enemies;

        void updatePhotons();

        /* Utility Functions for bullets */
        void makeBullet(int source, float bulletX, float bulletY, Vector2<float> dir);
>>>>>>> customShapes
        void updateBullets();

        // Utility functions for stars
        void makeStar(float startingHeight);
        void populateInitialStars();
        void updateStars();

        /* Utility Functions for player ship */
>>>>>>> customShapes
        void updateShip();
        std::vector<bounds> shipOnBound();

        void makeInitEnemies();
        void updateEnemies();


    public:
        World();

        void show();
        void update();
        Ship getPlayerShip();
>>>>>>> customShapes

        // Random Real Generators
        static std::random_device ranDev;
        static std::mt19937 rng;
        static std::uniform_real_distribution<float> starDist;
        static std::uniform_int_distribution<int> starBrightness;
        static std::uniform_int_distribution<int> randomInt;
};

#endif // WORLD_H
