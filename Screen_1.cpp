/*Screen_1.cpp
Team Members: William Horn, Corey Gray, Michael Bilan, Cameron Titus, Kyle Tam, Andrew Cummins
Created: 17/5/2017
Updated: 17/5/2017
Screen_1 is the game screen.*/

#include "Screen_1.h"
#include <vector>
using std::vector;


bool firstrun = true;

///////////////////////////STAR FUNCTIONS/////////////////////////////////
// Creates a new star
void makeStar(float startingHeight)
{
	// Sets star size, shape, and color
	sf::Vector2<float> starSize((float)STAR_HEIGHT, (float)STAR_WIDTH);
    StarShape newStar(starSize);

    // Makes a new star with a random position along width of screen
    newStar.setFillColor(sf::Color(255,255,255,starBrightness(rng)));
    //Makes a new star with a random position along with of screen

    float starX = starDist(rng);
    newStar.setPosition(starX, startingHeight);
	stars.push_back(newStar);
}

// Fills screen with stars
void populateInitialStars(){
    for(int h = 0; h < HEIGHT; ++h){
        //This is finicky
        if(!(h % (STAR_SPAWN_RATE*7))){
            makeStar(h);

        }
    }
}

// Move the stars down the screen and deletes them if they fall off
// Also makes stars according to the spawn rate
void updateStars()
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
// Moves bullets up the screen and deletes them if they fall off
void updateBullets()
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

void updatePhotons(){
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
Ship getPlayerShip() {
    return playerShip;

}

// Returns if ship is bounded by the edges of the game window
vector<bounds> onBound(const Ship & playerShip) {
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
void makeInitEnemies(){
    for(int h = 5; h < HEIGHT / 2; h += ENEMY_HEIGHT + 5){
        Vector2<float> starting_pos(starDist(rng), h);

        Vector2<float> starting_dir = (randomInt(rng) % 2) ? Vector2<float>(-1,0) : Vector2<float>(1,0);

        enemies.push_back(Enemy(starting_pos, starting_dir, 5, 5));
    }
}

void updateEnemies(){
    //Look through all the enemies
    for(int e = enemies.size() - 1; e >= 0; --e){
        //Gets the position of the enemy
        Vector2<float> pos = enemies[e].getPosition();

        //Have enemies periodically shoot
        if(randomInt(rng) % 200 == 0){
            //Make a bullet shooting down
            bullets.push_back(Bullet(ENEMY, pos.x, pos.y, Vector2<float>(0, ENEMY_BULLET_SPEED)));
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

                sf::Color currColor = enemies[e].getFillColor();

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

                sf::Color currColor = enemies[e].getFillColor();

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

// Updates all the entities in the game world
void update()
{
    playerShip.update();
    updateStars();
    updateBullets();
    updatePhotons();
    updateEnemies();
}

//Draws all the entities to the SFML window
void show(){
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


int Screen_1::Run(sf::RenderWindow &gameScreen){
    while(true){
        sf::Event event;

        if(firstrun){
            populateInitialStars();
            makeInitEnemies();
        }

        //event loop for screen close/menu return
        while(gameScreen.pollEvent(event)){
            if(event.type == sf::Event::Closed)
                return -1;
            else if(event.type == sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                return 0;
        }

        /* clear/draw/display cycle */
        //Clear needs to be called before stuff can be drawn
        gameScreen.clear(sf::Color::Black);
        gameScreen.update();
        gameScreen.show();
        gameScreen.display();
    }
}
