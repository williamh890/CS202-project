//Asteroid.cpp
//Auth: William Horn
//4.12.2017
//Definitions for Asteroid class

#include "../../globals.h"
#include "../Asteroid.h"

#include <SFML/Graphics.hpp>
using sf::TriangleFan;
using sf::Triangles;
using sf::TriangleStrip;
using sf::VertexArray;
using sf::Vertex;
using sf::Vector2;
using sf::Color;
#include <cmath>
using std::cos;
using std::sin;

//Ctor
Asteroid::Asteroid(unsigned int numVertices) : vertices(VertexArray(TriangleFan, numVertices)){

    vertices[0].position = Vector2<float>(0,0);
    vertices[0].color =  Color(142, 105, 41);

    for(int v = 1; v < (int)numVertices; ++v){
        vertices[v].position = Vector2<float>(cos((2.4*PI * v) / numVertices) * 50, sin((2.4*PI*v)/ numVertices) * 100);
        vertices[v].color =  Color(142, 105, 41);
    }

};

//So the custom object can be drawn on the screen
