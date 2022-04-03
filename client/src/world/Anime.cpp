//
// Created by william on 2022-04-03.
//

#include "world/Anime.h"

void Anime::insertFrame(sf::Texture* attackTexture) {
    animationFrames.push_back(attackTexture);
}

void Anime::setStateSprite(sf::Sprite* sprite) {
    this->sprite = sprite;
}

void Anime::animate(float delta) {
    timeSinceLastFrame += delta;
    if (timeSinceLastFrame >= msBetweenFrames) {
        if (currentFrame >= animationFrames.size()) {
            currentFrame = 0;
        }

        sprite->setTexture(*animationFrames.at(currentFrame));

        currentFrame++;
        timeSinceLastFrame = 0;
    }
}

void Anime::resetAnimationState() {
    sprite->setTexture(*animationFrames.at(0));
}