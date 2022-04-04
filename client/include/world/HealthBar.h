//
// Created by root on 2022-04-03.
//

#ifndef LD50_CLIENT_HEALTHBAR_H
#define LD50_CLIENT_HEALTHBAR_H

#include "SFML/Graphics/Drawable.hpp"
#include "SFML/System/Vector2.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "WIZ/asset/AssetLoader.h"
#include "Physical.h"
#include "Damageable.h"

class HealthBar : public sf::Drawable {
    Physical* physicalTarget;
    Damageable* damageable;
    mutable sf::Sprite barSprite;
    bool treeHealthBar;
    sf::Color backgroundColor;
    sf::Color foregroundColor;

    float barWidth = 5.0f;
    float barHeight = 0.5f;

public:
    HealthBar(Physical* physicalTarget, Damageable* damageable, const wiz::AssetLoader& assetLoader);

    void draw(sf::RenderTarget &target, const sf::RenderStates &states) const override;
};


#endif //LD50_CLIENT_HEALTHBAR_H