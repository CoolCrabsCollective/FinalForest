//
// Created by scrub on 2022-04-03.
//

#ifndef LD50_COMMON_ANIMALMENU_H
#define LD50_COMMON_ANIMALMENU_H

#include "UI/Menu.h"

class AnimalMenu : public Menu {

public:
    AnimalMenu(const wiz::AssetLoader &assetLoader, Forest &forest);
};


#endif //LD50_COMMON_ANIMALMENU_H
