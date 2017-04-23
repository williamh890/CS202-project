//healthbar.h
//Kyle Tam
//4-20-17
//Last rev 4-22-17
#include "constants.h"
#include "World.h"


#pragma once
class HealthBar:public HPBarShape{
public:
        HealthBar();
      virtual  ~HealthBar();
    float getHealth();
    void damage(float damageDealt);
    void drawHealthBar();
    void updateHealthBar(World& world);
private:
    float _CurrentHealth;
    float _MaxHealth;


};

