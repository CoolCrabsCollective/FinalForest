//
// Created by root on 2022-04-02.
//

#include <iostream>
#include "UI/PurchaseButton.h"
#include "GameAssets.h"

PurchaseButton::PurchaseButton(sf::IntRect rectangle, Forest& forest, std::function<void(Button*)> onClick, const wiz::AssetLoader& assetLoader, const wiz::TextureAsset* textureType, Currency currency, int price) : Button(rectangle, forest, onClick), price(price), currency(currency) {
    sf::FloatRect bounds;
    float scale = 3.0f;

    sprite = sf::Sprite(*assetLoader.get(*textureType));
    sprite.setScale({scale, scale});
    bounds = sf::FloatRect({0, 0} , {
           sprite.getTexture()->getSize().x * sprite.getScale().x,
           sprite.getTexture()->getSize().y * sprite.getScale().y
    });
    sprite.setPosition(sf::Vector2f(rectangle.getPosition().x + (rectangle.getSize().x / 2) - (bounds.width / 2), rectangle.getPosition().y + (rectangle.getSize().y / 2) - (bounds.height / 2)));

    const wiz::TextureAsset* currencyTextureAsset;
    if (currency == Nuts)
        currencyTextureAsset = &GameAssets::NUT;
    else if (currency == Mana)
        currencyTextureAsset = &GameAssets::MANA;

    currencySprite = sf::Sprite(*assetLoader.get(*currencyTextureAsset));
    currencySprite.setPosition(sf::Vector2f(rectangle.getPosition().x + (rectangle.getSize().x / 2) - 16, rectangle.getPosition().y + (rectangle.getSize().y) - 16));
    currencySprite.setScale({1.0, 1.0});

    priceText.setString(std::to_string(price));
    priceText.setPosition(sf::Vector2f(currencySprite.getPosition().x + 20, currencySprite.getPosition().y - 5));
    priceText.setCharacterSize(20);
    priceText.setFont(*assetLoader.get(GameAssets::SANS_TTF));
    priceText.setFillColor(sf::Color::Black);

    std::string productName = textureType->getName().substr(4, textureType->getName().size() - 8);
    productName[0] = toupper(productName[0]);
    labelText.setString("Buy " + productName);
    labelText.setCharacterSize(20);
    labelText.setFont(*assetLoader.get(GameAssets::SANS_TTF));
    labelText.setFillColor(sf::Color::Black);
    bounds = labelText.getLocalBounds();
    labelText.setPosition(sf::Vector2f(rectangle.getPosition().x + (rectangle.width / 2) - (bounds.width / 2), rectangle.getPosition().y + 5));
}

void PurchaseButton::draw(sf::RenderTarget& target, const sf::RenderStates& states) const {
    Button::draw(target, states);
    target.draw(sprite);
    target.draw(currencySprite);
    target.draw(priceText);
    target.draw(labelText);
}

void PurchaseButton::tick(float delta) {
    int currencyCount = calculateCurrencyCount();

    if (currencyCount < price) {
        sprite.setColor(unavailableColor);
        currencySprite.setColor(unavailableColor);
        rectangleShape.setFillColor(unavailableColor);
        rectangleShape.setOutlineColor(gray);
        priceText.setFillColor(gray);
        labelText.setFillColor(gray);
    } else {
        sprite.setColor(availableColor);
        currencySprite.setColor(availableColor);
        rectangleShape.setFillColor(availableColor);
        rectangleShape.setOutlineColor(sf::Color::Black);
        priceText.setFillColor(sf::Color::Black);
        labelText.setFillColor(sf::Color::Black);
    }
}

void PurchaseButton::click() {
    int currencyCount = calculateCurrencyCount();

    if (currencyCount < price)
        return;

    forest.nutCount -= price;
    Button::click();
}

int PurchaseButton::calculateCurrencyCount() {
    if (currency == Nuts)
        return forest.nutCount;
    else if (currency == Mana)
        return forest.mana;
}
