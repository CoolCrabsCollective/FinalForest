//
// Created by Sir Dick on 2022-04-02.
//

#include "world/animal/state/AnimalIdleState.h"

AnimalIdleState::AnimalIdleState(Animal* animal)
	: AnimalState(animal)
{
	animal->setDestination(animal->getPosition());
}

void AnimalIdleState::tick(float delta) {
	getAnimal()->getBody()->SetLinearVelocity(*(new b2Vec2(0.0, 0.0)));
}
