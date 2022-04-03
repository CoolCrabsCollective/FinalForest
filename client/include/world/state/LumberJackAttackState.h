//
// Created by william on 2022-04-02.
//

#ifndef LD50_CLIENT_LUMBERJACKATTACKSTATE_H
#define LD50_CLIENT_LUMBERJACKATTACKSTATE_H

#include "LumberJackState.h"
class LumberJackAttackState : public LumberJackState {
public:
    LumberJackAttackState(Forest* forest, LumberJack* lumberJack);

    void tick(float delta) override;
};

#endif //LD50_CLIENT_LUMBERJACKATTACKSTATE_H
