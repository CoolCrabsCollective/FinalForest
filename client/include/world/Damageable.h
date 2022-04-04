//
// Created by william on 2022-04-03.
//

#ifndef LD50_CLIENT_DAMAGEABLE_H
#define LD50_CLIENT_DAMAGEABLE_H

#include "SFML/Graphics.hpp"

class Damageable {
private:
    float health;
    bool destroyed = false;
    sf::Texture* destroyedTexture = nullptr;
    sf::Sprite* sprite;

public:
    float maxHealth;

    Damageable();

    float getHealth();

    void setHealth(float health);

    virtual void damage(float attack);

    void setDestroyedTexture(sf::Texture* destroyedTexture);

    void setDamageStateSprite(sf::Sprite* sprite);

    bool isDestroyed() const;
};

#endif //LD50_CLIENT_DAMAGEABLE_H
