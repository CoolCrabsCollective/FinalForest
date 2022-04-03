//
// Created by cedric on 2022-04-02.
//

#ifndef LD50_COMMON_SQUIRRELATTACKSTATE_H
#define LD50_COMMON_SQUIRRELATTACKSTATE_H

#include "SquirrelState.h"
#include "world/enemy/LumberJack.h"

class SquirrelAttackState : public SquirrelState {
private:
    Enemy* target;
public:
    SquirrelAttackState(Forest* forest, Squirrel* squirrel, Enemy* target);

    void tick(float delta) override;
};



#endif //LD50_COMMON_SQUIRRELATTACKSTATE_H
