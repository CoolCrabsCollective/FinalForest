//
// Created by william on 2022-04-03.
//

#ifndef LD50_CLIENT_ANIMEATTACK_H
#define LD50_CLIENT_ANIMEATTACK_H

#include "SFML/Graphics.hpp"
#include "Anime.h"

class AnimeAttack: public Anime {
public:
    void startAttackAnimation();
    void runAttackAnimation(float delta);
    void resetAttackAnimation();

    void insertAttackFrame(sf::Texture* attackTexture);
    void setAttackStateSprite(sf::Sprite* sprite);
};

#endif //LD50_CLIENT_ANIMEATTACK_H
