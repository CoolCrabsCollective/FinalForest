//
// Created by cedric on 2022-04-02.
//

#ifndef LD50_COMMON_SQUIRRELSTATE_H
#define LD50_COMMON_SQUIRRELSTATE_H

#include "world/Squirrel.h"
class SquirrelState {
    Squirrel* squirrel;
    Forest* forest;
public:
    SquirrelState(Forest* forest, Squirrel* squirrel);
    void tick(float delta);
    Squirrel* getSquirrel();
};


#endif //LD50_COMMON_SQUIRRELSTATE_H
