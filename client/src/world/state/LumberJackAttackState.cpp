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
        std::vector<Tree*> *aliveTrees = &getForest()->aliveTrees;
        for (int i = 0; i<aliveTrees->size(); i++) {
            if (aliveTrees->at(i) == target) {
                aliveTrees->erase(aliveTrees->begin() + i);
            }
        }
    }

    lumberJack->getBody()->SetLinearVelocity(*(new b2Vec2(0.0, 0.0)));
}
