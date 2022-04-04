//
// Created by william on 2022-04-03.
//

#ifndef LD50_CLIENT_ANIME_H
#define LD50_CLIENT_ANIME_H

#include "SFML/Graphics.hpp"

class Anime {
private:
    std::vector<sf::Texture*> attackFrames;
    float msBetweenAttackFrames = 300.0f;
    float timeSinceLastAttackFrame = 0.0f;
    int currentAttackFrame = 0;

    sf::Sprite* sprite;

protected:
    void insertAttackFrame(sf::Texture* attackTexture);
    void setStateSprite(sf::Sprite* sprite);

public:
    void tickAttackAnimation(float delta);
    void resetAttackAnimation();
    void runFullAttackAnimation();

};

#endif //LD50_CLIENT_ANIME_H
