//
// Created by Sir Dick on 2022-04-02.
//

#include <memory>

#include "world/animal/state/SquirrelGoGathertState.h"
#include "world/animal/state/SquirrelGatherState.h"
#include "ForestScreen.h"

SquirrelGoGatherState::SquirrelGoGatherState(Squirrel *squirrel, Tree *tree)
	: SquirrelState(squirrel)
{
    this->tree = tree;
    getAnimal()->setDestination(tree->getPosition());
}

void SquirrelGoGatherState::tick(float delta) {
    if(b2Distance(this->getAnimal()->getPosition(), this->tree->getPosition()) < MIN_TREE_DISTANCE)
    {
        this->getSquirrel()->setState(std::make_shared<SquirrelGatherState>(this->getSquirrel(), this->tree));
    }
}
