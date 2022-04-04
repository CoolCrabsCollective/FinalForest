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
#include "world/anime/AnimeAttack.h"
#include "SFML/Graphics/Sprite.hpp"
#include "Enemy.h"
#include "SFML/Audio/Sound.hpp"

#define MIN_DISTANCE_FOR_CONTACT 2.5f

class EnemyState;
class Enemy;

class LumberJack : public Enemy {
	sf::Sound sound1, sound2, sound3;
public:
	LumberJack(Forest& forest, b2Vec2 position);

	b2Vec2 getSize() const override;

    void tick(float delta) override;

	void attack(Damageable* target) override;
};


#endif //LD50_CLIENT_LUMBERJACK_H
