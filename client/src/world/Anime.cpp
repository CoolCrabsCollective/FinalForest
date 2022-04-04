//
// Created by william on 2022-04-03.
//

#include "world/Anime.h"

void Anime::insertAttackFrame(sf::Texture* attackTexture) {
    attackFrames.push_back(attackTexture);
}

void Anime::setStateSprite(sf::Sprite* sprite) {
    this->sprite = sprite;
}

void Anime::tickAttackAnimation(float delta) {
	if(attackFrames.empty())
		return;

    timeSinceLastAttackFrame += delta;
    if (currentAttackFrame >= attackFrames.size()) {
        currentAttackFrame = 0;
    }

    sprite->setTexture(*attackFrames.at(currentAttackFrame));

    currentAttackFrame++;
    timeSinceLastAttackFrame = 0;
}

void Anime::resetAttackAnimation() {
	if(attackFrames.empty())
		return;
    sprite->setTexture(*attackFrames.at(0));
}