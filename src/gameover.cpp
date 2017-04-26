//Kyle Tam
//CS202 project
// April 25,2017
//gameover.h

#include "gameover.h"
#include "Ship.h"



#include <SFML/Graphics.hpp>



extern bool playerIsDead;
bool drawGameOver=true;

sf::RectangleShape TextBox;

void initalDraw(){

}


int GameOverScreen::Run(sf::RenderWindow & gameMenu){
    sf::Event event;
    int menuSelect =7;
    if(playerIsDead){//If player is dead draw the gameover text
        shape.setFillColor(sf::Color::Red);
        gameMenu.draw(TextBox);
    }
    if(drawGameOver)
        initalDraw(gameMenu,drawGameOver);
    while(true){
        while(gameMenu.pollEvent(event)){
            //check closed window
            if(event.type==sf::Event::Closed)
                return -1;

        }
    }

}
