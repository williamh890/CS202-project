#ifndef INTERFACE_H
#define INTERFACE_H

#include <SFML/Graphics.hpp>
#include <vector>

class Interface{
    public:
        Interface();

    private:
        sf::Font livesCaptionFont;
        sf::Text livesCaption;
        std::vector<sf::RectangleShape> lives;

        sf::Texture heart;
};

#endif // INTERFACE_H
