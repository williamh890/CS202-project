/*Screen_0.cpp
Team Members: William Horn, Corey Gray, Michael Bilan, Cameron Titus, Kyle Tam, Andrew Cummins
Created: 17/4/2017
Updated: 17/4/2017
Screen_0 is the game menu screen.*/

#include <iostream>
#include "Screen_0.h"

int Screen_0::Run(sf::RenderWindow &gameMenu){
    sf::Event event;
    sf::Font font;
    sf::Text menu1;
    sf::Text menu2;
    int menuSelect;
    bool playing = false;

    //checks for font file -- GETTING ERROR undefined reference to `sf::Font::loadFromFile(std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > const&)'|
    //supposedly this is error due to compiler/SFML build error - reinstalling both did not fix it
//    if(!font.loadFromFile("corbel-italic.ttf")){
//        std::cerr << "Error loading corbel-italic.ttf" << std::endl;
//        return -1;
//    }

    menu1.setFont(font);
    menu1.setCharacterSize(20);
    menu1.setString("New Game");
    menu1.setPosition({250, 600});

    menu2.setFont(font);
    menu2.setCharacterSize(20);
    menu2.setString("Exit");
    menu2.setPosition({250, 450});

    //checks if game flag is true; if it is, changes menu option to Continue game
    if(playing){
        menu1.setString("Continue");
    }

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
                        break;
                    case sf::Keyboard::Return:
                        if (menuSelect==0){
                            playing = true; //sets flag for holding game window
                            return 1; //starts game
                        }
                        else return -1; //closes game
                        break;
                    default:
                        break;
                }
            }
            //update menu text colors based on selection
            if(menuSelect==0){
                menu1.setFillColor(sf::Color::Blue);
                menu2.setFillColor(sf::Color::White);
            }
            else if (menuSelect==1){
                menu1.setFillColor(sf::Color::White);
                menu2.setFillColor(sf::Color::Blue);
            }
            else{
                menu1.setFillColor(sf::Color::White);
                menu2.setFillColor(sf::Color::White);
            }

            //clears the screen
            gameMenu.clear();

            //draw text menu - WON'T WORK UNTIL FONT IMPORTS WORK
            /*gameMenu.draw(menu1);
            gameMenu.draw(menu2);*/

            //display the screen
            gameMenu.display();

        }
    }
};
