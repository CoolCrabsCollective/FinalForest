//
// Created by william on 2022-04-02.
//

#ifndef LD50_CLIENT_ENEMYSTATE_H
#define LD50_CLIENT_ENEMYSTATE_H

#include "world/enemy/LumberJack.h"
#include "world/Forest.h"

class LumberJack;

class EnemyState {
    LumberJack* lumberJack;
public:
	EnemyState(LumberJack* lumberJack);

	[[deprecated]]
    EnemyState(Forest* forest, LumberJack* lumberJack);

    virtual void tick(float delta) = 0;

    LumberJack* getLumberJack();

    Forest* getForest();
};

#endif //LD50_CLIENT_ENEMYSTATE_H
