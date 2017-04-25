//Enemy.cpp
//Auth: William Horn
//4.10.2017
//Definitions for Enemy class

#include "Enemy.h"
#include "World.h"
#include "Loader.h"

#include <SFML/Graphics.hpp>
using sf::Vector2f;
using sf::Color;
#include <random>
#include <vector>
using std::vector;
#include <string>
using std::string;


std::random_device Enemy::ranDev;
std::mt19937 Enemy::rng = std::mt19937(ranDev());

std::uniform_real_distribution<float> Enemy::rngTargetWidth(ENEMY_WIDTH, WIDTH - ENEMY_WIDTH);
std::uniform_real_distribution<float> Enemy::rngTargetHeight(ENEMY_WIDTH, HEIGHT * (3./5.));
std::uniform_real_distribution<float> Enemy::rngFollowerHeight(HEIGHT / 5, HEIGHT * (2 / 5.0));
std::uniform_int_distribution<int> Enemy::randomInt(-2000000, 2000000);

//Ctor
Enemy::Enemy(Vector2f starting_pos,
             Vector2f starting_vel,
             int health, int d,
             Traits enemyTraits,
             string textureFilePath) :  EnemyShape(),
                                        vel(starting_vel),
                                        accel(Vector2f(0,0)),
                                        traits(enemyTraits),
                                        hp(health),
                                        damage(d),
                                        sourceID(ENEMY)
{
    Vector2f rngStartingDir(World::enemyStartingVel(World::rng), World::enemyStartingVel(World::rng));
    vel = rngStartingDir;

    load_texture(enemyTexture ,textureFilePath);
    setTexture(enemyTexture);
    setScale(.2,.2);
    setPosition(starting_pos);

    enemyDetectionRadius = ENEMY_HEIGHT + ENEMY_WIDTH / 2;

    //Make bullet detection larger then enemy detection
    bulletDetectionRadius = enemyDetectionRadius * 1.5;
    desiredPlayerDist = World::optimalPlayerDist(World::rng);

    dodgeChargeTime = DODGE_TIME;
    dodgeCounter = 0;

    target = Vector2f(rngTargetWidth(rng), rngTargetHeight(rng));

    bleed = 0;
}

bool Enemy::checkIntersect(const Bullet &b) {
    return (getGlobalBounds().intersects(b.getGlobalBounds()));
}

static float distance(const Vector2f & a, const Vector2f & b) {
    return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

static void scalarMul(Vector2f & vec, float scalar) {
    vec.x *= scalar;
    vec.y *= scalar;
}

static void scalarDiv(Vector2f & vec, float scalar) {
    vec.x /= scalar;
    vec.y /= scalar;
}

static void makeCenter(Vector2f & pos, float xOff, float yOff) {
    pos.x += xOff;
    pos.y += yOff;
}

static void normalize(Vector2f & vec) {
    scalarDiv(vec, sqrt(vec.y * vec.y + vec.x * vec.x));
}

static void setMag(Vector2f & vec, float newMag) {
    normalize(vec);
    scalarMul(vec, newMag);
}

Vector2f Enemy::separate(const vector<Enemy*> & enemies) {
    Vector2f steer{0,0};

    //Find the center of the current enemy
    Vector2f currEnemyPos = getPosition();
    makeCenter(currEnemyPos, ENEMY_WIDTH / 2, ENEMY_HEIGHT / 2);

    //Look through all the enemies

    for(int e = 0; e < (int)enemies.size(); ++e) {
        Vector2f pos = enemies[e]->getPosition();
        //Find the center of the enemy
        makeCenter(pos, ENEMY_WIDTH / 2, ENEMY_HEIGHT / 2);

        float dist = distance(currEnemyPos, pos);
        //check if the enemy can see the other enemy
        if(dist < enemyDetectionRadius) {
            Vector2f desired = currEnemyPos - pos;
            steer += desired - vel;
            //Make the force a repulsion force
        }
    }

    return steer;
}

Vector2f Enemy::dodge(const vector<Bullet *> & bullets, bool & hasForce) {
    Vector2f boostForce{0,0};

    //look through all the bullets
    Vector2f enemyPos = getPosition();
    makeCenter(enemyPos, ENEMY_WIDTH / 2, ENEMY_HEIGHT / 2);

    for(int i = 0; i < (int)bullets.size(); ++i) {
        //if the bullet is a player bullet
        if(bullets[i]->source == PLAYER) {
            //Find the center of that bullet
            Vector2f bulletPos = bullets[i]->getPosition();
            makeCenter(bulletPos, BULLET_WIDTH, BULLET_SPEED);
            //find the distance between the bullet and the enemy
            float dist = distance(bulletPos, enemyPos);
            //Sees the bullet
            if(dist < bulletDetectionRadius) {
                //Boost left or right based on where the bullet is respectively
                boostForce = (enemyPos.x > bulletPos.x) ? Vector2f(20, 0) : Vector2f(-20, 0);
                hasForce = true;
                break;
            }
        }
    }

    return boostForce;
}

Vector2f Enemy::seekPlayer(const Ship & playerShip) {
    //Find the center of the enemy
    Vector2f enemyCenter = getPosition();
    //Find the center
    makeCenter(enemyCenter, ENEMY_WIDTH / 2, ENEMY_HEIGHT / 2);

    //Find the center of the player
    Vector2f playerCenter = playerShip.getPosition();
    makeCenter(playerCenter, SHIP_RADIUS / 2, SHIP_RADIUS / 2);

    Vector2f desired =  playerCenter - enemyCenter;

    Vector2f seek = desired - vel;

    return seek;
}

Vector2f Enemy::seekTarget() {
    //Find the center of the enemy
    Vector2f enemyCenter = getPosition();
    //Find the center
    makeCenter(enemyCenter, ENEMY_WIDTH / 2, ENEMY_HEIGHT / 2);

    Vector2f desired =  target - enemyCenter;
    Vector2f seek = desired - vel;

    return seek;

}

void Enemy::update(World & world){
    //Gets the position of the enemyif(hasDodgeForce)
        Vector2f pos = getPosition();

        //Have enemies periodically shoot
        if(traits.hasGun && World::randomInt(World::rng) % 300 == 0){
            //Make a bullet shooting down
            world.bullets.push_back(new Bullet(ENEMY,
                                               pos.x, pos.y,
                                               Vector2f(0, ENEMY_BULLET_SPEED),
                                               Color{3, 198, 0}));
        }
        //Randomly assign new target
        if(!(randomInt(rng) % traits.targetSwitchChance)) {
            target = traits.setTarget(world.playerShip);
        }

        //  !!!NTF: Bullet dodge doesnt work right

        //Only if the enemy has dodge
        if(traits.bulletDodgeForce){
            //Reset back to the default texture
            if(dodgeCounter == (dodgeChargeTime -DODGE_ANIMATION_TIME))
                setTextureRect(sf::IntRect(4, 3, 50, 50));
            if(dodgeCounter <= 0) {
                //Default texture rect
                bool hasForce = false;
                Vector2f bulletDodge = dodge(world.bullets, hasForce);

                if(hasForce) {
                    accel += bulletDodge;
                    dodgeCounter = dodgeChargeTime;

                    if(accel.x > 0) //moving to the right
                        setTextureRect(sf::IntRect(70,4,49,39));
                    if(accel.x < 0) //moving to the left
                        setTextureRect(sf::IntRect(129,5,50,35));
                    }
            }
            else{
                dodgeCounter--;
            }
        }


        Vector2f enemySeparation = separate(world.enemies);
        //Add weights to the separation force for balance

        setMag(enemySeparation, traits.separateForce);

        //Only add target steer if that enemy has it
        if(traits.seekTargetForce) {
            Vector2f targetSteer = seekTarget();
            setMag(targetSteer, traits.seekTargetForce);
            accel += targetSteer;
        }
        //Only seek the player if that enemy has it
        if(traits.seekPlayerForce) {
            //If the seeker passed the player
            if(getPosition().y <= world.playerShip.getPosition().y) {
                Vector2f playerSteer = seekPlayer(world.playerShip);
                setMag(playerSteer, traits.seekPlayerForce);
                accel += playerSteer;
            }
            //
            else
                vel.y += 0.5F;

        }
        //Add the separation force to the total acceleration
        accel += enemySeparation;


        //Add the total acceleration to the velocity
        vel += accel;

        //Dampening of the velocity
        scalarMul(vel, .99);

        float velocityMag = sqrt(vel.y * vel.y + vel.x * vel.x);
        //Going faster then the max speed
        if(velocityMag >= traits.maxSpeed) {
            //Normalize
            normalize(vel);

            //Scale to the max speed
            scalarMul(vel, traits.maxSpeed);
        }

        //Zero out the acceleration
        scalarMul(accel, 0);

        //Move the enemy
        move(vel);

        //Look through all the bullets
        for (int b = world.bullets.size() - 1; b >= 0; --b) {
            //If an enemy and a bullet intersect
            if (checkIntersect(*world.bullets[b]) && world.bullets[b]->source == PLAYER) {
                //Do damage to the enemy
                hp -= world.bullets[b]->damage;

                //Have the enemy flash red if hit
                setColor(Color{244, 66, 66, 200});
                bleed = 10;

                //Remove the bullet
                delete world.bullets[b];
                world.bullets.erase(world.bullets.begin()+b);
                //Check if the enemy is dead
                if(hp <= 0) return;
                //erases the enemy outside the function
            }

        }
        // !!!NTF: THIS IS BAAAADDD...
        for (int p = world.photons.size() - 1; p >= 0; --p) {
            //If an enemy and a bullet intersect
            if (getGlobalBounds().intersects(world.photons[p]->hitBox.getGlobalBounds()) ) {
                //Do damage to the enemy
                hp -= world.photons[p]->damage;

                //Remove the bullet
                delete world.photons[p];
                world.photons.erase(world.photons.begin()+p);
                //Check if enemy is dead
                if(hp <= 0) return;
                //erases the enemy outside the function
            }
        }

        if(bleed <= 0) {
            setColor(Color::White);
        }
        else
            --bleed;
}

Enemy * make_seeker() {
    Traits seekerTraits(SEEKER_PLAYERSEEKER_FORCE,
                        0,
                        4,
                        0,
                        SEEKER_SPEED,
                        false);



    //Dummy function
    std::function<Vector2f(const ShipShape &)> targetSetter = [](const ShipShape &)-> Vector2f{return Vector2f(0,0);};

    seekerTraits.setTarget = targetSetter;

    Vector2f initPos{Enemy::rngTargetWidth(Enemy::rng), 0};
    Vector2f initVel{0,0};

    Enemy * seeker = new Enemy(initPos, initVel, 1, 0, seekerTraits, "resources/sprites/homingEnemySheet.png");

    seeker->setScale(0.5, 0.5);

    seeker->setTextureRect(sf::IntRect(0,0,81,87));

    return seeker;
}

Enemy * make_wanderer() {
    Traits wandererTraits(0,                        //Player seek force
                          WANDERER_TARGET_FORCE,    //Target seek force
                          WANDERER_TARGET_SWITCH,   //Target switch chance
                          0,                        //Bullet Dodge force
                          WANDERER_MAXSPEED,        //Enemy Speed
                          true);                    //Has a gun

    std::function<Vector2f (const ShipShape &)> targetSetter = [](const ShipShape & ship)->Vector2f{return Vector2f(Enemy::rngTargetWidth(Enemy::rng),
                                                                                                                     Enemy::rngTargetHeight(Enemy::rng));};
    wandererTraits.setTarget = targetSetter;

    Vector2f initPos{Enemy::rngTargetWidth(Enemy::rng), 0};
    Vector2f initVel{0,0};
    int hp = 3;

    Enemy * wanderer = new Enemy(initPos, initVel, hp, 1, wandererTraits);

    wanderer->setScale(0.3, 0.3);

    return wanderer;
}

Enemy * make_follower() {
    Traits followerTraits(0,
                          FOLLOWER_TARGET_FORCE,
                          FOLLOWER_TARGET_SWITCH,
                          FOLLOWER_BULLET_DODGE,
                          FOLLOWER_MAXSPEED,
                          true);

    std::function<Vector2f (const ShipShape &)> targetSetter = [](const ShipShape & ship)->Vector2f{return Vector2f(ship.getPosition().x,
                                                                                                                     Enemy::rngFollowerHeight(Enemy::rng));};
    followerTraits.setTarget = targetSetter;

    Vector2f initPos{Enemy::rngTargetWidth(Enemy::rng), 0};
    Vector2f initVel{0,0};
    int hp = 5;

    Enemy * follower = new Enemy(initPos, initVel, hp, 1, followerTraits, "resources/sprites/dodgeEnemySheet.png");

    follower->setScale(1, 1);
    follower->setTextureRect(sf::IntRect(4, 3, 50, 50));

    return follower;
}


