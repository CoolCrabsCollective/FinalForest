//
// Created by cedric on 2022-04-02.
//

#ifndef LD50_COMMON_SQUIRRELGATHERSTATE_H
#define LD50_COMMON_SQUIRRELGATHERSTATE_H

#include "SquirrelState.h"
#include "world/Tree.h"

#define SQUIRREL_HARVESTING_TIME 3.f

class SquirrelGatherState : public SquirrelState {
private:
    float timeLeftHarvesting;
    Tree* harvestingTree;
public:
    SquirrelGatherState(Forest* forest, Squirrel* squirrel, Tree* tree);
};


#endif //LD50_COMMON_SQUIRRELGATHERSTATE_H
