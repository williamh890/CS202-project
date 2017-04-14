//Ship.cpp
//Auth : William Horn
//4.12.2017
//Definitions for ship class

#include "../../globals.h"
#include "../Ship.h"

#include <SFML/Graphics.hpp>
using sf::Color;
#include <vector>
using std::vector;

Ship::Ship() : ShipShape(SHIP_RADIUS, 3), sourceID(PLAYER){
    int outline = 2;

    this->setRadius(SHIP_RADIUS);
    this->setOutlineThickness(outline);

    Color outlineColor{183, 183, 183};
    Color fillColor{42, 197, 224};

    this->setFillColor(fillColor);
    this->setOutlineColor(outlineColor);

    this->setPosition(WIDTH / 2, HEIGHT - 2.5*SHIP_RADIUS);
}

void Ship::photonCannon(vector<Photon> & photons){
    Photon newPhoton{PHOTON_RADIUS};

    float X = getPosition().x + .7*SHIP_RADIUS;
    float Y = getPosition().y - .7*SHIP_RADIUS;

    newPhoton.setPhotonPosition(X, Y);
    photons.push_back(newPhoton);
}
