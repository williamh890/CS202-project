//Kyle Tam
//CS202 project
// April 25,2017
//gameover.h
#pragma once

#include "Screens.h"
#include <SFML/Graphics.hpp>

class GameOverScreen: public Screens{
public:
    virtual int Run(sf::RenderWindow &) override;
};
void initalDraw();
