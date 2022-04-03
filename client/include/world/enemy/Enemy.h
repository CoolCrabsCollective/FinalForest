//
// Created by cedric on 2022-04-03.
//

#ifndef LD50_COMMON_ENEMY_H
#define LD50_COMMON_ENEMY_H


#include "world/Renderable.h"
#include "world/Physical.h"
#include "world/Tickable.h"
#include "world/Damageable.h"
#include "world/Damager.h"
#include "world/Anime.h"

class Enemy : public Renderable, public Physical, public Tickable, public Damageable, public Damager, public Anime {

};


#endif //LD50_COMMON_ENEMY_H
