//
// Created by root on 2022-04-02.
//

#include "UI/Button.h"
#include "SFML/Graphics/RectangleShape.hpp"

Button::Button(sf::IntRect rectangle, Forest& forest) : forest(forest){
    rectangleShape.setSize(sf::Vector2f(rectangle.getSize().x, rectangle.getSize().y));
    rectangleShape.setOutlineColor(sf::Color::Black);
    rectangleShape.setOutlineThickness(5);
    rectangleShape.setPosition({(float)rectangle.getPosition().x, (float)rectangle.getPosition().y});
};

void Button::draw(sf::RenderTarget& target, const sf::RenderStates& states) const {
    target.draw(rectangleShape);
}

void Button::checkClick(sf::Vector2f clickVector) {
    if (clickVector.x > rectangleShape.getPosition().x &&
        clickVector.x < rectangleShape.getPosition().y + rectangleShape.getSize().x &&
        clickVector.y > rectangleShape.getPosition().y &&
        clickVector.y < rectangleShape.getPosition().y + rectangleShape.getSize().y)
        forest.spawnSquirrel();
}
