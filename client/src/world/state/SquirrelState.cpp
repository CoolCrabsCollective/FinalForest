//
// Created by cedric on 2022-04-02.
//

#include "world/state/SquirrelState.h"

SquirrelState::SquirrelState(Forest *forest, Squirrel *squirrel) {
    this->forest = forest;
    this->squirrel = squirrel;
}

Squirrel* SquirrelState::getSquirrel() {
    return squirrel;
}

Forest *SquirrelState::getForest() {
    return this->forest;
}
