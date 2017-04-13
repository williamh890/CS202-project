//World.h
//CS202 Final Proj
//Auth: William Horn
//4.9.2017
#ifndef WORLD_H
#define WORLD_H

#include "globals.h"
#include "entities/Enemy.h"

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <random>
#include <SFML/Graphics/Text.hpp>
using std::string;

class World{
    private:

        /* Player Ship Object */
        ShipShape playerShip;

        /* Main Containers for game entities*/
        std::vector<BulletShape> bullets;
        std::vector<StarShape> stars;
        std::vector<Enemy> enemies;

        /* Utility Functions for bullets */
        void makeBullet(float bulletX, float bulletY);
        void updateBullets();

        /* Utility Functions for Stars */
        void makeStar(float startingHeight);
        void populateInitialStars();
        void updateStars();

        /* Utility Functions for player ship */
        void shipSettings();
        void updateShip();
        std::vector<bounds> shipOnBound();

        void makeInitEnemies();
        void updateEnemies();
        string gameOverText="--GAME\nOVER--";

    public:
        World();

        /* SFML Window */
        static sf::RenderWindow screen;

        void draw();
        void update();
        void display();
        int gameOver();


        /* Random Real Generators */
        static std::random_device r;
        static std::mt19937 rng;
        static std::uniform_real_distribution<float> starDist;
        static std::uniform_int_distribution<int> randomInt;
};



#endif // WORLD_H
