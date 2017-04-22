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

}
HealthBar::~HealthBar(){}

float HealthBar::getHealth(){
    return _CurrentHealth;

}
float HealthBar::damage(float damageDealt){
    return damageDealt *DAMAGE_MODIFIER;
}


void HealthBar::drawHealthBar(){

}
void HealthBar::updateHealthBar(){

}
