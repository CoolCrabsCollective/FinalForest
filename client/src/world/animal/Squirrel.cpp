//
// Created by Alexander Winter🤤 on 2022-04-02.
//

#include "world/animal/state/AnimalIdleState.h"

#include <memory>
#include "world/animal/state/SquirrelGatherState.h"
#include "world/animal/state/SquirrelReturnGatherState.h"
#include "world/animal/state/AnimalAttackState.h"
#include "world/animal/Squirrel.h"
#include "world/Forest.h"
#include "GameAssets.h"
#include "Box2D/Box2D.h"
#include "ForestScreen.h"
#include "world/animal/state/AnimalAttackState.h"

Squirrel::Squirrel(Forest& forest, b2Vec2 position) : Animal(forest, position) {
    setPower(0.5);

    squirrelWalk = forest.getAssets().get(GameAssets::SQUIRREL);
    squirrelIdle = forest.getAssets().get(GameAssets::SQUIRREL_IDLE);
    squirrelNut = forest.getAssets().get(GameAssets::SQUIRREL_WITH_NUT);
    squirrelAttack = forest.getAssets().get(GameAssets::SQUIRREL_ARMORED);
	sprite.setTexture(*squirrelWalk);

	this->state = std::make_shared<AnimalIdleState>(this);
    // Update the squirrel count.
    forest.squirrelCount++;
}

b2Vec2 Squirrel::getSize() const {
	return {1.5f, 1.5f};
}

void Squirrel::draw(sf::RenderTarget& target, const sf::RenderStates& states) const {

	if(dynamic_pointer_cast<AnimalIdleState>(state).get() || dynamic_pointer_cast<SquirrelGatherState>(state).get())
		sprite.setTexture(*squirrelIdle);
	else if(dynamic_pointer_cast<SquirrelReturnGatherState>(state).get())
		sprite.setTexture(*squirrelNut);
	else if(dynamic_pointer_cast<AnimalAttackState>(state).get() ||
			dynamic_pointer_cast<AnimalAttackState>(state).get())
		sprite.setTexture(*squirrelAttack);
	else
		sprite.setTexture(*squirrelWalk);

	Animal::draw(target, states);
}

void Squirrel::noEnemyLeft() {
	getForest().assignToNextAvailableTree(this);
}

