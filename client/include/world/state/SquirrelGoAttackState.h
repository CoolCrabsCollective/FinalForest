//
// Created by william on 2022-04-03.
//

#ifndef LD50_CLIENT_SQUIRRELGOATTACKSTATE_H
#define LD50_CLIENT_SQUIRRELGOATTACKSTATE_H

#include "SquirrelState.h"

class SquirrelGoAttackState : public SquirrelState {
private:
    Enemy* target;
public:
    SquirrelGoAttackState(Forest* forest, Squirrel* squirrel, Enemy* target);

    void tick(float delta) override;
};

#endif //LD50_CLIENT_SQUIRRELGOATTACKSTATE_H
