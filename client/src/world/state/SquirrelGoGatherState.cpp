//
// Created by cedric on 2022-04-02.
//

#include <memory>

#include "world/state/SquirrelGoGathertState.h"
#include "world/state/SquirrelGatherState.h"
#include "ForestScreen.h"

SquirrelGoGatherState::SquirrelGoGatherState(Forest *forest, Squirrel *squirrel, Tree *tree) : SquirrelState(forest, squirrel) {
    this->tree = tree;
    squirrel->setDestination(tree->getPosition());
}

void SquirrelGoGatherState::tick(float delta) {
    if(b2Distance(this->getSquirrel()->getPosition(), this->tree->getPosition()) < MIN_TREE_DISTANCE)
    {
        getForest()->getScreen().getLogger().debug("Harvesting Nut...");
        this->getSquirrel()->setState(std::make_shared<SquirrelGatherState>(this->getForest(), this->getSquirrel(), this->tree));
    }
}
