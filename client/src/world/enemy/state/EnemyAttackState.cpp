//
// Created by william on 2022-04-02.
//

#include "world/enemy/state/EnemyAttackState.h"
#include "world/enemy/state/EnemyIdleState.h"
#include "world/enemy/LumberJack.h"

EnemyAttackState::EnemyAttackState(Enemy* enemy, Damageable* target)
	: EnemyState(enemy), target(target) {

}

void EnemyAttackState::tick(float delta) {
	Enemy* enemy = getEnemy();

	if(target == nullptr || target->isDestroyed()) {
		enemy->setState(std::make_shared<EnemyIdleState>(enemy));
		enemy->resetAnimationState();
		enemy->targetNearestTree();
		return;
	}

    if(b2DistanceSquared(enemy->getDestination(), enemy->getPosition()) < MIN_DISTANCE_FOR_CONTACT * MIN_DISTANCE_FOR_CONTACT) {

		enemy->getBody()->SetLinearVelocity(*(new b2Vec2(0.0, 0.0)));

		enemy->setMsSinceLastAttack(enemy->getMsSinceLastAttack() + delta);
		if (enemy->getMsSinceLastAttack() >= enemy->getMsAttackInterval()) {
			enemy->attack(target);
			enemy->animate(delta);
			enemy->setMsSinceLastAttack(0.0f);
		}
    }

	if (target->isDestroyed()) {
		Tree* tree = dynamic_cast<Tree*>(target);
		if(tree)
			getForest()->killTree(tree);

		enemy->setState(std::make_shared<EnemyIdleState>(enemy));
		enemy->targetNearestTree();

		enemy->resetAnimationState();
	}
}
