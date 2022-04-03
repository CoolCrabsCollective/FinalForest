//
// Created by cedric on 2022-04-03.
//

#ifndef LD50_COMMON_ENEMY_H
#define LD50_COMMON_ENEMY_H


#include "Renderable.h"
#include "Physical.h"
#include "Tickable.h"
#include "Damageable.h"
#include "Damager.h"
#include "Anime.h"

class Enemy : public Renderable, public Physical, public Tickable, public Damageable, public Damager, public Anime {

};


#endif //LD50_COMMON_ENEMY_H
