//
// Created by william on 2022-04-03.
//

#ifndef LD50_CLIENT_DAMAGER_H
#define LD50_CLIENT_DAMAGER_H

#include "SFML/Graphics.hpp"
#include "Entity.h"

class Damageable;

class Damager : virtual public Entity {
private:
    float power = 1;
    bool destroyed = false;
    float msAttackInterval = 1000;
    float msSinceLastAttack = 0;

public:
    Damager();

    void setPower(float power);

    float getPower();

    float getMsAttackInterval() const;

    void setMsAttackInterval(float msAttackInterval);

    float getMsSinceLastAttack() const;

    void setMsSinceLastAttack(float msSinceLastAttack);

    void attack(Damageable* target);
};

#endif //LD50_CLIENT_DAMAGER_H
