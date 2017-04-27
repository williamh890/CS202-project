

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
