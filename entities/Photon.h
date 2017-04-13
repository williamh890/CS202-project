//Asteroid.h
//Auth: William Horn
//4.12.2017
//Definitions for Asteroid class
#ifndef PHOTON_H
#define PHOTON_H


#include <SFML/Graphics.hpp>
using sf::Drawable;
using sf::RenderTarget;
using sf::RenderStates;
using sf::Transformable;
using sf::VertexArray;
using sf::Vertex;
using sf::FloatRect;

class Photon : public Drawable, public Transformable{

    public:
        Photon(unsigned int numVertices = PHOTON_EDGES);
        FloatRect getGlobalBounds();
    private:
        virtual void draw(RenderTarget & target, RenderStates states) const{
            // apply the entity's transform -- combine it with the one that was passed by the caller
            states.transform *= getTransform(); // getTransform() is defined by sf::Transformable

            // you may also override states.shader or states.blendMode if you want

            // draw the vertex array
            target.draw(vertices, states);
        }

        VertexArray vertices;
        FloatRect globalBounds;
};


#endif // PHOTON_H
