//Asteroid.h
//Auth: William Horn
//4.12.2017
//Definitions for Asteroid class

#include <SFML/Graphics.hpp>
using sf::Drawable;
using sf::RenderTarget;
using sf::RenderStates;
using sf::Transformable;
using sf::VertexArray;
using sf::Vertex;

class Asteroid : public Drawable, public Transformable{

    public:
        Asteroid(unsigned int numVertices);

    private:
        virtual void draw(RenderTarget & target, RenderStates states) const{
            // apply the entity's transform -- combine it with the one that was passed by the caller
            states.transform *= getTransform(); // getTransform() is defined by sf::Transformable

            // you may also override states.shader or states.blendMode if you want

            // draw the vertex array
            target.draw(vertices, states);
        }

        VertexArray vertices;

};
