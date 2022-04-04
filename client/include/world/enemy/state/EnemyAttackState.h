//
// Created by william on 2022-04-02.
//

#ifndef LD50_CLIENT_LUMBERJACKGoATTACKSTATE_H
#define LD50_CLIENT_LUMBERJACKGoATTACKSTATE_H

#include "EnemyState.h"

class EnemyAttackState : public EnemyState {
	Damageable* target;
public:
    EnemyAttackState(LumberJack* lumberJack, Damageable* target);

    void tick(float delta) override;
};

#endif //LD50_CLIENT_LUMBERJACKGoATTACKSTATE_H
