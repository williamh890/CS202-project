/*Screen_0.cpp
Team Members: William Horn, Corey Gray, Michael Bilan, Cameron Titus, Kyle Tam, Andrew Cummins
Created: 17/4/2017
Updated: 26/4/2017
Screen_0 is the game menu screen.*/

//#include <iostream>
#include "Screen_0.h"

// GameMenu Constants
bool drawMenu = true;
bool playing = false;
sf::CircleShape shape;
sf::CircleShape shape2;

// Initial Menu Setup
void menuDraw(sf::RenderWindow &gameMenu, bool drawMenu)
{
    shape.setRadius(50);
    shape.setOrigin(shape.getRadius(),shape.getRadius());
    shape.setPosition(250, 200);
    shape.setFillColor(sf::Color::Green);

    shape2.setRadius(50);
    shape2.setOrigin(shape2.getRadius(),shape2.getRadius());
    shape2.setPosition(250,500);
    shape2.setFillColor(sf::Color::Red);

    gameMenu.clear();
    gameMenu.draw(shape);
    gameMenu.draw(shape2);
    gameMenu.display();
    drawMenu = false;
}

int MenuScreen::Run(sf::RenderWindow &gameMenu)
{
    sf::Event event;
    int menuSelect=0;

    // Checks if game flag is true; if it is, changes menu option to Continue game
    if(playing)
	{
        shape.setFillColor(sf::Color::Red);
        gameMenu.draw(shape);
    }

    if(drawMenu) menuDraw(gameMenu,drawMenu);

    while(true)
	{
        // Check SFML events
        while(gameMenu.pollEvent(event))
		{
            // Check if window has been closed
            if (event.type == sf::Event::Closed) return -1;
            
			//Check for key presses
            if(event.type == sf::Event::KeyPressed)
			{
                switch (event.key.code)
				{
                    case sf::Keyboard::Up:
                        menuSelect=0;
                        break;
                    
					case sf::Keyboard::Down:
                        menuSelect=1;
                        drawMenu = true;
                        break;
                    
					case sf::Keyboard::Return:
                        if (menuSelect==0)
						{
                            playing=true;
                            return 1; // Starts game
                        }
                        else if (menuSelect==1) return -1;
                        break;
                    
					case sf::Keyboard::Escape:
                            return -1;
                    
					default:
                        menuSelect=-1; // All other keys clear selection
                        break;
                }
            }
            
			// Update menu text colors based on selection
            if(menuSelect==0)
			{
                shape.setFillColor(sf::Color::Blue);
                shape2.setFillColor(sf::Color::Red);
            }
            
			else if (menuSelect==1)
			{
                if(playing)
                    shape.setFillColor(sf::Color::Cyan);
                
				else
                    shape.setFillColor(sf::Color::Green);
                
				shape2.setFillColor(sf::Color::Blue);
            }
            
			else
			{
                if(playing)
                    shape.setFillColor(sf::Color::Cyan);
            
				else
                    shape.setFillColor(sf::Color::Green);
                
				shape2.setFillColor(sf::Color::Red);
            }

            // Clears the screen
            gameMenu.clear();

            //draw text menu - WON'T WORK UNTIL FONT IMPORTS WORK
            /*gameMenu.draw(menu1);
            gameMenu.draw(menu2);*/

            // Display the screen
            gameMenu.draw(shape);
            gameMenu.draw(shape2);
            gameMenu.display();
        }
    }
};
