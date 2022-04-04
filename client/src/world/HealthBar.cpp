//
// Created by root on 2022-04-03.
//

#include "world/HealthBar.h"
#include "WIZ/asset/AssetLoader.h"
#include "GameAssets.h"
#include "world/Forest.h"

HealthBar::HealthBar(Physical* physicalTarget, Damageable* damageable, const wiz::AssetLoader& assetLoader) : physicalTarget(physicalTarget), damageable(damageable){
    barSprite = sf::Sprite((*assetLoader.get(GameAssets::WHITE_PIXEL)));
}

void HealthBar::draw(sf::RenderTarget &target, const sf::RenderStates &states) const {

    barSprite.setPosition({physicalTarget->getPosition().x, physicalTarget->getPosition().y});
    // draw white background
    barSprite.setColor(sf::Color(sf::Color(255, 255, 255, 255)));
    barSprite.setScale({10, 1});
    target.draw(barSprite);

    // draw red fill
    barSprite.setColor(sf::Color(sf::Color(255, 0, 0, 255)));
    barSprite.setScale({damageable->getHealth(), 1});
    target.draw(barSprite);
}