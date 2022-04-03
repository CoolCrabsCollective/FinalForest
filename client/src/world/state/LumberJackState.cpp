//
// Created by william on 2022-04-02.
//

#include "world/state/LumberJackState.h"

LumberJackState::LumberJackState(Forest *forest, LumberJack *lumberJack) {
    this->forest = forest;
    this->lumberJack = lumberJack;
}

LumberJack* LumberJackState::getLumberJack() {
    return lumberJack;
}

Forest *LumberJackState::getForest() {
    return this->forest;
}