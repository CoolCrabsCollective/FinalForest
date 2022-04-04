//
// Created by scrub on 2022-04-02.
//

#include "world/animal/state/AnimalAttackState.h"
#include "world/animal/state/AnimalAttackState.h"
#include "world/enemy/state/LumberJackLeaveState.h"

AnimalAttackState::AnimalAttackState(Animal* animal, Enemy *target)
	: AnimalState(animal)
{
    this->target = target;
	animal->setDestination(target->getPosition());
}

void AnimalAttackState::tick(float delta) {
    if (target->isDestroyed()) {
        getAnimal()->targetNearestEnemy();
		return;
    }

	if(LumberJack* jack = dynamic_cast<LumberJack*>(target)) {
		if(std::dynamic_pointer_cast<LumberJackLeaveState>(jack->getState())) {
			getAnimal()->targetNearestEnemy();
			return;
		}
	}

    if(b2DistanceSquared(getAnimal()->getPosition(), target->getPosition()) < MIN_DISTANCE_FOR_CONTACT) {

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