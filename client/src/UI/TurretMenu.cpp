//
// Created by cedric on 2022-04-03.
//

#include "UI/TurretMenu.h"

#include <UI/PurchaseButton.h>
#include <GameAssets.h>
#include "UI/AnimalMenu.h"

AnimalMenu::AnimalMenu(const wiz::AssetLoader &assetLoader, Forest &forest) : Menu(assetLoader, forest) {
    // Squirrel Button
    buttons.push_back(new PurchaseButton(
            sf::IntRect({50, 50}, {200, 100}),
            forest,
            [&](Button* button) {
                PurchaseButton* iconButton = dynamic_cast<PurchaseButton*>(button);
                iconButton->forest.spawnSquirrel();
            },
            assetLoader,
            &GameAssets::TREE,
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
            &GameAssets::GREAT_OAK,
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
            &GameAssets::TREE_STUMP,
            Nuts,
            50
    ));
}