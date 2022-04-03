//
// Created by william on 2022-04-02.
//

#include "world/state/LumberJackAttackState.h"

LumberJackAttackState::LumberJackAttackState(Forest *forest, LumberJack *lumberJack) : LumberJackState(forest, lumberJack) {}

void LumberJackAttackState::tick(float delta) {
    LumberJack* lumberJack = getLumberJack();
    Tree* target = lumberJack->getTarget();

    target->damage(lumberJack->getAttack() * delta);

    if (target->isDestroyed()) {
        std::vector<Tree*> *aliveTrees = &getForest()->aliveTrees;
        for (int i = 0; i<aliveTrees->size(); i++) {
            if (aliveTrees->at(i) == target) {
                aliveTrees->erase(aliveTrees->begin() + i);
            }
        }
    }
}
