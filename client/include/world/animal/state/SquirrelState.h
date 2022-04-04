//
// Created by Alexander Winter on 2022-04-03.
//

#ifndef LD50_CLIENT_SQUIRRELSTATE_H
#define LD50_CLIENT_SQUIRRELSTATE_H

#include "AnimalState.h"

class SquirrelState : public AnimalState {
public:
	SquirrelState(Squirrel* squirrel)
		: AnimalState(dynamic_cast<Animal*>(squirrel)) {}

	inline Squirrel* getSquirrel() {
		return dynamic_cast<Squirrel*>(getAnimal());
	}
};


#endif //LD50_CLIENT_SQUIRRELSTATE_H
