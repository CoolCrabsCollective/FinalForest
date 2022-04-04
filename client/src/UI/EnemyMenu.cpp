//
// Created by william on 2022-04-03.
//

#include <UI/Button.h>
#include <GameAssets.h>
#include "UI/EnemyMenu.h"

EnemyMenu::EnemyMenu(const wiz::AssetLoader &assetLoader, Forest &forest) : Menu(assetLoader, forest) {
    // Squirrel Button
    buttons.push_back(new Button(
            sf::IntRect({50, 50}, {200, 100}),
            forest,
            [&](Button* button) {
                Button* iconButton = dynamic_cast<Button*>(button);
                iconButton->forest.spawnSquirrel();
            }
    ));
    // Wolf Button
    buttons.push_back(new Button(
            sf::IntRect({50, 200}, {200, 200}),
            forest,
            [&](Button* button) {
                Button* iconButton = dynamic_cast<Button*>(button);
                // TODO: SPAWN WOLF
            }
    ));
    // Bear Button
    buttons.push_back(new Button(
            sf::IntRect({50, 450}, {200, 200}),
            forest,
            [&](Button* button) {
                Button* iconButton = dynamic_cast<Button*>(button);
                // TODO: SPAWN BEAR
            }
    ));
}
