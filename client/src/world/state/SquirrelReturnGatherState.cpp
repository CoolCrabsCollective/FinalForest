//
// Created by cedric on 2022-04-02.
//

#include <world/state/SquirrelGoGathertState.h>

#include <memory>
#include "world/state/SquirrelReturnGatherState.h"
#include "world/Forest.h"
#include "world/GreatOakTree.h"
#include "ForestScreen.h"

SquirrelReturnGatherState::SquirrelReturnGatherState(Forest *forest, Squirrel *squirrel, Tree* previousTree) : SquirrelState(forest, squirrel) {
    this->tree = previousTree;
    getSquirrel()->setDestination(getForest()->getGreatOakTree()->getPosition());
}

void SquirrelReturnGatherState::tick(float delta) {
    if(b2Distance(this->getSquirrel()->getPosition(), this->getForest()->getGreatOakTree()->getPosition()) < MIN_GREAT_TREE_DISTANCE)
    {
        getForest()->getScreen().getLogger().debug("Walking towards nut...");
        this->getSquirrel()->setState(std::make_shared<SquirrelGoGatherState>(this->getForest(), this->getSquirrel(), this->tree));
        this->getForest()->nutCount++;
    }
}
