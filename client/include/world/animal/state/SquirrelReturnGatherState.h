//
// Created by scrub on 2022-04-02.
//

#ifndef LD50_COMMON_SQUIRRELRETURNGATHERSTATE_H
#define LD50_COMMON_SQUIRRELRETURNGATHERSTATE_H

#include "world/tree/Tree.h"
#include "SquirrelState.h"

#define MIN_GREAT_TREE_DISTANCE 6
class SquirrelReturnGatherState : public SquirrelState {
  Tree* tree;
public:
    SquirrelReturnGatherState(Squirrel* squirrel, Tree* previousTree);

	void tick(float delta) override;
};


#endif //LD50_COMMON_SQUIRRELRETURNGATHERSTATE_H
