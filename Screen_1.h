/*Screen_0.h
Team Members: William Horn, Corey Gray, Michael Bilan, Cameron Titus, Kyle Tam, Andrew Cummins
Created: 17/5/2017
Updated: 17/5/2017
Screen_1 inherits from the Screens.h virtual class; it is an object that controls the game screen.*/

#ifndef SCREEN_1_H_INCLUDED
#define SCREEN_1_H_INCLUDED

#include "Screens.h"
#include <SFML/Graphics.hpp>

class Screen_1 : public Screens{
public:
    virtual int Run(sf::RenderWindow &) override;
};


#endif // SCREEN_1_H_INCLUDED
