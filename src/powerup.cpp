

#include "constants.h"
#include "powerup.h"
#include "loader.h"

#include <SFML/Graphics.hpp>
using sf::Vector2f;
#include <string>
using std::string;

Powerup::Powerup(Vector2f initPos, int type) : _type(type) {
    //ctor
    string textureFilePath = "";

    //Loads correct texture depending on the type
    if(type == LIFE_UP) {
        textureFilePath = "resources/sprites/extraLife.png";
    }
    else if (type == RELOAD_UP) {
        textureFilePath = "resources/sprites/reloadSpeedPowerUp.png";
    }
    //Load in the texture
    load_texture(_texture, textureFilePath);
    setTexture(_texture);

    //Just woked out that .3 worked for both types
    setScale(.3,.3);
    //Set the position of the powerup
    setPosition(initPos);
}
//Return the type of the powerup
int Powerup::getType() {
    return _type;
};
Powerup::~Powerup() {
    //dtor
}
