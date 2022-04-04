//
// Created by cedric on 2022-04-03.
//

#include <GameAssets.h>
#include "UI/WordsButton.h"
#include "SFML/Graphics/Text.hpp"
#include "UI/Button.h"

WordsButton::WordsButton(sf::IntRect rectangle, Forest &forest, std::function<void(Button *)> onClick,
                         std::string str) : Button(rectangle, forest, onClick) {
        lblText.setString(str);
        lblText.setPosition({(float)rectangle.getPosition().x, (float)rectangle.getPosition().y});
        lblText.setFont(*forest.getAssets().get(GameAssets::SANS_TTF));

        lblText.setCharacterSize(16);
        lblText.setFillColor(sf::Color::Black);

        rectangleShape.setSize(sf::Vector2f(rectangle.getSize().x, rectangle.getSize().y));
        rectangleShape.setOutlineColor(sf::Color::Black);
        rectangleShape.setFillColor(availableColor);
        rectangleShape.setOutlineThickness(5);
        rectangleShape.setPosition({(float)rectangle.getPosition().x, (float)rectangle.getPosition().y});
}

void WordsButton::tick(float delta) {

}

void WordsButton::draw(sf::RenderTarget &target, const sf::RenderStates &states) const {
    Button::draw(target, states);
    target.draw(lblText);
}
