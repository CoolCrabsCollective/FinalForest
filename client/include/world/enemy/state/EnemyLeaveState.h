//
// Created by Alexander Winter on 2022-04-03.
//

#ifndef LD50_CLIENT_ENEMYLEAVESTATE_H
#define LD50_CLIENT_ENEMYLEAVESTATE_H

#include "EnemyState.h"

class EnemyLeaveState : public EnemyState {
public:
	EnemyLeaveState(LumberJack* lumberJack);

	void tick(float delta) override;
};


#endif //LD50_CLIENT_ENEMYLEAVESTATE_H
