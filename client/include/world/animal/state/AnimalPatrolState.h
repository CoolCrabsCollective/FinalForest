//
// Created by Alexander Winter on 2022-04-03.
//

#ifndef LD50_CLIENT_ANIMALPATROLSTATE_H
#define LD50_CLIENT_ANIMALPATROLSTATE_H

#include "AnimalState.h"

class AnimalPatrolState : public AnimalState {
	float timeWaiting = 0.0f;
public:
	AnimalPatrolState(Animal* animal);

	void tick(float delta) override;
};


#endif //LD50_CLIENT_ANIMALPATROLSTATE_H
