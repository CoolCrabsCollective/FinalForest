//
// Created by william on 2022-04-02.
//

#include "world/state/LumberJackAttackState.h"
#include "GameAssets.h"

LumberJackAttackState::LumberJackAttackState(Forest *forest, LumberJack *lumberJack) : LumberJackState(forest, lumberJack) {
    lumberJack->setDestination(lumberJack->getPosition());
}

void LumberJackAttackState::tick(float delta) {
    LumberJack* lumberJack = getLumberJack();
    Tree* target = lumberJack->getTarget();

    target->damage(lumberJack->getAttack() * (delta / 1000));

    if (target->isDestroyed()) {
        getForest()->killTree(target);
    }

    lumberJack->getBody()->SetLinearVelocity(*(new b2Vec2(0.0, 0.0)));
}
