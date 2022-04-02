//
// Created by cedric on 2022-04-02.
//

#ifndef LD50_COMMON_GO_GATHER_STATE_H
#define LD50_COMMON_GO_GATHER_STATE_H

#include "SquirrelState.h"
#include "world/Tree.h"
class SquirrelGoGatherState : public SquirrelState {
    private:
        Tree* destination;
    public:
        SquirrelGoGatherState(Forest* forest, Squirrel* squirrel, Tree* tree);
};


#endif //LD50_COMMON_GO_GATHER_STATE_H
