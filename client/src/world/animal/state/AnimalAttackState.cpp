//
// Created by scrub on 2022-04-02.
//

#include "world/animal/state/AnimalAttackState.h"

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

    Animal* animal = getAnimal();

    animal->attack(target);
    animal->getBody()->SetLinearVelocity(*(new b2Vec2(0.0, 0.0)));
}