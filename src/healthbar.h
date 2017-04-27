// healthbar.h
// CS 202 Project: Scrolling Space Shooter
// Team Members: William Horn, Corey Gray, Michael Bilan, Cameron Titus, Kyle Tam, Andrew Cummins
// Created: 20170412
// Updated: 20170426
//
// Header for HealthBar class

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
