//
// Created by william on 2022-04-03.
//

#ifndef LD50_CLIENT_ANIMALGOATTACKSTATE_H
#define LD50_CLIENT_ANIMALGOATTACKSTATE_H

#include "AnimalState.h"

class AnimalGoAttackState : public AnimalState {
    Enemy* target;
public:
    AnimalGoAttackState(Animal* squirrel, Enemy* target);

    void tick(float delta) override;
};

#endif //LD50_CLIENT_ANIMALGOATTACKSTATE_H
