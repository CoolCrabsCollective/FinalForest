//
// Created by william on 2022-04-02.
//

#ifndef LD50_CLIENT_LUMBERJACKIDLESTATE_H
#define LD50_CLIENT_LUMBERJACKIDLESTATE_H

#include "LumberJackState.h"
class LumberJackIdleState : public LumberJackState {
public:
    LumberJackIdleState(Forest* forest, LumberJack* lumberJack);

    void tick(float delta) override;
};

#endif //LD50_CLIENT_LUMBERJACKIDLESTATE_H
