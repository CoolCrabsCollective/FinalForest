//
// Created by Alexander Winter🤤 on 2022-04-03.
//

#include "world/enemy/state/EnemyLeaveState.h"
#include "ForestScreen.h"

EnemyLeaveState::EnemyLeaveState(Enemy* enemy)
		: EnemyState(enemy) {
	b2Vec2 newPos = enemy->getPosition() - b2Vec2(50.0f, 50.0f);
	newPos.Normalize();
	newPos *= 200.0f;
	newPos += enemy->getPosition();

	enemy->setDestination(newPos);
}

void EnemyLeaveState::tick(float delta) {
	if(b2DistanceSquared(getEnemy()->getPosition(), b2Vec2(50.0f, 50.0f)) > 100.0f * 100.0f)
	{
		getForest()->sendToCompost(getEnemy());
	}
}
