//Ship.cpp
//Auth : William Horn
//4.12.2017
//Definitions for ship class

#include "Ship.h"
#include "World.h"

#include <SFML/Graphics.hpp>
using sf::Color;
using sf::Keyboard;
using sf::Vector2;
using sf::Vector2f;

#include <vector>
using std::vector;

#include "Loader.h"

Ship::Ship() : ShipShape(),
               vel(Vector2f(0.0, 0.0)),
               accel(Vector2f(0.0, 0.0)),
               laserReloadTime(DEFAULT_BULLET_FIRERATE),
               laserReloadSpeed(1),
               laserReloadCounter(0),
               photonReloadTime(DEFAULT_PHOTON_FIRERATE),
               photonReloadSpeed(1),
               photonReloadCounter(0),
               sourceID(PLAYER)

{
    int outline = 2;


    load_texture(shipTexture,"resources/sprites/f-15.png");
    setTexture(shipTexture);
    setScale(.15,.15);
    setPosition(WIDTH / 2, HEIGHT - 2.5*SHIP_RADIUS);
    amountOfLives = 5;
    playerIsDead = false;
    isTouchingEnemy = false;
}

bool Ship::checkIntersect(const sf::Shape &e) {
    return (getGlobalBounds().intersects(e.getGlobalBounds()));
}

bool Ship::checkIntersect(const sf::Sprite &e) {
    return (getGlobalBounds().intersects(e.getGlobalBounds()));
}

Bullet* Ship::laser(){
    //Gets the x/y position
    float bulletX = this->getPosition().x + SHIP_RADIUS;
    float bulletY = this->getPosition().y;
    Vector2<float> dir(0, -(float)BULLET_SPEED);

    Bullet* newBullet = new Bullet(PLAYER, bulletX, bulletY, dir);

    laserReloadCounter = 0;
    return newBullet;
}

Photon* Ship::photonCannon(){
    Photon* newPhoton = new Photon{PHOTON_RADIUS};

    float X = getPosition().x + .7*SHIP_RADIUS;
    float Y = getPosition().y - .7*SHIP_RADIUS;

    newPhoton->setPhotonPosition(X, Y);

    photonReloadCounter = 0;
    return newPhoton;
}

// Moves the ship with input from the keyboard and checks if a bullet has been fired
//  !!!NTF: Add acceleration to the movement so instead of
//          this being a direct move it would just apply a force
void Ship::update(World & world){
    ///////////////////////movement///////////////////////

    //LEFT ARROW TO MOVE LEFT
    if(Keyboard::isKeyPressed(Keyboard::Left) || (Keyboard::isKeyPressed((Keyboard::A)))){
           accel += Vector2f(-PLAYER_X_ACCEL, 0);
    }

    //RIGHT ARROW TO MOVE RIGHT
    if(Keyboard::isKeyPressed(Keyboard::Right) || (Keyboard::isKeyPressed((Keyboard::D)))){
            accel += Vector2f(PLAYER_X_ACCEL, 0);
    }

    //UP ARROW TO MOVE UP
    if(Keyboard::isKeyPressed(Keyboard::Up) || (Keyboard::isKeyPressed((Keyboard::W)))){
            accel += Vector2f(0, -PLAYER_Y_ACCEL);
    }
    //DOWN ARROW TO MOVE DOWN
    if(Keyboard::isKeyPressed(Keyboard::Down) || (Keyboard::isKeyPressed((Keyboard::S)))){
           accel += Vector2f(0, PLAYER_Y_ACCEL);
    }
    //Add the acceleration to the velocity
    vel += accel;

    accel.x *= 0;
    accel.y *= 0;

    //Slight drag to make things easier to control
    vel.y *= SHIP_DRAG;
    vel.x *= SHIP_DRAG;

    float velocityMag = sqrt(vel.y * vel.y + vel.x * vel.x);
    //Going faster then the max speed
    if(velocityMag >= MAX_SPEED) {
        //Normalize
        vel.x /= velocityMag;
        vel.y /= velocityMag;

        //Scale to the max speed
        vel.x *= MAX_SPEED;
        vel.y *= MAX_SPEED;
    }
    //Check if the ship is on a bound
    if(world.onBound(*this)[0] == RIGHT) {
        //If the ship has a leftward(?) velocity
        if(vel.x > 0) {
            vel.x = 0;
        }
    }
    if(world.onBound(*this)[1] == LEFT) {
        //If the ship has a leftward(?) velocity
        if(vel.x < 0) {
            vel.x = 0;
        }
    }

    if(world.onBound(*this)[2] == UPPER) {
        //If the ship has a leftward(?) velocity
        if(vel.y < 0) {
            vel.y = 0;
        }
    }
    if(world.onBound(*this)[3] == LOWER) {
        //If the ship has a leftward(?) velocity
        if(vel.y > 0) {
            vel.y = 0;
        }
    }

    //Move the players ship
    move(vel);

    /////////////////weapons and enemies////////////////

    //if the reload counter is full and the button is pressed
    if(laserReloadCounter >= laserReloadTime &&
       Keyboard::isKeyPressed(Keyboard::Space)){
        //Fires a bullet from the player ship
        world.bullets.push_back(laser());
    }
    //Add to the reload counter if it's not full
    else {
        laserReloadCounter += laserReloadSpeed;
    }
    //if the reload counter is full and the button is pressed
    if(photonReloadCounter >= photonReloadTime &&
       Keyboard::isKeyPressed(Keyboard::LShift)) {
        //Shoots a photon
        world.photons.push_back(photonCannon());

    }
    //Add to the reload counter if it's not full
    else {
        photonReloadCounter += photonReloadSpeed;
    }

    //Check  if collied with an enemy
    // !!!NTF: Maybe add some damage to the enemies as well
    for (int e = world.enemies.size() - 1; e >= 0; --e) {
        //If the player and an enemy intersect
        if (checkIntersect(*world.enemies[e])) {
            //minus a single life per collision
            amountOfLives--;
            setPosition(WIDTH / 2, HEIGHT - 2.5*SHIP_RADIUS);
            if (amountOfLives <= 0) {
                playerIsDead=true;
                break;
            }
        }
    }
    //Check if an enemy bullet hits the player
    //  !!!NTF: Separate out the player bullets and
    //          the enemy bullets into separate arrays
    for(int b = world.bullets.size() - 1; b >= 0; --b) {
        //If the bullet is an enemy bullet
        if(world.bullets[b]->source == ENEMY) {
            //If the bullets hits
            if(checkIntersect(*world.bullets[b])) {
                //Remove a life
                amountOfLives--;
                setPosition(WIDTH / 2, HEIGHT - 2.5*SHIP_RADIUS);
                //If yr dead...
                if (amountOfLives <= 0) {
                    playerIsDead=true;
                    break;
                }
                delete world.bullets[b];
                world.bullets.erase(world.bullets.begin() + b);
            }
        }
    }
}







