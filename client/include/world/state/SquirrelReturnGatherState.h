//
// Created by cedric on 2022-04-02.
//

#ifndef LD50_COMMON_SQUIRRELRETURNGATHERSTATE_H
#define LD50_COMMON_SQUIRRELRETURNGATHERSTATE_H

#include "world/tree/Tree.h"
#include "SquirrelState.h"

#define MIN_GREAT_TREE_DISTANCE 6
class SquirrelReturnGatherState : public SquirrelState {
private:
  Tree* tree;
public:
    SquirrelReturnGatherState(Forest* forest, Squirrel* squirrel, Tree* previousTree);

void tick(float delta) override;
};


#endif //LD50_COMMON_SQUIRRELRETURNGATHERSTATE_H
