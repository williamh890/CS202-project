// main.cpp
// CS 202 Project: Scrolling Space Shooter
// Team Members: William Horn, Corey Gray, Michael Bilan, Cameron Titus, Kyle Tam, Andrew Cummins
// Created: 20170410
// Updated: 20170412
// 
// Game loop

#include <SFML/Graphics.hpp>
using sf::Event;
using sf::Color;

#include "constants.h"
#include "world.h"

int main()
{
    // Initializes world
	World world;

    // Runs for as long as the window is open
    while(world.screen.isOpen())
	{
        // Gets all the events since the last iteration
        Event event;
        
		///////EVENT LOOP/////////
        while(world.screen.pollEvent(event))
		{
            //Act appropriately for different events
			if(event.type == sf::Event::Closed)
			{
				world.screen.close();
            }
            
			//else if(event.type == sf::Event::KeyPressed){}
        }
		///////END EVENT LOOP///////

        // Clear/Draw/Display cycle
        world.screen.clear(Color::Black); // Clear needs to be called before stuff can be drawn
        world.update();
        world.draw();
        world.screen.display();
    }

    return 0;
}
