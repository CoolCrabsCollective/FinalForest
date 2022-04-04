//
// Created by scrub on 2022-04-02.
//

#include "world/animal/state/AnimalAttackState.h"
#include "world/animal/state/AnimalAttackState.h"
#include "world/enemy/state/EnemyLeaveState.h"
#include "world/enemy/LumberJack.h"

AnimalAttackState::AnimalAttackState(Animal* animal, Enemy *target)
	: AnimalState(animal)
{
    this->target = target;
	animal->setDestination(target->getPosition());
}

void AnimalAttackState::tick(float delta) {
    if (target == nullptr || target->isDestroyed() || target->isLeaving()) {
        getAnimal()->targetNearestEnemy();
		return;
    }

    if(b2DistanceSquared(getAnimal()->getPosition(), target->getPosition()) < MIN_DISTANCE_FOR_CONTACT * MIN_DISTANCE_FOR_CONTACT) {

		getAnimal()->setMsSinceLastAttack(getAnimal()->getMsSinceLastAttack() + delta);

		if(getAnimal()->getMsSinceLastAttack() >= getAnimal()->getMsAttackInterval()) {
			getAnimal()->attack(target);
			getAnimal()->setMsSinceLastAttack(0.0f);
		}

		getAnimal()->getBody()->SetLinearVelocity(*(new b2Vec2(0.0, 0.0)));
    }
	else
		getAnimal()->setDestination(target->getPosition());
}