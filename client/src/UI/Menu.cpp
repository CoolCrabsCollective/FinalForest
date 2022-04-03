//
// Created by root on 2022-04-02.
//

#include "UI/Menu.h"
#include "UI/PurchaseButton.h"
#include "GameAssets.h"

Menu::Menu(const wiz::AssetLoader &assetLoader, Forest& forest) : assetLoader(assetLoader) {

}

void Menu::show(bool isShown) {
    hidden = !isShown;
}

void Menu::draw(sf::RenderTarget& target, const sf::RenderStates& states) const {
    if(hidden)
        return;

    for (int i = 0 ; i < buttons.size() ; i++) {
        buttons[i]->draw(target, states);
    }
};

void Menu::click(sf::Vector2f clickVector) {
    if(hidden)
        return;

    for (int i = 0 ; i < buttons.size() ; i++) {
        Button* b = buttons[i];
        b->checkClick(clickVector);
    }
}

void Menu::tick(float delta) {
    for (int i = 0 ; i < buttons.size() ; i++) {
        Button* b = buttons[i];
        b->tick(delta);
    }
}
