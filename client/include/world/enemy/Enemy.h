//
// Created by Sir Dick on 2022-04-03.
//

#ifndef LD50_COMMON_ENEMY_H
#define LD50_COMMON_ENEMY_H


#include "world/Renderable.h"
#include "world/Physical.h"
#include "world/Tickable.h"
#include "world/Damageable.h"
#include "world/Damager.h"
#include "world/Anime.h"

class Enemy : virtual public Renderable, virtual public Physical, virtual public Tickable, virtual public Damageable, virtual public Damager, virtual public Anime {

};


#endif //LD50_COMMON_ENEMY_H
