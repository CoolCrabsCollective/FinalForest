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
    sf::RectangleShape rectangleShape;
    Forest& forest;
    std::function<void()> onClick;

public:
    Button(sf::IntRect rectangle, Forest& forest, std::function<void()> onClick);

    void draw(sf::RenderTarget& target, const sf::RenderStates& states) const override;

    void checkClick(sf::Vector2f clickVector);

    void tick(float delta) override;
};


#endif //LD50_CLIENT_BUTTON_H
