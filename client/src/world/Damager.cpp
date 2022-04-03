//
// Created by william on 2022-04-03.
//

#include "world/Damager.h"

Damager::Damager() {}

float Damager::getPower() {
    return power;
}

void Damager::setPower(float power){
    this->power = power;
}

void Damager::attack(Damageable* target) {
    target->damage(power);
}
