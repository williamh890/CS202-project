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
#include "Ship.h"
#include "Enemy.h"
#include "Photon.h"
#include "Loader.h"

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
std::uniform_real_distribution<float> World::enemyStartingVel(-10.,10.);
std::uniform_real_distribution<float> World::optimalPlayerDist(HEIGHT / 2, HEIGHT - 100);
std::uniform_int_distribution<int> World::randomInt(-1000, 1000);
std::uniform_int_distribution<int> World::starBrightness(100, 255);


///////////////////////////STAR FUNCTIONS/////////////////////////////////
// Creates a new star
void World::makeStar(int startingHeight)
{
	// Sets star size, shape, and color
	Vector2<float> starSize((float)STAR_HEIGHT, (float)STAR_WIDTH);
    StarShape* newStar= new StarShape(starSize);

    // Makes a new star with a random position along width of screen
    newStar->setFillColor(Color(255,255,255,starBrightness(rng)));
    //Makes a new star with a random position along with of screen

    float starX = starDist(rng);
    newStar->setPosition(starX, (float)startingHeight);
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
        stars[i]->move(0.0, (float)BACKGROUND_SPEED);
        // Move stars to the top with a random width if they reaches the bottom
        if(stars[i]->getPosition().y > HEIGHT + STAR_HEIGHT)
		{
            stars[i]->setPosition(starDist(rng), 0);
        }
    }
}
///////////////////////////END STAR FUNCTIONS///////////////////////////

//////////////////////////BULLET FUNCTIONS//////////////////////////////
// Moves bullets up the screen and deletes them if they fall off
void World::updateBullets()
{
    // Loops through the bullets vector backwards
    for(int i = bullets.size() - 1; i >= 0; --i)
	{
        // Checks if the bullet is off the screen
        if(bullets[i]->getPosition().x < 0)
		{
            // Removes the bullet if so
            delete bullets[i];
            bullets.erase(bullets.begin() + i);
        }

        // Moves bullets up if not off the screen
        else{
            bullets[i]->move(bullets[i]->_direction.x, bullets[i]->_direction.y);
        }
    }
}

void World::updatePhotons(){
    for(int i = photons.size() - 1; i >= 0; --i){
        if(photons[i]->getPosition().x < 0){
            delete photons[i];
            photons.erase(photons.begin() + i);
        }
        else{
            photons[i]->moveCounter += PHOTON_FREQUENCY;
            float xDiff = 3*sin(photons[i]->moveCounter);
            float yDiff = -PHOTON_SPEED;
            photons[i]->movePhoton(xDiff, yDiff);
        }
    }
}
//////////////////////END BULLET FUNCTIONS//////////////////////////////

//////////////////////SHIP FUNCTIONS///////////////////////////////////

// Returns if ship is bounded by the edges of the game window
vector<bounds> World::onBound(const Ship & playerShip) {
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


//////////////////////////END SHIP FUNCTIONS/////////////////////////

////////////////////////ENEMY FUNCTIONS/////////////////////////////
// Creates first wave of enemies
void World::makeInitEnemies(){
    static int numSeekers = 3;
    static int numWanderers = 3;
    static int numFollowers = 3;

    for(int i = 0; i < numSeekers; ++i){
        //Makes a seeker at a random width at the top of the screen
        enemies.push_back(make_seeker());
    }
    for(int i = 0; i < numWanderers; ++i){
        //Makes a seeker at a random width at the top of the screen
        enemies.push_back(make_wanderer());
    }
    for(int i = 0; i < numFollowers; ++i){
        //Makes a seeker at a random width at the top of the screen
        enemies.push_back(make_follower());
    }
    numSeekers++;
    numWanderers++;
    numFollowers++;
}

void World::updateEnemies(){
    //Look through all the enemies
    for(int e = enemies.size() - 1; e >= 0; --e){
        enemies[e]->update(*this);
        //If dead
        if (enemies[e]->_hp <= 0 || enemies[e]->getPosition().y > HEIGHT) {
            if (enemies[e]->_hp <= 0){
            playerShip.playerScore+=25;
            }
            delete enemies[e];
            enemies.erase(enemies.begin()+e);

        }
    }
    if (enemies.size() <= 0) {
        makeInitEnemies();
    }

}
////////////////////////END ENEMY FUNCTIONS/////////////////////////

// Constructor
World::World() : Screens(),
                 playerShip(Ship())
{
    populateInitialStars();
}
//Cleans up all the memory
World::~World(){
    for(size_t i = 0; i < bullets.size(); ++i) {
        delete bullets[i];
    }
    for(size_t i = 0; i < photons.size(); ++i) {
        delete photons[i];
    }
    for(size_t i = 0; i < stars.size(); ++i) {
        delete stars[i];
    }
    for(size_t i = 0; i < enemies.size(); ++i) {
        delete enemies[i];
    }
}

// Updates all the entities in the game world
void World::update()
{
    playerShip.update(*this);
    updateStars();
    updateBullets();
    updatePhotons();
    updateEnemies();
}

//Draws all the entities to the sfml window
void World::show(sf::RenderWindow &gameScreen){
    // !!!NTF: Find a way to just loop through all the entities and draw them
    //         instead of having separate loops
    for(const auto & s : stars){
        gameScreen.draw(*s);
    }
    for(const auto & b : bullets){
       gameScreen.draw(*b);
    }
    for(const auto & p : photons){
        gameScreen.draw(*p);
        //this->draw(p.hitBox);
    }
    for(const auto & e : enemies){
        gameScreen.draw(*e);
    }
    if (!playerShip.playerIsDead) {
        gameScreen.draw(playerShip);
        //Draw health bar
        gameScreen.draw(playerShip.hpBar.currentHealthBar);
        gameScreen.draw(playerShip.hpBar.maxHealthBar);
        //Draw reload bars
        gameScreen.draw(playerShip.photonReloadBar.currentHealthBar);
        gameScreen.draw(playerShip.photonReloadBar.maxHealthBar);

        gameScreen.draw(playerShip.laserReloadBar.currentHealthBar);
        gameScreen.draw(playerShip.laserReloadBar.maxHealthBar);

    }
}

int World::Run(sf::RenderWindow &gameScreen){
    sf::Event event;

    World::makeInitEnemies();
    World::populateInitialStars();

    while(true){
        while(gameScreen.pollEvent(event)){
            if(event.type == sf::Event::Closed) return -1;
            if(event.type == sf::Event::KeyPressed){
                if(event.key.code == sf::Keyboard::Escape) return 0;
            }
        }
        gameScreen.clear();
        World::update();
        World::show(gameScreen);
        gameScreen.display();
    }
}
