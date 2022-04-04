//
// Created by scrub on 2022-04-02.
//

#include "world/animal/state/AnimalState.h"

AnimalState::AnimalState(Animal* animal)
	: animal(animal)
{}

Animal* AnimalState::getAnimal() {
    return animal;
}

Forest& AnimalState::getForest() {
    return getAnimal()->getForest();
}
