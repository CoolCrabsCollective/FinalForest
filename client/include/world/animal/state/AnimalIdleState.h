//
// Created by Sir Dick on 2022-04-02.
//

#ifndef LD50_COMMON_SQUIRRELIDLESTATE_H
#define LD50_COMMON_SQUIRRELIDLESTATE_H

#include "AnimalState.h"

class AnimalIdleState : public AnimalState {
public:
    AnimalIdleState(Animal* animal);

    void tick(float delta) override;
};


#endif //LD50_COMMON_SQUIRRELIDLESTATE_H
