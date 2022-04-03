//
// Created by cedric on 2022-04-02.
//

#include "world/state/SquirrelIdleState.h"

SquirrelIdleState::SquirrelIdleState(Forest *forest, Squirrel *squirrel) : SquirrelState(forest, squirrel) {
    squirrel->setDestination(squirrel->getPosition());
}

void SquirrelIdleState::tick(float delta) {
    getSquirrel()->getBody()->SetLinearVelocity(*(new b2Vec2(0.0, 0.0)));
}
