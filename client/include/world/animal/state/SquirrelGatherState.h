//
// Created by Cedric on 2022-04-02.
//

#ifndef LD50_COMMON_SQUIRRELGATHERSTATE_H
#define LD50_COMMON_SQUIRRELGATHERSTATE_H

#include "SquirrelState.h"
#include "world/tree/Tree.h"

#define SQUIRREL_HARVESTING_TIME 3000.f

class SquirrelGatherState : public SquirrelState {
    float timeLeftHarvesting;
    Tree* harvestingTree;
public:
    SquirrelGatherState(Squirrel* squirrel, Tree* tree);

    void tick(float delta) override;
};


#endif //LD50_COMMON_SQUIRRELGATHERSTATE_H
