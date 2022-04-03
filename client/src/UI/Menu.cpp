//
// Created by root on 2022-04-02.
//

#include "UI/Menu.h"
#include "UI/IconButton.h"
#include "GameAssets.h"

Menu::Menu(const wiz::AssetLoader &assetLoader) : assetLoader(assetLoader) {
    buttons.push_back(new IconButton(sf::IntRect({50, 50}, {200, 100}), assetLoader, &GameAssets::SQUIRREL));
}

void Menu::draw(sf::RenderTarget& target, const sf::RenderStates& states) const {
    for (int i = 0 ; i < buttons.size() ; i++) {
        buttons[i]->draw(target, states);
    }
};
