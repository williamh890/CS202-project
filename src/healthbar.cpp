/*
healthbar.cpp
CS 202 Final Project: Scrolling Space Shooter
Team Members: Michael Bilan, Andrew Cummins, Corey Gray, William Horn, Kyle Tam, Cameron Titus
Created: 22/4/2017
Last Updated: 27/04/2017
Definitions for HealthBar class
*/

#include "healthbar.h"
#include "constants.h"
#include <SFML/Graphics.hpp>
using sf::Vector2f;
using sf::Color;

// Constructor
HealthBar::HealthBar( float length,
                      float width ) : _maxHealthBar(HPBarShape(Vector2f(length, width))),
                                  _currentHealthBar(HPBarShape(Vector2f(length, width)))
{
    _maxHealthBar.setFillColor(Color{0,0,0,0});
    _maxHealthBar.setOutlineColor({255,255,255,200});
    _maxHealthBar.setOutlineThickness(3);

    _currentHealthBar.setFillColor(Color{255, 66, 66,230});

    _currentHealthBar.setPosition(WIDTH - length - HP_BAR_SCREEN_BUFFER, HEIGHT - width -HP_BAR_SCREEN_BUFFER);
    _maxHealthBar.setPosition(WIDTH - length - HP_BAR_SCREEN_BUFFER, HEIGHT - width - HP_BAR_SCREEN_BUFFER);

}

// Destructor
HealthBar::~HealthBar(){}

// Scales the current hp bar to the percentage given
void HealthBar::setCurrentHealthBar(float hpPercentage)
{
    _currentHealthBar.setScale(hpPercentage, 1.0);
}

void HealthBar::setCurrVertical(float hpPercentage)
{
    _currentHealthBar.setScale(1.0, hpPercentage);
}
