//
// Created by william on 2022-04-02.
//

#include "world/enemy/state/LumberJackIdleState.h"

LumberJackIdleState::LumberJackIdleState(Forest *forest, LumberJack *lumberJack) : LumberJackState(forest, lumberJack) {
    lumberJack->setDestination(lumberJack->getPosition());
}

void LumberJackIdleState::tick(float delta) {
    getLumberJack()->getBody()->SetLinearVelocity(*(new b2Vec2(0.0, 0.0)));
}
