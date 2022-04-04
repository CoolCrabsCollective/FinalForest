//
// Created by Cedric on 2022-04-02.
//

#include "world/animal/state/SquirrelReturnGatherState.h"

#include <memory>
#include "world/animal/state/SquirrelGatherState.h"
#include "world/Forest.h"
#include "ForestScreen.h"

SquirrelGatherState::SquirrelGatherState(Squirrel* squirrel, Tree* tree)
	: SquirrelState(squirrel)
{
	this->harvestingTree = tree;
	squirrel->setDestination(squirrel->getPosition());
	timeLeftHarvesting = SQUIRREL_HARVESTING_TIME;
}

void SquirrelGatherState::tick(float delta) {

    timeLeftHarvesting -= delta;

    if(timeLeftHarvesting <= 0)
        this->getSquirrel()->setState(std::make_shared<SquirrelReturnGatherState>(this->getSquirrel(), this->harvestingTree));
}
