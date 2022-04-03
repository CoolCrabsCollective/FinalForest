//
// Created by Alexander Winter on 2022-04-03.
//

#ifndef LD50_CLIENT_LUMBERJACKLEAVESTATE_H
#define LD50_CLIENT_LUMBERJACKLEAVESTATE_H

#include "LumberJackState.h"

class LumberJackLeaveState : public LumberJackState {
public:
	LumberJackLeaveState(Forest* forest, LumberJack* lumberJack);

	void tick(float delta) override;
};


#endif //LD50_CLIENT_LUMBERJACKLEAVESTATE_H
