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

void Damager::setAttackTexture(sf::Texture* attackTexture) {
    this->attackTexture = attackTexture;
}

void Damager::setAttackStateSprite(sf::Sprite* sprite) {
    this -> sprite = sprite;
}

void Damager::attack(Damageable* target) {
    target->damage(power);
}
