//
// Created by william on 2022-04-03.
//

#include "world/anime/AnimeAttack.h"

void AnimeAttack::insertAttackFrame(sf::Texture* attackTexture) {
    attackFrames.push_back(attackTexture);
}

void AnimeAttack::setStateSprite(sf::Sprite* sprite) {
    this->sprite = sprite;
}

void AnimeAttack::tickAttackAnimation() {
	if(attackFrames.empty())
		return;

    if (currentAttackFrame >= attackFrames.size()) {
        currentAttackFrame = 0;
    }

    sprite->setTexture(*attackFrames.at(currentAttackFrame));

    currentAttackFrame++;
}

void AnimeAttack::startAttackAnimation() {
    resetAttackAnimation();
    tickAttackAnimation();
    isAnimating = true;
}

void AnimeAttack::runAttackAnimation(float delta) {
    if (!isAnimating)
        return;

    timeSinceLastAttackFrame += delta;
    if (currentAttackFrame < attackFrames.size() && timeSinceLastAttackFrame >= msBetweenAttackFrames) {
        tickAttackAnimation();
        timeSinceLastAttackFrame = 0;
    }

    if (currentAttackFrame >= attackFrames.size() && timeSinceLastAttackFrame >= msBetweenAttackFrames)
        resetAttackAnimation();
}

void AnimeAttack::resetAttackAnimation() {
	if(attackFrames.empty())
		return;
    sprite->setTexture(*attackFrames.at(0));
    currentAttackFrame = 1;
    timeSinceLastAttackFrame = 0;
    isAnimating = false;
}