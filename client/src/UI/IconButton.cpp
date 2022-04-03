//
// Created by root on 2022-04-02.
//

#include <iostream>
#include "UI/IconButton.h"
#include "GameAssets.h"

IconButton::IconButton(sf::IntRect rectangle, Forest& forest, std::function<void(Button*)> onClick, const wiz::AssetLoader& assetLoader, const wiz::TextureAsset* textureType, Currency currency, int price) : Button(rectangle, forest, onClick), price(price), currency(currency) {
    float scale = 3.0f;
    sprite = sf::Sprite(*assetLoader.get(*textureType));
    sprite.setPosition(sf::Vector2f(rectangle.getPosition().x + (rectangle.getSize().x / 2) - (scale * 16 / 2), rectangle.getPosition().y + (rectangle.getSize().y / 2) - (scale * 16 / 2)));
    sprite.setScale({scale, scale});

    const wiz::TextureAsset* currencyTextureAsset;
    if (currency == Nuts)
        currencyTextureAsset = &GameAssets::NUT;
    else if (currency == Mana)
        currencyTextureAsset = &GameAssets::MANA;

    currencySprite = sf::Sprite(*assetLoader.get(*currencyTextureAsset));
    currencySprite.setPosition(sf::Vector2f(rectangle.getPosition().x + (rectangle.getSize().x / 2) - 8, rectangle.getPosition().y + (rectangle.getSize().y) - 16));
    currencySprite.setScale({1.0, 1.0});

    priceText.setString(std::to_string(price));
    priceText.setPosition(sf::Vector2f(currencySprite.getPosition().x + 20, currencySprite.getPosition().y - 5));
    priceText.setCharacterSize(20);
    priceText.setFont(*assetLoader.get(GameAssets::SANS_TTF));
    priceText.setFillColor(sf::Color::Black);

    std::string productName = textureType->getName().substr(4, textureType->getName().size() - 8);
    productName[0] = toupper(productName[0]);
    labelText.setString("Buy " + productName);
    labelText.setPosition(sf::Vector2f(rectangle.getPosition().x, rectangle.getPosition().y));
    labelText.setCharacterSize(20);
    labelText.setFont(*assetLoader.get(GameAssets::SANS_TTF));
    labelText.setFillColor(sf::Color::Black);
}

void IconButton::draw(sf::RenderTarget& target, const sf::RenderStates& states) const {
    Button::draw(target, states);
    target.draw(sprite);
    target.draw(currencySprite);
    target.draw(priceText);
    target.draw(labelText);
}

void IconButton::tick(float delta) {
    int currencyCount;
    if (currency == Nuts)
        currencyCount = forest.nutCount;
    else if (currency == Mana)
        currencyCount = forest.mana;

    if (currencyCount < price)
        rectangleShape.setOutlineColor(sf::Color::Red);
    else
        rectangleShape.setOutlineColor(sf::Color::Black);
}

