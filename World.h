// world.h
// CS 202 Project: Scrolling Space Shooter
// Team Members: William Horn, Corey Gray, Michael Bilan, Cameron Titus, Kyle Tam, Andrew Cummins
// Created: 20170409
// Updated: 20170412
// 
// Header for World class

#ifndef WORLD_H
#define WORLD_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <random>

#include "constants.h"
#include "enemy.h"

class World {
    private:
        // Player ship object
        ShipShape playerShip;

        // Main containers for game entities
        std::vector<BulletShape> bullets;
        std::vector<StarShape> stars;
        std::vector<Enemy> enemies;

        // Utility functions for bullets
        void makeBullet(float bulletX, float bulletY);
        void updateBullets();

        // Utility functions for stars
        void makeStar(float startingHeight);
        void populateInitialStars();
        void updateStars();

        // Utility functions for player ship
        void shipSettings();
        void updateShip();
        std::vector<bounds> shipOnBound();

        void makeInitEnemies();
        void updateEnemies();

    public:
        World();

        // SFML window
        static sf::RenderWindow screen;
		void draw();
        void update();
		void display();

        // Random Real Generators
        static std::random_device ranDev;
        static std::mt19937 rng;
        static std::uniform_real_distribution<float> starDist;
        static std::uniform_int_distribution<int> randomInt;
};

#endif // WORLD_H
