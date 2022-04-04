//
// Created by william on 2022-04-02.
//

#include "world/enemy/state/LumberJackGoAttackState.h"
#include "world/enemy/state/LumberJackAttackState.h"

LumberJackGoAttackState::LumberJackGoAttackState(Forest *forest, LumberJack *lumberJack) : LumberJackState(forest, lumberJack) {}

void LumberJackGoAttackState::tick(float delta) {
    LumberJack* lumberJack = getLumberJack();
    if(b2DistanceSquared(lumberJack->getDestination(), lumberJack->getPosition()) < MIN_DISTANCE_FOR_CONTACT) {
        lumberJack->setState(std::make_shared<LumberJackAttackState>(this->getForest(), lumberJack));
        return;
    }
}
