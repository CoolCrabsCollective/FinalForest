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
    if (damageable->getHealth() == damageable->maxHealth)
        return;

    if (damageable->getHealth() <= 0)
        return;

    barSprite.setPosition({physicalTarget->getPosition().x, 100 - physicalTarget->getPosition().y});
    // draw background
    barSprite.setColor(sf::Color(sf::Color::Red));
    barSprite.setScale({barWidth, barHeight});
    target.draw(barSprite);

    // draw red fill
    barSprite.setColor(sf::Color(sf::Color::Green));
    barSprite.setScale({(damageable->getHealth() / damageable->maxHealth) * barWidth, barHeight});
    target.draw(barSprite);
}