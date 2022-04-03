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
    sf::Texture* attackTexture;
    sf::Sprite* sprite;

public:
    Damager();

    void setPower(float power);

    float getPower();

    void setAttackTexture(sf::Texture* attackTexture);

    void setAttackStateSprite(sf::Sprite* sprite);

    void attack(Damageable* target, float delta);
};

#endif //LD50_CLIENT_DAMAGER_H
