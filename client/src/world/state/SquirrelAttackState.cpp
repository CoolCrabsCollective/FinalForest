//
// Created by cedric on 2022-04-02.
//

#include "world/state/SquirrelAttackState.h"

SquirrelAttackState::SquirrelAttackState(Forest *forest, Squirrel *squirrel, Enemy *target) : SquirrelState(forest, squirrel) {
    this->target = target;
    squirrel->setDestination(target->getPosition());
}

void SquirrelAttackState::tick(float delta) {
    if (target->isDestroyed()) {
        getSquirrel()->targetNearestEnemy();
        return;
    }

    Squirrel* squirrel = getSquirrel();

    squirrel->attack(target);

    squirrel->getBody()->SetLinearVelocity(*(new b2Vec2(0.0, 0.0)));
}