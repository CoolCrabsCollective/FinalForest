//
// Created by Cedric on 2022-04-02.
//

#ifndef LD50_COMMON_SQUIRRELSTATE_H
#define LD50_COMMON_SQUIRRELSTATE_H

#include "world/Forest.h"
#include "world/Tickable.h"

class Animal;

class AnimalState : public Tickable {
    Animal* animal;
public:
    AnimalState(Animal* animal);

    virtual void tick(float delta) = 0;

	Animal* getAnimal();
    Forest& getForest();
};


#endif //LD50_COMMON_SQUIRRELSTATE_H
