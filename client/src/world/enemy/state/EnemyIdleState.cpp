//
// Created by william on 2022-04-02.
//

#include "world/enemy/state/EnemyIdleState.h"
#include "world/enemy/Enemy.h"

EnemyIdleState::EnemyIdleState(Enemy* enemy)
	: EnemyState(enemy)
{
	enemy->setDestination(enemy->getPosition());
}

void EnemyIdleState::tick(float delta) {
	getEnemy()->getBody()->SetLinearVelocity(*(new b2Vec2(0.0, 0.0)));
}
