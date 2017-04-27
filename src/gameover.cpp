//Kyle Tam
//CS202 project
// April 25,2017
//gameover.h

#include "gameover.h"
#include "Ship.h"
#include "constants.h"


#include <SFML/Graphics.hpp>
#include "Loader.h"


extern const float WIDTH;
extern const float HEIGHT;
extern bool playerIsDead;
bool drawGameOver=true;
sf::Texture gameOverTexture;
sf::Sprite TextBox;


void initalDraw(sf::RenderWindow & gameMenu, bool drawGameOver){

    TextBox.setPosition(0,0);
    load_texture(gameOverTexture, "resources/sprites/GAME_OVER.png");
    TextBox.setTexture(gameOverTexture);
    TextBox.setTextureRect(sf::IntRect(0,0,WIDTH,HEIGHT));

    gameMenu.clear();
    gameMenu.draw(TextBox);
    gameMenu.display();
    drawGameOver=false;
}


int GameOverScreen::Run(sf::RenderWindow & gameMenu){
    sf::Event event;


    if(drawGameOver)
        initalDraw(gameMenu,drawGameOver);
    while(true){
        while(gameMenu.pollEvent(event)){
            //check closed window
            if(event.type==sf::Event::Closed)
                return -1;
            if(event.type==sf::Event::KeyPressed){
                switch(event.key.code){
                case sf::Keyboard::Escape:
                    return -1;
                    break;
                    //If the user hits escape close the window
                case sf::Keyboard::Return:
                 //   playerIsDead=false;
                    return 1;
                    break;
                    //If user hits enter restart the game?
                default:
                    break;
                }
            }
            gameMenu.clear();
            gameMenu.draw(TextBox);
            gameMenu.display();
        }
    }

}
