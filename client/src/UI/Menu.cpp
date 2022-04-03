//
// Created by root on 2022-04-02.
//

#include "UI/Menu.h"
#include "UI/IconButton.h"
#include "GameAssets.h"

Menu::Menu(const wiz::AssetLoader &assetLoader, Forest& forest) : assetLoader(assetLoader) {
    // Squirrel Button
    buttons.push_back(new IconButton(
            sf::IntRect({50, 50}, {200, 100}),
            forest,
            [&](Button* button) {
                IconButton* iconButton = dynamic_cast<IconButton*>(button);

                if (iconButton->forest.nutCount < iconButton->price)
                   return;

                iconButton->forest.nutCount -= iconButton->price;
                iconButton->forest.spawnSquirrel();
            },
            assetLoader,
            &GameAssets::SQUIRREL,
            Nuts,
            5
            ));
}

void Menu::draw(sf::RenderTarget& target, const sf::RenderStates& states) const {
    for (int i = 0 ; i < buttons.size() ; i++) {
        buttons[i]->draw(target, states);
    }
};

void Menu::click(sf::Vector2f clickVector) {
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
