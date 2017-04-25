//Kyle Tam
//Healthbar.cpp
// 4-22-17
//Last Rev 4-22-17

#include "healthbar.h"
#include "constants.h"
#include <SFML/Graphics.hpp>

HealthBar::HealthBar(){
 _MaxHealth =100.00;
 _CurrentHealth=_MaxHealth;
 drawHealthBar();


}
HealthBar::~HealthBar(){}

float HealthBar::getHealth(){
    return _CurrentHealth;

}
void HealthBar::damage(float damageDealt){
    _CurrentHealth-= damageDealt *DAMAGE_MODIFIER;
}


void HealthBar::drawHealthBar(){
    sf::RectangleShape MaxHealthBar(sf::Vector2f(_MaxHealth,25));
    MaxHealthBar.setFillColor(sf::Color(255,7,52));
    sf::RectangleShape CurrentHealthBar(sf::Vector2f(_CurrentHealth,25));
       CurrentHealthBar.setFillColor(sf::Color(7,255,36));
    //Make two health bars to show depletion


}
void HealthBar::updateHealthBar(World & world){

}
