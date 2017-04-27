/*
Photon.cpp
CS 202 Final Project
Team Members: Michael Bilan, Andrew Cummins, Corey Gray, William Horn, Kyle Tam, Cameron Titus
Created: 12/4/2017
Last Updated: 27/04/2017
Header for Photon weapon class
*/

#ifndef PHOTON_H
#define PHOTON_H

#include <SFML/Graphics.hpp>
#include "constants.h"
using sf::Drawable;
using sf::RenderTarget;
using sf::RenderStates;
using sf::Transformable;
using sf::VertexArray;
using sf::Vertex;
using sf::FloatRect;
using sf::CircleShape;

class Photon : public Drawable, public Transformable
{
    public:
        Photon(float radius, unsigned int numVertices = PHOTON_EDGES);

        void setPhotonPosition(float x, float y);
        void movePhoton(float delX, float delY);
        FloatRect getGlobalBounds();
		VertexArray _vertices;
		CircleShape _hitBox;
		FloatRect _globalBounds;
		int _damage;
		float _frequency;
		float _moveCounter;

    private:
        virtual void draw(RenderTarget & target, RenderStates states) const
		{
            // Apply the entity's transform -- combine it with the one that was passed by the caller
            states.transform *= getTransform(); // getTransform() is defined by sf::Transformable

            // You may also override states.shader or states.blendMode if you want

            // Draw the vertex array
            target.draw(_vertices, states);
        }
};

#endif // PHOTON_H
