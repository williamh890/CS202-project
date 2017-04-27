// main.cpp
// CS 202 Project: Scrolling Space Shooter
// Team Members: William Horn, Corey Gray, Michael Bilan, Cameron Titus, Kyle Tam, Andrew Cummins
// Created: 201704??
// Updated: 20170426
//
// Game framework

#include "constants.h"
#include "Screens.h"
#include "Screen_0.h"
#include "gameover.h"
#include "World.h"
#include "Photon.h"

#include <SFML/Graphics.hpp>
using sf::Event;
using sf::Color;
#include <vector>
using std::vector;

int main()
{
    // Vector of screens, holds all game screens
    std::vector<Screens*> screens;
    
	// Manages which screen to run; -1 indicates close status
    int screenSelect=0;

    // Create game window
    sf::RenderWindow App(sf::VideoMode((unsigned)WIDTH, (unsigned)HEIGHT), "SPACE GAME");
    App.setFramerateLimit(FRAMERATE);

    // Hide mouse cursor
    App.setMouseCursorVisible(false);

    // Make main menu
    MenuScreen ms;
    screens.push_back(&ms);
    
	// Make game world
    World gw;
    screens.push_back(&gw);
    GameOverScreen go;
    screens.push_back(&go);

    // Main game loop
    while(screenSelect>=0)
	{
        screenSelect = screens[screenSelect]->Run(App);
    }
    
	// Return value set but should not happen
    return 0;
}
