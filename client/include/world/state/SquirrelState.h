//
// Created by cedric on 2022-04-02.
//

#ifndef LD50_COMMON_SQUIRRELSTATE_H
#define LD50_COMMON_SQUIRRELSTATE_H

#include "world/animal/Squirrel.h"
#include "world/Forest.h"

class Squirrel;

class SquirrelState {
    Squirrel* squirrel;
    Forest* forest;
public:
    SquirrelState(Forest* forest, Squirrel* squirrel);
    virtual void tick(float delta) = 0;
    Squirrel* getSquirrel();
    Forest* getForest();
};


#endif //LD50_COMMON_SQUIRRELSTATE_H
