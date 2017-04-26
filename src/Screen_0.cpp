/*Screen_0.cpp
Team Members: William Horn, Corey Gray, Michael Bilan, Cameron Titus, Kyle Tam, Andrew Cummins
Created: 17/4/2017
Updated: 17/4/2017
Screen_0 is the game menu screen.*/

#include "Screen_0.h"
#include "Loader.h"
#include "constants.h"

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
using std::string;

//GameMenu Constants
bool drawMenu = true;
bool playing = false;
sf::CircleShape shape;
sf::CircleShape shape2;

string labelFilePath = "resources/sprites/LABELS.png";
sf::Texture newGameLabelTexture;
sf::Sprite newGameLabel;



//Initial Menu Setup
void initialDraw(sf::RenderWindow &gameMenu, bool drawMenu){
    load_texture(newGameLabelTexture, labelFilePath);
    newGameLabel.setTexture(newGameLabelTexture);
    newGameLabel.setTextureRect(sf::IntRect(0,0, 160, 63));
    newGameLabel.setOrigin(160 / 2, 63 / 2.0);
    newGameLabel.setPosition(250,200);

    shape.setRadius(50);
    shape.setOrigin(shape.getRadius(),shape.getRadius());
    shape.setPosition(250, 200);
    shape.setFillColor(sf::Color::Green);

    shape2.setRadius(50);
    shape2.setOrigin(shape2.getRadius(),shape2.getRadius());
    shape2.setPosition(250,500);
    shape2.setFillColor(sf::Color::Red);

    gameMenu.clear();
    gameMenu.draw(shape);
    gameMenu.draw(shape2);
    gameMenu.draw(newGameLabel);
    gameMenu.display();
    drawMenu = false;
}

int MenuScreen::Run(sf::RenderWindow &gameMenu){
    sf::Event event;
    int menuSelect=0;

    //checks if game flag is true; if it is, changes menu option to Continue game
    if(playing){
        shape.setFillColor(sf::Color::Red);
        gameMenu.draw(shape);
    }

    if(drawMenu) initialDraw(gameMenu,drawMenu);

    while(true){
        //check SFML events
        while(gameMenu.pollEvent(event)){
            //check if window has been closed
            if (event.type == sf::Event::Closed) return -1;
            //check for key presses
            if(event.type == sf::Event::KeyPressed){
                switch (event.key.code){
                    case sf::Keyboard::Up:
                        menuSelect=0;
                        break;
                    case sf::Keyboard::Down:
                        menuSelect=1;
                        drawMenu = true;
                        break;
                    case sf::Keyboard::Return:
                        if (menuSelect==0){
                            playing=true;
                            return 1; //starts game
                        }
                        else if (menuSelect==1) return -1;
                        break;
                    case sf::Keyboard::Escape:
                            return -1;
                    default:
                        menuSelect=-1; //all other keys clear selection
                        break;
                }
            }
            //Use the joystick to check the input
            int detectionThreshold = 98;
            if(sf::Joystick::isConnected(0)){
                //If the joystick is pressed halfway up just select
                if(sf::Joystick::getAxisPosition(0,sf::Joystick::Y) <= -detectionThreshold / 2) {
                    menuSelect = 0;
                    //If the right trigger is pushed

                }
                if (sf::Joystick::isButtonPressed(0, A) && menuSelect == 0){
                            playing=true;
                            return 1; //starts game
                    }
                if(sf::Joystick::getAxisPosition(0,sf::Joystick::Y) >= detectionThreshold / 2) {
                    menuSelect = 1;
                }
                if (sf::Joystick::isButtonPressed(0, A) && menuSelect == 1) {
                        return -1;
                }

            }
            //update menu text colors based on selection
            if(menuSelect==0){
                shape.setFillColor(sf::Color::Blue);
                shape2.setFillColor(sf::Color::Red);
            }
            else if (menuSelect==1){
                if(playing)
                    shape.setFillColor(sf::Color::Cyan);
                else
                    shape.setFillColor(sf::Color::Green);
                shape2.setFillColor(sf::Color::Blue);
            }
            else{
                if(playing)
                    shape.setFillColor(sf::Color::Cyan);
                else
                    shape.setFillColor(sf::Color::Green);
                shape2.setFillColor(sf::Color::Red);
            }

            //clears the screen
            gameMenu.clear();

            //draw text menu - WON'T WORK UNTIL FONT IMPORTS WORK
            /*gameMenu.draw(menu1);
            gameMenu.draw(menu2);*/

            //display the screen
            gameMenu.draw(shape);
            gameMenu.draw(shape2);
            gameMenu.draw(newGameLabel);
            gameMenu.display();
        }
    }
};
