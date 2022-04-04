//
// Created by root on 2022-04-02.
//

#include "UI/Button.h"

#include <utility>
#include "ForestScreen.h"
#include "ForestScreen.h"

Button::Button(sf::IntRect rectangle, Forest& forest, std::function<void(Button*)> onClick) : forest(forest), onClick(std::move(onClick)){
    rectangleShape.setSize(sf::Vector2f(rectangle.getSize().x, rectangle.getSize().y));
    rectangleShape.setOutlineColor(sf::Color::Black);
    rectangleShape.setFillColor(unavailableColor);
    rectangleShape.setOutlineThickness(5);
    rectangleShape.setPosition({(float)rectangle.getPosition().x, (float)rectangle.getPosition().y});
};

void Button::draw(sf::RenderTarget& target, const sf::RenderStates& states) const {
    sf::Vector2<int> rawMousePos = sf::Mouse::getPosition(forest.getScreen().getWindow());
    sf::Vector2f clickVector = forest.getScreen().getWindow().mapPixelToCoords({rawMousePos.x, rawMousePos.y}, sf::View({800.0f, 450.0f}, {1600.0f, 900.0f}));


    if (rectangleShape.getFillColor() != unavailableColor
        && clickVector.x > rectangleShape.getPosition().x &&
        clickVector.x < rectangleShape.getPosition().x + rectangleShape.getSize().x &&
        clickVector.y > rectangleShape.getPosition().y &&
        clickVector.y < rectangleShape.getPosition().y + rectangleShape.getSize().y)
    {

        sf::Color fillC = rectangleShape.getFillColor();
        sf::Color outlineC = rectangleShape.getOutlineColor();
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            rectangleShape.setFillColor(down);
            target.draw(rectangleShape);
        }
        else{
            rectangleShape.setFillColor(hover);
            target.draw(rectangleShape);
        }
        rectangleShape.setFillColor(fillC);
    }
    else
    {
        target.draw(rectangleShape);
    }
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
	forest.getScreen().getClick().play();
    onClick(this);
}
