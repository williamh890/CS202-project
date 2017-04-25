//Enemy.h
//Auth: William Horn
//4.20.2017
//Class header to represent base enemy

#ifndef ENEMY_H
#define ENEMY_H

#include "constants.h"
#include "Bullet.h"
#include "Enemy.h"
#include "Ship.h"

#include <SFML/Graphics.hpp>

#include <vector>
#include <random>
#include <string>
#include <functional>

struct Traits {
    Traits(float playerSeek,
           float targetSeek,
           int switchChance,
           float bulletDodge,
           float speed,
           bool gun,
           float separate = ENEMY_SEPARATE_FORCE) : seekPlayerForce(playerSeek),
                                                    seekTargetForce(targetSeek),
                                                    targetSwitchChance(switchChance),
                                                    bulletDodgeForce(bulletDodge),
                                                    maxSpeed(speed),
                                                    hasGun(gun),
                                                    separateForce(separate){}

    float seekPlayerForce;
    float seekTargetForce;
    int targetSwitchChance;
    float bulletDodgeForce;

    float  maxSpeed;
    bool hasGun;
    float separateForce;


    //A variable function for setting the target
    //2 possible types
    //  -random x, random y
    //  -player x, random y
    std::function<Vector2f(const ShipShape & ship)> setTarget;
};

class World;

struct Enemy : public EnemyShape{

    Enemy(sf::Vector2f starting_pos,
          sf::Vector2f starting_vel,
          int hp, int damage,
          Traits enemyTraits,
          std::string textureFilePath = "resources/sprites/eyeball.png");

    Vector2f vel;
    Vector2f accel;
    float maxSpeed;
    sf::Texture enemyTexture;

    Traits traits;

    //Used to periodically dodge bullets
    Vector2f dodge(const std::vector<Bullet *> & bullets, bool & hasForce);
    int dodgeChargeTime;
    int dodgeCounter;

    //Push away from other enemies
    Vector2f separate(const std::vector<Enemy*> & enemies);
    //Pull in the direction of the player
    Vector2f seekPlayer(const Ship & playerShip);
    //Seek a random target
    Vector2f seekTarget();
    Vector2f target;


    float enemyDetectionRadius;
    float bulletDetectionRadius;
    float desiredPlayerDist;

    int hp;
    int damage;
    int sourceID;

    int bleed;

    bool checkIntersect(const Bullet &b);
    void update(World & world);

    static std::random_device ranDev;
    static std::mt19937 rng;

    static std::uniform_real_distribution<float> rngTargetWidth;
    static std::uniform_real_distribution<float> rngTargetHeight;
    static std::uniform_real_distribution<float> rngFollowerHeight;
    static std::uniform_int_distribution<int> randomInt;
};

//Factory function for making the different types of enemies
Enemy * make_seeker();
Enemy * make_wanderer();
Enemy * make_follower();


#endif // ENEMY_H
