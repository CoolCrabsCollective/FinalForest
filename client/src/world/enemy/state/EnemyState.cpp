//
// Created by william on 2022-04-02.
//

#include "world/enemy/state/EnemyState.h"


EnemyState::EnemyState(LumberJack* lumberJack) : lumberJack(lumberJack) {

}

EnemyState::EnemyState(Forest *forest, LumberJack *lumberJack) : lumberJack(lumberJack) {
    this->lumberJack = lumberJack;
}

LumberJack* EnemyState::getLumberJack() {
    return lumberJack;
}

Forest* EnemyState::getForest() {
    return &this->lumberJack->getForest();
}
