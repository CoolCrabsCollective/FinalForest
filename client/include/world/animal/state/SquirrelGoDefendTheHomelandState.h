//
// Created by Sir Dick on 2022-04-03.
//

#ifndef LD50_COMMON_SQUIRRELGODEFENDTHEHOMELANDSTATE_H
#define LD50_COMMON_SQUIRRELGODEFENDTHEHOMELANDSTATE_H

#include "SquirrelState.h"
#include "world/tree/Tree.h"

class SquirrelGoDefendTheHomelandState : public SquirrelState {
    Tree* tree;
public:
    SquirrelGoDefendTheHomelandState(Squirrel* squirrel, Tree* tree);
    void tick(float delta) override;
};


#endif //LD50_COMMON_SQUIRRELGODEFENDTHEHOMELANDSTATE_H
