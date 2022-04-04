//
// Created by scrub on 2022-04-02.
//

#include "world/animal/state/SquirrelGoGathertState.h"

#include <memory>
#include "world/animal/state/SquirrelReturnGatherState.h"
#include "world/Forest.h"
#include "world/tree/BigAssTree.h"
#include "ForestScreen.h"

SquirrelReturnGatherState::SquirrelReturnGatherState(Squirrel* squirrel, Tree* previousTree)
	: SquirrelState(squirrel)
{
    this->tree = previousTree;
    getAnimal()->setDestination(getForest().getGreatOakTree()->getPosition());
}

void SquirrelReturnGatherState::tick(float delta) {
    if(b2Distance(this->getAnimal()->getPosition(), this->getForest().getGreatOakTree()->getPosition()) < MIN_GREAT_TREE_DISTANCE)
    {
        this->getSquirrel()->setState(std::make_shared<SquirrelGoGatherState>(this->getSquirrel(), this->tree));
        this->getForest().nutCount++;
    }
}
