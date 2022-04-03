//
// Created by root on 2022-04-02.
//

#include "UI/Menu.h"
#include "UI/PurchaseButton.h"
#include "GameAssets.h"

Menu::Menu(const wiz::AssetLoader &assetLoader, Forest& forest) : assetLoader(assetLoader) {
    // Squirrel Button
    buttons.push_back(new PurchaseButton(
            sf::IntRect({50, 50}, {200, 100}),
            forest,
            [&](Button* button) {
                PurchaseButton* iconButton = dynamic_cast<PurchaseButton*>(button);
                iconButton->forest.spawnSquirrel();
            },
            assetLoader,
            &GameAssets::SQUIRREL,
            Nuts,
            5
            ));
    // Wolf Button
    buttons.push_back(new PurchaseButton(
            sf::IntRect({50, 200}, {200, 200}),
            forest,
            [&](Button* button) {
                PurchaseButton* iconButton = dynamic_cast<PurchaseButton*>(button);
                // TODO: SPAWN WOLF
            },
            assetLoader,
            &GameAssets::WOLF,
            Nuts,
            20
    ));
    // Bear Button
    buttons.push_back(new PurchaseButton(
            sf::IntRect({50, 450}, {200, 200}),
            forest,
            [&](Button* button) {
                PurchaseButton* iconButton = dynamic_cast<PurchaseButton*>(button);
                // TODO: SPAWN BEAR
            },
            assetLoader,
            &GameAssets::BEAR,
            Nuts,
            50
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
