//Ship.cpp
//Auth : William Horn
//4.12.2017
//Definitions for ship class

#include "Ship.h"
#include "World.h"
#include "healthbar.h"

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
               photonReloadCounter(photonReloadTime),
               photonReloadBar(ReloadBar(RELOAD_BAR_HEIGHT, RELOAD_BAR_WIDTH)),
               laserReloadBar(ReloadBar(RELOAD_BAR_HEIGHT, RELOAD_BAR_WIDTH)),
               health(STARTING_HP),
               maxHP(health),
               hpBar(HealthBar()),
               sourceID(PLAYER)

{
    load_texture(shipTexture,"resources/sprites/f-15.png");
    setTexture(shipTexture);
    setScale(.2,.2);
    setPosition(WIDTH / 2, HEIGHT - 2.5*SHIP_RADIUS);
    playerIsDead = false;
    isTouchingEnemy = false;
    inInvincibleFrame = false;
    bleed = 0;
    clock.restart();

    hpBar.setCurrentHealthBar(1.0);
    photonReloadBar.setCurrentHealthBar(1.0);
    laserReloadBar.setCurrentHealthBar(1.0);

    int reloadBarBuffer = 5;

    photonReloadBar.currentHealthBar.rotate(180);
    laserReloadBar.currentHealthBar.rotate(180);

    //Change the positions of the reload bars
    laserReloadBar.currentHealthBar.setPosition(Vector2f(reloadBarBuffer + RELOAD_BAR_HEIGHT, HEIGHT - reloadBarBuffer));
    laserReloadBar.maxHealthBar.setPosition(Vector2f(reloadBarBuffer, HEIGHT - reloadBarBuffer - RELOAD_BAR_WIDTH));
    photonReloadBar.currentHealthBar.setPosition(Vector2f(2.5*reloadBarBuffer + 2*RELOAD_BAR_HEIGHT, HEIGHT - reloadBarBuffer));
    photonReloadBar.maxHealthBar.setPosition(Vector2f(2.5*reloadBarBuffer + RELOAD_BAR_HEIGHT, HEIGHT - reloadBarBuffer - RELOAD_BAR_WIDTH));

    photonReloadBar.currentHealthBar.setFillColor(Color(66, 164, 244));
    laserReloadBar.currentHealthBar.setFillColor(Color(244, 163, 65));

    photonReloadBar.maxHealthBar.setOutlineThickness(2);
    laserReloadBar.maxHealthBar.setOutlineThickness(2);

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
    Vector2<float> dir(0, -BULLET_SPEED);

    Bullet* newBullet = new Bullet(PLAYER, bulletX, bulletY, dir);

    laserReloadCounter = 0;
    return newBullet;
}

Photon* Ship::photonCannon(){
    Photon* newPhoton = new Photon{PHOTON_RADIUS};

    float X = getPosition().x + 0.7F*SHIP_RADIUS;
    float Y = getPosition().y - 0.7F*SHIP_RADIUS;

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

    accel *= (float)0;

    //Slight drag to make things easier to control
    vel *= (float)SHIP_DRAG;

    float velocityMag = sqrt(vel.y * vel.y + vel.x * vel.x);
    //Going faster then the max speed
    if(velocityMag >= MAX_SPEED) {
        //Normalize
        vel /= (float)velocityMag;


        //Scale to the max speed
        vel *= (float)MAX_SPEED;

    }
    //Check if the ship is on a bound
    if(world.onBound(*this)[0] == RIGHT) {
        //If the ship has a rightward(?) velocity
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
        //If the ship has a upward velocity
        if(vel.y < 0) {
            vel.y = 0;
        }
    }
    if(world.onBound(*this)[3] == LOWER) {
        //If the ship has a downward velocity
        if(vel.y > 0) {
            vel.y = 0;
        }
    }

    /////////////////weapons and enemies////////////////

    //if the reload counter is full and the button is pressed
    if(laserReloadCounter >= laserReloadTime &&
       Keyboard::isKeyPressed(Keyboard::Space)){
        //Fires a bullet from the player ship
        world.bullets.push_back(laser());
    }
    //Add to the reload counter if it's not full
    else if(laserReloadCounter <= laserReloadTime){
        laserReloadCounter += laserReloadSpeed;
    }
    //if the reload counter is full and the button is pressed
    if(photonReloadCounter >= photonReloadTime &&
       Keyboard::isKeyPressed(Keyboard::D)) {
        //Shoots a photon
        world.photons.push_back(photonCannon());

    }
    //Add to the reload counter if it's not full
    else if(photonReloadCounter <= photonReloadTime) {
        photonReloadCounter += photonReloadSpeed;
    }

    if(bleed <= 0) setColor(Color{255,255,255});
    else --bleed;

    if (inInvincibleFrame && clock.getElapsedTime().asMilliseconds() > 500) {
        inInvincibleFrame = false;
    }

    //Check  if collied with an enemy
    // !!!NTF: Maybe add some damage to the enemies as well
    for (int e = world.enemies.size() - 1; !inInvincibleFrame && e >= 0; --e) {
        //If the player and an enemy intersect
        if (checkIntersect(*world.enemies[e])) {
            //minus a single life per collision
            health--;
            if (!inInvincibleFrame) {
                inInvincibleFrame = true;
                clock.restart();
            }

            //Find the center of the enemy
            Vector2f enemyPos = world.enemies[e]->getPosition();
            enemyPos.x += ENEMY_WIDTH / 2;
            enemyPos.y += ENEMY_HEIGHT / 2;

            //Find the center of the ship
            Vector2f shipCenter = getPosition();
            shipCenter.x += SHIP_RADIUS;
            shipCenter.y += SHIP_RADIUS;

            Vector2f collisionForce = shipCenter - enemyPos;

            collisionForce *= (float).2;

            vel += collisionForce;

            //Apply an opposite force to the enemy
            collisionForce *= (float)-1;
            world.enemies[e]->vel += collisionForce;

            //Flash red if hit by an enemy
            setColor(Color{244, 66, 66, 200});
            bleed = 10;

            if (health <= 0) {
                playerIsDead=true;
                break;
            }
        }
    }
    //Check if an enemy bullet hits the player
    //  !!!NTF: Separate out the player bullets and
    //          the enemy bullets into separate arrays
    for(int b = world.bullets.size() - 1; !inInvincibleFrame && b >= 0; --b) {
        if(world.bullets[b]->source == ENEMY) {
            //If the bullets hits
            if(checkIntersect(*world.bullets[b])) {
                //Remove a life

                health--;
                if (!inInvincibleFrame) {
                    inInvincibleFrame = true;
                    clock.restart();
                }

                setColor(Color{244, 66, 66, 200});
                bleed = 5;

                delete world.bullets[b];
                world.bullets.erase(world.bullets.begin() + b);

                //If yr dead...
                if (health <= 0) {
                    playerIsDead=true;
                    break;
                }


            }
        }
    }

    //Move the players ship
    move(vel);

    //Set the health bar correctly
    float percentHP = health / maxHP;
    hpBar.setCurrentHealthBar(percentHP);
    //Set the reload bars
    float percentLaserReload = (float)laserReloadCounter / laserReloadTime;
    if(percentLaserReload >= 1) percentLaserReload = 1.0F;
    laserReloadBar.setCurrVertical(percentLaserReload);

    float percentPhotonReload = (float)photonReloadCounter / photonReloadTime;
    if(percentPhotonReload >= 1) percentPhotonReload = 1.0F;
    photonReloadBar.setCurrVertical(percentPhotonReload);



}
