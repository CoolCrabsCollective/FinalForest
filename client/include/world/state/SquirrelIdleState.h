//
// Created by cedric on 2022-04-02.
//

#ifndef LD50_COMMON_SQUIRRELIDLESTATE_H
#define LD50_COMMON_SQUIRRELIDLESTATE_H

#include "SquirrelState.h"
class SquirrelIdleState : public SquirrelState {
public:
    SquirrelIdleState(Forest* forest, Squirrel* squirrel);

    void tick(float delta) override;
};


#endif //LD50_COMMON_SQUIRRELIDLESTATE_H
