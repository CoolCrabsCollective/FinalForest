//
// Created by william on 2022-04-03.
//

#ifndef LD50_CLIENT_DAMAGER_H
#define LD50_CLIENT_DAMAGER_H

#include "SFML/Graphics.hpp"
#include "Damageable.h"

class Damager {
private:
    float power = 1;
    bool destroyed = false;

public:
    Damager();

    void setPower(float power);

    float getPower();

    void attack(Damageable* target);
};

#endif //LD50_CLIENT_DAMAGER_H
