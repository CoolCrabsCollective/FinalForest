//
// Created by root on 2022-04-02.
//

#include "UI/IconButton.h"
#include "GameAssets.h"

IconButton::IconButton(sf::IntRect rectangle, Forest& forest, std::function<void()> onClick, const wiz::AssetLoader& assetLoader, const wiz::TextureAsset* textureType, const wiz::TextureAsset* currencyTextureType) : Button(rectangle, forest, onClick) {
    float scale = 3.0f;
    sprite = sf::Sprite(*assetLoader.get(*textureType));
    sprite.setPosition(sf::Vector2f(rectangle.getPosition().x + (rectangle.getSize().x / 2) - (scale * 16 / 2), rectangle.getPosition().y + (rectangle.getSize().y / 2) - (scale * 16 / 2)));
    sprite.setScale({scale, scale});

    currencySprite = sf::Sprite(*assetLoader.get(*currencyTextureType));
    currencySprite.setPosition(sf::Vector2f(rectangle.getPosition().x + (rectangle.getSize().x / 2) - 8, rectangle.getPosition().y + (rectangle.getSize().y) - 16));
    currencySprite.setScale({1.0, 1.0});
}

void IconButton::draw(sf::RenderTarget& target, const sf::RenderStates& states) const {
    Button::draw(target, states);
    target.draw(sprite);
    target.draw(currencySprite);
}
