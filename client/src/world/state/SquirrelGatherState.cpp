//
// Created by cedric on 2022-04-02.
//

#include "world/state/SquirrelGatherState.h"

SquirrelGatherState::SquirrelGatherState(Forest *forest, Squirrel *squirrel, Tree *tree) : SquirrelState(forest, squirrel) {
        this->harvestingTree = tree;
}