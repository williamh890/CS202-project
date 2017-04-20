//World.cpp
//Auth: William Horn
//4.9.2017
//Definitions for world class

//Ctor for  world class

#include "globals.h"
#include "World.h"
#include "entities/Enemy.h"
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Color.hpp>
#include <iostream>
using std::cout;
using std::endl;
using sf::RenderWindow;
using sf::VideoMode;
using sf::Color;
using sf::Vector2;
using sf::Keyboard;
using sf::CircleShape;
#include <vector>
using std::vector;


//Set up for random real number generator for stars
std::random_device World::r;
std::mt19937 World::rng = std::mt19937(r());
std::uniform_real_distribution<float> World::starDist(0,WIDTH);
std::uniform_int_distribution<int> World::randomInt(-1000, 1000);

//Make the screen
RenderWindow World::screen(VideoMode(WIDTH, HEIGHT), "ASTEROIDS");

///////////////////////////STAR FUNCTIONS/////////////////////////////////

void World::makeStar(float startingHeight){
    Vector2<float> starSize(STAR_HEIGHT, STAR_WIDTH);
    StarShape newStar(starSize);

    newStar.setFillColor(Color(255,255,255,150));
    //Makes a new star with a random position along with of screen
    float starX = starDist(rng);
    newStar.setPosition(starX, startingHeight);

    stars.push_back(newStar);
}

void World::populateInitialStars(){
    for(int h = 0; h < HEIGHT; ++h){
        //This is finicky
        if(!(h % (STAR_SPAWN_RATE*8))){
            makeStar(h);
        }
    }

}

//Move the stars down the screen and delete if off
//Also makes stars according to the spawn rate
void World::updateStars(){
    //Move all the stars down
    for(int i = stars.size() - 1; i >= 0; --i){
        stars[i].move(0, BACKGROUND_SPEED);
        //Move the star to the top with a random width
        //if they reach the bottom
        if(stars[i].getPosition().y > HEIGHT + STAR_HEIGHT){
            stars[i].setPosition(starDist(rng), 0);
        }
    }
}
///////////////////////////END STAR FUNCTIONS///////////////////////////

//////////////////////////BULLET FUNCTIONS//////////////////////////////
void World::makeBullet(float bulletX, float bulletY){
    Color BULLET_COLOR{255, 0, 0};

    BulletShape newBullet(Vector2<float>(BULLET_WIDTH,BULLET_LEN));
    //Makes the bullets at the ships position

    newBullet.setPosition(bulletX, bulletY);
    newBullet.setFillColor(BULLET_COLOR);
    //Adds the bullet to the list of bullets
    bullets.push_back(newBullet);
}

void World::updateBullets(){
    //Loop through backwards
    for(int i = bullets.size() - 1; i >= 0; --i){
        //If off the screen...
        if(bullets[i].getPosition().x < 0){
            //Remove the bullet
            bullets.erase(bullets.begin() + i);
        }
        else{
            bullets[i].move(0, -BULLET_SPEED);
        }
    }
}
//////////////////////END BULLET FUNCTIONS//////////////////////////////

//////////////////////SHIP FUNCTIONS///////////////////////////////////

//Sets all the shape/color settings for the ship model
void World::shipSettings(){
    int outline = 2;

    playerShip.setRadius(SHIP_RADIUS);
    playerShip.setOutlineThickness(outline);

    Color outlineColor{183, 183, 183};
    Color fillColor{42, 197, 224};

    playerShip.setFillColor(fillColor);
    playerShip.setOutlineColor(outlineColor);

    playerShip.setPosition(WIDTH / 2, HEIGHT - 2.5*SHIP_RADIUS);
}

//Returns if ship is bounded on the left or the right of the screen
vector<bounds> World::shipOnBound(){
    Vector2<float> pos = playerShip.getPosition();
    vector <bounds> playerScope ={EMPTY,EMPTY,EMPTY,EMPTY};

    float shipX = pos.x;
    float shipY = pos.y;

    //On right bound
    if(shipX >= WIDTH-(SHIP_RADIUS*2))
        playerScope[0]= RIGHT;
    //On left bound
    if(shipX < SHIP_RADIUS/8)
        playerScope[1] = LEFT;
    //On upper bound
    if(shipY < SHIP_RADIUS/2)
        playerScope[2] = UPPER;
    //On lower bound
    if(shipY > HEIGHT - (SHIP_RADIUS*2))
        playerScope[3]= LOWER;

    return playerScope;
}
//Moves the ship with input from the keyboard and checks if a bullet has been fired
//  !!!NTF: Add acceleration to the movement so instead of
//          this being a direct move it would just apply a force
void World::updateShip(){
    //for controlling fire rate
    static int shotCounter = 0;

    //LEFT ARROW TO MOVE LEFT
    if(Keyboard::isKeyPressed(Keyboard::Left)){
        if(shipOnBound()[1] != LEFT)
            playerShip.move(-PLAYER_X_SPEED, 0);
    }
    //RIGHT ARROW TO MOVE RIGHT
    if(Keyboard::isKeyPressed(Keyboard::Right)){
        if(shipOnBound()[0] != RIGHT)
            playerShip.move(PLAYER_X_SPEED, 0);
    }
    //UP ARROW TO MOVE UP
    if(Keyboard::isKeyPressed(Keyboard::Up)){
        if(shipOnBound()[2] != UPPER)
            playerShip.move(0, -PLAYER_Y_SPEED);
    }
    //DOWN ARROW TO MOVE DOWN
    if(Keyboard::isKeyPressed(Keyboard::Down)){
        if(shipOnBound()[3] != LOWER)
            playerShip.move(0, PLAYER_Y_SPEED);
    }

    //SPACE TO FIRE BULLET
    if(Keyboard::isKeyPressed(Keyboard::Space)){
        if(shotCounter % FIRE_RATE == 0){
            //Gets the x/y position
            float bulletX = playerShip.getPosition().x + SHIP_RADIUS;
            float bulletY = playerShip.getPosition().y - SHIP_RADIUS;
            //Makes a bullet at that x,y position
            makeBullet(bulletX, bulletY);
        }
        shotCounter++;
    }
}
//////////////////////////END SHIP FUNCTIONS/////////////////////////

////////////////////////ENEMY FUNCTIONS/////////////////////////////
void World::makeInitEnemies(){
    for(int h = 5; h < HEIGHT / 2; h += ENEMY_HEIGHT + 5){
        Vector2<float> starting_pos(starDist(rng), h);

        Vector2<float> starting_dir = (randomInt(rng) % 2) ? Vector2<float>(-1,0) : Vector2<float>(1,0);

        enemies.push_back(Enemy(starting_pos, starting_dir, 5,5));
    }
}

void World::updateEnemies(){
    //Look through all the enemies
    for(auto & e : enemies){
        Vector2<float> pos = e.getPosition();
        //Right side of the screen
        if(pos.x > WIDTH - 2*ENEMY_WIDTH){
            e.direction.x  *= -1;
        }
        //Left side of the screen
        if(pos.x < ENEMY_WIDTH){
            e.direction.x *= -1;
        }

        e.setPosition(pos + e.direction);
    }

}


////////////////////////END ENEMY FUNCTIONS/////////////////////////
//CTOR
World::World() : playerShip(CircleShape(SHIP_RADIUS, 3)){

    shipSettings();
    populateInitialStars();
    makeInitEnemies();
    screen.setFramerateLimit(FRAMERATE);
}
//UPdate all the entities in the game world
void World::update(){
    updateShip();
    updateStars();
    updateBullets();
    updateEnemies();
}

//Draws all the entities to the sfml window
void World::draw(){
    // !!!NTF: Find a way to just loop through all the entities and draw them
    //         instead of having separate loops
    for(const auto & s : stars){
        screen.draw(s);
    }
    for(const auto & b : bullets){
        screen.draw(b);
    }
    for(const auto & e : enemies){
        screen.draw(e);
    }

    screen.draw(playerShip);
}
int World::gameOver(){
    sf::Font font;
    if(!font.loadFromFile("coure.fon")){
            cout<<"Can't find text file"<<endl;
        return -1;
        }
     sf::Text gO(gameOverText,font,30);
     gO.setColor(sf::Color::Red);
    screen.draw(gO);


    return 0;
}
