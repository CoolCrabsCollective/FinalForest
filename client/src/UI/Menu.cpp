//
// Created by root on 2022-04-02.
//

#include "UI/Menu.h"

Menu::Menu() {
    buttons.push_back(sf::IntRect({50, 50}, {200, 100}));
    buttons.push_back(sf::IntRect({50, 200}, {200, 100}));
}

void Menu::draw(sf::RenderTarget& target, const sf::RenderStates& states) const {
    for (Button butt : buttons) {
        butt.draw(target, states);
    }
};

void Menu::addButton(Button button) {
    buttons.push_back(button);
}
