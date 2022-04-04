//
// Created by william on 2022-04-02.
//

#include "world/enemy/state/EnemyIdleState.h"

EnemyIdleState::EnemyIdleState(LumberJack *lumberJack)
	: EnemyState(lumberJack)
{
    lumberJack->setDestination(lumberJack->getPosition());
}

void EnemyIdleState::tick(float delta) {
    getLumberJack()->getBody()->SetLinearVelocity(*(new b2Vec2(0.0, 0.0)));
}
