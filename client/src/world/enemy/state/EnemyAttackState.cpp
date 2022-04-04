//
// Created by william on 2022-04-02.
//

#include "world/enemy/state/EnemyAttackState.h"
#include "world/enemy/state/EnemyIdleState.h"

EnemyAttackState::EnemyAttackState(LumberJack* lumberJack, Damageable* target)
	: EnemyState(lumberJack), target(target) {

}

void EnemyAttackState::tick(float delta) {
    LumberJack* lumberJack = getLumberJack();

	if(target == nullptr || target->isDestroyed()) {
		lumberJack->setState(std::make_shared<EnemyIdleState>(lumberJack));
		lumberJack->resetAnimationState();
		lumberJack->targetNearestTree();
		return;
	}

    if(b2DistanceSquared(lumberJack->getDestination(), lumberJack->getPosition()) < MIN_DISTANCE_FOR_CONTACT * MIN_DISTANCE_FOR_CONTACT) {

		lumberJack->getBody()->SetLinearVelocity(*(new b2Vec2(0.0, 0.0)));

		lumberJack->setMsSinceLastAttack(lumberJack->getMsSinceLastAttack() + delta);
		if (lumberJack->getMsSinceLastAttack() >= lumberJack->getMsAttackInterval()) {
			lumberJack->attack(target);
			lumberJack->animate(delta);
			lumberJack->setMsSinceLastAttack(0.0f);
		}
    }

	if (target->isDestroyed()) {
		Tree* tree = dynamic_cast<Tree*>(target);
		if(tree)
			getForest()->killTree(tree);

		lumberJack->setState(std::make_shared<EnemyIdleState>(lumberJack));
		lumberJack->targetNearestTree();

		lumberJack->resetAnimationState();
	}
}
