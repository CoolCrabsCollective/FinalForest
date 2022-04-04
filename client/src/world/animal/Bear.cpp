//
// Created by Alexander Winter on 2022-04-03.
//

#include "world/animal/Bear.h"
#include "world/Forest.h"
#include "GameAssets.h"
#include "world/animal/state/AnimalPatrolState.h"


Bear::Bear(Forest& forest, b2Vec2 position)
		: Animal(forest, position)
{
	setPower(5.0);
	sprite.setTexture(*forest.getAssets().get(GameAssets::BEAR));

	this->state = std::make_shared<AnimalPatrolState>(this);
}

b2Vec2 Bear::getSize() const {
	return b2Vec2(3.0f, 3.0f);
}

void Bear::noEnemyLeft() {
	setState(std::make_shared<AnimalPatrolState>(this));
}
