//Enemy.cpp
//Auth: William Horn
//4.10.2017
//Definitions for Enemy class

#include "../Enemy.h"
#include "../../World.h"

#include <SFML/Graphics.hpp>
using sf::Vector2f;
using sf::Color;

//Ctor
Enemy::Enemy(Vector2f starting_pos,
             Vector2f starting_dir,
             int health,
             int d) :  EnemyShape(Vector2f(ENEMY_HEIGHT,ENEMY_WIDTH)),
                       vel(starting_dir),
                       accel(Vector2f(0,0)),
                       hp(health),
                       damage(d),
                       sourceID(ENEMY)
{
    this->setPosition(starting_pos);
    this->setFillColor(Color(0, 196, 58));
}

bool Enemy::checkIntersect(const Bullet &b) {
    return (this->getGlobalBounds().intersects(b.getGlobalBounds()));
}

Vector2f Enemy::separate(const vector<Enemy> & enemies){
    return Vector2f(0,0);
}

Vector2f Enemy::seek(){
    return Vector2f(0,0);
}

void Enemy::update(World & world){
    //Gets the position of the enemy
        Vector2f pos = getPosition();

        //Have enemies periodically shoot
        if(World::randomInt(World::rng) % 200 == 0){
            //Make a bullet shooting down
            world.bullets.push_back(Bullet(ENEMY, pos.x, pos.y, Vector2f(0, ENEMY_BULLET_SPEED), Color{247, 168, 255}));
        }

        //Right side of the screen
        if(pos.x > WIDTH - 2*ENEMY_WIDTH){
            vel.x  *= -1;
        }
        //Left side of the screen
        if(pos.x < ENEMY_WIDTH){
            vel.x *= -1;
        }

        //Move the enemy
        move(vel);

        //Look through all the bullets
        for (int b = world.bullets.size() - 1; b >= 0; --b) {
            //If an enemy and a bullet intersect
            if (checkIntersect(world.bullets[b]) && world.bullets[b].source == PLAYER) {
                //Do damage to the enemy
                hp -= world.bullets[b].damage;

                Color currColor = getFillColor();

                currColor.r += 50*world.bullets[b].damage;
                currColor.g -= 20*world.bullets[b].damage;

                setFillColor(currColor);
                //Remove the bullet
                world.bullets.erase(world.bullets.begin()+b);
                //Check if the enemy is dead
                if(hp <= 0) return;
            }

        }
        // !!!NTF: THIS IS BAAAADDD...
        for (int p = world.photons.size() - 1; p >= 0; --p) {
            //If an enemy and a bullet intersect
            if (getGlobalBounds().intersects(world.photons[p].hitBox.getGlobalBounds()) ) {
                //Do damage to the enemy
                hp -= world.photons[p].damage;

                Color currColor = getFillColor();

                setFillColor(currColor);
                //Remove the bullet
                world.photons.erase(world.photons.begin()+p);
                //Check if enemy is dead
                if(hp <= 0) return;
            }
        }
}
