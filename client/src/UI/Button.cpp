//
// Created by root on 2022-04-02.
//

#include "UI/Button.h"
#include "GameAssets.h"
#include "SFML/Graphics/RectangleShape.hpp"

Button::Button(sf::IntRect rectangle) {
    rectangleShape.setSize(sf::Vector2f(rectangle.getSize().x, rectangle.getSize().y));
    rectangleShape.setOutlineColor(sf::Color::Black);
    rectangleShape.setOutlineThickness(5);
    rectangleShape.setPosition({(float)rectangle.getPosition().x, (float)rectangle.getPosition().y});
};

void Button::draw(sf::RenderTarget& target, const sf::RenderStates& states) const {
    target.draw(rectangleShape);
}
