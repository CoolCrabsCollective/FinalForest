//
// Created by Cedric on 2022-04-02.
//

#ifndef LD50_COMMON_SQUIRRELATTACKSTATE_H
#define LD50_COMMON_SQUIRRELATTACKSTATE_H

#include "AnimalState.h"
#include "world/enemy/LumberJack.h"

class AnimalAttackState : public AnimalState {
    Enemy* target;
public:
    AnimalAttackState(Animal* animal, Enemy* target);

    void tick(float delta) override;
};



#endif //LD50_COMMON_SQUIRRELATTACKSTATE_H
