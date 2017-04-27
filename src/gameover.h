/*
gameover.h
CS 202 Final Project: Scrolling Space Shooter
Team Members: Michael Bilan, Andrew Cummins, Corey Gray, William Horn, Kyle Tam, Cameron Titus
Created: 25/4/2017
Last Updated: 27/04/2017
Header for GameOverScreen class
*/

#pragma once

#include "Screens.h"
#include <SFML/Graphics.hpp>

class GameOverScreen: public Screens{
public:
    virtual int Run(sf::RenderWindow &) override;
};

// Draws the game over screen
void gameOverDraw(sf::RenderWindow &, bool);
