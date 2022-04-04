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

	animal->setMsSinceLastAttack(animal->getMsSinceLastAttack() + delta);

	if(animal->getMsSinceLastAttack() >= animal->getMsAttackInterval()) {
		animal->attack(target);
		animal->setMsSinceLastAttack(0.0f);
	}

    animal->getBody()->SetLinearVelocity(*(new b2Vec2(0.0, 0.0)));
}