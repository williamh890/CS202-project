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
             Vector2f starting_vel,
             int health,
             int d) :  EnemyShape(Vector2f(ENEMY_HEIGHT,ENEMY_WIDTH)),
                       vel(starting_vel),
                       accel(Vector2f(0,0)),
                       hp(health),
                       damage(d),
                       sourceID(ENEMY)
{
    Vector2f rngStartingDir(World::enemyStartingVel(World::rng), World::enemyStartingVel(World::rng));
    vel = rngStartingDir;

    setPosition(starting_pos);
    setFillColor(Color(0, 196, 58));
    setOutlineColor(Color(119, 119, 119));
    setOutlineThickness(2);

    enemyDetectionRadius = ENEMY_HEIGHT + ENEMY_WIDTH / 2;
    desiredPlayerDist = World::optimalPlayerDist(World::rng);
}

bool Enemy::checkIntersect(const Bullet &b) {
    return (this->getGlobalBounds().intersects(b.getGlobalBounds()));
}

Vector2f Enemy::separate(const vector<Enemy> & enemies) {
    Vector2f steer{0,0};

    //Find the center of the current enemy
    Vector2f currEnemyPos = getPosition();
    currEnemyPos.x += ENEMY_WIDTH / 2;
    currEnemyPos.y += ENEMY_HEIGHT / 2;

    //Look through all the enemies
    for(int e = 0; e < enemies.size(); ++e) {
        Vector2f pos = enemies[e].getPosition();
        //Find the center of the enemy
        pos.x += ENEMY_WIDTH / 2;
        pos.y += ENEMY_HEIGHT / 2;

        float dist = sqrt(pow(currEnemyPos.x - pos.x, 2) + pow(currEnemyPos.y - pos.y, 2));
        //check if the enemy can see the other enemy
        if(dist < enemyDetectionRadius) {
            Vector2f desired = currEnemyPos - pos;
            steer = desired - vel;
            //Make the force a repulsion force
            steer.x *= 1;
            steer.y *= 1;
        }
    }

    return steer;
}

Vector2f Enemy::seek(const Ship & playerShip) {
    //Find the center of the enemy
    Vector2f enemyCenter = getPosition();
    //Find the center
    enemyCenter.x += ENEMY_WIDTH / 2;
    enemyCenter.y += ENEMY_HEIGHT / 2;

    //Find the center of the player
    Vector2f playerCenter = playerShip.getPosition();
    playerCenter.x += SHIP_RADIUS / 2;
    playerCenter.y += SHIP_RADIUS / 2;

    float dist = sqrt(pow(enemyCenter.x - playerCenter.x, 2) + pow(enemyCenter.y - playerCenter.y, 2));

    Vector2f desired =  playerCenter - enemyCenter;

    if(dist > desiredPlayerDist){
        desired.x *= 1;
        desired.y *= 1;
    }
    if(dist < desiredPlayerDist) {
        desired.x *= -1;
        desired.y *= -1;
    }

    Vector2f seek = desired - vel;

    return seek;
}

Vector2f Enemy::flee() {
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

        if(pos.y >= HEIGHT - 2 * ENEMY_HEIGHT){
            vel.y *= -1;
        }

        if(pos.y < 0){
            vel.y *= -1;
        }

        Vector2f enemySeparation = separate(world.enemies);
        Vector2f playerSeek = seek(world.playerShip);

        //Add weights to the separation force for balance
        enemySeparation.x *= ENEMY_SEPARATION_FORCE;
        enemySeparation.y *= ENEMY_SEPARATION_FORCE;

        playerSeek.x *= ENEMY_SEEK_FORCE;
        playerSeek.y *= ENEMY_SEEK_FORCE;

        //Add the separation force to the total acceleration
        accel += enemySeparation;
        accel += playerSeek;

        //Add the total acceleration to the velocity
        vel += accel;

        float velocityMag = sqrt(vel.y * vel.y + vel.x * vel.x);
        //Going faster then the max speed
        if(velocityMag >= ENEMY_MAX_SPEED) {
            //Normalize
            vel.x /= velocityMag;
            vel.y /= velocityMag;

            //Scale to the max speed
            vel.x *= ENEMY_MAX_SPEED;
            vel.y *= ENEMY_MAX_SPEED;
        }

        //Zero out the acceleration
        accel.x *= 0;
        accel.y *= 0;

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
