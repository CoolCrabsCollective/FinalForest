//
// Created by Cedric on 2022-04-02.
//

#ifndef LD50_COMMON_GO_GATHER_STATE_H
#define LD50_COMMON_GO_GATHER_STATE_H

#include "world/tree/Tree.h"
#include "SquirrelState.h"

#define MIN_TREE_DISTANCE 3.f
class SquirrelGoGatherState : public SquirrelState {
	Tree* tree;
public:
	SquirrelGoGatherState(Squirrel* squirrel, Tree* tree);

    void tick(float delta) override;
};

#endif //LD50_COMMON_GO_GATHER_STATE_H
