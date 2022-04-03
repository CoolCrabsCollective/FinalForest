//
// Created by root on 2022-04-02.
//

#ifndef LD50_CLIENT_MENU_H
#define LD50_CLIENT_MENU_H


#include "SFML/Graphics/Drawable.hpp"
#include "Button.h"

class Menu : public sf::Drawable {
    std::vector<Button> buttons;

public:
    Menu();

    void draw(sf::RenderTarget& target, const sf::RenderStates& states) const override;
    void addButton(Button button);
};


#endif //LD50_CLIENT_MENU_H
