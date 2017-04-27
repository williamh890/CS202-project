/*
powerup.h
CS 202 Final Project: Scrolling Space Shooter
Team Members: Michael Bilan, Andrew Cummins, Corey Gray, William Horn, Kyle Tam, Cameron Titus
Created: 26/4/2017
Last Updated: 27/04/2017
Header for Powerup class
*/

#ifndef POWERUP_H
#define POWERUP_H

#include <SFML/Graphics.hpp>
//Simple sprite for powerups all the mechanics of the powerups are done in the ship and world classes
class Powerup : public sf::Sprite {
    public:
        Powerup(sf::Vector2f initPos, int type);

        virtual ~Powerup();
        //Returns the type of the powerup
        int getType();

    private:
        //Store what type of powerup it is
        int _type;
        //The texture for the powerup
        sf::Texture _texture;
};

#endif // POWERUP_H
