//
// Created by Alexander Winter🤤 on 2022-04-03.
//

#include "world/animal/Wolf.h"
#include "world/Forest.h"
#include "GameAssets.h"
#include "world/animal/state/AnimalPatrolState.h"


Wolf::Wolf(Forest& forest, b2Vec2 position)
	: Animal(forest, position)
{
	setPower(1.0);
	speed = 20.0f;
	setMsAttackInterval(500);
	sprite.setTexture(*forest.getAssets().get(GameAssets::WOLF));

	this->state = std::make_shared<AnimalPatrolState>(this);
}

b2Vec2 Wolf::getSize() const {
	return b2Vec2(2.0f, 2.0f);
}

void Wolf::noEnemyLeft() {
	setState(std::make_shared<AnimalPatrolState>(this));
}
