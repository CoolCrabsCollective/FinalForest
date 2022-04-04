//
// Created by William on 2022-04-02.
//

#ifndef LD50_CLIENT_LUMBERJACK_H
#define LD50_CLIENT_LUMBERJACK_H

#include "world/enemy/state/EnemyState.h"
#include "SFML/Graphics/Drawable.hpp"
#include "world/Physical.h"
#include "world/Tickable.h"
#include "world/tree/Tree.h"
#include "world/Damager.h"
#include "world/Anime.h"
#include "SFML/Graphics/Sprite.hpp"
#include "Enemy.h"

#define MIN_DISTANCE_FOR_CONTACT 2.5f

class EnemyState;
class Enemy;

class LumberJack : public Enemy {
public:
	LumberJack(Forest& forest, b2Vec2 position);

	b2Vec2 getSize() const override;

    void tick(float delta) override;
};


#endif //LD50_CLIENT_LUMBERJACK_H
