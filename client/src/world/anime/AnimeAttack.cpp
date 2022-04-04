//
// Created by william on 2022-04-03.
//

#include "world/anime/AnimeAttack.h"

void AnimeAttack::startAttackAnimation() {
    Anime::startAnimation();
}

void AnimeAttack::runAttackAnimation(float delta) {
    Anime::runAnimation(delta);
}

void AnimeAttack::resetAttackAnimation() {
	Anime::resetAnimation();
}

void AnimeAttack::insertAttackFrame(sf::Texture* attackTexture) {
    Anime::insertFrame(attackTexture);
}

void AnimeAttack::setAttackStateSprite(sf::Sprite* sprite) {
    Anime::setStateSprite(sprite);
}