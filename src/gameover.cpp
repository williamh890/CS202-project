//Kyle Tam
//CS202 project
// April 25,2017
//gameover.h

#include "gameover.h"
#include "Ship.h"
#include "constants.h"


#include <SFML/Graphics.hpp>


extern const float WIDTH;
extern const float HEIGHT;
extern bool playerIsDead;
bool drawGameOver=true;

sf::RectangleShape TextBox;

void initalDraw(sf::RenderWindow & gameMenu, bool drawGameOver){
    TextBox.setFillColor(sf::Color::Red);
    TextBox.setSize(sf::Vector2f(400,200));
    TextBox.setPosition(50,HEIGHT/2.0);

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
