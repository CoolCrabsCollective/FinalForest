//
// Created by william on 2022-04-04.
//

#include "UI/EntityClickSelection.h"
#include "ForestScreen.h"
#include "world/tree/BigAssTree.h"

EntityClickSelection::EntityClickSelection() {
}

void EntityClickSelection::clickScan(sf::Vector2f clickVector, Forest& forest) {
    Entity* selectedEntity = nullptr;
    sf::Vector2f clickV = {clickVector.x, 100.f - clickVector.y};

    for (Entity* entity : forest.getObjects()) {
        Enemy* enemy = dynamic_cast<Enemy *>(entity);
        Tree* tree = dynamic_cast<Tree *>(entity);

        if(!tree && !enemy)
            continue;

        if (enemy && (clickV.x > enemy->getPosition().x - (enemy->getSize().x / 2) &&
                      clickV.x < enemy->getPosition().x + (enemy->getSize().x / 2) &&
                      clickV.y > enemy->getPosition().y - (enemy->getSize().y) &&
                      clickV.y < enemy->getPosition().y + (enemy->getSize().y))) {
            selectedEntity = enemy;
            break;
        }
        else if (tree && dynamic_cast<BigAssTree*>(entity) &&
                 ((clickV.x - tree->getPosition().x)*(clickV.x - tree->getPosition().x) +
                  (clickV.y - tree->getPosition().y)*(clickV.y - tree->getPosition().y)) < 61) {
            selectedEntity = tree;
        } else if (tree &&
                ((clickV.x - tree->getPosition().x)*(clickV.x - tree->getPosition().x) +
                (clickV.y - tree->getPosition().y)*(clickV.y - tree->getPosition().y)) < 14) {
            selectedEntity = tree;
        }

    }

    this->setSelectedEntity(selectedEntity);
}

Entity *EntityClickSelection::getSelectedEntity() const {
    return selectedEntity;
}

void EntityClickSelection::setSelectedEntity(Entity *selectedEntity) {
    EntityClickSelection::selectedEntity = selectedEntity;

    if(selectedEntity == nullptr)
        return;

    ForestScreen& screen = selectedEntity->getForest().getScreen();
    if (dynamic_cast<Enemy*>(selectedEntity)) {
        screen.setMenu(ENEMY_MENU);
    }  else if (dynamic_cast<BigAssTree*>(selectedEntity)) {
        screen.setMenu(ANIMAL_MENU);
    }
    else if (dynamic_cast<Tree*>(selectedEntity)) {
        screen.setMenu(TURRET_MENU);
    }
}
