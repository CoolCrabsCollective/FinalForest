//
// Created by william on 2022-04-02.
//

#ifndef LD50_CLIENT_LUMBERJACKSTATE_H
#define LD50_CLIENT_LUMBERJACKSTATE_H

#include "world/enemy/LumberJack.h"
#include "world/Forest.h"

class LumberJack;

class LumberJackState {
    LumberJack* lumberJack;
    Forest* forest;
public:
    LumberJackState(Forest* forest, LumberJack *lumberJack);

    virtual void tick(float delta) = 0;

    LumberJack* getLumberJack();

    Forest* getForest();
};

#endif //LD50_CLIENT_LUMBERJACKSTATE_H
