//
// Created by william on 2022-04-03.
//

#include "world/animal/state/AnimalGoAttackState.h"
#include "world/animal/state/AnimalAttackState.h"

AnimalGoAttackState::AnimalGoAttackState(Animal* animal, Enemy *target)
	: AnimalState(animal)
{
    this->target = target;
	animal->setDestination(target->getPosition());
}

void AnimalGoAttackState::tick(float delta) {
    if (target->isDestroyed()) {
        getAnimal()->targetNearestEnemy();
		return;
    }

    getAnimal()->setDestination(target->getPosition());

    if(b2DistanceSquared(getAnimal()->getPosition(), target->getPosition()) < MIN_DISTANCE_FOR_CONTACT) {
        getAnimal()->setState(std::make_shared<AnimalAttackState>(getAnimal(), target));
        return;
    }
}