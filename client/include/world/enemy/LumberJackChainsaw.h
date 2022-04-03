//
// Created by William Wells on 2022-04-02.
//

#ifndef LD50_CLIENT_LUMBERJACKCHAINSAW_H
#define LD50_CLIENT_LUMBERJACKCHAINSAW_H


#include "LumberJack.h"

class LumberJackChainsaw : public LumberJack {
public:
    LumberJackChainsaw(Forest& forest, const b2Vec2& position);

};


#endif //LD50_CLIENT_LUMBERJACKCHAINSAW_H