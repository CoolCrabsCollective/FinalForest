//
// Created by william on 2022-04-02.
//

#ifndef LD50_CLIENT_LUMBERJACKGoATTACKSTATE_H
#define LD50_CLIENT_LUMBERJACKGoATTACKSTATE_H

#include "LumberJackState.h"
class LumberJackGoAttackState : public LumberJackState {
public:
    LumberJackGoAttackState(Forest* forest, LumberJack* lumberJack);

    void tick(float delta) override;
};

#endif //LD50_CLIENT_LUMBERJACKGoATTACKSTATE_H
