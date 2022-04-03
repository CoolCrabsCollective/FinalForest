//
// Created by cedric on 2022-04-02.
//

#include <world/state/SquirrelReturnGatherState.h>

#include <memory>
#include "world/state/SquirrelGatherState.h"
#include "world/Forest.h"
#include "ForestScreen.h"

SquirrelGatherState::SquirrelGatherState(Forest *forest, Squirrel *squirrel, Tree *tree) : SquirrelState(forest, squirrel) {
        this->harvestingTree = tree;
        squirrel->setDestination(squirrel->getPosition());
        timeLeftHarvesting = SQUIRREL_HARVESTING_TIME;
        getForest()->getScreen().getLogger().debug("Harvest Start");
}

void SquirrelGatherState::tick(float delta) {

    timeLeftHarvesting -= delta;

    if(timeLeftHarvesting <= 0)
    {
        getForest()->getScreen().getLogger().debug("Harvest End");
        this->getSquirrel()->setState(std::make_shared<SquirrelReturnGatherState>(this->getForest(), this->getSquirrel(), this->harvestingTree));
    }
}
