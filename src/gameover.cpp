// gameover.cpp
// CS 202 Project: Scrolling Space Shooter
// Team Members: William Horn, Corey Gray, Michael Bilan, Cameron Titus, Kyle Tam, Andrew Cummins
// Created: 20170425
// Updated: 20170426
//
// Definitions for GameOverScreen class

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

// Draws the game over screen
void gameOverDraw(sf::RenderWindow & gameMenu, bool drawGameOver)
{
    TextBox.setPosition(0,0);
    load_texture(gameOverTexture, "resources/sprites/GAME_OVER.png");
    TextBox.setTexture(gameOverTexture);
    TextBox.setTextureRect(sf::IntRect(0,0,(int)WIDTH,(int)HEIGHT));

    gameMenu.clear();
    gameMenu.draw(TextBox);
    gameMenu.display();
    drawGameOver=false;
}

// Draws and listens for input on the Game Over screen
int GameOverScreen::Run(sf::RenderWindow & gameMenu){
    sf::Event event;

    if(drawGameOver)
        gameOverDraw(gameMenu,drawGameOver);

    while(true)
	{
        while(gameMenu.pollEvent(event))
		{
            // Check closed window
            if(event.type==sf::Event::Closed)
                return -1;

			// Checks for input
            if(event.type==sf::Event::KeyPressed)
			{
                switch(event.key.code)
				{
				// If the user hits escape, close the window
				case sf::Keyboard::Escape:
                    return -1;
                    break;
                
				// If user hits enter, restart the game
                case sf::Keyboard::Return:
                    return 1;
                    break;
                    
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
