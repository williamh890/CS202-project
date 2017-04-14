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
        std::vector<Photon> photons;
        std::vector<StarShape> stars;
        std::vector<Enemy> enemies;

        void updatePhotons();

        /* Utility Functions for bullets */
        void makeBullet(int source, float bulletX, float bulletY, Vector2<float> dir);
        void updateBullets();

        /* Utility Functions for Stars */
        void makeStar(float startingHeight);
        void populateInitialStars();
        void updateStars();

        /* Utility Functions for player ship */
        void updateShip();
        std::vector<bounds> shipOnBound();

        void makeInitEnemies();
        void updateEnemies();


    public:
        World();

        void show();
        void update();
        Ship getPlayerShip();

        /* Random Real Generators */
        static std::random_device r;
        static std::mt19937 rng;
        static std::uniform_real_distribution<float> starDist;
        static std::uniform_int_distribution<int> starBrightness;
        static std::uniform_int_distribution<int> randomInt;
};



#endif // WORLD_H
