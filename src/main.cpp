/*
main.cpp
CS 202 Final Project: Scrolling Space Shooter
Team Members: Michael Bilan, Andrew Cummins, Corey Gray, William Horn, Kyle Tam, Cameron Titus
Created: 9/4/2017
Last Updated: 27/04/2017
main.cpp contains the game RenderWindow object, as well as stores a vector of pointers to Screens objects (pure virtual).
New screens are declared in main and stored the the Screens vector by reference; additional screens can be implemented in
main by adding the appropriate header file include, creating a new screen object (must inherit from Screens.h) and storing
it in the screens vector.
The runtime loop manages screens by setting the screenSelect to a value return by each screen's run function.
*/

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
