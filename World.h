//World.h
//CS202 Final Proj
//Auth: William Horn
//4.9.2017
#ifndef WORLD_H
#define WORLD_H

#include "globals.h"
#include "entities/Enemy.h"
#include "entities/Bullet.h"
#include "entities/Ship.h"
#include "entities/Photon.h"

#include <SFML/Graphics.hpp>
#include <vector>
#include <random>

class World : public sf::RenderWindow{
    private:

        /* Player Ship Object */
        Ship playerShip;

        /* Main Containers for game entities*/
        std::vector<Bullet> bullets;
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

    public:
        World();

        void show();
        void update();


        /* Random Real Generators */
        static std::random_device r;
        static std::mt19937 rng;
        static std::uniform_real_distribution<float> starDist;
        static std::uniform_int_distribution<int> starBrightness;
        static std::uniform_int_distribution<int> randomInt;
};



#endif // WORLD_H
