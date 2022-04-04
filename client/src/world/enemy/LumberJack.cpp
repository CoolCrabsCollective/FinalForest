//
// Created by William Wells on 2022-04-02.
//

#include "world/enemy/state/EnemyIdleState.h"
#include "world/enemy/state/EnemyAttackState.h"

#include "world/enemy/LumberJack.h"
#include "world/Forest.h"
#include "GameAssets.h"
#include "Box2D/Box2D.h"
#include "SFML/Graphics/RenderTarget.hpp"
#include "ForestScreen.h"
#include "world/pathfinding/ForestPathFinder.h"
#include "world/enemy/state/EnemyLeaveState.h"
#include "world/animal/Bear.h"
#include "world/enemy/Enemy.h"

LumberJack::LumberJack(Forest& forest, b2Vec2 position) : Enemy(forest, position) {
    sprite.setTexture(*forest.getAssets().get(GameAssets::LUMBERJACKAXE));
    whiteSprite.setTexture(*forest.getAssets().get(GameAssets::WHITE_LUMBERJACK));
	debugSprite.setTexture(*forest.getAssets().get(GameAssets::WHITE_PIXEL));

	sound1.setBuffer(*forest.getAssets().get(GameAssets::AXE_TREE1));
	sound1.setVolume(100.0f);
	sound2.setBuffer(*forest.getAssets().get(GameAssets::AXE_TREE2));
	sound2.setVolume(100.0f);
	sound3.setBuffer(*forest.getAssets().get(GameAssets::AXE_TREE3));
	sound3.setVolume(100.0f);

    insertAttackFrame(forest.getAssets().get(GameAssets::LUMBERJACKAXE));
    insertAttackFrame(forest.getAssets().get(GameAssets::LUMBERJACKAXE_SWING));
}

void LumberJack::attack(Damageable* target) {
	Damager::attack(target);

	int sound = rand() % 3;

	if(sound == 0)
		sound1.play();
	else if(sound == 1)
		sound2.play();
	else if(sound == 2)
		sound3.play();
}

void LumberJack::tick(float delta) {
    if(this->isDestroyed())
    {
        this->getForest().sendToCompost(this);
        return;
    }

	for(Entity* entity : getForest().getObjects()) {
		Bear* bear = dynamic_cast<Bear*>(entity);

		if(bear) {
			if(b2DistanceSquared(bear->getPosition(), getPosition()) < 5.0f * 5.0f) {
				this->state = std::make_shared<EnemyLeaveState>(this);
				this->speed = 15.0f;
				break;
			}
		}
	}

	Enemy::tick(delta);
}

b2Vec2 LumberJack::getSize() const {
	return b2Vec2(1.5f, 1.5f);
}