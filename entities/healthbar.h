//healthbar.h
//Kyle Tam
//4-20-17
//Last rev 4-20-17

#pragma once
class HealthBar{
public:
        HealthBar();
      virtual  ~HealthBar();
    float getHealth();
    float damage(float damageDealt);
protected:
    float _Health;
    float _MaxHealth;
    bool _IsDead;

};

class ShipHealthBar : public HeallthBar{
public:
    ShipHealthBar();
    virtual ~ShipHealthBar() ;
    void drawHealthBar();
    void updateHealthBar();
};
