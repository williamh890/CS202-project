//Kyle Tam
//Healthbar.cpp
// 4-22-17
//Last Rev 4-22-17

#include "healthbar.h"
#include "constants.h"
#include <SFML/Graphics.hpp>
using sf::Vector2f;
using sf::Color;

HealthBar::HealthBar( float l,
                      float w ) : maxHealthBar(HPBarShape(Vector2f(l,w))),
                                  currentHealthBar(HPBarShape(Vector2f(l, w)))
{
    maxHealthBar.setFillColor(Color{0,0,0,0});
    maxHealthBar.setOutlineColor({255,255,255,200});
    maxHealthBar.setOutlineThickness(3);

    currentHealthBar.setFillColor(Color{255, 66, 66,230});

    currentHealthBar.setPosition(WIDTH - l - HP_BAR_SCREEN_BUFFER, HEIGHT - w -HP_BAR_SCREEN_BUFFER);
    maxHealthBar.setPosition(WIDTH - l - HP_BAR_SCREEN_BUFFER, HEIGHT - w - HP_BAR_SCREEN_BUFFER);

}
HealthBar::~HealthBar(){}

void HealthBar::setCurrentHealthBar(float hpPercentage) {
    //Scales the current hp bar to the percentage given
    currentHealthBar.setScale(hpPercentage, 1.0);
};
