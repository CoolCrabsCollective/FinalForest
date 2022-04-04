//
// Created by Cedric on 2022-04-03.
//

#include <GameAssets.h>
#include "UI/WordsButton.h"
#include "SFML/Graphics/Text.hpp"
#include "UI/Button.h"

WordsButton::WordsButton(sf::IntRect rectangle, Forest &forest, std::function<void(Button *)> onClick, std::function<bool(void)> isEnabled,
                         std::string str) : Button(rectangle, forest, onClick) {
        this->isEnabled = isEnabled;
        lblText.setString(str);
        lblText.setCharacterSize(16);
        lblText.setFillColor(sf::Color::Black);
        lblText.setFont(*forest.getAssets().get(GameAssets::DEFAULT_FONT));
        sf::FloatRect bounds = lblText.getLocalBounds();
        lblText.setPosition({(float)rectangle.getPosition().x + (rectangle.width / 2) - (bounds.width / 2), (float)rectangle.getPosition().y + (rectangle.height / 2) - (bounds.height / 2)});

        rectangleShape.setSize(sf::Vector2f(rectangle.getSize().x, rectangle.getSize().y));
        rectangleShape.setOutlineColor(sf::Color::Black);
        rectangleShape.setFillColor(availableColor);
        rectangleShape.setOutlineThickness(5);
        rectangleShape.setPosition({(float)rectangle.getPosition().x, (float)rectangle.getPosition().y});
}

void WordsButton::tick(float delta) {
    if(isEnabled())
    {
        rectangleShape.setFillColor(availableColor);
        rectangleShape.setOutlineColor(sf::Color::Black);
    }
    else
    {
        rectangleShape.setFillColor(unavailableColor);
        rectangleShape.setOutlineColor(gray);
    }
}

void WordsButton::draw(sf::RenderTarget &target, const sf::RenderStates &states) const {
    Button::draw(target, states);
    target.draw(lblText);
}

void WordsButton::click() {
    if(isEnabled())
        Button::click();
}
