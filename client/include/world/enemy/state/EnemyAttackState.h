//
// Created by william on 2022-04-02.
//

#ifndef LD50_CLIENT_LUMBERJACKGoATTACKSTATE_H
#define LD50_CLIENT_LUMBERJACKGoATTACKSTATE_H

#include "EnemyState.h"
#include "world/Damageable.h"

class EnemyAttackState : public EnemyState {
	Damageable* target;
public:
    EnemyAttackState(Enemy* enemy, Damageable* target);

    void tick(float delta) override;
};

#endif //LD50_CLIENT_LUMBERJACKGoATTACKSTATE_H
