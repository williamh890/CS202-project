/*
healthbar.h
CS 202 Final Project: Scrolling Space Shooter
Team Members: Michael Bilan, Andrew Cummins, Corey Gray, William Horn, Kyle Tam, Cameron Titus
Created: 20/4/2017
Last Updated: 27/04/2017
Header for HealthBar class
*/

#include "constants.h"

#ifndef HEALTHBAR_H
#define HEALTHBAR_H

class HealthBar {

public:
    HealthBar(float length = HP_BAR_LEN, float width = HP_BAR_WIDTH);
    virtual  ~HealthBar();

    void setCurrentHealthBar(float hpPercentage);
    void setCurrVertical(float hpPercentage);

    HPBarShape _maxHealthBar;
    HPBarShape _currentHealthBar;
};

typedef HealthBar ReloadBar;

#endif // HEALTHBAR_H
