//
// Created by william on 2022-04-02.
//

#ifndef LD50_CLIENT_ENEMYIDLESTATE_H
#define LD50_CLIENT_ENEMYIDLESTATE_H

#include "EnemyState.h"

class EnemyIdleState : public EnemyState {
public:
    EnemyIdleState(LumberJack* lumberJack);

    void tick(float delta) override;
};

#endif //LD50_CLIENT_ENEMYIDLESTATE_H
