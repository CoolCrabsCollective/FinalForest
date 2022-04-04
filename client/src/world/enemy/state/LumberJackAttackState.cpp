//
// Created by william on 2022-04-02.
//

#include "world/enemy/state/LumberJackAttackState.h"
#include "GameAssets.h"
#include "world/enemy/state/LumberJackIdleState.h"

LumberJackAttackState::LumberJackAttackState(Forest *forest, LumberJack *lumberJack) : LumberJackState(forest, lumberJack) {
    lumberJack->setDestination(lumberJack->getPosition());
}

void LumberJackAttackState::tick(float delta) {
    LumberJack* lumberJack = getLumberJack();
    Tree* target = lumberJack->getTarget();

    lumberJack->getBody()->SetLinearVelocity(*(new b2Vec2(0.0, 0.0)));

    lumberJack->setMsSinceLastAttack(lumberJack->getMsSinceLastAttack() + delta);
    if (lumberJack->getMsSinceLastAttack() >= lumberJack->getMsAttackInterval()) {
        lumberJack->attack(target);
        lumberJack->animate(delta);
        lumberJack->setMsSinceLastAttack(0.0f);
    }

    if (target->isDestroyed()) {
        getForest()->killTree(target);

		lumberJack->setState(std::make_shared<LumberJackIdleState>(&lumberJack->getForest(), lumberJack));
		lumberJack->targetNearestTree();

        lumberJack->resetAnimationState();
    }
}
