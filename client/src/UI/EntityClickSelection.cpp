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
    sf::Vector2f clickV = {clickVector.x, 100.f - clickVector.y};

    for (Entity* entity : forest.getObjects()) {
        Enemy* enemy = dynamic_cast<Enemy *>(entity);
        Tree* tree = dynamic_cast<Tree *>(entity);

        if (enemy &&
            (clickV.x > enemy->getPosition().x - (enemy->getSize().x / 2) &&
                      clickV.x < enemy->getPosition().x + (enemy->getSize().x / 2) &&
                      clickV.y > enemy->getPosition().y - (enemy->getSize().y) &&
                      clickV.y < enemy->getPosition().y + (enemy->getSize().y))) {
            selectedEnemy = enemy;
            break;
        } else if (tree && selectedTree == nullptr &&
                ((clickV.x - tree->getPosition().x)*(clickV.x - tree->getPosition().x) +
                (clickV.y - tree->getPosition().y)*(clickV.y - tree->getPosition().y)) < 14) {
            selectedTree = tree;
            break;
        }
        else if (tree && selectedTree == nullptr && dynamic_cast<BigAssTree*>(entity) &&
                ((clickV.x - tree->getPosition().x)*(clickV.x - tree->getPosition().x) +
                 (clickV.y - tree->getPosition().y)*(clickV.y - tree->getPosition().y)) < 61) {
            selectedTree = tree;
            break;
        }
    }
    if (selectedEnemy != nullptr) {
        selectedEntity = selectedEnemy;
        forest.getScreen().setMenu(ENEMY_MENU);
    } else if (selectedTree != nullptr  && dynamic_cast<Tree*>(selectedTree)) {
        selectedEntity = selectedTree;
        forest.getScreen().setMenu(TURRET_MENU);
    } else if (selectedTree != nullptr && dynamic_cast<BigAssTree*>(selectedTree)) {
        forest.getScreen().setMenu(ANIMAL_MENU);
    }
}

Entity *EntityClickSelection::getSelectedEntity() const {
    return selectedEntity;
}

void EntityClickSelection::setSelectedEntity(Entity *selectedEntity) {
    EntityClickSelection::selectedEntity = selectedEntity;
}
