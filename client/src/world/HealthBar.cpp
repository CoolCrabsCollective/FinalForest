//
// Created by root on 2022-04-03.
//

#include "world/HealthBar.h"
#include "WIZ/asset/AssetLoader.h"
#include "GameAssets.h"
#include "world/Forest.h"

HealthBar::HealthBar(Physical* physicalTarget, Damageable* damageable, const wiz::AssetLoader& assetLoader) : physicalTarget(physicalTarget), damageable(damageable){
    barSprite = sf::Sprite((*assetLoader.get(GameAssets::WHITE_PIXEL)));

    treeHealthBar = dynamic_cast<Tree*>(damageable) != NULL;
    if (treeHealthBar) {
        backgroundColor = sf::Color(0xBBBBBBFF);
        foregroundColor = sf::Color::White;
    } else {
        backgroundColor = sf::Color::Red;
        foregroundColor = sf::Color::Green;
    }
}

void HealthBar::draw(sf::RenderTarget &target, const sf::RenderStates &states) const {
    if (damageable->getHealth() == damageable->maxHealth)
        return;

    if (damageable->getHealth() <= 0)
        return;

    barSprite.setPosition({physicalTarget->getPosition().x - (barWidth / 2), 100 - physicalTarget->getPosition().y - 5});
    // draw background
    barSprite.setColor(backgroundColor);
    barSprite.setScale({barWidth, barHeight});
    target.draw(barSprite);

    // draw red fill
    barSprite.setColor(sf::Color(foregroundColor));
    barSprite.setScale({(damageable->getHealth() / damageable->maxHealth) * barWidth, barHeight});
    target.draw(barSprite);
}