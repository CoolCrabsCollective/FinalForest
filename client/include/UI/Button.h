//
// Created by root on 2022-04-02.
//

#ifndef LD50_CLIENT_BUTTON_H
#define LD50_CLIENT_BUTTON_H


#include "SFML/Graphics/Drawable.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "world/Tickable.h"
#include "world/Forest.h"
#include "SFML/Graphics/RectangleShape.hpp"

class Button : public sf::Drawable, public Tickable  {
    std::function<void(Button*)> onClick;

protected:
    sf::RectangleShape rectangleShape;

    constexpr static const sf::Color unavailableColor = sf::Color(255, 255, 255, 100);
    constexpr static const sf::Color availableColor = sf::Color(255, 255, 255, 255);

public:
    Forest& forest;

    Button(sf::IntRect rectangle, Forest& forest, std::function<void(Button*)> onClick);

    void draw(sf::RenderTarget& target, const sf::RenderStates& states) const override;

    void checkClick(sf::Vector2f clickVector);
};


#endif //LD50_CLIENT_BUTTON_H
