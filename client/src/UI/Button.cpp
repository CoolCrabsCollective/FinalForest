//
// Created by root on 2022-04-02.
//

#include "UI/Button.h"

#include <utility>
#include "SFML/Graphics/RectangleShape.hpp"

Button::Button(sf::IntRect rectangle, Forest& forest, std::function<void(Button*)> onClick) : forest(forest), onClick(std::move(onClick)){
    rectangleShape.setSize(sf::Vector2f(rectangle.getSize().x, rectangle.getSize().y));
    rectangleShape.setOutlineColor(sf::Color::Black);
    rectangleShape.setFillColor(unavailableColor);
    rectangleShape.setOutlineThickness(5);
    rectangleShape.setPosition({(float)rectangle.getPosition().x, (float)rectangle.getPosition().y});
};

void Button::draw(sf::RenderTarget& target, const sf::RenderStates& states) const {
    target.draw(rectangleShape);
}

void Button::checkClick(sf::Vector2f clickVector) {
    if (clickVector.x > rectangleShape.getPosition().x &&
        clickVector.x < rectangleShape.getPosition().x + rectangleShape.getSize().x &&
        clickVector.y > rectangleShape.getPosition().y &&
        clickVector.y < rectangleShape.getPosition().y + rectangleShape.getSize().y)
        click();
}

void Button::tick(float delta) {

}

void Button::click() {
    onClick(this);
}
