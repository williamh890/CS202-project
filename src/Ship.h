//Ship.h
//Auth : William Horn
//4.12.2017
//Header for ship class

#ifndef SHIP_H
#define SHIP_H

#include "constants.h"
#include "Photon.h"
#include "Bullet.h"
#include "healthbar.h"

#include <vector>

#include <SFML/Graphics.hpp>

class World;

struct Ship : public ShipShape{
    //constructor
    Ship();

    sf::Vector2f vel;
    sf::Vector2f accel;
    sf::Texture shipTexture;
    sf::Texture explosionTexture;
    sf::Sprite explosionSprite;
    sf::Clock clock;
    sf::Time time;

    /* weapons */
    //Creates a photon at the ships position
    Photon* photonCannon();
    //Creates a bullet at the ships position
    Bullet* laser();

    /* reload values */ // !!!NTF: Put these in some sort of struct
                        //         Along with the weapon functions
    int laserReloadTime;
    int laserReloadSpeed;
    int laserReloadCounter;
    int photonReloadTime;
    int photonReloadSpeed;
    int photonReloadCounter;
    int playerScore;

    ReloadBar photonReloadBar;
    ReloadBar laserReloadBar;

    /* health */
    float health;
    float maxHP;
    bool playerIsDead;
    bool isTouchingEnemy;
    bool inInvincibleFrame;
    HealthBar hpBar;

    //Checks if an enemy collides with the ship
    bool checkIntersect(const sf::Shape &e);
    bool checkIntersect(const sf::Sprite &e);

    int bleed;
    //To id the bullets
    int sourceID;

    //Respond to keyboard inputs, controls movement and weapons
    //Modifies the world
    void update(World & world);

};

#endif // SHIP_H
