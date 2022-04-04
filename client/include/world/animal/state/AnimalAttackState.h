//
// Created by william on 2022-04-03.
//

#ifndef LD50_CLIENT_ANIMALATTACKSTATE_H
#define LD50_CLIENT_ANIMALATTACKSTATE_H

#include "AnimalState.h"

class AnimalAttackState : public AnimalState {
    Enemy* target;
public:
    AnimalAttackState(Animal* squirrel, Enemy* target);

    void tick(float delta) override;
};

#endif //LD50_CLIENT_ANIMALATTACKSTATE_H
