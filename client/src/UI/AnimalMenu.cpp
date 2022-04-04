//
// Created by Sir Dick on 2022-04-03.
//

#include <UI/PurchaseButton.h>
#include <GameAssets.h>
#include "UI/AnimalMenu.h"

AnimalMenu::AnimalMenu(const wiz::AssetLoader &assetLoader, Forest &forest) : Menu(assetLoader, forest) {
    // Squirrel Button
    buttons.push_back(new PurchaseButton(
            sf::IntRect({50, 50}, {200, 115}),
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
            sf::IntRect({50, 215}, {200, 120}),
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
            sf::IntRect({50, 395}, {200, 140}),
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