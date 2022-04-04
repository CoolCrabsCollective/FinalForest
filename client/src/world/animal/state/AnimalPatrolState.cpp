//
// Created by Alexander Winter on 2022-04-03.
//

#include "world/animal/state/AnimalPatrolState.h"

AnimalPatrolState::AnimalPatrolState(Animal* animal)
	: AnimalState(animal)
{
	animal->setDestination(b2Vec2(50.0f, 45.0f));
}

void AnimalPatrolState::tick(float delta) {
	if(b2DistanceSquared(animal->getDestination(), animal->getPosition()) < 1.0f) {
		timeWaiting += delta / 1000.0f;
	}

	if(timeWaiting > 3.0f) {
		float x = (rand() % 1000) / 1000.0f * 20.0f - 10.0f;
		float y = (rand() % 1000) / 1000.0f * 20.0f - 10.0f;

		animal->setDestination(b2Vec2(50.0f + x, 50.0f + y));
		timeWaiting = 0.0f;
	}
	animal->targetNearestEnemy();
}
