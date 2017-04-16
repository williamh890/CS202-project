
#include "../interface.h"

#include <SFML/Graphics.hpp>
using sf::Color;
using sf::Font;

#include <exception>
using std::runtime_error;
#include <string>
using std::string;

//constructor
Interface::Interface() {
    //Color of the text
    Color textColor{216, 216, 216};
    string fontRelPath = "resources/fonts/interface_font(Orbitron)/Orbitron-Regular.ttf";
    //Load the font from the file
    if(!livesCaptionFont.loadFromFile(fontRelPath)) {
        throw runtime_error("Interface::Interface - Error loading lives caption font...");
    }

    //Set the font to one just loaded
    //livesCaption.setFont(livesCaptionFont);
    livesCaption.setString("Lives");
    livesCaption.setFillColor(textColor);
}

