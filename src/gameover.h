// gameover.h
// CS 202 Project: Scrolling Space Shooter
// Team Members: William Horn, Corey Gray, Michael Bilan, Cameron Titus, Kyle Tam, Andrew Cummins
// Created: 20170425
// Updated: 20170426
//
// Header for GameOverScreen class

#ifndef GAMEOVER_H
#define GAMEOVER_H

#include "Screens.h"
#include <SFML/Graphics.hpp>

class GameOverScreen: public Screens{
public:
    virtual int Run(sf::RenderWindow &) override;
};

// Draws the game over screen
void gameOverDraw(sf::RenderWindow &, bool);

#endif
