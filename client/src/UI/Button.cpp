//
// Created by root on 2022-04-02.
//

#include "UI/Button.h"
#include "GameAssets.h"
#include "SFML/Graphics/RectangleShape.hpp"

Button::Button(sf::IntRect rectangle) {
    rectangleShape.setSize(sf::Vector2f(100, 50));
    rectangleShape.setOutlineColor(sf::Color::Red);
    rectangleShape.setOutlineThickness(5);
    rectangleShape.setPosition({10, 20});
};

void Button::draw(sf::RenderTarget& target, const sf::RenderStates& states) const {
    target.draw(rectangleShape);
}
