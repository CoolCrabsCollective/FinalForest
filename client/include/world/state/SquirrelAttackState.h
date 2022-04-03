//
// Created by cedric on 2022-04-02.
//

#ifndef LD50_COMMON_SQUIRRELATTACKSTATE_H
#define LD50_COMMON_SQUIRRELATTACKSTATE_H

#include "SquirrelState.h"

class SquirrelAttackState : public SquirrelState {
private:
    Entity* target;
public:
    SquirrelAttackState(Forest* forest, Squirrel* squirrel, Entity* target);

    void tick(float delta) override;

    Entity* getTarget();
};



#endif //LD50_COMMON_SQUIRRELATTACKSTATE_H
