//asteroids.cpp
//CS 202 Final Proj
//Auth: William Horn
//Rough draft for game framework

#include "constants.h"
#include "Screens.h"
#include "Screen_0.h"
#include "Screen_1.h"
#include "World.h"
#include "entities/Photon.h"

#include <SFML/Graphics.hpp>
using sf::Event;
using sf::Color;
#include <vector>
using std::vector;

int main(){
    //vector of screens, holds all game screens
    std::vector<Screens*> screens;
    //manages which screen to run; -1 indicates close status
    int screen=0;

    //create game window
    sf::RenderWindow App(sf::VideoMode(WIDTH, HEIGHT), "SPACE GAME");
    App.setFramerateLimit(FRAMERATE);

    //hide mouse cursor
    App.setMouseCursorVisible(false);

    //Make screens
    Screen_0 s0;
    screens.push_back(&s0);
    Screen_1 s1;
    screens.push_back(&s1);

    //main game loop
    while(screen>=0){
        screen = screens[screen]->Run(App);
    }
    //return value set, should not happen
    return 0;
}
