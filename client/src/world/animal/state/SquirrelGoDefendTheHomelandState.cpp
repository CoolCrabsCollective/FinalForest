//
// Created by Sir Dick on 2022-04-03.
//

#include "world/animal/state/SquirrelGoDefendTheHomelandState.h"

SquirrelGoDefendTheHomelandState::SquirrelGoDefendTheHomelandState(Squirrel* squirrel, Tree* tree)
        : SquirrelState(squirrel)
{
    this->tree = tree;
    squirrel->setDestination(tree->getPosition());
}

void SquirrelGoDefendTheHomelandState::tick(float delta) {

    if(b2Distance(this->getSquirrel()->getPosition(), this->tree->getPosition()) < 3.f)
    {
        this->getForest().sendToCompost(getSquirrel());
        tree->addSquirrelTurret();
    }
}
