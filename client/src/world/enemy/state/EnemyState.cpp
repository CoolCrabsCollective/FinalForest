//
// Created by william on 2022-04-02.
//

#include "world/enemy/state/EnemyState.h"
#include "world/enemy/Enemy.h"


EnemyState::EnemyState(Enemy* enemy) : enemy(enemy) {

}

Enemy* EnemyState::getEnemy() {
    return enemy;
}

Forest* EnemyState::getForest() {
    return &this->enemy->getForest();
}
