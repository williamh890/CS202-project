// world.cpp
// CS 202 Project: Scrolling Space Shooter
// Team Members: William Horn, Corey Gray, Michael Bilan, Cameron Titus, Kyle Tam, Andrew Cummins
// Created: 20170409
// Updated: 20170412
//
// Definitions and constructor for World class

//Ctor for  world class

#include "constants.h"
#include "World.h"
#include "entities/Enemy.h"
#include "entities/Photon.h"

#include <SFML/Graphics.hpp>
using sf::RenderWindow;
using sf::VideoMode;
using sf::Color;
using sf::Vector2;
using sf::Keyboard;
using sf::CircleShape;
#include <vector>
using std::vector;
#include <iostream>
using std::cout;
using std::endl;
#include <cmath>
using std::sin;
using std::floor;


// Setup for random real number generator for stars
std::random_device World::ranDev;
std::mt19937 World::rng = std::mt19937(ranDev());
std::uniform_real_distribution<float> World::starDist(0.0,(float)WIDTH);
std::uniform_int_distribution<int> World::randomInt(-1000, 1000);
std::uniform_int_distribution<int> World::starBrightness(100, 255);

///////////////////////////STAR FUNCTIONS/////////////////////////////////
// Creates a new star
void World::makeStar(float startingHeight)
{
	// Sets star size, shape, and color
	Vector2<float> starSize((float)STAR_HEIGHT, (float)STAR_WIDTH);
    StarShape newStar(starSize);

    // Makes a new star with a random position along width of screen
    newStar.setFillColor(Color(255,255,255,starBrightness(rng)));
    //Makes a new star with a random position along with of screen

    float starX = starDist(rng);
    newStar.setPosition(starX, startingHeight);
	stars.push_back(newStar);
}

// Fills screen with stars
void World::populateInitialStars(){
    for(int h = 0; h < HEIGHT; ++h){
        //This is finicky
        if(!(h % (STAR_SPAWN_RATE*7))){
            makeStar(h);

        }
    }
}

// Move the stars down the screen and deletes them if they fall off
// Also makes stars according to the spawn rate
void World::updateStars()
{
    // Move all the stars down
    for(int i = stars.size() - 1; i >= 0; --i)
	{
        stars[i].move(0.0, (float)BACKGROUND_SPEED);
        // Move stars to the top with a random width if they reaches the bottom
        if(stars[i].getPosition().y > HEIGHT + STAR_HEIGHT)
		{
            stars[i].setPosition(starDist(rng), 0);
        }
    }
}
///////////////////////////END STAR FUNCTIONS///////////////////////////

//////////////////////////BULLET FUNCTIONS//////////////////////////////
void World::makeBullet(int source, float bulletX, float bulletY, Vector2<float> dir){
    //Make a new bullet
    Bullet newBullet(source, bulletX, bulletY, dir);
    //Adds the bullet to the list of bullets
    bullets.push_back(newBullet);
}

// Moves bullets up the screen and deletes them if they fall off
void World::updateBullets()
{
    // Loops through the bullets vector backwards
    for(int i = bullets.size() - 1; i >= 0; --i)
	{
        // Checks if the bullet is off the screen
        if(bullets[i].getPosition().x < 0)
		{
            // Removes the bullet if so
            bullets.erase(bullets.begin() + i);
        }

        // Moves bullets up if not off the screen
        else{
            bullets[i].move(bullets[i].direction.x, bullets[i].direction.y);
        }
    }
}

void World::updatePhotons(){
    for(int i = photons.size() - 1; i >= 0; --i){
        if(photons[i].getPosition().x < 0){
            photons.erase(photons.begin() + i);
        }
        else{
            photons[i].moveCounter += PHOTON_FREQUENCY;
            float xDiff = 3*sin(photons[i].moveCounter);
            float yDiff = -PHOTON_SPEED;
            photons[i].movePhoton(xDiff, yDiff);
        }
    }
}
//////////////////////END BULLET FUNCTIONS//////////////////////////////

//////////////////////SHIP FUNCTIONS///////////////////////////////////
Ship World::getPlayerShip() {
    return playerShip;

}

// Returns if ship is bounded by the edges of the game window
vector<bounds> World::shipOnBound(){
    Vector2<float> pos = playerShip.getPosition();
    vector <bounds> playerScope ={EMPTY,EMPTY,EMPTY,EMPTY};

    float shipX = pos.x;
    float shipY = pos.y;

    // On right bound
    if(shipX >= WIDTH-(SHIP_RADIUS*2))
        playerScope[0]= RIGHT;
    // On left bound
    if(shipX < SHIP_RADIUS/8)
        playerScope[1] = LEFT;
    // On upper bound
    if(shipY < SHIP_RADIUS/2)
        playerScope[2] = UPPER;
    // On lower bound
    if(shipY > HEIGHT - (SHIP_RADIUS*2))
        playerScope[3]= LOWER;

    return playerScope;
}

// Moves the ship with input from the keyboard and checks if a bullet has been fired
//  !!!NTF: Add acceleration to the movement so instead of
//          this being a direct move it would just apply a force
void World::updateShip(){
    //for controlling fire rate
    static int shotCounter = FIRE_RATE;
    static int photonShotCounter = PHOTON_FIRERATE;

    //LEFT ARROW TO MOVE LEFT
    if(Keyboard::isKeyPressed(Keyboard::Left) || (Keyboard::isKeyPressed((Keyboard::A)))){
        if(shipOnBound()[1] != LEFT)
            playerShip.move(-PLAYER_X_SPEED, 0);
    }
    //RIGHT ARROW TO MOVE RIGHT
    if(Keyboard::isKeyPressed(Keyboard::Right) || (Keyboard::isKeyPressed((Keyboard::D)))){
        if(shipOnBound()[0] != RIGHT)
            playerShip.move(PLAYER_X_SPEED, 0);
    }
    //UP ARROW TO MOVE UP
    if(Keyboard::isKeyPressed(Keyboard::Up) || (Keyboard::isKeyPressed((Keyboard::W)))){
        if(shipOnBound()[2] != UPPER)
            playerShip.move(0, -PLAYER_Y_SPEED);
    }
    //DOWN ARROW TO MOVE DOWN
    if(Keyboard::isKeyPressed(Keyboard::Down) || (Keyboard::isKeyPressed((Keyboard::S)))){
        if(shipOnBound()[3] != LOWER)
            playerShip.move(0.0, (float)PLAYER_Y_SPEED);
    }

    //SPACE TO FIRE BULLET
    if(Keyboard::isKeyPressed(Keyboard::Space)){
        if(shotCounter >= FIRE_RATE){
            //Gets the x/y position
            float bulletX = playerShip.getPosition().x + SHIP_RADIUS;
            float bulletY = playerShip.getPosition().y;
            //Makes a bullet at that x,y position
            makeBullet(PLAYER, bulletX, bulletY, Vector2<float>(0, -(float)BULLET_SPEED));
            shotCounter = 0;

        }
    }
    if(Keyboard::isKeyPressed(Keyboard::LShift)){
        if(photonShotCounter >= PHOTON_FIRERATE){
            //Gets the x/y position

            //Makes a bullet at that x,y position
            playerShip.photonCannon(photons);

            photonShotCounter = 0;
        }

    }

    if(shotCounter <= FIRE_RATE){
        shotCounter++;
    }

     for (int e = enemies.size() - 1; e >= 0; --e) {
            //If the player and an enemy intersect
            if (playerShip.checkIntersect(enemies[e])) {
                //minus a single life per collision
                playerShip.amountOfLives--;
                playerShip.setPosition(WIDTH / 2, HEIGHT - 2.5*SHIP_RADIUS);
                if (playerShip.amountOfLives <= 0) {
                    playerShip.playerIsDead=true;
                    break;
                }
            }
        }

    if(photonShotCounter <= PHOTON_FIRERATE){
        photonShotCounter++;
    }
}
//////////////////////////END SHIP FUNCTIONS/////////////////////////

////////////////////////ENEMY FUNCTIONS/////////////////////////////
// Creates first wave of enemies
void World::makeInitEnemies(){
    for(int h = 5; h < HEIGHT / 2; h += ENEMY_HEIGHT + 5){
        Vector2<float> starting_pos(starDist(rng), h);

        Vector2<float> starting_dir = (randomInt(rng) % 2) ? Vector2<float>(-1,0) : Vector2<float>(1,0);

        enemies.push_back(Enemy(starting_pos, starting_dir, 5, 5));
    }
}

void World::updateEnemies(){
    //Look through all the enemies
    for(int e = enemies.size() - 1; e >= 0; --e){
        //Gets the position of the enemy
        Vector2<float> pos = enemies[e].getPosition();

        //Have enemies periodically shoot
        if(randomInt(rng) % 200 == 0){
            //Make a bullet shooting down
            makeBullet(ENEMY, pos.x, pos.y, Vector2<float>(0, ENEMY_BULLET_SPEED));
        }

        //Right side of the screen
        if(pos.x > WIDTH - 2*ENEMY_WIDTH){
            enemies[e].direction.x  *= -1;
        }
        //Left side of the screen
        if(pos.x < ENEMY_WIDTH){
            enemies[e].direction.x *= -1;
        }
        bool doesEnemyExist = true;
        //Look through all the bullets
        for (int b = bullets.size() - 1; b >= 0; --b) {
            //If an enemy and a bullet intersect
            if (enemies[e].checkIntersect(bullets[b]) && bullets[b].source == PLAYER) {
                //Do damage to the enemy
                enemies[e].hp -= bullets[b].damage;

                Color currColor = enemies[e].getFillColor();

                currColor.r += 50*bullets[b].damage;
                currColor.g -= 20*bullets[b].damage;

                enemies[e].setFillColor(currColor);
                //Remove the bullet
                bullets.erase(bullets.begin()+b);
                //Check if enemy is dead
                if (enemies[e].hp <= 0) {
                    //Delete the enemy
                    enemies.erase(enemies.begin()+e);
                    doesEnemyExist = false;
                    break;
                }
            }

        }
        // !!!NTF: THIS IS BAAAADDD...
        for (int p = photons.size() - 1; p >= 0; --p) {
            //If an enemy and a bullet intersect
            if (enemies[e].getGlobalBounds().intersects(photons[p].hitBox.getGlobalBounds()) ) {
                //Do damage to the enemy
                enemies[e].hp -= photons[p].damage;

                Color currColor = enemies[e].getFillColor();

                enemies[e].setFillColor(currColor);
                //Remove the bullet
                photons.erase(photons.begin()+p);
                //Check if enemy is dead
                if (enemies[e].hp <= 0) {
                    //Delete the enemy
                    enemies.erase(enemies.begin()+e);
                    doesEnemyExist = false;
                    break;
                }
            }
        }

        //Don't move the wrong enemy
        if(!doesEnemyExist) continue;
        //Move the enemy
        enemies[e].setPosition(pos + enemies[e].direction);

//        Vector2<float> origin = enemies[e].getOrigin();
//        enemies[e].setOrigin(HEIGHT / 2, WIDTH / 2);
//        enemies[e].rotate(1);
//        enemies[e].setOrigin(origin);

    }

}
////////////////////////END ENEMY FUNCTIONS/////////////////////////


// Constructor
World::World() : RenderWindow(VideoMode(WIDTH, HEIGHT), "ASTEROIDS"),
                 playerShip(Ship())
{
    populateInitialStars();
    makeInitEnemies();
    this->setFramerateLimit(FRAMERATE);
}

// Updates all the entities in the game world
void World::update()
{
    updateShip();
    updateStars();
    updateBullets();
    updatePhotons();
    updateEnemies();
}

//Draws all the entities to the sfml window
void World::show(){
    // !!!NTF: Find a way to just loop through all the entities and draw them
    //         instead of having separate loops
    for(const auto & s : stars){
        this->draw(s);
    }
    for(const auto & b : bullets){
        this->draw(b);
    }
    for(const auto & p : photons){
        this->draw(p);
        //this->draw(p.hitBox);
    }
    for(const auto & e : enemies){
        this->draw(e);
    }
    if (!playerShip.playerIsDead) {
        this->draw(playerShip);
    }

}
