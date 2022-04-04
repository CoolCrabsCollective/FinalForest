//
// Created by william on 2022-04-03.
//

#ifndef LD50_CLIENT_ANIMEATTACK_H
#define LD50_CLIENT_ANIMEATTACK_H

#include "SFML/Graphics.hpp"

class AnimeAttack {
private:
    std::vector<sf::Texture*> attackFrames;
    float msBetweenAttackFrames = 500.0f;
    float timeSinceLastAttackFrame = 0;
    int currentAttackFrame = 0;

    bool isAnimating = false;

    sf::Sprite* sprite;

protected:
    void insertAttackFrame(sf::Texture* attackTexture);
    void setStateSprite(sf::Sprite* sprite);

public:
    void tickAttackAnimation();
    void startAttackAnimation();
    void runAttackAnimation(float delta);
    void resetAttackAnimation();
};

#endif //LD50_CLIENT_ANIMEATTACK_H
