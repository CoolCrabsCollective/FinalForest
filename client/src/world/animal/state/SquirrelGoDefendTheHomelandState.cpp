//
// Created by Cedric on 2022-04-03.
//

#include "world/animal/state/SquirrelGoDefendTheHomelandState.h"

SquirrelGoDefendTheHomelandState::SquirrelGoDefendTheHomelandState(Squirrel* squirrel, Tree* tree)
        : SquirrelState(squirrel)
{
    this->tree = tree;
    squirrel->setDestination(tree->getPosition());
}

void SquirrelGoDefendTheHomelandState::tick(float delta) {

	if(tree->isDestroyed()) {
		getForest().assignToNextAvailableTree(getSquirrel());
		return;
	}

    if(b2DistanceSquared(this->getSquirrel()->getPosition(), this->tree->getPosition()) < 9.f)
    {
        this->getForest().sendToCompost(getSquirrel());
        tree->addSquirrelTurret();
    }
}
