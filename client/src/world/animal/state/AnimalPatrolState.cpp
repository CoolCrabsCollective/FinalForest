//
// Created by Alexander Winter on 2022-04-03.
//

#include "world/animal/state/AnimalPatrolState.h"

AnimalPatrolState::AnimalPatrolState(Animal* animal)
	: AnimalState(animal)
{
}

void AnimalPatrolState::tick(float delta) {
	if(b2DistanceSquared(animal->getDestination(), animal->getPosition()) < 1.0f) {
		timeWaiting += delta / 1000.0f;
	}

	if(timeWaiting > 3.0f) {
		float x = (rand() % 1000) / 1000.0f * 10.0f - 5.0f;
		float y = (rand() % 1000) / 1000.0f * 10.0f - 5.0f;

		b2Vec2 newDest = animal->getPosition() + b2Vec2(x, y);

		if(b2DistanceSquared(newDest, b2Vec2(50.0f, 50.0f)) > 50.0f * 50.0f) {
			b2Vec2 diff = newDest - b2Vec2(50.0f, 50.0f);
			diff.Normalize();
			diff *= 45.0f;
			newDest = b2Vec2(50.0f, 50.0f) + diff;
		}

		animal->setDestination(newDest);
		timeWaiting = 0.0f;
	}
	animal->targetNearestEnemy();
}
