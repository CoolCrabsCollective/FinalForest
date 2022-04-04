//
// Created by Cedric on 2022-04-03.
//

#include <UI/PurchaseButton.h>
#include <GameAssets.h>
#include "UI/AnimalMenu.h"

AnimalMenu::AnimalMenu(const wiz::AssetLoader &assetLoader, Forest &forest) : Menu(assetLoader, forest) {

    animalMenu.setTexture(*assetLoader.get(GameAssets::ANIMAL_MENU));
    animalMenu.setPosition({25, 20});
    animalMenu.setColor(sf::Color::White);
    animalMenu.setScale({4.f, 4.f});
    // Squirrel Button
    buttons.push_back(new PurchaseButton(
            sf::IntRect({50, 125}, {200, 115}),
            forest,
            [&](Button* button) {
                PurchaseButton* iconButton = dynamic_cast<PurchaseButton*>(button);
                iconButton->forest.spawnSquirrel();
            },
            assetLoader,
            &GameAssets::SQUIRREL,
            Nuts,
            5,
            0
    ));
    // Wolf Button
    buttons.push_back(new PurchaseButton(
            sf::IntRect({50, 285}, {200, 120}),
            forest,
            [&](Button* button) {
                PurchaseButton* iconButton = dynamic_cast<PurchaseButton*>(button);
				iconButton->forest.spawnWolf();
            },
            assetLoader,
            &GameAssets::WOLF,
            Nuts,
            20,
            -15
    ));
    // Bear Button
    buttons.push_back(new PurchaseButton(
            sf::IntRect({50, 450}, {200, 140}),
            forest,
            [&](Button* button) {
                PurchaseButton* iconButton = dynamic_cast<PurchaseButton*>(button);
				iconButton->forest.spawnBear();
            },
            assetLoader,
            &GameAssets::BEAR,
            Nuts,
            50,
            -8
    ));
}

void AnimalMenu::draw(sf::RenderTarget &target, const sf::RenderStates &states) const {
    Menu::draw(target, states);
    if(!hidden)
        target.draw(animalMenu);
}

void AnimalMenu::tick(float delta) {
    Menu::tick(delta);
}
