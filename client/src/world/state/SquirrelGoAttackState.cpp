//
// Created by william on 2022-04-03.
//

#include "world/state/SquirrelGoAttackState.h"
#include "world/state/SquirrelAttackState.h"

SquirrelGoAttackState::SquirrelGoAttackState(Forest *forest, Squirrel *squirrel, Enemy *target) : SquirrelState(forest, squirrel) {
    this->target = target;
    squirrel->setDestination(target->getPosition());
}

void SquirrelGoAttackState::tick(float delta) {
    if(b2DistanceSquared(getSquirrel()->getDestination(), target->getPosition()) < MIN_DISTANCE_FOR_CONTACT) {
        getSquirrel()->setState(std::make_shared<SquirrelAttackState>(this->getForest(), getSquirrel(), target));
        return;
    }
}