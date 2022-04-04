//
// Created by william on 2022-04-04.
//

#include "UI/EntityClickSelection.h"
#include "ForestScreen.h"
#include "world/tree/BigAssTree.h"

EntityClickSelection::EntityClickSelection() {
}

void EntityClickSelection::clickScan(sf::Vector2f clickVector, Forest& forest) {
    Enemy* selectedEnemy = nullptr;
    Tree* selectedTree = nullptr;
    for (Entity* entity : forest.getObjects()) {
        Enemy* enemy = dynamic_cast<Enemy *>(entity);
        Tree* tree = dynamic_cast<Tree *>(entity);
        if (enemy && selectedEnemy == nullptr &&
                     (clickVector.x > enemy->getPosition().x - (enemy->getSize().x / 2) &&
                      clickVector.x < enemy->getPosition().x + (enemy->getSize().x / 2) &&
                      100.0f - clickVector.y > enemy->getPosition().y - (enemy->getSize().y) &&
                      100.0f - clickVector.y < enemy->getPosition().y + (enemy->getSize().y))) {
            selectedEnemy = enemy;
            break;
        } else if (tree && selectedTree == nullptr &&
                (clickVector.x > tree->getPosition().x - (tree->getSize().x) &&
                 clickVector.x < tree->getPosition().x + (tree->getSize().x) &&
                 100.0f - clickVector.y > tree->getPosition().y - (tree->getSize().y) &&
                 100.0f - clickVector.y < tree->getPosition().y + (tree->getSize().y))) {
            selectedTree = tree;
        }
    }

    if (selectedEnemy != nullptr) {
        selectedEntity = selectedEnemy;
        forest.getScreen().setMenu(ENEMY_MENU);
    } else if (selectedTree != nullptr && dynamic_cast<BigAssTree*>(selectedTree)) {
        forest.getScreen().setMenu(ANIMAL_MENU);
    } else if (selectedTree != nullptr) {
        selectedEntity = selectedTree;
        forest.getScreen().setMenu(TURRET_MENU);
    }
}

Entity *EntityClickSelection::getSelectedEntity() const {
    return selectedEntity;
}

void EntityClickSelection::setSelectedEntity(Entity *selectedEntity) {
    EntityClickSelection::selectedEntity = selectedEntity;
}
