//
// Created by william on 2022-04-04.
//

#ifndef LD50_CLIENT_ENTITYCLICKSELECTION_H
#define LD50_CLIENT_ENTITYCLICKSELECTION_H

#include "world/Forest.h"

class EntityClickSelection {
    Entity* selectedEntity = nullptr;
public:

    EntityClickSelection();

    void clickScan(sf::Vector2f clickVector, Forest& forest);

    Entity *getSelectedEntity() const;

    void setSelectedEntity(Entity *selectedEntity);
};

#endif //LD50_CLIENT_ENTITYCLICKSELECTION_H
