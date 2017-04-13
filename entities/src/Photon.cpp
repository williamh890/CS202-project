//Asteroid.cpp
//Auth: William Horn
//4.12.2017
//Definitions for Asteroid class

#include "../../globals.h"
#include "../Photon.h"

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
Photon::Photon(unsigned int numVertices) : vertices(VertexArray(TriangleFan, numVertices)){

    vertices[0].position = Vector2<float>(0,0);
    vertices[0].color = Color(200,200,255);

    for(int v = 1; v < (int)numVertices - 1; ++v){
        vertices[v].position = Vector2<float>(cos((2 * PI * v) / (numVertices - 1)) * PHOTON_RADIUS,
                                              sin((2 * PI * v)/ (numVertices - 1)) * PHOTON_RADIUS);
        vertices[v].color =  Color(0, 0, 255, 0);
    }
    vertices[numVertices - 1].position = vertices[1].position;
    vertices[numVertices - 1].color = Color(0, 0, 255, 100);



};

//So the custom object can be drawn on the screen
