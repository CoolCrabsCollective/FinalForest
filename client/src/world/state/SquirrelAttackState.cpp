//
// Created by cedric on 2022-04-02.
//

#include "world/state/SquirrelAttackState.h"

SquirrelAttackState::SquirrelAttackState(Forest *forest, Squirrel *squirrel, Entity *target) : SquirrelState(forest, squirrel) {
//    squirrel->setDestination(target->getPosition());
}

void SquirrelAttackState::tick(float delta) {
//    Squirrel* squirrel = getSquirrel();
//    Entity* target = getTarget();
//
//    target->damage(squirrel->getAttack() * (delta / 1000));
//
//    if (target->isDestroyed()) {
//        getForest()->killTree(target);
//    }
//
//    squirrel->getBody()->SetLinearVelocity(*(new b2Vec2(0.0, 0.0)));
}