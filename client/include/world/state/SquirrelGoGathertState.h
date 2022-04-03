//
// Created by cedric on 2022-04-02.
//

#ifndef LD50_COMMON_GO_GATHER_STATE_H
#define LD50_COMMON_GO_GATHER_STATE_H

#include "SquirrelState.h"
#include "world/Tree.h"

#define MIN_TREE_DISTANCE 3.f
class SquirrelGoGatherState : public SquirrelState {
    private:
        Tree* tree;
    public:
        SquirrelGoGatherState(Forest* forest, Squirrel* squirrel, Tree* tree);

    void tick(float delta) override;
};

#endif //LD50_COMMON_GO_GATHER_STATE_H
