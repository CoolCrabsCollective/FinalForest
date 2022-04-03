//
// Created by root on 2022-04-02.
//

#include "UI/IconButton.h"
#include "GameAssets.h"

IconButton::IconButton(sf::IntRect rectangle, Forest& forest, const wiz::AssetLoader& assetLoader, const wiz::TextureAsset* textureType) : Button(rectangle, forest) {
    float scale = 3.0f;

    sprite = sf::Sprite(*assetLoader.get(*textureType));
    sprite.setTextureRect(sf::Rect<int>({0, 0}, {16, 16}));
    sprite.setColor(sf::Color(255, 255, 255, 200));
    sprite.setPosition(sf::Vector2f(rectangle.getPosition().x + (rectangle.getSize().x / 2) - (scale * 16 / 2), rectangle.getPosition().y + (rectangle.getSize().y / 2) - (scale * 16 / 2)));
    sprite.setScale({scale, scale});
}

void IconButton::draw(sf::RenderTarget& target, const sf::RenderStates& states) const {
    Button::draw(target, states);
    target.draw(sprite);
}
