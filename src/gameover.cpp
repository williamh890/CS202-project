/*
gameover.cpp
CS 202 Final Project: Scrolling Space Shooter
Team Members: Michael Bilan, Andrew Cummins, Corey Gray, William Horn, Kyle Tam, Cameron Titus
Created: 25/4/2017
Last Updated: 27/04/2017
Definitions for GameOverScreen class
*/

#include "gameover.h"
#include "Ship.h"
#include "constants.h"
#include "Loader.h"

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>


extern const float WIDTH;
extern const float HEIGHT;
extern bool playerIsDead;
bool drawGameOver=true;
sf::Texture gameOverTexture;
sf::Sprite TextBox;
sf::SoundBuffer gameOverSoundBuffer;
sf::Sound gameOverSound;

// Draws the game over screen
void gameOverDraw(sf::RenderWindow & gameMenu, bool drawGameOver)
{
    //set the position of the gameover object, and display the textured image fullscreen
    TextBox.setPosition(0,0);
    load_texture(gameOverTexture, "resources/sprites/GAME_OVER.png");
    TextBox.setTexture(gameOverTexture);
    TextBox.setTextureRect(sf::IntRect(0,0,(int)WIDTH,(int)HEIGHT));

    //play the game over sound fx
    load_buffer(gameOverSoundBuffer, "resources/sound/gameOverSound.wav");
    gameOverSound.setBuffer(gameOverSoundBuffer);
    gameOverSound.play();


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

				// TODO: Make a way for players to restart the game
                // case sf::Keyboard::Return:
                //     return 1;
                //     break;

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
