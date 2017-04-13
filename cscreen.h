//Kyle Tam
//cscreen.h

#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
class CScreen{
public:
    virtual int Run(sf::RenderWindow &App)=0 ;

};

class Screen_0 : public CScreen{
private:
    int alpha_max, alpha_div;
    bool playing;
public:
    Screen_0(void);
    virtual int Run(sf::RenderWindow & App);

};

Screen_0::screen_0(void){
    alpha_max = 3*255;
    alpha_div = 3;
    playing = false;
}
